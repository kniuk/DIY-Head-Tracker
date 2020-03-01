//--------------------------------------------------------------------------------------
// File:    MainForm.cpp (C++/CLI)
// Desc:    Implements the main form handlers.
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

HTSETTINGS HTSettings;

int serialbyte = 0;
unsigned char linecount = 0;
float SerialData[25];
int Serialindex = 0;
long i = 0;

//--------------------------------------------------------------------------------------
// Func: main
// Desc: Called by system at app startup. Program entry point.
//--------------------------------------------------------------------------------------
[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    TrackerWrap::Tracker = gcnew HeadTracker();
    
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}

//--------------------------------------------------------------------------------------
// Func: Form1_Load
// Desc: Form initialization handler
//--------------------------------------------------------------------------------------
System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e)
{
    // Disable resizing
    //this->FormBorderStyle = ::FormBorderStyle::FixedDialog;

    // Serial ports
    array<String^>^ ports = TrackerWrap::Tracker->Port->GetPortNames();
    dd_comport->Items->Clear();
    for each(String^ port in ports)
    {
        dd_comport->Items->Add(port);
    }
}

//--------------------------------------------------------------------------------------
// Func: RetrieveSettings
// Desc: Retrieves the settings from the tracker, and stores them in a local structure
//--------------------------------------------------------------------------------------
System::Void Form1::RetrieveSettings()
{
    HTSettings = TrackerWrap::Tracker->RetrieveSettings();
}

//--------------------------------------------------------------------------------------
// Func: UpdateUIFromSettings
// Desc: Updates the UI state with the specified settings
//--------------------------------------------------------------------------------------
System::Void Form1::UpdateUIFromSettings(HTSETTINGS& Settings)
{
    try
    {
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
        panGainTrackBar->Value = Settings.ServoGainPan;
        tiltGainTrackBar->Value = Settings.ServoGainTilt;
        rollGainTrackBar->Value = Settings.ServoGainRoll;
        panCenterTrackBar->Value = Settings.PanCenter - 2100;
        panMinTrackBar->Value = Settings.PanMin - (Settings.PanCenter - 2100);
        panMaxTrackBar->Value = Settings.PanMax + (Settings.PanCenter - 2100);
        tiltCenterTrackBar->Value = Settings.TiltCenter - 2100;
        tiltMinTrackBar->Value = Settings.TiltMin - (Settings.TiltCenter - 2100);
        tiltMaxTrackBar->Value = Settings.TiltMax + (Settings.TiltCenter - 2100);
        rollCenterTrackBar->Value = Settings.RollCenter - 2100;
        rollMinTrackBar->Value = Settings.RollMin - (Settings.RollCenter - 2100);
        rollMaxTrackBar->Value = Settings.RollMax + (Settings.RollCenter - 2100);
    }
    catch (System::Exception^ e)
    {
        Serial_output_box->Text += String::Format("Error updating UI from settings.\r\n");
#ifdef DEBUG
        Serial_output_box->Text += e->Message;
        Serial_output_box->Text += String::Format("\r\n");
#endif
    }
}

//--------------------------------------------------------------------------------------
// Func: UpdateSettingsFromUI
// Desc: Updates the specified settings struct with the user-provided settings from the
//       UI.
//--------------------------------------------------------------------------------------
System::Void Form1::UpdateSettingsFromUI(HTSETTINGS& Settings)
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
}

