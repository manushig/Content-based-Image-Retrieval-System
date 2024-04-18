/*! \file deep_network_embeddings.cpp
    \brief Deep Network Embeddings for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file contains the implementation of functions for loading deep network embeddings from a CSV file,
    normalizing feature vectors, and performing deep network embeddings matching to find similar images.
*/
#include "feature_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Load embeddings and filenames from a CSV file.
 *
 * @param filePath The path to the CSV file containing embeddings.
 * @return A vector of pairs, where each pair consists of a filename and its corresponding feature vector.
 */
std::vector<std::pair<std::string, std::vector<float>>> loadDeepFeatureVectors(const std::string& filePath) {
    std::vector<std::pair<std::string, std::vector<float>>> embeddings;
    std::ifstream file(filePath);
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string filename;
        std::string value;
        std::vector<float> embedding;

        // Extract filename
        getline(iss, filename, ',');

        // Extract embedding values
        while (getline(iss, value, ',')) {
            embedding.push_back(std::stof(value));
        }
      
        embeddings.push_back({ filename, embedding });
    }

    return embeddings;
}

/**
 * @brief Normalize a vector to unit length.
 *
 * @param vec The vector to be normalized.
 * @return The normalized vector.
 */
std::vector<float> normalizeVectorDne(const std::vector<float>& vec) {
    std::vector<float> normalizedVec(vec.size());
    float len = vectorLength(vec);
    if (len > 0) {
        for (size_t i = 0; i < vec.size(); ++i) {
            normalizedVec[i] = vec[i] / len;
        }
    }
    return normalizedVec;
}

/**
 * @brief Perform deep network embeddings matching to find similar images.
 *
 * @param targetImageFile The path to the target image file.
 * @param topN The number of top matching images to retrieve.
 * @param featureFile The path to the CSV file containing feature vectors.
 * @return A vector of paths to the top matching images.
 */
std::vector<std::string> performdeepNetworkEmbeddingsMatching(const std::string& targetImageFile, int topN, const std::string& featureFile) {
    // Load the target image and compute its histograms manually
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);
    if (targetImage.empty()) {
        std::cerr << "Error loading target image." << std::endl;
    }

    auto embeddings = loadDeepFeatureVectors(featureFile);

    std::string targetFilename = std::filesystem::path(targetImageFile).filename().string();

    // Find the embedding for the target image
    std::vector<float> targetEmbedding;
    bool found = false;
    for (const auto& e : embeddings) {
        if (e.first == targetFilename) {
            targetEmbedding = e.second;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Embedding for the target image not found." << std::endl;
    }

    std::vector<std::pair<float, std::string>> distances;
    std::vector<float> normTargetEmbedding = normalizeVectorDne(targetEmbedding);
    for (const auto& e : embeddings) {
        if (e.first != targetFilename) {
            std::vector<float> normEmbedding = normalizeVectorDne(e.second);
            float similarity = cosineSimilarity(normTargetEmbedding, normEmbedding);
            float distance = 1 - similarity; // Cosine distance
            distances.push_back({ distance, e.first });
        }
    }

    // Sort by distance in ascending order
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
        });


    // Display closest matches
    std::cout << "Closest matches to " << targetFilename << ":\n";
    for (size_t i = 0; i < topN && i < distances.size(); ++i) {
        std::cout << i + 1 << ". " << distances[i].second << " (Distance: " << distances[i].first << ")\n";
    }
   

    fs::path targetImagePath(targetImageFile);
    fs::path dirPath = targetImagePath.parent_path();

    std::vector<std::string> topMatches;
    for (int i = 0; i < std::min(topN, static_cast<int>(distances.size())); ++i) {
        std::string matchFilename = distances[i].second;
        std::string imagePath = (dirPath / matchFilename).string();

        topMatches.push_back(imagePath);
    }

    return topMatches;

}
