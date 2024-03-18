#include "ui/centralwidget.h"
#include "ads_globals.h"
#include "edit/highlighter.h"
#include "manager/microtexmanager.h"
#include "qglobal.h"
#include "ui/DebugLogDock.h"
#include "ui/favoritewidget.h"
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

    Highlighter *m_highlighter;

    microtex::Samples _samples;
};

void CentralWidgetPrivate::setupUI()
{
    // Q_INIT_RESOURCE(ads);

    CDockManager::setConfigFlag(CDockManager::XmlCompressionEnabled, false); // 不对xml文件进行压缩
    CDockManager::setAutoHideConfigFlags(CDockManager::DefaultAutoHideConfig);

    ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewIsDynamic, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewShowsContentPixmap, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    // When tabs title/text elide disabled and lots of tabs opened, tabs menu button will not show
    // as it only shows when tab title elided.
    // So disable dynamic tabs menu visibility.
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::EqualSplitOnInsertion, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::MiddleMouseButtonClosesTab, true);

    m_centralLay = new QVBoxLayout(m_this);

    m_DockManager = new CDockManager(m_this);
    m_DockManager->setStyleSheet(QStringLiteral(""));

    // 设置Tex编辑窗口//TODO:添加在那一边pin之后就停靠在那一边
    auto *texedit = new TexEdit();
    // auto *texedit = new ScintillaTex("a");

    // 设置渲染窗口//TODO:添加在那一边pin之后就停靠在那一边
    auto *renderWidget = new RenderOptionWidget();
    renderWidget->setTexEdit(texedit);
    // renderWidget->setScintillaTex(texedit);
    auto *renderDockWidget = new CDockWidget("Render");
    renderDockWidget->setWidget(renderWidget);
    // renderDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    // renderDockWidget->setMinimumSize(200, 150);
    // auto RenderArea = m_DockManager->addDockWidget(DockWidgetArea::RightDockWidgetArea, renderDockWidget);
    auto RenderArea = m_DockManager->setCentralWidget(renderDockWidget);
    RenderArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);

    texedit->setPlaceholderText("This is the central editor. Enter your text here.");
    texedit->setFont(QFont("FiraCode Nerd Font", 12));
    CDockWidget *TexEditDockWidget = new CDockWidget("TexEdit");
    TexEditDockWidget->setFeatures(CDockWidget::DockWidgetPinnable);
    TexEditDockWidget->setWidget(texedit);
    TexEditDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    TexEditDockWidget->resize(250, 150);
    TexEditDockWidget->setMinimumSize(500, 150);
    auto TexEditArea = m_DockManager->addDockWidget(DockWidgetArea::LeftDockWidgetArea, TexEditDockWidget);

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
    auto *logwidget = new DebugLogDock();
    CDockWidget *LogDockWidget = new CDockWidget("Log");
    LogDockWidget->setWidget(logwidget);
    LogDockWidget->setMinimumSizeHintMode(CDockWidget::MinimumSizeHintFromDockWidget);
    LogDockWidget->setMinimumSize(200, 150);
    auto LogArea = m_DockManager->addDockWidget(DockWidgetArea::BottomDockWidgetArea, LogDockWidget);

    /*const auto logautoHideContainer =
        m_DockManager->addAutoHideDockWidget(SideBarLocation::SideBarBottom, LogDockWidget);
    logautoHideContainer->setSize(240);*/

    m_highlighter = new Highlighter(texedit->document());
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
