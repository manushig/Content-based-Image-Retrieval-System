/*! \file imgDisplay.cpp
    \brief Display an image from a file.
    \author Manushi
    \date January 24, 2024

    This program reads an image from a specified file path and displays it in a window.
    The program enters a loop, waiting for the user to press 'q' to quit the program.
    Additional functionality includes applying sepia, Sobel X, Sobel Y, and median filtering
    to the image and displaying them in separate windows.
    The windows are destroyed upon exiting.
*/

#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

/*!
 *  \brief Main function.
 *
 *  \param argc Count of command-line arguments.
 *  \param argv Array of command-line arguments.
 *  \return int Returns 0 on successful execution, -1 on failure.
 *
 *  The main function checks if an image file path is provided as an argument.
 *  It then reads the image, displays it in a window, and applies various filters.
 *  The program waits for the user to press 'q' to exit.
 */

int main() {
    // Read the image file
    Mat image = imread("Original.jpg", IMREAD_COLOR);

    namedWindow("Sepia", WINDOW_AUTOSIZE);
    imshow("Sepia", image);

    waitKey(0);
}
