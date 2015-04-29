#include "ftnoir_tracker_gvrs.h"
#include "ftnoir_tracker_udp/ftnoir_tracker_udp.h"
#include "opentrack/plugin-api.hpp"
#include "opentrack/plugin-support.h"
#include <QCoreApplication>
#include <QLibrary>


GVRS_Tracker::GVRS_Tracker() : last_recv_pose { 0,0,0, 0,0,0 }, should_quit(false) {
	QString fullPath = QCoreApplication::applicationDirPath() + "/" + "libopentrack-tracker-udp.dll";
	handle = new QLibrary(fullPath);
	if(handle){
		ptrTracker = (TRACKER_PTR) handle->resolve("GetConstructor");
	}
}

GVRS_Tracker::~GVRS_Tracker()
{
    should_quit = true;
    wait();			
}

void GVRS_Tracker::run() {
	if(ptrTracker){
		ptrTracker->run();
	}
	
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

void GVRS_Tracker::start_tracker(QFrame* videoframe)
{
	start();
	
	//if(handle){
		//ptrTrackerStart = (TRACKER_PTRSTART) handle->resolve("start_tracker");
		//if(ptrTrackerStart)
			//ptrTrackerStart(videoframe);
	//}
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
