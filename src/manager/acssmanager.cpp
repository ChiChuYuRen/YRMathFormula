#include "acssmanager.h"
// ACSS
#include <QtAdvancedStylesheet.h>

#include "yapplication.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFont>
// ACSSManager *ACSSManager::_instance = nullptr;
ACSSManager::ACSSManager(QObject* parent)
{
}

void ACSSManager::init()
{
	QString AppDir = yApp->applicationDirPath();

	QString StylesDir = AppDir + "/share/styles";

	setStylesDirPath(StylesDir);
	setOutputDirPath(AppDir + "/output");
	setCurrentStyle("qt_material");
	setDefaultTheme();
	updateStylesheet();
	yApp->setStyleSheet(styleSheet());
	parseThemeJsonFile();
	yApp->setFont(QFont(m_fontFamily,m_fontSize.remove("px").toInt()));
}

bool ACSSManager::parseThemeJsonFile()
{
	QString StylesDir = yApp->applicationDirPath() + "/share/styles/" + currentStyle();
	QDir Dir(StylesDir);
	auto JsonFiles = Dir.entryInfoList({"*.json"}, QDir::Files);
	if (JsonFiles.count() < 1)
	{
		qInfo() << QStringLiteral("不存在json文件");
		return false;
	}

	if (JsonFiles.count() > 1)
	{
		qInfo() << QStringLiteral("json文件过多");
		return false;
	}

	QFile StyleJsonFile(JsonFiles[0].absoluteFilePath());
	StyleJsonFile.open(QIODevice::ReadOnly);

	auto JsonData = StyleJsonFile.readAll();
	StyleJsonFile.close();
	QJsonParseError ParseError{};
	auto JsonDocument = QJsonDocument::fromJson(JsonData, &ParseError);
	if (JsonDocument.isNull())
	{
		qInfo() << QStringLiteral("加载json文件内容出错:") + ParseError.errorString();
		return false;
	}

	QMap<QString, QString> Variables;
	auto json = JsonDocument.object();
	auto jvariables = json.value("variables").toObject();
	
	m_fontFamily = jvariables.value("font_family").toString();
	m_fontSize = jvariables.value("font_size").toString();
	m_lineHeight = jvariables.value("line_height").toString();

	

	m_defaultTheme = json.value("default_theme").toString();
	if (m_defaultTheme.isEmpty())
	{
		qInfo() << QStringLiteral("没有设置default_theme");
		return false;
	}

	return true;
}

bool ACSSManager::saveJsonFile() const
{
	QString StylesDir = yApp->applicationDirPath() + "/share/styles/" + currentStyle();
	QDir Dir(StylesDir);
	auto JsonFiles = Dir.entryInfoList({"*.json"}, QDir::Files);
	if (JsonFiles.count() < 1)
	{
		
		qInfo() << QStringLiteral("不存在json文件");
		return false;
	}

	if (JsonFiles.count() > 1)
	{
		qInfo() << QStringLiteral("json文件过多");
		return false;
	}

	QFile StyleJsonFile(JsonFiles[0].absoluteFilePath());
	StyleJsonFile.open(QIODevice::ReadOnly);

	auto JsonData = StyleJsonFile.readAll();
	StyleJsonFile.close();
	QJsonParseError ParseError{};
	auto JsonDocument = QJsonDocument::fromJson(JsonData, &ParseError);
	if (JsonDocument.isNull())
	{
		// setError(QtAdvancedStylesheet::StyleJsonError, "Loading style json file "
		//    "caused error: " +
		//    ParseError.errorString());
		qInfo() << QStringLiteral("加载json文件内容出错:") + ParseError.errorString();
		return false;
	}
	auto json = JsonDocument.object();
	auto jvariablesValue = json.value("variables");

	if (jvariablesValue.type() == QJsonValue::Object)
	{
		auto jvariables = jvariablesValue.toObject();
		jvariables["font_family"] = m_fontFamily;
		jvariables["font_size"] = m_fontSize;
		jvariables["line_height"] = m_lineHeight;

		json["variables"] = jvariables;
	}

	json["default_theme"] = currentTheme();

	JsonDocument.setObject(json);
	StyleJsonFile.open(QIODevice::WriteOnly);
	QTextStream wStream(&StyleJsonFile);
	wStream.setCodec("UTF-8");
	wStream << JsonDocument.toJson();
	StyleJsonFile.close();
	return true;
}

void ACSSManager::changeFont(const QString& family, int size)
{
	m_fontSize = QString::number(size)+"px";
	m_fontFamily = family;
	update();
}

void ACSSManager::changeLineHeight(int height)
{
	m_lineHeight = QString::number(height)+"px";
	update();
}

void ACSSManager::update()
{
	
	setCurrentTheme(currentTheme());
	
	updateStylesheet();
	saveJsonFile();
}
