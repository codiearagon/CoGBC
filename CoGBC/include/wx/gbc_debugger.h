#pragma once

#include <vector>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "opcode_info.h"

#define DEBUGGER_HEIGHT 600
#define DEBUGGER_WIDTH 600

class GBCDebugger : public wxFrame {
public:
    GBCDebugger();
    ~GBCDebugger();

    void log_message(std::string message);
    void log_instruction(opcode_info current_op);
    void log_status();

private:
    wxPanel *info_panel;
    wxPanel *list_panel;

    wxListBox *inst_history;
    wxListBox *msg_history;

    // opcode info
    wxStaticText* mnemonic_info;
    wxStaticText* bytes_info;
    wxStaticText* ticks_info;
    wxStaticText* z_info_flag;
    wxStaticText* n_info_flag;
    wxStaticText* h_info_flag;
    wxStaticText* c_info_flag;

    // cpu state
    wxCheckBox* z_current_flag;
    wxCheckBox* n_current_flag;
    wxCheckBox* h_current_flag;
    wxCheckBox* c_current_flag;

    void OnClose(wxCloseEvent& event);
};