#!/bin/bash

# note: set DEBFULLNAME, DEBEMAIL in .bashrc prior to running

sudo apt-add-repository ppa:djcj/vlc-stable
sudo apt-get update
cd true-vlc/src
#sudo apt-get build-dep vlc=2.1.3-1~ubuntu12.04.2~ppa1 ??? not sure if this works
apt-get source vlc=2.1.3-1~ubuntu12.04.2~ppa1
cd vlc-2.1.3
dch -l "+true" "Initial build for True Fitness"
#modify debian/rules and replace confflags with correct enable/disable options
dpkg-buildpackage -b -us -uc -j4

#sudo apt-get build-dep vlc

cd vlc-2.1.3
quilt new true-gc-black-screenfix.patch
quilt add src/declarative/qml/qdeclarative{component,objectscriptclass,vme}.cpp
quilt add src/declarative/qml/qdeclarativedata_p.h 
patch -p6 < ../../true_patches/rootObjectCreation.patch
quilt refresh
#quilt header -e "message"

#dch -v "4:4.8.4+dfsg-0ubuntu18.1~precise1+true2"

#dpkg-buildpackage -us -uc -j4

# sequence to add a patch and rebuild
#make getsources
#make unpack
#cd src/vlc-2.1.3
#quilt new foo.patch
#quilt add src/foo.cpp
#patch -p0 < some.patch
#quilt refresh
#dch -v "2.1.3-1~ubuntu12.04.2~ppa1+true2" "log message"
# edit makefile and bump TRVERSION
#make source
#make

