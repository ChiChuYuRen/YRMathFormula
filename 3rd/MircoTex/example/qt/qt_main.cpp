#include <QApplication>

#include "graphic_qt.h"
#include "microtex.h"
#include "qt_mainwindow.h"

void initQt() {
  microtex::PlatformFactory::registerFactory(
    "qt",
    std::make_unique<microtex::PlatformFactory_qt>()
  );
  microtex::PlatformFactory::activate("qt");
}

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QString clm(QStringLiteral("D:/Program/tex/MicroTeX/res/firamath/FiraMath-Regular.clm2"));
  QString otf(QStringLiteral("D:/Program/tex/MicroTeX/res/firamath/FiraMath-Regular.otf"));
  QString sample(QStringLiteral("D:/Program/tex/MicroTeX/res/SAMPLES.tex"));
  const microtex::FontSrcFile math{clm.toStdString(), otf.toStdString()};
  microtex::MicroTeX::init(math);
  const std::string samples(sample.toStdString());
  microtex::MicroTeX::setRenderGlyphUsePath(false);

  initQt();

  MainWindow win(nullptr, samples);
  win.show();
  int ret = QApplication::exec();

  microtex::MicroTeX::release();
  return ret;
}
