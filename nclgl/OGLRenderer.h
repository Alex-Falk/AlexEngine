#pragma once
/*
Class:OGLRenderer
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:Abstract base class for the graphics tutorials. Creates an OpenGL 
3.2 CORE PROFILE rendering context. Each lesson will create a renderer that 
inherits from this class - so all context creation is handled automatically,
but students still get to see HOW such a context is created.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*/

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include "Common.h"

#include <string>
#include <vector>
#include <Maths/Matrix4.h>
#include <Maths/Quaternion.h>

#include <GL\glew.h>
#include <GL\wglew.h>

#include "Window.h"
#include "light.h"

#include "Shader.h"		//Students make this file...

using std::vector;

//
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "SOIL.lib")

#ifdef _DEBUG
#define GL_BREAKPOINT glUniform4uiv(0,0,0);//Invalid, but triggers gdebugger ;)
#else
#define GL_BREAKPOINT //
#endif

//#define OPENGL_DEBUGGING

static constexpr float biasValues[4][4] = {
	{ 0.5, 0.0, 0.0, 0.0 },
	{ 0.0, 0.5, 0.0, 0.0 },
	{ 0.0, 0.0, 0.5, 0.0 },
	{ 0.5, 0.5, 0.5, 1.0 }
};
static const Maths::Matrix4 biasMatrix(biasValues);

class Shader;

class OGLRenderer	{
public:
	friend class Window;
	OGLRenderer(Window &parent);
	virtual ~OGLRenderer(void);

	virtual void	RenderScene()		= 0;
	virtual void	UpdateScene(float msec);
	void			SwapBuffers();

	bool			HasInitialised() const;	
	
	Shader*			GetCurrentShader() const {
		return currentShader;
	}

protected:
	virtual void	Resize(int x, int y);	
	void			UpdateShaderMatrices();
	void			SetCurrentShader(Shader*s);

	void			SetTextureRepeating(GLuint target, bool state);

	void			SetShaderLight(const Light &l);

	void			DrawDebugPerspective(Maths::Matrix4*matrix = 0);
	void			DrawDebugOrtho(Maths::Matrix4*matrix = 0);

	Shader* currentShader;
	

	Maths::Matrix4 projMatrix;		//Projection matrix
	Maths::Matrix4 modelMatrix;		//Model matrix. NOT MODELVIEW
	Maths::Matrix4 viewMatrix;		//View matrix
	Maths::Matrix4 textureMatrix;	//Texture matrix

	int		width;			//Render area width (not quite the same as window width)
	int		height;			//Render area height (not quite the same as window height)
	bool	init;			//Did the renderer initialise properly?

	HDC		deviceContext;	//...Device context?
	HGLRC	renderContext;	//Permanent Rendering Context

#ifdef _DEBUG
	static void CALLBACK DebugCallback(GLuint source, GLuint type,GLuint id, GLuint severity,
									   int length, const char* message, void* userParam);
#endif

};