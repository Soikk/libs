#include "display.h"


int InitializeWindowContext(char className[], char windowName[], WNDPROC WindowProc, WindowContext *WContext){

	WContext->windowClass = (WNDCLASSEX){
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WindowProc,
		.hInstance = GetModuleHandle(NULL),
		.hCursor = LoadCursor(NULL, IDC_CROSS),
		.lpszClassName = className
	};
	if(RegisterClassEx(&WContext->windowClass) == 0){
		return 1;
	}

	WContext->window = CreateWindowEx(
		0,
		WContext->windowClass.lpszClassName,
		windowName,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
	if(WContext->window == NULL){
		return 1;
	}

	WContext->windowDC = GetDC(WContext->window);
	if(WContext->windowDC == NULL){
		return 1;
	}

	return 0;
}

int InitializeOpenGL(HWND window, HGLRC *renderingContext){

	int error = 0;

	int pfdAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
		0
	};

	HDC windowDC = GetDC(window);
	if(windowDC == NULL){
		error = 1;
		goto end;
	}
	UINT pixelFormat, numFormats;
	if(wglChoosePixelFormatARB(
		windowDC,
		pfdAttribs,
		NULL, 1,
		&pixelFormat,
		&numFormats
	) == FALSE){
		error = 1;
		goto end;
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	if(SetPixelFormat(
		windowDC,
		pixelFormat,
		&pixelFormatDescriptor
	) == FALSE){
		error = 1;
		goto end;
	}

	int contextAttribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		0
	};
	*renderingContext = wglCreateContextAttribsARB(windowDC, NULL, contextAttribs);
	if(renderingContext == NULL){
		error = 1;
		goto end;
	}

	if(wglMakeCurrent(windowDC, *renderingContext) == FALSE){
		error = 1;
		goto end;
	}

end:
	ReleaseDC(window, windowDC);

	return error;
}
