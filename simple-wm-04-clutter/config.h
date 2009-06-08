#include <X11/keysym.h>

//
// Defaults go here!
//


// launch commands
#define LAUNCHER_CMD "`dmenu_path | dmenu -b -nb \"#000\" -nf \"#777\" -sb \"#777\" -sf \"#000\"`&"

// action keys
#define ACTIONKEY_QUIT              XK_q
#define ACTIONKEY_LAUNCHER          XK_p
#define ACTIONKEY_SNAPSHOT          XK_c
#define ACTIONKEY_KILL_WINDOW       XK_w
#define ACTIONKEY_NEXT_WINDOW       XK_Tab
#define ACTIONKEY_HIDE_ALL_WINDOWS  XK_F11
