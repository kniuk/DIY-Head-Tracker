#pragma once

namespace PPM_expander_and_headtracker
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AccelCalibrateForm
	/// </summary>
	public ref class AccelCalibrateForm : public System::Windows::Forms::Form
	{
	public:
		AccelCalibrateForm()
		{
			InitializeComponent();
			
            SerialData = new float[5];

            cal0Min = 999;
            cal0Max = -999;
            cal1Min = 999;
            cal1Max = -999;
            cal2Min = 999;
            cal2Max = -999;
            serialbyte = 0;
            headtracker_active = 0;
            Serialindex = 0;
            PointIndex = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AccelCalibrateForm()
		{
			if (components)
			{
				delete components;
			}

            if ( SerialData )
                delete SerialData;
		}

    private: System::Windows::Forms::Timer^  mainUpdateTimer;
    private: System::Windows::Forms::Label^  zMin;
    private: System::Windows::Forms::Button^  SetZMinButton;
    private: System::Windows::Forms::Button^  SetYMinButton;
    private: System::Windows::Forms::Button^  SetXMinButton;
    private: System::Windows::Forms::Button^  ResetCalButton;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Button^  SaveCalButton;
    private: System::Windows::Forms::Label^  label31;
    private: System::Windows::Forms::Label^  XOffsetLbl;
    private: System::Windows::Forms::Label^  label32;
    private: System::Windows::Forms::Label^  YOffsetLbl;
    private: System::Windows::Forms::Label^  label33;
    private: System::Windows::Forms::Label^  ZOffsetLbl;
    private: System::Windows::Forms::Label^  label24;
    private: System::Windows::Forms::Label^  label17;
    private: System::Windows::Forms::Label^  label16;
    private: System::Windows::Forms::Button^  SetZMaxButton;
    private: System::Windows::Forms::Button^  SetYMaxButton;
    private: System::Windows::Forms::Label^  zMax;
    private: System::Windows::Forms::Label^  yMin;
    private: System::Windows::Forms::Label^  yMax;
    private: System::Windows::Forms::Label^  xMin;
    private: System::Windows::Forms::Label^  xMax;
    private: System::Windows::Forms::Button^  SetXMaxButton;
    private: System::Windows::Forms::Button^  StopCalButton;
    private: System::Windows::Forms::Button^  ClearPlotButton;
    private: System::Windows::Forms::Button^  StartCalButton;
    private: System::Windows::Forms::DataVisualization::Charting::Chart^  DataChart;
    private: System::Windows::Forms::Label^  XCurValLbl;
    private: System::Windows::Forms::Label^  YCurValLbl;
    private: System::Windows::Forms::Label^  ZCurValLbl;
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
            System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
            System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->mainUpdateTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->zMin = (gcnew System::Windows::Forms::Label());
            this->SetZMinButton = (gcnew System::Windows::Forms::Button());
            this->SetYMinButton = (gcnew System::Windows::Forms::Button());
            this->SetXMinButton = (gcnew System::Windows::Forms::Button());
            this->ResetCalButton = (gcnew System::Windows::Forms::Button());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->SaveCalButton = (gcnew System::Windows::Forms::Button());
            this->label31 = (gcnew System::Windows::Forms::Label());
            this->XOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label32 = (gcnew System::Windows::Forms::Label());
            this->YOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label33 = (gcnew System::Windows::Forms::Label());
            this->ZOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->SetZMaxButton = (gcnew System::Windows::Forms::Button());
            this->SetYMaxButton = (gcnew System::Windows::Forms::Button());
            this->zMax = (gcnew System::Windows::Forms::Label());
            this->yMin = (gcnew System::Windows::Forms::Label());
            this->yMax = (gcnew System::Windows::Forms::Label());
            this->xMin = (gcnew System::Windows::Forms::Label());
            this->xMax = (gcnew System::Windows::Forms::Label());
            this->SetXMaxButton = (gcnew System::Windows::Forms::Button());
            this->StopCalButton = (gcnew System::Windows::Forms::Button());
            this->ClearPlotButton = (gcnew System::Windows::Forms::Button());
            this->StartCalButton = (gcnew System::Windows::Forms::Button());
            this->DataChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            this->XCurValLbl = (gcnew System::Windows::Forms::Label());
            this->YCurValLbl = (gcnew System::Windows::Forms::Label());
            this->ZCurValLbl = (gcnew System::Windows::Forms::Label());
            this->groupBox1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataChart))->BeginInit();
            this->SuspendLayout();
            // 
            // mainUpdateTimer
            // 
            this->mainUpdateTimer->Enabled = true;
            this->mainUpdateTimer->Interval = 50;
            this->mainUpdateTimer->Tick += gcnew System::EventHandler(this, &AccelCalibrateForm::MainUpdateTimer_Tick);
            // 
            // zMin
            // 
            this->zMin->AutoSize = true;
            this->zMin->Location = System::Drawing::Point(336, 155);
            this->zMin->Name = L"zMin";
            this->zMin->Size = System::Drawing::Size(13, 13);
            this->zMin->TabIndex = 208;
            this->zMin->Text = L"0";
            // 
            // SetZMinButton
            // 
            this->SetZMinButton->Location = System::Drawing::Point(255, 150);
            this->SetZMinButton->Name = L"SetZMinButton";
            this->SetZMinButton->Size = System::Drawing::Size(75, 23);
            this->SetZMinButton->TabIndex = 207;
            this->SetZMinButton->Text = L"Set Z-min";
            this->SetZMinButton->UseVisualStyleBackColor = true;
            this->SetZMinButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetZMinBtnClicked);
            // 
            // SetYMinButton
            // 
            this->SetYMinButton->Location = System::Drawing::Point(135, 150);
            this->SetYMinButton->Name = L"SetYMinButton";
            this->SetYMinButton->Size = System::Drawing::Size(75, 23);
            this->SetYMinButton->TabIndex = 206;
            this->SetYMinButton->Text = L"Set Y-min";
            this->SetYMinButton->UseVisualStyleBackColor = true;
            this->SetYMinButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetYMinBtnClicked);
            // 
            // SetXMinButton
            // 
            this->SetXMinButton->Location = System::Drawing::Point(12, 150);
            this->SetXMinButton->Name = L"SetXMinButton";
            this->SetXMinButton->Size = System::Drawing::Size(75, 23);
            this->SetXMinButton->TabIndex = 205;
            this->SetXMinButton->Text = L"Set X-min";
            this->SetXMinButton->UseVisualStyleBackColor = true;
            this->SetXMinButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetXMinBtnClicked);
            // 
            // ResetCalButton
            // 
            this->ResetCalButton->Location = System::Drawing::Point(216, 12);
            this->ResetCalButton->Name = L"ResetCalButton";
            this->ResetCalButton->Size = System::Drawing::Size(93, 35);
            this->ResetCalButton->TabIndex = 204;
            this->ResetCalButton->Text = L"Reset Calibration";
            this->ResetCalButton->UseVisualStyleBackColor = true;
            this->ResetCalButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::ResetCalBtnClicked);
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->SaveCalButton);
            this->groupBox1->Controls->Add(this->label31);
            this->groupBox1->Controls->Add(this->XOffsetLbl);
            this->groupBox1->Controls->Add(this->label32);
            this->groupBox1->Controls->Add(this->YOffsetLbl);
            this->groupBox1->Controls->Add(this->label33);
            this->groupBox1->Controls->Add(this->ZOffsetLbl);
            this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->groupBox1->Location = System::Drawing::Point(366, 12);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(126, 134);
            this->groupBox1->TabIndex = 203;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Result";
            // 
            // SaveCalButton
            // 
            this->SaveCalButton->Location = System::Drawing::Point(6, 99);
            this->SaveCalButton->Name = L"SaveCalButton";
            this->SaveCalButton->Size = System::Drawing::Size(75, 23);
            this->SaveCalButton->TabIndex = 183;
            this->SaveCalButton->Text = L"Save settings";
            this->SaveCalButton->UseVisualStyleBackColor = true;
            this->SaveCalButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SaveBtnClicked);
            // 
            // label31
            // 
            this->label31->AutoSize = true;
            this->label31->Location = System::Drawing::Point(6, 73);
            this->label31->Name = L"label31";
            this->label31->Size = System::Drawing::Size(55, 15);
            this->label31->TabIndex = 182;
            this->label31->Text = L"Z-offset";
            // 
            // XOffsetLbl
            // 
            this->XOffsetLbl->AutoSize = true;
            this->XOffsetLbl->Location = System::Drawing::Point(97, 28);
            this->XOffsetLbl->Name = L"XOffsetLbl";
            this->XOffsetLbl->Size = System::Drawing::Size(15, 15);
            this->XOffsetLbl->TabIndex = 154;
            this->XOffsetLbl->Text = L"0";
            // 
            // label32
            // 
            this->label32->AutoSize = true;
            this->label32->Location = System::Drawing::Point(6, 51);
            this->label32->Name = L"label32";
            this->label32->Size = System::Drawing::Size(55, 15);
            this->label32->TabIndex = 181;
            this->label32->Text = L"Y-offset";
            // 
            // YOffsetLbl
            // 
            this->YOffsetLbl->AutoSize = true;
            this->YOffsetLbl->Location = System::Drawing::Point(97, 54);
            this->YOffsetLbl->Name = L"YOffsetLbl";
            this->YOffsetLbl->Size = System::Drawing::Size(15, 15);
            this->YOffsetLbl->TabIndex = 155;
            this->YOffsetLbl->Text = L"0";
            // 
            // label33
            // 
            this->label33->AutoSize = true;
            this->label33->Location = System::Drawing::Point(6, 28);
            this->label33->Name = L"label33";
            this->label33->Size = System::Drawing::Size(56, 15);
            this->label33->TabIndex = 180;
            this->label33->Text = L"X-offset";
            // 
            // ZOffsetLbl
            // 
            this->ZOffsetLbl->AutoSize = true;
            this->ZOffsetLbl->Location = System::Drawing::Point(97, 76);
            this->ZOffsetLbl->Name = L"ZOffsetLbl";
            this->ZOffsetLbl->Size = System::Drawing::Size(15, 15);
            this->ZOffsetLbl->TabIndex = 157;
            this->ZOffsetLbl->Text = L"0";
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label24->Location = System::Drawing::Point(252, 74);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(91, 16);
            this->label24->TabIndex = 202;
            this->label24->Text = L"Pan (Z-axis)";
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label17->Location = System::Drawing::Point(132, 74);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(93, 16);
            this->label17->TabIndex = 201;
            this->label17->Text = L"Roll (Y-axis)";
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label16->Location = System::Drawing::Point(12, 74);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(86, 16);
            this->label16->TabIndex = 200;
            this->label16->Text = L"Tilt (X-axis)";
            // 
            // SetZMaxButton
            // 
            this->SetZMaxButton->Location = System::Drawing::Point(255, 112);
            this->SetZMaxButton->Name = L"SetZMaxButton";
            this->SetZMaxButton->Size = System::Drawing::Size(75, 23);
            this->SetZMaxButton->TabIndex = 199;
            this->SetZMaxButton->Text = L"Set Z-max";
            this->SetZMaxButton->UseVisualStyleBackColor = true;
            this->SetZMaxButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetZMaxBtnClicked);
            // 
            // SetYMaxButton
            // 
            this->SetYMaxButton->Location = System::Drawing::Point(135, 112);
            this->SetYMaxButton->Name = L"SetYMaxButton";
            this->SetYMaxButton->Size = System::Drawing::Size(75, 23);
            this->SetYMaxButton->TabIndex = 198;
            this->SetYMaxButton->Text = L"Set Y-max";
            this->SetYMaxButton->UseVisualStyleBackColor = true;
            this->SetYMaxButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetYMaxBtnClicked);
            // 
            // zMax
            // 
            this->zMax->AutoSize = true;
            this->zMax->Location = System::Drawing::Point(336, 117);
            this->zMax->Name = L"zMax";
            this->zMax->Size = System::Drawing::Size(13, 13);
            this->zMax->TabIndex = 197;
            this->zMax->Text = L"0";
            // 
            // yMin
            // 
            this->yMin->AutoSize = true;
            this->yMin->Location = System::Drawing::Point(216, 155);
            this->yMin->Name = L"yMin";
            this->yMin->Size = System::Drawing::Size(13, 13);
            this->yMin->TabIndex = 196;
            this->yMin->Text = L"0";
            // 
            // yMax
            // 
            this->yMax->AutoSize = true;
            this->yMax->Location = System::Drawing::Point(216, 117);
            this->yMax->Name = L"yMax";
            this->yMax->Size = System::Drawing::Size(13, 13);
            this->yMax->TabIndex = 195;
            this->yMax->Text = L"0";
            // 
            // xMin
            // 
            this->xMin->AutoSize = true;
            this->xMin->Location = System::Drawing::Point(93, 155);
            this->xMin->Name = L"xMin";
            this->xMin->Size = System::Drawing::Size(13, 13);
            this->xMin->TabIndex = 194;
            this->xMin->Text = L"0";
            // 
            // xMax
            // 
            this->xMax->AutoSize = true;
            this->xMax->Location = System::Drawing::Point(93, 117);
            this->xMax->Name = L"xMax";
            this->xMax->Size = System::Drawing::Size(13, 13);
            this->xMax->TabIndex = 193;
            this->xMax->Text = L"0";
            // 
            // SetXMaxButton
            // 
            this->SetXMaxButton->Location = System::Drawing::Point(12, 112);
            this->SetXMaxButton->Name = L"SetXMaxButton";
            this->SetXMaxButton->Size = System::Drawing::Size(75, 23);
            this->SetXMaxButton->TabIndex = 192;
            this->SetXMaxButton->Text = L"Set X-max";
            this->SetXMaxButton->UseVisualStyleBackColor = true;
            this->SetXMaxButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::SetXMaxBtnClicked);
            // 
            // StopCalButton
            // 
            this->StopCalButton->Location = System::Drawing::Point(12, 41);
            this->StopCalButton->Name = L"StopCalButton";
            this->StopCalButton->Size = System::Drawing::Size(117, 23);
            this->StopCalButton->TabIndex = 191;
            this->StopCalButton->Text = L"Stop Calibration";
            this->StopCalButton->UseVisualStyleBackColor = true;
            this->StopCalButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::StopBtnClicked);
            // 
            // ClearPlotButton
            // 
            this->ClearPlotButton->Location = System::Drawing::Point(417, 150);
            this->ClearPlotButton->Name = L"ClearPlotButton";
            this->ClearPlotButton->Size = System::Drawing::Size(75, 23);
            this->ClearPlotButton->TabIndex = 190;
            this->ClearPlotButton->Text = L"Clear plot";
            this->ClearPlotButton->UseVisualStyleBackColor = true;
            this->ClearPlotButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::ClearPlotBtnClicked);
            // 
            // StartCalButton
            // 
            this->StartCalButton->Location = System::Drawing::Point(12, 12);
            this->StartCalButton->Name = L"StartCalButton";
            this->StartCalButton->Size = System::Drawing::Size(117, 23);
            this->StartCalButton->TabIndex = 189;
            this->StartCalButton->Text = L"Start Calibration";
            this->StartCalButton->UseVisualStyleBackColor = true;
            this->StartCalButton->Click += gcnew System::EventHandler(this, &AccelCalibrateForm::StartBtnClicked);
            // 
            // DataChart
            // 
            this->DataChart->BackColor = System::Drawing::Color::Transparent;
            chartArea1->BackColor = System::Drawing::Color::Transparent;
            chartArea1->BackImageTransparentColor = System::Drawing::Color::Red;
            chartArea1->BackSecondaryColor = System::Drawing::Color::Black;
            chartArea1->Name = L"ChartArea1";
            chartArea1->ShadowColor = System::Drawing::Color::Fuchsia;
            this->DataChart->ChartAreas->Add(chartArea1);
            legend1->Enabled = false;
            legend1->Name = L"Legend1";
            this->DataChart->Legends->Add(legend1);
            this->DataChart->Location = System::Drawing::Point(-30, 179);
            this->DataChart->Name = L"DataChart";
            series1->ChartArea = L"ChartArea1";
            series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series1->Legend = L"Legend1";
            series1->Name = L"Series1";
            series2->ChartArea = L"ChartArea1";
            series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series2->Legend = L"Legend1";
            series2->LegendText = L"Pan";
            series2->Name = L"Series2";
            series3->ChartArea = L"ChartArea1";
            series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series3->Legend = L"Legend1";
            series3->Name = L"Series3";
            series4->ChartArea = L"ChartArea1";
            series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series4->Legend = L"Legend1";
            series4->Name = L"Series4";
            this->DataChart->Series->Add(series1);
            this->DataChart->Series->Add(series2);
            this->DataChart->Series->Add(series3);
            this->DataChart->Series->Add(series4);
            this->DataChart->Size = System::Drawing::Size(556, 229);
            this->DataChart->TabIndex = 188;
            this->DataChart->Text = L"chart1";
            // 
            // XCurValLbl
            // 
            this->XCurValLbl->AutoSize = true;
            this->XCurValLbl->Location = System::Drawing::Point(104, 77);
            this->XCurValLbl->Name = L"XCurValLbl";
            this->XCurValLbl->Size = System::Drawing::Size(13, 13);
            this->XCurValLbl->TabIndex = 209;
            this->XCurValLbl->Text = L"0";
            // 
            // YCurValLbl
            // 
            this->YCurValLbl->AutoSize = true;
            this->YCurValLbl->Location = System::Drawing::Point(231, 77);
            this->YCurValLbl->Name = L"YCurValLbl";
            this->YCurValLbl->Size = System::Drawing::Size(13, 13);
            this->YCurValLbl->TabIndex = 210;
            this->YCurValLbl->Text = L"0";
            // 
            // ZCurValLbl
            // 
            this->ZCurValLbl->AutoSize = true;
            this->ZCurValLbl->Location = System::Drawing::Point(349, 77);
            this->ZCurValLbl->Name = L"ZCurValLbl";
            this->ZCurValLbl->Size = System::Drawing::Size(13, 13);
            this->ZCurValLbl->TabIndex = 211;
            this->ZCurValLbl->Text = L"0";
            // 
            // AccelCalibrateForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(514, 411);
            this->Controls->Add(this->ZCurValLbl);
            this->Controls->Add(this->YCurValLbl);
            this->Controls->Add(this->XCurValLbl);
            this->Controls->Add(this->zMin);
            this->Controls->Add(this->SetZMinButton);
            this->Controls->Add(this->SetYMinButton);
            this->Controls->Add(this->SetXMinButton);
            this->Controls->Add(this->ResetCalButton);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label24);
            this->Controls->Add(this->label17);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->SetZMaxButton);
            this->Controls->Add(this->SetYMaxButton);
            this->Controls->Add(this->zMax);
            this->Controls->Add(this->yMin);
            this->Controls->Add(this->yMax);
            this->Controls->Add(this->xMin);
            this->Controls->Add(this->xMax);
            this->Controls->Add(this->SetXMaxButton);
            this->Controls->Add(this->StopCalButton);
            this->Controls->Add(this->ClearPlotButton);
            this->Controls->Add(this->StartCalButton);
            this->Controls->Add(this->DataChart);
            this->Name = L"AccelCalibrateForm";
            this->Text = L"Accelerometer Calibration";
            this->Load += gcnew System::EventHandler(this, &AccelCalibrateForm::AccelCalibrate_Load);
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataChart))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

