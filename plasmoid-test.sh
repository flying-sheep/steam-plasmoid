#!/bin/sh

myplasmoid=steam

(
	cd "org.kde.plasma.$myplasmoid"
	export QML2_IMPORT_PATH="../build/:${QML2_IMPORT_PATH-/usr/lib/qt/qml/}"
	plasmoidviewer "$@" .
)



#ktraderclient5 --servicetype Plasma/Applet | grep 'X-KDE-PluginInfo-Name' 
#ktraderclient --servicetype Plasma/Applet --constraint "[X-KDE-PluginInfo-Name] == 'org.kde.plasma.$myplasmoid'"

#org.kde.plasma.$myplasmoid/ → $prefix/share/plasma/plasmoids/
#org.kde.plasma.$myplasmoid/metadata.desktop → $prefix/share/kservices5/org.kde.plasma.$myplasmoid