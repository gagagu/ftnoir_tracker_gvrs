#include "ftnoir_tracker_gvrs.h"
#include "opentrack/plugin-api.hpp"

GVRS_TrackerControls::GVRS_TrackerControls()
{
	ui.setupUi( this );
	
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(doOK()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(doCancel()));
	
	tie_setting(s.port, ui.spinPortNumber);
}

void GVRS_TrackerControls::doOK(){
	s.b->save();
	this->close();
}

void GVRS_TrackerControls::doCancel(){
	s.b->reload();
	this->close();
}
