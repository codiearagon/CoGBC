#include <wx/wfstream.h>
#include "wx/gbc_main_frame.h"

GBCMainFrame::GBCMainFrame() : wxFrame(nullptr, wxID_ANY, "CoGBC") {

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_LoadRom, "&Load Rom");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuTools = new wxMenu;
    menuTools->Append(ID_ShowDebugger, "&Show Debugger");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuTools, "&Tools");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
    BindCallbacks();
}

void GBCMainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void GBCMainFrame::OnLoadRom(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Load a GBC Rom"), "", "", "GBC Files (*.gbc)|*.gbc", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    gbc.load_rom(openFileDialog.GetPath().ToStdString());
}

void GBCMainFrame::OnShowDebugger(wxCommandEvent& event) {

}

void GBCMainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("GBC Emulator made by Codie Aragon");
}

void GBCMainFrame::BindCallbacks() {
    Bind(wxEVT_MENU, &GBCMainFrame::OnLoadRom, this, ID_LoadRom);
    Bind(wxEVT_MENU, &GBCMainFrame::OnShowDebugger, this, ID_ShowDebugger);
    Bind(wxEVT_MENU, &GBCMainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &GBCMainFrame::OnExit, this, wxID_EXIT);
}