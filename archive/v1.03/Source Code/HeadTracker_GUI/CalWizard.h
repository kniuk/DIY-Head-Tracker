#pragma once

namespace HeadTrackerGUI
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    enum CALMODE { AXISALIGNMENT, MINMAXTRACKING };

	/// <summary>
	/// Summary for CalWizard
	/// </summary>
	public ref class CalWizard : public System::Windows::Forms::Form
	{
	public:
		CalWizard(void)
		{
			InitializeComponent();
			CurrentStep = 0;
            SerialData = new float[10];

            serialbyte = 0;
            Serialindex = 0;
            
            MagXOffset = 0;
            MagYOffset = 0;
            MagZOffset = 0;

            MagX1 = 0; 
            MagX2 = 0;
            MagY1 = 0; 
            MagY2 = 0; 
            MagZ1 = 0; 
            MagZ2 = 0; 

            MagXReading = 0;
            MagYReading = 0;
            MagZReading = 0; 

            AccXOffset = 0;
            AccYOffset = 0;
            AccZOffset = 0;

            AccXMin = 0;
            AccXMax = 0;
            AccYMin = 0;
            AccYMax = 0;
            AccZMin = 0;
            AccZMax = 0;

            AccXReading = 0;
            AccYReading = 0;
            AccZReading = 0;

            CalMode = MINMAXTRACKING;
            TrackMinMax = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CalWizard()
		{
			if (components)
			    delete components;

            if ( SerialData )
                delete SerialData;
		}

    private: System::Windows::Forms::Timer^  mainUpdateTimer;
    private: System::Windows::Forms::Button^  WizardNextBtn;
    private: System::Windows::Forms::Button^  WizardPrevBtn;
    private: System::Windows::Forms::Button^  WizardCancelBtn;
    private: System::Windows::Forms::Label^  WizardInstructionsLbl;
    private: System::Windows::Forms::PictureBox^  WizardPictureBox;
    private: System::Windows::Forms::GroupBox^  WizardDataGrp;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  AccCurZLbl;
    private: System::Windows::Forms::Label^  AccCurYLbl;
    private: System::Windows::Forms::Label^  AccCurXLbl;
    private: System::Windows::Forms::Label^  MagCurZLbl;
    private: System::Windows::Forms::Label^  MagCurYLbl;
    private: System::Windows::Forms::Label^  MagCurXLbl;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  AccZOffsetLbl;
    private: System::Windows::Forms::Label^  AccYOffsetLbl;
    private: System::Windows::Forms::Label^  AccXOffsetLbl;
    private: System::Windows::Forms::Label^  MagZOffsetLbl;
    private: System::Windows::Forms::Label^  MagYOffsetLbl;
    private: System::Windows::Forms::Label^  MagXOffsetLbl;
    private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->components = (gcnew System::ComponentModel::Container());
            this->mainUpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->WizardNextBtn = (gcnew System::Windows::Forms::Button());
            this->WizardPrevBtn = (gcnew System::Windows::Forms::Button());
            this->WizardCancelBtn = (gcnew System::Windows::Forms::Button());
            this->WizardInstructionsLbl = (gcnew System::Windows::Forms::Label());
            this->WizardPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->WizardDataGrp = (gcnew System::Windows::Forms::GroupBox());
            this->AccZOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->AccYOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->AccXOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->MagZOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->MagYOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->MagXOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->AccCurZLbl = (gcnew System::Windows::Forms::Label());
            this->AccCurYLbl = (gcnew System::Windows::Forms::Label());
            this->AccCurXLbl = (gcnew System::Windows::Forms::Label());
            this->MagCurZLbl = (gcnew System::Windows::Forms::Label());
            this->MagCurYLbl = (gcnew System::Windows::Forms::Label());
            this->MagCurXLbl = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WizardPictureBox))->BeginInit();
            this->WizardDataGrp->SuspendLayout();
            this->SuspendLayout();
            // 
            // mainUpdateTimer
            // 
            this->mainUpdateTimer->Interval = 50;
            this->mainUpdateTimer->Tick += gcnew System::EventHandler(this, &CalWizard::MainUpdateTimer_Tick);
            // 
            // WizardNextBtn
            // 
            this->WizardNextBtn->Location = System::Drawing::Point(93, 443);
            this->WizardNextBtn->Name = L"WizardNextBtn";
            this->WizardNextBtn->Size = System::Drawing::Size(75, 23);
            this->WizardNextBtn->TabIndex = 0;
            this->WizardNextBtn->Text = L"Next";
            this->WizardNextBtn->UseVisualStyleBackColor = true;
            this->WizardNextBtn->Click += gcnew System::EventHandler(this, &CalWizard::NextBtn_Click);
            // 
            // WizardPrevBtn
            // 
            this->WizardPrevBtn->Location = System::Drawing::Point(12, 443);
            this->WizardPrevBtn->Name = L"WizardPrevBtn";
            this->WizardPrevBtn->Size = System::Drawing::Size(75, 23);
            this->WizardPrevBtn->TabIndex = 1;
            this->WizardPrevBtn->Text = L"Previous";
            this->WizardPrevBtn->UseVisualStyleBackColor = true;
            this->WizardPrevBtn->Click += gcnew System::EventHandler(this, &CalWizard::PreviousBtn_Click);
            // 
            // WizardCancelBtn
            // 
            this->WizardCancelBtn->Location = System::Drawing::Point(273, 443);
            this->WizardCancelBtn->Name = L"WizardCancelBtn";
            this->WizardCancelBtn->Size = System::Drawing::Size(75, 23);
            this->WizardCancelBtn->TabIndex = 2;
            this->WizardCancelBtn->Text = L"Cancel";
            this->WizardCancelBtn->UseVisualStyleBackColor = true;
            this->WizardCancelBtn->Click += gcnew System::EventHandler(this, &CalWizard::CancelBtn_Click);
            // 
            // WizardInstructionsLbl
            // 
            this->WizardInstructionsLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->WizardInstructionsLbl->Location = System::Drawing::Point(12, 9);
            this->WizardInstructionsLbl->Name = L"WizardInstructionsLbl";
            this->WizardInstructionsLbl->Size = System::Drawing::Size(336, 93);
            this->WizardInstructionsLbl->TabIndex = 3;
            this->WizardInstructionsLbl->Text = L"Instructions";
            // 
            // WizardPictureBox
            // 
            this->WizardPictureBox->Location = System::Drawing::Point(12, 105);
            this->WizardPictureBox->Name = L"WizardPictureBox";
            this->WizardPictureBox->Size = System::Drawing::Size(336, 211);
            this->WizardPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->WizardPictureBox->TabIndex = 4;
            this->WizardPictureBox->TabStop = false;
            // 
            // WizardDataGrp
            // 
            this->WizardDataGrp->Controls->Add(this->AccZOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->AccYOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->AccXOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->MagZOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->MagYOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->MagXOffsetLbl);
            this->WizardDataGrp->Controls->Add(this->label6);
            this->WizardDataGrp->Controls->Add(this->label7);
            this->WizardDataGrp->Controls->Add(this->label8);
            this->WizardDataGrp->Controls->Add(this->label5);
            this->WizardDataGrp->Controls->Add(this->label4);
            this->WizardDataGrp->Controls->Add(this->label3);
            this->WizardDataGrp->Controls->Add(this->AccCurZLbl);
            this->WizardDataGrp->Controls->Add(this->AccCurYLbl);
            this->WizardDataGrp->Controls->Add(this->AccCurXLbl);
            this->WizardDataGrp->Controls->Add(this->MagCurZLbl);
            this->WizardDataGrp->Controls->Add(this->MagCurYLbl);
            this->WizardDataGrp->Controls->Add(this->MagCurXLbl);
            this->WizardDataGrp->Controls->Add(this->label2);
            this->WizardDataGrp->Controls->Add(this->label1);
            this->WizardDataGrp->Location = System::Drawing::Point(15, 322);
            this->WizardDataGrp->Name = L"WizardDataGrp";
            this->WizardDataGrp->Size = System::Drawing::Size(333, 113);
            this->WizardDataGrp->TabIndex = 5;
            this->WizardDataGrp->TabStop = false;
            this->WizardDataGrp->Text = L"Calibration Data";
            // 
            // AccZOffsetLbl
            // 
            this->AccZOffsetLbl->AutoSize = true;
            this->AccZOffsetLbl->Location = System::Drawing::Point(229, 87);
            this->AccZOffsetLbl->Name = L"AccZOffsetLbl";
            this->AccZOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->AccZOffsetLbl->TabIndex = 19;
            this->AccZOffsetLbl->Text = L"0";
            // 
            // AccYOffsetLbl
            // 
            this->AccYOffsetLbl->AutoSize = true;
            this->AccYOffsetLbl->Location = System::Drawing::Point(229, 62);
            this->AccYOffsetLbl->Name = L"AccYOffsetLbl";
            this->AccYOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->AccYOffsetLbl->TabIndex = 18;
            this->AccYOffsetLbl->Text = L"0";
            // 
            // AccXOffsetLbl
            // 
            this->AccXOffsetLbl->AutoSize = true;
            this->AccXOffsetLbl->Location = System::Drawing::Point(229, 38);
            this->AccXOffsetLbl->Name = L"AccXOffsetLbl";
            this->AccXOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->AccXOffsetLbl->TabIndex = 17;
            this->AccXOffsetLbl->Text = L"0";
            // 
            // MagZOffsetLbl
            // 
            this->MagZOffsetLbl->AutoSize = true;
            this->MagZOffsetLbl->Location = System::Drawing::Point(64, 87);
            this->MagZOffsetLbl->Name = L"MagZOffsetLbl";
            this->MagZOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->MagZOffsetLbl->TabIndex = 16;
            this->MagZOffsetLbl->Text = L"0";
            // 
            // MagYOffsetLbl
            // 
            this->MagYOffsetLbl->AutoSize = true;
            this->MagYOffsetLbl->Location = System::Drawing::Point(64, 62);
            this->MagYOffsetLbl->Name = L"MagYOffsetLbl";
            this->MagYOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->MagYOffsetLbl->TabIndex = 15;
            this->MagYOffsetLbl->Text = L"0";
            // 
            // MagXOffsetLbl
            // 
            this->MagXOffsetLbl->AutoSize = true;
            this->MagXOffsetLbl->Location = System::Drawing::Point(64, 38);
            this->MagXOffsetLbl->Name = L"MagXOffsetLbl";
            this->MagXOffsetLbl->Size = System::Drawing::Size(13, 13);
            this->MagXOffsetLbl->TabIndex = 14;
            this->MagXOffsetLbl->Text = L"0";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(175, 87);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(48, 13);
            this->label6->TabIndex = 13;
            this->label6->Text = L"Z Offset:";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(175, 62);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(48, 13);
            this->label7->TabIndex = 12;
            this->label7->Text = L"Y Offset:";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(175, 38);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(48, 13);
            this->label8->TabIndex = 11;
            this->label8->Text = L"X Offset:";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(10, 87);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(48, 13);
            this->label5->TabIndex = 10;
            this->label5->Text = L"Z Offset:";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(10, 62);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(48, 13);
            this->label4->TabIndex = 9;
            this->label4->Text = L"Y Offset:";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(10, 38);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(48, 13);
            this->label3->TabIndex = 8;
            this->label3->Text = L"X Offset:";
            // 
            // AccCurZLbl
            // 
            this->AccCurZLbl->AutoSize = true;
            this->AccCurZLbl->Location = System::Drawing::Point(305, 16);
            this->AccCurZLbl->Name = L"AccCurZLbl";
            this->AccCurZLbl->Size = System::Drawing::Size(13, 13);
            this->AccCurZLbl->TabIndex = 7;
            this->AccCurZLbl->Text = L"0";
            // 
            // AccCurYLbl
            // 
            this->AccCurYLbl->AutoSize = true;
            this->AccCurYLbl->Location = System::Drawing::Point(277, 16);
            this->AccCurYLbl->Name = L"AccCurYLbl";
            this->AccCurYLbl->Size = System::Drawing::Size(13, 13);
            this->AccCurYLbl->TabIndex = 6;
            this->AccCurYLbl->Text = L"0";
            // 
            // AccCurXLbl
            // 
            this->AccCurXLbl->AutoSize = true;
            this->AccCurXLbl->Location = System::Drawing::Point(251, 16);
            this->AccCurXLbl->Name = L"AccCurXLbl";
            this->AccCurXLbl->Size = System::Drawing::Size(13, 13);
            this->AccCurXLbl->TabIndex = 5;
            this->AccCurXLbl->Text = L"0";
            // 
            // MagCurZLbl
            // 
            this->MagCurZLbl->AutoSize = true;
            this->MagCurZLbl->Location = System::Drawing::Point(140, 16);
            this->MagCurZLbl->Name = L"MagCurZLbl";
            this->MagCurZLbl->Size = System::Drawing::Size(13, 13);
            this->MagCurZLbl->TabIndex = 4;
            this->MagCurZLbl->Text = L"0";
            // 
            // MagCurYLbl
            // 
            this->MagCurYLbl->AutoSize = true;
            this->MagCurYLbl->Location = System::Drawing::Point(109, 16);
            this->MagCurYLbl->Name = L"MagCurYLbl";
            this->MagCurYLbl->Size = System::Drawing::Size(13, 13);
            this->MagCurYLbl->TabIndex = 3;
            this->MagCurYLbl->Text = L"0";
            // 
            // MagCurXLbl
            // 
            this->MagCurXLbl->AutoSize = true;
            this->MagCurXLbl->Location = System::Drawing::Point(78, 16);
            this->MagCurXLbl->Name = L"MagCurXLbl";
            this->MagCurXLbl->Size = System::Drawing::Size(13, 13);
            this->MagCurXLbl->TabIndex = 2;
            this->MagCurXLbl->Text = L"0";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label2->Location = System::Drawing::Point(175, 16);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(70, 13);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Accel Data";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(10, 16);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(62, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Mag Data";
            // 
            // CalWizard
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(357, 475);
            this->Controls->Add(this->WizardDataGrp);
            this->Controls->Add(this->WizardPictureBox);
            this->Controls->Add(this->WizardInstructionsLbl);
            this->Controls->Add(this->WizardCancelBtn);
            this->Controls->Add(this->WizardPrevBtn);
            this->Controls->Add(this->WizardNextBtn);
            this->Name = L"CalWizard";
            this->Text = L"Headtracker Calibration Wizard";
            this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &CalWizard::CalWizard_OnClose);
            this->Load += gcnew System::EventHandler(this, &CalWizard::CalWizard_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WizardPictureBox))->EndInit();
            this->WizardDataGrp->ResumeLayout(false);
            this->WizardDataGrp->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion

