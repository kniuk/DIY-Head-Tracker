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
    /// Summary for Form1
    /// </summary>
    public ref class Form1 : public System::Windows::Forms::Form
    {
    public:
        Form1(void)
        {
            InitializeComponent();

            _CalWizard = gcnew CalWizard;
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }
    
    private: 
    
        System::Windows::Forms::ComboBox^  dd_comport; 
        System::Windows::Forms::Button^  btn_connect;
        System::Windows::Forms::Button^  btn_disconnect;
        System::Windows::Forms::Timer^  timer1;
        System::Windows::Forms::Timer^  comPortTimer;
        System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
        System::Windows::Forms::Label^  Lowpass_text;
        System::Windows::Forms::TextBox^  Serial_output_box;
        System::Windows::Forms::TextBox^  textBox_LP_value;
        System::Windows::Forms::Button^  btn_update_headtracker;
        System::Windows::Forms::Button^  start_HT;
        System::Windows::Forms::Button^  clear_plot;
        System::Windows::Forms::Label^  lbl_servo_max;
        System::Windows::Forms::Label^  lbl_servo_center;
        System::Windows::Forms::Label^  lbl_tilt_roll_gyro_weight;
        System::Windows::Forms::Label^  lbl_gyro_weight_pan;
        System::Windows::Forms::Label^  lbl_filter_pan;
        System::Windows::Forms::TextBox^  textBox_LP_valuePan;
        System::Windows::Forms::TextBox^  GyroWeight_tiltRoll;
        System::Windows::Forms::TextBox^  GyroWeight_pan;
        System::Windows::Forms::TextBox^  inputPanTravlMin;
        System::Windows::Forms::TextBox^  inputPanCenter;
        System::Windows::Forms::Button^  stop_HT;
        System::Windows::Forms::TextBox^  servoGainTilt;
        System::Windows::Forms::TextBox^  servoGainPan;
        System::Windows::Forms::Label^  txt_tiltRoll;
        System::Windows::Forms::Label^  label42;
        System::Windows::Forms::Label^  txt_reverse;
        System::Windows::Forms::CheckBox^  chk_tilt;
        System::Windows::Forms::CheckBox^  chk_roll;
        System::Windows::Forms::CheckBox^  chk_pan;
        System::Windows::Forms::GroupBox^  rollCenter;
        System::Windows::Forms::GroupBox^  groupBox2;
        System::Windows::Forms::Label^  label6;
        System::Windows::Forms::TextBox^  inputRollTravlMax;
        System::Windows::Forms::Label^  label7;
        System::Windows::Forms::Label^  label8;
        System::Windows::Forms::Label^  label9;
        System::Windows::Forms::TextBox^  inputRollTravlMin;
        System::Windows::Forms::TextBox^  inputRollCenter;
        System::Windows::Forms::Label^  label2;
        System::Windows::Forms::TextBox^  inputTiltTravlMax;
        System::Windows::Forms::Label^  label3;
        System::Windows::Forms::Label^  label4;
        System::Windows::Forms::Label^  label5;
        System::Windows::Forms::TextBox^  inputTiltTravlMin;
        System::Windows::Forms::TextBox^  inputTiltCenter;
        System::Windows::Forms::Label^  label1;
        System::Windows::Forms::TextBox^  inputPanTravlMax;
        System::Windows::Forms::Label^  Pan_lbl;
        System::Windows::Forms::Label^  label10;
        System::Windows::Forms::TextBox^  servoGainRoll;
        System::Windows::Forms::GroupBox^  groupBox1;
        System::Windows::Forms::ComboBox^  inputRollCh;
        System::Windows::Forms::ComboBox^  inputTiltCh;
        System::Windows::Forms::ComboBox^  inputPanCh;
        System::Windows::Forms::Label^  label13;
        System::Windows::Forms::Label^  label12;
        System::Windows::Forms::Label^  label11;
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
        System::Windows::Forms::ToolStripMenuItem^  showToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  advancedSettingsToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  basicSettingsToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
        System::Windows::Forms::ToolStripMenuItem^  calibrationWizardToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  exportSettingsToFileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  importSettingsFromFileToolStripMenuItem;
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
            System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
            System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->dd_comport = (gcnew System::Windows::Forms::ComboBox());
            this->btn_connect = (gcnew System::Windows::Forms::Button());
            this->btn_disconnect = (gcnew System::Windows::Forms::Button());
            this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
            this->comPortTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            this->Lowpass_text = (gcnew System::Windows::Forms::Label());
            this->Serial_output_box = (gcnew System::Windows::Forms::TextBox());
            this->textBox_LP_value = (gcnew System::Windows::Forms::TextBox());
            this->btn_update_headtracker = (gcnew System::Windows::Forms::Button());
            this->start_HT = (gcnew System::Windows::Forms::Button());
            this->clear_plot = (gcnew System::Windows::Forms::Button());
            this->lbl_servo_max = (gcnew System::Windows::Forms::Label());
            this->lbl_servo_center = (gcnew System::Windows::Forms::Label());
            this->lbl_tilt_roll_gyro_weight = (gcnew System::Windows::Forms::Label());
            this->lbl_gyro_weight_pan = (gcnew System::Windows::Forms::Label());
            this->lbl_filter_pan = (gcnew System::Windows::Forms::Label());
            this->textBox_LP_valuePan = (gcnew System::Windows::Forms::TextBox());
            this->GyroWeight_tiltRoll = (gcnew System::Windows::Forms::TextBox());
            this->GyroWeight_pan = (gcnew System::Windows::Forms::TextBox());
            this->inputPanTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->inputPanCenter = (gcnew System::Windows::Forms::TextBox());
            this->stop_HT = (gcnew System::Windows::Forms::Button());
            this->servoGainTilt = (gcnew System::Windows::Forms::TextBox());
            this->servoGainPan = (gcnew System::Windows::Forms::TextBox());
            this->txt_tiltRoll = (gcnew System::Windows::Forms::Label());
            this->label42 = (gcnew System::Windows::Forms::Label());
            this->txt_reverse = (gcnew System::Windows::Forms::Label());
            this->chk_tilt = (gcnew System::Windows::Forms::CheckBox());
            this->chk_roll = (gcnew System::Windows::Forms::CheckBox());
            this->chk_pan = (gcnew System::Windows::Forms::CheckBox());
            this->rollCenter = (gcnew System::Windows::Forms::GroupBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->servoGainRoll = (gcnew System::Windows::Forms::TextBox());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->inputRollTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->inputRollTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->inputRollCenter = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->inputTiltTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->inputTiltTravlMin = (gcnew System::Windows::Forms::TextBox());
            this->inputTiltCenter = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->inputPanTravlMax = (gcnew System::Windows::Forms::TextBox());
            this->Pan_lbl = (gcnew System::Windows::Forms::Label());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->inputRollCh = (gcnew System::Windows::Forms::ComboBox());
            this->inputTiltCh = (gcnew System::Windows::Forms::ComboBox());
            this->inputPanCh = (gcnew System::Windows::Forms::ComboBox());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->btnCalibrate = (gcnew System::Windows::Forms::Button());
            this->grpBoxServp2 = (gcnew System::Windows::Forms::GroupBox());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->rollGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->tiltGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->panGainTrackBar = (gcnew System::Windows::Forms::TrackBar());
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
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->exportSettingsToFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->importSettingsFromFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->showToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->advancedSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->basicSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->calibrationWizardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
            this->rollCenter->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->groupBox1->SuspendLayout();
            this->grpBoxServp2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollGainTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltGainTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panGainTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollCenterTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltCenterTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panMaxTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panMinTrackBar))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panCenterTrackBar))->BeginInit();
            this->menuStrip1->SuspendLayout();
            this->SuspendLayout();
            // 
            // dd_comport
            // 
            this->dd_comport->FormattingEnabled = true;
            this->dd_comport->Items->AddRange(gcnew cli::array< System::Object^  >(30) {L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6", 
                L"COM7", L"COM8", L"COM9", L"COM10", L"COM11", L"COM12", L"COM13", L"COM14", L"COM15", L"COM16", L"COM17", L"COM18", L"COM19", 
                L"COM20", L"COM21", L"COM22", L"COM23", L"COM24", L"COM25", L"COM26", L"COM27", L"COM28", L"COM29", L"COM30"});
            this->dd_comport->Location = System::Drawing::Point(12, 43);
            this->dd_comport->Name = L"dd_comport";
            this->dd_comport->Size = System::Drawing::Size(75, 21);
            this->dd_comport->TabIndex = 0;
            this->dd_comport->Text = L"COM1";
            // 
            // btn_connect
            // 
            this->btn_connect->Location = System::Drawing::Point(103, 41);
            this->btn_connect->Name = L"btn_connect";
            this->btn_connect->Size = System::Drawing::Size(75, 23);
            this->btn_connect->TabIndex = 1;
            this->btn_connect->Text = L"&Connect";
            this->btn_connect->UseVisualStyleBackColor = true;
            this->btn_connect->Click += gcnew System::EventHandler(this, &Form1::btn_connect_Click);
            // 
            // btn_disconnect
            // 
            this->btn_disconnect->Enabled = false;
            this->btn_disconnect->Location = System::Drawing::Point(103, 70);
            this->btn_disconnect->Name = L"btn_disconnect";
            this->btn_disconnect->Size = System::Drawing::Size(75, 23);
            this->btn_disconnect->TabIndex = 2;
            this->btn_disconnect->Text = L"&Disconnect";
            this->btn_disconnect->UseVisualStyleBackColor = true;
            this->btn_disconnect->Click += gcnew System::EventHandler(this, &Form1::btn_disconnect_Click);
            // 
            // timer1
            // 
            this->timer1->Interval = 50;
            this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
            // 
            // comPortTimer
            // 
            this->comPortTimer->Enabled = true;
            this->comPortTimer->Interval = 2000;
            this->comPortTimer->Tick += gcnew System::EventHandler(this, &Form1::comPortTimer_Tick);
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
            legend1->Enabled = false;
            legend1->Name = L"Legend1";
            this->chart1->Legends->Add(legend1);
            this->chart1->Location = System::Drawing::Point(-27, 454);
            this->chart1->Name = L"chart1";
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
            this->chart1->Series->Add(series1);
            this->chart1->Series->Add(series2);
            this->chart1->Series->Add(series3);
            this->chart1->Series->Add(series4);
            this->chart1->Size = System::Drawing::Size(577, 176);
            this->chart1->TabIndex = 78;
            this->chart1->Text = L"chart1";
            // 
            // Lowpass_text
            // 
            this->Lowpass_text->AutoSize = true;
            this->Lowpass_text->Location = System::Drawing::Point(6, 23);
            this->Lowpass_text->Name = L"Lowpass_text";
            this->Lowpass_text->Size = System::Drawing::Size(105, 13);
            this->Lowpass_text->TabIndex = 79;
            this->Lowpass_text->Text = L"LP FilterSensorData on tilt/roll [%]";
            // 
            // Serial_output_box
            // 
            this->Serial_output_box->Location = System::Drawing::Point(285, 43);
            this->Serial_output_box->Multiline = true;
            this->Serial_output_box->Name = L"Serial_output_box";
            this->Serial_output_box->Size = System::Drawing::Size(236, 165);
            this->Serial_output_box->TabIndex = 80;
            // 
            // textBox_LP_value
            // 
            this->textBox_LP_value->Location = System::Drawing::Point(6, 39);
            this->textBox_LP_value->Name = L"textBox_LP_value";
            this->textBox_LP_value->Size = System::Drawing::Size(72, 20);
            this->textBox_LP_value->TabIndex = 81;
            this->textBox_LP_value->Text = L"75";
            // 
            // btn_update_headtracker
            // 
            this->btn_update_headtracker->Enabled = false;
            this->btn_update_headtracker->Location = System::Drawing::Point(188, 41);
            this->btn_update_headtracker->Name = L"btn_update_headtracker";
            this->btn_update_headtracker->Size = System::Drawing::Size(91, 23);
            this->btn_update_headtracker->TabIndex = 82;
            this->btn_update_headtracker->Text = L"Store Settings";
            this->btn_update_headtracker->UseVisualStyleBackColor = true;
            this->btn_update_headtracker->Click += gcnew System::EventHandler(this, &Form1::btn_update_headtracker_Click);
            // 
            // start_HT
            // 
            this->start_HT->Enabled = false;
            this->start_HT->Location = System::Drawing::Point(7, 632);
            this->start_HT->Name = L"start_HT";
            this->start_HT->Size = System::Drawing::Size(75, 23);
            this->start_HT->TabIndex = 83;
            this->start_HT->Text = L"Start plot";
            this->start_HT->UseVisualStyleBackColor = true;
            this->start_HT->Click += gcnew System::EventHandler(this, &Form1::start_HT_Click);
            // 
            // clear_plot
            // 
            this->clear_plot->Location = System::Drawing::Point(194, 632);
            this->clear_plot->Name = L"clear_plot";
            this->clear_plot->Size = System::Drawing::Size(75, 23);
            this->clear_plot->TabIndex = 84;
            this->clear_plot->Text = L"Clear plot";
            this->clear_plot->UseVisualStyleBackColor = true;
            this->clear_plot->Click += gcnew System::EventHandler(this, &Form1::clear_plot_Click);
            // 
            // lbl_servo_max
            // 
            this->lbl_servo_max->AutoSize = true;
            this->lbl_servo_max->Location = System::Drawing::Point(17, 53);
            this->lbl_servo_max->Name = L"lbl_servo_max";
            this->lbl_servo_max->Size = System::Drawing::Size(87, 13);
            this->lbl_servo_max->TabIndex = 113;
            this->lbl_servo_max->Text = L"Travel adjust min";
            // 
            // lbl_servo_center
            // 
            this->lbl_servo_center->AutoSize = true;
            this->lbl_servo_center->Location = System::Drawing::Point(17, 146);
            this->lbl_servo_center->Name = L"lbl_servo_center";
            this->lbl_servo_center->Size = System::Drawing::Size(68, 13);
            this->lbl_servo_center->TabIndex = 114;
            this->lbl_servo_center->Text = L"Servo center";
            // 
            // lbl_tilt_roll_gyro_weight
            // 
            this->lbl_tilt_roll_gyro_weight->AutoSize = true;
            this->lbl_tilt_roll_gyro_weight->Location = System::Drawing::Point(123, 23);
            this->lbl_tilt_roll_gyro_weight->Name = L"lbl_tilt_roll_gyro_weight";
            this->lbl_tilt_roll_gyro_weight->Size = System::Drawing::Size(126, 13);
            this->lbl_tilt_roll_gyro_weight->TabIndex = 115;
            this->lbl_tilt_roll_gyro_weight->Text = L"Gyro weight on tilt/roll [%]";
            // 
            // lbl_gyro_weight_pan
            // 
            this->lbl_gyro_weight_pan->AutoSize = true;
            this->lbl_gyro_weight_pan->Location = System::Drawing::Point(123, 71);
            this->lbl_gyro_weight_pan->Name = L"lbl_gyro_weight_pan";
            this->lbl_gyro_weight_pan->Size = System::Drawing::Size(116, 13);
            this->lbl_gyro_weight_pan->TabIndex = 116;
            this->lbl_gyro_weight_pan->Text = L"Gyro weight on pan [%]";
            // 
            // lbl_filter_pan
            // 
            this->lbl_filter_pan->AutoSize = true;
            this->lbl_filter_pan->Location = System::Drawing::Point(6, 71);
            this->lbl_filter_pan->Name = L"lbl_filter_pan";
            this->lbl_filter_pan->Size = System::Drawing::Size(95, 13);
            this->lbl_filter_pan->TabIndex = 117;
            this->lbl_filter_pan->Text = L"LP FilterSensorData on pan [%]";
            // 
            // textBox_LP_valuePan
            // 
            this->textBox_LP_valuePan->Location = System::Drawing::Point(6, 87);
            this->textBox_LP_valuePan->Name = L"textBox_LP_valuePan";
            this->textBox_LP_valuePan->Size = System::Drawing::Size(72, 20);
            this->textBox_LP_valuePan->TabIndex = 118;
            this->textBox_LP_valuePan->Text = L"75";
            // 
            // GyroWeight_tiltRoll
            // 
            this->GyroWeight_tiltRoll->Location = System::Drawing::Point(126, 39);
            this->GyroWeight_tiltRoll->Name = L"GyroWeight_tiltRoll";
            this->GyroWeight_tiltRoll->Size = System::Drawing::Size(72, 20);
            this->GyroWeight_tiltRoll->TabIndex = 119;
            this->GyroWeight_tiltRoll->Text = L"98";
            // 
            // GyroWeight_pan
            // 
            this->GyroWeight_pan->Location = System::Drawing::Point(126, 87);
            this->GyroWeight_pan->Name = L"GyroWeight_pan";
            this->GyroWeight_pan->Size = System::Drawing::Size(72, 20);
            this->GyroWeight_pan->TabIndex = 120;
            this->GyroWeight_pan->Text = L"98";
            // 
            // inputPanTravlMin
            // 
            this->inputPanTravlMin->Location = System::Drawing::Point(20, 69);
            this->inputPanTravlMin->Name = L"inputPanTravlMin";
            this->inputPanTravlMin->Size = System::Drawing::Size(72, 20);
            this->inputPanTravlMin->TabIndex = 121;
            this->inputPanTravlMin->Text = L"1150";
            this->inputPanTravlMin->TextChanged += gcnew System::EventHandler(this, &Form1::PanMinTravelEdit_ValueChanged);
            // 
            // inputPanCenter
            // 
            this->inputPanCenter->Location = System::Drawing::Point(20, 162);
            this->inputPanCenter->Name = L"inputPanCenter";
            this->inputPanCenter->Size = System::Drawing::Size(72, 20);
            this->inputPanCenter->TabIndex = 122;
            this->inputPanCenter->Text = L"2100";
            this->inputPanCenter->TextChanged += gcnew System::EventHandler(this, &Form1::PanCenterEdit_ValueChanged);
            // 
            // stop_HT
            // 
            this->stop_HT->Enabled = false;
            this->stop_HT->Location = System::Drawing::Point(98, 632);
            this->stop_HT->Name = L"stop_HT";
            this->stop_HT->Size = System::Drawing::Size(75, 23);
            this->stop_HT->TabIndex = 123;
            this->stop_HT->Text = L"Stop plot";
            this->stop_HT->UseVisualStyleBackColor = true;
            this->stop_HT->Click += gcnew System::EventHandler(this, &Form1::stop_HT_Click);
            // 
            // servoGainTilt
            // 
            this->servoGainTilt->Location = System::Drawing::Point(133, 207);
            this->servoGainTilt->Name = L"servoGainTilt";
            this->servoGainTilt->Size = System::Drawing::Size(72, 20);
            this->servoGainTilt->TabIndex = 125;
            this->servoGainTilt->Text = L"170";
            this->servoGainTilt->TextChanged += gcnew System::EventHandler(this, &Form1::TiltGainEdit_ValueChanged);
            // 
            // servoGainPan
            // 
            this->servoGainPan->Location = System::Drawing::Point(20, 207);
            this->servoGainPan->Name = L"servoGainPan";
            this->servoGainPan->Size = System::Drawing::Size(72, 20);
            this->servoGainPan->TabIndex = 126;
            this->servoGainPan->Text = L"170";
            this->servoGainPan->TextChanged += gcnew System::EventHandler(this, &Form1::PanGainEdit_ValueChanged);
            // 
            // txt_tiltRoll
            // 
            this->txt_tiltRoll->AutoSize = true;
            this->txt_tiltRoll->Location = System::Drawing::Point(129, 191);
            this->txt_tiltRoll->Name = L"txt_tiltRoll";
            this->txt_tiltRoll->Size = System::Drawing::Size(46, 13);
            this->txt_tiltRoll->TabIndex = 127;
            this->txt_tiltRoll->Text = L"Tilt Gain";
            // 
            // label42
            // 
            this->label42->AutoSize = true;
            this->label42->Location = System::Drawing::Point(17, 191);
            this->label42->Name = L"label42";
            this->label42->Size = System::Drawing::Size(49, 13);
            this->label42->TabIndex = 128;
            this->label42->Text = L"Pan gain";
            // 
            // txt_reverse
            // 
            this->txt_reverse->AutoSize = true;
            this->txt_reverse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->txt_reverse->Location = System::Drawing::Point(442, 51);
            this->txt_reverse->Name = L"txt_reverse";
            this->txt_reverse->Size = System::Drawing::Size(54, 13);
            this->txt_reverse->TabIndex = 129;
            this->txt_reverse->Text = L"Reverse";
            // 
            // chk_tilt
            // 
            this->chk_tilt->AutoSize = true;
            this->chk_tilt->Location = System::Drawing::Point(445, 100);
            this->chk_tilt->Name = L"chk_tilt";
            this->chk_tilt->Size = System::Drawing::Size(40, 17);
            this->chk_tilt->TabIndex = 130;
            this->chk_tilt->Text = L"Tilt";
            this->chk_tilt->UseVisualStyleBackColor = true;
            // 
            // chk_roll
            // 
            this->chk_roll->AutoSize = true;
            this->chk_roll->Location = System::Drawing::Point(445, 123);
            this->chk_roll->Name = L"chk_roll";
            this->chk_roll->Size = System::Drawing::Size(44, 17);
            this->chk_roll->TabIndex = 131;
            this->chk_roll->Text = L"Roll";
            this->chk_roll->UseVisualStyleBackColor = true;
            // 
            // chk_pan
            // 
            this->chk_pan->AutoSize = true;
            this->chk_pan->Location = System::Drawing::Point(445, 77);
            this->chk_pan->Name = L"chk_pan";
            this->chk_pan->Size = System::Drawing::Size(45, 17);
            this->chk_pan->TabIndex = 132;
            this->chk_pan->Text = L"Pan";
            this->chk_pan->UseVisualStyleBackColor = true;
            // 
            // rollCenter
            // 
            this->rollCenter->BackColor = System::Drawing::Color::Transparent;
            this->rollCenter->Controls->Add(this->label10);
            this->rollCenter->Controls->Add(this->servoGainRoll);
            this->rollCenter->Controls->Add(this->label6);
            this->rollCenter->Controls->Add(this->inputRollTravlMax);
            this->rollCenter->Controls->Add(this->label7);
            this->rollCenter->Controls->Add(this->label8);
            this->rollCenter->Controls->Add(this->label9);
            this->rollCenter->Controls->Add(this->inputRollTravlMin);
            this->rollCenter->Controls->Add(this->inputRollCenter);
            this->rollCenter->Controls->Add(this->label2);
            this->rollCenter->Controls->Add(this->inputTiltTravlMax);
            this->rollCenter->Controls->Add(this->label3);
            this->rollCenter->Controls->Add(this->label4);
            this->rollCenter->Controls->Add(this->label5);
            this->rollCenter->Controls->Add(this->inputTiltTravlMin);
            this->rollCenter->Controls->Add(this->inputTiltCenter);
            this->rollCenter->Controls->Add(this->label1);
            this->rollCenter->Controls->Add(this->inputPanTravlMax);
            this->rollCenter->Controls->Add(this->Pan_lbl);
            this->rollCenter->Controls->Add(this->txt_tiltRoll);
            this->rollCenter->Controls->Add(this->lbl_servo_max);
            this->rollCenter->Controls->Add(this->lbl_servo_center);
            this->rollCenter->Controls->Add(this->inputPanTravlMin);
            this->rollCenter->Controls->Add(this->inputPanCenter);
            this->rollCenter->Controls->Add(this->label42);
            this->rollCenter->Controls->Add(this->servoGainTilt);
            this->rollCenter->Controls->Add(this->servoGainPan);
            this->rollCenter->Location = System::Drawing::Point(541, 187);
            this->rollCenter->Name = L"rollCenter";
            this->rollCenter->Size = System::Drawing::Size(255, 463);
            this->rollCenter->TabIndex = 133;
            this->rollCenter->TabStop = false;
            this->rollCenter->Text = L"Servo";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Location = System::Drawing::Point(18, 411);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(48, 13);
            this->label10->TabIndex = 151;
            this->label10->Text = L"Roll gain";
            // 
            // servoGainRoll
            // 
            this->servoGainRoll->Location = System::Drawing::Point(21, 427);
            this->servoGainRoll->Name = L"servoGainRoll";
            this->servoGainRoll->Size = System::Drawing::Size(72, 20);
            this->servoGainRoll->TabIndex = 150;
            this->servoGainRoll->Text = L"170";
            this->servoGainRoll->TextChanged += gcnew System::EventHandler(this, &Form1::RollGainEdit_ValueChanged);
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(17, 318);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(90, 13);
            this->label6->TabIndex = 149;
            this->label6->Text = L"Travel adjust max";
            // 
            // inputRollTravlMax
            // 
            this->inputRollTravlMax->Location = System::Drawing::Point(20, 334);
            this->inputRollTravlMax->Name = L"inputRollTravlMax";
            this->inputRollTravlMax->Size = System::Drawing::Size(72, 20);
            this->inputRollTravlMax->TabIndex = 148;
            this->inputRollTravlMax->Text = L"1150";
            this->inputRollTravlMax->TextChanged += gcnew System::EventHandler(this, &Form1::RollMaxTravelEdit_ValueChanged);
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label7->Location = System::Drawing::Point(17, 242);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(61, 13);
            this->label7->TabIndex = 147;
            this->label7->Text = L"Roll        ";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(17, 271);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(87, 13);
            this->label8->TabIndex = 143;
            this->label8->Text = L"Travel adjust min";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(17, 364);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(68, 13);
            this->label9->TabIndex = 144;
            this->label9->Text = L"Servo center";
            // 
            // inputRollTravlMin
            // 
            this->inputRollTravlMin->Location = System::Drawing::Point(20, 287);
            this->inputRollTravlMin->Name = L"inputRollTravlMin";
            this->inputRollTravlMin->Size = System::Drawing::Size(72, 20);
            this->inputRollTravlMin->TabIndex = 145;
            this->inputRollTravlMin->Text = L"1150";
            this->inputRollTravlMin->TextChanged += gcnew System::EventHandler(this, &Form1::RollMinTravelEdit_ValueChanged);
            // 
            // inputRollCenter
            // 
            this->inputRollCenter->Location = System::Drawing::Point(20, 380);
            this->inputRollCenter->Name = L"inputRollCenter";
            this->inputRollCenter->Size = System::Drawing::Size(72, 20);
            this->inputRollCenter->TabIndex = 146;
            this->inputRollCenter->Text = L"2100";
            this->inputRollCenter->TextChanged += gcnew System::EventHandler(this, &Form1::RollCenterEdit_ValueChanged);
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(128, 100);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(90, 13);
            this->label2->TabIndex = 142;
            this->label2->Text = L"Travel adjust max";
            // 
            // inputTiltTravlMax
            // 
            this->inputTiltTravlMax->Location = System::Drawing::Point(131, 116);
            this->inputTiltTravlMax->Name = L"inputTiltTravlMax";
            this->inputTiltTravlMax->Size = System::Drawing::Size(72, 20);
            this->inputTiltTravlMax->TabIndex = 141;
            this->inputTiltTravlMax->Text = L"1150";
            this->inputTiltTravlMax->TextChanged += gcnew System::EventHandler(this, &Form1::TiltMaxTravelEdit_ValueChanged);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label3->Location = System::Drawing::Point(128, 24);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(65, 13);
            this->label3->TabIndex = 140;
            this->label3->Text = L"Tilt          ";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(128, 53);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(87, 13);
            this->label4->TabIndex = 136;
            this->label4->Text = L"Travel adjust min";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(128, 146);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(68, 13);
            this->label5->TabIndex = 137;
            this->label5->Text = L"Servo center";
            // 
            // inputTiltTravlMin
            // 
            this->inputTiltTravlMin->Location = System::Drawing::Point(131, 69);
            this->inputTiltTravlMin->Name = L"inputTiltTravlMin";
            this->inputTiltTravlMin->Size = System::Drawing::Size(72, 20);
            this->inputTiltTravlMin->TabIndex = 138;
            this->inputTiltTravlMin->Text = L"1150";
            this->inputTiltTravlMin->TextChanged += gcnew System::EventHandler(this, &Form1::TiltMinTravelEdit_ValueChanged);
            // 
            // inputTiltCenter
            // 
            this->inputTiltCenter->Location = System::Drawing::Point(131, 162);
            this->inputTiltCenter->Name = L"inputTiltCenter";
            this->inputTiltCenter->Size = System::Drawing::Size(72, 20);
            this->inputTiltCenter->TabIndex = 139;
            this->inputTiltCenter->Text = L"2100";
            this->inputTiltCenter->TextChanged += gcnew System::EventHandler(this, &Form1::TiltCenterEdit_ValueChanged);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(17, 100);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(90, 13);
            this->label1->TabIndex = 135;
            this->label1->Text = L"Travel adjust max";
            // 
            // inputPanTravlMax
            // 
            this->inputPanTravlMax->Location = System::Drawing::Point(20, 116);
            this->inputPanTravlMax->Name = L"inputPanTravlMax";
            this->inputPanTravlMax->Size = System::Drawing::Size(72, 20);
            this->inputPanTravlMax->TabIndex = 134;
            this->inputPanTravlMax->Text = L"1150";
            this->inputPanTravlMax->TextChanged += gcnew System::EventHandler(this, &Form1::PanMaxTravelEdit_ValueChanged);
            // 
            // Pan_lbl
            // 
            this->Pan_lbl->AutoSize = true;
            this->Pan_lbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->Pan_lbl->Location = System::Drawing::Point(17, 24);
            this->Pan_lbl->Name = L"Pan_lbl";
            this->Pan_lbl->Size = System::Drawing::Size(61, 13);
            this->Pan_lbl->TabIndex = 133;
            this->Pan_lbl->Text = L"Pan        ";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->Lowpass_text);
            this->groupBox2->Controls->Add(this->textBox_LP_value);
            this->groupBox2->Controls->Add(this->lbl_tilt_roll_gyro_weight);
            this->groupBox2->Controls->Add(this->GyroWeight_pan);
            this->groupBox2->Controls->Add(this->lbl_gyro_weight_pan);
            this->groupBox2->Controls->Add(this->GyroWeight_tiltRoll);
            this->groupBox2->Controls->Add(this->lbl_filter_pan);
            this->groupBox2->Controls->Add(this->textBox_LP_valuePan);
            this->groupBox2->Location = System::Drawing::Point(540, 43);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(256, 115);
            this->groupBox2->TabIndex = 134;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"Advanced Parameters";
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->inputRollCh);
            this->groupBox1->Controls->Add(this->inputTiltCh);
            this->groupBox1->Controls->Add(this->inputPanCh);
            this->groupBox1->Controls->Add(this->label13);
            this->groupBox1->Controls->Add(this->label12);
            this->groupBox1->Controls->Add(this->label11);
            this->groupBox1->Location = System::Drawing::Point(13, 114);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(256, 85);
            this->groupBox1->TabIndex = 136;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"PPM channels";
            // 
            // inputRollCh
            // 
            this->inputRollCh->FormattingEnabled = true;
            this->inputRollCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
                L"8", L"9", L"10", L"11", L"12"});
            this->inputRollCh->Location = System::Drawing::Point(170, 39);
            this->inputRollCh->Name = L"inputRollCh";
            this->inputRollCh->Size = System::Drawing::Size(58, 21);
            this->inputRollCh->TabIndex = 5;
            this->inputRollCh->Text = L"6";
            // 
            // inputTiltCh
            // 
            this->inputTiltCh->FormattingEnabled = true;
            this->inputTiltCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
                L"8", L"9", L"10", L"11", L"12"});
            this->inputTiltCh->Location = System::Drawing::Point(89, 39);
            this->inputTiltCh->Name = L"inputTiltCh";
            this->inputTiltCh->Size = System::Drawing::Size(58, 21);
            this->inputTiltCh->TabIndex = 4;
            this->inputTiltCh->Text = L"8";
            // 
            // inputPanCh
            // 
            this->inputPanCh->FormattingEnabled = true;
            this->inputPanCh->Items->AddRange(gcnew cli::array< System::Object^  >(13) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
                L"8", L"9", L"10", L"11", L"12"});
            this->inputPanCh->Location = System::Drawing::Point(10, 38);
            this->inputPanCh->Name = L"inputPanCh";
            this->inputPanCh->Size = System::Drawing::Size(58, 21);
            this->inputPanCh->TabIndex = 3;
            this->inputPanCh->Text = L"7";
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Location = System::Drawing::Point(167, 23);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(43, 13);
            this->label13->TabIndex = 2;
            this->label13->Text = L"Roll ch:";
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Location = System::Drawing::Point(86, 23);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(39, 13);
            this->label12->TabIndex = 1;
            this->label12->Text = L"Tilt ch:";
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(6, 23);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(44, 13);
            this->label11->TabIndex = 0;
            this->label11->Text = L"Pan ch:";
            // 
            // btnCalibrate
            // 
            this->btnCalibrate->Enabled = false;
            this->btnCalibrate->Location = System::Drawing::Point(188, 70);
            this->btnCalibrate->Name = L"btnCalibrate";
            this->btnCalibrate->Size = System::Drawing::Size(91, 23);
            this->btnCalibrate->TabIndex = 137;
            this->btnCalibrate->Text = L"Calibrate";
            this->btnCalibrate->UseVisualStyleBackColor = true;
            this->btnCalibrate->Click += gcnew System::EventHandler(this, &Form1::btnCalibrate_Click);
            // 
            // grpBoxServp2
            // 
            this->grpBoxServp2->Controls->Add(this->label29);
            this->grpBoxServp2->Controls->Add(this->rollGainTrackBar);
            this->grpBoxServp2->Controls->Add(this->label28);
            this->grpBoxServp2->Controls->Add(this->tiltGainTrackBar);
            this->grpBoxServp2->Controls->Add(this->label25);
            this->grpBoxServp2->Controls->Add(this->label27);
            this->grpBoxServp2->Controls->Add(this->panGainTrackBar);
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
            this->grpBoxServp2->Controls->Add(this->txt_reverse);
            this->grpBoxServp2->Controls->Add(this->chk_pan);
            this->grpBoxServp2->Controls->Add(this->chk_roll);
            this->grpBoxServp2->Controls->Add(this->chk_tilt);
            this->grpBoxServp2->Location = System::Drawing::Point(13, 214);
            this->grpBoxServp2->Name = L"grpBoxServp2";
            this->grpBoxServp2->Size = System::Drawing::Size(512, 229);
            this->grpBoxServp2->TabIndex = 138;
            this->grpBoxServp2->TabStop = false;
            this->grpBoxServp2->Text = L"Servo";
            // 
            // label29
            // 
            this->label29->AutoSize = true;
            this->label29->Location = System::Drawing::Point(331, 168);
            this->label29->Name = L"label29";
            this->label29->Size = System::Drawing::Size(29, 13);
            this->label29->TabIndex = 178;
            this->label29->Text = L"Gain";
            // 
            // rollGainTrackBar
            // 
            this->rollGainTrackBar->Location = System::Drawing::Point(288, 179);
            this->rollGainTrackBar->Maximum = 500;
            this->rollGainTrackBar->Name = L"rollGainTrackBar";
            this->rollGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollGainTrackBar->TabIndex = 177;
            this->rollGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollGainTrackBar->Value = 170;
            this->rollGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::RollGainTrackBar_ValueChanged);
            // 
            // label28
            // 
            this->label28->AutoSize = true;
            this->label28->Location = System::Drawing::Point(190, 168);
            this->label28->Name = L"label28";
            this->label28->Size = System::Drawing::Size(29, 13);
            this->label28->TabIndex = 176;
            this->label28->Text = L"Gain";
            // 
            // tiltGainTrackBar
            // 
            this->tiltGainTrackBar->Location = System::Drawing::Point(147, 179);
            this->tiltGainTrackBar->Maximum = 500;
            this->tiltGainTrackBar->Name = L"tiltGainTrackBar";
            this->tiltGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltGainTrackBar->TabIndex = 175;
            this->tiltGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltGainTrackBar->Value = 170;
            this->tiltGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::TiltGainTrackBar_ValueChanged);
            // 
            // label25
            // 
            this->label25->AutoSize = true;
            this->label25->Location = System::Drawing::Point(54, 168);
            this->label25->Name = L"label25";
            this->label25->Size = System::Drawing::Size(29, 13);
            this->label25->TabIndex = 174;
            this->label25->Text = L"Gain";
            // 
            // label27
            // 
            this->label27->AutoSize = true;
            this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label27->Location = System::Drawing::Point(305, 24);
            this->label27->Name = L"label27";
            this->label27->Size = System::Drawing::Size(61, 13);
            this->label27->TabIndex = 152;
            this->label27->Text = L"Roll        ";
            // 
            // panGainTrackBar
            // 
            this->panGainTrackBar->Location = System::Drawing::Point(11, 179);
            this->panGainTrackBar->Maximum = 500;
            this->panGainTrackBar->Name = L"panGainTrackBar";
            this->panGainTrackBar->Size = System::Drawing::Size(130, 45);
            this->panGainTrackBar->TabIndex = 173;
            this->panGainTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panGainTrackBar->Value = 170;
            this->panGainTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::PanGainTrackBar_ValueChanged);
            // 
            // label26
            // 
            this->label26->AutoSize = true;
            this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label26->Location = System::Drawing::Point(160, 24);
            this->label26->Name = L"label26";
            this->label26->Size = System::Drawing::Size(65, 13);
            this->label26->TabIndex = 152;
            this->label26->Text = L"Tilt          ";
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
            this->label22->Location = System::Drawing::Point(331, 125);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(38, 13);
            this->label22->TabIndex = 171;
            this->label22->Text = L"<- End";
            // 
            // rollMaxTrackBar
            // 
            this->rollMaxTrackBar->Location = System::Drawing::Point(288, 136);
            this->rollMaxTrackBar->Maximum = 1150;
            this->rollMaxTrackBar->Name = L"rollMaxTrackBar";
            this->rollMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollMaxTrackBar->TabIndex = 170;
            this->rollMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollMaxTrackBar->Value = 1150;
            this->rollMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::RollMaxTrackBar_ValueChanged);
            // 
            // label23
            // 
            this->label23->AutoSize = true;
            this->label23->Location = System::Drawing::Point(331, 83);
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
            this->rollMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::RollMinTrackBar_ValueChanged);
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Location = System::Drawing::Point(331, 41);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(38, 13);
            this->label24->TabIndex = 167;
            this->label24->Text = L"Center";
            // 
            // rollCenterTrackBar
            // 
            this->rollCenterTrackBar->Location = System::Drawing::Point(288, 51);
            this->rollCenterTrackBar->Maximum = 400;
            this->rollCenterTrackBar->Minimum = -400;
            this->rollCenterTrackBar->Name = L"rollCenterTrackBar";
            this->rollCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->rollCenterTrackBar->TabIndex = 166;
            this->rollCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->rollCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::RollCenterTrackBar_ValueChanged);
            // 
            // label19
            // 
            this->label19->AutoSize = true;
            this->label19->Location = System::Drawing::Point(190, 125);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(38, 13);
            this->label19->TabIndex = 165;
            this->label19->Text = L"<- End";
            // 
            // tiltMaxTrackBar
            // 
            this->tiltMaxTrackBar->Location = System::Drawing::Point(147, 136);
            this->tiltMaxTrackBar->Maximum = 1150;
            this->tiltMaxTrackBar->Name = L"tiltMaxTrackBar";
            this->tiltMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltMaxTrackBar->TabIndex = 164;
            this->tiltMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltMaxTrackBar->Value = 1150;
            this->tiltMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::TiltMaxTrackBar_ValueChanged);
            // 
            // label20
            // 
            this->label20->AutoSize = true;
            this->label20->Location = System::Drawing::Point(190, 83);
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
            this->tiltMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::TiltMinTrackBar_ValueChanged);
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->Location = System::Drawing::Point(190, 41);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(38, 13);
            this->label21->TabIndex = 161;
            this->label21->Text = L"Center";
            // 
            // tiltCenterTrackBar
            // 
            this->tiltCenterTrackBar->Location = System::Drawing::Point(147, 51);
            this->tiltCenterTrackBar->Maximum = 400;
            this->tiltCenterTrackBar->Minimum = -400;
            this->tiltCenterTrackBar->Name = L"tiltCenterTrackBar";
            this->tiltCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->tiltCenterTrackBar->TabIndex = 160;
            this->tiltCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->tiltCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::TiltCenterTrackBar_ValueChanged);
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Location = System::Drawing::Point(54, 125);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(38, 13);
            this->label17->TabIndex = 159;
            this->label17->Text = L"<- End";
            // 
            // panMaxTrackBar
            // 
            this->panMaxTrackBar->Location = System::Drawing::Point(11, 136);
            this->panMaxTrackBar->Maximum = 1150;
            this->panMaxTrackBar->Name = L"panMaxTrackBar";
            this->panMaxTrackBar->Size = System::Drawing::Size(130, 45);
            this->panMaxTrackBar->TabIndex = 158;
            this->panMaxTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panMaxTrackBar->Value = 1150;
            this->panMaxTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::PanMaxTrackBar_ValueChanged);
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->Location = System::Drawing::Point(54, 83);
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
            this->panMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::PanMinTrackBar_ValueChanged);
            // 
            // LblPanCenter
            // 
            this->LblPanCenter->AutoSize = true;
            this->LblPanCenter->Location = System::Drawing::Point(54, 41);
            this->LblPanCenter->Name = L"LblPanCenter";
            this->LblPanCenter->Size = System::Drawing::Size(38, 13);
            this->LblPanCenter->TabIndex = 153;
            this->LblPanCenter->Text = L"Center";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->label14->Location = System::Drawing::Point(18, 24);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(61, 13);
            this->label14->TabIndex = 152;
            this->label14->Text = L"Pan        ";
            // 
            // panCenterTrackBar
            // 
            this->panCenterTrackBar->Location = System::Drawing::Point(11, 51);
            this->panCenterTrackBar->Maximum = 400;
            this->panCenterTrackBar->Minimum = -400;
            this->panCenterTrackBar->Name = L"panCenterTrackBar";
            this->panCenterTrackBar->Size = System::Drawing::Size(130, 45);
            this->panCenterTrackBar->TabIndex = 140;
            this->panCenterTrackBar->TickStyle = System::Windows::Forms::TickStyle::None;
            this->panCenterTrackBar->ValueChanged += gcnew System::EventHandler(this, &Form1::PanCenterTrackBar_ValueChanged);
            // 
            // menuStrip1
            // 
            this->menuStrip1->BackColor = System::Drawing::Color::WhiteSmoke;
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->fileToolStripMenuItem, 
                this->showToolStripMenuItem, this->toolsToolStripMenuItem, this->helpToolStripMenuItem});
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(810, 24);
            this->menuStrip1->TabIndex = 139;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->exportSettingsToFileToolStripMenuItem, 
                this->importSettingsFromFileToolStripMenuItem, this->exitToolStripMenuItem});
            this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
            this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
            this->fileToolStripMenuItem->Text = L"File";
            // 
            // exportSettingsToFileToolStripMenuItem
            // 
            this->exportSettingsToFileToolStripMenuItem->Name = L"exportSettingsToFileToolStripMenuItem";
            this->exportSettingsToFileToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->exportSettingsToFileToolStripMenuItem->Text = L"Export Settings to File...";
            this->exportSettingsToFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnExportSettingsToFile_Menu);
            // 
            // importSettingsFromFileToolStripMenuItem
            // 
            this->importSettingsFromFileToolStripMenuItem->Name = L"importSettingsFromFileToolStripMenuItem";
            this->importSettingsFromFileToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->importSettingsFromFileToolStripMenuItem->Text = L"Import Settings From File...";
            this->importSettingsFromFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnImportSettingsFromFile_Menu);
            // 
            // exitToolStripMenuItem
            // 
            this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
            this->exitToolStripMenuItem->Size = System::Drawing::Size(216, 22);
            this->exitToolStripMenuItem->Text = L"Exit";
            this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
            // 
            // showToolStripMenuItem
            // 
            this->showToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->advancedSettingsToolStripMenuItem, 
                this->basicSettingsToolStripMenuItem});
            this->showToolStripMenuItem->Name = L"showToolStripMenuItem";
            this->showToolStripMenuItem->Size = System::Drawing::Size(44, 20);
            this->showToolStripMenuItem->Text = L"View";
            // 
            // advancedSettingsToolStripMenuItem
            // 
            this->advancedSettingsToolStripMenuItem->Name = L"advancedSettingsToolStripMenuItem";
            this->advancedSettingsToolStripMenuItem->Size = System::Drawing::Size(171, 22);
            this->advancedSettingsToolStripMenuItem->Text = L"Advanced settings";
            this->advancedSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::advancedSettingsToolStripMenuItem_Click);
            // 
            // basicSettingsToolStripMenuItem
            // 
            this->basicSettingsToolStripMenuItem->Enabled = false;
            this->basicSettingsToolStripMenuItem->Name = L"basicSettingsToolStripMenuItem";
            this->basicSettingsToolStripMenuItem->Size = System::Drawing::Size(171, 22);
            this->basicSettingsToolStripMenuItem->Text = L"Basic settings";
            this->basicSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::basicSettingsToolStripMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->calibrationWizardToolStripMenuItem});
            this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
            this->toolsToolStripMenuItem->Size = System::Drawing::Size(48, 20);
            this->toolsToolStripMenuItem->Text = L"Tools";
            // 
            // calibrationWizardToolStripMenuItem
            // 
            this->calibrationWizardToolStripMenuItem->Enabled = false;
            this->calibrationWizardToolStripMenuItem->Name = L"calibrationWizardToolStripMenuItem";
            this->calibrationWizardToolStripMenuItem->Size = System::Drawing::Size(180, 22);
            this->calibrationWizardToolStripMenuItem->Text = L"Calibration Wizard...";
            this->calibrationWizardToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OnCalWizard_Menu);
            // 
            // helpToolStripMenuItem
            // 
            this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
            this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
            this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
            this->helpToolStripMenuItem->Text = L"Help";
            // 
            // aboutToolStripMenuItem
            // 
            this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
            this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
            this->aboutToolStripMenuItem->Text = L"About";
            this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::SkyBlue;
            this->ClientSize = System::Drawing::Size(810, 662);
            this->Controls->Add(this->grpBoxServp2);
            this->Controls->Add(this->btnCalibrate);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->rollCenter);
            this->Controls->Add(this->stop_HT);
            this->Controls->Add(this->clear_plot);
            this->Controls->Add(this->start_HT);
            this->Controls->Add(this->btn_update_headtracker);
            this->Controls->Add(this->Serial_output_box);
            this->Controls->Add(this->chart1);
            this->Controls->Add(this->btn_disconnect);
            this->Controls->Add(this->btn_connect);
            this->Controls->Add(this->dd_comport);
            this->Controls->Add(this->menuStrip1);
            this->MainMenuStrip = this->menuStrip1;
            this->MaximizeBox = false;
            this->Name = L"Form1";
            this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
            this->Text = L"DIY Headtraker GUI v0.80  -  (Dennis Frie - 2012)";
            this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
            this->rollCenter->ResumeLayout(false);
            this->rollCenter->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->grpBoxServp2->ResumeLayout(false);
            this->grpBoxServp2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollGainTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltGainTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panGainTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->rollCenterTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tiltCenterTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panMaxTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panMinTrackBar))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->panCenterTrackBar))->EndInit();
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

private: // variables

    CalWizard^ _CalWizard;

private:
    System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
    System::Void RetrieveSettings();
    System::Void UpdateUIFromSettings(HTSETTINGS& Settings);
    System::Void UpdateSettingsFromUI(HTSETTINGS& Settings);
    System::Void btn_connect_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btn_disconnect_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void comPortTimer_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void start_HT_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void clear_plot_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btn_update_headtracker_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void stop_HT_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void btnCalibrate_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
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
    System::Void advancedSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void basicSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void OnCalWizard_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void OnExportSettingsToFile_Menu(System::Object^  sender, System::EventArgs^  e);
    System::Void OnImportSettingsFromFile_Menu(System::Object^  sender, System::EventArgs^  e);
}; // class



} // namespace

