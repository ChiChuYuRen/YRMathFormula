﻿#include "renderoptionwidget.h"
#include "qt_tex_render.h"
#include "samples.h"
#include "ui/qttexrenderwidget.h"
#include "ui/texedit.h"

// Qt
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrent>

#include "manager/acssmanager.h"
#include "yapplication.h"

class RenderOptionWidgetPrivate
{
  public:
    RenderOptionWidgetPrivate(RenderOptionWidget *p) : m_this(p), _samples("D:/Program/tex/MicroTeX/res/SAMPLES.tex")
    {
    }

    RenderOptionWidget *m_this;
    TeXRender *_render;
    TexEdit *_texedit;
    microtex::Samples _samples;
    void initUI();
};

void RenderOptionWidgetPrivate::initUI()
{

    /*QString sample(QStringLiteral("D:/Program/tex/MicroTeX/res/SAMPLES.tex"));
    _samples =  microtex::Samples(sample.toStdString());*/

    auto *texRenderWidget = new QtTeXRenderWidget();
    // 初始化渲染窗口
    _render = dynamic_cast<TeXRender *>(texRenderWidget);
    texRenderWidget->setMinimumWidth(400);

    // 为渲染窗口设置滚动条
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(texRenderWidget);

    // 设置操作窗口
    auto *toolWidget = new QWidget();
    auto *renderLay = new QVBoxLayout();
    auto *toolLay = new QHBoxLayout();
    auto *tipLabel = new QLabel(QStringLiteral("修改字体大小"));
    auto *sizeBox = new QSpinBox();
    sizeBox->setValue(texRenderWidget->getTextSize());
    auto *nextBtn = new QPushButton(QStringLiteral("下一个示例"));
    auto *renderBtn = new QPushButton(QStringLiteral("渲染"));
    auto *saveBtn = new QPushButton(QStringLiteral("保存为SVG图片"));
    auto *updateBtn = new QPushButton(QStringLiteral("更新主题"));
    toolLay->addWidget(tipLabel);
    toolLay->addWidget(sizeBox);
    toolLay->addWidget(nextBtn);
    toolLay->addWidget(renderBtn);
    toolLay->addWidget(saveBtn);
    toolLay->addWidget(updateBtn);
    toolWidget->setLayout(toolLay);

    renderLay->addWidget(scrollArea);
    renderLay->addWidget(toolWidget);

    m_this->setLayout(renderLay);

    // 对操作窗口的控件设置信号与槽
    QObject::connect(nextBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::nextClicked);
    QObject::connect(renderBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::renderClicked);
    QObject::connect(saveBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::saveClicked);
    QObject::connect(updateBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::updateStyle);
    QObject::connect(sizeBox, SIGNAL(valueChanged(int)), m_this, SLOT(fontSizeChanged(int)));
}

RenderOptionWidget::RenderOptionWidget(QWidget *parent) : QWidget(parent), d_ptr(new RenderOptionWidgetPrivate(this))
{

    d_ptr->initUI();
}
void RenderOptionWidget::setTexEdit(QTextEdit *p_edit)
{
    d_ptr->_texedit = qobject_cast<TexEdit *>(p_edit);
}
RenderOptionWidget::~RenderOptionWidget()
{
    delete d_ptr;
}

void RenderOptionWidget::fontSizeChanged(int size)
{
    d_ptr->_render->setTextSize(size);
}
void RenderOptionWidget::updateStyle()
{
    // QtConcurrent::run(this,&RenderOptionWidget::updatess);
    QtConcurrent::run([this]() { ACSSManager::getInstance()->updateStyleSheet(); });
}
void RenderOptionWidget::nextClicked()
{
    auto sample = d_ptr->_samples.next();
    d_ptr->_texedit->setText(QString::fromStdString(sample));
    d_ptr->_render->setLaTeX(sample);
}

void RenderOptionWidget::renderClicked()
{
    QString text = d_ptr->_texedit->toPlainText();
    d_ptr->_render->setLaTeX(text.toStdString());
}

void RenderOptionWidget::saveClicked()
{
    d_ptr->_render->saveSVG("out.svg");
}