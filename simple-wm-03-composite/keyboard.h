#include <X11/Xutil.h>
#include <X11/keysym.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

enum { A_Quit, A_Launcher, A_Last };
typedef int ActionKey;

Bool handle_keyevent(XKeyEvent *event, Window active_window); // returns `should quit app?`

#endif
