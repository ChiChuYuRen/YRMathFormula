#include "microtexmanager.h"
#include "qstringliteral.h"
#include "yapplication.h"

// MicroTex
#include <graphic_qt.h>
#include <microtex.h>

MicroTexManager::MicroTexManager(QObject * /*unused*/) : QObject(yApp)
{
}

MicroTexManager::~MicroTexManager()
{
    //release();
}
void MicroTexManager::init()
{
    /*
    默认使用内置字体进行渲染
    当在设置中选择外置字体时才从外部指定路径或者变量中加载
    */

    setDefaultFontInit(":/clm/STIXTwoMath", "");
}
void MicroTexManager::autoFontPathInit()
{ // TODO:解决加载大量字体占用内存过大问题
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
#ifdef QT_DEBUG
    qInfo() << "[" << yApp->elapseTime() << "]" << Q_FUNC_INFO << " ," << __FILE__ << " ," << __LINE__;
#endif
    qInfo() << QStringLiteral("初始化内置字体成功");
}

void MicroTexManager::setDefaultFont(const QString &clm)
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

QStringList MicroTexManager::getMathFontNames()
{
    QStringList list;
    std::vector<std::string> fonts = microtex::MicroTeX::mathFontNames();
    for (const auto &font : fonts)
    {
        list.append(QString::fromStdString(font));
    }
    return list;
}

QStringList MicroTexManager::getFontFamilies()
{
    QStringList list;
    std::vector<std::string> fonts = microtex::MicroTeX::mainFontFamilies();
    for (const auto &font : fonts)
    {
        list.append(QString::fromStdString(font));
    }
    return list;
}