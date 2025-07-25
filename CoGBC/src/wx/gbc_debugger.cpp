#include <iostream>
#include <sstream>

#include "wx/gbc_debugger.h"

GBCDebugger::GBCDebugger() : wxFrame(nullptr, wxID_ANY, "GBC Debugger", wxDefaultPosition, wxSize(DEBUGGER_WIDTH, DEBUGGER_HEIGHT)) {
    Bind(wxEVT_CLOSE_WINDOW, &GBCDebugger::OnClose, this);

    wxBoxSizer* h_sizer = new wxBoxSizer(wxHORIZONTAL);

    // logger and disassembler
    info_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));
    list_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(DEBUGGER_WIDTH/2, DEBUGGER_HEIGHT));

    wxBoxSizer* list_sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* inst_history_label = new wxStaticText(list_panel, wxID_ANY, "Instruction History: ");
    inst_history = new wxListBox(list_panel, wxID_ANY, wxDefaultPosition);

    wxStaticText* msg_history_label = new wxStaticText(list_panel, wxID_ANY, "Message History: ");
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

    mnemonic_info = new wxStaticText(info_panel, wxID_ANY, "no mnemonic");
    bytes_info = new wxStaticText(info_panel, wxID_ANY, "-");
    ticks_info = new wxStaticText(info_panel, wxID_ANY, "-");
    z_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    n_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    h_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");
    c_info_flag = new wxStaticText(info_panel, wxID_ANY, "-");

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
    a_reg = new wxStaticText(info_panel, wxID_ANY, "A: ");
    f_reg = new wxStaticText(info_panel, wxID_ANY, "F: ");
    b_reg = new wxStaticText(info_panel, wxID_ANY, "B: ");
    c_reg = new wxStaticText(info_panel, wxID_ANY, "C: ");
    d_reg = new wxStaticText(info_panel, wxID_ANY, "D: ");
    e_reg = new wxStaticText(info_panel, wxID_ANY, "E: ");
    h_reg = new wxStaticText(info_panel, wxID_ANY, "H: ");
    l_reg = new wxStaticText(info_panel, wxID_ANY, "L: ");
    sp = new wxStaticText(info_panel, wxID_ANY, "SP: ");
    pc = new wxStaticText(info_panel, wxID_ANY, "PC: ");

    z_current_flag = new wxCheckBox(info_panel, wxID_ANY, "Z");
    n_current_flag = new wxCheckBox(info_panel, wxID_ANY, "N");
    h_current_flag = new wxCheckBox(info_panel, wxID_ANY, "H");
    c_current_flag = new wxCheckBox(info_panel, wxID_ANY, "C");

    z_current_flag->Enable(false);
    n_current_flag->Enable(false);
    h_current_flag->Enable(false);
    c_current_flag->Enable(false);

    current_flags->Add(z_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(n_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(h_current_flag, 1, wxEXPAND | wxALL, 2);
    current_flags->Add(c_current_flag, 1, wxEXPAND | wxALL, 2);
    current_state_sizer->Add(a_reg, 1, wxALL, 2);
    current_state_sizer->Add(f_reg, 1, wxALL, 2);
    current_state_sizer->Add(b_reg, 1, wxALL, 2);
    current_state_sizer->Add(c_reg, 1, wxALL, 2);
    current_state_sizer->Add(d_reg, 1, wxALL, 2);
    current_state_sizer->Add(e_reg, 1, wxALL, 2);
    current_state_sizer->Add(h_reg, 1, wxALL, 2);
    current_state_sizer->Add(l_reg, 1, wxALL, 2);
    current_state_sizer->Add(sp, 1, wxALL, 2);
    current_state_sizer->Add(pc, 1, wxALL, 2);
    current_state_sizer->Add(current_flags, 1, wxALL, 2);

    info_sizer->Add(opcode_info_sizer, 0, wxEXPAND | wxALL, 2);
    info_sizer->Add(current_state_sizer, 1, wxEXPAND | wxALL, 2);

    info_panel->SetSizerAndFit(info_sizer);
    
    h_sizer->Add(info_panel, 1, wxEXPAND | wxALL, 2);
    h_sizer->Add(list_panel, 2, wxEXPAND | wxALL, 2);
        
    this->SetSizerAndFit(h_sizer);
}

GBCDebugger::~GBCDebugger() {
}

void GBCDebugger::log_message(std::string message) {
    msg_history->AppendString(message);
}

void GBCDebugger::log_instruction(opcode_info current_op) {
    inst_history->AppendString(current_op.mnemonic);
    mnemonic_info->SetLabelText(current_op.mnemonic);
    bytes_info->SetLabelText(std::to_string(current_op.bytes));
    ticks_info->SetLabelText(current_op.ticks);
    z_info_flag->SetLabelText(current_op.z);
    n_info_flag->SetLabelText(current_op.n);
    h_info_flag->SetLabelText(current_op.h);
    c_info_flag->SetLabelText(current_op.c);
}

void GBCDebugger::set_register(std::string reg, uint8_t value) {
    std::stringstream hex_string;
    hex_string << "0x" << std::hex << value;
    if (reg == "a") a_reg->SetLabelText("A: " + hex_string.str());
    else if (reg == "f") f_reg->SetLabelText("F: " + hex_string.str());
    else if (reg == "b") b_reg->SetLabelText("B: " + hex_string.str());
    else if (reg == "c") c_reg->SetLabelText("C: " + hex_string.str());
    else if (reg == "d") d_reg->SetLabelText("D: " + hex_string.str());
    else if (reg == "e") e_reg->SetLabelText("E: " + hex_string.str());
    else if (reg == "h") h_reg->SetLabelText("H: " + hex_string.str());
    else if (reg == "l") l_reg->SetLabelText("L: " + hex_string.str());
    else if (reg == "sp") sp->SetLabelText("SP: " + hex_string.str());
    else if (reg == "pc") pc->SetLabelText("PC: " + hex_string.str());
    else log_message("Trying to set unknown register: " + reg);
}

void GBCDebugger::set_flag(std::string flag, bool value) {
    if (flag == "z") z_current_flag->SetValue(value);
    else if (flag == "n") n_current_flag->SetValue(value);
    else if (flag == "h") h_current_flag->SetValue(value);
    else if (flag == "c") c_current_flag->SetValue(value);
    else log_message("Trying to set unknown flag: " + flag);
}

void GBCDebugger::OnClose(wxCloseEvent& event) {
    Hide();
    event.Veto();
}