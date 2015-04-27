g++ -c -I C:\opentrack_build -I C:\ftnoir_tracker_gvrs -I C:\opentrack-opentrack-2.3-rc9 -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtCore -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtWidgets -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtGui -std=c++11 ftnoir_tracker_gvrs_dll.cpp ftnoir_tracker_gvrs_dialog.cpp ftnoir_tracker_gvrs.cpp 2>compile_log.txt
cd C:\ftnoir_tracker_gvrs\
g++ -shared -o libopentrack-tracker-gvrs.dll ftnoir_tracker_gvrs_dll.o ftnoir_tracker_gvrs_dialog.o ftnoir_tracker_gvrs.o C:\Qt\Qt5.4.1\5.4\mingw491_32\lib\libQt5Core.a C:\Qt\Qt5.4.1\5.4\mingw491_32\lib\libQt5Gui.a C:\Qt\Qt5.4.1\5.4\mingw491_32\lib\libQt5Widgets.a C:\opentrack_build\libopentrack-api.a 2>link_log.txt


