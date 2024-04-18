/*! \file custom_design.cpp
    \brief Custom Design for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file is part of a Content-Based Image Retrieval (CBIR) system, focusing specifically
    on custom design features for image retrieval.
*/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm> 
#include <filesystem>
#include <fstream>
#include <sstream>
#include "feature_utils.h"
#include "csv_util.h"  
#define NOMINMAX
#include <windows.h>
#include <Shlwapi.h> 
#pragma comment(lib, "Shlwapi.lib")
#include <string>
#include <cstring>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;
using namespace cv::dnn;

struct FeatureVector {
    vector<float> sunsetColorHistogram; // Emphasizing sunset colors
    vector<float> textureFeatures;
    vector<float> dnnFeatures;
    vector<float> edgeFeatures; // New: for horizon line detection
};

/**
* @brief Normalize a vector.
* @param v The vector to be normalized.
* @return The normalized vector.
*/
vector<float> normalizeVector(const vector<float>& v) {
    vector<float> nv(v.size());
    float norm = sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0f));
    if (norm > 0) {
        std::transform(v.begin(), v.end(), nv.begin(), [norm](float val) { return val / norm; });
    }
    return nv;
}


/**
* @brief Calculate the Euclidean distance between two feature vectors.
* 
* @param featureVec1 The first feature vector.
* @param featureVec2 The second feature vector.
* @return The Euclidean distance between the two feature vectors.
*/
float euclideanDistance(const std::vector<float>& featureVec1, const std::vector<float>& featureVec2) {
    std::cout << "FeatureVec1 size: " << featureVec1.size() << ", FeatureVec2 size: " << featureVec2.size() << std::endl;
    assert(featureVec1.size() == featureVec2.size());
    float distance = 0.0f;
    for (size_t i = 0; i < featureVec1.size(); ++i) {
        distance += std::pow(featureVec1[i] - featureVec2[i], 2);
    }
    return std::sqrt(distance);
}

/**
* @brief Extract the color histogram emphasizing sunset colors from an image.
* 
* @param image The input image.
* @return The normalized histogram vector.
*/
vector<float> extractSunsetColorHistogram(const Mat& image) {
    // Adjust histogram calculation to emphasize red-orange hues
    // This is a conceptual representation and needs fine-tuning
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    // Hue range for sunsets is typically in the lower end
    float h_ranges[] = { 0, 180 };
    // Saturation might be high for sunsets
    float s_ranges[] = { 0, 256 };

    const float* ranges[] = { h_ranges, s_ranges };
    int channels[] = { 0, 1 }; // Using both hue and saturation

    MatND hist;
    calcHist(&hsvImage, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);

    // Normalize the result to [0, 1]
    normalize(hist, hist, 0, 1, NORM_MINMAX, -1, Mat());

    // Flatten the histogram to a vector
    vector<float> histogram;
    hist.reshape(1, 1).convertTo(histogram, CV_32F);
    return normalizeVector(histogram);
}

/**
* @brief Extract edge features for horizon detection from an image.
* 
* @param image The input image.
* @return The normalized edge features vector.
*/
vector<float> extractEdgeFeatures(const Mat& image) {
    Mat gray, edges;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 50, 150, 3); // Parameters need tuning

    // Convert edges to a simple histogram by counting edge pixels in horizontal bins
    vector<float> edgeHistogram(1, 0); // Simplified for demonstration
    for (int i = 0; i < edges.rows; i++) {
        for (int j = 0; j < edges.cols; j++) {
            if (edges.at<uchar>(i, j) > 0) {
                edgeHistogram[0]++; 
            }
        }
    }

    return normalizeVector(edgeHistogram);
}

/**
* @brief Calculate Local Binary Patterns (LBP) features from an image.
* 
* @param image The input image.
* @return The normalized LBP features vector.
*/
void lbpCalculate(const Mat& src, Mat& dst) {
    dst = Mat::zeros(src.size(), CV_8UC1);
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            uchar center = src.at<uchar>(y, x);
            unsigned char code = 0;
            code |= (src.at<uchar>(y - 1, x - 1) > center) << 7;
            code |= (src.at<uchar>(y - 1, x) > center) << 6;
            code |= (src.at<uchar>(y - 1, x + 1) > center) << 5;
            code |= (src.at<uchar>(y, x + 1) > center) << 4;
            code |= (src.at<uchar>(y + 1, x + 1) > center) << 3;
            code |= (src.at<uchar>(y + 1, x) > center) << 2;
            code |= (src.at<uchar>(y + 1, x - 1) > center) << 1;
            code |= (src.at<uchar>(y, x - 1) > center) << 0;
            dst.at<uchar>(y - 1, x - 1) = code;
        }
    }
}

