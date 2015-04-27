gcc -c -I C:\ftnoir_tracker_gvrs -I C:\opentrack-opentrack-2.3-rc9 -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtCore -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtWidgets -I C:\Qt\Qt5.4.1\5.4\mingw491_32\include\QtGui -std=c++11 ftnoir_tracker_gvrs_dll.cpp 2>compile_log.txt
cd C:\ftnoir_tracker_gvrs\
gcc -shared -o libopentrack-tracker-gvrs.dll ftnoir_tracker_gvrs_dll.o 2>link_log.txt
