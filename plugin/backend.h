#ifndef BACKEND_H
#define BACKEND_H

#include "gamesmodel.h"

class QQuickItem;

class Backend : public QObject {
	Q_OBJECT
	Q_PROPERTY(QObject* gamesModel READ gamesModel CONSTANT)

public:
	Backend(QObject *parent = 0);
	~Backend();
	GamesModel * gamesModel() const;
	Q_INVOKABLE void openUrl(QUrl url);

private:
	GamesModel * m_gamesModel;
	void initModel();
};

#endif