/**
* @brief Extract DNN features from an image using a pre-trained model.
* 
* @param image The input image.
* @param modelPath The path to the DNN model file.
* @param configPath The path to the configuration file.
* @param inputSize The input size expected by the model.
* @param meanVal The mean values used for input normalization.
* @param swapRB Whether to swap red and blue channels.
* @return The normalized DNN features vector.
*/
vector<float> extractLBPFeatures(const Mat& image) {
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat lbpImage;
    lbpCalculate(grayImage, lbpImage);

    int histSize[] = { 256 }; // LBP can encode values from 0 to 255
    float ranges[] = { 0, 256 };
    const float* histRanges = { ranges };
    Mat hist;
    calcHist(&lbpImage, 1, 0, Mat(), hist, 1, histSize, &histRanges, true, false);

    vector<float> histogram;
    hist.convertTo(histogram, CV_32F);
    return histogram;
}

/**
* @brief Calculate the distance between two feature vectors, considering different feature weights.
* 
* @param features1 The first feature vector.
* @param features2 The second feature vector.
* @return The distance between the two feature vectors.
*/
vector<float> extractDNNFeatures(const Mat& image, const string& modelPath, const string& configPath, const Size& inputSize, const Scalar& meanVal, bool swapRB) {
    Net net = readNet(modelPath, configPath);
    Mat blob;
    blobFromImage(image, blob, 1.0, inputSize, meanVal, swapRB, false);
    net.setInput(blob);
    Mat dnnOutput = net.forward();

    // Convert dnnOutput to a flat vector
    vector<float> features(dnnOutput.size[1]);
    memcpy(features.data(), dnnOutput.data, dnnOutput.total() * sizeof(float));
    return features;
}

/**
* @brief Calculate the distance between two feature vectors, considering different feature weights.
* 
* @param features1 The first feature vector.
* @param features2 The second feature vector.
* @return The distance between the two feature vectors.
*/
float calculateDistance(const FeatureVector& features1, const FeatureVector& features2) {
    // Adjust weights for sunset-specific features
    float w1 = 0.4; // Increased weight for sunset colors
    float w2 = 0.1; // Decreased weight for texture
    float w3 = 0.2; // DNN features
    float w4 = 0.3; // Increased weight for edge features (horizon detection)

    float colorDistance = euclideanDistance(features1.sunsetColorHistogram, features2.sunsetColorHistogram);
    float textureDistance = euclideanDistance(features1.textureFeatures, features2.textureFeatures);
    float dnnDistance = 1 - cosineSimilarity(features1.dnnFeatures, features2.dnnFeatures);
    float edgeDistance = euclideanDistance(features1.edgeFeatures, features2.edgeFeatures);

    float totalDistance = w1 * colorDistance + w2 * textureDistance + w3 * dnnDistance + w4 * edgeDistance;
    return totalDistance;
}

/**
* @brief Save feature vectors to a CSV file.
* 
* @param csvFilePath The path to the CSV file.
* @param featureVectors The feature vectors to be saved.
* @param imagePaths The corresponding image paths.
*/
void saveFeatureVectorsToCSV(const std::string& csvFilePath, const std::vector<std::vector<float>>& featureVectors, const std::vector<std::string>& imagePaths) {
    std::ofstream file(csvFilePath, std::ofstream::out | std::ofstream::app); // Open in append mode

    for (size_t i = 0; i < featureVectors.size(); ++i) {
        file << imagePaths[i]; 
        for (const auto& feature : featureVectors[i]) {
            file << "," << feature; 
        }
        file << "\n"; // 
    }

    file.close();
}

/**
* @brief Get the directory of the current executable.
* 
* @return The directory path.
*/
std::string GetCurrentExecutableDirectory() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    PathRemoveFileSpecA(path);
    return std::string(path);
}

