#include "gamesmodel.h"

GameInfo::GameInfo(QString & name, uint & appID): m_name(name), m_appID(appID) {}

QString GameInfo::name() const {
	return m_name;
}

uint GameInfo::appID() const {
	return m_appID;
}

/////////////////////////

GamesModel::GamesModel(QObject * parent) : QAbstractListModel(parent) {
	
}

QHash<int, QByteArray> GamesModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[NameRole] = "name";
	roles[AppIDRole] = "appID";
	return roles;
}

void GamesModel::addInfo(const GameInfo & info) {
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_gameInfos << info;
	endInsertRows();
}

int GamesModel::rowCount(const QModelIndex & parent) const {
	Q_UNUSED(parent);
	return m_gameInfos.count();
}

QVariant GamesModel::data(const QModelIndex & index, int role) const {
	int row = index.row();
	if (row > m_gameInfos.count() || row < 0 )
		return QVariant();
	
	const GameInfo info = m_gameInfos[row];
	switch(role) {
		case Qt::DisplayRole: return QString("%1 (%2)").arg(info.name()).arg(QString::number(info.appID()));
		case NameRole: return info.name();
		case AppIDRole: return info.appID();
		default: return QVariant();
	};
}

#include "gamesmodel.moc"
