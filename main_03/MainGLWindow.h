/************************************************************************************

OpenGL with Qt - main version
Autor      : Papa Karlo <do.insys@gmail.com>
Repository : https://github.com/papa-karlo/do-qt-opengl
License    : MIT License,
			 see https://github.com/papa-karlo/do-qt-opengl/main/LICENSE

************************************************************************************/

#ifndef MainGLWindow_H
#define MainGLWindow_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "OpenGLWindow.h"
#include "GlObjCommon.h"

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
	//QOpenGLVertexArrayObject	m_vao_grid;
	// Vertex buffer (only positions now).
	QOpenGLBuffer				m_vertexBufferObject;
	QOpenGLBuffer				m_vertexBufferObject2;
	//QOpenGLBuffer				m_vertexBufferObjectGrid;

	// Holds the compiled shader programs.
	QOpenGLShaderProgram		*m_program;
	//QOpenGLShaderProgram		*m_program_grid;

	GlObjCommon* grid;
};

#endif // MainGLWindow_H
