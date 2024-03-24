// Copyright (C) 2023-2024 Stdware Collections (https://www.github.com/stdware)
// Copyright (C) 2021-2023 wangwenx190 (Yuhang Zhao)
// SPDX-License-Identifier: Apache-2.0

#include "qobject.h"
#include "yapplication.h"

#include <QMessageBox>
int main(int argc, char *argv[])
{

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    QCoreApplication::setOrganizationName("ChiChuYuRen");
    QCoreApplication::setApplicationName("YRMathFormula");

    YApplication app(argc, argv);
    app.timerStart();
    // Log some debug info
    qInfo("=============================");
    qInfo("%s v%s%s", qUtf8Printable(QApplication::applicationDisplayName()),
          qUtf8Printable(QApplication::applicationVersion()), "YRMathFormula");
    qInfo("Build Date/Time: %s %s", __DATE__, __TIME__);
    qInfo("Qt: %s", qVersion());
    qInfo("OS: %s", qUtf8Printable(QSysInfo::prettyProductName()));
    qInfo("Locale: %s", qUtf8Printable(QLocale::system().name()));
    qInfo("CPU: %s", qUtf8Printable(QSysInfo::currentCpuArchitecture()));
    qInfo("File Path: %s", qUtf8Printable(QApplication::applicationFilePath()));
    qInfo("=============================");
    if (app.isPrimary())
    {
        app.init();

        return YApplication::exec();
    }
    else
    {
        qInfo() << "Primary instance already running. PID:" << app.primaryPid();

        app.sendInfoToPrimaryInstance();

        qInfo() << "Secondary instance closing...";

        YApplication::exit(0);

        return 0;
    }
}
