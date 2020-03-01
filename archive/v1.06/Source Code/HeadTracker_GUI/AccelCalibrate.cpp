#include "StdAfx.h"
#include "AccelCalibrate.h"
#include "HeadTrackerHardware.h"
#include "Windows.h"

using namespace PPM_expander_and_headtracker;


//--------------------------------------------------------------------------------------
// Func: AccelCalibrate_Load
// Desc: Form load handler
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::AccelCalibrate_Load(System::Object^  sender, System::EventArgs^  e)
{

}

System::Void AccelCalibrateForm::MainUpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
    if (TrackerWrap::Tracker->Port->IsOpen)
    {
        while (TrackerWrap::Tracker->Port->BytesToRead > 0)
        {
            serialbyte = (TrackerWrap::Tracker->Port->ReadChar());

            if (headtracker_active)
            {
                if (serialbyte == 13)
                {
                    PointIndex++;

                    if (PointIndex == 1)
                    {
                        DataChart->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::WhiteSmoke;
                    }

                    SerialData[0] -= 3000;
                    SerialData[1] -= 3000;
                    SerialData[2] -= 3000;

                    XCurValLbl->Text = Convert::ToString(SerialData[0]);
                    YCurValLbl->Text = Convert::ToString(SerialData[1]);
                    ZCurValLbl->Text = Convert::ToString(SerialData[2]);

                    DataChart->Series["Series1"] -> Points -> AddXY(PointIndex, SerialData[0]);
                    DataChart->Series["Series3"] -> Points -> AddXY(PointIndex, SerialData[1]);
                    DataChart->Series["Series4"] -> Points -> AddXY(PointIndex, SerialData[2]);

                    xreading = (int)SerialData[0];
                    yreading = (int)SerialData[1];
                    zreading = (int)SerialData[2];

                    SerialData[0] = 0.0;
                    SerialData[1] = 0.0;
                    SerialData[2] = 0.0;
                    Serialindex = 0;
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
        } // while serial data is pulled in
    } // if port is open
}

//--------------------------------------------------------------------------------------
// Func: StartBtnClicked
// Desc: User pressed the start button
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::StartBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 1;
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$PLEN") );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$GRAV") );
}

//--------------------------------------------------------------------------------------
// Func: StopBtnClicked
// Desc: Stop calibration button press handler.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::StopBtnClicked(System::Object^ sender, System::EventArgs^ e)
{
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$GREN") );
}

//--------------------------------------------------------------------------------------
// Func: ClearPlotBtnClicked
// Desc: User clicked button to clear plot.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::ClearPlotBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    DataChart->Series["Series1"]->Points->Clear();
    DataChart->Series["Series2"]->Points->Clear();
    DataChart->Series["Series3"]->Points->Clear();
    DataChart->Series["Series4"]->Points->Clear();
    DataChart->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::Transparent;
    PointIndex = 0;
}

//--------------------------------------------------------------------------------------
// Func: ResetCalBtnClicked
// Desc: User pressed the reset calibration button.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::ResetCalBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 0;

    // Stop mag cal
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAEN") );
    Sleep(250);
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$2000,2000,2000ACC") );

    headtracker_active = 1;
}

//--------------------------------------------------------------------------------------
// Func: SetXMaxBtnClicked
// Desc: User clicked button to set X axis max value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetXMaxBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    xMax->Text = Convert::ToString(xreading); 
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SetXMinBtnClicked
// Desc: User clicked button to set X axis min value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetXMinBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    xMin->Text = Convert::ToString(xreading); 
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SetYMaxBtnClicked
// Desc: User clicked button to set Y axis max value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetYMaxBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    yMax->Text = Convert::ToString(yreading); 
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SetYMinBtnClicked
// Desc: User clicked button to set Y axis min value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetYMinBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    yMin->Text = Convert::ToString(yreading); 
    UpdateCalc();
}

//--------------------------------------------------------------------------------------
// Func: SetZMaxBtnClicked
// Desc: User clicked button to set Z axis max value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetZMaxBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    zMax->Text = Convert::ToString(zreading); 
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SetZMinBtnClicked
// Desc: User clicked button to set X axis min value.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SetZMinBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    zMin->Text = Convert::ToString(zreading); 
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SaveBtnClicked
// Desc: User clicked button to upload calibration to hardware.
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::SaveBtnClicked(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 0;

    TrackerWrap::Tracker->Port->WriteLine(String::Format("$GREN") );
    Sleep(250);

    String^ xtemp = Convert::ToString(xoffset + 2000);
    String^ ytemp = Convert::ToString(yoffset + 2000);
    String^ ztemp = Convert::ToString(zoffset + 2000);

    TrackerWrap::Tracker->Port->WriteLine(String::Format("${0},{1},{2}ACC", xtemp, ytemp, ztemp) );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$GRAV") );
    
    headtracker_active = 1;
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void AccelCalibrateForm::UpdateCalc()
{
    xoffset = (Convert::ToInt32(xMax->Text) + Convert::ToInt32(xMin->Text)) / -2; 
    yoffset = (Convert::ToInt32(yMax->Text) + Convert::ToInt32(yMin->Text)) / -2; 
    zoffset = (Convert::ToInt32(zMax->Text) + Convert::ToInt32(zMin->Text)) / -2; 

    XOffsetLbl-> Text = Convert::ToString(xoffset);
    YOffsetLbl-> Text = Convert::ToString(yoffset);
    ZOffsetLbl-> Text = Convert::ToString(zoffset);
}