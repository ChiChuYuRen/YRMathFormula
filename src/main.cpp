// Copyright (C) 2023-2024 Stdware Collections (https://www.github.com/stdware)
// Copyright (C) 2021-2023 wangwenx190 (Yuhang Zhao)
// SPDX-License-Identifier: Apache-2.0

#include "yapplication.h"

#include "MainWindow.h"

int main(int argc, char *argv[])
{

    // load res from libqnanopainter
    // Q_INIT_RESOURCE(ads_CMAKE_);

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    QCoreApplication::setOrganizationName("ChiChuYuRen");
    QCoreApplication::setApplicationName("YRMathType");

    YApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
