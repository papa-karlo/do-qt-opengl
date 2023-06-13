/************************************************************************************

OpenGL with Qt - main version
Autor      : Papa Karlo <do.insys@gmail.com>
Repository : https://github.com/papa-karlo/do-qt-opengl
License    : MIT License,
			 see https://github.com/papa-karlo/do-qt-opengl/main/LICENSE

************************************************************************************/

#include "MainGLWindow.h"

#include <QDebug>

MainGLWindow::MainGLWindow() 
{
	m_grid = new GlObjCommon();
	m_triangle = new GlObjCommon();
}


MainGLWindow::~MainGLWindow() {
	// resource cleanup

	// since we release resources related to an OpenGL context,
	// we make this context current before cleaning up our resources
	bool success = m_context->makeCurrent(this);
	if (!success)
		qDebug() << "Cannot make OpenGL context current.";

	m_vao.destroy();
	m_vertexBufferObject.destroy();
	delete m_program;
	delete m_grid;
	delete m_triangle;

}


void MainGLWindow::initialize() {
	// this function is called once, when the window is first shown, i.e. when
	// the the window content is first rendered

	// build and compile our shader program
	// ------------------------------------

	float vertices_grid[] = {
	 -1.0f, 0.75f, 0.0f,
	 1.0f,  0.75f, 0.0f,
	 -1.0f, 0.5f, 0.0f,
	 1.0f,  0.5f, 0.0f,
	 -1.0f, 0.25f, 0.0f,
	 1.0f,  0.25f, 0.0f,
	 -1.0f, -0.0f, 0.0f,
	 1.0f, -0.0f, 0.0f,
	 -1.0f, -0.25f, 0.0f,
	 1.0f,  -0.25f, 0.0f,
	 -1.0f, -0.5f, 0.0f,
	 1.0f,  -0.5f, 0.0f,
	 -1.0f, -0.75f, 0.0f,
	 1.0f,  -0.75f, 0.0f,

	 -0.75f, 1.0f, 0.0f,
	 -0.75f, -1.0f, 0.0f,
	 -0.5f, 1.0f, 0.0f,
	 -0.5f, -1.0f, 0.0f,
	 -0.25f, 1.0f, 0.0f,
	 -0.25f, -1.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, -1.0f, 0.0f,
	  0.25f, 1.0f, 0.0f,
	  0.25f, -1.0f, 0.0f,
	  0.5f, 1.0f, 0.0f,
	  0.5f, -1.0f, 0.0f,
	  0.75f, 1.0f, 0.0f,
	  0.75f, -1.0f, 0.0f
	};

	float grid_color[] = {
		0.2f, 0.2f, 0.2f
	};

	//grid->init(vertices_grid, sizeof(vertices_grid), GL_LINES, ":/shaders/pass_through_grid.vert", ":/shaders/uniform_color_grid.frag");
    m_grid->init(vertices_grid, sizeof(vertices_grid), GL_LINES, grid_color, sizeof(grid_color),  ":/shaders/grid.vert", ":/shaders/grid.frag");
	
	
	
	float vertices_triangle[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	float triangle_color[] = {
		1.0f, 0.0f, 0.0f		// red
	};

	m_triangle->init(vertices_triangle, sizeof(vertices_triangle), GL_TRIANGLES, triangle_color, sizeof(triangle_color), ":/shaders/grid.vert", ":/shaders/grid.frag");


	m_program = new QOpenGLShaderProgram();

	// read the shader programs from the resource
	if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/pass_through.vert"))
		qDebug() << "Vertex shader errors:\n" << m_program->log();

	if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/uniform_color.frag"))
		qDebug() << "Fragment shader errors:\n" << m_program->log();

	if (!m_program->link())
		qDebug() << "Shader linker errors:\n" << m_program->log();


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float vertices2[] = {
	-0.7f, -0.7f, 0.0f,
	 0.7f, -0.7f, 0.0f,
	 0.0f,  0.7f, 0.0f
	};
	/*
	float vertices_grid[] = {
	 -1.0f, 0.75f, 0.0f,
	 1.0f,  0.75f, 0.0f,
	 -1.0f, 0.5f, 0.0f,
	 1.0f,  0.5f, 0.0f,
	 -1.0f, 0.25f, 0.0f,
	 1.0f,  0.25f, 0.0f,
	 -1.0f, -0.0f, 0.0f,
	 1.0f, -0.0f, 0.0f,
	 -1.0f, -0.25f, 0.0f,
	 1.0f,  -0.25f, 0.0f,
	 -1.0f, -0.5f, 0.0f,
	 1.0f,  -0.5f, 0.0f,
	 -1.0f, -0.75f, 0.0f,
	 1.0f,  -0.75f, 0.0f,

	 -0.75f, 1.0f, 0.0f,
	 -0.75f, -1.0f, 0.0f,
	 -0.5f, 1.0f, 0.0f,
	 -0.5f, -1.0f, 0.0f,
	 -0.25f, 1.0f, 0.0f,
	 -0.25f, -1.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, -1.0f, 0.0f,
	  0.25f, 1.0f, 0.0f,
	  0.25f, -1.0f, 0.0f,
	  0.5f, 1.0f, 0.0f,
	  0.5f, -1.0f, 0.0f,
	  0.75f, 1.0f, 0.0f,
	  0.75f, -1.0f, 0.0f
	};
	*/

	// create a new buffer for the vertices
	m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
	m_vertexBufferObject.create(); // create underlying OpenGL object
	m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw); // must be called before allocate

	m_vertexBufferObject.bind(); // set it active in the context, so that we can write to it
	// int bufSize = sizeof(vertices) = 9 * sizeof(float) = 9*4 = 36 bytes
	m_vertexBufferObject.allocate(vertices, sizeof(vertices) ); // copy data into buffer

		// Initialize the Vertex Array Object (VAO) to record and remember subsequent attribute assocations with
	// generated vertex buffer(s)
	m_vao.create(); // create underlying OpenGL object
	m_vao.bind(); // sets the Vertex Array Object current to the OpenGL context so it monitors attribute assignments

	//m_program_grid->enableAttributeArray(0);
	//m_program_grid->setAttributeBuffer(0, GL_FLOAT, 0, 3);
	
	// create a new buffer for the vertices
	m_vertexBufferObject2 = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
	m_vertexBufferObject2.create(); // create underlying OpenGL object
	m_vertexBufferObject2.setUsagePattern(QOpenGLBuffer::StaticDraw); // must be called before allocate

	m_vertexBufferObject2.bind(); // set it active in the context, so that we can write to it
	// int bufSize = sizeof(vertices) = 9 * sizeof(float) = 9*4 = 36 bytes
	m_vertexBufferObject2.allocate(vertices2, sizeof(vertices2)); // copy data into buffer

	// Initialize the Vertex Array Object (VAO) to record and remember subsequent attribute assocations with
	// generated vertex buffer(s)
	m_vao2.create(); // create underlying OpenGL object
	m_vao2.bind(); // sets the Vertex Array Object current to the OpenGL context so it monitors attribute assignments

	// now all following enableAttributeArray(), disableAttributeArray() and setAttributeBuffer() calls are
	// "recorded" in the currently bound VBA.
	/*
	// Enable attribute array at layout location 0
	m_program_grid->enableAttributeArray(0);
	m_program_grid->setAttributeBuffer(0, GL_FLOAT, 0, 3);
	// This maps the data we have set in the VBO to the "position" attribute.
	// 0 - offset - means the "position" data starts at the begin of the memory array
	// 3 - size of each vertex (=vec3) - means that each position-tuple has the size of 3 floats (those are the 3 coordinates,
	//     mind: this is the size of GL_FLOAT, not the size in bytes!
	
		// create a new buffer for the vertices
	m_vertexBufferObjectGrid = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
	m_vertexBufferObjectGrid.create(); // create underlying OpenGL object
	m_vertexBufferObjectGrid.setUsagePattern(QOpenGLBuffer::StaticDraw); // must be called before allocate

	m_vertexBufferObjectGrid.bind(); // set it active in the context, so that we can write to it
	// int bufSize = sizeof(vertices) = 9 * sizeof(float) = 9*4 = 36 bytes
	m_vertexBufferObjectGrid.allocate(vertices_grid, sizeof(vertices_grid)); // copy data into buffer

	// Initialize the Vertex Array Object (VAO) to record and remember subsequent attribute assocations with
	// generated vertex buffer(s)
	m_vao_grid.create(); // create underlying OpenGL object
	m_vao_grid.bind(); // sets the Vertex Array Object current to the OpenGL context so it monitors attribute assignments
	*/
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

	// Release (unbind) all
	//m_vertexBufferObjectGrid.release();
	m_vertexBufferObject2.release();
	m_vertexBufferObject.release();
	//m_vao_grid.release();
	m_vao2.release();
	m_vao.release();
	m_program->release();
	//m_program_grid->release();

}


