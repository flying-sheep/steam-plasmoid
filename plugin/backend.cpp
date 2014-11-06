//https://projects.kde.org/projects/kde/workspace/plasma-desktop/repository/revisions/master/entry/applets/taskmanager/plugin/backend.cpp

#include "backend.h"
#include "texttoken.h"

#include <QDir>
#include <KIOWidgets/KRun>

Backend::Backend(QObject* parent) : QObject(parent), m_gamesModel(new GamesModel(this)) {
	initModel();
}

Backend::~Backend() {}

GamesModel* Backend::gamesModel() const {
	return m_gamesModel;
}

void Backend::initModel() {
	QDir appDir = QDir::home();
	appDir.cd(".local/share/Steam/SteamApps");
	QFileInfoList acfFiles = appDir.entryInfoList(QStringList("*.acf"), QDir::Files);
	
	QList<QFileInfo>::iterator fi;
	for (fi = acfFiles.begin(); fi != acfFiles.end(); ++fi) {
		QFile file(fi->absoluteFilePath());
		file.open(QIODevice::ReadOnly);
		
		QTextStream stream(&file);
		
		TextToken info(stream, "AppState");
		QString bytesKey("BytesToDownload");
		if (info.get<uint>(bytesKey) != 0) { //SteamVR and so on
			QString name = info.getValue("name");
			uint appID = info.get<uint>("appID");
			m_gamesModel->addInfo(GameInfo(name, appID));
		}
	}
}

void Backend::openUrl(QUrl url) {
	new KRun(url, 0);
}