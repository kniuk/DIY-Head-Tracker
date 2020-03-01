//--------------------------------------------------------------------------------------
// File:    CalWizard.cpp (C++/CLI)
// Desc:    Implements the calibration wizard UI.
//
// Hist:    4/15/13 - Mark Mansur - initial creation.
//--------------------------------------------------------------------------------------
/*
    Wizard steps:
    0: Welcome/overview
    1: IMU is upright, 0 degrees. Mag X/Y values, gyro cal, accel Z max
    2: IMU is upright, panned 180 degrees. Mag X/Y/Z values
    3: IMU tilt forward 90 degrees. Accel X max
    4: IMU tilt backward -90 degrees. Accel X min
    5: IMU roll left -90 degrees. Accel Y max
    6: IMU roll right +90 degrees. Accel Y min
    7: IMU upside down, panned 0 degrees. mag Z value, accel Z min
    8: Save calibration
    9: Complete!
*/

#include "StdAfx.h"
#include "CalWizard.h"
#include "HeadTrackerHardware.h"

using namespace HeadTrackerGUI;
using namespace System::Resources;

//--------------------------------------------------------------------------------------
// Func: CalWizard_Load
// Desc: Handler called by system when the wizard is first loaded into memory.
//--------------------------------------------------------------------------------------
System::Void CalWizard::CalWizard_Load(System::Object^ sender, System::EventArgs^ e)
{
    mainUpdateTimer->Enabled = false;
    SetupUIForStep(0);
}

