#include "microtexmanager.h"
#include "yapplication.h"

// MicroTex
#include <graphic_qt.h>
#include <microtex.h>

MicroTexManager::MicroTexManager(QObject * /*unused*/) : QObject(yApp)
{
}

MicroTexManager::~MicroTexManager()
{
    release();
}

void MicroTexManager::autoFontPathInit()
{
	microtex::MicroTeX::setRenderGlyphUsePath(true);
    microtex::InitFontSenseAuto autoPath;
    microtex::Init variant;
    variant = autoPath;
    microtex::MicroTeX::init(variant);



    microtex::PlatformFactory::registerFactory("qt", std::make_unique<microtex::PlatformFactory_qt>());
    microtex::PlatformFactory::activate("qt");
}
void MicroTexManager::setDefaultFontInit(const QString &clm, const QString &font)
{
    // QString clm(QStringLiteral("D:/Program/tex/MicroTeX/res/firamath/FiraMath-Regular.clm2"));
    // QString otf(QStringLiteral("D:/Program/tex/MicroTeX/res/firamath/FiraMath-Regular.otf"));
    m_defaultClm = clm;
    m_defaultFont = font;
    microtex::MicroTeX::setRenderGlyphUsePath(true);

    QFile file(clm);
    file.open(QIODevice::ReadOnly);
    QByteArray data(file.readAll());
    const microtex::FontSrcData math(data.length(), reinterpret_cast<microtex::u8 *>(data.data()), font.toStdString());
    microtex::MicroTeX::init(math);

    microtex::PlatformFactory::registerFactory("qt", std::make_unique<microtex::PlatformFactory_qt>());
    microtex::PlatformFactory::activate("qt");
}

void MicroTexManager::setDefaultFont(const QString& clm)
{
    microtex::MicroTeX::setDefaultMathFont(clm.toStdString());
}
void MicroTexManager::updateFont(const QString &clm, const QString &font)
{
    release();
    setDefaultFontInit(clm, font);
}

QString MicroTexManager::getDefaultClm() const
{
    return m_defaultClm;
}

QString MicroTexManager::getDefaultFont() const
{
    return m_defaultFont;
}
void MicroTexManager::release()
{
    microtex::MicroTeX::release();
}