private: // variables

    int serialbyte;
    unsigned char headtracker_active;
    
    int xoffset;
    int yoffset;
    int zoffset;

    int xreading;
    int yreading;
    int zreading; 

    int cal0Min;
    int cal0Max;
    int cal1Min;
    int cal1Max;
    int cal2Min;
    int cal2Max;

    float* SerialData;
    int Serialindex;

    long PointIndex;

    // Methods
    private: System::Void UpdateCalc();
    private: System::Void MainUpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    private: System::Void AccelCalibrate_Load(System::Object^  sender, System::EventArgs^  e);
    private: System::Void StartBtnClicked(System::Object^  sender, System::EventArgs^  e);
    private: System::Void ClearPlotBtnClicked(System::Object^  sender, System::EventArgs^  e);
    private: System::Void ResetCalBtnClicked(System::Object^  sender, System::EventArgs^  e);
    private: System::Void SetXMaxBtnClicked(System::Object^  sender, System::EventArgs^  e);
    private: System::Void SetXMinBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void SetYMaxBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void SetYMinBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void SetZMaxBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void SetZMinBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void SaveBtnClicked(System::Object^  sender, System::EventArgs^  e); 
    private: System::Void StopBtnClicked(System::Object^  sender, System::EventArgs^  e);
}; // Class

} // Namespace
