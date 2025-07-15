#include "wx/gbc_app.h"
#include "wx/gbc_main_frame.h"

bool GBCApp::OnInit() {
	GBCMainFrame* frame = new GBCMainFrame();
	frame->Show();
	return true;
}