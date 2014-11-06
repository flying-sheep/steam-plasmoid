#include "steamplugin.h"
#include "backend.h"

#include <QtQml>
#include <QQmlDebuggingEnabler>


void SteamPlugin::registerTypes(const char *uri) {
	QQmlDebuggingEnabler enabler;
	Q_ASSERT(uri == QLatin1String("org.kde.plasma.private.steam"));
	qmlRegisterType<Backend>(uri, 0, 1, "Backend");
}

#include "steamplugin.moc"
