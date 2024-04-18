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
#define NOMINMAX
#include <windows.h>
#include <Shlwapi.h> 
#pragma comment(lib, "Shlwapi.lib")
#include <string>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;
using namespace cv::dnn;

struct FeatureVector {
    vector<float> colorHistogram;
    vector<float> textureFeatures;
    vector<float> dnnFeatures;
    vector<float> faceFeatures;
};

/**
 * @brief Retrieves the directory path of the current executable.
 *
 * @return std::string The directory path of the current executable.
 */
std::string GetCurrentExecutableDirectoryFace() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    PathRemoveFileSpecA(path);
    return std::string(path);
}

/**
 * @brief Normalizes a given vector by dividing each element by its Euclidean norm.
 *
 * @param v The vector to normalize.
 * @return std::vector<float> The normalized vector.
 */
vector<float> normalizeVectorFace(const vector<float>& v) {
    vector<float> nv(v.size());
    float norm = sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0f));
    if (norm > 0) {
        std::transform(v.begin(), v.end(), nv.begin(), [norm](float val) { return val / norm; });
    }
    return nv;
}


/**
 * @brief Calculates the Euclidean distance between two feature vectors.
 *
 * @param featureVec1 The first feature vector.
 * @param featureVec2 The second feature vector.
 * @return float The Euclidean distance between the two feature vectors.
 */
float euclideanDistanceFace(const std::vector<float>& featureVec1, const std::vector<float>& featureVec2) {
    assert(featureVec1.size() == featureVec2.size());
    float distance = 0.0f;
    for (size_t i = 0; i < featureVec1.size(); ++i) {
        distance += std::pow(featureVec1[i] - featureVec2[i], 2);
    }
    return std::sqrt(distance);
}

/**
 * @brief Extracts the color histogram features from an input image.
 *
 * @param image The input image.
 * @param binsPerChannel The number of bins per color channel.
 * @return std::vector<float> The color histogram features.
 */
vector<float> extractColorHistogramFace(const Mat& image, int binsPerChannel = 8) {
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // Convert the 3D histogram cv::Mat to a flat std::vector<float>
    cv::Mat hist3D = compute3DColorHistogramManual(hsvImage, binsPerChannel);
    vector<float> histogram;
    if (!hist3D.empty()) {
        hist3D.reshape(0, 1).convertTo(histogram, CV_32F); // Reshape to a single row and convert to std::vector
    }
    else {
        std::cerr << "Histogram calculation failed or returned empty histogram." << std::endl;
    }
    return histogram;
}

/**
 * @brief Calculates Local Binary Patterns (LBP) for an input image.
 *
 * @param src The source image.
 * @param dst The destination image where LBP will be stored.
 */
