//--------------------------------------------------------------------------------------
// File:    MainForm.cpp (C++/CLI)
//    Implements the main form handlers.
//
// Hist:    2012 - Dennis Frie - initial creation.
//          4/15/13 - Mark Mansur - initial update with settings persistence,
//              calibration wizard, code cleanup, and other changes.
//--------------------------------------------------------------------------------------

#include "stdafx.h"
#include "MainForm.h"
#include "HeadTrackerHardware.h"
#include "CalWizard.h"

using namespace HeadTrackerGUI;
using namespace System::Windows::Forms;
using namespace System;

#define MAX_LINES           13
#define START_HT_TEXT       L"Start plot"
#define STOP_HT_TEXT        L"Stop plot"


HTSETTINGS HTSettings;

float SerialData[25];
int Serialindex = 0;
long  chartX= 0;

// Called by system at app startup. Program entry point.
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    TrackerWrap::Tracker = gcnew HeadTracker();
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew MainForm());
	return 0;
}

System::Void LogFlushHandler() {
    MainForm::mainForm->LogFlush();
}
System::Void LogCharHandler(int ch ) {
    MainForm::mainForm->Log( ch );
}
System::Void LogHandler(String^ line) {
    MainForm::mainForm->Log(line);
}

// Form initialization handler
System::Void MainForm::Form1_Load(System::Object^  sender, System::EventArgs^  e) {
    this->Text = String::Format("DIY Headtracker GUI v1.08 [{0}] - Dennis Frie & Friends", String(__DATE__).Replace("  ", " ") );

    TrackerWrap::Tracker->LogFlush += gcnew LogFlushDelegate( &LogFlushHandler );
    TrackerWrap::Tracker->LogChar += gcnew LogCharDelegate(&LogCharHandler);
    TrackerWrap::Tracker->Log += gcnew LogDelegate(&LogHandler);

    dd_bluetooth->SelectedIndex = 0;
    chartLimit->SelectedIndex = 1;
    chartLimit_SelectionChangeCommitted(this, nullptr);
    // Fill in Serial ports
    comPortTimer_Tick( this, nullptr );
}

System::Void MainForm::SetTBValue(TrackBar^ tb, int v) {
    if (tb != nullptr) {
        if (v < tb->Minimum) v = tb->Minimum;
        if (v > tb->Maximum) v = tb->Maximum;
        tb->Value = v;
    }
}

// Updates the UI state with the specified settings
System::Void MainForm::UpdateUIFromSettings(HTSETTINGS& Settings) {
    try {
        textBox_LP_value->Text = Convert::ToString(Settings.LPTiltRoll, 10);
        textBox_LP_valuePan->Text = Convert::ToString(Settings.LPPan, 10);
        GyroWeight_tiltRoll->Text = Convert::ToString(Settings.GyroWeightTiltRoll, 10);
        GyroWeight_pan->Text = Convert::ToString(Settings.GyroWeightPan, 10);
        servoGainPan->Text = Convert::ToString(Settings.ServoGainPan, 10);
        servoGainTilt->Text = Convert::ToString(Settings.ServoGainTilt, 10);
        servoGainRoll->Text = Convert::ToString(Settings.ServoGainRoll, 10);

        // Channels
        inputPanCh->SelectedIndex = Settings.PanCh;
        inputTiltCh->SelectedIndex = Settings.TiltCh;
        inputRollCh->SelectedIndex = Settings.RollCh;

        chk_tilt->Checked = ((Settings.ServoReverse & HT_TILT_REVERSE_BIT) != 0);
        chk_roll->Checked = ((Settings.ServoReverse & HT_ROLL_REVERSE_BIT) != 0);
        chk_pan->Checked = ((Settings.ServoReverse & HT_PAN_REVERSE_BIT) != 0);


        // Pulse values
        inputPanCenter->Text = Convert::ToString(Settings.PanCenter, 10);
        inputPanTravlMin->Text = Convert::ToString(Settings.PanMin, 10);
        inputPanTravlMax->Text = Convert::ToString(Settings.PanMax, 10);
        inputTiltCenter->Text = Convert::ToString(Settings.TiltCenter, 10);
        inputTiltTravlMin->Text = Convert::ToString(Settings.TiltMin, 10);
        inputTiltTravlMax->Text = Convert::ToString(Settings.TiltMax, 10);
        inputRollCenter->Text = Convert::ToString(Settings.RollCenter, 10);
        inputRollTravlMin->Text = Convert::ToString(Settings.RollMin, 10);
        inputRollTravlMax->Text = Convert::ToString(Settings.RollMax, 10);

        // Track bars
        SetTBValue( panGainTrackBar, Settings.ServoGainPan);
        SetTBValue( tiltGainTrackBar, Settings.ServoGainTilt);
        SetTBValue( rollGainTrackBar, Settings.ServoGainRoll);
        SetTBValue( panCenterTrackBar, Settings.PanCenter - 2100);
        SetTBValue( panMinTrackBar, Settings.PanMin - (Settings.PanCenter - 2100));
        SetTBValue( panMaxTrackBar, Settings.PanMax + (Settings.PanCenter - 2100));

        SetTBValue( tiltCenterTrackBar, Settings.TiltCenter - 2100);
        SetTBValue( tiltMinTrackBar, Settings.TiltMin - (Settings.TiltCenter - 2100));
        SetTBValue( tiltMaxTrackBar, Settings.TiltMax + (Settings.TiltCenter - 2100));
        SetTBValue( rollCenterTrackBar, Settings.RollCenter - 2100);
        SetTBValue( rollMinTrackBar, Settings.RollMin - (Settings.RollCenter - 2100));
        SetTBValue( rollMaxTrackBar, Settings.RollMax + (Settings.RollCenter - 2100));

        dd_bluetooth->SelectedIndex = ((Settings.BluetoothMode >= 0) && (Settings.BluetoothMode < dd_bluetooth->Items->Count)) ? Settings.BluetoothMode : 0;
    } catch (System::Exception ^ e) {
        Log("Error updating UI from settings", e);
    }
}

