#include "mainwindow.h"
#include "manager/microtexmanager.h"
#include "ui/centralwidget.h"

// Qt
#include <QActionGroup>
#include <QApplication>
#include <QColorDialog>
#include <QDockWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
// ACSS
#include <QtAdvancedStylesheet.h>

// MicroTex
#include <graphic_qt.h>
#include <microtex.h>

/**
 * Private data class - pimpl
 */
class MainWindowPrivate
{
  public:
    MainWindow *m_this;
    // Ui::MainWindow ui;
    acss::QtAdvancedStylesheet *m_advancedStyleSheet;
    QVector<QPushButton *> m_themeColorButtons;
    CentralWidget *m_centralWidget;
    QMenuBar *m_menuBar;
    /**
     * Private data constructor
     */
    MainWindowPrivate(MainWindow *_public) : m_this(_public)
    {
    }
    ~MainWindowPrivate();
    void setupAcss();
    void setupMenuBar();
    void initUI();
    void createThemeColorDockWidget();
    void fillThemeMenu();

    /// \brief 初始化MicroTex引擎
    void setupMicroTex();

    void updateThemeColorButtons();
};

MainWindowPrivate::~MainWindowPrivate()
{
}

void MainWindowPrivate::setupMicroTex()
{
    MicroTexManager::autoFontPathInit();
}

/**
 * @brief 创建一个Change Theme窗口
 *
 */
void MainWindowPrivate::createThemeColorDockWidget()
{
    auto *dock = new QDockWidget(("Change Theme"), m_this);
    QWidget *w = new QWidget(dock);
    auto *Layout = new QVBoxLayout(w);
    Layout->setContentsMargins(12, 12, 12, 12);
    Layout->setSpacing(12);
    w->setLayout(Layout);
    dock->setWidget(w);
    m_this->addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setFloating(true);

    const auto &ThemeColors = m_advancedStyleSheet->themeColorVariables();
    for (auto itc = ThemeColors.constBegin(); itc != ThemeColors.constEnd(); ++itc)
    {
        auto *Button = new QPushButton(itc.key());
        QObject::connect(Button, &QPushButton::clicked, m_this, &MainWindow::onThemeColorButtonClicked);
        Layout->addWidget(Button);
        m_themeColorButtons.append(Button);
    }

    updateThemeColorButtons();
}
/**
 * @brief 当主题颜色窗口颜色改变后调用函数
 *
 */
void MainWindowPrivate::updateThemeColorButtons()
{
    for (auto *Button : m_themeColorButtons)
    {
        auto Color = m_advancedStyleSheet->themeColor(Button->text());
        QString TextColor = (Color.value() < 128) ? "#ffffff" : "#000000";
        QString ButtonStylesheet = QString("background-color: %1; color: %2;"
                                           "border: none;")
                                       .arg(Color.name())
                                       .arg(TextColor);
        Button->setStyleSheet(ButtonStylesheet);
    }
}
/**
 * @brief 加载指定目录下的所有主题文件并填充菜单栏
 *
 */
void MainWindowPrivate::fillThemeMenu()
{

    auto *m = new QMenu(QObject::tr("Theme"));
    for (const auto &Theme : m_advancedStyleSheet->themes())
    {
        QAction *a = new QAction(Theme);
        m->addAction(a);
        QObject::connect(a, &QAction::triggered, m_this, &MainWindow::onThemeActionTriggered);
    }
    m_menuBar->addMenu(m);
}

// MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), d_ptr(new MainWindowPrivate(this))
MainWindow::MainWindow(QApplication *parent) : app(parent), d_ptr(new MainWindowPrivate(this))
{

    d_ptr->initUI();

    setMenuBar(d_ptr->m_menuBar);

    setCentralWidget(d_ptr->m_centralWidget);

    setWindowTitle(tr("YRMathFormula"));
    resize(1280, 720);
}

MainWindow::~MainWindow()
{
    delete d_ptr;
}
QMenuBar *MainWindow::getMenuBar() const
{
    return d_ptr->m_menuBar;
}

void MainWindowPrivate::initUI()
{
    setupMicroTex();

    m_centralWidget = new CentralWidget(m_this);
    setupMenuBar();
    setupAcss();
}
/**
 * @brief 设置Acss相关参数并加载样式
 *
 */
void MainWindowPrivate::setupAcss()
{
    // QString AppDir = qApp->applicationDirPath();

    // // TODO: Release时修改加载style的路径
    // QString StylesDir = AppDir + "/share/styles";
    // // QString StylesDir = "D:/myprogram/YRMathType/src/resources/styles";
    // m_advancedStyleSheet = new acss::QtAdvancedStylesheet(m_this);
    // m_advancedStyleSheet->setStylesDirPath(StylesDir);
    // m_advancedStyleSheet->setOutputDirPath(AppDir + "/output");
    // m_advancedStyleSheet->setCurrentStyle("qt_material");
    // m_advancedStyleSheet->setDefaultTheme();
    // m_advancedStyleSheet->updateStylesheet();
    // // setWindowIcon(d->AdvancedStyleSheet->styleIcon());
    // qApp->setStyleSheet(m_advancedStyleSheet->styleSheet());
    // QObject::connect(m_advancedStyleSheet, SIGNAL(stylesheetChanged()), m_this,
    //                  SLOT(onStyleManagerStylesheetChanged()));

    // // createThemeColorDockWidget();
    // fillThemeMenu();
}
/**
 * @brief 设置菜单栏
 *
 */
void MainWindowPrivate::setupMenuBar()
{
    // 2. Construct your title bar
    m_menuBar = [this]() {
        auto *menuBar = new QMenuBar();

        // Virtual menu
        auto *file = new QMenu(QObject::tr("File(&F)"), menuBar);
        file->addAction(new QAction(QObject::tr("New(&N)"), menuBar));
        file->addAction(new QAction(QObject::tr("Open(&O)"), menuBar));
        file->addSeparator();

        auto *edit = new QMenu(QObject::tr("Edit(&E)"), menuBar);
        edit->addAction(new QAction(QObject::tr("Undo(&U)"), menuBar));
        edit->addAction(new QAction(QObject::tr("Redo(&R)"), menuBar));

        menuBar->addMenu(file);
        menuBar->addMenu(edit);

        return menuBar;
    }();
    m_menuBar->setObjectName(QStringLiteral("win-menu-bar"));
}
/**
 * @brief Theme改变后更新样式
 *
 */
void MainWindow::onThemeActionTriggered()
{
    auto *Action = qobject_cast<QAction *>(sender());
    d_ptr->m_advancedStyleSheet->setCurrentTheme(Action->text());
    d_ptr->m_advancedStyleSheet->updateStylesheet();
}

void MainWindow::onStyleManagerStylesheetChanged()
{
    qApp->setStyleSheet(d_ptr->m_advancedStyleSheet->styleSheet());
    d_ptr->updateThemeColorButtons();
}
/**
 * @brief Change Theme窗口的颜色按钮点击事件, 弹出颜色选择对话框并更新样式
 *
 */
void MainWindow::onThemeColorButtonClicked()
{
    auto *Button = qobject_cast<QPushButton *>(sender());
    QColorDialog ColorDialog;
    auto Color = d_ptr->m_advancedStyleSheet->themeColor(Button->text());
    ColorDialog.setCurrentColor(Color);
    if (ColorDialog.exec() != QDialog::Accepted)
    {
        return;
    }
    Color = ColorDialog.currentColor();
    d_ptr->m_advancedStyleSheet->setThemeVariableValue(Button->text(), Color.name());
    d_ptr->m_advancedStyleSheet->updateStylesheet();
}
