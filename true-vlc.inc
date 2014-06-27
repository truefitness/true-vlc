#!/usr/bin/make

DEBVERSION := 2.0.8
UBVERSION := 0ubuntu0.12.04.1
TRVERSION := +true3
VERSION := ${DEBVERSION}-${UBVERSION}${TRVERSION}
APPNAME=vlc
SRCDIR=./src
DEBDIR=./debs
APPDIR=${SRCDIR}/${APPNAME}-${VERSION}
TARNAME=${APPDIR}.tar.gz
DSCNAME=${APPNAME}_${VERSION}.dsc
MAINTAINER=mpnolan@truefitness.com
BUILDDIR=${SRCDIR}/${APPNAME}-${DEBVERSION}
#DEBDIR := ${APPDIR}/debian
DEBIAN_TGZ := http://software.truefitness.com/true-vlc/2.0.8/vlc_2.0.8-0ubuntu0.12.04.1${TRVERSION}.debian.tar.gz


all: shownames getsources unpack build repo
getsources: get_debian_tgz get_source_package

shownames:
	@echo packaging ${APPDIR}
	@echo packagename=${APPNAME}
	@echo version=${VERSION}
	@echo dirname=${APPDIR}
	@echo debdir=${DEBDIR}
	@echo srcdir=${SRCDIR}
	@echo dscname=${DSCNAME}
	@echo buildir=${BUILDDIR}	
	@echo debian_tgz=${DEBIAN_TGZ}	
	
unpack:
	@echo dpkg-source ...
	(cd ${SRCDIR}; dpkg-source -x ${DSCNAME})

get_debian_tgz:
	@echo "downloading debian.tar.gz..."
	(cd ${SRCDIR}; wget -N ${DEBIAN_TGZ})

get_source_package:
	@echo "downloading orig.tar.gz from server..."
	(cd ${SRCDIR}; wget -N http://software.truefitness.com/true-vlc/2.0.8/vlc_2.0.8.orig.tar.xz)

source:
	@echo "creating source package..."
	(cd ${BUILDDIR}; debuild --no-lintian -S -uc -us -sd)

build:
	@echo building...
	( cd ${BUILDDIR}; dpkg-buildpackage -rfakeroot -b -us -uc -j4)

repo:
	@ echo building repository
	@mkdir -p repo/
	cp ${SRCDIR}/*.deb repo/
	(cd repo; dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz)
	
repo-clean:
	rm -rf ${BUILDDIR}
	rm -rf repo 

clean:
	rm -rf ${SRCDIR}/*.deb 
	rm -rf ${BUILDDIR}
	rm -rf repo

		
