#include "microtexmanager.h"
#include "yapplication.h"

// MicroTex
#include <microtex.h>
#include <graphic_qt.h>

MicroTexManager::MicroTexManager(QObject* /*unused*/) : QObject(yApp)
{
}

MicroTexManager::~MicroTexManager()
{
	release();
}

void MicroTexManager::init()
{
	microtex::InitFontSenseAuto autoPath;
	microtex::Init variant;
	variant = autoPath;
	microtex::MicroTeX::init(variant);

	microtex::MicroTeX::setRenderGlyphUsePath(true);

	microtex::PlatformFactory::registerFactory("qt", std::make_unique<microtex::PlatformFactory_qt>());
	microtex::PlatformFactory::activate("qt");
}


void MicroTexManager::release()
{
	 microtex::MicroTeX::release();
}