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

    void OnClose(wxCloseEvent& event);
};