#!/bin/sh

XMP_SRCDIR=$1
XMP_TMPDIR=$2

DEB_DIR="${XMP_SRCDIR}/release/debian"
CHANGELOG_FILE="${DEB_DIR}/changelog"
CONTROL_FILE="${DEB_DIR}/control"
RULES_FILE="${DEB_DIR}/rules"
COMPAT_FILE="${DEB_DIR}/compat"
MKARCHIVE_FILE="${XMP_SRCDIR}/release/mkarchive"
XMPPKG_NAME="omni-compiler"
XMPPKG_VERSION="0.9.2"
XMPPKG_RELEASE="r20151127"
XMPPKG_PREFIX="//home/mnakao/work/xmp-trunk"
XMPPKG_CONF_PREFIX="/home/mnakao/work/xmp-trunk/etc"
ARCHIVE_NAME="${XMPPKG_NAME}"

clean_exit () {
	rm -rf "${XMP_TMPDIR}"
	exit $1
}

trap "clean_exit 1" INT HUP TERM

if test "$#" -ne 2 ; then
	echo "Usage: $0 <top_src_dir> <tmp_dir> <prefix>"
	exit 1
fi
if test ! -d "$1" -o ! -d "$2" ; then
	echo "Usage: $0 <top_src_dir> <tmp_dir> <prefix>"
	exit 1
fi
if test -z "${XMPPKG_NAME}" -o -z "${XMPPKG_VERSION}" -o -z "${XMPPKG_RELEASE}" ; then
	clean_exit 1
fi
if test ! -f "${MKARCHIVE_FILE}" ; then
	clean_exit 1
fi

# create archive
rm -f "${ARCHIVE_NAME}.tar.gz"

/bin/sh "${MKARCHIVE_FILE}" "${ARCHIVE_NAME}"
if test "$?" -ne 0 ; then
	clean_exit 1
fi

# extract archive
if test ! -f "${ARCHIVE_NAME}.tar.gz" ; then
	clean_exit 1
fi
mv "${ARCHIVE_NAME}.tar.gz" "${XMP_TMPDIR}"/.
if test "$?" -ne 0 ; then
	clean_exit 1
fi
cd "${XMP_TMPDIR}"
tar zxf "${ARCHIVE_NAME}.tar.gz"

# build
cd "${XMP_TMPDIR}"/"${XMPPKG_NAME}"
./configure --sysconfdir=${XMPPKG_CONF_PREFIX} --prefix=${XMPPKG_PREFIX} \
&& make clean \
&& make \
&& make sysconfdir=${XMP_TMPDIR}/debian/${XMPPKG_NAME}/${XMPPKG_CONF_PREFIX} prefix=${XMP_TMPDIR}/debian/${XMPPKG_NAME}/${XMPPKG_PREFIX} install \
|| clean_exit 1

# copy conffiles
cp ${CHANGELOG_FILE} ${XMP_TMPDIR}/debian/. \
&& cp ${RULES_FILE} ${XMP_TMPDIR}/debian/. \
&& cp ${COMPAT_FILE} ${XMP_TMPDIR}/debian/. \
|| clean_exit 1

sed -e "/^Section:\s*$/d" -e "/^Priority:\s*$/d" ${CONTROL_FILE} > ${XMP_TMPDIR}/debian/control \
|| clean_exit 1

# build DEB file
cd ${XMP_TMPDIR}
dpkg-buildpackage -d -rfakeroot -uc -us
if test "$?" -ne 0 ; then
	clean_exit 1
fi
CPU=`dpkg-architecture -qDEB_HOST_ARCH`
if test "$?" -ne 0 ; then
	clean_exit 1
fi
cp "../${XMPPKG_NAME}_${XMPPKG_VERSION}-${XMPPKG_RELEASE}_${CPU}.deb" "${XMP_SRCDIR}"/.

rm -rf ${XMP_TMPDIR}
mkdir -p ${XMP_TMPDIR}
cp "../${XMPPKG_NAME}_${XMPPKG_VERSION}-${XMPPKG_RELEASE}_${CPU}.deb" ${XMP_TMPDIR}
cd ${XMP_TMPDIR}
apt-ftparchive packages . | gzip -9c > "${XMP_SRCDIR}"/Packages.gz
apt-ftparchive contents . | gzip -9c > "${XMP_SRCDIR}"/Contents.gz
apt-ftparchive release  . > "${XMP_SRCDIR}"/Release

echo "  $ scp ${XMPPKG_NAME}_${XMPPKG_VERSION}-${XMPPKG_RELEASE}_${CPU}.deb Packages.gz Contents.gz Release omni@omni-compiler.org:~/public_html/download/package/[debian|ubuntu]/stable/"

# clean up
rm -rf ${XMP_TMPDIR}

exit 0
