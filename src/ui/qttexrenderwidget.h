#pragma once


#include "ui/qt_tex_render.h"
#include <microtex.h>

#include <QWidget>
class QtTeXRenderWidgetPrivate;
class QtTeXRenderWidget : public QWidget, public TeXRender
{
    Q_OBJECT

  public:
    explicit QtTeXRenderWidget(QWidget *parent = nullptr, float text_size = 20.0f);
    ~QtTeXRenderWidget() override;

    float getTextSize() override;
    void setTextSize(float size) override;
    void setLaTeX(const std::string &latex) override;
    bool isRenderDisplayed() override;
    int getRenderWidth() override;
    int getRenderHeight() override;
    void paintEvent(QPaintEvent *event) override;
    void saveSVG(const char *path) override;

  private:
    QtTeXRenderWidgetPrivate *d_ptr;
    friend class QtTeXRenderWidgetPrivate;
	
};
