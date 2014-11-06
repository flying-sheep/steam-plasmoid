#!/bin/sh
#usage: ./plasmoid-tempinstall-run.sh plasmoidname

myplasmoid=$1

uninstall() {
	echo installing
	
	#plasmapkg2 -r "org.kde.plasma.$myplasmoid"
	
	rm -r "$HOME/.local/share/plasma/plasmoids/org.kde.plasma.$myplasmoid"
	rmdir --ignore-fail-on-non-empty "$HOME/.local/share/plasma/plasmoids"
	rm -r "$HOME/.local/share/kservices5/plasma-applet-org.kde.plasma.$myplasmoid.desktop"
	rmdir --ignore-fail-on-non-empty "$HOME/.local/share/kservices5"
	
	kbuildsycoca5
}

install_() {
	echo uninstalling
	
	plasmapkg2 -i "./org.kde.plasma.$myplasmoid"
	
	kbuildsycoca5
}


if [[ -d "$HOME/.local/share/plasma/plasmoids/org.kde.plasma.$myplasmoid" ]]; then
	uninstall
fi

install_

QML2_IMPORT_PATH="./build" plasmawindowed "org.kde.plasma.$myplasmoid"

uninstall


#ktraderclient5 --servicetype Plasma/Applet | grep 'X-KDE-PluginInfo-Name' 
#ktraderclient --servicetype Plasma/Applet --constraint "[X-KDE-PluginInfo-Name] == 'org.kde.plasma.$myplasmoid'"

#org.kde.plasma.$myplasmoid/ → $prefix/share/plasma/plasmoids/
#org.kde.plasma.$myplasmoid/metadata.desktop → $prefix/share/kservices5/org.kde.plasma.$myplasmoid