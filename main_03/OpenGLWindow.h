/************************************************************************************

OpenGL with Qt - main version
Autor      : Papa Karlo <do.insys@gmail.com>
Repository : https://github.com/papa-karlo/do-qt-opengl
License    : MIT License,
			 see https://github.com/papa-karlo/do-qt-opengl/main/LICENSE

************************************************************************************/

#ifndef OpenGLWindow_H
#define OpenGLWindow_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QOpenGLContext;
QT_END_NAMESPACE

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
	Q_OBJECT
public:
	explicit OpenGLWindow(QWindow *parent = nullptr);

	virtual void render() = 0;
	virtual void initialize() = 0;

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent *event) Q_DECL_OVERRIDE;
	void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

	QOpenGLContext *m_context;
};

#endif // OpenGLWindow_H
