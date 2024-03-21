#include "renderoptionwidget.h"
#include "manager/acssmanager.h"
#include "manager/microtexmanager.h"
#include "qcombobox.h"
#include "qglobal.h"
#include "qobject.h"
#include "qt_tex_render.h"
#include "samples.h"
#include "texeditor.h"
#include "ui/qttexrenderwidget.h"
#include "ui/texeditor.h"
#include "yapplication.h"

// Qt
#include <QComboBox>
#include <QFontDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrent>

class RenderOptionWidgetPrivate
{
  public:
    RenderOptionWidgetPrivate(RenderOptionWidget *p)
        : m_this(p), _samples("D:/Program/tex/MicroTeX/res/SAMPLES.tex"), m_microTexManager(new MicroTexManager())
    {
    }

    RenderOptionWidget *m_this;
    TeXRender *_render;
    TexEditor *_texedit;
    microtex::Samples _samples;
    MicroTexManager *m_microTexManager;
    QComboBox *m_fontComboBox;
    void initUI();
};

void RenderOptionWidgetPrivate::initUI()
{
#ifdef QT_DEBUG
    qInfo() << "[" << yApp->elapseTime() << "]" << Q_FUNC_INFO << " ," << __FILE__ << " ," << __LINE__;
#endif

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
    auto *fontBtn = new QPushButton(QStringLiteral("设置字体"));
    QMap<QString, QString> fontMap;
    fontMap.insert("Garamond", "Garamond-Math");
    fontMap.insert("latinmodern", "LatinModernMath-Regular");
    fontMap.insert("STIXTwoMath", "STIX Two Math");

    m_fontComboBox = new QComboBox();
    foreach (const QString &fontName, fontMap.keys())
    {
        m_fontComboBox->addItem(fontName, fontMap.value(fontName));
    }

    toolLay->addWidget(tipLabel);
    toolLay->addWidget(sizeBox);
    toolLay->addWidget(nextBtn);
    toolLay->addWidget(renderBtn);
    toolLay->addWidget(m_fontComboBox);
    toolLay->addWidget(saveBtn);
    toolLay->addWidget(fontBtn);

    toolWidget->setLayout(toolLay);

    renderLay->addWidget(scrollArea);
    renderLay->addWidget(toolWidget);

    m_this->setLayout(renderLay);

    // 对操作窗口的控件设置信号与槽
    QObject::connect(nextBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::nextClicked);
    QObject::connect(renderBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::renderClicked);
    QObject::connect(saveBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::saveClicked);
    QObject::connect(fontBtn, &QPushButton::clicked, m_this, &RenderOptionWidget::fontBtnClicked);
    QObject::connect(m_fontComboBox, SIGNAL(currentIndexChanged(QString)), m_this, SLOT(fontChanged(QString)));
    QObject::connect(sizeBox, SIGNAL(valueChanged(int)), m_this, SLOT(fontSizeChanged(int)));
}

RenderOptionWidget::RenderOptionWidget(QWidget *parent) : QWidget(parent), d_ptr(new RenderOptionWidgetPrivate(this))
{

    d_ptr->initUI();
}
void RenderOptionWidget::setTexEdit(QPlainTextEdit *p_edit)
{
    d_ptr->_texedit = qobject_cast<TexEditor *>(p_edit);
}

RenderOptionWidget::~RenderOptionWidget()
{
    delete d_ptr;
}

void RenderOptionWidget::fontSizeChanged(int size)
{
    d_ptr->_render->setTextSize(size);
}

void RenderOptionWidget::fontChanged(const QString &font)
{ // TODO: 这里需要修改,更改字体无变化
    QString text = d_ptr->_texedit->toPlainText();
    MicroTexManager::setDefaultFont(d_ptr->m_fontComboBox->currentData().toString());
    d_ptr->_render->setLaTeX(text.toStdString());
}

void RenderOptionWidget::nextClicked()
{
    auto sample = d_ptr->_samples.next();
    d_ptr->_texedit->setPlainText(QString::fromStdString(sample));
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

void RenderOptionWidget::fontBtnClicked()
{
    bool flag = true;
    QFont font = QFontDialog::getFont(&flag, QApplication::font(), this, QStringLiteral("选择字体"),
                                      QFontDialog::ScalableFonts | QFontDialog::MonospacedFonts |
                                          QFontDialog::ProportionalFonts);

    QApplication::setFont(font);
    yApp->getACSSManager()->changeFont(font.family(), font.pointSize());
}