#include "DebugLogDock.h"
#include "manager/debugmanager.h"
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QString>
class DebugLogDockPrivate
{
  public:
    DebugLogDockPrivate(DebugLogDock *p) : m_this(p)
    {
    }

    QPlainTextEdit *txtDebugOutput;
    DebugLogDock *m_this;
};
static QPlainTextEdit *output = Q_NULLPTR;

static void debugLogDockMessageHandler(const QString &msg)
{
    output->appendPlainText(msg);
}

DebugLogDock::DebugLogDock(QWidget *parent) : QDockWidget(parent), d_ptr(new DebugLogDockPrivate(this))
{
    setWindowTitle(QStringLiteral("调试日志"));
    d_ptr->txtDebugOutput = new QPlainTextEdit(this);
    setWidget(d_ptr->txtDebugOutput);

    output = d_ptr->txtDebugOutput;
    DebugManager::addMessageHandler(debugLogDockMessageHandler);

    connect(this, &QDockWidget::visibilityChanged, this, [=](bool visible) {
        if (visible)
        {
            d_ptr->txtDebugOutput->horizontalScrollBar()->setValue(0);
        }
    });
}

DebugLogDock::~DebugLogDock()
{
    delete d_ptr;
}