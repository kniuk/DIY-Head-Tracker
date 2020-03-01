//--------------------------------------------------------------------------------------
// File:    HeadTrackerHardware.h 
// Desc:    Implements a very basic hardware class for simple communications with Dennis
//          Frie's open source head tracker. Class client needs to read the port for
//          any streamed data; this object does not buffer replies from the hardware.
//
// Hist:    4/15/13 - Mark Mansur - initial creation
//--------------------------------------------------------------------------------------
#pragma once
#include "Windows.h"

using namespace System;

#define HT_TILT_REVERSE_BIT     0x01
#define HT_ROLL_REVERSE_BIT     0x02
#define HT_PAN_REVERSE_BIT      0x04




// Settings
//
value struct HTSETTINGS {
    int LPTiltRoll;         // Firmware: tiltRollBeta
    int LPPan;              // Firmware: panBeta
    int GyroWeightTiltRoll; // Firmware: gyroWeightTiltRoll
    int GyroWeightPan;      // Firmware: GyroWeightPan
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
};

delegate void LogFlushDelegate();
delegate void LogCharDelegate(int ch);
delegate void LogDelegate(String^ line);

//---------------------------------------------------------------------------------------
//  Class: HeadTracker
//      Quick and dirty implementation of a head tracker helper. Application still has
//      to read the stream data when sensor streaming is enabled.
//---------------------------------------------------------------------------------------
ref class HeadTracker {

    // The count of settings values returned from the head tracker. Update this
    // when new settings are added to the firmware. +1 for newline.
#define HT_SETTINGS_COUNT       21

public: // Events

    LogCharDelegate^ LogChar;
    LogDelegate^ Log;
    LogFlushDelegate^ LogFlush;
public: // methods

    HeadTracker() {
        Port = gcnew System::IO::Ports::SerialPort();
    }

    ~HeadTracker() {
    }



    System::Void Open(String^ ComPort, boolean ForceOpen) {
        _AccelStreaming = false;
        _MagStreaming = false;
        _MagAccelStreaming = false;
        _TrackStreaming = false;
        _Streaming = false;
        Port->PortName = ComPort;
        Port->BaudRate = 57600;
        Port->ReadTimeout = 2000;
        _FWVersion = 0.0;
        _HWVersion = "";
        try { Port->Open(); } catch (System::Exception ^ e) { }

        if (Port->IsOpen) {
            DiscardBuffer();
            StreamTrackingData(false);
            Sleep(500);
            DiscardBuffer();
            GetVersion();

            // Sometimes version retrieval early in power-up doesn't work. Try again.
            if (_FWVersion == 0.0) {
                Sleep(500);
                GetVersion();
            }

            // If it failed again, the open request failed. IF we're forcing the port 
            // open, we don't care about failures, leave the COM port open.
            if (_FWVersion == 0.0 && !ForceOpen)
                this->Close();
        }
    }

    System::Void Close() {
        if (Log != nullptr) Log("> Disconnecting");
        _FWVersion = 0.0;
        _HWVersion = "";
        _AccelStreaming = false;
        _MagStreaming = false;
        _MagAccelStreaming = false;
        _TrackStreaming = false;
        _Streaming = false;
        Port->Close();
    }

    bool IsOpen() {
        try {
            return ((Port != nullptr) && (Port->IsOpen));
        } catch (Exception^) {
            return false;
        }
    }

    bool IsDataAvailable() {
        return (IsOpen() && (Port->BytesToRead > 0));
    }

    int ReadChar() {
        if (IsOpen() && (Port->BytesToRead > 0)) {
            int ch = Port->ReadChar();
            if (LogChar != nullptr) LogChar(ch);
            if ( (LogFlush!=nullptr) && ((ch <= 13) || (Port->BytesToRead <= 0))) LogFlush();
            return ch;
        } else {
            return 0;
        }
    }

    System::String^ ReadLine() {
        System::String^ line;

        try {
            line = Port->ReadLine();
            if (Log != nullptr) Log(line);
        } catch (System::Exception ^ e) {
            return "Error";
        }
        return line;
    }

    /// Send long command safely by 32 byte chunks
    bool WriteLine(String^ command) {
        if (String::IsNullOrWhiteSpace(command)) return false;
        if (Log != nullptr) Log("> "+command);
        try {
            if (Port->IsOpen) {
                DiscardBuffer();
                int p = 0;
                while (true) {
                    // Get chunk len
                    int len = command->Length - p;
                    if (len > 32) len = 32;

                    Port->Write(command->Substring(p, len));
                    p += len;

                    if (p >= command->Length) return true;
                    Sleep(100);
                }
                return true;
            }
        } catch (System::Exception ^ e) {
        }
        return false;
    }
    void DiscardBuffer() {
        while(IsDataAvailable() ) {
            Port->DiscardInBuffer();
        }
        while (IsOpen() && (Port->BytesToWrite > 0)) {
            Port->DiscardOutBuffer();
        }
        if (LogFlush != nullptr) LogFlush();
    }

    array<System::String^>^ GetPortNames() {
        return Port->GetPortNames();
    }

    HTSETTINGS RetrieveSettings() {
        HTSETTINGS ht;
        if (IsOpen()) {
            DiscardBuffer();
            WriteLine("$GSET");
            String^ Line = ReadLine();
            try {
                if (Line->Substring(0, 5)->Equals("$SET$")) {
                    String^ toParse = Line->Substring(5);
                    System::Globalization::CultureInfo^ ci = gcnew System::Globalization::CultureInfo("en-US");
                    System::Globalization::NumberFormatInfo^ fi = ci->NumberFormat;
                    fi->NumberDecimalSeparator = ".";

                    // Par5se the rest of the response
                    array<wchar_t>^ delim = { ',','\r','\n' };
                    array<String^>^ items = toParse->Split(delim);
                    if (HT_SETTINGS_COUNT <= items->Length) {
                        ht.LPTiltRoll = (int)Convert::ToSingle(items[0], fi);
                        ht.LPPan = (int)Convert::ToSingle(items[1], fi);
                        ht.GyroWeightTiltRoll = (int)Convert::ToSingle(items[2], fi);
                        ht.GyroWeightPan = (int)Convert::ToSingle(items[3], fi);
                        ht.ServoGainTilt = (int)Convert::ToSingle(items[4], fi);
                        ht.ServoGainPan = (int)Convert::ToSingle(items[5], fi);
                        ht.ServoGainRoll = (int)Convert::ToSingle(items[6], fi);
                        ht.ServoReverse = Convert::ToByte(items[7], 10);
                        ht.PanCenter = Convert::ToInt32(items[8], 10);
                        ht.PanMin = Convert::ToInt32(items[9], 10);
                        ht.PanMax = Convert::ToInt32(items[10], 10);
                        ht.TiltCenter = Convert::ToInt32(items[11], 10);
                        ht.TiltMin = Convert::ToInt32(items[12], 10);
                        ht.TiltMax = Convert::ToInt32(items[13], 10);
                        ht.RollCenter = Convert::ToInt32(items[14], 10);
                        ht.RollMin = Convert::ToInt32(items[15], 10);
                        ht.RollMax = Convert::ToInt32(items[16], 10);
                        ht.PanCh = Convert::ToByte(items[17], 10);
                        ht.TiltCh = Convert::ToByte(items[18], 10);
                        ht.RollCh = Convert::ToByte(items[19], 10);
                        ht.BluetoothMode = Convert::ToByte(items[20], 10);
                    }
                }
            } catch (System::Exception ^ e) {

            }
        }

        return ht;
    }

    System::Void CommitSettings() {
        WriteLine("$SAVE");
    }

    float GetVersion() {
        _FWVersion = 0.0;
        _HWVersion = "";
        if ( IsOpen() ) {
            DiscardBuffer();
            WriteLine("$VERS");
            String^ versLine = ReadLine();
            try {
                if (versLine->Length > 4 && versLine->Substring(0, 4)->Equals("FW: ")) {
                    String^ vers = versLine->Substring(4);
                    // Parse the rest of the response
                    array<wchar_t>^ delim = { ',','\r','\n' };
                    array<String^>^ items = vers->Split(delim);
                    System::Globalization::CultureInfo^ ci = gcnew System::Globalization::CultureInfo("en-US");
                    System::Globalization::NumberFormatInfo^ fi = ci->NumberFormat;
                    fi->NumberDecimalSeparator = ".";

                    _FWVersion = Convert::ToSingle(items[0], fi);
                }
            } catch (System::Exception ^ e) {
            }
            if (_FWVersion > 0) {
                DiscardBuffer();
                WriteLine("$HARD");
                versLine = ReadLine();
                try {
                    if (versLine->Length > 4 && versLine->Substring(0, 4)->Equals("HW: ")) {
                        String^ vers = versLine->Substring(4);
                        // Parse the rest of the response
                        array<wchar_t>^ delim = { ',','\r','\n' };
                        array<String^>^ items = vers->Split(delim);
                        System::Globalization::CultureInfo^ ci = gcnew System::Globalization::CultureInfo("en-US");
                        System::Globalization::NumberFormatInfo^ fi = ci->NumberFormat;

                        _HWVersion = items[0];
                    }
                } catch (System::Exception ^ e) {
                }
            }
        }
        return _FWVersion;
    }

    System::Void StreamTrackingData(bool Start) {
        if (Port->IsOpen) {
            if (Start)
                WriteLine("$PLST");
            else {
                WriteLine("$PLEN");
                _AccelStreaming = false;
                _MagStreaming = false;
                _MagAccelStreaming = false;
            }
            _TrackStreaming = Start;
            _Streaming = Start;
        } else {
            _AccelStreaming = false;
            _MagStreaming = false;
            _MagAccelStreaming = false;
            _TrackStreaming = false;
            _Streaming = false;
        }
    }

    System::Void StreamAccelData(bool Start) {
        if (Port->IsOpen) {
            if (Start)
                WriteLine("$GRAV");
            else {
                WriteLine("$GREN");
                _MagStreaming = false;
                _MagAccelStreaming = false;
                _TrackStreaming = false;
            }
            _AccelStreaming = Start;
            _Streaming = Start;
        }
    }

    System::Void StreamMagData(bool Start) {
        if (Port->IsOpen) {
            if (Start)
                WriteLine("$CAST");
            else {
                WriteLine("$CAEN");
                _AccelStreaming = false;
                _MagAccelStreaming = false;
                _TrackStreaming = false;
            }
            _MagStreaming = Start;
            _Streaming = Start;
        }
    }

    System::Void StreamMagAccelData(bool Start) {
        if (Port->IsOpen) {
            if (Port->IsOpen) {
                if (Start)
                    WriteLine("$CMAS");
                else {
                    WriteLine("$CMAE");
                    _AccelStreaming = false;
                    _MagStreaming = false;
                    _TrackStreaming = false;
                }
                _MagAccelStreaming = Start;
                _Streaming = Start;
            }
        }
    }

    System::Void StoreAccelCal(int XOffset, int YOffset, int ZOffset) {
        if (Port->IsOpen) {
            StreamAccelData(false);
            Sleep(250);

            String^ xtemp = Convert::ToString(XOffset + 2000);
            String^ ytemp = Convert::ToString(YOffset + 2000);
            String^ ztemp = Convert::ToString(ZOffset + 2000);

            WriteLine(String::Format("${0},{1},{2}ACC", xtemp, ytemp, ztemp));
        }
    }

    System::Void ResetAccelCal() {
        StoreAccelCal(0, 0, 0);
    }

    System::Void StoreMagCal(int XOffset, int YOffset, int ZOffset) {
        if (Port->IsOpen) {
            StreamMagData(false);
            Sleep(250);

            String^ xtemp = Convert::ToString(XOffset + 2000);
            String^ ytemp = Convert::ToString(YOffset + 2000);
            String^ ztemp = Convert::ToString(ZOffset + 2000);

            WriteLine(String::Format("${0},{1},{2}MAG", xtemp, ytemp, ztemp));
        }
    }

    System::Void ResetMagCal() {
        StoreMagCal(0, 0, 0);
    }

    System::Void CalibrateGyro() {
        WriteLine(String::Format("$CALG"));
    }

public: // properties

    property bool AccelStreaming
    {
        bool get() {
            return _AccelStreaming;
        }
    }
    property bool MagStreaming
    {
        bool get() {
            return _MagStreaming;
        }
    }
    property bool MagAccelStreaming
    {
        bool get() {
            return _MagAccelStreaming;
        }
    }
    property bool TrackStreaming
    {
        bool get() {
            return _TrackStreaming;
        }
    }

    property bool Streaming
    {
        bool get() {
            return _Streaming;
        }
    }

    property float Version
    {
        float get() {
            return _FWVersion;
        }
    }

    property String^ Hardware
    {
        String^ get() {
            return _HWVersion;
        }
    }

private:

    bool _TrackStreaming;
    bool _MagStreaming;
    bool _AccelStreaming;
    bool _MagAccelStreaming;
    bool _Streaming;
    float _FWVersion;
    String^ _HWVersion = "";
    System::IO::Ports::SerialPort^ Port;

};

ref class TrackerWrap {
public:
    static HeadTracker^ Tracker;
};