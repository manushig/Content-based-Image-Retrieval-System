# Content-based Image Retrieval (CBIR) System

## Overview
This project focuses on the development of a Content-based Image Retrieval (CBIR) system. The goal is to learn and implement image manipulation and analysis techniques at the pixel level, using both classic features and deep network embeddings to find images in a database that are similar to a given target image.

## Features
- **Classic Feature Extraction**: Implements extraction of classic image features such as color histograms, texture analysis, and spatial distribution of features.
- **Deep Neural Network Embeddings**: Utilizes embeddings from a pre-trained ResNet18 model to capture high-level semantic information from images.
- **Multiple Distance Metrics**: Supports various distance metrics including sum-of-squares difference, histogram intersection, and cosine similarity for diverse feature comparisons.
- **Flexible Query System**: Allows users to query against a database of images with options to specify feature types and the number of similar images to retrieve.
- **Performance Optimization**: Offers mechanisms to pre-compute features for all database images, enabling quick retrieval during query execution.
- **User Interface**: Provides a command-line interface for ease of use, with plans for a future graphical user interface to enhance user interaction.
- **Extensibility**: Designed to be easily extendable for experimenting with new image features and retrieval algorithms.

## Installation
Ensure you have the following prerequisites installed:
- OpenCV library (version 4.x.x or later)
- CMake (version 3.15 or later)
- A C++ compiler (GCC for Linux, Visual Studio for Windows)

## Instructions for Running the Executables
1. **Prerequisites**: Verify the installation of OpenCV, CMake, and an appropriate C++ compiler.
2. **Building the Project**:
   - Open a terminal or command prompt.
   - Navigate to the project directory.
   - Create a new directory for building the project: `mkdir build && cd build`.
   - Configure the project: `cmake ..`.
   - Build the project: `cmake --build .` (add `--config Release` for Windows).
3. **Running the Executable**:
   - Locate the executable in the `build` directory.
   - Execute the program with necessary arguments:
     - On Linux: `./CBIR`
     - On Windows: `CBIR.exe`
4. **Using the Application**:
   - Follow on-screen prompts for image retrieval.
   - Select the feature extraction method and input the path to your target image.
   - The application displays or outputs paths to the most similar images.

## Acknowledgements
This project was enriched by various resources providing invaluable guidance and insight:
- **Textbooks**: "Computer Vision: Algorithms and Applications, 2nd Edition" by Richard Szeliski provided foundational knowledge.
- **Websites**: OpenCV Documentation and Stack Overflow were crucial for practical implementations and troubleshooting.
- **GitHub Repositories**: Offered a wealth of example codes and project setups.

## Contact
- **Name**: Manushi
