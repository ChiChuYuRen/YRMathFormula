#pragma once

#include <QMutex>
#include <QObject>
#include <QThread>

class MicroTexManager final : QObject
{
  public:
    explicit MicroTexManager(QObject *parent = nullptr);
    ~MicroTexManager() final;
    /**
     * @brief 从默认字体路径中初始化字体
     *
     */
	/**
 * MicroTeX context initialization.
 * <ol>
 *  <li> If a FontSrc presents, the context will load math font from the given font source.
 *  <li> If a InitFontSenseAuto presents, fill the search dirs by following rules:
 *    <ul>
 *      <li> If environment variable `MICROTEX_FONTDIR` is set, add it into search dirs.
 *      <li> If environment variable `XDG_DATA_HOME` is set, add `${XDG_DATA_HOME}/microtex` into
 *           search dirs.
 *      <li> If environment variable `XDG_DATA_DIRS` is set, iterate over the list and add the sub
 *           dir `microtex` of each item into search dirs.
 *      <li> If the current platform is WIN32, add the dir `share/microtex` where its parent is the
 *           executable running dir into search dirs.
 *      <li> Otherwise, try the following ways:
 *      <ul>
 *        <li> If environment variable `HOME` is set, add dir `${HOME}/.local/share/microtex` into
 *             search dirs.
 *        <li> Add `/usr/local/share/microtex` into search dirs.
 *        <li> Add `/usr/share/microtex` into search dirs.
 *      </ul>
 *    </ul>
 *    And then iterate over the search dirs, add all found fonts to context, and select the first
 *    found math font as the default.
 *  <li> If a string presents, follow the above way to init the context but select the math font
 *       which its name was given by this string as the default.
 * </ol>
 */
    static void autoFontPathInit();
    /**
     * @brief 指定初始字体
     *
     * @param clm 用于渲染的公式字体
     * @param font 其他字体
     */
    void setDefaultFontInit(const QString &clm, const QString &font);

    void updateFont(const QString &clm, const QString &font);

    static void setDefaultFont(const QString& clm);

    QString getDefaultClm() const;
    QString getDefaultFont() const;

  private:
    static void release();

    // 默认字体
    QString m_defaultClm;
    QString m_defaultFont;
    // 用户自定义的字体
    QString m_outsideClm;
    QString m_outsideFont;
};



