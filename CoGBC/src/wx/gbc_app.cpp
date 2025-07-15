#include "wx/gbc_app.h"
#include "wx/gbc_main_frame.h"

bool GBCApp::OnInit() {
	GBCMainFrame *main_frame = new GBCMainFrame();
	main_frame->Show();
	return true;
}