# DIY-Head-Tracker
Head tracker for RC FPV purposes. Project father: Denis Frie.

The purpose of this repository is to make stable platform for future development of the great work started by Denis Frie.

## Basic setup
Head Tracker (HT) is installed on FPV gogles, weared on your head. It is connected to a trainer port of your RC transmitter and supplied from some power source. It uses from one to three servo channels for: yaw, tilt and rarely for roll.
In your RC model camera is mounted on gimbal. Gimbal is driven by its servos accordingly to movements of your head.
There is also an extended version, which uses readily available serial communication Bluetooth modules to get rid of the cable between your head and your RC transmitter.

In this repository you will find:
- instructions how to build your own HT (.docx files)
- firmware written in C++ for your HT Arduino board (you will need to compile it and upload using Arduino IDE)
- Windows app written in C++ to calibrate, setup and test your HT (EXE and sources for Microsoft Visual Studio)

## Version history
Please see ChangeLog.txt and HeadTrackerFW.ino

Pre github versions are archived here:
https://github.com/kniuk/DIY-Head-Tracker/tree/master/archive

## Discussion
http://www.rcgroups.com/forums/showthread.php?t=1677559

## Credits (perhaps not all):
- Dennis Frie - author of the project:  Versions up to 0.08 (2012)
- Mark Mansur : Version 1.02 to 1.04 (2013)
- Chris Stephens - RCGroups 'hangarspace' : Versions 1.05 and 1.06 (2018)
- Carlo Nebuloni - RCGroups user 'carlonb' : Version 1.07 (2019)
- RCGroups user 'mric3412' : Version 1.07 contributor (2019)
- Alexander ELtsyn - RCGroups 'AE_' : Version 1.08 (2019)
- Jacek Wielogorski - RCGroups 'kniuk' : Version 1.09 (2020)

## Collaboration
Collaborators welcome, please feel free to contact kniuk@data.pl
