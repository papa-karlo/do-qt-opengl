/************************************************************************************

OpenGL with Qt - Tutorial
-------------------------
Autor      : Andreas Nicolai <andreas.nicolai@gmx.net>
Repository : https://github.com/ghorwin/OpenGLWithQt-Tutorial
License    : BSD License,
			 see https://github.com/ghorwin/OpenGLWithQt-Tutorial/blob/master/LICENSE

************************************************************************************/

#ifndef MainGLWindow_H
#define MainGLWindow_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "OpenGLWindow.h"

/*	This is the window that shows the MainGL.
	We derive from our OpenGLWindow base class and implement the
	virtual initialize() and render() functions.
*/
class MainGLWindow : public OpenGLWindow {
public:
	MainGLWindow();
	~MainGLWindow() Q_DECL_OVERRIDE;

	void initialize() Q_DECL_OVERRIDE;
	void render() Q_DECL_OVERRIDE;

private:
	// Wraps an OpenGL VertexArrayObject (VAO)
	QOpenGLVertexArrayObject	m_vao;
	QOpenGLVertexArrayObject	m_vao2;
	QOpenGLVertexArrayObject	m_vao_grid;
	// Vertex buffer (only positions now).
	QOpenGLBuffer				m_vertexBufferObject;
	QOpenGLBuffer				m_vertexBufferObject2;
	QOpenGLBuffer				m_vertexBufferObjectGrid;

	// Holds the compiled shader programs.
	QOpenGLShaderProgram		*m_program;
	QOpenGLShaderProgram		*m_program_grid;
};

#endif // MainGLWindow_H