// Updates the specified settings struct with the user-provided settings from the UI.
System::Void MainForm::UpdateSettingsFromUI(HTSETTINGS& Settings)
{
    Settings.LPTiltRoll = Convert::ToInt32(textBox_LP_value->Text);
    Settings.LPPan = Convert::ToInt32(textBox_LP_valuePan->Text);

    Settings.GyroWeightTiltRoll = Convert::ToInt32(GyroWeight_tiltRoll->Text);
    Settings.GyroWeightPan = Convert::ToInt32(GyroWeight_pan->Text);

    Settings.ServoGainPan = Convert::ToInt32(servoGainPan->Text);
    Settings.ServoGainTilt = Convert::ToInt32(servoGainTilt->Text);
    Settings.ServoGainRoll = Convert::ToInt32(servoGainRoll->Text);

    int temp = 0;

    if (chk_tilt->Checked)
        temp |= HT_TILT_REVERSE_BIT;

    if (chk_roll->Checked)
        temp |= HT_ROLL_REVERSE_BIT;

    if (chk_pan->Checked) 
        temp |= HT_PAN_REVERSE_BIT;

    Settings.ServoReverse = temp;

    Settings.PanCenter = Convert::ToInt32(inputPanCenter->Text);
    Settings.PanMin = Convert::ToInt32(inputPanTravlMin->Text);
    Settings.PanMax = Convert::ToInt32(inputPanTravlMax->Text);

    Settings.TiltCenter = Convert::ToInt32(inputTiltCenter->Text);
    Settings.TiltMin = Convert::ToInt32(inputTiltTravlMin->Text);
    Settings.TiltMax = Convert::ToInt32(inputTiltTravlMax->Text);

    Settings.RollCenter = Convert::ToInt32(inputRollCenter->Text);
    Settings.RollMin = Convert::ToInt32(inputRollTravlMin->Text);
    Settings.RollMax = Convert::ToInt32(inputRollTravlMax->Text);

    Settings.PanCh = Convert::ToByte(inputPanCh->Text);
    Settings.TiltCh = Convert::ToByte(inputTiltCh->Text);
    Settings.RollCh = Convert::ToByte(inputRollCh->Text);

	Settings.BluetoothMode = Convert::ToByte((dd_bluetooth->SelectedIndex>=0)? dd_bluetooth->SelectedIndex : 0);
}

