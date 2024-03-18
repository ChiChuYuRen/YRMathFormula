#pragma once

#include <QtMessageHandler>

typedef void (*DebugOutputHandler)(const QString &str);

namespace DebugManager
{
void manageDebugOutput();
void pauseDebugOutput();
void resumeDebugOutput();
void addMessageHandler(DebugOutputHandler handler);
} // namespace DebugManager
