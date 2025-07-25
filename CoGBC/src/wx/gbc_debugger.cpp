#include <iostream>

#include "wx/gbc_debugger.h"

GBCDebugger::GBCDebugger() : wxFrame(nullptr, wxID_ANY, "GBC Debugger", wxDefaultPosition, wxSize(DEBUGGER_WIDTH, DEBUGGER_HEIGHT)) {
    SetBackgroundColour(wxColour(0, 0, 0, 255));
    Bind(wxEVT_CLOSE_WINDOW, &GBCDebugger::OnClose, this);

    wxBoxSizer* h_sizer = new wxBoxSizer(wxHORIZONTAL);

    // logger and disassembler
    info_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));
    info_panel->SetBackgroundColour(wxColour(0, 0, 0, 255));

    list_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));
    list_panel->SetBackgroundColour(wxColour(10, 10, 10, 255));

    wxBoxSizer* list_sizer = new wxBoxSizer(wxVERTICAL);

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

    // cpu state and registers
    wxBoxSizer* info_sizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* opcode_info_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bytes_ticks_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* info_flags = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* opcode_info_label = new wxStaticText(info_panel, wxID_ANY, "Current opcode:");
    opcode_info_label->SetForegroundColour(wxColour(255, 255, 255, 255));

    mnemonic_info = new wxStaticText(info_panel, wxID_ANY, "no mnemonic");
    mnemonic_info->SetForegroundColour(wxColour(255, 255, 255, 255));

    bytes_info = new wxStaticText(info_panel, wxID_ANY, "-");
    bytes_info->SetForegroundColour(wxColour(255, 255, 255, 255));

    ticks_info = new wxStaticText(info_panel, wxID_ANY, "-");
    ticks_info->SetForegroundColour(wxColour(255, 255, 255, 255));

    z_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    z_info_flag->SetForegroundColour(wxColour(255, 255, 255, 255));

    n_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    n_info_flag->SetForegroundColour(wxColour(255, 255, 255, 255));

    h_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    h_info_flag->SetForegroundColour(wxColour(255, 255, 255, 255));

    c_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    c_info_flag->SetForegroundColour(wxColour(255, 255, 255, 255));

    info_flags->Add(z_info_flag, 1, wxALL, 2);
    info_flags->Add(n_info_flag, 1, wxALL, 2);
    info_flags->Add(h_info_flag, 1, wxALL, 2);
    info_flags->Add(c_info_flag, 1, wxALL, 2);
    bytes_ticks_sizer->Add(bytes_info, 1, wxALL, 2);
    bytes_ticks_sizer->Add(ticks_info, 1, wxALL, 2);
    opcode_info_sizer->Add(opcode_info_label, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 2);
    opcode_info_sizer->Add(mnemonic_info, 1,  wxALL | wxALIGN_CENTER_HORIZONTAL, 1);
    opcode_info_sizer->Add(bytes_ticks_sizer, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 1);
    opcode_info_sizer->Add(info_flags, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, 1);

    wxBoxSizer* current_state_sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* current_flags = new wxBoxSizer(wxHORIZONTAL);
    z_current_flag = new wxCheckBox(info_panel, wxID_ANY, "Z");
    z_current_flag->Enable(false);

    n_current_flag = new wxCheckBox(info_panel, wxID_ANY, "N");
    n_current_flag->Enable(false);

    h_current_flag = new wxCheckBox(info_panel, wxID_ANY, "H");
    h_current_flag->Enable(false);

    c_current_flag = new wxCheckBox(info_panel, wxID_ANY, "C");
    c_current_flag->Enable(false);

    current_flags->Add(z_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(n_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(h_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(c_current_flag, 1, wxEXPAND | wxALL, 2);
    current_state_sizer->Add(current_flags, 1, wxEXPAND | wxALL, 2);

    info_sizer->Add(opcode_info_sizer, 0, wxEXPAND | wxALL, 2);
    info_sizer->Add(current_state_sizer, 1, wxEXPAND | wxALL, 2);

    info_panel->SetSizerAndFit(info_sizer);
    
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
    mnemonic_info->SetLabelText(current_op.mnemonic);
    bytes_info->SetLabelText(std::to_string(current_op.bytes));
    ticks_info->SetLabelText(current_op.ticks);
    z_info_flag->SetLabelText(current_op.z);
    n_info_flag->SetLabelText(current_op.n);
    h_info_flag->SetLabelText(current_op.h);
    c_info_flag->SetLabelText(current_op.c);
}

void GBCDebugger::OnClose(wxCloseEvent& event) {
    Hide();
    event.Veto();
}