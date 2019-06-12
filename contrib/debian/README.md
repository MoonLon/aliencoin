
Debian
====================
This directory contains files used to package aliencoind/aliencoin-qt
for Debian-based Linux systems. If you compile aliencoind/aliencoin-qt yourself, there are some useful files here.

## aliencoin: URI support ##


aliencoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install aliencoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your aliencoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/aliencoin128.png` to `/usr/share/pixmaps`

aliencoin-qt.protocol (KDE)