// Event handler for hardware connection button.
System::Void MainForm::btn_connect_Click(System::Object^ sender, System::EventArgs^ e) {
    bool connected = false;
    btn_connect->Enabled = false;
    if (!TrackerWrap::Tracker->IsOpen()) {
        LogClear();
        groupBoxChart->Enabled = false;
        clear_HT_Click(this, nullptr);
        TrackerWrap::Tracker->Open(dd_comport->Text, true);
        if (TrackerWrap::Tracker->IsOpen() && (TrackerWrap::Tracker->Version > 1.0)) {
            connected = true;
        } else {
            Log("Hardware not found! Please check the COM port and ensure you have loaded the proper firmware.");
            TrackerWrap::Tracker->Close();
        }
    } else {
        TrackerWrap::Tracker->StreamTrackingData(false);
        TrackerWrap::Tracker->Close();
    }

    if (connected) {
        btn_connect->Text = "Disconnect";
        groupBoxChart->Enabled = true;

        HTSettings = TrackerWrap::Tracker->RetrieveSettings();
        UpdateUIFromSettings(HTSettings);
        Log(String::Format("Firmware Version {0}", TrackerWrap::Tracker->Version));
        if (!String::IsNullOrWhiteSpace(TrackerWrap::Tracker->Hardware)) {
            Log(String::Format("Hardware {0}", TrackerWrap::Tracker->Hardware));
        }

    } else {
        btn_connect->Text = "Connect";
    }
    start_HT->Text = START_HT_TEXT;
    start_HT->Enabled = connected;
    comPortTimer->Enabled = !connected;
    dd_comport->Enabled = !connected;
    dataReaderTimer->Enabled = connected;

    grpBoxServp2->Enabled = connected;
    groupBox2->Enabled = connected;
    groupBox3->Enabled = connected;
    grpBoxServp2->Enabled = connected;
    grpBoxServp1->Enabled = connected;
    dd_bluetooth->Enabled = connected;
    chartLimit->Enabled = connected;
    btn_update_headtracker->Enabled = connected;
    btnCalibrate->Enabled = connected;
    exportSettingsToFileToolStripMenuItem->Enabled = connected;
    importSettingsFromFileToolStripMenuItem->Enabled = connected;
    calibrationWizardToolStripMenuItem->Enabled = connected;
    calibrationWizardRotToolStripMenuItem->Enabled = connected;
    btnSendManualCmd->Enabled = connected;

    btn_connect->Enabled = true;
}
System::Void MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
    try {
        if ((TrackerWrap::Tracker != nullptr) && (TrackerWrap::Tracker->IsOpen())) {
            TrackerWrap::Tracker->Close();
        }
    } catch (Exception^) {}
}
System::Void MainForm::btnClearLog_Click(System::Object^ sender, System::EventArgs^ e) {
    LogClear();
}

// Set maxPoints limit on combobox change
System::Void MainForm::chartLimit_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
    int limits[10] = { 100, 200, 500, 1000, -1, -1, -1, -1, -1, -1 };
    maxPoints = limits[(chartLimit->SelectedIndex >= 0) ? chartLimit->SelectedIndex : 9];
    if ((maxPoints > 0) && (chart1->Series["Tilt"]->Points->Count >= maxPoints)) {
        while (chart1->Series["Tilt"]->Points->Count >= maxPoints) {
            chart1->Series["Tilt"]->Points->RemoveAt(0);
            chart1->Series["Roll"]->Points->RemoveAt(0);
            chart1->Series["Pan"]->Points->RemoveAt(0);
        }
        chart1->ResetAutoValues();
    }
}

// A window timer is used to update the chart every n milliseconds. Here's where the
// work is done to capture serial data from the hardware and update the UI with
// the data.
System::Void MainForm::dataReaderTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
    if (TrackerWrap::Tracker->IsOpen()) {
//  if (TrackerWrap::Tracker->Port->IsOpen && !_CalWizard->Visible) {

        while (TrackerWrap::Tracker->IsDataAvailable() > 0) {
            int serialbyte = (TrackerWrap::Tracker->ReadChar());

            if (TrackerWrap::Tracker->TrackStreaming) {
                if (serialbyte == 13) {
                    chartX++;

                    if (chartX == 1) {
                        chart1->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::WhiteSmoke;
                    }
                    for (int j = 0; j < 3; j++) {
                        if (SerialData[j] > 36000) SerialData[j] = 36000; else if (SerialData[j] < -36000) SerialData[j] = -36000;
                    }

                    if( (maxPoints>0) && (chart1->Series["Tilt"]->Points->Count >= maxPoints) ) {
                        while (chart1->Series["Tilt"]->Points->Count >= maxPoints) {
                            chart1->Series["Tilt"]->Points->RemoveAt(0);
                            chart1->Series["Roll"]->Points->RemoveAt(0);
                            chart1->Series["Pan"]->Points->RemoveAt(0);
                        }
                        chart1->ResetAutoValues();
                    }

                    chart1->Series["Tilt"]->Points->AddXY(chartX, SerialData[0] / 100 - 90);
                    chart1->Series["Roll"]->Points->AddXY(chartX, SerialData[1] / 100 - 90);
                    chart1->Series["Pan"]->Points->AddXY(chartX, SerialData[2] / 100 - 180);

                    SerialData[0] = 0;
                    SerialData[1] = 0;
                    SerialData[2] = 0;
                    Serialindex = 0;
                } else if (serialbyte == 44) {
                    Serialindex++;
                } else if (serialbyte > 47 && serialbyte < 58) {
                    try {
                        SerialData[Serialindex] = SerialData[Serialindex] * 10 + (serialbyte - 48);
                    } catch (Exception^) {
                    }
                }
            }
        }
    }
}

