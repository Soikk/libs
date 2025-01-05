#include "ogl.h"


BOOL LoadExtensionList(void){
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if(wglChoosePixelFormatARB == NULL){
		return FALSE;
	}
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(wglCreateContextAttribsARB == NULL){
		return FALSE;
	}
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(wglSwapIntervalEXT == NULL){
		return FALSE;
	}
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if(!glAttachShader){
		return FALSE;
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if(!glBindBuffer){
		return FALSE;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if(!glBindVertexArray){
		return FALSE;
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if(!glBufferData){
		return FALSE;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if(!glCompileShader){
		return FALSE;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if(!glCreateProgram){
		return FALSE;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if(!glCreateShader){
		return FALSE;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if(!glDeleteBuffers){
		return FALSE;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if(!glDeleteProgram){
		return FALSE;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if(!glDeleteShader){
		return FALSE;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if(!glDeleteVertexArrays){
		return FALSE;
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if(!glDetachShader){
		return FALSE;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if(!glEnableVertexAttribArray){
		return FALSE;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if(!glGenBuffers){
		return FALSE;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if(!glGenVertexArrays){
		return FALSE;
	}

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if(!glGetAttribLocation){
		return FALSE;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if(!glGetProgramInfoLog){
		return FALSE;
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if(!glGetProgramiv){
		return FALSE;
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if(!glGetShaderInfoLog){
		return FALSE;
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if(!glGetShaderiv){
		return FALSE;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if(!glLinkProgram){
		return FALSE;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if(!glShaderSource){
		return FALSE;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if(!glUseProgram){
		return FALSE;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if(!glVertexAttribPointer){
		return FALSE;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if(!glBindAttribLocation){
		return FALSE;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if(!glGetUniformLocation){
		return FALSE;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv){
		return FALSE;
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if(!glActiveTexture){
		return FALSE;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if(!glUniform1i){
		return FALSE;
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if(!glGenerateMipmap){
		return FALSE;
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if(!glDisableVertexAttribArray){
		return FALSE;
	}

	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	if(!glUniform1f){
		return FALSE;
	}

	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	if(!glUniform2f){
		return FALSE;
	}

	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	if(!glUniform3f){
		return FALSE;
	}

	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	if(!glUniform4f){
		return FALSE;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if(!glUniform1i){
		return FALSE;
	}

	glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
	if(!glUniform2i){
		return FALSE;
	}

	glUniform3i = (PFNGLUNIFORM3IPROC)wglGetProcAddress("glUniform3i");
	if(!glUniform3i){
		return FALSE;
	}

	glUniform4i = (PFNGLUNIFORM4IPROC)wglGetProcAddress("glUniform4i");
	if(!glUniform4i){
		return FALSE;
	}

	glUniform1ui = (PFNGLUNIFORM1UIPROC)wglGetProcAddress("glUniform1ui");
	if(!glUniform1ui){
		return FALSE;
	}

	glUniform2ui = (PFNGLUNIFORM2UIPROC)wglGetProcAddress("glUniform2ui");
	if(!glUniform2ui){
		return FALSE;
	}

	glUniform3ui = (PFNGLUNIFORM3UIPROC)wglGetProcAddress("glUniform3ui");
	if(!glUniform3ui){
		return FALSE;
	}

	glUniform4ui = (PFNGLUNIFORM4UIPROC)wglGetProcAddress("glUniform4ui");
	if(!glUniform4ui){
		return FALSE;
	}

	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	if(!glUniform1fv){
		return FALSE;
	}

	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	if(!glUniform2fv){
		return FALSE;
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if(!glUniform3fv){
		return FALSE;
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if(!glUniform4fv){
		return FALSE;
	}

	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	if(!glUniform1iv){
		return FALSE;
	}

	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	if(!glUniform2iv){
		return FALSE;
	}

	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	if(!glUniform3iv){
		return FALSE;
	}

	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	if(!glUniform4iv){
		return FALSE;
	}

	glUniform1uiv = (PFNGLUNIFORM1UIVPROC)wglGetProcAddress("glUniform1uiv");
	if(!glUniform1uiv){
		return FALSE;
	}

	glUniform2uiv = (PFNGLUNIFORM2UIVPROC)wglGetProcAddress("glUniform2uiv");
	if(!glUniform2uiv){
		return FALSE;
	}

	glUniform3uiv = (PFNGLUNIFORM3UIVPROC)wglGetProcAddress("glUniform3uiv");
	if(!glUniform3uiv){
		return FALSE;
	}

	glUniform4uiv = (PFNGLUNIFORM4UIVPROC)wglGetProcAddress("glUniform4uiv");
	if(!glUniform4uiv){
		return FALSE;
	}

	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
	if(!glUniformMatrix2fv){
		return FALSE;
	}

	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
	if(!glUniformMatrix3fv){
		return FALSE;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv){
		return FALSE;
	}

	glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)wglGetProcAddress("glUniformMatrix2x3fv");
	if(!glUniformMatrix2x3fv){
		return FALSE;
	}

	glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)wglGetProcAddress("glUniformMatrix3x2fv");
	if(!glUniformMatrix3x2fv){
		return FALSE;
	}

	glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)wglGetProcAddress("glUniformMatrix2x4fv");
	if(!glUniformMatrix2x4fv){
		return FALSE;
	}

	glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)wglGetProcAddress("glUniformMatrix4x2fv");
	if(!glUniformMatrix4x2fv){
		return FALSE;
	}

	glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)wglGetProcAddress("glUniformMatrix3x4fv");
	if(!glUniformMatrix3x4fv){
		return FALSE;
	}

	glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)wglGetProcAddress("glUniformMatrix4x3fv");
	if(!glUniformMatrix4x3fv){
		return FALSE;
	}

	return TRUE;
}

// TODO: error handling
int InitializeOpenGLExtensions(void){
	int error = 0;

	WNDCLASS dummyClass = {
		.style = CS_OWNDC,
		.lpfnWndProc = DefWindowProc,
		.hInstance = GetModuleHandle(0),
		.lpszClassName = "dummyClass",
	};
	if(RegisterClassA(&dummyClass) == 0){
		error = 1;
		goto end_class;
	}

	HWND dummyWindow = CreateWindowEx(
		0,
		dummyClass.lpszClassName,
		"dummyWindow",
		0,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		dummyClass.hInstance,
		NULL
	);
	if(dummyWindow == NULL) {
		error = 2;
		goto end_window;
	}
	HDC dummyDC = GetDC(dummyWindow);
	if(dummyDC == NULL){
		error = 3;
		goto end_DC;
	}

	PIXELFORMATDESCRIPTOR dummyPFD = {
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 32,
		.cDepthBits = 24,
		.cStencilBits = 8
	};
	int pf = ChoosePixelFormat(dummyDC, &dummyPFD);
	if(pf == 0){
		error = 4;
		goto end_DC;
	}
	if(SetPixelFormat(dummyDC, pf, &dummyPFD) == FALSE){
		error = 5;
		goto end_DC;
	}

	HGLRC dummyContext = wglCreateContext(dummyDC);
	if(dummyContext == NULL){
		error = 6;
		goto end_context;
	}
	if(wglMakeCurrent(dummyDC, dummyContext) == FALSE){
		error = 7;
		goto end_current;
	}

	if(LoadExtensionList() == FALSE){
		error = 8;
	}

end_current:
	if(wglMakeCurrent(NULL, NULL) == FALSE){
		error = 9;
	}
end_context:
	if(wglDeleteContext(dummyContext) == FALSE){
		error = 10;
	}else{
		dummyContext = NULL;
	}
end_DC:
	if(ReleaseDC(dummyWindow, dummyDC) == 0){
		error = 11;
	}else{
		dummyDC = NULL;
	}
end_window:
	if(DestroyWindow(dummyWindow) == 0){
		error = 12;
	}else{
		dummyWindow = NULL;
	}
end_class:
	if(UnregisterClass(dummyClass.lpszClassName, dummyClass.hInstance) == 0){
		error = 13;
	}

	return error;
}

// TODO: abstract away to a platform-independent library
static long getFileSize(FILE *fp){
	long curr = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, curr, SEEK_SET);
	return size;
}

GLuint LoadShaders(char *vertex_file_path, char *fragment_file_path){
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// use str.h
	char *VertexShaderCode;
	FILE *VertexShaderStream = fopen(vertex_file_path, "rb");
	if(VertexShaderStream != NULL){
		long fsize = getFileSize(VertexShaderStream);
		VertexShaderCode = calloc(fsize, sizeof(char));
		fread(VertexShaderCode, sizeof(char), fsize, VertexShaderStream);
		fclose(VertexShaderStream);
	}else{
		return 0;
	}

	// use str.h
	char *FragmentShaderCode;
	FILE *FragmentShaderStream = fopen(fragment_file_path, "rb");
	if(FragmentShaderStream != NULL){
		long fsize = getFileSize(VertexShaderStream);
		FragmentShaderCode = calloc(fsize, sizeof(char));
		fread(FragmentShaderCode, sizeof(char), fsize, FragmentShaderStream);
		fclose(FragmentShaderStream);
	}else{
		return 0;
	}

	GLint Result;
	
	glShaderSource(VertexShaderID, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if(Result != GL_TRUE){
		return 0;
	}

	glShaderSource(FragmentShaderID, 1, &FragmentShaderCode , NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if(Result != GL_TRUE){
		return 0;
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	if(Result != GL_TRUE){
		return 0;
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

