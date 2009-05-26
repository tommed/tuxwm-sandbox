#include <stdio.h>
#include <stdlib.h>
#include <X11/extensions/Xrender.h>
#include <X11/xpm.h>
#include "composite.h"

static Bool has_composite_extension;

//
// Check composition
//
Bool init_composite_extension(Display *d, Window *root, int screen)
{
	has_composite_extension = False;
	int event_base, error_base;
	if (XCompositeQueryExtension(d, &event_base, &error_base)) {
		int major=0, minor=2; // this is the first version which allowed composite
		XCompositeQueryVersion(d, &major, &minor);
		has_composite_extension = (major >= 0 || minor > 2);
		// begin off-screen composition
		if (has_composite_extension) {
			XCompositeRedirectSubwindows(d, *root, CompositeRedirectAutomatic);
		}
	}
	return has_composite_extension;
}

//
// Take a snapshot of the given window
//
void snapshot_window(Display *d, Window *win_handle)
{
	printf("attempting to snapshot active window\n");
	
	if (win_handle == NULL) {
		fprintf(stderr, "Cannot snapshot window as window is NULL\n");
		return;
	}
	
	// can only happen if composite is initialized and configured
	if (!has_composite_extension) {
		fprintf(stderr, "Cannot snapshot window as composite extension is not enabled\n");
		return;
	}
		
	// grab some properties from the Window
	XWindowAttributes a;
	if (!XGetWindowAttributes(d, *win_handle, &a)) {
		fprintf(stderr, "Cannot snapshot window; unable to retrieve window attributes\n");
		return;
	}
	
	// extract the properties we need to take the snapshot
	//XRenderPictFormat *format = XRenderFindVisualFormat(d, a.visual);
	//Bool has_alpha = (format->type == PictTypeDirect && format->direct.alphaMask);
	//int x=a.x, y=a.y;
	int width=a.width, height=a.height;
	printf("window attributes: width=%d, height=%d\n", width, height);
	
	// take the snapshot, save it to the root window!
	XWindowAttributes root_attribs;
	XImage *img = XGetImage(d, *win_handle, 0, 0, width, height, AllPlanes, ZPixmap);
	Window root = RootWindow(d,0);
	XGetWindowAttributes(d, root, &root_attribs);
	GC gc = XCreateGC(d, root, 0, NULL);
	XSetForeground(d, gc, WhitePixel(d,0)); // make sure the fg color is white
	XFillRectangle(d, root, gc, 0, 0, root_attribs.width, root_attribs.height); // clear root window with fg color
	XPutImage(d, root, gc, img, 0, 0, 400, 400, width, height); // draw snapshot to root window at an offset
	XDestroyImage(img);
	
	//XFreePixmap(d, pixmap);
	printf("snapshot taken\n");
}
