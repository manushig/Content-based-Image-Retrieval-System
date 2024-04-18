/*! \file multi_histogram_matcher.cpp
    \brief Multi-Histogram Matching for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file implements a Content-Based Image Retrieval (CBIR) system utilizing multi-histogram matching.
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
#include <cstring>
#include "feature_utils.h"

namespace fs = std::filesystem;

/**
 * @brief Combines multiple histograms into a single feature vector.
 *
 * @param histograms Vector of histograms to combine.
 * @return std::vector<float> Combined histogram feature vector.
 */
std::vector<float> combineHistograms(const std::vector<std::vector<float>>& histograms) {
    std::vector<float> combined;
    for (const auto& hist : histograms) {
        combined.insert(combined.end(), hist.begin(), hist.end());
    }
    return combined;
}

/**
 * @brief Computes a normalized color histogram manually for a specified region of the image.
 *
 * @param image Input image.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 * @param startX X-coordinate of the starting point of the region.
 * @param startY Y-coordinate of the starting point of the region.
 * @param width Width of the region.
 * @param height Height of the region.
 * @return std::vector<float> Normalized color histogram for the specified region.
 */
std::vector<float> computePartialHistogram(const cv::Mat& image, int binsPerChannel,
    int startX, int startY, int width, int height) {
    // Define the range for each bin
    float range = 256.0f / binsPerChannel;

    // Initialize the histogram
    std::vector<float> histogram(binsPerChannel * binsPerChannel * binsPerChannel, 0.0f);

    // Calculate the histogram for the specified region
    for (int y = startY; y < startY + height; ++y) {
        for (int x = startX; x < startX + width; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            int binR = static_cast<int>(pixel[2] / range);
            int binG = static_cast<int>(pixel[1] / range);
            int binB = static_cast<int>(pixel[0] / range);

            histogram[binR * binsPerChannel * binsPerChannel + binG * binsPerChannel + binB]++;
        }
    }

    // Normalize the histogram
    float totalPixels = width * height;
    for (float& value : histogram) {
        value /= totalPixels;
    }

    return histogram;
}

/**
 * @brief Reads histogram data from a CSV file containing pre-computed histograms of images in the database.
 *
 * @param csvFilePath Path to the CSV file containing histogram data.
 * @param binsPerChannel Number of bins per color channel in the histogram.
 * @param databaseHistograms Output vector to store the loaded histograms and their corresponding filenames.
 * @throws std::runtime_error If there is an error while reading the CSV file.
 */
void loadDatabaseMultiHistograms(const std::string& csvFilePath, int binsPerChannel,
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
        
        int expectedBinCount = binsPerChannel * binsPerChannel * binsPerChannel * 2; // For two histograms combined
        if (bins.size() != expectedBinCount) {
            std::cerr << "Histogram size mismatch for " << filename << std::endl;
            continue;
        }

        // Create a 1D cv::Mat for the histogram data and then reshape it to 3D
        cv::Mat flatHist = cv::Mat(bins.size(), 1, CV_32F, bins.data());


        int newSize[] = { binsPerChannel, binsPerChannel, binsPerChannel * 2 }; // New shape
        cv::Mat hist = flatHist.reshape(0, 3, newSize);
        if (hist.total() != bins.size()) {
            throw std::runtime_error("Reshape operation failed due to size mismatch.");
        }
        databaseHistograms.push_back(std::make_pair(filename, hist.clone())); // Clone to ensure continuity


    }
}

/**
 * @brief Computes the histogram intersection between two histograms represented as vectors.
 *
 * @param start1 Iterator to the beginning of the first histogram.
 * @param end1 Iterator to the end of the first histogram.
 * @param start2 Iterator to the beginning of the second histogram.
 * @return float Histogram intersection value.
 */
float histogramIntersection(const std::vector<float>::const_iterator& start1,
    const std::vector<float>::const_iterator& end1,
    const std::vector<float>::const_iterator& start2) {
    float intersection = 0.0f;
    auto it1 = start1;
    auto it2 = start2;
    while (it1 != end1) {
        intersection += std::min(*it1, *it2);
        ++it1;
        ++it2;
    }
    return intersection;
}

