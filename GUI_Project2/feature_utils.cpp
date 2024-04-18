/*! \file feature_utils.cpp
    \brief Implements functions for color histogram computation and similarity calculation.
    \author Manushi
    \date February 10, 2024

    This file is part of a Content-Based Image Retrieval (CBIR) system to implement functions for color histogram computation and similarity calculation.
*/

#include "feature_utils.h"

/**
 * @brief Computes a 3D color histogram manually from an input image.
 *
 * @param image The input image for which to compute the histogram.
 * @param binsPerChannel The number of bins per color channel.
 * @return A 3D color histogram represented as a cv::Mat.
 */
cv::Mat compute3DColorHistogramManual(const cv::Mat& image, int binsPerChannel) {
    // Define the range for each bin
    float binWidth = 256.0f / binsPerChannel;

    // Initialize the histogram with zeros
    int totalBins = binsPerChannel * binsPerChannel * binsPerChannel;
    std::vector<float> histogram(totalBins, 0.0f);

    // Iterate over all pixels to fill the histogram
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            // Calculate the bin for each channel
            int binR = static_cast<int>(pixel[2] / binWidth);
            int binG = static_cast<int>(pixel[1] / binWidth);
            int binB = static_cast<int>(pixel[0] / binWidth);

            // Calculate the index in the histogram
            int histIndex = binR * binsPerChannel * binsPerChannel + binG * binsPerChannel + binB;

            // Increment the corresponding histogram bin
            histogram[histIndex]++;
        }
    }

    // Normalize the histogram to turn counts into probabilities
    float totalPixels = static_cast<float>(image.rows * image.cols);
    for (float& value : histogram) {
        value /= totalPixels;
    }

    // Now, reshape the flat histogram into a 3D cv::Mat structure
    int sizes[] = { binsPerChannel, binsPerChannel, binsPerChannel };
    cv::Mat hist(3, sizes, CV_32F, histogram.data());

    // Return a clone to ensure the data is continuous
    return hist.clone();
}

/**
 * @brief Computes the Euclidean norm (length) of a vector.
 *
 * @param vec The input vector.
 * @return The Euclidean norm of the input vector.
 */
float vectorLength(const std::vector<float>& vec) {
    float sum = 0.0;
    for (float elem : vec) {
        sum += elem * elem;
    }
    return std::sqrt(sum);
}

/**
 * @brief Calculates the cosine similarity between two vectors.
 *
 * @param vecA The first input vector.
 * @param vecB The second input vector.
 * @return The cosine similarity between the two input vectors.
 */
float cosineSimilarity(const std::vector<float>& vecA, const std::vector<float>& vecB) {
    float dotProduct = 0.0;
    float normA = vectorLength(vecA);
    float normB = vectorLength(vecB);

    for (size_t i = 0; i < vecA.size(); ++i) {
        dotProduct += vecA[i] * vecB[i];
    }

    // Prevent division by zero
    if (normA == 0 || normB == 0) return -1; 

    return dotProduct / (normA * normB);
}