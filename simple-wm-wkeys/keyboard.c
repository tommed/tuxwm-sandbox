#include <stdlib.h>
#include <stdio.h>
#include "keyboard.h"
#include "config.h"

// prototypes
void exec_launcher();

//
// Handle a keypress on any window (inc. Root window)
//
Bool handle_keyevent(XKeyEvent *event)
{
	Bool should_quit = False;
	XComposeStatus status;
	KeySym keysym;
	char keybuffer[2];
	int length;
	
	// translate the vendor-dependent keycode to a keysym and string
	length = XLookupString(event, keybuffer, 1, &keysym, &status);
	
	// actions-keys are only action-keys when the Mod key is depressed
	if (event->state & Mod1Mask || event->state & Mod2Mask) {
		switch (keysym) {
			case ACTIONKEY_QUIT:
				should_quit = True;
				break;
			case ACTIONKEY_LAUNCHER:
				exec_launcher();
				break;				
		}
	}
	
	return should_quit;
}

//
// Launch the launcher
//
void exec_launcher()
{
	popen(LAUNCHER_CMD, "r");
}
