#pragma once
#ifndef OPENGLHEIGHTMAP_H
#define OPENGLHEIGHTMAP_H
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>
#include <qopenglshaderprogram.h>

class OpenGLHeightmap : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
public:
	explicit OpenGLHeightmap(QWidget *parent = 0);
	~OpenGLHeightmap();

protected:
	void initializeGL() override;
	void paintGL();
	void resizeGL(int width, int height);

private:
	QOpenGLShaderProgram *m_program;
};

#endif //OPENGLHEIGHTMAP_H