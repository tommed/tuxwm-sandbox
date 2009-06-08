#include <X11/Xlib.h>

#ifndef STATE_H
#define STATE_H

typedef struct state_machine_t StateMachine;
struct state_machine_t {
	Bool mod_down;
	Bool button1_down;
	Bool is_moving;
	Bool is_hidden;
	int move_mousex, move_mousey; // initial mouse position when moving started
	int move_winx, move_winy;           // initial window position of the window when moving started
};

#endif
