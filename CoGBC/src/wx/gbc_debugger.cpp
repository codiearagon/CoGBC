#include <iostream>

#include "wx/gbc_debugger.h"

GBCDebugger::GBCDebugger() : wxFrame(nullptr, wxID_ANY, "GBC Debugger", wxDefaultPosition, wxSize(DEBUGGER_WIDTH, DEBUGGER_HEIGHT)) {
    SetBackgroundColour(wxColour(0, 0, 0, 0));
    Bind(wxEVT_CLOSE_WINDOW, &GBCDebugger::OnClose, this);
}

GBCDebugger::~GBCDebugger() {
    Cleanup();
}

void GBCDebugger::Draw() {

}

void GBCDebugger::Cleanup() {

}

void GBCDebugger::OnClose(wxCloseEvent& event) {
    Hide();
    event.Veto();
}