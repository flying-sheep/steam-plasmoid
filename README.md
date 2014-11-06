Plasma Applet Template
======================

Build instructions
------------------

cd /where/your/applet/is/generated
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$KDEDIRS .. 
make 
make install

(your $KDEDIRS is where you install your KDE 4, set this variable in your .bashrc file)

Restart plasma to load the applet 
(in a terminal type: 
kquitapp plasma-desktop 
and then
plasma-desktop)

or view it with 
plasmoidviewer YourAppletName

You might need to run kbuildsycoca4
in order to get the .desktop file recognized.

Tutorials and resources
-----------------------
The explanation of the template
https://techbase.kde.org/Development/Tutorials/Plasma2/QML2/GettingStarted

Plasma techbase pages
http://techbase.kde.org/Projects/Plasma2

Plasma QML API explained
http://techbase.kde.org/Development/Tutorials/Plasma2/QML2/API

Where to get stuff from
-----------------------

Icons: http://forums.steampowered.com/forums/showthread.php?t=3128676