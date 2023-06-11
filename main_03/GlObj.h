
/************************************************************************************

OpenGL with Qt - main version
Autor      : Papa Karlo <do.insys@gmail.com>
Repository : https://github.com/papa-karlo/do-qt-opengl
License    : MIT License,
			 see https://github.com/papa-karlo/do-qt-opengl/main/LICENSE

************************************************************************************/

#ifndef GL_OBJ_H
#define GL_OBJ_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class GlObj : QObject
{
	Q_OBJECT

public:
	GlObj();
	~GlObj();

private:
	// Wraps an OpenGL VertexArrayObject (VAO)
	QOpenGLVertexArrayObject	m_vao;

	// Vertex buffer (only positions now).
	QOpenGLBuffer				m_vertexBufferObject;

	// Holds the compiled shader programs.
	QOpenGLShaderProgram* m_program;


public:

	int	m_vsize;		// vertex size
	int	m_mode;			// draw mode (GL_POINT, SGL_LINES, ...)
	int	m_csize;		// vertex color size

	int bind();
	int release();
	void _init(float* vertices, int vsize, int mode, float *color, int csize, QString vert, QString frag);
	virtual void init(void) = 0;
	virtual void init(float* vertices, int vsize, int mode, float* color, int csize, QString vert, QString frag) = 0;

	virtual void draw(void) = 0;

};

#endif // GL_OBJ_H