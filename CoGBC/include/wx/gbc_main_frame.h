#pragma once

#include <wx/wx.h>

#include "gbc_emulator.h"

enum {
	ID_LoadRom = 1,
	ID_ShowDebugger = 2
};

class GBCMainFrame : public wxFrame {
public:
	GBCMainFrame();

private:
	GBCEmulator gbc;

	void OnLoadRom(wxCommandEvent& event);
	void OnShowDebugger(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void BindCallbacks();
};