/**
 * @brief Performs multi-histogram matching between a target image and a database of images.
 *
 * @param targetImageFile Path to the target image file.
 * @param topN Number of top matching images to return.
 * @param binsPerChannel Number of bins per color channel in the histograms.
 * @param outputFile Path to the CSV file containing database histogram data.
 * @return std::vector<std::string> Vector of filenames of the top N matching images.
 */
std::vector<std::string> performMultiHistogramMatchingTask(const std::string& targetImageFile, int topN, int binsPerChannel, const std::string& outputFile){
    // Load the target image and compute its histograms manually
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);
    if (targetImage.empty()) {
        std::cerr << "Error loading target image." << std::endl;
    }

    // Compute histograms for different parts of the target image
    std::vector<float> topHalfHist = computePartialHistogram(targetImage, binsPerChannel, 0, 0, targetImage.cols, targetImage.rows / 2);
    std::vector<float> bottomHalfHist = computePartialHistogram(targetImage, binsPerChannel, 0, targetImage.rows / 2, targetImage.cols, targetImage.rows / 2);

    // Combine histograms of the target image
    std::vector<float> combinedTargetHist = combineHistograms({ topHalfHist, bottomHalfHist });

    // Load database histograms
    std::vector<std::pair<std::string, cv::Mat>> databaseHistograms;
    loadDatabaseMultiHistograms(outputFile, binsPerChannel, databaseHistograms);

    // Compute histogram intersections with the target image
    std::vector<std::pair<float, std::string>> matches;
    for (const auto& [filename, histMat] : databaseHistograms) {
        if (filename == targetImageFile) continue; // Skip the target image

        // Ensure histMat is continuous and has a type of CV_32F for comparison
        if (!histMat.isContinuous() || histMat.type() != CV_32F) {
            std::cerr << "Histogram data is not in expected format." << std::endl;
            continue;
        }

        // Convert Mat to a vector for comparison
        std::vector<float> dbHist(histMat.begin<float>(), histMat.end<float>());

        // Calculate intersection for each part and then average them
        float intersectionTop = histogramIntersection(combinedTargetHist.begin(), combinedTargetHist.begin() + topHalfHist.size(), dbHist.begin());
        float intersectionBottom = histogramIntersection(combinedTargetHist.begin() + topHalfHist.size(), combinedTargetHist.end(), dbHist.begin() + topHalfHist.size());

        float combinedIntersection = (intersectionTop + intersectionBottom) / 2;

        matches.push_back({ combinedIntersection, filename });
    }

    // Sort based on the combined intersection (higher is better)
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
 * @brief Preprocesses images in a given directory, computing histograms for different parts of each image and saving their combined histograms to a CSV file.
 *
 * @param directoryPath Path to the directory containing images.
 * @param outputFile Path to the output CSV file to save histogram data.
 * @param binsPerChannel Number of bins per color channel in the histograms.
 */
void preprocessMultiHistogramDatabaseImages(const std::string& directoryPath, const std::string& outputFile, const std::int32_t& binsPerChannel) {
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

            // Compute histograms for different parts
            std::vector<float> topHalfHist = computePartialHistogram(image, binsPerChannel, 0, 0, image.cols, image.rows / 2);
            std::vector<float> bottomHalfHist = computePartialHistogram(image, binsPerChannel, 0, image.rows / 2, image.cols, image.rows / 2);

            // Combine histograms
            std::vector<float> combinedHist = combineHistograms({ topHalfHist, bottomHalfHist });

            // Save combined histogram
            out << imagePath;
            for (float value : combinedHist) {
                out << "," << value;
            }
            out << "\n";
        }
    }
}

/**
 * @brief Performs the preprocessing step for the multi-histogram image database.
 *
 * @param directoryPath Path to the directory containing images.
 * @param binsPerChannel Number of bins per color channel in the histograms.
 * @param outputFile Path to the output CSV file to save histogram data.
 */
void performMultiHistogramCalculationTask(const std::string& directoryPath, int binsPerChannel, const std::string& outputFile)
{
    preprocessMultiHistogramDatabaseImages(directoryPath, outputFile, binsPerChannel);

    std::cout << "Histograms computed and saved to " << outputFile << "\n\n" << std::endl;
}