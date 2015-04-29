#pragma once
#include "ui_ftnoir_ftnclientcontrols.h"
#include <QUdpSocket>
#include <QThread>
#include <cmath>
#include "opentrack/plugin-api.hpp"
#include "opentrack/options.hpp"
#include "opentrack/plugin-support.h"


//#include "ftnoir_tracker_aruco/ftnoir_tracker_aruco.h"

using namespace options;

struct gvrs_settings {
    pbundle b;
    value<int> port;
    gvrs_settings() :
        b(bundle("gvrs-tracker")),
        port(b, "port", 4242)
    {}
};

typedef ITracker* (*TRACKER_PTR)(void);
typedef ITracker* (*TRACKER_PTRSTART)(QFrame*);

class GVRS_Tracker : public ITracker, protected QThread
{
public:
	GVRS_Tracker();
    ~GVRS_Tracker();
    void start_tracker(QFrame *);
    void data(double *data);
protected:
	void run() override;
private:
    QUdpSocket sock;
    double last_recv_pose[6];
    QMutex mutex;
    gvrs_settings s;
    volatile bool should_quit;
	QLibrary* handle;
	TRACKER_PTR ptrTracker;
	TRACKER_PTRSTART ptrTrackerStart;
	ITracker* artrack;
};

class GVRS_TrackerControls: public ITrackerDialog
{
    Q_OBJECT
public:
	GVRS_TrackerControls();
    void register_tracker(ITracker *) {}
    void unregister_tracker() {}
private:
	Ui::UICFTNClientControls ui;
    gvrs_settings s;
private slots:
	void doOK();
	void doCancel();
};

class GVRS_TrackerDll : public Metadata
{
public:
    QString name() { return QString("GVRS sender"); }
    QIcon icon() { return QIcon(":/images/facetracknoir.png"); }
};
