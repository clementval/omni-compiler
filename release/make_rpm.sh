#!/bin/sh

XMP_SRCDIR=$1
XMP_TMPDIR=$2

XMP_RPM_BUILD_DIR="${XMP_TMPDIR}/rpmbuild/"
XMPPKG_NAME="omni-compiler"
XMPPKG_VERSION="0.9.2"
XMPPKG_RELEASE="r20151127"
SPEC_FILE_NAME="xcalablemp.spec"
SPEC_FILE="${XMP_SRCDIR}/release/${SPEC_FILE_NAME}"
MKARCHIVE_FILE="${XMP_SRCDIR}/release/mkarchive"
ARCHIVE_NAME="${XMPPKG_NAME}-${XMPPKG_VERSION}"

clean_exit () {
        rm -rf ${XMP_RPM_BUILD_DIR}
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
test ! -f "${MKARCHIVE_FILE}" && clean_exit 1

# create directory
rm -rf ${XMP_RPM_BUILD_DIR}
mkdir -p ${XMP_RPM_BUILD_DIR}/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
test $? -ne 0 && clean_exit 1

# set files
sed -e "/^Vendor:\s*$/d" -e "/^Packager:\s*$/d" -e "/^Group:\s*$/d" -e "/^URL:\s*$/d" "${SPEC_FILE}" > "${XMP_RPM_BUILD_DIR}/SPECS/${SPEC_FILE_NAME}"
test $? -ne 0 && clean_exit 1
rm -f "${ARCHIVE_NAME}.tar.gz"
/bin/sh "${MKARCHIVE_FILE}" "${ARCHIVE_NAME}"
test $? -ne 0 && clean_exit 1
test ! -f "${ARCHIVE_NAME}.tar.gz" && clean_exit 1
mv "${ARCHIVE_NAME}.tar.gz" "${XMP_RPM_BUILD_DIR}/SOURCES/."
test $? -ne 0 && clean_exit 1

# build RPM file
cd ${XMP_RPM_BUILD_DIR}
rpmbuild -v -bb \
--define "_topdir ${XMP_RPM_BUILD_DIR}" \
--define "_specdir ${XMP_RPM_BUILD_DIR}/SPECS" \
--define "_sourcedir ${XMP_RPM_BUILD_DIR}/SOURCES" \
--define "_builddir ${XMP_RPM_BUILD_DIR}/BUILD" \
--define "_srcrpmdir ${XMP_RPM_BUILD_DIR}/SRPMS" \
--define "_rpmdir ${XMP_RPM_BUILD_DIR}/RPMS" \
--define "debug_package %{nil}" \
 ${XMP_RPM_BUILD_DIR}/SPECS/${SPEC_FILE_NAME}
test $? -ne 0 && clean_exit 1
CPU=`uname -m`
case $CPU in
    i*86)
        CPU=i386;;
esac
cp ${XMP_RPM_BUILD_DIR}/RPMS/${CPU}/${XMPPKG_NAME}-${XMPPKG_VERSION}-${XMPPKG_RELEASE}.${CPU}.rpm ${XMP_SRCDIR}/.
test $? -ne 0 && clean_exit 1

if [ -d ${XMP_SRCDIR}/rpm_release ]; then
  rm -r ${XMP_SRCDIR}/rpm_release
fi

mkdir -p ${XMP_SRCDIR}/rpm_release
mv ${XMP_SRCDIR}/${XMPPKG_NAME}-${XMPPKG_VERSION}-${XMPPKG_RELEASE}.${CPU}.rpm ${XMP_SRCDIR}/rpm_release/
rpm --addsign ${XMP_SRCDIR}/rpm_release/${XMPPKG_NAME}-${XMPPKG_VERSION}-${XMPPKG_RELEASE}.${CPU}.rpm
createrepo ${XMP_SRCDIR}/rpm_release/
echo "  $ scp -r rpm_release/* omni@omni-compiler.org:~/public_html/download/package/centos/stable/"

# clean up
rm -rf ${XMP_RPM_BUILD_DIR}
exit 0
