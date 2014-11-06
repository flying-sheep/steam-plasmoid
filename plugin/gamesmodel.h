#ifndef GAMESMODEL_H
#define GAMESMODEL_H

#include <QtCore>

class GameInfo {
public:
	GameInfo(QString & name, uint & appID);
	QString name() const;
	uint appID() const;

private:
	QString m_name;
	uint m_appID;
};

class GamesModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum GameRoles {
		NameRole = Qt::UserRole + 1,
		AppIDRole
	};
	
	GamesModel(QObject * parent = nullptr);
	
	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	
	void addInfo(const GameInfo & info);

protected:
	QHash<int, QByteArray> roleNames() const;

private:
	QList<GameInfo> m_gameInfos;
};

#endif // GAMESMODEL_H