//--------------------------------------------------------------------------------------
// Func: btn_connect_Click
// Desc: Event handler for hardware connection button.
//--------------------------------------------------------------------------------------
System::Void Form1::btn_connect_Click(System::Object^ sender, System::EventArgs^ e)
{
    btn_connect->Enabled = false;
    TrackerWrap::Tracker->Open(dd_comport->Text, true);
    if (TrackerWrap::Tracker->Port->IsOpen)
    {
        // Start reading from the port
        timer1->Enabled = true;

        // Stop any streaming, in case something failed last time
        TrackerWrap::Tracker->StreamTrackingData(false);

        // Set up controls
        stop_HT->Enabled = true;
        start_HT->Enabled = true;
        btn_update_headtracker->Enabled = true;
        btnCalibrate->Enabled = true;
        btn_disconnect->Enabled = true;
        calibrationWizardToolStripMenuItem->Enabled = true;
        calibrationWizardRotToolStripMenuItem->Enabled = true;
        btnSendManualCmd->Enabled = true;
        
        RetrieveSettings();
        UpdateUIFromSettings(HTSettings);
        float f = TrackerWrap::Tracker->Version;
        Serial_output_box->Text += String::Format("Firmware Version {0}\r\n", f);
        comPortTimer->Enabled = false;
    }
    else
    {
        btn_connect->Enabled = true;
        Serial_output_box->Text += String::Format("Hardware not found! Double check the COM port and ensure you have loaded the proper firmware.\r\n");
    }
}

//--------------------------------------------------------------------------------------
// Func: btn_disconnect_Click
// Desc: Hardware disconnection button press handler
//--------------------------------------------------------------------------------------
System::Void Form1::btn_disconnect_Click(System::Object^ sender, System::EventArgs^ e)
{
    if ( TrackerWrap::Tracker->Port->IsOpen )
    {
        // Tell hardware to stop streaming (to be nice during next connection)
        TrackerWrap::Tracker->StreamTrackingData(false);
        TrackerWrap::Tracker->Close();
        timer1->Enabled = false;
    }
    btn_connect->Enabled = true;
    stop_HT->Enabled = false;
    start_HT->Enabled = false;
    btn_update_headtracker->Enabled = false;
    btnCalibrate->Enabled = false;
    btn_disconnect->Enabled = false;
    comPortTimer->Enabled = true;
    calibrationWizardToolStripMenuItem->Enabled = false;
    calibrationWizardRotToolStripMenuItem->Enabled = false;
    btnSendManualCmd->Enabled = false;
}

//--------------------------------------------------------------------------------------
// Func: timer1_Tick
// Desc: A window timer is used to update the UI every n milliseconds. Here's where the
//       work is done to capture serial data from the hardware and update the UI with
//       the data.
//--------------------------------------------------------------------------------------
System::Void Form1::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
    if (TrackerWrap::Tracker->Port->IsOpen && !_CalWizard->Visible)
    {
        while(TrackerWrap::Tracker->Port->BytesToRead > 0)
        {
            serialbyte = (TrackerWrap::Tracker->Port->ReadChar());

            Serial_output_box->Text += Convert::ToChar((serialbyte));

            if (serialbyte == 13)
            {
                linecount++;

                if (linecount > 12)
                {
                    Serial_output_box->Clear();
                    linecount = 0;
                }
            }

            if (TrackerWrap::Tracker->TrackStreaming)
            {
                if (serialbyte == 13)
                {
                    i++;
                    
                    if (i == 1)
                    {
                        chart1->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::WhiteSmoke;
                    }
                    
                    chart1->Series["Tilt"]->Points->AddXY(i, SerialData[0] / 100 - 90);
                    chart1->Series["Roll"]->Points->AddXY(i, SerialData[1] / 100 - 90);
                    chart1->Series["Pan"]->Points->AddXY(i, SerialData[2] / 100 - 180);

                    SerialData[0] = 0;
                    SerialData[1] = 0;
                    SerialData[2] = 0;
                    Serialindex   = 0;
                }
                else if (serialbyte == 44)
                {
                    Serialindex++;
                }
                else if (serialbyte > 47 && serialbyte < 58)
                {
                    SerialData[Serialindex] = SerialData[Serialindex] * 10 + (serialbyte - 48);
                }
            }
        }
    }	 
}

//--------------------------------------------------------------------------------------
// Func: comPortTimer_Tick
// Desc: Enumerates available serial ports. This timer fires every few seconds, just
//       in case the user plugs in the device after starting the app.
//--------------------------------------------------------------------------------------
System::Void Form1::comPortTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
    Object^ curPort = dd_comport->SelectedItem;

    array<String^>^ ports = TrackerWrap::Tracker->Port->GetPortNames();
    dd_comport->Items->Clear();
    for each(String^ port in ports)
    {
        dd_comport->Items->Add(port);
    }

    dd_comport->SelectedItem = curPort;
    dd_comport->SelectionLength = 4;
}