/**
* @brief Extract custom design feature vector from an image.
* 
* @param image The input image.
* @return The custom design feature vector.
*/
std::vector<float> extractCustomDesignFeatureVector(const cv::Mat& image) {
    std::string baseDir = GetCurrentExecutableDirectory();

    std::string modelPath = baseDir + "\\models\\DenseNet_121.prototxt";
    std::string configPath = baseDir + "\\models\\DenseNet_121.caffemodel";

    // This function combines all custom design features into a single vector for an image
    vector<float> sunsetColorHistogram = normalizeVector(extractSunsetColorHistogram(image));
    vector<float> textureFeatures = normalizeVector(extractLBPFeatures(image));
    vector<float> dnnFeatures = normalizeVector(extractDNNFeatures(image, modelPath, configPath, Size(224, 224), Scalar(104, 117, 123), true));
    vector<float> edgeFeatures = normalizeVector(extractEdgeFeatures(image));

    // Combine all features into a single vector
    vector<float> combinedFeatures;
    combinedFeatures.insert(combinedFeatures.end(), sunsetColorHistogram.begin(), sunsetColorHistogram.end());
    combinedFeatures.insert(combinedFeatures.end(), textureFeatures.begin(), textureFeatures.end());
    combinedFeatures.insert(combinedFeatures.end(), dnnFeatures.begin(), dnnFeatures.end());
    combinedFeatures.insert(combinedFeatures.end(), edgeFeatures.begin(), edgeFeatures.end());

    return combinedFeatures;
}

/**
* @brief Perform custom design calculation and save feature vectors to a CSV file.
* 
* @param directory The directory containing images.
* @param outputFile The path to the output CSV file.
*/
void performCustomDesignCalculation(const std::string& directory, const std::string& outputFile)
{
    std::vector<std::vector<float>> featureVectors;
    std::vector<std::string> imagePaths;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".jpg") {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (!image.empty()) {
                std::vector<float> featureVector = extractCustomDesignFeatureVector(image);

                featureVectors.push_back(featureVector);
                imagePaths.push_back(imagePath);
            }
        }
    }

    // Save extracted feature vectors to a CSV file
    saveFeatureVectorsToCSV(outputFile, featureVectors, imagePaths);
}

/**
* @brief Split a string by a delimiter.
* 
* @param s The input string to be split.
* @param delimiter The delimiter character.
* @return A vector containing the split substrings.
*/
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
* @brief Read feature vectors from a CSV file.
* 
* @param csvFilePath The path to the CSV file.
* @return A vector of pairs containing image paths and corresponding feature vectors.
*/
std::vector<std::pair<std::string, std::vector<float>>> readFeatureVectorsFromCSV(const std::string& csvFilePath) {
    std::vector<std::pair<std::string, std::vector<float>>> featureVectors;
    std::ifstream file(csvFilePath);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() > 1) {
            std::string imagePath = tokens[0];
            std::vector<float> features(tokens.size() - 1, 0.0f);
            for (size_t i = 1; i < tokens.size(); ++i) {
                features[i - 1] = std::stof(tokens[i]);
            }
            featureVectors.push_back({ imagePath, features });
        }
    }

    return featureVectors;
}

/**
* @brief Perform custom design CBIR (Content-Based Image Retrieval) using a target image.
* 
* @param targetImageFile The path to the target image.
* @param featureVectorCSVPath The path to the CSV file containing feature vectors.
* @param topN The number of top matches to retrieve.
* @return A vector containing the paths of the top N matching images.
*/
std::vector<std::string> performCustomDesignCbir(const std::string& targetImageFile, const std::string& featureVectorCSVPath, int topN) {
    // Extract the feature vector for the target image
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);
    if (targetImage.empty()) {
        std::cerr << "Error: Target image could not be read." << std::endl;
        return {};
    }

    std::vector<float> queryFeatures = extractCustomDesignFeatureVector(targetImage);

    // Read the feature vectors from the CSV file
    auto featureVectors = readFeatureVectorsFromCSV(featureVectorCSVPath);
    std::vector<std::pair<float, std::string>> imageDistances;

    // Calculate distances between the query image features and each feature vector in the CSV
    for (const auto& [imagePath, features] : featureVectors) {
        // Skip comparison if the current image is the target image
        if (std::filesystem::path(imagePath).filename() == std::filesystem::path(targetImageFile).filename()) {
            continue; // Skip this image
        }
        float distance = euclideanDistance(queryFeatures, features);
        imageDistances.push_back(std::make_pair(distance, imagePath));
    }

    // Sort based on distances
    std::sort(imageDistances.begin(), imageDistances.end(), [](const std::pair<float, std::string>& a, const std::pair<float, std::string>& b) {
        return a.first < b.first; // Ascending order
        });

    // Extract top N matches
    std::vector<std::string> topMatches;
    int loopLimit = std::min(topN, static_cast<int>(imageDistances.size()));
    for (int i = 0; i < loopLimit; ++i) {
        topMatches.push_back(imageDistances[i].second);
    }

    return topMatches;
}

