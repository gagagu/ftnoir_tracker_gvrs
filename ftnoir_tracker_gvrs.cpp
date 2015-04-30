#include "ftnoir_tracker_gvrs.h"
#include "ftnoir_tracker_udp/ftnoir_tracker_udp.h"
#include "opentrack/plugin-api.hpp"
#include "opentrack/plugin-support.h"
#include <QCoreApplication>
#include <QLibrary>

GVRS_Tracker::GVRS_Tracker() : last_recv_pose { 0,0,0, 0,0,0 }, should_quit(false) {
	// Find dll for aruco tracker and load it
#if defined(_WIN32)	
	QString fullPath = QCoreApplication::applicationDirPath() + "/" + "libopentrack-tracker-aruco.dll";
	handle = new QLibrary(fullPath);
	if(handle){
		ptrTracker = (TRACKER_PTR) handle->resolve("GetConstructor");
		if(ptrTracker)
			artrack = ptrTracker();
	}
#else
	QByteArray latin1 = QFile::encodeName("libopentrack-tracker-aruco.dll");
    handle = dlopen(latin1.constData(), RTLD_NOW |
#   if defined(__APPLE__)
                    RTLD_LOCAL|RTLD_FIRST|RTLD_NOW
#   else
                    RTLD_NOW|RTLD_GLOBAL|RTLD_NODELETE
#   endif
                    );
   if (handle)
   {
		ptrTracker = (TRACKER_PTR) dlsym(handle, "GetConstructor");
		if(ptrTracker)
			artrack = ptrTracker();		
   }		
#endif
	
}

GVRS_Tracker::~GVRS_Tracker()
{
    should_quit = true;
    wait();			
	if(artrack)
		delete artrack;
}

void GVRS_Tracker::run() {

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
	// start aruco tracker
	if(artrack)
		artrack->start_tracker(videoframe);

}

void GVRS_Tracker::data(double *data)
{
	double ardata[6] {0,0,0, 0,0,0};
    QMutexLocker foo(&mutex);

	if(artrack)
		artrack->data(ardata);
	// Set Aruco data (x,y,z)
    for (int i = 0; i < 3; i++)
        data[i] = ardata[i];
	// set udp data (yaw,pitch,roll)
    for (int i = 3; i < 6; i++)
        data[i] = last_recv_pose[i];
}

extern "C" OPENTRACK_EXPORT ITracker* GetConstructor()
{
    return new GVRS_Tracker;
}