public: // Methods

    System::Void Begin(CALMODE mode);

private: // Vars

    System::Resources::ResourceManager^ rm;
    int CurrentStep;    // The current wizard page (0 = intro)

    int serialbyte;
    float* SerialData;
    int Serialindex;
    
    // Mag
    //
    int MagXOffset;
    int MagYOffset;
    int MagZOffset;

    int MagX1; 
    int MagX2;
    int MagY1; 
    int MagY2; 
    int MagZ1; 
    int MagZ2; 

    int MagXReading;
    int MagYReading;
    int MagZReading;

    // Accel
    //
    int AccXOffset;
    int AccYOffset;
    int AccZOffset;

    int AccXMin;
    int AccXMax;
    int AccYMin;
    int AccYMax;
    int AccZMin;
    int AccZMax;

    int AccXReading;
    int AccYReading;
    int AccZReading; 

    CALMODE CalMode;
    bool TrackMinMax;

private:

    System::Void CalWizard_Load(System::Object^  sender, System::EventArgs^  e);
    System::Void CalWizard_OnClose(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
    System::Void MainUpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void PreviousBtn_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void NextBtn_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void CancelBtn_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void UpdateCalc();
    System::Void ZeroMinMaxTracking();
    System::Void SetupUIForStep(int Step);
    System::Void CompleteStep(int Step);
    System::Void SetupAxisCalStepUI(int Step);
    System::Void SetupTrackingCalStepUI(int Step);
    System::Void CompleteAxisCalStep(int Step);
    System::Void CompleteTrackingCalStep(int Step);
};

} // namespace