//--------------------------------------------------------------------------------------
// Func: start_HT_Click
// Desc: Plot start button handler. Sends message to hardware to stream data.
//--------------------------------------------------------------------------------------
System::Void Form1::start_HT_Click(System::Object^ sender, System::EventArgs^ e)
{
    if ( TrackerWrap::Tracker->Port->IsOpen )
        TrackerWrap::Tracker->StreamTrackingData(true);
}

//--------------------------------------------------------------------------------------
// Func: clear_plot_Click
// Desc: Clear plot button handler. Clears the series in the plots.
//--------------------------------------------------------------------------------------
System::Void Form1::clear_plot_Click(System::Object^ sender, System::EventArgs^ e)
{
    chart1->Series["Tilt"]->Points->Clear();
    chart1->Series["Roll"]->Points->Clear();
    chart1->Series["Pan"]->Points->Clear();
    i=0;
    chart1->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::Transparent;
}

//--------------------------------------------------------------------------------------
// Func: btn_update_headtracker_Click
// Desc: Sends settings to head tracker for storage
//--------------------------------------------------------------------------------------
System::Void Form1::btn_update_headtracker_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (TrackerWrap::Tracker->Port->IsOpen)
    {
        HTSETTINGS settings;
        UpdateSettingsFromUI(settings);
        TrackerWrap::Tracker->Port->WriteLine(String::Format("${0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19}HE", 
            settings.LPTiltRoll, settings.LPPan, // 0 , 1
            settings.GyroWeightTiltRoll,settings.GyroWeightPan, // 2, 3
            settings.ServoGainTilt, settings.ServoGainPan, settings.ServoGainRoll, // 4, 5, 6
            settings.ServoReverse, // 7
            settings.PanCenter,settings.PanMin,settings.PanMax, // 8, 9, 10
            settings.TiltCenter,settings.TiltMin,settings.TiltMax, // 11, 12, 13
            settings.RollCenter,settings.RollMin,settings.RollMax, // 14, 15, 16
            settings.PanCh,settings.TiltCh,settings.RollCh) );  // 17, 18 19
    }
}

//--------------------------------------------------------------------------------------
// Func: stop_HT_Click
// Desc: Plot stop button handler. Sends request to hardware to cease data streaming.
//--------------------------------------------------------------------------------------
System::Void Form1::stop_HT_Click(System::Object^ sender, System::EventArgs^ e)
{
    if ( TrackerWrap::Tracker->Port->IsOpen )
        TrackerWrap::Tracker->StreamTrackingData(false);
}

//--------------------------------------------------------------------------------------
// Func: btnCalibrate_Click
// Desc: Calibrate button click handler. Does the same thing as the menu entry.
//--------------------------------------------------------------------------------------
System::Void Form1::btnCalibrate_Click(System::Object^ sender, System::EventArgs^ e)
{
    Form1::OnCalWizardRot_Menu(sender, e);
}

//--------------------------------------------------------------------------------------
// Func: exitToolStripMenuItem_Click
// Desc: File->exit menu handler.
//--------------------------------------------------------------------------------------
System::Void Form1::exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
}

//--------------------------------------------------------------------------------------
// Func: aboutToolStripMenuItem_Click
// Desc: Help->About menu handler
//--------------------------------------------------------------------------------------
System::Void Form1::aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("DIY headtracker project\n - Written by Dennis Frie 2012\n - Augmented by Mark Mansur 2013");
}

//--------------------------------------------------------------------------------------
// Func: SendManualCmd_OnClick
// Desc: 
//--------------------------------------------------------------------------------------
System::Void Form1::btnSendManualCmd_Click(System::Object^  sender, System::EventArgs^  e)
{
    System::String^ line = ManualCmdEdit->Text;
    if ( TrackerWrap::Tracker->Port->IsOpen )
    {
        TrackerWrap::Tracker->Port->DiscardInBuffer();
        TrackerWrap::Tracker->Port->WriteLine(line);
    }
}