void MainGLWindow::render() {
	// this function is called for every frame to be rendered on screen
	const qreal retinaScale = devicePixelRatio(); // needed for Macs with retina display
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	// set the background color = clear color
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_grid->bind();
	m_grid->draw();
	m_grid->release();

	m_triangle->bind();
	m_triangle->draw();
	m_triangle->release();

	return;

	// use our shader program
	//m_program_grid->bind();
	// bind the vertex array object, which in turn binds the vertex buffer object and
	// sets the attribute buffer in the OpenGL context

	m_vertexBufferObject.bind(); // set it active in the context, so that we can write to it
	m_vao.bind();
	// now draw the MainGLs:
	// - GL_MainGLS - draw individual MainGLs
	// - 0 index of first MainGL to draw
	// - 3 number of vertices to process
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawArrays(GL_LINE_STRIP, 0, 3);

	// finally release VAO again (not really necessary, just for completeness)
	m_vao.release();
	
	//m_program->bind();
	m_vertexBufferObject2.bind(); // set it active in the context, so that we can write to it
	m_vao2.bind();
	// now draw the MainGLs:
	// - GL_MainGLS - draw individual MainGLs
	// - 0 index of first MainGL to draw
	// - 3 number of vertices to process
	//glDrawArrays(GL_MainGLS, 0, 3);
	//glDrawArrays(GL_LINE_STRIP, 0, 3);
	glDrawArrays(GL_LINE_LOOP, 0, 3);

	// finally release VAO again (not really necessary, just for completeness)
	m_vao2.release();
	//m_vao.release();
	//m_program->release();

	m_program->bind();
	//m_vertexBufferObjectGrid.bind(); // set it active in the context, so that we can write to it
	//m_vao_grid.bind();
	// now draw the MainGLs:
	// - GL_MainGLS - draw individual MainGLs
	// - 0 index of first MainGL to draw
	// - 3 number of vertices to process
	//glDrawArrays(GL_MainGLS, 0, 3);
	//glDrawArrays(GL_LINE_STRIP, 0, 3);
	//glDrawArrays(GL_LINE_LOOP, 0, 6);
	glDrawArrays(GL_LINES, 0, 28);

	// finally release VAO again (not really necessary, just for completeness)
	//m_vao_grid.release();

}