// Enumerates available serial ports. This timer fires every few seconds, just
// in case the user plugs in the device after starting the app.
System::Void MainForm::comPortTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
    Object^ curPort = dd_comport->SelectedItem;

    dd_comport->Items->Clear();
    dd_comport->Items->AddRange(TrackerWrap::Tracker->GetPortNames());

    if (dd_comport->Items->Count > 0) {
        try {
            dd_comport->SelectedItem = curPort;
        } catch (Exception^) { }
        if (dd_comport->SelectedIndex < 0) dd_comport->SelectedIndex = 0;
    }
    btn_connect->Enabled = (dd_comport->SelectedIndex >= 0);
}

// Plot start button handler. Sends message to hardware to stream data.
System::Void MainForm::start_HT_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (TrackerWrap::Tracker->IsOpen()) TrackerWrap::Tracker->StreamTrackingData(!TrackerWrap::Tracker->TrackStreaming);
    if( TrackerWrap::Tracker->TrackStreaming ) clear_HT->Enabled = true;
    start_HT->Text = TrackerWrap::Tracker->TrackStreaming ? STOP_HT_TEXT : START_HT_TEXT;
}

// Clear plot button handler. Clears the series in the plots.
System::Void MainForm::clear_HT_Click(System::Object^ sender, System::EventArgs^ e) {
    chart1->Series["Tilt"]->Points->Clear();
    chart1->Series["Roll"]->Points->Clear();
    chart1->Series["Pan"]->Points->Clear();
    chartX = 0;
    chart1->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::Transparent;
    clear_HT->Enabled = TrackerWrap::Tracker->TrackStreaming;
    start_HT->Text = TrackerWrap::Tracker->TrackStreaming ? STOP_HT_TEXT : START_HT_TEXT;
}

// Sends settings to head tracker for storage
System::Void MainForm::btn_update_headtracker_Click(System::Object^ sender, System::EventArgs^ e) {
    if (TrackerWrap::Tracker->IsOpen()) {
        HTSETTINGS settings;
        UpdateSettingsFromUI(settings);
        TrackerWrap::Tracker->WriteLine( String::Format(
            "${0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20}HE",
            settings.LPTiltRoll, settings.LPPan, // 0 , 1
            settings.GyroWeightTiltRoll, settings.GyroWeightPan, // 2, 3
            settings.ServoGainTilt, settings.ServoGainPan, settings.ServoGainRoll, // 4, 5, 6
            settings.ServoReverse, // 7
            settings.PanCenter, settings.PanMin, settings.PanMax, // 8, 9, 10
            settings.TiltCenter, settings.TiltMin, settings.TiltMax, // 11, 12, 13
            settings.RollCenter, settings.RollMin, settings.RollMax, // 14, 15, 16
            settings.PanCh, settings.TiltCh, settings.RollCh, settings.BluetoothMode  // 17, 18 19, 20
        ));
    }
}

// Calibrate button click handler. Does the same thing as the menu entry.
System::Void MainForm::btnCalibrate_Click(System::Object^ sender, System::EventArgs^ e) {
    MainForm::OnCalWizardRot_Menu(sender, e);
}

// File->exit menu handler.
System::Void MainForm::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
}

// Help->About menu handler
System::Void MainForm::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("DIY headtracker project\n\n"+
        "   - Written by Dennis Frie 2012\n"+
        "   - Augmented by Mark Mansur 2013\n"+
        "   - Wireless version support by Chris Stephens 2018\n" +
        "   - Win10 freeze fix and UI cleanups by Alexander Eltsyn 2019");
}

System::Void MainForm::btnSendManualCmd_Click(System::Object^  sender, System::EventArgs^  e) {
    TrackerWrap::Tracker->WriteLine( ManualCmdEdit->Text );
}

// Called when the control gains focus. Highlights existing text.
System::Void MainForm::ManualCmdEdit_OnFocusEnter(System::Object^  sender, System::EventArgs^  e)
{
    ManualCmdEdit->SelectAll();
}

