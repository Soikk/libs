#ifndef DISPLAY_H
#define DISPLAY_H

#define WIN32_LEAN_AND_MEAN // so winsock1 isnt included, mainly

#include <windows.h>
#include "ogl/ogl.h"


typedef struct WindowContext {
	WNDCLASSEX windowClass;
	HWND window;
	HDC windowDC;
} WindowContext;

int InitializeWindowContext(char className[], char windowName[], WNDPROC WindowProc, WindowContext *WContext);
int InitializeOpenGL(HWND window, HGLRC *renderingContext);

#endif
