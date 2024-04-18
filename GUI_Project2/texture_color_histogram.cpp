/*! \file texture_color_histogram.cpp
    \brief Texture And Color for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file contains the implementation of functions for computing color and texture histograms, combining them, 
    performing matching tasks, and saving/loading histograms to/from CSV files.The system is designed for 
    content-based image retrieval, where images are compared based on their color and texture features.
*/
#include <opencv2/opencv.hpp>
#include <vector>
#include "feature_utils.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

/**
 * @brief Compute the histogram of gradient magnitudes.
 * 
 * @param gradient The input gradient image.
 * @param bins The number of bins for the histogram.
 * @return A vector representing the histogram of gradient magnitudes.
 */
std::vector<float> computeGradientHistogram(const cv::Mat& gradient, int bins) {
    std::vector<float> histogram(bins, 0.0f);
    float maxVal = *std::max_element(gradient.begin<float>(), gradient.end<float>());
    float binWidth = maxVal / bins;

    for (int i = 0; i < gradient.rows; ++i) {
        for (int j = 0; j < gradient.cols; ++j) {
            int binIndex = static_cast<int>(gradient.at<float>(i, j) / binWidth);
            binIndex = std::min(binIndex, bins - 1);
            histogram[binIndex]++;
        }
    }

    // Normalize the histogram
    float total = static_cast<float>(gradient.rows * gradient.cols);
    for (float& value : histogram) {
        value /= total;
    }

    return histogram;
}

/**
 * @brief Compute the texture histogram of an image using Sobel magnitude.
 * 
 * @param image The input image.
 * @param magnitudeBins The number of bins for the histogram.
 * @return A vector representing the texture histogram.
 */
std::vector<float> computeTextureHistogram(const cv::Mat& image, int magnitudeBins) {
    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Apply Sobel operator to get gradients in x and y directions
    cv::Mat grad_x, grad_y;
    cv::Sobel(gray, grad_x, CV_32F, 1, 0);
    cv::Sobel(gray, grad_y, CV_32F, 0, 1);

    // Compute gradient magnitudes and orientations
    cv::Mat magnitude, orientation;
    cv::cartToPolar(grad_x, grad_y, magnitude, orientation);

    // Compute histogram for gradient magnitudes
    std::vector<float> magHist = computeGradientHistogram(magnitude, magnitudeBins);    

    return magHist;
}

/**
 * @brief Calculate the Euclidean distance between two feature vectors.
 * 
 * @param featureVec1 The first feature vector.
 * @param featureVec2 The second feature vector.
 * @return The Euclidean distance between the two feature vectors.
 */
float calculateFeatureDistance(const std::vector<float>& featureVec1, const std::vector<float>& featureVec2) {
    assert(featureVec1.size() == featureVec2.size());
    float distance = 0.0f;
    for (size_t i = 0; i < featureVec1.size(); ++i) {
        distance += std::pow(featureVec1[i] - featureVec2[i], 2);
    }
    return std::sqrt(distance);
}

/**
 * @brief Load combined color and texture histograms from a CSV file.
 * 
 * @param csvFilePath The path to the CSV file.
 * @param databaseFeatures Output parameter containing the loaded histograms.
 */
void loadCombinedDatabaseHistograms(const std::string& csvFilePath,
    std::vector<std::pair<std::string, std::vector<float>>>& databaseFeatures) {
    std::ifstream file(csvFilePath);
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string filename;
        getline(iss, filename, ','); // Extract filename

        std::vector<float> features;
        std::string value;
        while (getline(iss, value, ',')) {
            features.push_back(std::stof(value));
        }

        databaseFeatures.push_back(std::make_pair(filename, std::move(features)));
    }
}

/**
 * @brief Combine the color and texture histograms into a single feature vector.
 * 
 * @param colorHist The color histogram.
 * @param textureHist The texture histogram.
 * @return The combined histogram.
 */
std::vector<float> combineHistograms(const cv::Mat& colorHist, const std::vector<float>& textureHist) {
    // Convert color histogram Mat to vector
    std::vector<float> colorHistVector(colorHist.begin<float>(), colorHist.end<float>());

    // Combine histograms without additional normalization
    std::vector<float> combinedHistogram;
    combinedHistogram.reserve(colorHistVector.size() + textureHist.size());
    combinedHistogram.insert(combinedHistogram.end(), colorHistVector.begin(), colorHistVector.end());
    combinedHistogram.insert(combinedHistogram.end(), textureHist.begin(), textureHist.end());

    return combinedHistogram;
}

