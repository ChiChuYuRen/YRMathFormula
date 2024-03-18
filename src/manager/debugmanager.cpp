#include "debugmanager.h"

#include <QList>

Q_GLOBAL_STATIC(QList<DebugOutputHandler>, handlers);
Q_GLOBAL_STATIC(QStringList, buffered_debug_output);
QtMessageHandler original = Q_NULLPTR;

static void buffer_debug_output(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    buffered_debug_output->append(qFormatLogMessage(type, context, msg));

    original(type, context, msg);
}

static void debug_manager_handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const QString log_message = qFormatLogMessage(type, context, msg);
    for (DebugOutputHandler handler : *handlers)
    {
        handler(log_message);
    }

    original(type, context, msg);
}

void DebugManager::manageDebugOutput()
{
    // Just to be safe, restore the original message handler
    qInstallMessageHandler(0);

    // Clear the list if it was ever used previously
    handlers->clear();

    // Install our own custom handler
    original = qInstallMessageHandler(debug_manager_handler);
}

void DebugManager::pauseDebugOutput()
{
    // Just to be safe, restore the original message handler
    qInstallMessageHandler(0);

    buffered_debug_output->clear();

    original = qInstallMessageHandler(buffer_debug_output);
}

void DebugManager::resumeDebugOutput()
{
    for (DebugOutputHandler handler : *handlers)
    {
        for (const QString &msg : *buffered_debug_output)
        {
            handler(msg);
        }
    }

    buffered_debug_output->clear();

    qInstallMessageHandler(debug_manager_handler);
}

void DebugManager::addMessageHandler(DebugOutputHandler handler)
{
    handlers->append(handler);
}
