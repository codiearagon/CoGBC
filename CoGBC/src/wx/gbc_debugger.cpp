#include <iostream>

#include "wx/gbc_debugger.h"

GBCDebugger::GBCDebugger() : wxFrame(nullptr, wxID_ANY, "GBC Debugger", wxDefaultPosition, wxSize(DEBUGGER_WIDTH, DEBUGGER_HEIGHT)) {
    SetBackgroundColour(wxColour(0, 0, 0, 255));
    Bind(wxEVT_CLOSE_WINDOW, &GBCDebugger::OnClose, this);

    wxBoxSizer *h_sizer = new wxBoxSizer(wxHORIZONTAL);

    info_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));
    info_panel->SetBackgroundColour(wxColour(0, 0, 0, 255));

    list_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));
    list_panel->SetBackgroundColour(wxColour(10, 10, 10, 255));

    wxSizer *list_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* inst_history_label = new wxStaticText(list_panel, wxID_ANY, "Instruction History: ");
    inst_history_label->SetForegroundColour(wxColour(255, 255, 255, 255));
    inst_history = new wxListBox(list_panel, wxID_ANY, wxDefaultPosition);

    wxStaticText* msg_history_label = new wxStaticText(list_panel, wxID_ANY, "Message History: ");
    msg_history_label->SetForegroundColour(wxColour(255, 255, 255, 255));
    msg_history = new wxListBox(list_panel, wxID_ANY, wxDefaultPosition);

    list_sizer->Add(inst_history_label, 0, wxLEFT | wxTOP | wxBOTTOM, 2);
    list_sizer->Add(inst_history, 2, wxEXPAND | wxALL, 2);
    list_sizer->Add(msg_history_label, 0, wxLEFT | wxTOP | wxBOTTOM, 2);
    list_sizer->Add(msg_history, 1, wxEXPAND | wxALL, 2);

    list_panel->SetSizerAndFit(list_sizer);
    
    h_sizer->Add(info_panel, 1, wxEXPAND | wxALL, 2);
    h_sizer->Add(list_panel, 1, wxEXPAND | wxALL, 2);
        
    this->SetSizerAndFit(h_sizer);
}

GBCDebugger::~GBCDebugger() {
}

void GBCDebugger::log_message(std::string message) {
    msg_history->AppendString(message);
}

void GBCDebugger::log_instruction(opcode_info current_op) {
    inst_history->AppendString(current_op.mnemonic);
}

void GBCDebugger::OnClose(wxCloseEvent& event) {
    Hide();
    event.Veto();
}