// Captures enter key down, to send the command.
System::Void MainForm::ManualCmdEdit_OnKeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
    if ( e->KeyCode == Keys::Enter )
        btnSendManualCmd_Click(sender, e);
}

// Pan center trackbar value change handler.
System::Void MainForm::PanCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panCenterTrackBar->Value);
    inputPanCenter->Text = Convert::ToString(2100 + panCenterTrackBar->Value);
    int temp = panMinTrackBar->Value + panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMin->Text = Convert::ToString(temp); 

    temp = panMaxTrackBar->Value - panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMax->Text = Convert::ToString(temp); 
}

// Pan min extreme trackbar value change handler.
System::Void MainForm::PanMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panMinTrackBar->Value);
    inputPanCenter->Text = Convert::ToString(2100 + panCenterTrackBar->Value);
    int temp = panMinTrackBar->Value + panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMin->Text = Convert::ToString(temp);
}

// Pan max extreme trackbar value change handler.
System::Void MainForm::PanMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panMaxTrackBar->Value);
    inputPanCenter->Text = Convert::ToString(2100 + panCenterTrackBar->Value);
    int temp = panMaxTrackBar->Value - panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMax->Text = Convert::ToString(temp); 
}

// Tilt center trackbar value change handler.
System::Void MainForm::TiltCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltCenterTrackBar->Value);
    inputTiltCenter->Text = Convert::ToString(2100 + tiltCenterTrackBar->Value);
    int temp = tiltMinTrackBar->Value + tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMin->Text = Convert::ToString(temp); 

    temp = tiltMaxTrackBar->Value - tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMax->Text = Convert::ToString(temp);
}

// Tilt min extreme trackbar value change handler.
System::Void MainForm::TiltMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltMinTrackBar->Value);
    inputTiltCenter->Text = Convert::ToString(2100 + tiltCenterTrackBar->Value);
    int temp = tiltMinTrackBar->Value + tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMin->Text = Convert::ToString(temp);
}

// Tilt max extreme trackbar value change handler.
System::Void MainForm::TiltMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltMaxTrackBar->Value);

    inputTiltCenter->Text = Convert::ToString(2100 + tiltCenterTrackBar->Value);
    int temp = tiltMaxTrackBar->Value - tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMax->Text = Convert::ToString(temp); 
}

// Roll center trackbar value change handler.
System::Void MainForm::RollCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollCenterTrackBar->Value);


    inputRollCenter->Text = Convert::ToString(2100 + rollCenterTrackBar->Value);
    int temp = rollMinTrackBar->Value + rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMin->Text = Convert::ToString(temp); 

    temp = rollMaxTrackBar->Value - rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMax->Text = Convert::ToString(temp); 
}

// Roll min extreme trackbar value change handler.
System::Void MainForm::RollMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollMinTrackBar->Value);
    inputRollCenter->Text = Convert::ToString(2100 + rollCenterTrackBar->Value);
    int temp = rollMinTrackBar->Value + rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMin->Text = Convert::ToString(temp);
}

// Roll max extreme trackbar value change handler.
System::Void MainForm::RollMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollMaxTrackBar->Value);
    inputRollCenter->Text = Convert::ToString(2100 + rollCenterTrackBar->Value);
    int temp = rollMaxTrackBar->Value - rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMax->Text =Convert::ToString(temp); 
}

// Pan gain trackbar value change handler.
System::Void MainForm::PanGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panGainTrackBar->Value);
    servoGainPan->Text = Convert::ToString(panGainTrackBar->Value);
}

// Tilt gain trackbar value change handler.
System::Void MainForm::TiltGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltGainTrackBar->Value);
    servoGainTilt->Text = Convert::ToString(tiltGainTrackBar->Value);
}

// Roll gain trackbar value change handler.
System::Void MainForm::RollGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollGainTrackBar->Value);
    servoGainRoll->Text = Convert::ToString(rollGainTrackBar->Value);
}

// User text input handler for pan min travel edit control.
System::Void MainForm::PanMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanTravlMin->Modified )
    {
        try
        {
            SetTBValue( panMinTrackBar, Convert::ToInt32(inputPanTravlMin->Text, 10));
            inputPanTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log( "ERROR updating pan min trackbar.", e );
        }
    }
}

// User text input handler for pan max travel edit control.
System::Void MainForm::PanMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanTravlMax->Modified )
    {
        try
        {
            SetTBValue( panMaxTrackBar, Convert::ToInt32(inputPanTravlMax->Text, 10));
            inputPanTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log( "ERROR updating pan max trackbar.", e );
        }
    }
}

