/*! \file CBIR.cpp
    \brief GUI for Content-Based Image Retrieval (CBIR) System.
    \author Manushi
    \date February 10, 2024

    This file is part of a Content-Based Image Retrieval (CBIR) system implementing GUI.
*/
#include "CBIR.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

/**
 * @brief Entry point for the application.
 *
 * This function sets up and runs the graphical user interface (GUI) for the CBIR system.
 *
 * @param args Command-line arguments passed to the application.
 */
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew GUIProject2::CBIR);
}
