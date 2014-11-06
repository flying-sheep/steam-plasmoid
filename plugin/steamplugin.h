#ifndef PLUGIN_H
#define PLUGIN_H

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class SteamPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

    public:
        virtual void registerTypes(const char *uri);
};

#endif // TASKMANAGERPLUGIN_H