// User text input handler for pan center edit control.
System::Void MainForm::PanCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanCenter->Modified)
    {
        try
        {
            SetTBValue( panCenterTrackBar, Convert::ToInt32(inputPanCenter->Text, 10) - 2100);

            int temp = panMinTrackBar->Value + panCenterTrackBar->Value;
            if (temp >= 0)
                inputPanTravlMin->Text = Convert::ToString(temp); 

            temp = panMaxTrackBar->Value - panCenterTrackBar->Value;
            if (temp >= 0)
                inputPanTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Log( "ERROR updating pan trackbars.", e );
        }
        
        inputPanCenter->Modified = false;
    }
}

System::Void MainForm::TiltMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltTravlMin->Modified )
    {
        try
        {
            SetTBValue(tiltMinTrackBar, Convert::ToInt32(inputTiltTravlMin->Text, 10));
            inputTiltTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating tilt min trackbar.", e);
        }
    }
}

System::Void MainForm::TiltMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltTravlMax->Modified )
    {
        try
        {
            SetTBValue(tiltMaxTrackBar, Convert::ToInt32(inputTiltTravlMax->Text, 10));
            inputTiltTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating tilt max trackbar.", e);
        }
    }
}

System::Void MainForm::TiltCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltCenter->Modified)
    {
        try
        {
            SetTBValue( tiltCenterTrackBar, Convert::ToInt32(inputTiltCenter->Text, 10) - 2100);

            int temp = tiltMinTrackBar->Value + tiltCenterTrackBar->Value;
            if (temp >= 0)
                inputTiltTravlMin->Text = Convert::ToString(temp); 

            temp = tiltMaxTrackBar->Value - tiltCenterTrackBar->Value;
            if (temp >= 0)
                inputTiltTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating tilt trackbars.", e);
        }

        inputTiltCenter->Modified = false;
    }
}

System::Void MainForm::RollMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollTravlMin->Modified )
    {
        try
        {
            SetTBValue( rollMinTrackBar, Convert::ToInt32(inputRollTravlMin->Text, 10));
            inputRollTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating roll min trackbar.", e);
        }
    }
}

System::Void MainForm::RollMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollTravlMax->Modified )
    {
        try
        {
            SetTBValue(rollMaxTrackBar, Convert::ToInt32(inputRollTravlMax->Text, 10));
            inputRollTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating roll max trackbar.", e);
        }
    }
}

System::Void MainForm::RollCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollCenter->Modified)
    {
        try
        {
            SetTBValue(rollCenterTrackBar, Convert::ToInt32(inputRollCenter->Text, 10) - 2100);

            int temp = rollMinTrackBar->Value + rollCenterTrackBar->Value;
            if (temp >= 0)
                inputRollTravlMin->Text = Convert::ToString(temp); 

            temp = rollMaxTrackBar->Value - rollCenterTrackBar->Value;
            if (temp >= 0)
                inputRollTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating roll trackbars.", e);
        }

        inputRollCenter->Modified = false;
    }
}

System::Void MainForm::TiltGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainTilt->Modified )
    {
        try
        {
            SetTBValue(tiltGainTrackBar, Convert::ToInt32(servoGainTilt->Text, 10));
            servoGainTilt->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating tilt gain trackbar.", e);
        }
    }
}

// Handler for user entry of text into edit control
System::Void MainForm::PanGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainPan->Modified )
    {
        try
        {
            SetTBValue(panGainTrackBar, Convert::ToInt32(servoGainPan->Text, 10));
            servoGainPan->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating pan gain trackbar.", e);
        }
    }
}

// Handler for user entry of text into edit control
System::Void MainForm::RollGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainRoll->Modified )
    {
        try
        {
            SetTBValue(rollGainTrackBar, Convert::ToInt32(servoGainRoll->Text, 10));
            servoGainRoll->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Log("ERROR updating roll gain trackbar.", e );
        }
    }
}

// Menu click handler
System::Void MainForm::OnCalWizard_Menu(System::Object^  sender, System::EventArgs^  e)
{
    CalWizard^ wizard = gcnew CalWizard(AXISALIGNMENT);
    try { wizard->ShowDialog(this); } catch (Exception^) {};
    try { delete wizard; } catch (Exception^) {};
}

