Steam plasmoid
==============

![Screenshot](/screenshot.png?raw=true)

Build instructions
------------------

```bash
cd /where/your/applet/is/generated
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
```

### Now either install globally…

```bash
sudo make install
kbuildsycoca5

kquitapp5 plasmashell
plasmashell
```

### …or run it in a temporary installation

```bash
./plasmoid-tempinstall-run.sh steam
```

Tutorials and resources
-----------------------
* [The explanation of the template](https://techbase.kde.org/Development/Tutorials/Plasma2/QML2/GettingStarted)
* [Plasma techbase pages](http://techbase.kde.org/Projects/Plasma2)
* [Plasma QML API explained](http://techbase.kde.org/Development/Tutorials/Plasma2/QML2/API)
* [C++ Models in QML](http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-cppmodels.html)


Where to get stuff from
-----------------------
* [Icons](http://forums.steampowered.com/forums/showthread.php?t=3128676)
