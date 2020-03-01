#include "StdAfx.h"
#include "MagCalibrate.h"
#include "HeadTrackerHardware.h"
#include "Windows.h"

using namespace PPM_expander_and_headtracker;

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::StartCal_Click(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 1;
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$PLEN") );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAST") );
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::StopCal_Click(System::Object^  sender, System::EventArgs^  e)
{
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAEN") );
    headtracker_active = 0;
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::ClearPlot_Click(System::Object^  sender, System::EventArgs^  e)
{
    DataChart->Series["Series1"]->Points->Clear();
    DataChart->Series["Series2"]->Points->Clear();
    DataChart->Series["Series3"]->Points->Clear();
    DataChart->Series["Series4"]->Points->Clear();
    PointIndex = 0;
    DataChart->ChartAreas["ChartArea1"]->BackColor = System::Drawing::Color::Transparent;
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::StageOneSet_Click(System::Object^  sender, System::EventArgs^  e)
{
    x1 = xreading; 
    y1 = yreading; 

    StageOneXLbl->Text = Convert::ToString(x1); 
    StageOneYLbl->Text = Convert::ToString(y1); 

    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::StageTwoSet_Click(System::Object^  sender, System::EventArgs^  e)
{
    x2 = xreading; 
    y2 = yreading; 
    z1 = zreading; 

    StageTwoXLbl->Text = Convert::ToString(x2); 
    StageTwoYLbl->Text = Convert::ToString(y2); 
    StageTwoZLbl->Text = Convert::ToString(z1); 

    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: 
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::StageThreeSet_Click(System::Object^  sender, System::EventArgs^  e)
{
    z2 = zreading;
    StageThreeZLbl-> Text = Convert::ToString(z2);
    UpdateCalc(); 
}

//--------------------------------------------------------------------------------------
// Func: SaveCal_Click
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::SaveCal_Click(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 0;
    
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAEN") );
    Sleep(250);

    String^ xtemp = Convert::ToString(xoffset + 2000);
    String^ ytemp = Convert::ToString(yoffset + 2000);
    String^ ztemp = Convert::ToString(zoffset + 2000);

    TrackerWrap::Tracker->Port->WriteLine(String::Format("${0},{1},{2}MA", xtemp, ytemp, ztemp) );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$PLEN") );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAST") );

    headtracker_active = 1;
}

//--------------------------------------------------------------------------------------
// Func: ResetCal_Click
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::ResetCal_Click(System::Object^  sender, System::EventArgs^  e)
{
    headtracker_active = 0;

    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAEN") );
    Sleep(250);
    
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$2000,2000,2000MA") );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$PLEN") );
    TrackerWrap::Tracker->Port->WriteLine(String::Format("$CAST") );
    
    headtracker_active = 1;
}

//--------------------------------------------------------------------------------------
// Func: UpdateTimer_Tick
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::UpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
    if (TrackerWrap::Tracker->Port -> IsOpen)
    {
        while (TrackerWrap::Tracker->Port -> BytesToRead > 0)
        {
            serialbyte = TrackerWrap::Tracker->Port->ReadChar();
            
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

                    DataChart->Series["Series1"]->Points->AddXY(PointIndex, SerialData[0]);
                    DataChart->Series["Series3"]->Points->AddXY(PointIndex, SerialData[1]);
                    DataChart->Series["Series4"]->Points->AddXY(PointIndex, SerialData[2]);

                    xreading = (int)SerialData[0];
                    yreading = (int)SerialData[2];
                    zreading = (int)SerialData[1];
                    
                    SerialData[0] = 0;
                    SerialData[1] = 0;
                    SerialData[2] = 0;
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
        }
    }
}

//--------------------------------------------------------------------------------------
// Func: UpdateCalc
// Desc: 
//--------------------------------------------------------------------------------------
System::Void MagCalibrate::UpdateCalc()
{
    xoffset = (int)((x1 + x2) * (0.5)); 
    yoffset = (int)((y1 + y2) * (0.5));
    zoffset = (int)((z1 + z2) * (0.5));

    XOffsetLbl->Text = Convert::ToString(xoffset);
    YOffsetLbl->Text = Convert::ToString(yoffset);
    ZOffsetLbl->Text = Convert::ToString(zoffset);
}