//--------------------------------------------------------------------------------------
// Func: MainUpdateTimer_Tick
// Desc: Handler for the serial update timer. This handler reads any new data from the
//       serial driver's FIFO buffer, converts, and stores the results.
//--------------------------------------------------------------------------------------
System::Void CalWizard::MainUpdateTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
    if (TrackerWrap::Tracker->Port->IsOpen)
    {
        while (TrackerWrap::Tracker->Port->BytesToRead > 0)
        {
            serialbyte = TrackerWrap::Tracker->Port->ReadChar();

            if (TrackerWrap::Tracker->MagAccelStreaming)
            {
                if (serialbyte == 13)
                {
                    SerialData[0] -= 3000;
                    SerialData[1] -= 3000;
                    SerialData[2] -= 3000;
                    SerialData[3] -= 3000;
                    SerialData[4] -= 3000;
                    SerialData[5] -= 3000;
                    
                    if ( Serialindex == 5 )
                    {
                        // Mag Y and Z swapped on purpose
                        MagXReading = (int)SerialData[0];
                        MagYReading = (int)SerialData[2];
                        MagZReading = (int)SerialData[1];
                        AccXReading = (int)SerialData[3];
                        AccYReading = (int)SerialData[4];
                        AccZReading = (int)SerialData[5];

                        MagCurXLbl->Text = Convert::ToString(MagXReading);
                        MagCurYLbl->Text = Convert::ToString(MagYReading);
                        MagCurZLbl->Text = Convert::ToString(MagZReading);
                        AccCurXLbl->Text = Convert::ToString(AccXReading);
                        AccCurYLbl->Text = Convert::ToString(AccYReading);
                        AccCurZLbl->Text = Convert::ToString(AccZReading);
                    }
                    SerialData[0] = 0;
                    SerialData[1] = 0;
                    SerialData[2] = 0;
                    SerialData[3] = 0;
                    SerialData[4] = 0;
                    SerialData[5] = 0;

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
// Func: PreviousBtn_Click
// Desc: Previous button click handler.
//--------------------------------------------------------------------------------------
System::Void CalWizard::PreviousBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
    CurrentStep--;
    SetupUIForStep(CurrentStep);
    
}

//--------------------------------------------------------------------------------------
// Func: NextBtn_Click
// Desc: Next button click handler.
//--------------------------------------------------------------------------------------
System::Void CalWizard::NextBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
    CompleteStep(CurrentStep++);
    SetupUIForStep(CurrentStep);
}

//--------------------------------------------------------------------------------------
// Func: CancelBtn_Click
// Desc: Cancel button click handler.
//--------------------------------------------------------------------------------------
System::Void CalWizard::CancelBtn_Click(System::Object^  sender, System::EventArgs^  e)
{
    TrackerWrap::Tracker->StreamMagAccelData(false);
    mainUpdateTimer->Enabled = false;
    Close();
}

//--------------------------------------------------------------------------------------
// Func: UpdateCalc
// Desc: Updates the calibration calculations and updates the UI to reflect new values.
//--------------------------------------------------------------------------------------
System::Void CalWizard::UpdateCalc()
{
    MagXOffset = (int)((MagX1 + MagX2) * 0.5); 
    MagYOffset = (int)((MagY1 + MagY2) * 0.5);
    MagZOffset = (int)((MagZ1 + MagZ2) * 0.5);

    AccXOffset = (AccXMax + AccXMin) / -2; 
    AccYOffset = (AccYMax + AccYMin) / -2;
    AccZOffset = (AccZMax + AccZMin) / -2;

    MagXOffsetLbl->Text = Convert::ToString(MagXOffset);
    MagYOffsetLbl->Text = Convert::ToString(MagYOffset);
    MagZOffsetLbl->Text = Convert::ToString(MagZOffset);

    AccXOffsetLbl->Text = Convert::ToString(AccXOffset);
    AccYOffsetLbl->Text = Convert::ToString(AccYOffset);
    AccZOffsetLbl->Text = Convert::ToString(AccZOffset);
}

//--------------------------------------------------------------------------------------
// Func: CompleteStep
// Desc: Gathers the necessary info and performs necessary processing from the user's
//       completion of the specified step. Used to gather sensor data when the user
//       presses the next button.
//--------------------------------------------------------------------------------------
System::Void CalWizard::CompleteStep(int Step)
{
    switch ( Step )
    {
    case 0:
        // Start collecting data
        mainUpdateTimer->Enabled = true;
        // Start mag and accel output from device for calibration. This call will
        // also stop any other stream data.
        TrackerWrap::Tracker->StreamMagAccelData(true);
        break;
    case 1:
        {
            TrackerWrap::Tracker->CalibrateGyro();
            MagX1 = MagXReading;
            MagY1 = MagYReading;
            AccZMax = AccZReading;
            UpdateCalc();
        }
        break;
    case 2:
        {
            MagX2 = MagXReading;
            MagY2 = MagYReading;
            MagZ1 = MagZReading;
            UpdateCalc();
        }
        break;
    case 3:
        {
            AccXMax = AccXReading;
            UpdateCalc();
        }
        break;
    case 4:
        {
            AccXMin = AccXReading;
            UpdateCalc();
        }
        break;
    case 5:
        {
            AccYMax = AccYReading;
            UpdateCalc();
        }
        break;
    case 6:
        {
            AccYMin = AccYReading;
            UpdateCalc();
        }
        break;
    case 7:
        {
            MagZ2 = MagZReading;
            AccZMin = AccZReading;
            UpdateCalc();
        }
        break;
    case 8:
        {
            TrackerWrap::Tracker->StoreAccelCal(AccXOffset, AccYOffset, AccZOffset);
            TrackerWrap::Tracker->StoreMagCal(MagXOffset, MagYOffset, MagZOffset);
        }
        break;
    case 9:
        TrackerWrap::Tracker->StreamMagAccelData(false);
        mainUpdateTimer->Enabled = false;
        Close();
        break;
    }
}

//--------------------------------------------------------------------------------------
// Func: SetupUIForStep
// Desc: Initializes the UI to display to the user for the specified step.
//--------------------------------------------------------------------------------------
System::Void CalWizard::SetupUIForStep(int Step)
{
    ResourceManager^ rm = gcnew ResourceManager("HeadTrackerGUI.Resources", GetType()->Assembly);
    switch ( Step )
    {
    case 0:
        {
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz0");
        }
        break;
    case 1:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position1");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz1");
        }
        break;
    case 2:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position2");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz2");
        }
        break;
    case 3:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position3");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz3");
        }
        break;
    case 4:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position4");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz4");
        }
        break;
    case 5:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position5");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz5");
        }
        break;
    case 6:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position6");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz6");
        }
        break;
    case 7:
        {
            WizardPictureBox->Image = (System::Drawing::Image^)rm->GetObject(L"Position7");
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz7");
        }
        break;
    case 8:
        {
            delete WizardPictureBox->Image;
            WizardPictureBox->Image = nullptr;
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz8");
        }
        break;
    case 9:
        {
            WizardInstructionsLbl->Text = (System::String^)rm->GetObject(L"CalWiz9");

            WizardNextBtn->Text = "Finish";
            WizardPrevBtn->Enabled = false;
            WizardCancelBtn->Enabled = false;
        }
        break;
    }

    if ( Step == 0 )
    {
        WizardPrevBtn->Enabled = false;
    }
    else if ( Step != 9 )
    {
        WizardPrevBtn->Enabled = true;
    }

    if ( Step != 9 )
    {
        WizardNextBtn->Text = "Next";
    }
}