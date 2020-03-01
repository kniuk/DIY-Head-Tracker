#pragma once

namespace PPM_expander_and_headtracker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MagCalibrate
	/// </summary>
	public ref class MagCalibrate : public System::Windows::Forms::Form
	{
	public:
		MagCalibrate(void)
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
		~MagCalibrate()
		{
			if (components)
			{
				delete components;
			}
        
            if ( SerialData )
                delete SerialData;
		}

    private: System::Windows::Forms::Timer^  updateTimer;
    private: System::Windows::Forms::Button^  ResetCalBtn;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Button^  SaveCalBtn;
    private: System::Windows::Forms::Label^  label31;
    private: System::Windows::Forms::Label^  XOffsetLbl;
    private: System::Windows::Forms::Label^  label32;
    private: System::Windows::Forms::Label^  YOffsetLbl;
    private: System::Windows::Forms::Label^  label33;
    private: System::Windows::Forms::Label^  ZOffsetLbl;
    private: System::Windows::Forms::Label^  label30;
    private: System::Windows::Forms::Label^  label29;
    private: System::Windows::Forms::Label^  label27;
    private: System::Windows::Forms::Label^  label28;
    private: System::Windows::Forms::Label^  label26;
    private: System::Windows::Forms::Label^  label25;
    private: System::Windows::Forms::Label^  label24;
    private: System::Windows::Forms::Label^  label17;
    private: System::Windows::Forms::Label^  label16;
    private: System::Windows::Forms::Button^  button7;
    private: System::Windows::Forms::Button^  button6;
    private: System::Windows::Forms::Button^  button5;
    private: System::Windows::Forms::Button^  SetStageThreeBtn;
    private: System::Windows::Forms::Button^  SetStageTwoBtn;
    private: System::Windows::Forms::Label^  StageThreeZLbl;
    private: System::Windows::Forms::Label^  StageTwoZLbl;
    private: System::Windows::Forms::Label^  StageTwoYLbl;
    private: System::Windows::Forms::Label^  StageTwoXLbl;
    private: System::Windows::Forms::Label^  StageOneYLbl;
    private: System::Windows::Forms::Label^  StageOneXLbl;
    private: System::Windows::Forms::Button^  SetStageOneBtn;
    private: System::Windows::Forms::Button^  StopCalBtn;
    private: System::Windows::Forms::Button^  ClearPlotBtn;
    private: System::Windows::Forms::Button^  StartCalBtn;
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
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MagCalibrate::typeid));
            System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
            System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->updateTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->ResetCalBtn = (gcnew System::Windows::Forms::Button());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->SaveCalBtn = (gcnew System::Windows::Forms::Button());
            this->label31 = (gcnew System::Windows::Forms::Label());
            this->XOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label32 = (gcnew System::Windows::Forms::Label());
            this->YOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label33 = (gcnew System::Windows::Forms::Label());
            this->ZOffsetLbl = (gcnew System::Windows::Forms::Label());
            this->label30 = (gcnew System::Windows::Forms::Label());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->label26 = (gcnew System::Windows::Forms::Label());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->button7 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->SetStageThreeBtn = (gcnew System::Windows::Forms::Button());
            this->SetStageTwoBtn = (gcnew System::Windows::Forms::Button());
            this->StageThreeZLbl = (gcnew System::Windows::Forms::Label());
            this->StageTwoZLbl = (gcnew System::Windows::Forms::Label());
            this->StageTwoYLbl = (gcnew System::Windows::Forms::Label());
            this->StageTwoXLbl = (gcnew System::Windows::Forms::Label());
            this->StageOneYLbl = (gcnew System::Windows::Forms::Label());
            this->StageOneXLbl = (gcnew System::Windows::Forms::Label());
            this->SetStageOneBtn = (gcnew System::Windows::Forms::Button());
            this->StopCalBtn = (gcnew System::Windows::Forms::Button());
            this->ClearPlotBtn = (gcnew System::Windows::Forms::Button());
            this->StartCalBtn = (gcnew System::Windows::Forms::Button());
            this->DataChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            this->XCurValLbl = (gcnew System::Windows::Forms::Label());
            this->YCurValLbl = (gcnew System::Windows::Forms::Label());
            this->ZCurValLbl = (gcnew System::Windows::Forms::Label());
            this->groupBox1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataChart))->BeginInit();
            this->SuspendLayout();
            // 
            // updateTimer
            // 
            this->updateTimer->Enabled = true;
            this->updateTimer->Interval = 50;
            this->updateTimer->Tick += gcnew System::EventHandler(this, &MagCalibrate::UpdateTimer_Tick);
            // 
            // ResetCalBtn
            // 
            this->ResetCalBtn->Location = System::Drawing::Point(659, 199);
            this->ResetCalBtn->Name = L"ResetCalBtn";
            this->ResetCalBtn->Size = System::Drawing::Size(93, 35);
            this->ResetCalBtn->TabIndex = 207;
            this->ResetCalBtn->Text = L"Reset Calibration";
            this->ResetCalBtn->UseVisualStyleBackColor = true;
            this->ResetCalBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::ResetCal_Click);
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->SaveCalBtn);
            this->groupBox1->Controls->Add(this->label31);
            this->groupBox1->Controls->Add(this->XOffsetLbl);
            this->groupBox1->Controls->Add(this->label32);
            this->groupBox1->Controls->Add(this->YOffsetLbl);
            this->groupBox1->Controls->Add(this->label33);
            this->groupBox1->Controls->Add(this->ZOffsetLbl);
            this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->groupBox1->Location = System::Drawing::Point(650, 45);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(137, 145);
            this->groupBox1->TabIndex = 206;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Result";
            // 
            // SaveCalBtn
            // 
            this->SaveCalBtn->Location = System::Drawing::Point(9, 105);
            this->SaveCalBtn->Name = L"SaveCalBtn";
            this->SaveCalBtn->Size = System::Drawing::Size(75, 23);
            this->SaveCalBtn->TabIndex = 183;
            this->SaveCalBtn->Text = L"Save settings";
            this->SaveCalBtn->UseVisualStyleBackColor = true;
            this->SaveCalBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::SaveCal_Click);
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
            // label30
            // 
            this->label30->AutoSize = true;
            this->label30->Location = System::Drawing::Point(440, 218);
            this->label30->Name = L"label30";
            this->label30->Size = System::Drawing::Size(35, 13);
            this->label30->TabIndex = 205;
            this->label30->Text = L"Z-axis";
            // 
            // label29
            // 
            this->label29->AutoSize = true;
            this->label29->Location = System::Drawing::Point(217, 266);
            this->label29->Name = L"label29";
            this->label29->Size = System::Drawing::Size(35, 13);
            this->label29->TabIndex = 204;
            this->label29->Text = L"Z-axis";
            // 
            // label27
            // 
            this->label27->AutoSize = true;
            this->label27->Location = System::Drawing::Point(217, 244);
            this->label27->Name = L"label27";
            this->label27->Size = System::Drawing::Size(35, 13);
            this->label27->TabIndex = 203;
            this->label27->Text = L"Y-axis";
            // 
            // label28
            // 
            this->label28->AutoSize = true;
            this->label28->Location = System::Drawing::Point(217, 221);
            this->label28->Name = L"label28";
            this->label28->Size = System::Drawing::Size(38, 13);
            this->label28->TabIndex = 202;
            this->label28->Text = L"X-axis:";
            // 
            // label26
            // 
            this->label26->AutoSize = true;
            this->label26->Location = System::Drawing::Point(7, 244);
            this->label26->Name = L"label26";
            this->label26->Size = System::Drawing::Size(35, 13);
            this->label26->TabIndex = 201;
            this->label26->Text = L"Y-axis";
            // 
            // label25
            // 
            this->label25->AutoSize = true;
            this->label25->Location = System::Drawing::Point(5, 218);
            this->label25->Name = L"label25";
            this->label25->Size = System::Drawing::Size(38, 13);
            this->label25->TabIndex = 200;
            this->label25->Text = L"X-axis:";
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label24->Location = System::Drawing::Point(440, 42);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(98, 16);
            this->label24->TabIndex = 199;
            this->label24->Text = L"Upside down";
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label17->Location = System::Drawing::Point(217, 43);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(130, 16);
            this->label17->TabIndex = 198;
            this->label17->Text = L"Turn 180-degrees";
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
                static_cast<System::Byte>(0)));
            this->label16->Location = System::Drawing::Point(5, 45);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(40, 16);
            this->label16->TabIndex = 197;
            this->label16->Text = L"Start";
            // 
            // button7
            // 
            this->button7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button7.BackgroundImage")));
            this->button7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->button7->Location = System::Drawing::Point(443, 61);
            this->button7->Name = L"button7";
            this->button7->Size = System::Drawing::Size(191, 121);
            this->button7->TabIndex = 196;
            this->button7->UseVisualStyleBackColor = true;
            // 
            // button6
            // 
            this->button6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button6.BackgroundImage")));
            this->button6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->button6->Location = System::Drawing::Point(220, 62);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(191, 121);
            this->button6->TabIndex = 195;
            this->button6->UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this->button5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button5.BackgroundImage")));
            this->button5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->button5->Location = System::Drawing::Point(7, 61);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(191, 121);
            this->button5->TabIndex = 194;
            this->button5->UseVisualStyleBackColor = true;
            // 
            // SetStageThreeBtn
            // 
            this->SetStageThreeBtn->Location = System::Drawing::Point(443, 188);
            this->SetStageThreeBtn->Name = L"SetStageThreeBtn";
            this->SetStageThreeBtn->Size = System::Drawing::Size(75, 23);
            this->SetStageThreeBtn->TabIndex = 193;
            this->SetStageThreeBtn->Text = L"Set";
            this->SetStageThreeBtn->UseVisualStyleBackColor = true;
            this->SetStageThreeBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::StageThreeSet_Click);
            // 
            // SetStageTwoBtn
            // 
            this->SetStageTwoBtn->Location = System::Drawing::Point(220, 188);
            this->SetStageTwoBtn->Name = L"SetStageTwoBtn";
            this->SetStageTwoBtn->Size = System::Drawing::Size(75, 23);
            this->SetStageTwoBtn->TabIndex = 192;
            this->SetStageTwoBtn->Text = L"Set";
            this->SetStageTwoBtn->UseVisualStyleBackColor = true;
            this->SetStageTwoBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::StageTwoSet_Click);
            // 
            // StageThreeZLbl
            // 
            this->StageThreeZLbl->AutoSize = true;
            this->StageThreeZLbl->Location = System::Drawing::Point(525, 218);
            this->StageThreeZLbl->Name = L"StageThreeZLbl";
            this->StageThreeZLbl->Size = System::Drawing::Size(13, 13);
            this->StageThreeZLbl->TabIndex = 191;
            this->StageThreeZLbl->Text = L"0";
            // 
            // StageTwoZLbl
            // 
            this->StageTwoZLbl->AutoSize = true;
            this->StageTwoZLbl->Location = System::Drawing::Point(309, 269);
            this->StageTwoZLbl->Name = L"StageTwoZLbl";
            this->StageTwoZLbl->Size = System::Drawing::Size(13, 13);
            this->StageTwoZLbl->TabIndex = 190;
            this->StageTwoZLbl->Text = L"0";
            // 
            // StageTwoYLbl
            // 
            this->StageTwoYLbl->AutoSize = true;
            this->StageTwoYLbl->Location = System::Drawing::Point(309, 244);
            this->StageTwoYLbl->Name = L"StageTwoYLbl";
            this->StageTwoYLbl->Size = System::Drawing::Size(13, 13);
            this->StageTwoYLbl->TabIndex = 189;
            this->StageTwoYLbl->Text = L"0";
            // 
            // StageTwoXLbl
            // 
            this->StageTwoXLbl->AutoSize = true;
            this->StageTwoXLbl->Location = System::Drawing::Point(309, 218);
            this->StageTwoXLbl->Name = L"StageTwoXLbl";
            this->StageTwoXLbl->Size = System::Drawing::Size(13, 13);
            this->StageTwoXLbl->TabIndex = 188;
            this->StageTwoXLbl->Text = L"0";
            // 
            // StageOneYLbl
            // 
            this->StageOneYLbl->AutoSize = true;
            this->StageOneYLbl->Location = System::Drawing::Point(95, 244);
            this->StageOneYLbl->Name = L"StageOneYLbl";
            this->StageOneYLbl->Size = System::Drawing::Size(13, 13);
            this->StageOneYLbl->TabIndex = 187;
            this->StageOneYLbl->Text = L"0";
            // 
            // StageOneXLbl
            // 
            this->StageOneXLbl->AutoSize = true;
            this->StageOneXLbl->Location = System::Drawing::Point(95, 218);
            this->StageOneXLbl->Name = L"StageOneXLbl";
            this->StageOneXLbl->Size = System::Drawing::Size(13, 13);
            this->StageOneXLbl->TabIndex = 186;
            this->StageOneXLbl->Text = L"0";
            // 
            // SetStageOneBtn
            // 
            this->SetStageOneBtn->Location = System::Drawing::Point(7, 188);
            this->SetStageOneBtn->Name = L"SetStageOneBtn";
            this->SetStageOneBtn->Size = System::Drawing::Size(75, 23);
            this->SetStageOneBtn->TabIndex = 185;
            this->SetStageOneBtn->Text = L"Set";
            this->SetStageOneBtn->UseVisualStyleBackColor = true;
            this->SetStageOneBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::StageOneSet_Click);
            // 
            // StopCalBtn
            // 
            this->StopCalBtn->Location = System::Drawing::Point(134, 12);
            this->StopCalBtn->Name = L"StopCalBtn";
            this->StopCalBtn->Size = System::Drawing::Size(118, 23);
            this->StopCalBtn->TabIndex = 184;
            this->StopCalBtn->Text = L"Stop Calibration";
            this->StopCalBtn->UseVisualStyleBackColor = true;
            this->StopCalBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::StopCal_Click);
            // 
            // ClearPlotBtn
            // 
            this->ClearPlotBtn->Location = System::Drawing::Point(258, 12);
            this->ClearPlotBtn->Name = L"ClearPlotBtn";
            this->ClearPlotBtn->Size = System::Drawing::Size(75, 23);
            this->ClearPlotBtn->TabIndex = 183;
            this->ClearPlotBtn->Text = L"Clear plot";
            this->ClearPlotBtn->UseVisualStyleBackColor = true;
            this->ClearPlotBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::ClearPlot_Click);
            // 
            // StartCalBtn
            // 
            this->StartCalBtn->Location = System::Drawing::Point(12, 12);
            this->StartCalBtn->Name = L"StartCalBtn";
            this->StartCalBtn->Size = System::Drawing::Size(116, 23);
            this->StartCalBtn->TabIndex = 182;
            this->StartCalBtn->Text = L"Start Calibration";
            this->StartCalBtn->UseVisualStyleBackColor = true;
            this->StartCalBtn->Click += gcnew System::EventHandler(this, &MagCalibrate::StartCal_Click);
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
            this->DataChart->Location = System::Drawing::Point(-27, 286);
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
            this->DataChart->Size = System::Drawing::Size(814, 229);
            this->DataChart->TabIndex = 181;
            this->DataChart->Text = L"MagChart";
            // 
            // XCurValLbl
            // 
            this->XCurValLbl->AutoSize = true;
            this->XCurValLbl->Location = System::Drawing::Point(362, 17);
            this->XCurValLbl->Name = L"XCurValLbl";
            this->XCurValLbl->Size = System::Drawing::Size(13, 13);
            this->XCurValLbl->TabIndex = 208;
            this->XCurValLbl->Text = L"0";
            // 
            // YCurValLbl
            // 
            this->YCurValLbl->AutoSize = true;
            this->YCurValLbl->Location = System::Drawing::Point(386, 17);
            this->YCurValLbl->Name = L"YCurValLbl";
            this->YCurValLbl->Size = System::Drawing::Size(13, 13);
            this->YCurValLbl->TabIndex = 209;
            this->YCurValLbl->Text = L"0";
            // 
            // ZCurValLbl
            // 
            this->ZCurValLbl->AutoSize = true;
            this->ZCurValLbl->Location = System::Drawing::Point(410, 17);
            this->ZCurValLbl->Name = L"ZCurValLbl";
            this->ZCurValLbl->Size = System::Drawing::Size(13, 13);
            this->ZCurValLbl->TabIndex = 210;
            this->ZCurValLbl->Text = L"0";
            // 
            // MagCalibrate
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(798, 557);
            this->Controls->Add(this->ZCurValLbl);
            this->Controls->Add(this->YCurValLbl);
            this->Controls->Add(this->XCurValLbl);
            this->Controls->Add(this->ResetCalBtn);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label30);
            this->Controls->Add(this->label29);
            this->Controls->Add(this->label27);
            this->Controls->Add(this->label28);
            this->Controls->Add(this->label26);
            this->Controls->Add(this->label25);
            this->Controls->Add(this->label24);
            this->Controls->Add(this->label17);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->button7);
            this->Controls->Add(this->button6);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->SetStageThreeBtn);
            this->Controls->Add(this->SetStageTwoBtn);
            this->Controls->Add(this->StageThreeZLbl);
            this->Controls->Add(this->StageTwoZLbl);
            this->Controls->Add(this->StageTwoYLbl);
            this->Controls->Add(this->StageTwoXLbl);
            this->Controls->Add(this->StageOneYLbl);
            this->Controls->Add(this->StageOneXLbl);
            this->Controls->Add(this->SetStageOneBtn);
            this->Controls->Add(this->StopCalBtn);
            this->Controls->Add(this->ClearPlotBtn);
            this->Controls->Add(this->StartCalBtn);
            this->Controls->Add(this->DataChart);
            this->Name = L"MagCalibrate";
            this->Text = L"Magnetometer Calibration";
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DataChart))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

private: // Variables

    int serialbyte;
    unsigned char headtracker_active;

    int xoffset;
    int yoffset;
    int zoffset;

    int x1; 
    int x2;
    int y1; 
    int y2; 
    int z1; 
    int z2; 

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

    private: System::Void StartCal_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void StopCal_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void ClearPlot_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void StageOneSet_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void StageTwoSet_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void StageThreeSet_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void SaveCal_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void ResetCal_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void UpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    private: System::Void MagCalibrate::UpdateCalc();
};
}
