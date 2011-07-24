[Files]
Source: ..\..\FieldStripper-build-desktop\release\FieldStripper.exe; DestDir: {app}; 
Source: C:\QtSDK\Desktop\Qt\4.7.3\mingw\bin\libgcc_s_dw2-1.dll; DestDir: {app}; 
Source: C:\QtSDK\Desktop\Qt\4.7.3\mingw\bin\QtCore4.dll; DestDir: {app}; 
Source: C:\QtSDK\Desktop\Qt\4.7.3\mingw\bin\QtGui4.dll; DestDir: {app}; 
Source: C:\Projects\FieldStripper\installer\readme.txt; DestDir: {app}; Flags: isreadme; 
Source: C:\Projects\FieldStripper\installer\exampleInputFile.txt; DestDir: {app}; 
Source: C:\Projects\FieldStripper\installer\sampleFields.frf; DestDir: {app}; 
Source: C:\Projects\FieldStripper\installer\settings.ini; DestDir: {app}; 
Source: C:\QtSDK\Desktop\Qt\4.7.3\mingw\bin\mingwm10.dll; DestDir: {app}; 

[Setup]
AppName=FieldStripper
AppVerName=FieldStripper v1.0
DefaultDirName=FieldStripper
DefaultGroupName=FieldStripper

[Icons]
Name: {group}\FieldStripper; Filename: {app}\FieldStripper.exe; 
