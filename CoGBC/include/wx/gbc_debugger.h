#include <vector>
#include <wx/wx.h>
#include "opcode_info.h"

#define DEBUGGER_HEIGHT 600
#define DEBUGGER_WIDTH 600

class GBCDebugger : public wxFrame {
    public:
        GBCDebugger();
        ~GBCDebugger();

        //void log_message(std::string message);
        //void log_instruction(opcode_info current_op);
        //void log_status();

        void Draw();

        void Cleanup();
    private:
        // area containers, will not be rendered

        std::vector<std::string> message_history;
        std::vector<opcode_info> inst_history;

        void OnClose(wxCloseEvent& event);
        //void draw_panel();
};