//--------------------------------------------------------------------------------------
// Func: ManualCmdEdit_OnFocusEnter
// Desc: Called when the control gains focus. Highlights existing text.
//--------------------------------------------------------------------------------------
System::Void Form1::ManualCmdEdit_OnFocusEnter(System::Object^  sender, System::EventArgs^  e)
{
    ManualCmdEdit->SelectAll();
}

//--------------------------------------------------------------------------------------
// Func: ManualCmdEdit_OnKeyDown
// Desc: Captures enter key down, to send the command.
//--------------------------------------------------------------------------------------
System::Void Form1::ManualCmdEdit_OnKeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
    if ( e->KeyCode == Keys::Enter )
        btnSendManualCmd_Click(sender, e);
}

//--------------------------------------------------------------------------------------
// Func: PanCenterTrackBar_ValueChanged
// Desc: Pan center trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::PanCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
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

//--------------------------------------------------------------------------------------
// Func: PanMinTrackBar_ValueChanged
// Desc: Pan min extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::PanMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panMinTrackBar->Value);
    inputPanCenter->Text = Convert::ToString(2100 + panCenterTrackBar->Value);
    int temp = panMinTrackBar->Value + panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMin->Text = Convert::ToString(temp);
}

//--------------------------------------------------------------------------------------
// Func: PanMaxTrackBar_ValueChanged
// Desc: Pan max extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::PanMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panMaxTrackBar->Value);
    inputPanCenter->Text = Convert::ToString(2100 + panCenterTrackBar->Value);
    int temp = panMaxTrackBar->Value - panCenterTrackBar->Value;
    if (temp >= 0)
        inputPanTravlMax->Text = Convert::ToString(temp); 
}

//--------------------------------------------------------------------------------------
// Func: TiltCenterTrackBar_ValueChanged
// Desc: Tilt center trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::TiltCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
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

//--------------------------------------------------------------------------------------
// Func: TiltMinTrackBar_ValueChanged
// Desc: Tilt min extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::TiltMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltMinTrackBar->Value);
    inputTiltCenter->Text = Convert::ToString(2100 + tiltCenterTrackBar->Value);
    int temp = tiltMinTrackBar->Value + tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMin->Text = Convert::ToString(temp);
}

//--------------------------------------------------------------------------------------
// Func: TiltMaxTrackBar_ValueChanged
// Desc: Tilt max extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::TiltMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltMaxTrackBar->Value);

    inputTiltCenter->Text = Convert::ToString(2100 + tiltCenterTrackBar->Value);
    int temp = tiltMaxTrackBar->Value - tiltCenterTrackBar->Value;
    if (temp >= 0)
        inputTiltTravlMax->Text = Convert::ToString(temp); 
}

//--------------------------------------------------------------------------------------
// Func: RollCenterTrackBar_ValueChanged
// Desc: Roll center trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::RollCenterTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
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

//--------------------------------------------------------------------------------------
// Func: RollMinTrackBar_ValueChanged
// Desc: Roll min extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::RollMinTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollMinTrackBar->Value);
    inputRollCenter->Text = Convert::ToString(2100 + rollCenterTrackBar->Value);
    int temp = rollMinTrackBar->Value + rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMin->Text = Convert::ToString(temp);
}

//--------------------------------------------------------------------------------------
// Func: RollMaxTrackBar_ValueChanged
// Desc: Roll max extreme trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::RollMaxTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollMaxTrackBar->Value);
    inputRollCenter->Text = Convert::ToString(2100 + rollCenterTrackBar->Value);
    int temp = rollMaxTrackBar->Value - rollCenterTrackBar->Value;
    if (temp >= 0)
        inputRollTravlMax->Text =Convert::ToString(temp); 
}

