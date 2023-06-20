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

    //m_vao.destroy();
    //m_vertexBufferObject.destroy();
//	delete m_program;
	delete m_grid;
	delete m_triangle;

}


void MainGLWindow::initialize() {
	// this function is called once, when the window is first shown, i.e. when
	// the the window content is first rendered

    const int x_grid_max = 20;
    const int y_grid_max = 20;

    float vertices_grid[(x_grid_max+1 + y_grid_max+1)*2*3];// reserve for grid vertices

    for(int ii=0;ii<sizeof(vertices_grid)/sizeof(float);ii++)   //clear array
        vertices_grid[ii] = 0.0;

    float x_max = 1.0;
    float y_max = 1.0;

    int x_grid = 10;
    int y_grid = 8;

    float dx_offset = 0.8;
    float dy_offset = 0.5;

    // calculate coordinates X/Y - Vertical
    float dx = 2.0*x_max/(x_grid+2);
    float x_offset = dx*dx_offset;
    dx += (2*x_offset)/(x_grid+2);

    float dy = 2.0*y_max/(y_grid+2);
    float y_offset = dy*dy_offset;
    dy += (2*y_offset)/(y_grid+2);

    for(int ii=0;ii<x_grid+1;ii++) {
        vertices_grid[2*ii*3]     = -1.0+dx*(ii+1)-x_offset;    // par coords for line draw
        vertices_grid[2*ii*3+1]   = -1.0+dy-y_offset;

        vertices_grid[2*ii*3+3]   = -1.0+dx*(ii+1)-x_offset;
        vertices_grid[2*ii*3+3+1] = 1.0-dy+y_offset;
    }

    // calculate coordinates X/Y - Horizontal
    float _dy = 2.0*y_max/(y_grid+2);
    _dy += (2*y_offset)/(y_grid+2);

    float _dx = 2.0*x_max/(x_grid+2);
    _dx += (2*x_offset)/(x_grid+2);

    for(int ii=0;ii<y_grid+1;ii++) {
        vertices_grid[3*2*(x_grid+1)+2*ii*3+1]   = -1.0+_dy*(ii+1)-y_offset;
        vertices_grid[3*2*(x_grid+1)+2*ii*3]     = -1.0+_dx-x_offset;

        vertices_grid[3*2*(x_grid+1)+2*ii*3+3+1] = -1.0+_dy*(ii+1)-y_offset;
        vertices_grid[3*2*(x_grid+1)+2*ii*3+3]   = 1.0-_dx+x_offset;
    }


    float grid_color[] = {
        0.3f, 0.3f, 0.3f
	};

    int size_of_grid = (x_grid+1 + y_grid+1) * 2 * 3 * sizeof(float);
    m_grid->init(vertices_grid, size_of_grid, GL_LINES, grid_color, sizeof(grid_color),  ":/shaders/grid.vert", ":/shaders/grid.frag");
	
	float vertices_triangle[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	float triangle_color[] = {
		1.0f, 0.0f, 0.0f		// red
	};

	m_triangle->init(vertices_triangle, sizeof(vertices_triangle), GL_TRIANGLES, triangle_color, sizeof(triangle_color), ":/shaders/grid.vert", ":/shaders/grid.frag");

    return;

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

    //return;

	m_triangle->bind();
	m_triangle->draw();
	m_triangle->release();

	return;
}
