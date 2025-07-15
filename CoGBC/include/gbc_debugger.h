#include <vector>
#include "opcode_info.h"

#define DEBUGGER_HEIGHT 800
#define DEBUGGER_WIDTH 800

class GBCDebugger {
    public:
        GBCDebugger();
        ~GBCDebugger();

        //void log_message(std::string message);
        //void log_instruction(opcode_info current_op);
        //void log_status();

        void show_debugger();
        void hide_debugger();

        void draw();

        void cleanup();
    private:
        // area containers, will not be rendered


        std::vector<std::string> message_history;
        std::vector<opcode_info> inst_history;

        //void draw_panel();
};