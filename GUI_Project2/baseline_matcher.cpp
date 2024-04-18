/*! \file baseline_matcher.cpp
    \brief Baseline Matching for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file is part of a Content-Based Image Retrieval (CBIR) system, focusing specifically on the baseline matching approach.
    It includes functions for extracting a 7x7 feature vector from the center of images, computing distances between these feature vectors
    using the sum of squared differences, and identifying the most similar images in a database based on these distances.
    The functionality provided herein is crucial for the initial stage of building a CBIR system, offering a foundation for more
    advanced image retrieval tasks. It caters to the need for efficient and effective retrieval of images by visual content.
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "csv_util.h"  
#include "feature_utils.h"

/**
 * @brief Extracts a 7x7 feature vector from the center of an image, encapsulating the color information of each pixel within this square.
 * This method assumes the image is in color and uses the BGR color space provided by OpenCV.
 *
 * @param image The cv::Mat object containing the loaded image from which the feature vector will be extracted.
 * @return std::vector<float> A 147-element vector (7x7 pixels * 3 color channels) containing the color values of the extracted square.
 * @throws std::runtime_error if the input image is too small to extract a 7x7 feature vector.
 */

std::vector<float> extract7x7FeatureVector(const cv::Mat& image) {
    // Check if the image is too small to extract a 7x7 square
    if (image.cols < 7 || image.rows < 7) {
        throw std::runtime_error("Image is too small to extract a 7x7 feature vector.");
    }

    // Calculate the start point for the 7x7 square
    int start_i = (image.rows / 2) - 3;
    int start_j = (image.cols / 2) - 3;

    std::vector<float> featureVector;
    featureVector.reserve(49); // 7x7 = 49

    // Extract the 7x7 square and flatten it into a vector
    for (int i = start_i; i < start_i + 7; ++i) {
        for (int j = start_j; j < start_j + 7; ++j) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j); 
            featureVector.push_back(pixel[0]); // Blue channel
            featureVector.push_back(pixel[1]); // Green channel
            featureVector.push_back(pixel[2]); // Red channel
        }
    }
    return featureVector;
}

/**
 * @brief Computes the sum of squared differences between two feature vectors, serving as a distance metric.
 * This function is essential for evaluating the similarity between images based on their feature vectors.
 *
 * @param vec1 The first feature vector as a std::vector<float>.
 * @param vec2 The second feature vector as a std::vector<float>.
 * @return float The computed sum of squared differences between the two vectors.
 * @throws std::invalid_argument if the vectors are not of the same size.
 */

float computeDistance(const std::vector<float>& vec1, const std::vector<float>& vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Vectors must be of the same size to compute distance.");
    }

    float sum = 0.0f;
    for (size_t i = 0; i < vec1.size(); ++i) {
        float diff = vec1[i] - vec2[i];
        sum += diff * diff;
    }
    return sum;
}

/**
 * @brief Matches a target image against a database of images based on the sum of squared difference metric,
 * returning the top N most similar images. It loads the target image, computes its feature vector, reads
 * pre-computed feature vectors from a CSV file, and computes distances to find the best matches.
 *
 * @param targetImageFile A string representing the file path of the target image.
 * @param topN An integer specifying the number of top similar images to return.
 * @param featureFile A string representing the file path to the CSV file containing pre-computed feature vectors of the database images.
 * @return std::vector<std::string> A list of filenames for the top N matching images.
 * @note If the target image cannot be loaded or the CSV file cannot be read, the function will print an error message.
 */

std::vector<std::string> performBaselineMatching(const std::string& targetImageFile, int topN, const std::string& featureFile) {
    // Load the target image
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);
    if (targetImage.empty()) {
        std::cerr << "Could not read the image: " << targetImageFile << std::endl;
    }

    // Extract the feature vector from the target image
    std::vector<float> targetFeatures = extract7x7FeatureVector(targetImage);

    // Read the feature vectors and filenames from the CSV file
    std::vector<char*> filenames;
    std::vector<std::vector<float>> databaseFeatures;
    if (read_image_data_csv(const_cast<char*>(featureFile.c_str()), filenames, databaseFeatures, false) != 0) {
        std::cerr << "Error reading feature data from CSV file." << std::endl;
    }

    // Compute distances from the target features to each image's features in the database
    std::vector<std::pair<float, std::string>> distances;
    for (size_t i = 0; i < databaseFeatures.size(); ++i) {
        float dist = computeDistance(targetFeatures, databaseFeatures[i]);

        if (dist > 0) { // To skip distances with a value of 0
            distances.push_back(std::make_pair(dist, std::string(filenames[i])));
        }
    }

    // Sort the distances in ascending order to get the closest matches first
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
        });

    std::vector<std::string> topMatches;
    for (int i = 0; i < std::min(topN, static_cast<int>(distances.size())); ++i) {
        topMatches.push_back(distances[i].second);
    }

    return topMatches;

}

/**
 * @brief Processes a directory of images, extracting a 7x7 feature vector from each image and saving these vectors to a CSV file.
 * This function facilitates the offline computation of feature vectors for all images in a database, optimizing the matching process.
 *
 * @param directory A string representing the path to the directory containing the images to be processed.
 * @param outputFile A string representing the file path where the extracted feature vectors should be saved in CSV format.
 * @note This function will overwrite the existing CSV file if reset_file is set to true; otherwise, it appends to it.
 * @note The function prints an error message if an image cannot be loaded or if writing to the CSV file fails.
 */

void performBaselineCalculation(const std::string& directory, const std::string& outputFile)
{
    bool reset_file = true; // Set this to true to overwrite the existing CSV file, or false to append.

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {

        // Check if the file is a .jpg image before processing
        if (entry.path().extension() == ".jpg") {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (image.empty()) {
                std::cerr << "Error loading image: " << imagePath << std::endl;
                continue;
            }

            // Extract the 7x7 feature vector from the image
            std::vector<float> featureVector = extract7x7FeatureVector(image);

            // Append the feature vector to the CSV file
            char* imagePathCStr = new char[imagePath.length() + 1];
            std::strcpy(imagePathCStr, imagePath.c_str());
            int status = append_image_data_csv(const_cast<char*>(outputFile.c_str()), imagePathCStr, featureVector, reset_file);
            delete[] imagePathCStr; // Clean up the allocated memory

            // Only reset the file once, at the beginning
            reset_file = false;

            if (status != 0) {
                std::cerr << "Error writing to CSV file." << std::endl;
            }
        }
    }
}