// Menu click handler
System::Void MainForm::OnCalWizardRot_Menu(System::Object^  sender, System::EventArgs^  e)
{
    CalWizard^ wizard = gcnew CalWizard(MINMAXTRACKING);
    try { wizard->ShowDialog(this);} catch (Exception^) {};
    try { delete wizard; } catch (Exception^) {};
}

// Exports settings from the UI to a file.
// Settings to export:
/*    
    int LPTiltRoll;         // Firmware: tiltRollBeta
    int LPPan;              // Firmware: panBeta
    int GyroWeightTiltRoll; // Firmware: gyroWeightTiltRoll
    int GyroWeightPan;      // Firmware: gyroWeightPan
    int ServoGainPan;       // Firmware: tiltFactor
    int ServoGainTilt;      // Firmware: panFactor
    int ServoGainRoll;      // Firmware: rollFactor
    Byte ServoReverse;      // Firmware: servoReverseMask
    int PanCenter;          // Firmware: servoPanCenter
    int PanMin;             // Firmware: panMinPulse
    int PanMax;             // Firmware: panMaxPulse
    int TiltCenter;         // Firmware: servoTiltCenter
    int TiltMin;            // Firmware: tiltMinPulse
    int TiltMax;            // Firmware: tiltMaxPulse
    int RollCenter;         // Firmware: servoRollCenter
    int RollMin;            // Firmware: rollMinPulse
    int RollMax;            // Firmware: rollMaxPulse
    Byte PanCh;             // Firmware: htChannels[0]
    Byte TiltCh;            // Firmware: htChannels[1]
    Byte RollCh;            // Firmware: htChannels[2]
	Byte BluetoothMode;		// Firmware: bluetoothMode
*/
System::Void MainForm::OnExportSettingsToFile_Menu(System::Object^ sender, System::EventArgs^ e)
{
    String^ fileName = "textfile.txt";
    FileDialog^ saveFileDialog = gcnew SaveFileDialog;

    saveFileDialog->InitialDirectory = "";
    saveFileDialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
    saveFileDialog->FilterIndex = 1;
    saveFileDialog->RestoreDirectory = true;

    if ( saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK )
    {
        try
        {
            HTSETTINGS settings;
            UpdateSettingsFromUI(settings);

            System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(saveFileDialog->FileName);
            float f = TrackerWrap::Tracker->Version;
            sw->WriteLine("{0} : FW Version", f);
            sw->WriteLine("{0} : LPTiltRoll", settings.LPTiltRoll);
            sw->WriteLine("{0} : LPPan", settings.LPPan);
            sw->WriteLine("{0} : GyroWeightTiltRoll", settings.GyroWeightTiltRoll);
            sw->WriteLine("{0} : GyroWeightPan", settings.GyroWeightPan);
            sw->WriteLine("{0} : ServoGainPan", settings.ServoGainPan);
            sw->WriteLine("{0} : ServoGainTilt", settings.ServoGainTilt);
            sw->WriteLine("{0} : ServoGainRoll", settings.ServoGainRoll);
            sw->WriteLine("{0} : ServoReverseMask", settings.ServoReverse);
            sw->WriteLine("{0} : PanCenter", settings.PanCenter);
            sw->WriteLine("{0} : PanMin", settings.PanMin);
            sw->WriteLine("{0} : PanMax", settings.PanMax);
            sw->WriteLine("{0} : TiltCenter", settings.TiltCenter);
            sw->WriteLine("{0} : TiltMin", settings.TiltMin);
            sw->WriteLine("{0} : TiltMax", settings.TiltMax);
            sw->WriteLine("{0} : RollCenter", settings.RollCenter);
            sw->WriteLine("{0} : RollMin", settings.RollMin);
            sw->WriteLine("{0} : RollMax", settings.RollMax);
            sw->WriteLine("{0} : PanCh", settings.PanCh);
            sw->WriteLine("{0} : TiltCh", settings.TiltCh);
            sw->WriteLine("{0} : RollCh", settings.RollCh);
			sw->WriteLine("{0} : BluetoothMode", settings.BluetoothMode);
            sw->Close();
        }
        catch (Exception^ e) {
            Log("Error exportings settings", e);
        }
    }
}

