/*! \file histogram_matcher.cpp
    \brief Histogram Matching for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file is part of a Content-Based Image Retrieval (CBIR) system, focusing specifically on the histogram matching approach.
    It includes functions to load database histograms, compute histogram intersection, perform histogram matching, compute color
    histograms manually, and preprocess database images.
*/


#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "feature_utils.h"

namespace fs = std::filesystem;

/**
 * @brief Reads histogram data from a CSV file containing pre-computed histograms of images in the database. It parses the file line by
 * line, extracts the filename and histogram values, and constructs a vector of pairs containing the filename and corresponding histogram
 * as a cv::Mat.
 *
 * @param csvFilePath The path to the CSV file containing histogram data.
 * @param binsPerChannel The number of bins per color channel in the histogram.
 * @param databaseHistograms Output vector to store the loaded histograms and their corresponding filenames.
 * @throws std::runtime_error If there is an error while reading the CSV file.
 */
void loadDatabaseHistograms(const std::string& csvFilePath, int binsPerChannel,
    std::vector<std::pair<std::string, cv::Mat>>& databaseHistograms) {
    std::ifstream file(csvFilePath);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string filename;
        getline(iss, filename, ','); // Extract filename

        std::vector<float> bins;
        std::string binValue;
        while (getline(iss, binValue, ',')) {
            bins.push_back(std::stof(binValue));
        }

        // Check if the number of bins matches the expected size for a 3D histogram
        int expectedBinCount = binsPerChannel * binsPerChannel * binsPerChannel;

        // Create a 3D histogram from the flattened vector
        cv::Mat hist(3, std::vector<int>{binsPerChannel, binsPerChannel, binsPerChannel}.data(), CV_32F, bins.data());
        databaseHistograms.push_back(std::make_pair(filename, hist.clone())); // Clone the Mat to copy the data
    }
}

/**
 * @brief Computes the histogram intersection between two histograms.
 *
 * @param hist1 First histogram.
 * @param hist2 Second histogram.
 * @return float The histogram intersection value.
 */
float histogramIntersection(const cv::Mat& hist1, const cv::Mat& hist2) {
    CV_Assert(hist1.dims == hist2.dims && hist1.size == hist2.size && hist1.type() == hist2.type());
    float intersection = 0.0f;
    for (int r = 0; r < hist1.size[0]; ++r) {
        for (int g = 0; g < hist1.size[1]; ++g) {
            for (int b = 0; b < hist1.size[2]; ++b) {
                float value1 = hist1.at<float>(r, g, b);
                float value2 = hist2.at<float>(r, g, b);
                intersection += std::min(value1, value2);
            }
        }
    }
    return intersection;
}

/**
 * @brief Performs histogram matching between a target image and a database of images.
 *
 * @param targetImageFile Path to the target image file.
 * @param topN Number of top matching images to return.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 * @param csvFilePath Path to the CSV file containing database histogram data.
 * @return std::vector<std::string> Vector of filenames of the top N matching images.
 */
std::vector<std::string> performHistogramMatching(const std::string& targetImageFile, int topN, int binsPerChannel, const std::string& csvFilePath) {

    // Load the target image and compute its histogram manually
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);

    cv::Mat targetHist = compute3DColorHistogramManual(targetImage, binsPerChannel);

    std::vector<std::pair<std::string, cv::Mat>> databaseHistograms; // Pair of filename and histogram
    loadDatabaseHistograms(csvFilePath, binsPerChannel, databaseHistograms);

    // Compute histogram intersections with the target image
    std::vector<std::pair<float, std::string>> matches;

    for (const auto& [filename, hist] : databaseHistograms) {
        if (filename == targetImageFile) continue; // Skip if it's the target image

        float intersection = histogramIntersection(targetHist, hist);
        matches.push_back({ intersection, filename });
    }

    // Sort based on the intersection (higher is better)
    std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        return a.first > b.first; 
        });

    std::vector<std::string> topMatches;
    for (int i = 0; i < std::min(topN, static_cast<int>(matches.size())); ++i) {
        topMatches.push_back(matches[i].second);
    }

    return topMatches;
}

/**
 * @brief Computes a normalized color histogram manually from an input image.
 *
 * @param image Input image.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 * @return std::vector<float> Normalized color histogram.
 */
std::vector<float> computeColorHistogramManual(const cv::Mat& image, int binsPerChannel) {
    // Define the range for each bin
    float range = 256.0f / binsPerChannel;

    // Initialize the histogram
    std::vector<float> histogram(binsPerChannel * binsPerChannel * binsPerChannel, 0.0f);

    // Calculate the histogram
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            int binR = static_cast<int>(pixel[2] / range);
            int binG = static_cast<int>(pixel[1] / range);
            int binB = static_cast<int>(pixel[0] / range);

            histogram[binR * binsPerChannel * binsPerChannel + binG * binsPerChannel + binB]++;
        }
    }

    // Normalize the histogram
    float totalPixels = image.rows * image.cols;
    for (float& value : histogram) {
        value /= totalPixels;
    }

    return histogram;
}

/**
 * @brief Preprocesses images in a given directory, computing and saving their histograms to a CSV file.
 *
 * @param directoryPath Path to the directory containing images.
 * @param outputFile Path to the output CSV file to save histogram data.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 */
void preprocessDatabaseImages(const std::string& directoryPath, const std::string& outputFile, const std::int32_t& binsPerChannel) {
    std::ofstream out(outputFile);

    // Iterate over all files in the given directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        // Check if the entry is a file and has a .jpg extension (you can add more conditions for other formats)
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (image.empty()) {
                std::cerr << "Unable to read image: " << imagePath << std::endl;
                continue; // Skip to the next file if this one can't be read
            }

            // Compute and save the histogram
            std::vector<float> histogram = computeColorHistogramManual(image, binsPerChannel);
            out << imagePath;
            for (float value : histogram) {
                out << "," << value;
            }
            out << "\n";
        }
    }
}

/**
 * @brief Performs histogram calculation for the images in the database directory and saves the histograms to a CSV file.
 *
 * @param directoryPath Path to the directory containing images.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 * @param outputFile Path to the output CSV file to save histogram data.
 */
void performHistogramCalculation(const std::string& directoryPath, int binsPerChannel, const std::string& outputFile)
{
    preprocessDatabaseImages(directoryPath, outputFile, binsPerChannel);

    std::cout << "\nHistograms computed and saved to " << outputFile << "\n\n" << std::endl;
}
