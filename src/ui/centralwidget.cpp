#include "ui/centralwidget.h"
#include "manager/microtexmanager.h"
#include "qglobal.h"
#include "ui/favoritewidget.h"
#include "ui/logwidget.h"
#include "ui/qttexrenderwidget.h"
#include "ui/renderoptionwidget.h"
#include "ui/texedit.h"

// Qt
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QSpinBox>
#include <QTableWidget>

// ads
#include <AutoHideDockContainer.h>
#include <DockAreaTitleBar.h>
#include <DockAreaWidget.h>
#include <DockManager.h>
#include <DockWidget.h>

#include "samples.h"

using namespace ads;

class CentralWidgetPrivate
{
  public:
    CentralWidgetPrivate(CentralWidget *p) : m_this(p), _samples("D:/Program/tex/MicroTeX/res/SAMPLES.tex")
    {
    }

    void setupUI();

    ads::CDockWidget *createFavoriteWidget();
    CentralWidget *m_this;
    CDockManager *m_DockManager;
    QVBoxLayout *m_centralLay;

    QWidget *_texwidget;
    TeXRender *_render;
    QTextEdit *_textedit;
    QSpinBox *_sizespin;

    microtex::Samples _samples;
};

void CentralWidgetPrivate::setupUI()
{
    // Q_INIT_RESOURCE(ads);

    CDockManager::setConfigFlag(CDockManager::OpaqueSplitterResize, true);   // 调整大小实时预览
    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false); // 不对xml文件进行压缩
    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    CDockManager::setAutoHideConfigFlags(CDockManager::DefaultAutoHideConfig);
    m_centralLay = new QVBoxLayout(m_this);

    m_DockManager = new CDockManager(m_this);
    m_DockManager->setStyleSheet(QStringLiteral(""));

    // 设置Tex编辑窗口//TODO:添加在那一边pin之后就停靠在那一边
    auto *texedit = new TexEdit();
    texedit->setPlaceholderText("This is the central editor. Enter your text here.");
    texedit->setFontFamily("Monaco");
    CDockWidget *TexEditDockWidget = new CDockWidget("TexEdit");
    TexEditDockWidget->setFeatures(CDockWidget::DockWidgetPinnable);
    TexEditDockWidget->setWidget(texedit);
    TexEditDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TexEditDockWidget->resize(250, 150);
    TexEditDockWidget->setMinimumSize(200, 150);
    auto TexEditArea = m_DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TexEditDockWidget);

    // 设置渲染窗口//TODO:添加在那一边pin之后就停靠在那一边
    auto *renderWidget = new RenderOptionWidget();
    renderWidget->setTexEdit(texedit);
    auto *renderDockWidget = new CDockWidget("Render");
    renderDockWidget->setWidget(renderWidget);
    renderDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    renderDockWidget->setMinimumSize(200, 150);
    auto RenderArea = m_DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, renderDockWidget);

    // TODO: 设置便捷输入按钮的窗口
    auto *table = new QTableWidget();
    table->setColumnCount(3);
    table->setRowCount(10);
    CDockWidget *TableDockWidget = new CDockWidget("Table");
    TableDockWidget->setWidget(table);
    TableDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->setMinimumSize(200, 150);
    // auto TableArea = m_DockManager->addDockWidget(DockWidgetArea::TopAutoHideArea, TableDockWidget);
    const auto autoHideContainer = m_DockManager->addAutoHideDockWidget(SideBarLocation::SideBarTop, TableDockWidget);
    autoHideContainer->setSize(480);
    // 日志窗口
    auto *logwidget = new LogWidget();
    CDockWidget *LogDockWidget = new CDockWidget("Log");
    LogDockWidget->setWidget(logwidget);
    LogDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    LogDockWidget->setMinimumSize(200, 150);
    auto LogArea = m_DockManager->addDockWidget(DockWidgetArea::BottomDockWidgetArea, LogDockWidget);
    const auto logautoHideContainer =
        m_DockManager->addAutoHideDockWidget(SideBarLocation::SideBarBottom, LogDockWidget);
    logautoHideContainer->setSize(240);
    QStringList fontNames = MicroTexManager::getMathFontNames();
    foreach (auto font, fontNames)
    {
        logwidget->append(font);
    }
    QStringList fontFamilies = MicroTexManager::getFontFamilies();
    logwidget->append("font families\n");
    foreach (auto font, fontFamilies)
    {
        logwidget->append(font);
    }
    // 布局管理
    m_centralLay->addWidget(m_DockManager);
    m_this->setLayout(m_centralLay);
}

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent), d_ptr(new CentralWidgetPrivate(this))
{
    d_ptr->setupUI();
    // d_ptr->testUI();
}

CentralWidget::~CentralWidget()
{
    delete d_ptr;
}