void lbpCalculateFace(const Mat& src, Mat& dst) {
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
 * @brief Extracts Local Binary Pattern (LBP) features from an input image.
 *
 * @param image The input image.
 * @return std::vector<float> The LBP features.
 */
vector<float> extractLBPFeaturesFace(const Mat& image) {
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat lbpImage;
    lbpCalculateFace(grayImage, lbpImage);

    // Assume lbp_calculate returns a Mat with the same dimensions as the input image,
    // where each pixel contains its LBP value. Now, compute the histogram.
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
 * @brief Extracts features using a pre-trained Deep Neural Network (DNN) model.
 *
 * @param image The input image.
 * @param modelPath The file path to the DNN model.
 * @param configPath The file path to the configuration file for the DNN model.
 * @param inputSize The input size expected by the DNN model.
 * @param meanVal The mean value to subtract from the input image.
 * @param swapRB Whether to swap the R and B channels.
 * @return std::vector<float> The extracted DNN features.
 */
vector<float> extractDNNFeaturesFace(const Mat& image, const string& modelPath, const string& configPath, const Size& inputSize, const Scalar& meanVal, bool swapRB) {
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
 * @brief Calculates the combined distance between two sets of feature vectors.
 *
 * @param features1 The first set of feature vectors.
 * @param features2 The second set of feature vectors.
 * @return float The combined distance between the two sets of feature vectors.
 */
float calculateDistanceFace(const FeatureVector& features1, const FeatureVector& features2) {
    // Example weights
    float w1 = 0.33, w2 = 0.33, w3 = 0.34;

    float colorDistance = euclideanDistanceFace(features1.colorHistogram, features2.colorHistogram);
    float textureDistance = euclideanDistanceFace(features1.textureFeatures, features2.textureFeatures);
    float dnnDistance = 1 - cosineSimilarity(features1.dnnFeatures, features2.dnnFeatures);

    float totalDistance = w1 * colorDistance + w2 * textureDistance + w3 * dnnDistance;
    return totalDistance;
}

/**
 * @brief Extracts face embeddings from a given face region of interest (ROI) using a face recognition model.
 *
 * @param faceROI The face region of interest.
 * @param faceRecognitionModel The pre-trained face recognition model.
 * @return std::vector<float> The face embeddings.
 */
vector<float> getFaceEmbeddings(const Mat& faceROI, Net& faceRecognitionModel) {
    // Preprocess the face ROI as required by the OpenFace model
    Mat preprocessedFace = blobFromImage(faceROI, 1.0 / 255, Size(96, 96), Scalar(0, 0, 0), true, false);

    // Set the input blob for the neural network
    faceRecognitionModel.setInput(preprocessedFace);

    // Forward pass to compute the output
    Mat embeddings = faceRecognitionModel.forward();

    // Flatten the result to convert to std::vector<float>
    return embeddings.reshape(1, 1).isContinuous() ? embeddings.reshape(1, 1) : embeddings.clone().reshape(1, 1);
}

/**
 * @brief Extracts various features from faces detected in the input image.
 *
 * @param image The input image.
 * @param faceNet The face detection model.
 * @param faceRecognitionModel The face recognition model.
 * @return std::vector<float> The extracted face features.
 */
vector<float> extractFaceFeatures(const Mat& image, Net& faceNet, Net& faceRecognitionModel) {
    vector<float> faceFeatures;
    Mat inputBlob = blobFromImage(image, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0), false, false);
    faceNet.setInput(inputBlob);
    Mat detections = faceNet.forward();

    Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    for (int i = 0; i < detectionMat.rows; i++) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > 0.3) { // Only consider detections with high confidence
            // Calculate the (x, y)-coordinates of the bounding box for the object
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows);
            Rect faceRect(x1, y1, x2 - x1, y2 - y1);

            // Ensure the bounding box fits within the frame
            faceRect = faceRect & Rect(0, 0, image.cols, image.rows);
           
            // Extract the face ROI and possibly resize it for your face feature extractor input
            Mat faceROI = image(faceRect).clone();
            resize(faceROI, faceROI, Size(96, 96)); // Example resize if needed

            // Here you would pass the faceROI to your face feature extractor
            // For example, let's say we have a function called 'getFaceEmbeddings' that returns a vector of floats
            vector<float> faceEmbeddings = getFaceEmbeddings(faceROI, faceRecognitionModel);

            // Then add these face features to the faceFeatures vector
            faceFeatures.insert(faceFeatures.end(), faceEmbeddings.begin(), faceEmbeddings.end());
        }
    }
    return faceFeatures;
}


/**
 * @brief Highlights faces detected in the input image.
 *
 * @param image The input image.
 * @param faceNet The face detection model.
 */
