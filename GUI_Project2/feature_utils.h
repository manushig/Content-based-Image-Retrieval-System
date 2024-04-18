/*! \file feature_utils.h
    \brief Declarations of functions for various image feature computations and matching tasks.
    \author Manushi
    \date February 10, 2024

    This file encapsulates a variety of functions for computing image features, performing matching tasks, 
    and supporting Content-Based Image Retrieval (CBIR) system.
*/

#ifndef FEATURE_UTILS_H
#define FEATURE_UTILS_H

#include <opencv2/opencv.hpp>
#include <vector>

/**
 * @brief Computes a 3D color histogram manually from an input image.
 *
 * @param image The input image for which to compute the histogram.
 * @param binsPerChannel The number of bins per color channel.
 * @return A 3D color histogram represented as a cv::Mat.
 */
cv::Mat compute3DColorHistogramManual(const cv::Mat& image, int binsPerChannel);

/**
 * @brief Performs deep network embeddings matching to find similar images.
 *
 * @param targetImageFile The path to the target image file.
 * @param topN The number of top matching images to retrieve.
 * @param featureFile The path to the CSV file containing feature vectors.
 * @return A vector of paths to the top matching images.
 */
std::vector<std::string> performdeepNetworkEmbeddingsMatching(const std::string& targetImageFile, int topN, const std::string& featureFile);

/**
 * @brief Performs histogram matching to find similar images.
 *
 * @param targetImageFile The path to the target image file.
 * @param topN The number of top matching images to retrieve.
 * @param binsPerChannel The number of bins per color channel for histogram computation.
 * @param csvFilePath The path to the CSV file containing feature vectors.
 * @return A vector of paths to the top matching images.
 */
std::vector<std::string> performHistogramMatching(const std::string& targetImageFile, int topN, int binsPerChannel, const std::string& csvFilePath);

/**
 * @brief Calculates histograms for images in a directory and stores them in a CSV file.
 *
 * @param directoryPath The path to the directory containing images.
 * @param binsPerChannel The number of bins per color channel for histogram computation.
 * @param outputFile The path to the output CSV file.
 */
void performHistogramCalculation(const std::string& directoryPath, int binsPerChannel, const std::string& outputFile);

/**
 * @brief Performs multi-histogram matching between a target image and a database of images.
 *
 * @param targetImageFile Path to the target image file.
 * @param topN Number of top matching images to return.
 * @param binsPerChannel Number of bins per color channel in the histograms.
 * @param outputFile Path to the CSV file containing database histogram data.
 * @return std::vector<std::string> Vector of filenames of the top N matching images.
 */
std::vector<std::string> performMultiHistogramMatchingTask(const std::string& targetImageFile, int topN, int binsPerChannel, const std::string& outputFile);

/**
 * @brief Performs the preprocessing step for the multi-histogram image database.
 *
 * @param directoryPath Path to the directory containing images.
 * @param binsPerChannel Number of bins per color channel in the histograms.
 * @param outputFile Path to the output CSV file to save histogram data.
 */
void performMultiHistogramCalculationTask(const std::string& directoryPath, int binsPerChannel, const std::string& outputFile);

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
std::vector<std::string>  performTextureAndColorMatchingTask(const std::string& targetImageFile, int TopN, int colorBinsPerChannel, int textureBins, const std::string& outputFile);

/**
 * @brief Perform texture and color calculation task for a directory of images.
 *
 * @param directoryPath The path to the directory containing images.
 * @param colorBinsPerChannel The number of bins per channel for the color histogram.
 * @param textureBins The number of bins for the texture histogram.
 * @param outputPath The path to save the combined histograms CSV file.
 */
void performTextureAndColorCalculationTask(const std::string& directoryPath, int colorBinsPerChannel, int textureBins, const std::string& outputPath);

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
std::vector<std::string> performBaselineMatching(const std::string& targetImageFile, int topN, const std::string& featureFile);

/**
 * @brief Processes a directory of images, extracting a 7x7 feature vector from each image and saving these vectors to a CSV file.
 * This function facilitates the offline computation of feature vectors for all images in a database, optimizing the matching process.
 *
 * @param directory A string representing the path to the directory containing the images to be processed.
 * @param outputFile A string representing the file path where the extracted feature vectors should be saved in CSV format.
 * @note This function will overwrite the existing CSV file if reset_file is set to true; otherwise, it appends to it.
 * @note The function prints an error message if an image cannot be loaded or if writing to the CSV file fails.
 */
void performBaselineCalculation(const std::string& directory, const std::string& outputFile);

/**
 * @brief Performs content-based image retrieval (CBIR) with custom-designed features and face detection.
 *
 * @param directoryPath The directory path containing the database of images.
 * @param targetImageFile The file path of the target image.
 * @param topN The number of top similar images to return.
 * @return std::vector<std::pair<cv::Mat, std::string>> A vector of pairs, each containing a processed image and its file path.
 */

std::vector<std::pair<cv::Mat, std::string>> performCustomDesignFaceCbir(const std::string& featureVectorCSVPath, const std::string& targetImageFile, int topN);
/**
* @brief Perform custom design CBIR (Content-Based Image Retrieval) using a target image.
*
* @param targetImageFile The path to the target image.
* @param featureVectorCSVPath The path to the CSV file containing feature vectors.
* @param topN The number of top matches to retrieve.
* @return A vector containing the paths of the top N matching images.
*/
std::vector<std::string> performCustomDesignCbir(const std::string& targetImageFile, const std::string& featureVectorCSVPath, int topN);

/**
* @brief Perform custom design calculation and save feature vectors to a CSV file.
*
* @param directory The directory containing images.
* @param outputFile The path to the output CSV file.
*/
void performCustomDesignCalculation(const std::string& directory, const std::string& outputFile);

void performCustomDesignCalculationFace(const std::string& directory, const std::string& outputFile);

/**
 * @brief Calculates the cosine similarity between two vectors.
 *
 * @param vecA The first input vector.
 * @param vecB The second input vector.
 * @return The cosine similarity between the two input vectors.
 */
float cosineSimilarity(const std::vector<float>& vecA, const std::vector<float>& vecB);

/**
 * @brief Computes the Euclidean norm (length) of a vector.
 *
 * @param vec The input vector.
 * @return The Euclidean norm of the input vector.
 */
float vectorLength(const std::vector<float>& vec);
#endif // FEATURE_UTILS_H
