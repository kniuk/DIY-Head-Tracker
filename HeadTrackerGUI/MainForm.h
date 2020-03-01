#pragma once
#include "CalWizard.h"
#include "HeadTrackerHardware.h"

namespace HeadTrackerGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for MainForm
    /// </summary>
    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            mainForm = this;
            InitializeComponent();
        }
        static MainForm^ mainForm = nullptr;

        System::Void Log(int ch);
        System::Void Log(System::String^ str);
        System::Void Log(System::String^ str, System::Exception^ e);
        System::Void LogClear();
        System::Void LogFlush();

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }
    
    private: 
        String^ text = "";
        bool newLine = false;
        int maxPoints = 200;

    
        System::Windows::Forms::ComboBox^  dd_comport; 
        System::Windows::Forms::Button^  btn_connect;

        System::Windows::Forms::Timer^  dataReaderTimer;

        System::Windows::Forms::Timer^  comPortTimer;
        System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
        System::Windows::Forms::Label^  Lowpass_text;
        System::Windows::Forms::Label^  logViewer;

        System::Windows::Forms::TextBox^  textBox_LP_value;
        System::Windows::Forms::Button^  btn_update_headtracker;
        System::Windows::Forms::Button^  start_HT;
        System::Windows::Forms::Button^  clear_HT;
        System::Windows::Forms::Label^  lbl_tilt_roll_gyro_weight;
        System::Windows::Forms::Label^  lbl_gyro_weight_pan;
        System::Windows::Forms::Label^  lbl_filter_pan;
        System::Windows::Forms::TextBox^  textBox_LP_valuePan;
        System::Windows::Forms::TextBox^  GyroWeight_tiltRoll;
        System::Windows::Forms::TextBox^  GyroWeight_pan;

        System::Windows::Forms::GroupBox^  groupBox2;
        System::Windows::Forms::GroupBox^ groupBox3;
        System::Windows::Forms::GroupBox^ groupBoxChart;
        System::Windows::Forms::Button^  btnCalibrate;
        System::Windows::Forms::GroupBox^  grpBoxServp2;
        System::Windows::Forms::MenuStrip^  menuStrip1;
        System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
        System::Windows::Forms::TrackBar^  panCenterTrackBar;
        System::Windows::Forms::Label^  label14;
        System::Windows::Forms::Label^  label17;
        System::Windows::Forms::TrackBar^  panMaxTrackBar;
        System::Windows::Forms::Label^  label18;
        System::Windows::Forms::TrackBar^  panMinTrackBar;
        System::Windows::Forms::Label^  LblPanCenter;
        System::Windows::Forms::Label^  label27;
        System::Windows::Forms::Label^  label26;
        System::Windows::Forms::Label^  lblShowOutput;
        System::Windows::Forms::Label^  label22;
        System::Windows::Forms::TrackBar^  rollMaxTrackBar;
        System::Windows::Forms::Label^  label23;
        System::Windows::Forms::TrackBar^  rollMinTrackBar;
        System::Windows::Forms::Label^  label24;
        System::Windows::Forms::TrackBar^  rollCenterTrackBar;
        System::Windows::Forms::Label^  label19;
        System::Windows::Forms::TrackBar^  tiltMaxTrackBar;
        System::Windows::Forms::Label^  label20;
        System::Windows::Forms::TrackBar^  tiltMinTrackBar;
        System::Windows::Forms::Label^  label21;
        System::Windows::Forms::TrackBar^  tiltCenterTrackBar;
        System::Windows::Forms::Label^  label29;
        System::Windows::Forms::TrackBar^  rollGainTrackBar;
        System::Windows::Forms::Label^  label28;
        System::Windows::Forms::TrackBar^  tiltGainTrackBar;
        System::Windows::Forms::Label^  label25;
        System::Windows::Forms::TrackBar^  panGainTrackBar;
        System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  calibrationWizardToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  exportSettingsToFileToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  importSettingsFromFileToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  calibrationWizardRotToolStripMenuItem;



        System::Windows::Forms::CheckBox^  chk_roll;
        System::Windows::Forms::CheckBox^  chk_tilt;
        System::Windows::Forms::CheckBox^  chk_pan;
        System::Windows::Forms::TextBox^  servoGainPan;
        System::Windows::Forms::TextBox^  servoGainTilt;
        System::Windows::Forms::Label^  label42;
        System::Windows::Forms::TextBox^  inputPanCenter;
        System::Windows::Forms::TextBox^  inputPanTravlMin;
        System::Windows::Forms::Label^  lbl_servo_center;
        System::Windows::Forms::Label^  lbl_servo_max;
        System::Windows::Forms::Label^  Pan_lbl;
        System::Windows::Forms::TextBox^  inputPanTravlMax;
        System::Windows::Forms::Label^  label1;
        System::Windows::Forms::TextBox^  inputTiltCenter;
        System::Windows::Forms::TextBox^  inputTiltTravlMin;
        System::Windows::Forms::Label^  label3;
        System::Windows::Forms::TextBox^  inputTiltTravlMax;
        System::Windows::Forms::TextBox^  inputRollCenter;
        System::Windows::Forms::TextBox^  inputRollTravlMin;
        System::Windows::Forms::Label^  label7;
        System::Windows::Forms::TextBox^  inputRollTravlMax;
        System::Windows::Forms::TextBox^  servoGainRoll;
        System::Windows::Forms::ComboBox^  inputPanCh;
        System::Windows::Forms::Label^  label2;
        System::Windows::Forms::ComboBox^  inputTiltCh;
        System::Windows::Forms::Label^  label4;
        System::Windows::Forms::ComboBox^  inputRollCh;
        System::Windows::Forms::GroupBox^ grpBoxServp1;
        System::Windows::Forms::ComboBox^ chartLimit;
        System::Windows::Forms::Button^ btnClearLog;
        System::Windows::Forms::Label^ label6;
        System::Windows::Forms::ComboBox^ dd_bluetooth;
        System::Windows::Forms::TextBox^ ManualCmdEdit;
        System::Windows::Forms::Button^ btnSendManualCmd;

       System::ComponentModel::IContainer^  components;

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
            System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
            System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->dd_comport = (gcnew System::Windows::Forms::ComboBox());
            this->btn_connect = (gcnew System::Windows::Forms::Button());
            this->dataReaderTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->comPortTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            this->Lowpass_text = (gcnew System::Windows::Forms::Label());
            this->logViewer = (gcnew System::Windows::Forms::Label());
            this->textBox_LP_value = (gcnew System::Windows::Forms::TextBox());
            this->btn_update_headtracker = (gcnew System::Windows::Forms::Button());
            this->start_HT = (gcnew System::Windows::Forms::Button());
            this->clear_HT = (gcnew System::Windows::Forms::Button());
            this->lbl_tilt_roll_gyro_weight = (gcnew System::Windows::Forms::Label());
            this->lbl_gyro_weight_pan = (gcnew System::Windows::Forms::Label());
            this->lbl_filter_pan = (gcnew System::Windows::Forms::Label());
            this->textBox_LP_valuePan = (gcnew System::Windows::Forms::TextBox());
            this->GyroWeight_tiltRoll = (gcnew System::Windows::Forms::TextBox());
            this->GyroWeight_pan = (gcnew System::Windows::Forms::TextBox());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->dd_bluetooth = (gcnew System::Windows::Forms::ComboBox());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->ManualCmdEdit = (gcnew System::Windows::Forms::TextBox());
            this->btnSendManualCmd = (gcnew System::Windows::Forms::Button());
            this->groupBoxChart = (gcnew System::Windows::Forms::GroupBox());
            this->chartLimit = (gcnew System::Windows::Forms::ComboBox());
            this->btnCalibrate = (gcnew System::Windows::Forms::Button());
            this->grpBoxServp2 = (gcnew System::Windows::Forms::GroupBox());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->rollGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->tiltGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->label26 = (gcnew System::Windows::Forms::Label());
            this->lblShowOutput = (gcnew System::Windows::Forms::Label());
            this->label22 = (gcnew System::Windows::Forms::Label());
            this->rollMaxTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label23 = (gcnew System::Windows::Forms::Label());
            this->rollMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->rollCenterTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->tiltMaxTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label20 = (gcnew System::Windows::Forms::Label());
            this->tiltMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label21 = (gcnew System::Windows::Forms::Label());
            this->tiltCenterTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->panMaxTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->panMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->LblPanCenter = (gcnew System::Windows::Forms::Label());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->panCenterTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->panGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->exportSettingsToFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->importSettingsFromFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->calibrationWizardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->calibrationWizardRotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->chk_roll = (gcnew System::Windows::Forms::CheckBox());
            this->chk_tilt = (gcnew System::Windows::Forms::CheckBox());
            this->chk_pan = (gcnew System::Windows::Forms::CheckBox());
            this->servoGainPan = (gcnew System::Windows::Forms::TextBox());
            this->servoGainTilt = (gcnew System::Windows::Forms::TextBox());
            this->label42 = (gcnew System::Windows::Forms::Label());
            this->inputPanCenter = (gcnew System::Windows::Forms::TextBox());
            this->inputPanTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->lbl_servo_center = (gcnew System::Windows::Forms::Label());
            this->lbl_servo_max = (gcnew System::Windows::Forms::Label());
            this->Pan_lbl = (gcnew System::Windows::Forms::Label());
            this->inputPanTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->inputTiltCenter = (gcnew System::Windows::Forms::TextBox());
            this->inputTiltTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->inputTiltTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->inputRollCenter = (gcnew System::Windows::Forms::TextBox());
            this->inputRollTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->inputRollTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->servoGainRoll = (gcnew System::Windows::Forms::TextBox());
            this->inputPanCh = (gcnew System::Windows::Forms::ComboBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->inputTiltCh = (gcnew System::Windows::Forms::ComboBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->inputRollCh = (gcnew System::Windows::Forms::ComboBox());
            this->grpBoxServp1 = (gcnew System::Windows::Forms::GroupBox());
            this->btnClearLog = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
            this->groupBox2->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->groupBoxChart->SuspendLayout();
            this->grpBoxServp2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollGainTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltGainTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollCenterTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltCenterTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panCenterTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panGainTrackBar))->BeginInit();
            this->menuStrip1->SuspendLayout();
            this->grpBoxServp1->SuspendLayout();
            this->SuspendLayout();
            // 
            // dd_comport
            // 
            this->dd_comport->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->dd_comport->FormattingEnabled = true;
            this->dd_comport->Location = System::Drawing::Point(12, 44);
            this->dd_comport->Name = L"dd_comport";
            this->dd_comport->Size = System::Drawing::Size(93, 21);
            this->dd_comport->TabIndex = 0;
            // 
            // btn_connect
            // 
            this->btn_connect->Location = System::Drawing::Point(12, 69);
            this->btn_connect->Name = L"btn_connect";
            this->btn_connect->Size = System::Drawing::Size(93, 23);
            this->btn_connect->TabIndex = 1;
            this->btn_connect->Text = L"&Connect";
            this->btn_connect->UseVisualStyleBackColor = true;
            this->btn_connect->Click += gcnew System::EventHandler(this, &MainForm::btn_connect_Click);
            // 
            // dataReaderTimer
            // 
            this->dataReaderTimer->Interval = 50;
            this->dataReaderTimer->Tick += gcnew System::EventHandler(this, &MainForm::dataReaderTimer_Tick);
            // 
            // comPortTimer
            // 
            this->comPortTimer->Enabled = true;
            this->comPortTimer->Interval = 2000;
            this->comPortTimer->Tick += gcnew System::EventHandler(this, &MainForm::comPortTimer_Tick);
            // 
            // chart1
            // 
            this->chart1->BackColor = System::Drawing::Color::Transparent;
            chartArea1->BackColor = System::Drawing::Color::Transparent;
            chartArea1->BackImageTransparentColor = System::Drawing::Color::Red;
            chartArea1->BackSecondaryColor = System::Drawing::Color::Black;
            chartArea1->Name = L"ChartArea1";
            chartArea1->ShadowColor = System::Drawing::Color::Fuchsia;
            this->chart1->ChartAreas->Add(chartArea1);
            legend1->BackColor = System::Drawing::Color::Transparent;
            legend1->Name = L"Legend1";
            this->chart1->Legends->Add(legend1);
            this->chart1->Location = System::Drawing::Point(-13, 16);
            this->chart1->Margin = System::Windows::Forms::Padding(0);
            this->chart1->Name = L"chart1";
            series1->ChartArea = L"ChartArea1";
            series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series1->Legend = L"Legend1";
            series1->Name = L"Pan";
            series2->ChartArea = L"ChartArea1";
            series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series2->Legend = L"Legend1";
            series2->Name = L"Tilt";
            series3->ChartArea = L"ChartArea1";
            series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
            series3->Legend = L"Legend1";
            series3->Name = L"Roll";
            this->chart1->Series->Add(series1);
            this->chart1->Series->Add(series2);
            this->chart1->Series->Add(series3);
            this->chart1->Size = System::Drawing::Size(739, 211);
            this->chart1->TabIndex = 78;
            this->chart1->Text = L"chart1";
            // 
            // Lowpass_text
            // 
            this->Lowpass_text->AutoSize = true;
            this->Lowpass_text->Location = System::Drawing::Point(60, 46);
            this->Lowpass_text->Name = L"Lowpass_text";
            this->Lowpass_text->Size = System::Drawing::Size(129, 13);
            this->Lowpass_text->TabIndex = 79;
            this->Lowpass_text->Text = L"LP filter beta on tilt/roll [%]";
            // 
            // logViewer
            // 
            this->logViewer->AllowDrop = true;
            this->logViewer->BackColor = System::Drawing::Color::White;
            this->logViewer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.6F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->logViewer->Location = System::Drawing::Point(117, 44);
            this->logViewer->Margin = System::Windows::Forms::Padding(3);
            this->logViewer->Name = L"logViewer";
            this->logViewer->Size = System::Drawing::Size(325, 189);
            this->logViewer->TabIndex = 80;
            // 
            // textBox_LP_value
            // 
            this->textBox_LP_value->Location = System::Drawing::Point(195, 43);
            this->textBox_LP_value->Name = L"textBox_LP_value";
            this->textBox_LP_value->Size = System::Drawing::Size(41, 20);
            this->textBox_LP_value->TabIndex = 81;
            this->textBox_LP_value->Text = L"75";
            // 
            // btn_update_headtracker
            // 
            this->btn_update_headtracker->Enabled = false;
            this->btn_update_headtracker->Location = System::Drawing::Point(12, 121);
            this->btn_update_headtracker->Name = L"btn_update_headtracker";
            this->btn_update_headtracker->Size = System::Drawing::Size(93, 23);
            this->btn_update_headtracker->TabIndex = 82;
            this->btn_update_headtracker->Text = L"Store Settings";
            this->btn_update_headtracker->UseVisualStyleBackColor = true;
            this->btn_update_headtracker->Click += gcnew System::EventHandler(this, &MainForm::btn_update_headtracker_Click);
            // 
            // start_HT
            // 
            this->start_HT->Enabled = false;
            this->start_HT->Location = System::Drawing::Point(619, 108);
            this->start_HT->Name = L"start_HT";
            this->start_HT->Size = System::Drawing::Size(75, 23);
            this->start_HT->TabIndex = 83;
            this->start_HT->Text = L"Start plot";
            this->start_HT->UseVisualStyleBackColor = true;
            this->start_HT->Click += gcnew System::EventHandler(this, &MainForm::start_HT_Click);
            // 
            // clear_HT
            // 
            this->clear_HT->Enabled = false;
            this->clear_HT->Location = System::Drawing::Point(619, 136);
            this->clear_HT->Name = L"clear_HT";
            this->clear_HT->Size = System::Drawing::Size(75, 23);
            this->clear_HT->TabIndex = 84;
            this->clear_HT->Text = L"Clear plot";
            this->clear_HT->UseVisualStyleBackColor = true;
            this->clear_HT->Click += gcnew System::EventHandler(this, &MainForm::clear_HT_Click);
            // 
            // lbl_tilt_roll_gyro_weight
            // 
            this->lbl_tilt_roll_gyro_weight->AutoSize = true;
            this->lbl_tilt_roll_gyro_weight->Location = System::Drawing::Point(64, 69);
            this->lbl_tilt_roll_gyro_weight->Name = L"lbl_tilt_roll_gyro_weight";
            this->lbl_tilt_roll_gyro_weight->Size = System::Drawing::Size(126, 13);
            this->lbl_tilt_roll_gyro_weight->TabIndex = 115;
            this->lbl_tilt_roll_gyro_weight->Text = L"Gyro weight on tilt/roll [%]";
            // 
            // lbl_gyro_weight_pan
            // 
            this->lbl_gyro_weight_pan->AutoSize = true;
            this->lbl_gyro_weight_pan->Location = System::Drawing::Point(73, 115);
            this->lbl_gyro_weight_pan->Name = L"lbl_gyro_weight_pan";
            this->lbl_gyro_weight_pan->Size = System::Drawing::Size(116, 13);
            this->lbl_gyro_weight_pan->TabIndex = 116;
            this->lbl_gyro_weight_pan->Text = L"Gyro weight on pan [%]";
            // 
            // lbl_filter_pan
            // 
            this->lbl_filter_pan->AutoSize = true;
            this->lbl_filter_pan->Location = System::Drawing::Point(70, 92);
            this->lbl_filter_pan->Name = L"lbl_filter_pan";
            this->lbl_filter_pan->Size = System::Drawing::Size(119, 13);
            this->lbl_filter_pan->TabIndex = 117;
            this->lbl_filter_pan->Text = L"LP filter beta on pan [%]";
            // 
            // textBox_LP_valuePan
            // 
            this->textBox_LP_valuePan->Location = System::Drawing::Point(195, 89);
            this->textBox_LP_valuePan->Name = L"textBox_LP_valuePan";
            this->textBox_LP_valuePan->Size = System::Drawing::Size(41, 20);
            this->textBox_LP_valuePan->TabIndex = 118;
            this->textBox_LP_valuePan->Text = L"75";
            // 
            // GyroWeight_tiltRoll
            // 
            this->GyroWeight_tiltRoll->Location = System::Drawing::Point(195, 66);
            this->GyroWeight_tiltRoll->Name = L"GyroWeight_tiltRoll";
            this->GyroWeight_tiltRoll->Size = System::Drawing::Size(41, 20);
            this->GyroWeight_tiltRoll->TabIndex = 119;
            this->GyroWeight_tiltRoll->Text = L"98";
            // 
            // GyroWeight_pan
            // 
            this->GyroWeight_pan->Location = System::Drawing::Point(195, 112);
            this->GyroWeight_pan->Name = L"GyroWeight_pan";
            this->GyroWeight_pan->Size = System::Drawing::Size(41, 20);
            this->GyroWeight_pan->TabIndex = 120;
            this->GyroWeight_pan->Text = L"98";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->label6);
            this->groupBox2->Controls->Add(this->dd_bluetooth);
            this->groupBox2->Controls->Add(this->Lowpass_text);
            this->groupBox2->Controls->Add(this->textBox_LP_value);
            this->groupBox2->Controls->Add(this->lbl_tilt_roll_gyro_weight);
            this->groupBox2->Controls->Add(this->GyroWeight_pan);
            this->groupBox2->Controls->Add(this->lbl_gyro_weight_pan);
            this->groupBox2->Controls->Add(this->GyroWeight_tiltRoll);
            this->groupBox2->Controls->Add(this->lbl_filter_pan);
            this->groupBox2->Controls->Add(this->textBox_LP_valuePan);
            this->groupBox2->Enabled = false;
            this->groupBox2->Location = System::Drawing::Point(457, 91);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(256, 144);
            this->groupBox2->TabIndex = 134;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Advanced Parameters";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(45, 20);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(71, 13);
            this->label6->TabIndex = 146;
            this->label6->Text = L"Device Mode";
            // 
            // dd_bluetooth
            // 
            this->dd_bluetooth->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->dd_bluetooth->Enabled = false;
            this->dd_bluetooth->FormattingEnabled = true;
            this->dd_bluetooth->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Standard", L"BT Tracker", L"BT Receiver" });
            this->dd_bluetooth->Location = System::Drawing::Point(122, 17);
            this->dd_bluetooth->Name = L"dd_bluetooth";
            this->dd_bluetooth->Size = System::Drawing::Size(114, 21);
            this->dd_bluetooth->TabIndex = 145;
            // 
            // groupBox3
            // 
            this->groupBox3->Controls->Add(this->ManualCmdEdit);
            this->groupBox3->Controls->Add(this->btnSendManualCmd);
            this->groupBox3->Enabled = false;
            this->groupBox3->Location = System::Drawing::Point(457, 37);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(256, 48);
            this->groupBox3->TabIndex = 134;
            this->groupBox3->TabStop = false;
            this->groupBox3->Text = L"Manual command";
            // 
            // ManualCmdEdit
            // 
            this->ManualCmdEdit->Location = System::Drawing::Point(11, 16);
            this->ManualCmdEdit->MaxLength = 100;
            this->ManualCmdEdit->Name = L"ManualCmdEdit";
            this->ManualCmdEdit->Size = System::Drawing::Size(178, 20);
            this->ManualCmdEdit->TabIndex = 142;
            this->ManualCmdEdit->WordWrap = false;
            this->ManualCmdEdit->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::ManualCmdEdit_OnKeyDown);
            // 
            // btnSendManualCmd
            // 
            this->btnSendManualCmd->Enabled = false;
            this->btnSendManualCmd->Location = System::Drawing::Point(195, 14);
            this->btnSendManualCmd->Name = L"btnSendManualCmd";
            this->btnSendManualCmd->Size = System::Drawing::Size(50, 23);
            this->btnSendManualCmd->TabIndex = 143;
            this->btnSendManualCmd->Text = L"Send";
            this->btnSendManualCmd->UseVisualStyleBackColor = true;
            this->btnSendManualCmd->Click += gcnew System::EventHandler(this, &MainForm::btnSendManualCmd_Click);
            // 
            // groupBoxChart
            // 
            this->groupBoxChart->Controls->Add(this->chartLimit);
            this->groupBoxChart->Controls->Add(this->clear_HT);
            this->groupBoxChart->Controls->Add(this->start_HT);
            this->groupBoxChart->Controls->Add(this->chart1);
            this->groupBoxChart->Enabled = false;
            this->groupBoxChart->Location = System::Drawing::Point(13, 475);
            this->groupBoxChart->Name = L"groupBoxChart";
            this->groupBoxChart->Size = System::Drawing::Size(700, 242);
            this->groupBoxChart->TabIndex = 134;
            this->groupBoxChart->TabStop = false;
            this->groupBoxChart->Text = L"Pan / Tilt / Roll graph";
            // 
            // chartLimit
            // 
            this->chartLimit->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->chartLimit->Enabled = false;
            this->chartLimit->FormattingEnabled = true;
            this->chartLimit->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
                L"100 points", L"200 points", L"500 points", L"1000 points",
                    L"All points"
            });
            this->chartLimit->Location = System::Drawing::Point(619, 83);
            this->chartLimit->Name = L"chartLimit";
            this->chartLimit->Size = System::Drawing::Size(75, 21);
            this->chartLimit->TabIndex = 144;
            this->chartLimit->SelectionChangeCommitted += gcnew System::EventHandler(this, &MainForm::chartLimit_SelectionChangeCommitted);
            // 
            // btnCalibrate
            // 
            this->btnCalibrate->Enabled = false;
            this->btnCalibrate->Location = System::Drawing::Point(12, 95);
            this->btnCalibrate->Name = L"btnCalibrate";
            this->btnCalibrate->Size = System::Drawing::Size(93, 23);
            this->btnCalibrate->TabIndex = 137;
            this->btnCalibrate->Text = L"Calibrate";
            this->btnCalibrate->UseVisualStyleBackColor = true;
            this->btnCalibrate->Click += gcnew System::EventHandler(this, &MainForm::btnCalibrate_Click);
            // 
            // grpBoxServp2
            // 
            this->grpBoxServp2->Controls->Add(this->label29);
            this->grpBoxServp2->Controls->Add(this->rollGainTrackBar);
            this->grpBoxServp2->Controls->Add(this->label28);
            this->grpBoxServp2->Controls->Add(this->tiltGainTrackBar);
            this->grpBoxServp2->Controls->Add(this->label25);
            this->grpBoxServp2->Controls->Add(this->label27);
            this->grpBoxServp2->Controls->Add(this->label26);
            this->grpBoxServp2->Controls->Add(this->lblShowOutput);
            this->grpBoxServp2->Controls->Add(this->label22);
            this->grpBoxServp2->Controls->Add(this->rollMaxTrackBar);
            this->grpBoxServp2->Controls->Add(this->label23);
            this->grpBoxServp2->Controls->Add(this->rollMinTrackBar);
            this->grpBoxServp2->Controls->Add(this->label24);
            this->grpBoxServp2->Controls->Add(this->rollCenterTrackBar);
            this->grpBoxServp2->Controls->Add(this->label19);
            this->grpBoxServp2->Controls->Add(this->tiltMaxTrackBar);
            this->grpBoxServp2->Controls->Add(this->label20);
            this->grpBoxServp2->Controls->Add(this->tiltMinTrackBar);
            this->grpBoxServp2->Controls->Add(this->label21);
            this->grpBoxServp2->Controls->Add(this->tiltCenterTrackBar);
            this->grpBoxServp2->Controls->Add(this->label17);
            this->grpBoxServp2->Controls->Add(this->panMaxTrackBar);
            this->grpBoxServp2->Controls->Add(this->label18);
            this->grpBoxServp2->Controls->Add(this->panMinTrackBar);
            this->grpBoxServp2->Controls->Add(this->LblPanCenter);
            this->grpBoxServp2->Controls->Add(this->label14);
            this->grpBoxServp2->Controls->Add(this->panCenterTrackBar);
            this->grpBoxServp2->Controls->Add(this->panGainTrackBar);
            this->grpBoxServp2->Enabled = false;
            this->grpBoxServp2->Location = System::Drawing::Point(13, 241);
            this->grpBoxServp2->Name = L"grpBoxServp2";
            this->grpBoxServp2->Size = System::Drawing::Size(430, 229);
            this->grpBoxServp2->TabIndex = 138;
            this->grpBoxServp2->TabStop = false;
            this->grpBoxServp2->Text = L"Servo";
            // 
            // label29
            // 
            this->label29->AutoSize = true;
            this->label29->BackColor = System::Drawing::Color::Transparent;
            this->label29->Location = System::Drawing::Point(331, 170);
            this->label29->Name = L"label29";
            this->label29->Size = System::Drawing::Size(29, 13);
            this->label29->TabIndex = 178;
            this->label29->Text = L"Gain";
            // 
            // rollGainTrackBar
            // 
            this->rollGainTrackBar->Location = System::Drawing::Point(288, 181);
            this->rollGainTrackBar->Maximum = 500;
            this->rollGainTrackBar->Name = L"rollGainTrackBar";
            this->rollGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollGainTrackBar->TabIndex = 177;
            this->rollGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollGainTrackBar->Value = 170;
            this->rollGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::RollGainTrackBar_ValueChanged);
            // 
            // label28
            // 
            this->label28->AutoSize = true;
            this->label28->BackColor = System::Drawing::Color::Transparent;
            this->label28->Location = System::Drawing::Point(190, 170);
            this->label28->Name = L"label28";
            this->label28->Size = System::Drawing::Size(29, 13);
            this->label28->TabIndex = 176;
            this->label28->Text = L"Gain";
            // 
            // tiltGainTrackBar
            // 
            this->tiltGainTrackBar->Location = System::Drawing::Point(147, 181);
            this->tiltGainTrackBar->Maximum = 500;
            this->tiltGainTrackBar->Name = L"tiltGainTrackBar";
            this->tiltGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltGainTrackBar->TabIndex = 175;
            this->tiltGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltGainTrackBar->Value = 170;
            this->tiltGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::TiltGainTrackBar_ValueChanged);
            // 
            // label25
            // 
            this->label25->AutoSize = true;
            this->label25->BackColor = System::Drawing::Color::Transparent;
            this->label25->Location = System::Drawing::Point(54, 170);
            this->label25->Name = L"label25";
            this->label25->Size = System::Drawing::Size(29, 13);
            this->label25->TabIndex = 174;
            this->label25->Text = L"Gain";
            // 
            // label27
            // 
            this->label27->AutoSize = true;
            this->label27->BackColor = System::Drawing::Color::Transparent;
            this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label27->Location = System::Drawing::Point(334, 19);
            this->label27->Name = L"label27";
            this->label27->Size = System::Drawing::Size(29, 13);
            this->label27->TabIndex = 152;
            this->label27->Text = L"Roll";
            // 
            // label26
            // 
            this->label26->AutoSize = true;
            this->label26->BackColor = System::Drawing::Color::Transparent;
            this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label26->Location = System::Drawing::Point(196, 19);
            this->label26->Name = L"label26";
            this->label26->Size = System::Drawing::Size(25, 13);
            this->label26->TabIndex = 152;
            this->label26->Text = L"Tilt";
            // 
            // lblShowOutput
            // 
            this->lblShowOutput->AutoSize = true;
            this->lblShowOutput->Location = System::Drawing::Point(463, 200);
            this->lblShowOutput->Name = L"lblShowOutput";
            this->lblShowOutput->Size = System::Drawing::Size(0, 13);
            this->lblShowOutput->TabIndex = 172;
            // 
            // label22
            // 
            this->label22->AutoSize = true;
            this->label22->BackColor = System::Drawing::Color::Transparent;
            this->label22->Location = System::Drawing::Point(331, 127);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(38, 13);
            this->label22->TabIndex = 171;
            this->label22->Text = L"<- End";
            // 
            // rollMaxTrackBar
            // 
            this->rollMaxTrackBar->Location = System::Drawing::Point(288, 138);
            this->rollMaxTrackBar->Maximum = 1150;
            this->rollMaxTrackBar->Name = L"rollMaxTrackBar";
            this->rollMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollMaxTrackBar->TabIndex = 170;
            this->rollMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollMaxTrackBar->Value = 1150;
            this->rollMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::RollMaxTrackBar_ValueChanged);
            // 
            // label23
            // 
            this->label23->AutoSize = true;
            this->label23->BackColor = System::Drawing::Color::Transparent;
            this->label23->Location = System::Drawing::Point(331, 85);
            this->label23->Name = L"label23";
            this->label23->Size = System::Drawing::Size(38, 13);
            this->label23->TabIndex = 169;
            this->label23->Text = L"End ->";
            // 
            // rollMinTrackBar
            // 
            this->rollMinTrackBar->Location = System::Drawing::Point(287, 93);
            this->rollMinTrackBar->Maximum = 1150;
            this->rollMinTrackBar->Name = L"rollMinTrackBar";
            this->rollMinTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollMinTrackBar->TabIndex = 168;
            this->rollMinTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollMinTrackBar->Value = 1150;
            this->rollMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::RollMinTrackBar_ValueChanged);
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->BackColor = System::Drawing::Color::Transparent;
            this->label24->Location = System::Drawing::Point(331, 43);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(38, 13);
            this->label24->TabIndex = 167;
            this->label24->Text = L"Center";
            // 
            // rollCenterTrackBar
            // 
            this->rollCenterTrackBar->Location = System::Drawing::Point(288, 56);
            this->rollCenterTrackBar->Maximum = 400;
            this->rollCenterTrackBar->Minimum = -400;
            this->rollCenterTrackBar->Name = L"rollCenterTrackBar";
            this->rollCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollCenterTrackBar->TabIndex = 166;
            this->rollCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::RollCenterTrackBar_ValueChanged);
            // 
            // label19
            // 
            this->label19->AutoSize = true;
            this->label19->BackColor = System::Drawing::Color::Transparent;
            this->label19->Location = System::Drawing::Point(190, 127);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(38, 13);
            this->label19->TabIndex = 165;
            this->label19->Text = L"<- End";
            // 
            // tiltMaxTrackBar
            // 
            this->tiltMaxTrackBar->Location = System::Drawing::Point(147, 138);
            this->tiltMaxTrackBar->Maximum = 1150;
            this->tiltMaxTrackBar->Name = L"tiltMaxTrackBar";
            this->tiltMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltMaxTrackBar->TabIndex = 164;
            this->tiltMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltMaxTrackBar->Value = 1150;
            this->tiltMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::TiltMaxTrackBar_ValueChanged);
            // 
            // label20
            // 
            this->label20->AutoSize = true;
            this->label20->BackColor = System::Drawing::Color::Transparent;
            this->label20->Location = System::Drawing::Point(190, 85);
            this->label20->Name = L"label20";
            this->label20->Size = System::Drawing::Size(38, 13);
            this->label20->TabIndex = 163;
            this->label20->Text = L"End ->";
            // 
            // tiltMinTrackBar
            // 
            this->tiltMinTrackBar->Location = System::Drawing::Point(146, 93);
            this->tiltMinTrackBar->Maximum = 1150;
            this->tiltMinTrackBar->Name = L"tiltMinTrackBar";
            this->tiltMinTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltMinTrackBar->TabIndex = 162;
            this->tiltMinTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltMinTrackBar->Value = 1150;
            this->tiltMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::TiltMinTrackBar_ValueChanged);
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->BackColor = System::Drawing::Color::Transparent;
            this->label21->Location = System::Drawing::Point(190, 43);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(38, 13);
            this->label21->TabIndex = 161;
            this->label21->Text = L"Center";
            // 
            // tiltCenterTrackBar
            // 
            this->tiltCenterTrackBar->Location = System::Drawing::Point(147, 56);
            this->tiltCenterTrackBar->Maximum = 400;
            this->tiltCenterTrackBar->Minimum = -400;
            this->tiltCenterTrackBar->Name = L"tiltCenterTrackBar";
            this->tiltCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltCenterTrackBar->TabIndex = 160;
            this->tiltCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::TiltCenterTrackBar_ValueChanged);
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->BackColor = System::Drawing::Color::Transparent;
            this->label17->Location = System::Drawing::Point(54, 127);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(38, 13);
            this->label17->TabIndex = 159;
            this->label17->Text = L"<- End";
            // 
            // panMaxTrackBar
            // 
            this->panMaxTrackBar->Location = System::Drawing::Point(11, 138);
            this->panMaxTrackBar->Maximum = 1150;
            this->panMaxTrackBar->Name = L"panMaxTrackBar";
            this->panMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->panMaxTrackBar->TabIndex = 158;
            this->panMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panMaxTrackBar->Value = 1150;
            this->panMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::PanMaxTrackBar_ValueChanged);
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->BackColor = System::Drawing::Color::Transparent;
            this->label18->Location = System::Drawing::Point(54, 85);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(38, 13);
            this->label18->TabIndex = 157;
            this->label18->Text = L"End ->";
            // 
            // panMinTrackBar
            // 
            this->panMinTrackBar->Location = System::Drawing::Point(10, 93);
            this->panMinTrackBar->Maximum = 1150;
            this->panMinTrackBar->Name = L"panMinTrackBar";
            this->panMinTrackBar->Size = System::Drawing::Size(130, 45);
            this->panMinTrackBar->TabIndex = 156;
            this->panMinTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panMinTrackBar->Value = 1150;
            this->panMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::PanMinTrackBar_ValueChanged);
            // 
            // LblPanCenter
            // 
            this->LblPanCenter->AutoSize = true;
            this->LblPanCenter->BackColor = System::Drawing::Color::Transparent;
            this->LblPanCenter->Location = System::Drawing::Point(54, 43);
            this->LblPanCenter->Name = L"LblPanCenter";
            this->LblPanCenter->Size = System::Drawing::Size(38, 13);
            this->LblPanCenter->TabIndex = 153;
            this->LblPanCenter->Text = L"Center";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->BackColor = System::Drawing::Color::Transparent;
            this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label14->Location = System::Drawing::Point(56, 19);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(29, 13);
            this->label14->TabIndex = 152;
            this->label14->Text = L"Pan";
            // 
            // panCenterTrackBar
            // 
            this->panCenterTrackBar->Location = System::Drawing::Point(11, 56);
            this->panCenterTrackBar->Maximum = 400;
            this->panCenterTrackBar->Minimum = -400;
            this->panCenterTrackBar->Name = L"panCenterTrackBar";
            this->panCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->panCenterTrackBar->TabIndex = 140;
            this->panCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::PanCenterTrackBar_ValueChanged);
            // 
            // panGainTrackBar
            // 
            this->panGainTrackBar->Location = System::Drawing::Point(11, 181);
            this->panGainTrackBar->Maximum = 500;
            this->panGainTrackBar->Name = L"panGainTrackBar";
            this->panGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->panGainTrackBar->TabIndex = 173;
            this->panGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panGainTrackBar->Value = 170;
            this->panGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::PanGainTrackBar_ValueChanged);
            // 
            // menuStrip1
            // 
            this->menuStrip1->BackColor = System::Drawing::Color::WhiteSmoke;
            this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->fileToolStripMenuItem,
                    this->toolsToolStripMenuItem, this->helpToolStripMenuItem
            });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
            this->menuStrip1->Size = System::Drawing::Size(729, 24);
            this->menuStrip1->TabIndex = 139;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                this->exportSettingsToFileToolStripMenuItem,
                    this->importSettingsFromFileToolStripMenuItem, this->exitToolStripMenuItem
            });
            this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
            this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
            this->fileToolStripMenuItem->Text = L"File";
            // 
            // exportSettingsToFileToolStripMenuItem
            // 
            this->exportSettingsToFileToolStripMenuItem->Enabled = false;
            this->exportSettingsToFileToolStripMenuItem->Name = L"exportSettingsToFileToolStripMenuItem";
            this->exportSettingsToFileToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->exportSettingsToFileToolStripMenuItem->Text = L"Export Settings to File...";
            this->exportSettingsToFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OnExportSettingsToFile_Menu);
            // 
            // importSettingsFromFileToolStripMenuItem
            // 
            this->importSettingsFromFileToolStripMenuItem->Enabled = false;
            this->importSettingsFromFileToolStripMenuItem->Name = L"importSettingsFromFileToolStripMenuItem";
            this->importSettingsFromFileToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->importSettingsFromFileToolStripMenuItem->Text = L"Import Settings From File...";
            this->importSettingsFromFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OnImportSettingsFromFile_Menu);
            // 
            // exitToolStripMenuItem
            // 
            this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
            this->exitToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->exitToolStripMenuItem->Text = L"Exit";
            this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->calibrationWizardToolStripMenuItem,
                    this->calibrationWizardRotToolStripMenuItem
            });
            this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
            this->toolsToolStripMenuItem->Size = System::Drawing::Size(46, 20);
            this->toolsToolStripMenuItem->Text = L"Tools";
            // 
            // calibrationWizardToolStripMenuItem
            // 
            this->calibrationWizardToolStripMenuItem->Enabled = false;
            this->calibrationWizardToolStripMenuItem->Name = L"calibrationWizardToolStripMenuItem";
            this->calibrationWizardToolStripMenuItem->Size = System::Drawing::Size(281, 22);
            this->calibrationWizardToolStripMenuItem->Text = L"Calibration Wizard (Axis Method)...";
            this->calibrationWizardToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OnCalWizard_Menu);
            // 
            // calibrationWizardRotToolStripMenuItem
            // 
            this->calibrationWizardRotToolStripMenuItem->Enabled = false;
            this->calibrationWizardRotToolStripMenuItem->Name = L"calibrationWizardRotToolStripMenuItem";
            this->calibrationWizardRotToolStripMenuItem->Size = System::Drawing::Size(281, 22);
            this->calibrationWizardRotToolStripMenuItem->Text = L"Calibration Wizard (Rotation Method)...";
            this->calibrationWizardRotToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OnCalWizardRot_Menu);
            // 
            // helpToolStripMenuItem
            // 
            this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
            this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
            this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
            this->helpToolStripMenuItem->Text = L"Help";
            // 
            // aboutToolStripMenuItem
            // 
            this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
            this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
            this->aboutToolStripMenuItem->Text = L"About";
            this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
            // 
            // chk_roll
            // 
            this->chk_roll->AutoSize = true;
            this->chk_roll->Location = System::Drawing::Point(204, 183);
            this->chk_roll->Name = L"chk_roll";
            this->chk_roll->Size = System::Drawing::Size(15, 14);
            this->chk_roll->TabIndex = 131;
            this->chk_roll->UseVisualStyleBackColor = true;
            // 
            // chk_tilt
            // 
            this->chk_tilt->AutoSize = true;
            this->chk_tilt->Location = System::Drawing::Point(152, 183);
            this->chk_tilt->Name = L"chk_tilt";
            this->chk_tilt->Size = System::Drawing::Size(15, 14);
            this->chk_tilt->TabIndex = 130;
            this->chk_tilt->UseVisualStyleBackColor = true;
            // 
            // chk_pan
            // 
            this->chk_pan->AutoSize = true;
            this->chk_pan->Location = System::Drawing::Point(101, 183);
            this->chk_pan->Name = L"chk_pan";
            this->chk_pan->Size = System::Drawing::Size(15, 14);
            this->chk_pan->TabIndex = 132;
            this->chk_pan->UseVisualStyleBackColor = true;
            // 
            // servoGainPan
            // 
            this->servoGainPan->Location = System::Drawing::Point(86, 153);
            this->servoGainPan->Name = L"servoGainPan";
            this->servoGainPan->Size = System::Drawing::Size(46, 20);
            this->servoGainPan->TabIndex = 126;
            this->servoGainPan->Text = L"170";
            this->servoGainPan->TextChanged += gcnew System::EventHandler(this, &MainForm::PanGainEdit_ValueChanged);
            // 
            // servoGainTilt
            // 
            this->servoGainTilt->Location = System::Drawing::Point(138, 153);
            this->servoGainTilt->Name = L"servoGainTilt";
            this->servoGainTilt->Size = System::Drawing::Size(46, 20);
            this->servoGainTilt->TabIndex = 125;
            this->servoGainTilt->Text = L"170";
            this->servoGainTilt->TextChanged += gcnew System::EventHandler(this, &MainForm::TiltGainEdit_ValueChanged);
            // 
            // label42
            // 
            this->label42->Location = System::Drawing::Point(6, 154);
            this->label42->Name = L"label42";
            this->label42->Size = System::Drawing::Size(78, 18);
            this->label42->TabIndex = 128;
            this->label42->Text = L"Gain";
            this->label42->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // inputPanCenter
            // 
            this->inputPanCenter->Location = System::Drawing::Point(86, 127);
            this->inputPanCenter->Name = L"inputPanCenter";
            this->inputPanCenter->Size = System::Drawing::Size(46, 20);
            this->inputPanCenter->TabIndex = 122;
            this->inputPanCenter->Text = L"2100";
            this->inputPanCenter->TextChanged += gcnew System::EventHandler(this, &MainForm::PanCenterEdit_ValueChanged);
            // 
            // inputPanTravlMin
            // 
            this->inputPanTravlMin->Location = System::Drawing::Point(86, 75);
            this->inputPanTravlMin->Name = L"inputPanTravlMin";
            this->inputPanTravlMin->Size = System::Drawing::Size(46, 20);
            this->inputPanTravlMin->TabIndex = 121;
            this->inputPanTravlMin->Text = L"1150";
            this->inputPanTravlMin->TextChanged += gcnew System::EventHandler(this, &MainForm::PanMinTravelEdit_ValueChanged);
            // 
            // lbl_servo_center
            // 
            this->lbl_servo_center->Location = System::Drawing::Point(6, 128);
            this->lbl_servo_center->Name = L"lbl_servo_center";
            this->lbl_servo_center->Size = System::Drawing::Size(78, 18);
            this->lbl_servo_center->TabIndex = 114;
            this->lbl_servo_center->Text = L"Center";
            this->lbl_servo_center->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // lbl_servo_max
            // 
            this->lbl_servo_max->Location = System::Drawing::Point(6, 76);
            this->lbl_servo_max->Name = L"lbl_servo_max";
            this->lbl_servo_max->Size = System::Drawing::Size(78, 18);
            this->lbl_servo_max->TabIndex = 113;
            this->lbl_servo_max->Text = L"Travel Min";
            this->lbl_servo_max->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // Pan_lbl
            // 
            this->Pan_lbl->AutoSize = true;
            this->Pan_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->Pan_lbl->Location = System::Drawing::Point(91, 21);
            this->Pan_lbl->Name = L"Pan_lbl";
            this->Pan_lbl->Size = System::Drawing::Size(29, 13);
            this->Pan_lbl->TabIndex = 133;
            this->Pan_lbl->Text = L"Pan";
            // 
            // inputPanTravlMax
            // 
            this->inputPanTravlMax->Location = System::Drawing::Point(86, 101);
            this->inputPanTravlMax->Name = L"inputPanTravlMax";
            this->inputPanTravlMax->Size = System::Drawing::Size(46, 20);
            this->inputPanTravlMax->TabIndex = 134;
            this->inputPanTravlMax->Text = L"1150";
            this->inputPanTravlMax->TextChanged += gcnew System::EventHandler(this, &MainForm::PanMaxTravelEdit_ValueChanged);
            // 
            // label1
            // 
            this->label1->Location = System::Drawing::Point(6, 102);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(78, 18);
            this->label1->TabIndex = 135;
            this->label1->Text = L"Travel Max";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // inputTiltCenter
            // 
            this->inputTiltCenter->Location = System::Drawing::Point(138, 127);
            this->inputTiltCenter->Name = L"inputTiltCenter";
            this->inputTiltCenter->Size = System::Drawing::Size(46, 20);
            this->inputTiltCenter->TabIndex = 139;
            this->inputTiltCenter->Text = L"2100";
            this->inputTiltCenter->TextChanged += gcnew System::EventHandler(this, &MainForm::TiltCenterEdit_ValueChanged);
            // 
            // inputTiltTravlMin
            // 
            this->inputTiltTravlMin->Location = System::Drawing::Point(138, 75);
            this->inputTiltTravlMin->Name = L"inputTiltTravlMin";
            this->inputTiltTravlMin->Size = System::Drawing::Size(46, 20);
            this->inputTiltTravlMin->TabIndex = 138;
            this->inputTiltTravlMin->Text = L"1150";
            this->inputTiltTravlMin->TextChanged += gcnew System::EventHandler(this, &MainForm::TiltMinTravelEdit_ValueChanged);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label3->Location = System::Drawing::Point(146, 21);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(25, 13);
            this->label3->TabIndex = 140;
            this->label3->Text = L"Tilt";
            // 
            // inputTiltTravlMax
            // 
            this->inputTiltTravlMax->Location = System::Drawing::Point(138, 101);
            this->inputTiltTravlMax->Name = L"inputTiltTravlMax";
            this->inputTiltTravlMax->Size = System::Drawing::Size(46, 20);
            this->inputTiltTravlMax->TabIndex = 141;
            this->inputTiltTravlMax->Text = L"1150";
            this->inputTiltTravlMax->TextChanged += gcnew System::EventHandler(this, &MainForm::TiltMaxTravelEdit_ValueChanged);
            // 
            // inputRollCenter
            // 
            this->inputRollCenter->Location = System::Drawing::Point(190, 127);
            this->inputRollCenter->Name = L"inputRollCenter";
            this->inputRollCenter->Size = System::Drawing::Size(46, 20);
            this->inputRollCenter->TabIndex = 146;
            this->inputRollCenter->Text = L"2100";
            this->inputRollCenter->TextChanged += gcnew System::EventHandler(this, &MainForm::RollCenterEdit_ValueChanged);
            // 
            // inputRollTravlMin
            // 
            this->inputRollTravlMin->Location = System::Drawing::Point(190, 75);
            this->inputRollTravlMin->Name = L"inputRollTravlMin";
            this->inputRollTravlMin->Size = System::Drawing::Size(46, 20);
            this->inputRollTravlMin->TabIndex = 145;
            this->inputRollTravlMin->Text = L"1150";
            this->inputRollTravlMin->TextChanged += gcnew System::EventHandler(this, &MainForm::RollMinTravelEdit_ValueChanged);
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(196, 21);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(29, 13);
            this->label7->TabIndex = 147;
            this->label7->Text = L"Roll";
            // 
            // inputRollTravlMax
            // 
            this->inputRollTravlMax->Location = System::Drawing::Point(190, 101);
            this->inputRollTravlMax->Name = L"inputRollTravlMax";
            this->inputRollTravlMax->Size = System::Drawing::Size(46, 20);
            this->inputRollTravlMax->TabIndex = 148;
            this->inputRollTravlMax->Text = L"1150";
            this->inputRollTravlMax->TextChanged += gcnew System::EventHandler(this, &MainForm::RollMaxTravelEdit_ValueChanged);
            // 
            // servoGainRoll
            // 
            this->servoGainRoll->Location = System::Drawing::Point(190, 153);
            this->servoGainRoll->Name = L"servoGainRoll";
            this->servoGainRoll->Size = System::Drawing::Size(46, 20);
            this->servoGainRoll->TabIndex = 150;
            this->servoGainRoll->Text = L"170";
            this->servoGainRoll->TextChanged += gcnew System::EventHandler(this, &MainForm::RollGainEdit_ValueChanged);
            // 
            // inputPanCh
            // 
            this->inputPanCh->FormattingEnabled = true;
            this->inputPanCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
                L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7",
                    L"8", L"9", L"10", L"11", L"12"
            });
            this->inputPanCh->Location = System::Drawing::Point(86, 50);
            this->inputPanCh->Name = L"inputPanCh";
            this->inputPanCh->Size = System::Drawing::Size(45, 21);
            this->inputPanCh->TabIndex = 3;
            this->inputPanCh->Text = L"7";
            // 
            // label2
            // 
            this->label2->Location = System::Drawing::Point(6, 179);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(78, 18);
            this->label2->TabIndex = 151;
            this->label2->Text = L"Reverse";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // inputTiltCh
            // 
            this->inputTiltCh->FormattingEnabled = true;
            this->inputTiltCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
                L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7",
                    L"8", L"9", L"10", L"11", L"12"
            });
            this->inputTiltCh->Location = System::Drawing::Point(138, 50);
            this->inputTiltCh->Name = L"inputTiltCh";
            this->inputTiltCh->Size = System::Drawing::Size(46, 21);
            this->inputTiltCh->TabIndex = 4;
            this->inputTiltCh->Text = L"8";
            // 
            // label4
            // 
            this->label4->Location = System::Drawing::Point(6, 51);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(78, 18);
            this->label4->TabIndex = 152;
            this->label4->Text = L"Channel";
            this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
            // 
            // inputRollCh
            // 
            this->inputRollCh->FormattingEnabled = true;
            this->inputRollCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
                L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7",
                    L"8", L"9", L"10", L"11", L"12"
            });
            this->inputRollCh->Location = System::Drawing::Point(190, 50);
            this->inputRollCh->Name = L"inputRollCh";
            this->inputRollCh->Size = System::Drawing::Size(46, 21);
            this->inputRollCh->TabIndex = 5;
            this->inputRollCh->Text = L"6";
            // 
            // grpBoxServp1
            // 
            this->grpBoxServp1->BackColor = System::Drawing::Color::Transparent;
            this->grpBoxServp1->Controls->Add(this->inputRollCh);
            this->grpBoxServp1->Controls->Add(this->label4);
            this->grpBoxServp1->Controls->Add(this->inputTiltCh);
            this->grpBoxServp1->Controls->Add(this->label2);
            this->grpBoxServp1->Controls->Add(this->inputPanCh);
            this->grpBoxServp1->Controls->Add(this->servoGainRoll);
            this->grpBoxServp1->Controls->Add(this->inputRollTravlMax);
            this->grpBoxServp1->Controls->Add(this->label7);
            this->grpBoxServp1->Controls->Add(this->inputRollTravlMin);
            this->grpBoxServp1->Controls->Add(this->inputRollCenter);
            this->grpBoxServp1->Controls->Add(this->inputTiltTravlMax);
            this->grpBoxServp1->Controls->Add(this->label3);
            this->grpBoxServp1->Controls->Add(this->inputTiltTravlMin);
            this->grpBoxServp1->Controls->Add(this->inputTiltCenter);
            this->grpBoxServp1->Controls->Add(this->label1);
            this->grpBoxServp1->Controls->Add(this->inputPanTravlMax);
            this->grpBoxServp1->Controls->Add(this->Pan_lbl);
            this->grpBoxServp1->Controls->Add(this->lbl_servo_max);
            this->grpBoxServp1->Controls->Add(this->lbl_servo_center);
            this->grpBoxServp1->Controls->Add(this->inputPanTravlMin);
            this->grpBoxServp1->Controls->Add(this->inputPanCenter);
            this->grpBoxServp1->Controls->Add(this->label42);
            this->grpBoxServp1->Controls->Add(this->servoGainTilt);
            this->grpBoxServp1->Controls->Add(this->servoGainPan);
            this->grpBoxServp1->Controls->Add(this->chk_pan);
            this->grpBoxServp1->Controls->Add(this->chk_tilt);
            this->grpBoxServp1->Controls->Add(this->chk_roll);
            this->grpBoxServp1->Enabled = false;
            this->grpBoxServp1->Location = System::Drawing::Point(457, 241);
            this->grpBoxServp1->Name = L"grpBoxServp1";
            this->grpBoxServp1->Size = System::Drawing::Size(256, 229);
            this->grpBoxServp1->TabIndex = 133;
            this->grpBoxServp1->TabStop = false;
            this->grpBoxServp1->Text = L"Servo";
            // 
            // btnClearLog
            // 
            this->btnClearLog->Enabled = false;
            this->btnClearLog->Location = System::Drawing::Point(12, 147);
            this->btnClearLog->Name = L"btnClearLog";
            this->btnClearLog->Size = System::Drawing::Size(93, 23);
            this->btnClearLog->TabIndex = 145;
            this->btnClearLog->Text = L"Clear Log";
            this->btnClearLog->UseVisualStyleBackColor = true;
            this->btnClearLog->Click += gcnew System::EventHandler(this, &MainForm::btnClearLog_Click);
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::SkyBlue;
            this->ClientSize = System::Drawing::Size(729, 731);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->btnClearLog);
            this->Controls->Add(this->grpBoxServp2);
            this->Controls->Add(this->btnCalibrate);
            this->Controls->Add(this->groupBox3);
            this->Controls->Add(this->grpBoxServp1);
            this->Controls->Add(this->btn_update_headtracker);
            this->Controls->Add(this->logViewer);
            this->Controls->Add(this->btn_connect);
            this->Controls->Add(this->dd_comport);
            this->Controls->Add(this->menuStrip1);
            this->Controls->Add(this->groupBoxChart);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MainMenuStrip = this->menuStrip1;
            this->MaximizeBox = false;
            this->Name = L"MainForm";
            this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
            this->Text = L"DIY Headtracker GUI v1.08  -  (Dennis Frie & Friends - 2012-2019)";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
            this->Load += gcnew System::EventHandler(this, &MainForm::Form1_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->groupBox3->ResumeLayout(false);
            this->groupBox3->PerformLayout();
            this->groupBoxChart->ResumeLayout(false);
            this->grpBoxServp2->ResumeLayout(false);
            this->grpBoxServp2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollGainTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltGainTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rollCenterTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tiltCenterTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panCenterTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->panGainTrackBar))->EndInit();
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->grpBoxServp1->ResumeLayout(false);
            this->grpBoxServp1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

private: // variables


private:
    System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
    System::Void UpdateUIFromSettings(HTSETTINGS& Settings);
    System::Void UpdateSettingsFromUI(HTSETTINGS& Settings);
    System::Void btn_connect_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void dataReaderTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void comPortTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void start_HT_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void clear_HT_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btn_update_headtracker_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btnCalibrate_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btnSendManualCmd_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void PanCenterTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanMinTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanMaxTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltCenterTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltMinTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltMaxTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollCenterTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollMinTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollMaxTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanGainTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltGainTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollGainTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void TiltGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void PanGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void RollGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void OnCalWizard_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void OnCalWizardRot_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void OnExportSettingsToFile_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void OnImportSettingsFromFile_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void ManualCmdEdit_OnFocusEnter(System::Object^  sender, System::EventArgs^  e);
    System::Void ManualCmdEdit_OnKeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
    System::Void chartLimit_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e);
    System::Void btnClearLog_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void AppendLog(System::String^ str);
    System::Void SetTBValue(TrackBar^ tb, int v);
    System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
}; // class


} // namespace

