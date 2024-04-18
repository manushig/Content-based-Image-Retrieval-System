/*! \file CBIR.h
	\brief GUI for Content-Based Image Retrieval (CBIR) System.
	\author Manushi
	\date February 10, 2024

	This file is part of a Content-Based Image Retrieval (CBIR) system implementing GUI.
*/
#pragma once
#include<opencv2/opencv.hpp>
#include "iostream"
#include "feature_utils.h"
#include <msclr/marshal_cppstd.h>

namespace GUIProject2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;
	using namespace System::IO;

	/// <summary>
	/// Constructor for CBIR class
	/// </summary>
	public ref class CBIR : public System::Windows::Forms::Form
	{
	public:
		CBIR(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			topMatches = new std::vector<std::string>();
			topCustomMatches = new std::vector<std::pair<cv::Mat, std::string>>();
			currentIndex = 0;
			
			System::String^ initialDirectory = Path::GetDirectoryName(Path::GetDirectoryName(Application::StartupPath));
			this->folderBrowserDialog1->SelectedPath = initialDirectory;		
		}

	protected:
		/// <summary>
		/// Destructor for the CBIR GUI.
		/// </summary>
		~CBIR()
		{
			if (components)
			{
				delete components;
			}
			if (topMatches != nullptr) {
				delete topMatches;
				topMatches = nullptr;
			}
			if (topCustomMatches != nullptr) {
				delete topCustomMatches;
				topCustomMatches = nullptr;
			}
		}
	private: System::String^ targetImagePath;
	private: System::String^ featureFilePath;
	private: System::String^ imageDirectoryPath;
	private: System::String^ saveFeatureFilePath;
	private: System::Int32 taskNo;
	private: System::Int32 subTaskNo;
	private:
		std::vector<std::string>* topMatches;
		int currentIndex;
	private:
		std::vector<std::pair<cv::Mat, std::string>>* topCustomMatches;
		int currentIndex1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ operationsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ generateFeatureVectorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ baselineMatchingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ histogramMatchingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ multiHistogramMatchingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ textureAndColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ identifyMatchesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ baselineMatchingToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ histogramMatchingToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ multiHistogramMatchingToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ textureAndColorToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ deepNetworkEmbeddingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ customDesignToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Label^ headingLabel;
	private: System::Windows::Forms::Label^ displayImageDirLabel;

	private: System::Windows::Forms::Button^ uploadFeatureFile;
	private: System::Windows::Forms::Label^ displayFeatureFileLabel;
	private: System::Windows::Forms::Label^ NoTopMatchesLabel;
	private: System::Windows::Forms::NumericUpDown^ topMatchesNumericUpDown;
	private: System::Windows::Forms::Button^ submitButton;
	private: System::Windows::Forms::PictureBox^ targetImagePictureBox;
	private: System::Windows::Forms::PictureBox^ resultPictureBox;
	private: System::Windows::Forms::Label^ targetImageDisplayLabel;
	private: System::Windows::Forms::Label^ topMatchesDisplayLabel;
	private: System::Windows::Forms::Button^ previousButton;
	private: System::Windows::Forms::Button^ nextButton;
	private: System::Windows::Forms::Label^ matchNoLabel;
	private: System::Windows::Forms::Button^ uploadImageDirButton;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::NumericUpDown^ binsChannelNumericUpDown;
	private: System::Windows::Forms::Label^ NoBinsChannelLabel;
	private: System::Windows::Forms::Label^ targetImageFileNameLabel;
	private: System::Windows::Forms::Label^ resultFileNameLabel;
	private: System::Windows::Forms::NumericUpDown^ binsTextureChannelNumericUpDown;
	private: System::Windows::Forms::Label^ NoBinsTextureChannelLabel;
	private: System::Windows::Forms::ToolStripMenuItem^ customDesignWithFaceDetectionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ customDesignToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ customDesignWithFaceDetectionToolStripMenuItem1;















	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		///  GUI component initialization.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->operationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateFeatureVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baselineMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->multiHistogramMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textureAndColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customDesignToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->identifyMatchesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baselineMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->multiHistogramMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textureAndColorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deepNetworkEmbeddingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customDesignToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customDesignWithFaceDetectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->headingLabel = (gcnew System::Windows::Forms::Label());
			this->displayImageDirLabel = (gcnew System::Windows::Forms::Label());
			this->uploadFeatureFile = (gcnew System::Windows::Forms::Button());
			this->displayFeatureFileLabel = (gcnew System::Windows::Forms::Label());
			this->NoTopMatchesLabel = (gcnew System::Windows::Forms::Label());
			this->topMatchesNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->targetImagePictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->resultPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->targetImageDisplayLabel = (gcnew System::Windows::Forms::Label());
			this->topMatchesDisplayLabel = (gcnew System::Windows::Forms::Label());
			this->previousButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			this->matchNoLabel = (gcnew System::Windows::Forms::Label());
			this->uploadImageDirButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->binsChannelNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->NoBinsChannelLabel = (gcnew System::Windows::Forms::Label());
			this->targetImageFileNameLabel = (gcnew System::Windows::Forms::Label());
			this->resultFileNameLabel = (gcnew System::Windows::Forms::Label());
			this->binsTextureChannelNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->NoBinsTextureChannelLabel = (gcnew System::Windows::Forms::Label());
			this->customDesignWithFaceDetectionToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->topMatchesNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetImagePictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binsChannelNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binsTextureChannelNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->operationsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1052, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// operationsToolStripMenuItem
			// 
			this->operationsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->generateFeatureVectorToolStripMenuItem,
					this->identifyMatchesToolStripMenuItem, this->resetToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->operationsToolStripMenuItem->Name = L"operationsToolStripMenuItem";
			this->operationsToolStripMenuItem->Size = System::Drawing::Size(77, 20);
			this->operationsToolStripMenuItem->Text = L"Operations";
			// 
			// generateFeatureVectorToolStripMenuItem
			// 
			this->generateFeatureVectorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->baselineMatchingToolStripMenuItem,
					this->histogramMatchingToolStripMenuItem, this->multiHistogramMatchingToolStripMenuItem, this->textureAndColorToolStripMenuItem,
					this->customDesignToolStripMenuItem1, this->customDesignWithFaceDetectionToolStripMenuItem1
			});
			this->generateFeatureVectorToolStripMenuItem->Name = L"generateFeatureVectorToolStripMenuItem";
			this->generateFeatureVectorToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->generateFeatureVectorToolStripMenuItem->Text = L"Generate Feature Vector";
			// 
			// baselineMatchingToolStripMenuItem
			// 
			this->baselineMatchingToolStripMenuItem->Name = L"baselineMatchingToolStripMenuItem";
			this->baselineMatchingToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->baselineMatchingToolStripMenuItem->Text = L"Baseline Matching";
			// 
			// histogramMatchingToolStripMenuItem
			// 
			this->histogramMatchingToolStripMenuItem->Name = L"histogramMatchingToolStripMenuItem";
			this->histogramMatchingToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->histogramMatchingToolStripMenuItem->Text = L"Histogram Matching";
			// 
			// multiHistogramMatchingToolStripMenuItem
			// 
			this->multiHistogramMatchingToolStripMenuItem->Name = L"multiHistogramMatchingToolStripMenuItem";
			this->multiHistogramMatchingToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->multiHistogramMatchingToolStripMenuItem->Text = L"Multi-Histogram Matching";
			// 
			// textureAndColorToolStripMenuItem
			// 
			this->textureAndColorToolStripMenuItem->Name = L"textureAndColorToolStripMenuItem";
			this->textureAndColorToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->textureAndColorToolStripMenuItem->Text = L"Texture And Color";
			// 
			// customDesignToolStripMenuItem1
			// 
			this->customDesignToolStripMenuItem1->Name = L"customDesignToolStripMenuItem1";
			this->customDesignToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->customDesignToolStripMenuItem1->Text = L"Custom Design";
			// 
			// identifyMatchesToolStripMenuItem
			// 
			this->identifyMatchesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->baselineMatchingToolStripMenuItem1,
					this->histogramMatchingToolStripMenuItem1, this->multiHistogramMatchingToolStripMenuItem1, this->textureAndColorToolStripMenuItem1,
					this->deepNetworkEmbeddingsToolStripMenuItem, this->customDesignToolStripMenuItem, this->customDesignWithFaceDetectionToolStripMenuItem
			});
			this->identifyMatchesToolStripMenuItem->Name = L"identifyMatchesToolStripMenuItem";
			this->identifyMatchesToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->identifyMatchesToolStripMenuItem->Text = L"Identify Matches";
			// 
			// baselineMatchingToolStripMenuItem1
			// 
			this->baselineMatchingToolStripMenuItem1->Name = L"baselineMatchingToolStripMenuItem1";
			this->baselineMatchingToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->baselineMatchingToolStripMenuItem1->Text = L"Baseline Matching";
			// 
			// histogramMatchingToolStripMenuItem1
			// 
			this->histogramMatchingToolStripMenuItem1->Name = L"histogramMatchingToolStripMenuItem1";
			this->histogramMatchingToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->histogramMatchingToolStripMenuItem1->Text = L"Histogram Matching";
			// 
			// multiHistogramMatchingToolStripMenuItem1
			// 
			this->multiHistogramMatchingToolStripMenuItem1->Name = L"multiHistogramMatchingToolStripMenuItem1";
			this->multiHistogramMatchingToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->multiHistogramMatchingToolStripMenuItem1->Text = L"Multi-Histogram Matching";
			// 
			// textureAndColorToolStripMenuItem1
			// 
			this->textureAndColorToolStripMenuItem1->Name = L"textureAndColorToolStripMenuItem1";
			this->textureAndColorToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->textureAndColorToolStripMenuItem1->Text = L"Texture And Color";
			// 
			// deepNetworkEmbeddingsToolStripMenuItem
			// 
			this->deepNetworkEmbeddingsToolStripMenuItem->Name = L"deepNetworkEmbeddingsToolStripMenuItem";
			this->deepNetworkEmbeddingsToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->deepNetworkEmbeddingsToolStripMenuItem->Text = L"Deep Network Embeddings";
			// 
			// customDesignToolStripMenuItem
			// 
			this->customDesignToolStripMenuItem->Name = L"customDesignToolStripMenuItem";
			this->customDesignToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->customDesignToolStripMenuItem->Text = L"Custom Design";
			// 
			// customDesignWithFaceDetectionToolStripMenuItem
			// 
			this->customDesignWithFaceDetectionToolStripMenuItem->Name = L"customDesignWithFaceDetectionToolStripMenuItem";
			this->customDesignWithFaceDetectionToolStripMenuItem->Size = System::Drawing::Size(262, 22);
			this->customDesignWithFaceDetectionToolStripMenuItem->Text = L"Custom Design with Face Detection";
			// 
			// resetToolStripMenuItem
			// 
			this->resetToolStripMenuItem->Name = L"resetToolStripMenuItem";
			this->resetToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->resetToolStripMenuItem->Text = L"Reset";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// headingLabel
			// 
			this->headingLabel->AutoSize = true;
			this->headingLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->headingLabel->Location = System::Drawing::Point(340, 43);
			this->headingLabel->Name = L"headingLabel";
			this->headingLabel->Size = System::Drawing::Size(310, 25);
			this->headingLabel->TabIndex = 1;
			this->headingLabel->Text = L"Content-based Image Retrieval";
			// 
			// displayImageDirLabel
			// 
			this->displayImageDirLabel->AutoSize = true;
			this->displayImageDirLabel->Location = System::Drawing::Point(41, 138);
			this->displayImageDirLabel->Name = L"displayImageDirLabel";
			this->displayImageDirLabel->Size = System::Drawing::Size(69, 13);
			this->displayImageDirLabel->TabIndex = 3;
			this->displayImageDirLabel->Text = L"Select Image";
			// 
			// uploadFeatureFile
			// 
			this->uploadFeatureFile->Location = System::Drawing::Point(269, 90);
			this->uploadFeatureFile->Name = L"uploadFeatureFile";
			this->uploadFeatureFile->Size = System::Drawing::Size(124, 23);
			this->uploadFeatureFile->TabIndex = 4;
			this->uploadFeatureFile->Text = L"Upload Feature File";
			this->uploadFeatureFile->UseVisualStyleBackColor = true;
			this->uploadFeatureFile->Click += gcnew System::EventHandler(this, &CBIR::uploadFeatureFile_Click);
			// 
			// displayFeatureFileLabel
			// 
			this->displayFeatureFileLabel->AutoSize = true;
			this->displayFeatureFileLabel->Location = System::Drawing::Point(269, 137);
			this->displayFeatureFileLabel->Name = L"displayFeatureFileLabel";
			this->displayFeatureFileLabel->Size = System::Drawing::Size(95, 13);
			this->displayFeatureFileLabel->TabIndex = 5;
			this->displayFeatureFileLabel->Text = L"Select Feature File";
			// 
			// NoTopMatchesLabel
			// 
			this->NoTopMatchesLabel->AutoSize = true;
			this->NoTopMatchesLabel->Location = System::Drawing::Point(528, 90);
			this->NoTopMatchesLabel->Name = L"NoTopMatchesLabel";
			this->NoTopMatchesLabel->Size = System::Drawing::Size(80, 13);
			this->NoTopMatchesLabel->TabIndex = 6;
			this->NoTopMatchesLabel->Text = L"# Top Matches";
			// 
			// topMatchesNumericUpDown
			// 
			this->topMatchesNumericUpDown->Location = System::Drawing::Point(689, 90);
			this->topMatchesNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->topMatchesNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->topMatchesNumericUpDown->Name = L"topMatchesNumericUpDown";
			this->topMatchesNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->topMatchesNumericUpDown->TabIndex = 7;
			this->topMatchesNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// submitButton
			// 
			this->submitButton->Location = System::Drawing::Point(840, 87);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(75, 23);
			this->submitButton->TabIndex = 8;
			this->submitButton->Text = L"Generate";
			this->submitButton->UseVisualStyleBackColor = true;
			this->submitButton->Click += gcnew System::EventHandler(this, &CBIR::submitButton_Click);
			// 
			// targetImagePictureBox
			// 
			this->targetImagePictureBox->Location = System::Drawing::Point(45, 245);
			this->targetImagePictureBox->Name = L"targetImagePictureBox";
			this->targetImagePictureBox->Size = System::Drawing::Size(436, 416);
			this->targetImagePictureBox->TabIndex = 9;
			this->targetImagePictureBox->TabStop = false;
			// 
			// resultPictureBox
			// 
			this->resultPictureBox->Location = System::Drawing::Point(516, 245);
			this->resultPictureBox->Name = L"resultPictureBox";
			this->resultPictureBox->Size = System::Drawing::Size(436, 416);
			this->resultPictureBox->TabIndex = 10;
			this->resultPictureBox->TabStop = false;
			// 
			// targetImageDisplayLabel
			// 
			this->targetImageDisplayLabel->AutoSize = true;
			this->targetImageDisplayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->targetImageDisplayLabel->Location = System::Drawing::Point(242, 219);
			this->targetImageDisplayLabel->Name = L"targetImageDisplayLabel";
			this->targetImageDisplayLabel->Size = System::Drawing::Size(51, 17);
			this->targetImageDisplayLabel->TabIndex = 11;
			this->targetImageDisplayLabel->Text = L"Image";
			// 
			// topMatchesDisplayLabel
			// 
			this->topMatchesDisplayLabel->AutoSize = true;
			this->topMatchesDisplayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->topMatchesDisplayLabel->Location = System::Drawing::Point(715, 219);
			this->topMatchesDisplayLabel->Name = L"topMatchesDisplayLabel";
			this->topMatchesDisplayLabel->Size = System::Drawing::Size(101, 17);
			this->topMatchesDisplayLabel->TabIndex = 12;
			this->topMatchesDisplayLabel->Text = L"Top Matches";
			// 
			// previousButton
			// 
			this->previousButton->Location = System::Drawing::Point(516, 708);
			this->previousButton->Name = L"previousButton";
			this->previousButton->Size = System::Drawing::Size(75, 23);
			this->previousButton->TabIndex = 13;
			this->previousButton->Text = L"<<";
			this->previousButton->UseVisualStyleBackColor = true;
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(876, 708);
			this->nextButton->Name = L"nextButton";
			this->nextButton->Size = System::Drawing::Size(75, 23);
			this->nextButton->TabIndex = 14;
			this->nextButton->Text = L">>";
			this->nextButton->UseVisualStyleBackColor = true;
			// 
			// matchNoLabel
			// 
			this->matchNoLabel->AutoSize = true;
			this->matchNoLabel->Location = System::Drawing::Point(718, 708);
			this->matchNoLabel->Name = L"matchNoLabel";
			this->matchNoLabel->Size = System::Drawing::Size(67, 13);
			this->matchNoLabel->TabIndex = 15;
			this->matchNoLabel->Text = L"Match 1 of 1";
			// 
			// uploadImageDirButton
			// 
			this->uploadImageDirButton->Location = System::Drawing::Point(45, 90);
			this->uploadImageDirButton->Name = L"uploadImageDirButton";
			this->uploadImageDirButton->Size = System::Drawing::Size(115, 23);
			this->uploadImageDirButton->TabIndex = 16;
			this->uploadImageDirButton->Text = L"Upload Image";
			this->uploadImageDirButton->UseVisualStyleBackColor = true;
			this->uploadImageDirButton->Click += gcnew System::EventHandler(this, &CBIR::uploadImageDirButton_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png|All files|*.*";
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->Filter = L"Feature Files|*.csv|All files|*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileName = L"featureFile.csv";
			this->saveFileDialog1->Filter = L"CSV Files (*.csv)|*.csv|All Files (*.*)|*.*";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(44, 758);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(908, 23);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 17;
			// 
			// binsChannelNumericUpDown
			// 
			this->binsChannelNumericUpDown->Location = System::Drawing::Point(689, 127);
			this->binsChannelNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->binsChannelNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->binsChannelNumericUpDown->Name = L"binsChannelNumericUpDown";
			this->binsChannelNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->binsChannelNumericUpDown->TabIndex = 19;
			this->binsChannelNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NoBinsChannelLabel
			// 
			this->NoBinsChannelLabel->AutoSize = true;
			this->NoBinsChannelLabel->Location = System::Drawing::Point(528, 127);
			this->NoBinsChannelLabel->Name = L"NoBinsChannelLabel";
			this->NoBinsChannelLabel->Size = System::Drawing::Size(98, 13);
			this->NoBinsChannelLabel->TabIndex = 18;
			this->NoBinsChannelLabel->Text = L"# Bins Per Channel";
			// 
			// targetImageFileNameLabel
			// 
			this->targetImageFileNameLabel->AutoSize = true;
			this->targetImageFileNameLabel->Location = System::Drawing::Point(242, 680);
			this->targetImageFileNameLabel->Name = L"targetImageFileNameLabel";
			this->targetImageFileNameLabel->Size = System::Drawing::Size(35, 13);
			this->targetImageFileNameLabel->TabIndex = 20;
			this->targetImageFileNameLabel->Text = L"label1";
			// 
			// resultFileNameLabel
			// 
			this->resultFileNameLabel->AutoSize = true;
			this->resultFileNameLabel->Location = System::Drawing::Point(718, 680);
			this->resultFileNameLabel->Name = L"resultFileNameLabel";
			this->resultFileNameLabel->Size = System::Drawing::Size(35, 13);
			this->resultFileNameLabel->TabIndex = 21;
			this->resultFileNameLabel->Text = L"label2";
			// 
			// binsTextureChannelNumericUpDown
			// 
			this->binsTextureChannelNumericUpDown->Location = System::Drawing::Point(689, 169);
			this->binsTextureChannelNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->binsTextureChannelNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->binsTextureChannelNumericUpDown->Name = L"binsTextureChannelNumericUpDown";
			this->binsTextureChannelNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->binsTextureChannelNumericUpDown->TabIndex = 23;
			this->binsTextureChannelNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NoBinsTextureChannelLabel
			// 
			this->NoBinsTextureChannelLabel->AutoSize = true;
			this->NoBinsTextureChannelLabel->Location = System::Drawing::Point(528, 169);
			this->NoBinsTextureChannelLabel->Name = L"NoBinsTextureChannelLabel";
			this->NoBinsTextureChannelLabel->Size = System::Drawing::Size(118, 13);
			this->NoBinsTextureChannelLabel->TabIndex = 22;
			this->NoBinsTextureChannelLabel->Text = L"# Bins Texture Channel";
			// 
			// customDesignWithFaceDetectionToolStripMenuItem1
			// 
			this->customDesignWithFaceDetectionToolStripMenuItem1->Name = L"customDesignWithFaceDetectionToolStripMenuItem1";
			this->customDesignWithFaceDetectionToolStripMenuItem1->Size = System::Drawing::Size(262, 22);
			this->customDesignWithFaceDetectionToolStripMenuItem1->Text = L"Custom Design with Face Detection";
			// 
			// CBIR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1052, 795);
			this->Controls->Add(this->binsTextureChannelNumericUpDown);
			this->Controls->Add(this->NoBinsTextureChannelLabel);
			this->Controls->Add(this->resultFileNameLabel);
			this->Controls->Add(this->targetImageFileNameLabel);
			this->Controls->Add(this->binsChannelNumericUpDown);
			this->Controls->Add(this->NoBinsChannelLabel);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->uploadImageDirButton);
			this->Controls->Add(this->matchNoLabel);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->previousButton);
			this->Controls->Add(this->topMatchesDisplayLabel);
			this->Controls->Add(this->targetImageDisplayLabel);
			this->Controls->Add(this->resultPictureBox);
			this->Controls->Add(this->targetImagePictureBox);
			this->Controls->Add(this->submitButton);
			this->Controls->Add(this->topMatchesNumericUpDown);
			this->Controls->Add(this->NoTopMatchesLabel);
			this->Controls->Add(this->displayFeatureFileLabel);
			this->Controls->Add(this->uploadFeatureFile);
			this->Controls->Add(this->displayImageDirLabel);
			this->Controls->Add(this->headingLabel);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"CBIR";
			this->Text = L"CBIR";
			this->Load += gcnew System::EventHandler(this, &CBIR::CBIR_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->topMatchesNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetImagePictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binsChannelNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binsTextureChannelNumericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	/**
		* @brief Initializes the CBIR form by resetting all controls and setting up event handlers for various menu items and buttons.
		*        This function is called when the CBIR form is loaded.
		*
		* @param sender The object that raised the event.
		* @param e The event data.
		* @return void
		*/
	private: System::Void CBIR_Load(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		// Set up event handlers for menu items
		this->baselineMatchingToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::baselineMatchingToolStripMenuItem1_Click);
		this->baselineMatchingToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::baselineMatchingToolStripMenuItem_Click);

		this->histogramMatchingToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::histogramMatchingToolStripMenuItem_Click);
		this->histogramMatchingToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::histogramMatchingToolStripMenuItem1_Click);

		this->multiHistogramMatchingToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::multiHistogramMatchingToolStripMenuItem_Click);
		this->multiHistogramMatchingToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::multiHistogramMatchingToolStripMenuItem1_Click);

		this->textureAndColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::textureAndColorToolStripMenuItem_Click);
		this->textureAndColorToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::textureAndColorToolStripMenuItem1_Click);

		this->deepNetworkEmbeddingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::deepNetworkEmbeddingsToolStripMenuItem_Click);
		
		this->customDesignToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::customDesignToolStripMenuItem_Click);
		this->customDesignToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::customDesignToolStripMenuItem1_Click);

		this->customDesignWithFaceDetectionToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::customDesignWithFaceDetectionToolStripMenuItem_Click);
		this->customDesignWithFaceDetectionToolStripMenuItem1->Click += gcnew System::EventHandler(this, &CBIR::customDesignWithFaceDetectionToolStripMenuItem1_Click);

		this->resetToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::resetToolStripMenuItem_Click);
		this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &CBIR::exitToolStripMenuItem_Click);
		
		// Set up event handlers for buttons
		this->nextButton->Click += gcnew System::EventHandler(this, &CBIR::nextButton_Click);
		this->previousButton->Click += gcnew System::EventHandler(this, &CBIR::previousButton_Click);
	}

	/**
	* @brief Resets all the controls on the CBIR form to their default state, hiding them from view.
	*
	* @return void
	*/
	private: System::Void resetAllControls() {
		// Hide all controls
		this->uploadImageDirButton->Visible = false;
		this->displayImageDirLabel->Visible = false;
		this->uploadFeatureFile->Visible = false;
		this->displayFeatureFileLabel->Visible = false;
		this->NoTopMatchesLabel->Visible = false;
		this->topMatchesNumericUpDown->Visible = false;

		this->NoBinsChannelLabel->Visible = false;
		this->binsChannelNumericUpDown->Visible = false;
		this->NoBinsTextureChannelLabel->Visible = false;
		this->binsTextureChannelNumericUpDown->Visible = false;

		this->submitButton->Visible = false;

		this->targetImageDisplayLabel->Visible = false;
		this->targetImagePictureBox->Visible = false;
		this->topMatchesDisplayLabel->Visible = false;
		this->resultPictureBox->Visible = false;
		this->previousButton->Visible = false;
		this->nextButton->Visible = false;
		this->matchNoLabel->Visible = false;

		this->targetImageFileNameLabel->Visible = false;
		this->resultFileNameLabel->Visible = false;
		
		this->progressBar1->Visible = false;

		// Reset numeric up-down values to default
		this->topMatchesNumericUpDown->Value = 1;
		this->binsChannelNumericUpDown->Value = 1;
		this->binsTextureChannelNumericUpDown->Value = 1;
	}

	/**
	* @brief Handles the click event for the "Baseline Matching" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void baselineMatchingToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		// Update UI elements
		this->headingLabel->Text = "Identify Matches - Baseline Matching";

		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 1;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}

	/**
	 * @brief Handles the click event for the "Baseline Matching" menu item, resetting controls and updating UI elements accordingly.
	 *
	 * @param sender The object that raised the event.
	 * @param e The event data.
	 * @return void
	 */
	private: System::Void baselineMatchingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();
		
		// Update UI elements
		this->headingLabel->Text = "Generate Feature Vector - Baseline Matching";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 1;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}

	/**
	* @brief Handles the click event for the "Custom Design" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void customDesignToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		// Update UI elements
		this->headingLabel->Text = "Generate Feature Vector - Custom Design";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 6;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}

	/**
	* @brief Handles the click event for the "Custom Design with Face Detection" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void customDesignWithFaceDetectionToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		// Update UI elements
		this->headingLabel->Text = "Generate Feature Vector - Custom Design with Face Detection";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 7;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}
		   

	/**
	* @brief Handles the click event for the "Histogram Matching" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void histogramMatchingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Generate Feature Vector - Histogram Matching";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 2;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}

	/**
	* @brief Handles the click event for the "Histogram Matching" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void histogramMatchingToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Histogram Matching";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 2;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}
	
	/**
	 * @brief Handles the click event for the "Multi-Histogram Matching" menu item, resetting controls and updating UI elements accordingly.
	 *
	 * @param sender The object that raised the event.
	 * @param e The event data.
	 * @return void
	 */
	private: System::Void multiHistogramMatchingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Generate Feature Vector - Multi-Histogram Matching";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 3;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}

	/**
	* @brief Handles the click event for the "Multi-Histogram Matching" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void multiHistogramMatchingToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Multi-Histogram Matching";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 3;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}		  
	
	/**
	 * @brief Handles the click event for the "Texture And Color" menu item, resetting controls and updating UI elements accordingly.
	 *
	 * @param sender The object that raised the event.
	 * @param e The event data.
	 * @return void
	 */
	private: System::Void textureAndColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Generate Feature Vector - Texture And Color";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;
		this->NoBinsTextureChannelLabel->Visible = true;
		this->binsTextureChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 1;
		this->subTaskNo = 4;

		this->uploadImageDirButton->Text = "Upload Directory";
		this->displayImageDirLabel->Text = "Upload Image Directory";
	}

	/**
	* @brief Handles the click event for the "Texture And Color" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void textureAndColorToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Texture And Color";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;
		this->NoBinsChannelLabel->Visible = true;
		this->binsChannelNumericUpDown->Visible = true;
		this->NoBinsTextureChannelLabel->Visible = true;
		this->binsTextureChannelNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 4;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}

	/**
	* @brief Handles the click event for the "Deep Network Embeddings" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void deepNetworkEmbeddingsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Deep Network Embeddings";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 5;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}

	/**
	* @brief Handles the click event for the "Custom Design" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void customDesignToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Custom Design";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 6;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}

	/**
	* @brief Handles the click event for the "Custom Design with Face Detection" menu item, resetting controls and updating UI elements accordingly.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void customDesignWithFaceDetectionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();

		this->headingLabel->Text = "Identify Matches - Custom Design with Face Detection";
		this->uploadImageDirButton->Visible = true;
		this->displayImageDirLabel->Visible = true;
		this->uploadFeatureFile->Visible = true;
		this->displayFeatureFileLabel->Visible = true;
		this->NoTopMatchesLabel->Visible = true;
		this->topMatchesNumericUpDown->Visible = true;

		this->submitButton->Visible = true;

		this->taskNo = 2;
		this->subTaskNo = 7;

		this->uploadImageDirButton->Text = "Upload Image";
		this->displayImageDirLabel->Text = "Select Image";

		this->uploadFeatureFile->Text = "Upload Feature File";
		this->displayFeatureFileLabel->Text = "Select Feature File";
	}
		   
	/**
	* @brief Handles the click event for the "Exit" menu item, exits the application.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}

	/**
	* @brief Handles the click event for the "Reset" menu item, resets all controls.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void resetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAllControls();
	}
		   
	/**
	* @brief Handles the click event for the "Submit" button, determines the appropriate task based on the selected options, and calls corresponding functions.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void submitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->taskNo == 2)
		{
			resetResultPictureBox();

			switch (this->subTaskNo) {
			case 1:
				baselineMatchingTask();
				break;
			case 2:
				histogramMatchingTask();
				break;
			case 3:
				multiHistogramMatchingTask();
				break;
			case 4:
				textureAndColorMatchingTask();
				break;
			case 5:
				deepNetworkEmbeddingsTask();
				break;
			case 6:
				combinedFeaturesTask();
				break;
			case 7:
				combinedFeaturesFaceTask();
				break;
			default:
				resetAllControls();
			}
		}
		else
		{
			switch (this->subTaskNo) {
			case 1:
				baselineCalculationTask();
				break;
			case 2:
				histogramCalculationTask();
				break;
			case 3:
				multiHistogramCalculationTask();
				break;
			case 4:
				textureAndColorCalculationTask();
				break;
			case 6:
				combinedFeaturesCalculationTask();
				break;
			case 7:
				combinedFeaturesWithFaceDetectionCalculationTask();
				break;
			default:
				resetAllControls();
			}
		}
	}

	/**
	* @brief Performs baseline matching task, updating the progress bar and image display accordingly.
	*
	* @return void
	*/
	private: System::Void  baselineMatchingTask() {

		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performBaselineMatching(stdTargetImagePath, topMatches, stdFeatureFilePath);
		
		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Performs histogram matching task, updating the progress bar and image display accordingly.
	*
	* @return void
	*/
	private: System::Void  histogramMatchingTask() {
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);

		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performHistogramMatching(stdTargetImagePath, topMatches, binsPerChannel, stdFeatureFilePath);
		
		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Performs multi-histogram matching task, updating the progress bar and image display accordingly.
	*
	* @return void
	*/
	private: System::Void  multiHistogramMatchingTask() {
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);

		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performMultiHistogramMatchingTask(stdTargetImagePath, topMatches, binsPerChannel, stdFeatureFilePath);

		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Performs texture and color matching task, updating the progress bar and image display accordingly.
	*
	* @return void
	*/
	private: System::Void  textureAndColorMatchingTask() {
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);
		int binsTextureChannel = Convert::ToInt32(this->binsTextureChannelNumericUpDown->Value);

		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performTextureAndColorMatchingTask(stdTargetImagePath, topMatches, binsPerChannel, binsTextureChannel, stdFeatureFilePath);

		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Handles the 'Deep Network Embeddings' task, performing matching and updating the display accordingly.
	*
	* @return void
	*/
	private: System::Void  deepNetworkEmbeddingsTask() {

		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performdeepNetworkEmbeddingsMatching(stdTargetImagePath, topMatches, stdFeatureFilePath);

		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Handles the 'Combined Features' task, performing matching and updating the display accordingly.
	*
	* @return void
	*/
	private: System::Void  combinedFeaturesTask() {
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topMatches) = performCustomDesignCbir(stdTargetImagePath, stdFeatureFilePath, topMatches);

		this->progressBar1->Visible = false;

		UpdateImageDisplay();
	}

	/**
	* @brief Handles the 'Combined Features' task, performing matching and updating the display accordingly.
	*
	* @return void
	*/
	private: System::Void  combinedFeaturesFaceTask() {
		if (System::String::IsNullOrWhiteSpace(this->targetImagePath) || System::String::IsNullOrWhiteSpace(this->featureFilePath)) {
			MessageBox::Show("Please select both target image and feature file.");
			return;
		}

		int topMatches = Convert::ToInt32(this->topMatchesNumericUpDown->Value);

		msclr::interop::marshal_context context;
		std::string stdTargetImagePath = context.marshal_as<std::string>(this->targetImagePath);
		std::string stdFeatureFilePath = context.marshal_as<std::string>(this->featureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		*(this->topCustomMatches) = performCustomDesignFaceCbir(stdFeatureFilePath, stdTargetImagePath, topMatches);

		this->progressBar1->Visible = false;

		UpdateCustomDesignImageDisplay();
	}

	/**
	* @brief Converts a cv::Mat image to a System::Drawing::Bitmap.
	*
	* @param matImage The input cv::Mat image.
	* @return System::Drawing::Bitmap^ The converted bitmap image.
	*/
	System::Drawing::Bitmap^ MatToBitmap(cv::Mat& matImage) {
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(matImage.cols, matImage.rows, matImage.step,
			System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)matImage.data);
		return bitmap;
	}

	/**
	 * @brief Updates the display with the custom design image matches.
	 *
	 * @return void
	 */
	private: System::Void UpdateCustomDesignImageDisplay() {
		if (this->topCustomMatches->empty()) return;

		this->topMatchesDisplayLabel->Visible = true;
		this->resultPictureBox->Visible = true;
		this->previousButton->Visible = true;
		this->nextButton->Visible = true;
		this->matchNoLabel->Visible = true;
		this->resultFileNameLabel->Visible = true;

		topMatchesDisplayLabel->Text = "Top " + this->topCustomMatches->size() + " Matches";

		// Extract the current image and filename from the pair
		cv::Mat& currentImage = (*this->topCustomMatches)[currentIndex].first;
		std::string currentFilename = (*this->topCustomMatches)[currentIndex].second;

		// Convert cv::Mat to System::Drawing::Bitmap^
		System::Drawing::Bitmap^ bitmapImage = MatToBitmap(currentImage); 

		// Display the converted image in the PictureBox
		this->resultPictureBox->Image = bitmapImage;
		this->resultPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;

		// Extract the filename from the image path and display it
		System::String^ managedFileName = gcnew System::String(currentFilename.c_str());
		System::String^ fileName = System::IO::Path::GetFileName(managedFileName);
		this->resultFileNameLabel->Text = fileName;

		// Update match number label
		this->matchNoLabel->Text = "Match " + (currentIndex + 1).ToString() + " of " + this->topCustomMatches->size().ToString();

		// Enable/disable buttons
		this->previousButton->Enabled = currentIndex > 0;
		this->nextButton->Enabled = currentIndex < this->topCustomMatches->size() - 1;
	}

	/**
	* @brief Resets the result picture box display.
	*
	* @return void
	*/
	private: System::Void resetResultPictureBox() {

		this->topMatchesDisplayLabel->Visible = false;
		this->resultPictureBox->Visible = false;
		this->previousButton->Visible = false;
		this->nextButton->Visible = false;
		this->matchNoLabel->Visible = false;
		this->resultFileNameLabel->Visible = false;

		currentIndex = 0;
	}

	/**
	* @brief Updates the image display.
	*
	* @return void
	*/
	private: System::Void UpdateImageDisplay() {
		if (this->topMatches->empty()) return;

		this->topMatchesDisplayLabel->Visible = true;
		this->resultPictureBox->Visible = true;
		this->previousButton->Visible = true;
		this->nextButton->Visible = true;
		this->matchNoLabel->Visible = true;
		this->resultFileNameLabel->Visible = true;


		topMatchesDisplayLabel->Text = "Top " + this->topMatches->size() + " Matches";

		// Load and display the current image		
		System::String^ imagePath = gcnew System::String((*topMatches)[currentIndex].c_str());
		this->resultPictureBox->Image = Image::FromFile(imagePath);
		this->resultPictureBox->SizeMode = PictureBoxSizeMode::StretchImage;

		// Extract the filename from the image path and display it
		System::String^ fileName = System::IO::Path::GetFileName(imagePath);
		this->resultFileNameLabel->Text = fileName; 

		// Update match number label
		matchNoLabel->Text = "Match " + (currentIndex + 1).ToString() + " of " + this->topMatches->size().ToString();

		// Enable/disable buttons
		previousButton->Enabled = currentIndex > 0;
		nextButton->Enabled = currentIndex < this->topMatches->size() - 1;
	}

	/**
	* @brief Handles the click event for the 'Previous' button.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void previousButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentIndex > 0) {
			--currentIndex;
			if (this->taskNo == 2 && this->subTaskNo == 7)
			{
				UpdateCustomDesignImageDisplay();
			}
			else
			{
				UpdateImageDisplay();
			}
		}

	}

	/**
	* @brief Handles the click event for the 'Next' button.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void nextButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->taskNo == 2 && this->subTaskNo == 7)
		{
			if (currentIndex < this->topCustomMatches->size() - 1) {
				++currentIndex;
				UpdateCustomDesignImageDisplay();
			}
		}
		else{
			if (currentIndex < this->topMatches->size() - 1) {
				++currentIndex;
				UpdateImageDisplay();
			}
		}
	}

	/**
	* @brief Handles the click event for the 'Upload Feature File' button.
	*        Allows the user to select a feature file or directory based on the current task and sub-task.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void uploadFeatureFile_Click(System::Object^ sender, System::EventArgs^ e) {

		if (this->openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->featureFilePath = this->openFileDialog2->FileName;

			System::String^ fileName = Path::GetFileName(this->featureFilePath);
			this->displayFeatureFileLabel->Text = fileName + " selected";
		}
	}
	

	/**
	* @brief Handles the click event for the 'Upload Image Directory' button.
	*        Allows the user to select an image directory or file based on the current task.
	*
	* @param sender The object that raised the event.
	* @param e The event data.
	* @return void
	*/
	private: System::Void uploadImageDirButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->taskNo == 2)
		{
			if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				this->targetImagePath = this->openFileDialog1->FileName;

				resetResultPictureBox();

				this->targetImageDisplayLabel->Visible = true;
				this->targetImagePictureBox->Visible = true;
				this->targetImageFileNameLabel->Visible = true;

				System::String^ fileName = Path::GetFileName(this->targetImagePath);
				this->displayImageDirLabel->Text = fileName + " selected"; // Display just the filename
				
				this->targetImageFileNameLabel->Text = fileName;

				// Display image in PictureBox (assuming you have a PictureBox named targetImagePictureBox)
				this->targetImagePictureBox->Image = Image::FromFile(this->targetImagePath);
				this->targetImagePictureBox->SizeMode = PictureBoxSizeMode::StretchImage;
			}
		}
		else
		{
			if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				this->imageDirectoryPath = folderBrowserDialog1->SelectedPath;

				this->displayImageDirLabel->Text = imageDirectoryPath + " selected";
			}
		}
	}

	/**
	* @brief Handles the baseline calculation task, including saving the computed features.
	*
	* @return void
	*/
	private: System::Void  baselineCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performBaselineCalculation(stdImageDirectoryPath, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}

	/**
	 * @brief Handles the histogram calculation task, including saving the computed features.
	 *
	 * @return void
	 */
	private: System::Void  histogramCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performHistogramCalculation(stdImageDirectoryPath, binsPerChannel, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}

	/**
	* @brief Handles the multi-histogram calculation task, including saving the computed features.
	*
	* @return void
	*/
	private: System::Void  multiHistogramCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performMultiHistogramCalculationTask(stdImageDirectoryPath, binsPerChannel, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}

	/**
	* @brief Handles the texture and color calculation task, including saving the computed features.
	*
	* @return void
	*/
	private: System::Void  textureAndColorCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		int binsPerChannel = Convert::ToInt32(this->binsChannelNumericUpDown->Value);
		int binsTextureChannel = Convert::ToInt32(this->binsTextureChannelNumericUpDown->Value);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performTextureAndColorCalculationTask(stdImageDirectoryPath, binsPerChannel, binsTextureChannel, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}

	/**
	* @brief Handles the custom design, including saving the computed features.
	*
	* @return void
	*/
	private: System::Void  combinedFeaturesCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performCustomDesignCalculation(stdImageDirectoryPath, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}

		   
	/**
	* @brief Handles the custom design with face detection, including saving the computed features.
	*
	* @return void
	*/
	private: System::Void  combinedFeaturesWithFaceDetectionCalculationTask() {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog1->FileName;

		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath)) {
			MessageBox::Show("Please select image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		this->progressBar1->Visible = true;
		this->progressBar1->Refresh();

		performCustomDesignCalculationFace(stdImageDirectoryPath, stdSaveFeatureFilePath);

		this->progressBar1->Visible = false;

		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}
};

}