// Imports tracker settings from a file into the UI.
System::Void MainForm::OnImportSettingsFromFile_Menu(System::Object^ sender, System::EventArgs^ e)
{
    String^ fileName = "textfile.txt";
    OpenFileDialog^ openFileDialog = gcnew OpenFileDialog;
    HTSETTINGS settings;

    openFileDialog->InitialDirectory = "";
    openFileDialog->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
    openFileDialog->FilterIndex = 1;
    openFileDialog->RestoreDirectory = true;

    if ( openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK )
    {
        try 
        {
            System::IO::StreamReader^ din = System::IO::File::OpenText(openFileDialog->FileName);

            String^ str;
            int count = 0;
            float fw = 0.0;
            while ((str = din->ReadLine()) != nullptr) 
            {
                array<wchar_t>^ delim = {' '};
                array<String^>^ items = str->Split(delim);
            
                System::Globalization::CultureInfo^ ci = gcnew System::Globalization::CultureInfo("en-US");
                System::Globalization::NumberFormatInfo^ fi = ci->NumberFormat;
                fi->NumberDecimalSeparator = ".";

                switch (count)
                {
                    // Check firmware version
                case 0: fw = Convert::ToSingle(items[0], fi); break;
                case 1: settings.LPTiltRoll = Convert::ToInt32(items[0]); break;
                case 2: settings.LPPan = Convert::ToInt32(items[0]); break;
                case 3: settings.GyroWeightTiltRoll = Convert::ToInt32(items[0]); break;
                case 4: settings.GyroWeightPan = Convert::ToInt32(items[0]); break;
                case 5: settings.ServoGainPan = Convert::ToInt32(items[0]); break;
                case 6: settings.ServoGainTilt = Convert::ToInt32(items[0]); break;
                case 7: settings.ServoGainRoll = Convert::ToInt32(items[0]); break;
                case 8: settings.ServoReverse = Convert::ToInt32(items[0]); break;
                case 9: settings.PanCenter = Convert::ToInt32(items[0]); break;
                case 10: settings.PanMin = Convert::ToInt32(items[0]); break;
                case 11: settings.PanMax = Convert::ToInt32(items[0]); break;
                case 12: settings.TiltCenter = Convert::ToInt32(items[0]); break;
                case 13: settings.TiltMin= Convert::ToInt32(items[0]); break;
                case 14: settings.TiltMax = Convert::ToInt32(items[0]); break;
                case 15: settings.RollCenter = Convert::ToInt32(items[0]); break;
                case 16: settings.RollMin = Convert::ToInt32(items[0]); break;
                case 17: settings.RollMax = Convert::ToInt32(items[0]); break;
                case 18: settings.PanCh = Convert::ToByte(items[0]); break;
                case 19: settings.TiltCh = Convert::ToByte(items[0]); break;
                case 20: settings.RollCh = Convert::ToByte(items[0]); break;
				case 21: settings.BluetoothMode = Convert::ToByte(items[0]); break;
                }
                count++;
            }
            UpdateUIFromSettings(settings);
            Log("Settings successfully loaded");
        }
        catch (Exception^ e)
        {
            if (dynamic_cast<System::IO::FileNotFoundException^>(e))
            {
                Log("File not found!", e);
            }
            else
            {
                Log("File error!", e);
            }
        }
    }
}
//Write char to log
System::Void MainForm::Log( int ch ) {
    if ((ch == 10) || (ch == 13)) {
        newLine = true;
    } else {
        AppendLog( Convert::ToChar(ch).ToString() );
    }
}

// Write line to log
System::Void MainForm::Log( System::String^ str) {
    newLine = true;
    AppendLog(str);
    newLine = true;
}

// Write error message to log
System::Void MainForm::Log(String^ str, Exception^ e) {
    Log(str);
#ifdef DEBUG
    Log( e->Message);
#endif
}

// Append string to log output buffer
void MainForm::AppendLog(String^ str) {
    if (newLine) {
        newLine = false;
        if ( (text->Length > 0) && (text[text->Length-1]!='\r') ) {
            int lineCount = 0;
            text += "\r\n";
            for (int p = text->Length - 1; p > 0; p--) {
                if (text[p] == '\r') {
                    lineCount++;
                    if (lineCount > MAX_LINES) {
                        text = text->Substring(p + ((text[p+1] == '\n') ? 2 : 1));
                        break;
                    }
                }
            }
        }
    }
    text += str;
    LogFlush();
}

void MainForm::LogClear() {
    text = "";
    LogFlush();
}

void MainForm::LogFlush() {
    if (mainForm == nullptr) return;

    if (mainForm->logViewer->InvokeRequired) {
        mainForm->logViewer->Invoke(gcnew LogFlushDelegate(this, &MainForm::LogFlush));
    } else {
        if (!mainForm->logViewer->Text->Equals(mainForm->text)) {
            mainForm->logViewer->Text = mainForm->text;
            mainForm->btnClearLog->Enabled = !String::IsNullOrWhiteSpace(mainForm->text);
        }
    }
}

