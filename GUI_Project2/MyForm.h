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
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			topMatches = new std::vector<std::string>();
			currentIndex = 0;
			System::String^ initialDirectory = System::IO::Path::GetDirectoryName(System::IO::Path::GetDirectoryName(Application::StartupPath));
			this->folderBrowserDialog2->SelectedPath = initialDirectory;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			if (topMatches != nullptr) {
				delete topMatches;
				topMatches = nullptr;
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
	private: System::Windows::Forms::Button^ baselineMatchingButton;
	protected:
	private: System::Windows::Forms::Button^ histogramMatchingButton;
	private: System::Windows::Forms::Button^ multiHistogramMatchingButton;
	private: System::Windows::Forms::Button^ textureColorButton;
	private: System::Windows::Forms::Button^ deepNetworkEmbButton;
	private: System::Windows::Forms::Button^ customDesignButton;
	private: System::Windows::Forms::Button^ targetImagePathButton;
	private: System::Windows::Forms::Label^ targetImagePathLabel;
	private: System::Windows::Forms::Label^ featureFilePathLabel;
	private: System::Windows::Forms::Button^ featurefilePathButton;
	private: System::Windows::Forms::Label^ NoTopMatchesLabel;
	private: System::Windows::Forms::Label^ noOfBinsTexturelabel;



	private: System::Windows::Forms::Label^ noOfBinsLabel;


	private: System::Windows::Forms::Button^ submitButton;
	private: System::Windows::Forms::Button^ generateFeatureFileButton;
	private: System::Windows::Forms::Button^ identifyMatchesButton;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::NumericUpDown^ topMatchesNumericUpDown;
	private: System::Windows::Forms::PictureBox^ targetImagePictureBox;
	private: System::Windows::Forms::PictureBox^ resultPictureBox;

	private: System::Windows::Forms::Button^ previousButton;
	private: System::Windows::Forms::Button^ nextButton;
	private: System::Windows::Forms::Label^ targetImageDisplayLabel;

	private: System::Windows::Forms::Label^ topMatchesDisplayLabel;


	private: System::Windows::Forms::NumericUpDown^ noOfBinsNumericUpDown;
	private: System::Windows::Forms::NumericUpDown^ noOfBinsTextureNumericUpDown;
	private: System::Windows::Forms::Button^ resetButton;
	private: System::Windows::Forms::Label^ matchNoLabel;
	
	
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog2;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog2;

	private: System::Windows::Forms::MenuStrip^ menuStrip2;
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
	private: System::Windows::Forms::ToolStripMenuItem^ customDesignInCBIRToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Label^ headingLabel;
	private: System::Windows::Forms::Label^ targetImageFileNameLabel;

	private: System::Windows::Forms::Label^ resultFileNameLabel;















	protected:











	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->baselineMatchingButton = (gcnew System::Windows::Forms::Button());
			this->histogramMatchingButton = (gcnew System::Windows::Forms::Button());
			this->multiHistogramMatchingButton = (gcnew System::Windows::Forms::Button());
			this->textureColorButton = (gcnew System::Windows::Forms::Button());
			this->deepNetworkEmbButton = (gcnew System::Windows::Forms::Button());
			this->customDesignButton = (gcnew System::Windows::Forms::Button());
			this->targetImagePathButton = (gcnew System::Windows::Forms::Button());
			this->targetImagePathLabel = (gcnew System::Windows::Forms::Label());
			this->featureFilePathLabel = (gcnew System::Windows::Forms::Label());
			this->featurefilePathButton = (gcnew System::Windows::Forms::Button());
			this->NoTopMatchesLabel = (gcnew System::Windows::Forms::Label());
			this->noOfBinsTexturelabel = (gcnew System::Windows::Forms::Label());
			this->noOfBinsLabel = (gcnew System::Windows::Forms::Label());
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->generateFeatureFileButton = (gcnew System::Windows::Forms::Button());
			this->identifyMatchesButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->topMatchesNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->targetImagePictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->resultPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->previousButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			this->targetImageDisplayLabel = (gcnew System::Windows::Forms::Label());
			this->topMatchesDisplayLabel = (gcnew System::Windows::Forms::Label());
			this->noOfBinsNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->noOfBinsTextureNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->matchNoLabel = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog2 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->operationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->generateFeatureVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baselineMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->multiHistogramMatchingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textureAndColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->identifyMatchesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baselineMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->multiHistogramMatchingToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textureAndColorToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deepNetworkEmbeddingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customDesignInCBIRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->headingLabel = (gcnew System::Windows::Forms::Label());
			this->targetImageFileNameLabel = (gcnew System::Windows::Forms::Label());
			this->resultFileNameLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->topMatchesNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetImagePictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noOfBinsNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noOfBinsTextureNumericUpDown))->BeginInit();
			this->menuStrip2->SuspendLayout();
			this->SuspendLayout();
			// 
			// baselineMatchingButton
			// 
			this->baselineMatchingButton->Location = System::Drawing::Point(273, 107);
			this->baselineMatchingButton->Name = L"baselineMatchingButton";
			this->baselineMatchingButton->Size = System::Drawing::Size(148, 23);
			this->baselineMatchingButton->TabIndex = 0;
			this->baselineMatchingButton->Text = L"Baseline Matching";
			this->baselineMatchingButton->UseVisualStyleBackColor = true;
			// 
			// histogramMatchingButton
			// 
			this->histogramMatchingButton->Location = System::Drawing::Point(273, 153);
			this->histogramMatchingButton->Name = L"histogramMatchingButton";
			this->histogramMatchingButton->Size = System::Drawing::Size(148, 23);
			this->histogramMatchingButton->TabIndex = 1;
			this->histogramMatchingButton->Text = L"Histogram Matching";
			this->histogramMatchingButton->UseVisualStyleBackColor = true;
			// 
			// multiHistogramMatchingButton
			// 
			this->multiHistogramMatchingButton->Location = System::Drawing::Point(273, 200);
			this->multiHistogramMatchingButton->Name = L"multiHistogramMatchingButton";
			this->multiHistogramMatchingButton->Size = System::Drawing::Size(148, 23);
			this->multiHistogramMatchingButton->TabIndex = 2;
			this->multiHistogramMatchingButton->Text = L"Multi-Histogram Matching";
			this->multiHistogramMatchingButton->UseVisualStyleBackColor = true;
			// 
			// textureColorButton
			// 
			this->textureColorButton->Location = System::Drawing::Point(273, 252);
			this->textureColorButton->Name = L"textureColorButton";
			this->textureColorButton->Size = System::Drawing::Size(148, 23);
			this->textureColorButton->TabIndex = 3;
			this->textureColorButton->Text = L"Texture And Color";
			this->textureColorButton->UseVisualStyleBackColor = true;
			// 
			// deepNetworkEmbButton
			// 
			this->deepNetworkEmbButton->Location = System::Drawing::Point(273, 303);
			this->deepNetworkEmbButton->Name = L"deepNetworkEmbButton";
			this->deepNetworkEmbButton->Size = System::Drawing::Size(148, 23);
			this->deepNetworkEmbButton->TabIndex = 4;
			this->deepNetworkEmbButton->Text = L"Deep Network Embeddings";
			this->deepNetworkEmbButton->UseVisualStyleBackColor = true;
			// 
			// customDesignButton
			// 
			this->customDesignButton->Location = System::Drawing::Point(273, 358);
			this->customDesignButton->Name = L"customDesignButton";
			this->customDesignButton->Size = System::Drawing::Size(148, 23);
			this->customDesignButton->TabIndex = 5;
			this->customDesignButton->Text = L"Custom Design in CBIR";
			this->customDesignButton->UseVisualStyleBackColor = true;
			// 
			// targetImagePathButton
			// 
			this->targetImagePathButton->Location = System::Drawing::Point(639, 107);
			this->targetImagePathButton->Name = L"targetImagePathButton";
			this->targetImagePathButton->Size = System::Drawing::Size(107, 23);
			this->targetImagePathButton->TabIndex = 7;
			this->targetImagePathButton->Text = L"Target Image";
			this->targetImagePathButton->UseVisualStyleBackColor = true;
			// 
			// targetImagePathLabel
			// 
			this->targetImagePathLabel->AutoSize = true;
			this->targetImagePathLabel->Location = System::Drawing::Point(484, 112);
			this->targetImagePathLabel->Name = L"targetImagePathLabel";
			this->targetImagePathLabel->Size = System::Drawing::Size(128, 13);
			this->targetImagePathLabel->TabIndex = 6;
			this->targetImagePathLabel->Text = L"Select Target Image Path";
			// 
			// featureFilePathLabel
			// 
			this->featureFilePathLabel->AutoSize = true;
			this->featureFilePathLabel->Location = System::Drawing::Point(484, 153);
			this->featureFilePathLabel->Name = L"featureFilePathLabel";
			this->featureFilePathLabel->Size = System::Drawing::Size(120, 13);
			this->featureFilePathLabel->TabIndex = 8;
			this->featureFilePathLabel->Text = L"Select Feature File Path";
			// 
			// featurefilePathButton
			// 
			this->featurefilePathButton->Location = System::Drawing::Point(639, 153);
			this->featurefilePathButton->Name = L"featurefilePathButton";
			this->featurefilePathButton->Size = System::Drawing::Size(107, 23);
			this->featurefilePathButton->TabIndex = 9;
			this->featurefilePathButton->Text = L"Feature File";
			this->featurefilePathButton->UseVisualStyleBackColor = true;
			// 
			// NoTopMatchesLabel
			// 
			this->NoTopMatchesLabel->AutoSize = true;
			this->NoTopMatchesLabel->Location = System::Drawing::Point(484, 200);
			this->NoTopMatchesLabel->Name = L"NoTopMatchesLabel";
			this->NoTopMatchesLabel->Size = System::Drawing::Size(122, 13);
			this->NoTopMatchesLabel->TabIndex = 10;
			this->NoTopMatchesLabel->Text = L"Number of Top Matches";
			// 
			// noOfBinsTexturelabel
			// 
			this->noOfBinsTexturelabel->AutoSize = true;
			this->noOfBinsTexturelabel->Location = System::Drawing::Point(484, 303);
			this->noOfBinsTexturelabel->Name = L"noOfBinsTexturelabel";
			this->noOfBinsTexturelabel->Size = System::Drawing::Size(133, 13);
			this->noOfBinsTexturelabel->TabIndex = 12;
			this->noOfBinsTexturelabel->Text = L"Number of Bins for Texture";
			// 
			// noOfBinsLabel
			// 
			this->noOfBinsLabel->AutoSize = true;
			this->noOfBinsLabel->Location = System::Drawing::Point(484, 252);
			this->noOfBinsLabel->Name = L"noOfBinsLabel";
			this->noOfBinsLabel->Size = System::Drawing::Size(140, 13);
			this->noOfBinsLabel->TabIndex = 14;
			this->noOfBinsLabel->Text = L"Number of Bins Per Channel";
			// 
			// submitButton
			// 
			this->submitButton->Location = System::Drawing::Point(639, 357);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(75, 23);
			this->submitButton->TabIndex = 16;
			this->submitButton->Text = L"Submit";
			this->submitButton->UseVisualStyleBackColor = true;
			// 
			// generateFeatureFileButton
			// 
			this->generateFeatureFileButton->Location = System::Drawing::Point(36, 107);
			this->generateFeatureFileButton->Name = L"generateFeatureFileButton";
			this->generateFeatureFileButton->Size = System::Drawing::Size(159, 23);
			this->generateFeatureFileButton->TabIndex = 0;
			this->generateFeatureFileButton->Text = L"Generate Feature Vector";
			this->generateFeatureFileButton->UseVisualStyleBackColor = true;
			// 
			// identifyMatchesButton
			// 
			this->identifyMatchesButton->Location = System::Drawing::Point(40, 200);
			this->identifyMatchesButton->Name = L"identifyMatchesButton";
			this->identifyMatchesButton->Size = System::Drawing::Size(159, 23);
			this->identifyMatchesButton->TabIndex = 0;
			this->identifyMatchesButton->Text = L"Identify Matches";
			this->identifyMatchesButton->UseVisualStyleBackColor = true;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png|All files|*.*";
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			this->openFileDialog2->Filter = L"Feature Files|*.csv|All files|*.*";
			// 
			// topMatchesNumericUpDown
			// 
			this->topMatchesNumericUpDown->Location = System::Drawing::Point(639, 200);
			this->topMatchesNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->topMatchesNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->topMatchesNumericUpDown->Name = L"topMatchesNumericUpDown";
			this->topMatchesNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->topMatchesNumericUpDown->TabIndex = 18;
			this->topMatchesNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// targetImagePictureBox
			// 
			this->targetImagePictureBox->Location = System::Drawing::Point(37, 446);
			this->targetImagePictureBox->Name = L"targetImagePictureBox";
			this->targetImagePictureBox->Size = System::Drawing::Size(387, 311);
			this->targetImagePictureBox->TabIndex = 19;
			this->targetImagePictureBox->TabStop = false;
			// 
			// resultPictureBox
			// 
			this->resultPictureBox->Location = System::Drawing::Point(467, 446);
			this->resultPictureBox->Name = L"resultPictureBox";
			this->resultPictureBox->Size = System::Drawing::Size(387, 311);
			this->resultPictureBox->TabIndex = 20;
			this->resultPictureBox->TabStop = false;
			// 
			// previousButton
			// 
			this->previousButton->Location = System::Drawing::Point(467, 791);
			this->previousButton->Name = L"previousButton";
			this->previousButton->Size = System::Drawing::Size(75, 23);
			this->previousButton->TabIndex = 21;
			this->previousButton->Text = L"previous";
			this->previousButton->UseVisualStyleBackColor = true;
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(779, 791);
			this->nextButton->Name = L"nextButton";
			this->nextButton->Size = System::Drawing::Size(75, 23);
			this->nextButton->TabIndex = 22;
			this->nextButton->Text = L"next";
			this->nextButton->UseVisualStyleBackColor = true;
			// 
			// targetImageDisplayLabel
			// 
			this->targetImageDisplayLabel->AutoSize = true;
			this->targetImageDisplayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->targetImageDisplayLabel->Location = System::Drawing::Point(184, 410);
			this->targetImageDisplayLabel->Name = L"targetImageDisplayLabel";
			this->targetImageDisplayLabel->Size = System::Drawing::Size(82, 13);
			this->targetImageDisplayLabel->TabIndex = 23;
			this->targetImageDisplayLabel->Text = L"Target Image";
			// 
			// topMatchesDisplayLabel
			// 
			this->topMatchesDisplayLabel->AutoSize = true;
			this->topMatchesDisplayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->topMatchesDisplayLabel->Location = System::Drawing::Point(639, 410);
			this->topMatchesDisplayLabel->Name = L"topMatchesDisplayLabel";
			this->topMatchesDisplayLabel->Size = System::Drawing::Size(81, 13);
			this->topMatchesDisplayLabel->TabIndex = 24;
			this->topMatchesDisplayLabel->Text = L"Top Matches";
			// 
			// noOfBinsNumericUpDown
			// 
			this->noOfBinsNumericUpDown->Location = System::Drawing::Point(639, 252);
			this->noOfBinsNumericUpDown->Name = L"noOfBinsNumericUpDown";
			this->noOfBinsNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->noOfBinsNumericUpDown->TabIndex = 25;
			// 
			// noOfBinsTextureNumericUpDown
			// 
			this->noOfBinsTextureNumericUpDown->Location = System::Drawing::Point(639, 295);
			this->noOfBinsTextureNumericUpDown->Name = L"noOfBinsTextureNumericUpDown";
			this->noOfBinsTextureNumericUpDown->Size = System::Drawing::Size(120, 20);
			this->noOfBinsTextureNumericUpDown->TabIndex = 26;
			// 
			// resetButton
			// 
			this->resetButton->Location = System::Drawing::Point(44, 299);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(159, 23);
			this->resetButton->TabIndex = 27;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			// 
			// matchNoLabel
			// 
			this->matchNoLabel->AutoSize = true;
			this->matchNoLabel->Location = System::Drawing::Point(639, 791);
			this->matchNoLabel->Name = L"matchNoLabel";
			this->matchNoLabel->Size = System::Drawing::Size(46, 13);
			this->matchNoLabel->TabIndex = 28;
			this->matchNoLabel->Text = L"Match 1";
			// 
			// saveFileDialog2
			// 
			this->saveFileDialog2->FileName = L"featureFile.csv";
			this->saveFileDialog2->Filter = L"CSV Files (*.csv)|*.csv|All Files (*.*)|*.*";
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->operationsToolStripMenuItem });
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(959, 24);
			this->menuStrip2->TabIndex = 30;
			this->menuStrip2->Text = L"menuStrip2";
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
			this->generateFeatureVectorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->baselineMatchingToolStripMenuItem,
					this->histogramMatchingToolStripMenuItem, this->multiHistogramMatchingToolStripMenuItem, this->textureAndColorToolStripMenuItem
			});
			this->generateFeatureVectorToolStripMenuItem->Name = L"generateFeatureVectorToolStripMenuItem";
			this->generateFeatureVectorToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->generateFeatureVectorToolStripMenuItem->Text = L"Generate Feature Vector";
			// 
			// baselineMatchingToolStripMenuItem
			// 
			this->baselineMatchingToolStripMenuItem->Name = L"baselineMatchingToolStripMenuItem";
			this->baselineMatchingToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->baselineMatchingToolStripMenuItem->Text = L"Baseline Matching";
			this->baselineMatchingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::baselineMatchingToolStripMenuItem_Click);
			// 
			// histogramMatchingToolStripMenuItem
			// 
			this->histogramMatchingToolStripMenuItem->Name = L"histogramMatchingToolStripMenuItem";
			this->histogramMatchingToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->histogramMatchingToolStripMenuItem->Text = L"Histogram Matching";
			// 
			// multiHistogramMatchingToolStripMenuItem
			// 
			this->multiHistogramMatchingToolStripMenuItem->Name = L"multiHistogramMatchingToolStripMenuItem";
			this->multiHistogramMatchingToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->multiHistogramMatchingToolStripMenuItem->Text = L"Multi-Histogram Matching";
			// 
			// textureAndColorToolStripMenuItem
			// 
			this->textureAndColorToolStripMenuItem->Name = L"textureAndColorToolStripMenuItem";
			this->textureAndColorToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->textureAndColorToolStripMenuItem->Text = L"Texture And Color";
			// 
			// identifyMatchesToolStripMenuItem
			// 
			this->identifyMatchesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->baselineMatchingToolStripMenuItem1,
					this->histogramMatchingToolStripMenuItem1, this->multiHistogramMatchingToolStripMenuItem1, this->textureAndColorToolStripMenuItem1,
					this->deepNetworkEmbeddingsToolStripMenuItem, this->customDesignInCBIRToolStripMenuItem
			});
			this->identifyMatchesToolStripMenuItem->Name = L"identifyMatchesToolStripMenuItem";
			this->identifyMatchesToolStripMenuItem->Size = System::Drawing::Size(199, 22);
			this->identifyMatchesToolStripMenuItem->Text = L"Identify Matches";
			// 
			// baselineMatchingToolStripMenuItem1
			// 
			this->baselineMatchingToolStripMenuItem1->Name = L"baselineMatchingToolStripMenuItem1";
			this->baselineMatchingToolStripMenuItem1->Size = System::Drawing::Size(218, 22);
			this->baselineMatchingToolStripMenuItem1->Text = L"Baseline Matching";
			// 
			// histogramMatchingToolStripMenuItem1
			// 
			this->histogramMatchingToolStripMenuItem1->Name = L"histogramMatchingToolStripMenuItem1";
			this->histogramMatchingToolStripMenuItem1->Size = System::Drawing::Size(218, 22);
			this->histogramMatchingToolStripMenuItem1->Text = L"Histogram Matching";
			// 
			// multiHistogramMatchingToolStripMenuItem1
			// 
			this->multiHistogramMatchingToolStripMenuItem1->Name = L"multiHistogramMatchingToolStripMenuItem1";
			this->multiHistogramMatchingToolStripMenuItem1->Size = System::Drawing::Size(218, 22);
			this->multiHistogramMatchingToolStripMenuItem1->Text = L"Multi-Histogram Matching";
			// 
			// textureAndColorToolStripMenuItem1
			// 
			this->textureAndColorToolStripMenuItem1->Name = L"textureAndColorToolStripMenuItem1";
			this->textureAndColorToolStripMenuItem1->Size = System::Drawing::Size(218, 22);
			this->textureAndColorToolStripMenuItem1->Text = L"Texture And Color";
			// 
			// deepNetworkEmbeddingsToolStripMenuItem
			// 
			this->deepNetworkEmbeddingsToolStripMenuItem->Name = L"deepNetworkEmbeddingsToolStripMenuItem";
			this->deepNetworkEmbeddingsToolStripMenuItem->Size = System::Drawing::Size(218, 22);
			this->deepNetworkEmbeddingsToolStripMenuItem->Text = L"Deep Network Embeddings";
			// 
			// customDesignInCBIRToolStripMenuItem
			// 
			this->customDesignInCBIRToolStripMenuItem->Name = L"customDesignInCBIRToolStripMenuItem";
			this->customDesignInCBIRToolStripMenuItem->Size = System::Drawing::Size(218, 22);
			this->customDesignInCBIRToolStripMenuItem->Text = L"Custom Design in CBIR";
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
			this->headingLabel->Location = System::Drawing::Point(308, 33);
			this->headingLabel->Name = L"headingLabel";
			this->headingLabel->Size = System::Drawing::Size(310, 25);
			this->headingLabel->TabIndex = 31;
			this->headingLabel->Text = L"Content-based Image Retrieval";
			// 
			// targetImageFileNameLabel
			// 
			this->targetImageFileNameLabel->AutoSize = true;
			this->targetImageFileNameLabel->Location = System::Drawing::Point(204, 768);
			this->targetImageFileNameLabel->Name = L"targetImageFileNameLabel";
			this->targetImageFileNameLabel->Size = System::Drawing::Size(35, 13);
			this->targetImageFileNameLabel->TabIndex = 32;
			this->targetImageFileNameLabel->Text = L"label1";
			// 
			// resultFileNameLabel
			// 
			this->resultFileNameLabel->AutoSize = true;
			this->resultFileNameLabel->Location = System::Drawing::Point(642, 768);
			this->resultFileNameLabel->Name = L"resultFileNameLabel";
			this->resultFileNameLabel->Size = System::Drawing::Size(35, 13);
			this->resultFileNameLabel->TabIndex = 33;
			this->resultFileNameLabel->Text = L"label2";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(959, 836);
			this->Controls->Add(this->resultFileNameLabel);
			this->Controls->Add(this->targetImageFileNameLabel);
			this->Controls->Add(this->headingLabel);
			this->Controls->Add(this->matchNoLabel);
			this->Controls->Add(this->resetButton);
			this->Controls->Add(this->noOfBinsTextureNumericUpDown);
			this->Controls->Add(this->noOfBinsNumericUpDown);
			this->Controls->Add(this->topMatchesDisplayLabel);
			this->Controls->Add(this->targetImageDisplayLabel);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->previousButton);
			this->Controls->Add(this->resultPictureBox);
			this->Controls->Add(this->targetImagePictureBox);
			this->Controls->Add(this->topMatchesNumericUpDown);
			this->Controls->Add(this->identifyMatchesButton);
			this->Controls->Add(this->generateFeatureFileButton);
			this->Controls->Add(this->submitButton);
			this->Controls->Add(this->noOfBinsLabel);
			this->Controls->Add(this->noOfBinsTexturelabel);
			this->Controls->Add(this->NoTopMatchesLabel);
			this->Controls->Add(this->featurefilePathButton);
			this->Controls->Add(this->featureFilePathLabel);
			this->Controls->Add(this->targetImagePathButton);
			this->Controls->Add(this->targetImagePathLabel);
			this->Controls->Add(this->customDesignButton);
			this->Controls->Add(this->deepNetworkEmbButton);
			this->Controls->Add(this->textureColorButton);
			this->Controls->Add(this->multiHistogramMatchingButton);
			this->Controls->Add(this->histogramMatchingButton);
			this->Controls->Add(this->baselineMatchingButton);
			this->Controls->Add(this->menuStrip2);
			this->Name = L"MyForm";
			this->Text = L"CBIR";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->topMatchesNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->targetImagePictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noOfBinsNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->noOfBinsTextureNumericUpDown))->EndInit();
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

		resetAll();

		// Attach event handlers
		this->generateFeatureFileButton->Click += gcnew System::EventHandler(this, &MyForm::generateFeatureFileButton_Click);
		this->identifyMatchesButton->Click += gcnew System::EventHandler(this, &MyForm::identifyMatchesButton_Click);
		this->baselineMatchingButton->Click += gcnew System::EventHandler(this, &MyForm::baselineMatchingButton_Click);
		this->targetImagePathButton->Click += gcnew System::EventHandler(this, &MyForm::targetImagePathButton_Click);
		this->featurefilePathButton->Click += gcnew System::EventHandler(this, &MyForm::featurefilePathButton_Click);
		this->submitButton->Click += gcnew System::EventHandler(this, &MyForm::submitButton_Click);
		this->nextButton->Click += gcnew System::EventHandler(this, &MyForm::nextButton_Click);
		this->previousButton->Click += gcnew System::EventHandler(this, &MyForm::previousButton_Click);
		this->resetButton->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);


	}

	private: System::Void resetAll() {
		// Initially hide buttons that should not be visible
		resetTasks();

		resetSubTasks();
	}

	private: System::Void resetTasks() {
		// Initially hide buttons that should not be visible
		this->baselineMatchingButton->Visible = false;
		this->histogramMatchingButton->Visible = false;
		this->multiHistogramMatchingButton->Visible = false;
		this->textureColorButton->Visible = false;
		this->deepNetworkEmbButton->Visible = false;
		this->customDesignButton->Visible = false;
	}

	private: System::Void resetSubTasks() {
		this->targetImagePathLabel->Visible = false;
		this->targetImagePathButton->Visible = false;
		this->featureFilePathLabel->Visible = false;
		this->featurefilePathButton->Visible = false;
		this->NoTopMatchesLabel->Visible = false;
		this->topMatchesNumericUpDown->Visible = false;
		this->noOfBinsLabel->Visible = false;
		this->noOfBinsNumericUpDown->Visible = false;
		this->noOfBinsTexturelabel->Visible = false;
		this->noOfBinsTextureNumericUpDown->Visible = false;

		this->submitButton->Visible = false;

		this->targetImageDisplayLabel->Visible = false;
		this->targetImagePictureBox->Visible = false;
		this->topMatchesDisplayLabel->Visible = false;
		this->resultPictureBox->Visible = false;
		this->previousButton->Visible = false;
		this->nextButton->Visible = false;
		this->matchNoLabel->Visible = false;
	}

	private: System::Void generateFeatureFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resetSubTasks();
		// Show relevant buttons when "Generate Feature File" is clicked
		this->baselineMatchingButton->Visible = true;
		this->histogramMatchingButton->Visible = true;
		this->multiHistogramMatchingButton->Visible = true;
		this->textureColorButton->Visible = true;

		// Optionally, hide buttons that should not be visible now
		this->deepNetworkEmbButton->Visible = false;
		this->customDesignButton->Visible = false;

		this->taskNo = 1;
	}

	private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resetAll();
	}

	private: System::Void identifyMatchesButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resetSubTasks();
		// Show all buttons when "Identify Matches" is clicked
		this->baselineMatchingButton->Visible = true;
		this->histogramMatchingButton->Visible = true;
		this->multiHistogramMatchingButton->Visible = true;
		this->textureColorButton->Visible = true;
		this->deepNetworkEmbButton->Visible = true;
		this->customDesignButton->Visible = true;
		this->taskNo = 2;
	}
	
	private: System::Void targetImagePathButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->taskNo == 2)
		{
			if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				this->targetImagePath = this->openFileDialog1->FileName;

				this->targetImageDisplayLabel->Visible = true;
				this->targetImagePictureBox->Visible = true;

				this->targetImagePathLabel->Text = "Target Image Selected";

				// Display image in PictureBox (assuming you have a PictureBox named targetImagePictureBox)
				this->targetImagePictureBox->Image = Image::FromFile(this->targetImagePath);
				this->targetImagePictureBox->SizeMode = PictureBoxSizeMode::StretchImage;
			}
		}
		else
		{
			if (folderBrowserDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				this->imageDirectoryPath = folderBrowserDialog2->SelectedPath;
				this->targetImagePathLabel->Text = "Image Directory Selected";
			}
		}
	}

	private: System::Void featurefilePathButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->featureFilePath = this->openFileDialog2->FileName;
			this->featureFilePathLabel->Text = "Feature File Selected";
		}
	}

	private: System::Void baselineMatchingButton_Click(System::Object^ sender, System::EventArgs^ e) {
		resetSubTasks();

		// Show all buttons when "Identify Matches" is clicked
		this->targetImagePathLabel->Visible = true;
		this->targetImagePathButton->Visible = true;
	
		this->submitButton->Visible = true;
		this->subTaskNo = 1;

		if (this->taskNo == 2)
		{
			this->featureFilePathLabel->Visible = true;
			this->featurefilePathButton->Visible = true;
			this->NoTopMatchesLabel->Visible = true;
			this->topMatchesNumericUpDown->Visible = true;
			this->targetImagePathLabel->Text = "Select Target Image";
			this->targetImagePathButton->Text = "Target Image";
			this->submitButton->Text = "Submit";
		}
		else
		{
			this->targetImagePathLabel->Text = "Select Image Directory";
			this->targetImagePathButton->Text = "Image Directory";
			this->submitButton->Text = "Save";
		}
	}

	private: System::Void submitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->taskNo == 2)
		{
			switch (this->subTaskNo) {
			case 1:
				baselineMatchingTask();
				break;
			case 2:
				//histogramMatchingTask();
				break;
			case 3:
				//multiHistogramMatchingTask();
				break;
			case 4:
				//textureAndColorMatchingTask();
				break;
			case 5:
				//deepNetworkEmbeddingsTask();
				break;
			case 6:
				//combinedFeaturesCalculationTask();
				break;
			default:
				resetSubTasks();
			}
		}
		else
		{
			switch (this->subTaskNo) {
			case 1:
				baselineCalculationTask();
				break;
			case 2:
				//histogramCalculationTask();
				break;
			case 3:
				//multiHistogramCalculationTask();
				break;
			case 4:
				//textureAndColorCalculationTask();
				break;
			default:
				resetSubTasks();
			}
		}
	}

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

		*(this->topMatches) = performBaselineMatching(stdTargetImagePath, topMatches, stdFeatureFilePath);
		// Update UI or perform further actions as needed after calling performBaselineMatching	
		UpdateImageDisplay();
	}

	private: System::Void  baselineCalculationTask() {
		if (saveFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			saveFeatureFilePath = saveFileDialog2->FileName;
			
		}
		// Validate inputs
		if (System::String::IsNullOrWhiteSpace(this->imageDirectoryPath) || System::String::IsNullOrWhiteSpace(this->saveFeatureFilePath)) {
			MessageBox::Show("Please image directory");
			return;
		}

		// Convert System::String to std::string for native function call
		msclr::interop::marshal_context context;
		std::string stdImageDirectoryPath = context.marshal_as<std::string>(this->imageDirectoryPath);
		std::string stdSaveFeatureFilePath = context.marshal_as<std::string>(this->saveFeatureFilePath);

		performBaselineCalculation(stdImageDirectoryPath, stdSaveFeatureFilePath);
		
		System::String^ message = "Features computed and saved to " + saveFeatureFilePath;
		MessageBox::Show(message);
	}
	
	void UpdateImageDisplay() {
		if (this->topMatches->empty()) return;
		
		this->topMatchesDisplayLabel->Visible = true;
		this->resultPictureBox->Visible = true;
		this->previousButton->Visible = true;
		this->nextButton->Visible = true;
		this->matchNoLabel->Visible = true;

		topMatchesDisplayLabel->Text = "Top " + this->topMatches->size() + " Matches";

		// Load and display the current image		
		System::String^ imagePath = gcnew System::String((*topMatches)[currentIndex].c_str());
		this->resultPictureBox->Image = Image::FromFile(imagePath);
		this->resultPictureBox->SizeMode = PictureBoxSizeMode::StretchImage;


		// Update match number label
		matchNoLabel->Text = "Match " + (currentIndex + 1).ToString() + " of " + this->topMatches->size().ToString();

		// Enable/disable buttons
		previousButton->Enabled = currentIndex > 0;
		nextButton->Enabled = currentIndex < this->topMatches->size() - 1;
	}

	private: System::Void previousButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentIndex > 0) {
			--currentIndex;
			UpdateImageDisplay();
		}
	}

	private: System::Void nextButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentIndex < this->topMatches->size() - 1) {
			++currentIndex;
			UpdateImageDisplay();
		}
	}
private: System::Void baselineMatchingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

}
};
}
