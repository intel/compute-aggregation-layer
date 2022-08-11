# spec file for package compute-aggregation-layer

#it's changed by external script
%global rel 1
%global ver xxx

%if !0%{?build_type:1}
%define build_type  Release
%endif

%define _source_payload w5T16.xzdio
%define _binary_payload w5T16.xzdio

Name:           compute-aggregation-layer
Epoch:          1
Version:        %{ver}
Release:        %{rel}%{?dist}
Summary:        Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications
License:        MIT
Group:          System Environment/Libraries
Url:            https://github.com/intel/compute-aggregation-layer
Source0:        %{url}/archive/%{version}/compute-aggregation-layer-%{version}.tar.xz
Source1:        copyright

ExclusiveArch:  x86_64
BuildRequires:  cmake make gcc-c++

%description
Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications.

%debug_package

%prep
%autosetup -p1 -n compute-aggregation-layer-%{version}

%build
%cmake .. \
   -DCMAKE_BUILD_TYPE=%{build_type} \
   -Wno-dev
%make_build

%install
cd build
%make_install

#insert license into package
mkdir -p %{buildroot}/usr/share/doc/compute-aggregation-layer%{?name_suffix}/
cp -pR %{_sourcedir}/copyright %{buildroot}/usr/share/doc/compute-aggregation-layer%{?name_suffix}/.

%files
%defattr(-,root,root)
%{_bindir}/calrun
%{_libdir}/libcal.so
/usr/share/doc/compute-aggregation-layer/copyright
/opt/compute-aggregation-layer/cal.icd
/opt/compute-aggregation-layer/cal_setvars.sh
/opt/compute-aggregation-layer/cal_setvars_l0.sh
/opt/compute-aggregation-layer/cal_setvars_ocl.sh

%changelog
* Mon Sep 13 2021 Compute-Runtime-Automation <compute-runtime@intel.com>
- Initial spec file for SLES 15.3
