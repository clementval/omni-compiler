#%define _topdir ${RPM_BUILD_DIR}

Summary: Omni Compiler Software
Name: omni-compiler
Version: 0.9.1
Release: r20150421
License: LGPLv2
Packager: Hitoshi Murai <h-murai@riken.jp>
Vendor: Riken AICS and University of Tsukuba
URL: http://omni-compiler.org/

Group: Development Languages
Source: %{name}-%{version}.tar.gz

Requires:	openmpi-devel gcc-gfortran java-1.7.0-openjdk

%define default_prefix /usr/local
%define default_conf_prefix /usr/local/etc

%description
Omni OpenMP/XcalableMP/OpenACC Compilers

%prep
%setup

%build
./configure --sysconfdir=%{default_conf_prefix} --prefix=%{default_prefix} MPI_CC=/usr/lib64/openmpi/bin/mpicc MPI_FC=/usr/lib64/openmpi/bin/mpif90
make

%install
rm -rf ${RPM_BUILD_ROOT}
mkdir -p ${RPM_BUILD_ROOT}/%{default_prefix}
mkdir -p ${RPM_BUILD_ROOT}/%{default_conf_prefix}
make sysconfdir=${RPM_BUILD_ROOT}/%{default_conf_prefix} prefix=${RPM_BUILD_ROOT}/%{default_prefix} install

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%{default_prefix}
%{default_conf_prefix}
