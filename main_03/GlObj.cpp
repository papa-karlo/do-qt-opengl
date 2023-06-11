#include "GlObj.h"

GlObj::GlObj() :
	m_program(nullptr)
{
}

GlObj::~GlObj() {
	// resource cleanup
	m_vao.destroy();
	m_vertexBufferObject.destroy();
	delete m_program;
}

int GlObj::bind()
{
	// use our shader program
	m_program->bind();
	// bind the vertex array object, which in turn binds the vertex buffer object and
	// sets the attribute buffer in the OpenGL context
	m_vertexBufferObject.bind(); // set it active in the context, so that we can write to it
	m_vao.bind();

	return 0;
}

int GlObj::release()
{
	m_vao.release();
	//m_program->release();

	return 0;
}

void GlObj::_init(float *vertices, int vsize, int mode, float *color, int csize, QString vert, QString frag)
{
	m_vsize = vsize / (3 * sizeof(float));
	m_mode = mode;
	m_csize = csize / (3 * sizeof(float));

	m_program = new QOpenGLShaderProgram();

	// read the shader programs from the resource
	if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert))
		qDebug() << "Vertex shader errors:\n" << m_program->log();

	if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag))
		qDebug() << "Fragment shader errors:\n" << m_program->log();

	if (!m_program->link())
		qDebug() << "Shader linker errors:\n" << m_program->log();

	// This maps the data we have set in the VBO to the "position" attribute.
	// 0 - offset - means the "position" data starts at the begin of the memory array
	// 3 - size of each vertex (=vec3) - means that each position-tuple has the size of 3 floats (those are the 3 coordinates,
	//     mind: this is the size of GL_FLOAT, not the size in bytes!

	// create a new buffer for the vertices
	m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
	m_vertexBufferObject.create(); // create underlying OpenGL object
	m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw); // must be called before allocate

	m_vertexBufferObject.bind(); // set it active in the context, so that we can write to it
	//m_vertexBufferObject.allocate(vertices, sizeof(vertices)); // copy data into buffer
	m_vertexBufferObject.allocate(vertices, vsize * 3 * sizeof(float)); // copy data into buffer

	// Initialize the Vertex Array Object (VAO) to record and remember subsequent attribute assocations with
	// generated vertex buffer(s)
	m_vao.create(); // create underlying OpenGL object
	m_vao.bind(); // sets the Vertex Array Object current to the OpenGL context so it monitors attribute assignments

	// Enable attribute array at layout location 0
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);
	
	m_program->bind();
	int uniform_location = m_program->uniformLocation("gridColor"); 
	m_program->setUniformValue(uniform_location, color[0], color[1], color[2]);


	m_program->release();
	m_vertexBufferObject.release();
	m_vao.release();
}

