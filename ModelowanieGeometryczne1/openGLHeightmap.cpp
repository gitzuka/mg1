#include "openGLHeightmap.h"

OpenGLHeightmap::OpenGLHeightmap(QWidget* parent)
{
}

OpenGLHeightmap::~OpenGLHeightmap()
{
	delete m_program;
}

void OpenGLHeightmap::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	auto *m_program = new QOpenGLShaderProgram();
	//program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ModelowanieGeometryczne1/ModelowanieGeometryczne1/heightmap.vert");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Andrzej/Documents/Visual Studio 2015/Projects/ModelowanieGeometryczne1/ModelowanieGeometryczne1/heightmap.frag");
	m_program->link();
}

void OpenGLHeightmap::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLHeightmap::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
}
