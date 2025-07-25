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
    void set_register(std::string reg, uint8_t value);
    void set_flag(std::string flag, bool value);

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
    wxStaticText* a_reg;
    wxStaticText* f_reg;
    wxStaticText* b_reg;
    wxStaticText* c_reg;
    wxStaticText* d_reg;
    wxStaticText* e_reg;
    wxStaticText* h_reg;
    wxStaticText* l_reg;
    wxStaticText* sp;
    wxStaticText* pc;
    wxCheckBox* z_current_flag;
    wxCheckBox* n_current_flag;
    wxCheckBox* h_current_flag;
    wxCheckBox* c_current_flag;

    void OnClose(wxCloseEvent& event);
};