void highlightFaces(Mat& image, Net& faceNet) {
    Mat inputBlob = blobFromImage(image, 1.0, Size(300, 300), Scalar(104.0, 177.0, 123.0), false, false);
    faceNet.setInput(inputBlob);
    Mat detections = faceNet.forward();
    Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

    for (int i = 0; i < detectionMat.rows; ++i) {
        float confidence = detectionMat.at<float>(i, 2);
        if (confidence > 0.5) {
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.cols);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.rows);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.cols);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.rows);
            rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2, 4);
        }
    }
}
/**
* @brief Save feature vectors to a CSV file.
*
* @param csvFilePath The path to the CSV file.
* @param featureVectors The feature vectors to be saved.
* @param imagePaths The corresponding image paths.
*/
void saveFeatureVectorsFaceToCSV(const std::string& csvFilePath, const std::vector<std::vector<float>>& featureVectors, const std::vector<std::string>& imagePaths) {
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
* @brief Calculate the custom design feature vector with face detection for an image and return it.
*
* @param image The input image.
* @return The custom design feature vector with face detection.
*/
std::vector<float> extractCustomDesignFaceFeatureVector(const cv::Mat& image) {
    std::string baseDir = GetCurrentExecutableDirectoryFace();

    std::string modelPath = baseDir + "\\models\\DenseNet_121.prototxt";
    std::string configPath = baseDir + "\\models\\DenseNet_121.caffemodel";

    std::string faceDetectorModelPath = baseDir + "\\models\\deploy.prototxt";
    std::string faceDetectorConfigPath = baseDir + "\\models\\res10_300x300_ssd_iter_140000_fp16.caffemodel";

    std::string faceRecognitionModelPath = baseDir + "\\models\\openface.nn4.small2.v1.t7";

    vector<float> colorHist = normalizeVectorFace(extractColorHistogramFace(image));
    vector<float> textureFeatures = normalizeVectorFace(extractLBPFeaturesFace(image));
    vector<float> dnnFeatures = normalizeVectorFace(extractDNNFeaturesFace(image, modelPath, configPath, Size(224, 224), Scalar(104, 117, 123), true));


    // Load face detection model
    Net faceNet = readNet(faceDetectorModelPath, faceDetectorConfigPath);

    // Load the face recognition model
    Net faceRecognitionModel = readNetFromTorch(faceRecognitionModelPath);

    // Extract face features
    vector<float> faceFeatures = extractFaceFeatures(image, faceNet, faceRecognitionModel);

    // Combine all features into a single feature vector
    vector<float> combinedFeatures;
    combinedFeatures.insert(combinedFeatures.end(), colorHist.begin(), colorHist.end());
    combinedFeatures.insert(combinedFeatures.end(), textureFeatures.begin(), textureFeatures.end());
    combinedFeatures.insert(combinedFeatures.end(), dnnFeatures.begin(), dnnFeatures.end());
    combinedFeatures.insert(combinedFeatures.end(), faceFeatures.begin(), faceFeatures.end());

    return combinedFeatures;
}

/**
* @brief Split a string by a delimiter.
*
* @param s The input string to be split.
* @param delimiter The delimiter character.
* @return A vector containing the split substrings.
*/
std::vector<std::string> splitFace(const std::string& s, char delimiter) {
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
std::vector<std::pair<std::string, std::vector<float>>> readFeatureVectorsFaceFromCSV(const std::string& csvFilePath) {
    std::vector<std::pair<std::string, std::vector<float>>> featureVectors;
    std::ifstream file(csvFilePath);
    std::string line;

    while (std::getline(file, line)) {
        auto tokens = splitFace(line, ',');
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
 * @brief Performs content-based image retrieval (CBIR) with custom-designed features and face detection.
 *
 * @param directoryPath The directory path containing the database of images.
 * @param targetImageFile The file path of the target image.
 * @param topN The number of top similar images to return.
 * @return std::vector<std::pair<cv::Mat, std::string>> A vector of pairs, each containing a processed image and its file path.
 */
std::vector<std::pair<cv::Mat, std::string>> performCustomDesignFaceCbir(const std::string& featureVectorCSVPath, const std::string& targetImageFile, int topN) {
    // Load the target image
    cv::Mat targetImage = cv::imread(targetImageFile, cv::IMREAD_COLOR);
    if (targetImage.empty()) {
        std::cerr << "Error loading target image." << std::endl;
        return {};
    }

    std::string baseDir = GetCurrentExecutableDirectoryFace();

    std::string faceDetectorModelPath = baseDir + "\\models\\deploy.prototxt";
    std::string faceDetectorConfigPath = baseDir + "\\models\\res10_300x300_ssd_iter_140000_fp16.caffemodel";

    // Load face detection model
    Net faceNet = readNet(faceDetectorModelPath, faceDetectorConfigPath);

    // Extract the feature vector for the target image
    std::vector<float> targetFeatureVector = extractCustomDesignFaceFeatureVector(targetImage);

    // Read the precomputed feature vectors from the CSV file
    auto featureVectors = readFeatureVectorsFaceFromCSV(featureVectorCSVPath);

    // Compute distances between the target image and each image in the dataset
    std::vector<std::pair<float, std::string>> distances;
    for (const auto& [imagePath, features] : featureVectors) {
        // Skip comparison if the current image is the target image
        if (std::filesystem::path(imagePath).filename() == std::filesystem::path(targetImageFile).filename()) {
            continue; // Skip this image
        }

        float distance = euclideanDistanceFace(targetFeatureVector, features);
        distances.push_back({ distance, imagePath });
    }

    // Sort images by ascending distance
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
        });

    // Highlight faces and collect top N matches
    std::vector<std::pair<cv::Mat, std::string>> topMatches;
    for (int i = 0; i < std::min(topN, static_cast<int>(distances.size())); ++i) {
        cv::Mat image = cv::imread(distances[i].second, cv::IMREAD_COLOR);
        highlightFaces(image, faceNet); 
        topMatches.push_back({ image, distances[i].second });
    }

    return topMatches;
}





/**
* @brief Perform custom design with FAce detection calculation and save feature vectors to a CSV file.
*
* @param directory The directory containing images.
* @param outputFile The path to the output CSV file.
*/
void performCustomDesignCalculationFace(const std::string& directory, const std::string& outputFile)
{
    std::vector<std::vector<float>> featureVectors;
    std::vector<std::string> imagePaths;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".jpg") {
            std::string imagePath = entry.path().string();
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
            if (!image.empty()) {
                std::vector<float> featureVector = extractCustomDesignFaceFeatureVector(image);

                featureVectors.push_back(featureVector);
                imagePaths.push_back(imagePath);
            }
        }
    }

    // Save extracted feature vectors to a CSV file
    saveFeatureVectorsFaceToCSV(outputFile, featureVectors, imagePaths);
}