/**
 * @brief Perform texture and color matching task.
 * 
 * @param targetImageFile The path to the target image.
 * @param topN The number of top matches to retrieve.
 * @param colorBinsPerChannel The number of bins per channel for the color histogram.
 * @param textureBins The number of bins for the texture histogram.
 * @param outputFile The path to the CSV file containing database histograms.
 * @return A vector of filenames of the top matches.
 */
std::vector<std::string>  performTextureAndColorMatchingTask(const std::string& targetImageFile, int topN, int colorBinsPerChannel, int textureBins, const std::string& outputFile) {
    // Load image
    cv::Mat image = cv::imread(targetImageFile, cv::IMREAD_COLOR);

    // Compute color histogram
    cv::Mat colorHist = compute3DColorHistogramManual(image, colorBinsPerChannel);

    // Compute texture histogram
    std::vector<float> textureHist = computeTextureHistogram(image, textureBins);

    // Combine color and texture histograms into a single feature vector
    std::vector<float> featureVector;
    featureVector.insert(featureVector.end(), colorHist.begin<float>(), colorHist.end<float>());
    featureVector.insert(featureVector.end(), textureHist.begin(), textureHist.end());

    // Combine and normalize histograms

    std::vector<float> queryFeatures = combineHistograms(colorHist, textureHist);
    // Load database histograms and combine them
    std::vector<std::pair<std::string, std::vector<float>>> databaseFeatures;
    loadCombinedDatabaseHistograms(outputFile, databaseFeatures);

    // Compare query image histogram with database histograms
    std::vector<std::pair<float, std::string>> matches;
    for (const auto& [imageName, features] : databaseFeatures) {
        // Skip comparison if the current image is the target image
        if (std::filesystem::path(imageName).filename() == std::filesystem::path(targetImageFile).filename()) {
            continue; // Skip this image
        }

        float distance = calculateFeatureDistance(queryFeatures, features);
        matches.push_back({ distance, imageName });
    }


    // Sort matches based on distance
    std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
        });

    std::vector<std::string> topMatches;
    for (int i = 0; i < std::min(topN, static_cast<int>(matches.size())); ++i) {
        topMatches.push_back(matches[i].second);
    }

    return topMatches;
}

/**
 * @brief Save the combined color and texture histograms to a CSV file.
 * 
 * @param outputPath The path to the output CSV file.
 * @param histograms The combined histograms to be saved.
 */
void saveCombinedHistogramsToCSV(const std::string& outputPath,
    const std::vector<std::pair<std::string, std::vector<float>>>& histograms) {
    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open output file.");
    }

    for (const auto& [filename, histogram] : histograms) {
        outputFile << filename;
        for (const auto& value : histogram) {
            outputFile << ", " << value;
        }
        outputFile << "\n";
    }
}

/**
 * @brief Perform texture and color calculation task for a directory of images.
 * 
 * @param directoryPath The path to the directory containing images.
 * @param colorBinsPerChannel The number of bins per channel for the color histogram.
 * @param textureBins The number of bins for the texture histogram.
 * @param outputPath The path to save the combined histograms CSV file.
 */
void performTextureAndColorCalculationTask(const std::string& directoryPath, int colorBinsPerChannel, int textureBins, const std::string& outputPath) {
    std::vector<std::pair<std::string, std::vector<float>>> combinedHistograms;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jpg") {
            cv::Mat image = cv::imread(entry.path().string(), cv::IMREAD_COLOR);
            if (image.empty()) {
                std::cerr << "Error reading image: " << entry.path() << std::endl;
                continue;
            }

            // Compute the color histogram
            cv::Mat colorHist = compute3DColorHistogramManual(image, colorBinsPerChannel);

            // Convert color histogram Mat to vector
            std::vector<float> colorHistVector(colorHist.begin<float>(), colorHist.end<float>());

            // Compute the texture histogram
            std::vector<float> textureHist = computeTextureHistogram(image, textureBins);

            // Combine color and texture histograms
            std::vector<float> combinedHist(colorHistVector);
            combinedHist.insert(combinedHist.end(), textureHist.begin(), textureHist.end());

            combinedHistograms.push_back({ entry.path().string(), combinedHist });
        }
    }

    // Save combined histograms to CSV
    try {
        saveCombinedHistogramsToCSV(outputPath, combinedHistograms);
        std::cout << "Histograms saved to " << outputPath << "\n\n" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to save histograms: " << e.what() << std::endl;
    }
}