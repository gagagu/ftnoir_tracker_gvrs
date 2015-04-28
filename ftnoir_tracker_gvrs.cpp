#include "ftnoir_tracker_gvrs.h"
#include "ftnoir_tracker_udp/ftnoir_tracker_udp.h"
#include "opentrack/plugin-api.hpp"
#include "opentrack/plugin-support.h"
#include <QCoreApplication>
#include <QLibrary>

//#include <stdio.h>
//#include <windows.h>

GVRS_Tracker::GVRS_Tracker() : last_recv_pose { 0,0,0, 0,0,0 }, should_quit(false) {}

GVRS_Tracker::~GVRS_Tracker()
{
    should_quit = true;
    wait();
}

void GVRS_Tracker::run() {
	/*HINSTANCE hInstLibrary = LoadLibrary("libopentrack-tracker-udp.dll");
	if (hInstLibrary)
    {
		FTNoIR_Tracker* track = (FTNoIR_Tracker)GetProcAddress(hInstLibrary, "GetConstructor");
	} else {
		// error output needed
		fprintf(stderr, "gvrs tracker: can't load libopentrack-tracker-udp.dll\n");
	}*/
	//QString fullPath = QCoreApplication::applicationDirPath() + "/" + "libopentrack-tracker-udp.dll";
	//handle = new QLibrary(fullPath);
	//Constructor = (CTOR_FUNPTR) handle->resolve("GetConstructor");

    QByteArray datagram;
    datagram.resize(sizeof(last_recv_pose));
    (void) sock.bind(QHostAddress::Any, (int) s.port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    for (;;) {
        if (should_quit)
            break;
        QMutexLocker foo(&mutex);
        while (sock.hasPendingDatagrams()) {
            sock.readDatagram((char * ) last_recv_pose, sizeof(double[6]));
        }
        msleep(1);
    }
}

void GVRS_Tracker::start_tracker(QFrame*)
{
	start();
}

void GVRS_Tracker::data(double *data)
{
    QMutexLocker foo(&mutex);
    for (int i = 0; i < 6; i++)
        data[i] = last_recv_pose[i];
}

extern "C" OPENTRACK_EXPORT ITracker* GetConstructor()
{
    return new GVRS_Tracker;
}