//--------------------------------------------------------------------------------------
// Func: PanGainTrackBar_ValueChanged
// Desc: Pan gain trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::PanGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(panGainTrackBar->Value);
    servoGainPan->Text = Convert::ToString(panGainTrackBar->Value);
}

//--------------------------------------------------------------------------------------
// Func: TiltGainTrackBar_ValueChanged
// Desc: Tilt gain trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::TiltGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(tiltGainTrackBar->Value);
    servoGainTilt->Text = Convert::ToString(tiltGainTrackBar->Value);
}

//--------------------------------------------------------------------------------------
// Func: RollGainTrackBar_ValueChanged
// Desc: Roll gain trackbar value change handler.
//--------------------------------------------------------------------------------------
System::Void Form1::RollGainTrackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
    lblShowOutput->Text = Convert::ToString(rollGainTrackBar->Value);
    servoGainRoll->Text = Convert::ToString(rollGainTrackBar->Value);
}

//--------------------------------------------------------------------------------------
// Func: PanMinTravelEdit_ValueChanged
// Desc: User text input handler for pan min travel edit control.
//--------------------------------------------------------------------------------------
System::Void Form1::PanMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanTravlMin->Modified )
    {
        try
        {
            panMinTrackBar->Value = Convert::ToInt32(inputPanTravlMin->Text, 10);
            inputPanTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating pan min trackbar.\r\n");
#ifdef DEBUG
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
#endif
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: PanMaxTravelEdit_ValueChanged
// Desc: User text input handler for pan max travel edit control.
//--------------------------------------------------------------------------------------
System::Void Form1::PanMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanTravlMax->Modified )
    {
        try
        {
            panMaxTrackBar->Value = Convert::ToInt32(inputPanTravlMax->Text, 10);
            inputPanTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating pan max trackbar.\r\n");
#ifdef DEBUG
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
#endif
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: PanCenterEdit_ValueChanged
// Desc: User text input handler for pan center edit control.
//--------------------------------------------------------------------------------------
System::Void Form1::PanCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputPanCenter->Modified)
    {
        try
        {
            panCenterTrackBar->Value = Convert::ToInt32(inputPanCenter->Text, 10) - 2100;

            int temp = panMinTrackBar->Value + panCenterTrackBar->Value;
            if (temp >= 0)
                inputPanTravlMin->Text = Convert::ToString(temp); 

            temp = panMaxTrackBar->Value - panCenterTrackBar->Value;
            if (temp >= 0)
                inputPanTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating pan trackbars.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
        
        inputPanCenter->Modified = false;
    }
}

System::Void Form1::TiltMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltTravlMin->Modified )
    {
        try
        {
            tiltMinTrackBar->Value = Convert::ToInt32(inputTiltTravlMin->Text, 10);
            inputTiltTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating tilt min trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

System::Void Form1::TiltMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltTravlMax->Modified )
    {
        try
        {
            tiltMaxTrackBar->Value = Convert::ToInt32(inputTiltTravlMax->Text, 10);
            inputTiltTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating tilt max trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

System::Void Form1::TiltCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputTiltCenter->Modified)
    {
        try
        {
            tiltCenterTrackBar->Value = Convert::ToInt32(inputTiltCenter->Text, 10) - 2100;

            int temp = tiltMinTrackBar->Value + tiltCenterTrackBar->Value;
            if (temp >= 0)
                inputTiltTravlMin->Text = Convert::ToString(temp); 

            temp = tiltMaxTrackBar->Value - tiltCenterTrackBar->Value;
            if (temp >= 0)
                inputTiltTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating tilt trackbars.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }

        inputTiltCenter->Modified = false;
    }
}

System::Void Form1::RollMinTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollTravlMin->Modified )
    {
        try
        {
            rollMinTrackBar->Value = Convert::ToInt32(inputRollTravlMin->Text, 10);
            inputRollTravlMin->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating roll min trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

System::Void Form1::RollMaxTravelEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollTravlMax->Modified )
    {
        try
        {
            rollMaxTrackBar->Value = Convert::ToInt32(inputRollTravlMax->Text, 10);
            inputRollTravlMax->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating roll max trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

System::Void Form1::RollCenterEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( inputRollCenter->Modified)
    {
        try
        {
            rollCenterTrackBar->Value = Convert::ToInt32(inputRollCenter->Text, 10) - 2100;

            int temp = rollMinTrackBar->Value + rollCenterTrackBar->Value;
            if (temp >= 0)
                inputRollTravlMin->Text = Convert::ToString(temp); 

            temp = rollMaxTrackBar->Value - rollCenterTrackBar->Value;
            if (temp >= 0)
                inputRollTravlMax->Text = Convert::ToString(temp); 
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating roll trackbars.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }

        inputRollCenter->Modified = false;
    }
}

System::Void Form1::TiltGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainTilt->Modified )
    {
        try
        {
            rollGainTrackBar->Value = Convert::ToInt32(servoGainTilt->Text, 10);
            servoGainTilt->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating tilt gain trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: PanGainEdit_ValueChanged
// Desc: Handler for user entry of text into edit control
//--------------------------------------------------------------------------------------
System::Void Form1::PanGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainPan->Modified )
    {
        try
        {
            panGainTrackBar->Value = Convert::ToInt32(servoGainPan->Text, 10);
            servoGainPan->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating pan gain trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: RollGainEdit_ValueChanged
// Desc: Handler for user entry of text into edit control
//--------------------------------------------------------------------------------------
System::Void Form1::RollGainEdit_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
    if ( servoGainRoll->Modified )
    {
        try
        {
            rollGainTrackBar->Value = Convert::ToInt32(servoGainRoll->Text, 10);
            servoGainRoll->Modified = false;
        }
        catch (System::Exception^ e)
        {
            Serial_output_box->Text += String::Format("ERROR updating roll gain trackbar.\r\n");
            Serial_output_box->Text += e->Message;
            Serial_output_box->Text += String::Format("\r\n");
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: OnCalWizard_Menu
// Desc: Menu click handler
//--------------------------------------------------------------------------------------
System::Void Form1::OnCalWizard_Menu(System::Object^  sender, System::EventArgs^  e)
{
    _CalWizard = gcnew CalWizard;
    _CalWizard->Begin(AXISALIGNMENT);
    _CalWizard->Show();
}

//--------------------------------------------------------------------------------------
// Func: OnCalWizardRot_Menu
// Desc: Menu click handler
//--------------------------------------------------------------------------------------
System::Void Form1::OnCalWizardRot_Menu(System::Object^  sender, System::EventArgs^  e)
{
    _CalWizard = gcnew CalWizard;
    _CalWizard->Begin(MINMAXTRACKING);
    _CalWizard->Show();
}

//--------------------------------------------------------------------------------------
// Func: OnExportSettingsToFile_Menu
// Desc: Exports settings from the UI to a file.
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
*/
//--------------------------------------------------------------------------------------
System::Void Form1::OnExportSettingsToFile_Menu(System::Object^ sender, System::EventArgs^ e)
{
    String^ fileName = "textfile.txt";
    SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog;

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
            sw->Close();
        }
        catch (Exception^ e)
        {

        }
    }
}

//--------------------------------------------------------------------------------------
// Func: OnImportSettingsFromFile_Menu
// Desc: Imports tracker settings from a file into the UI.
//--------------------------------------------------------------------------------------
System::Void Form1::OnImportSettingsFromFile_Menu(System::Object^ sender, System::EventArgs^ e)
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
                }
                count++;
            }
            UpdateUIFromSettings(settings);
            Serial_output_box->Text += String::Format("Settings successfully loaded\r\n");
        }
        catch (Exception^ e)
        {
            if (dynamic_cast<System::IO::FileNotFoundException^>(e))
            {
                Serial_output_box->Text += String::Format("File not found!\r\n");
            }
            else
            {
                Serial_output_box->Text += String::Format("File error!\r\n");
            }
        }
    }
}