REM Boost 설치 스크립트 : 다운로드, 설치 파일 생성, 설치 까지

REM @echo off

SET INSTALL_PATH=D:\01_Workspace\boost
SET BOOST_VERSION=1.82.0

ECHO install directory: %INSTALL_PATH%
ECHO boost version: %BOOST_VERSION%

SET BOOST_PATH=boost_%BOOST_VERSION:.=_%
if not exist %INSTALL_PATH% mkdir %INSTALL_PATH%

pushd .

if not exist .\%BOOST_PATH%.zip powershell -Command "Invoke-WebRequest https://boostorg.jfrog.io/artifactory/main/release/%BOOST_VERSION%/source/%BOOST_PATH%.zip -OutFile %BOOST_PATH%.zip"
if not exist %INSTALL_PATH%\%BOOST_PATH% "tar" -xf .\%BOOST_PATH%.zip -C %INSTALL_PATH%
cd /d "%INSTALL_PATH%\%BOOST_PATH%"
if not exist b2.exe call .\bootstrap.bat

REM Visual Studio 2008 v9.0 : msvc-9.0
REM Visual Studio 2010 v10.0 : msvc-10.0
REM Visual Studio 2012 v11.0 : msvc-11.0
REM Visual Studio 2013 v12.0 : msvc-12.0
REM Visual Studio 2015 v14.0 : msvc-14.0
REM Viusal Studio 2017 v15.0 : msvc-14.1
REM Viusal Studio 2017 v15.3 : msvc-14.11
REM Viusal Studio 2017 v15.5 : msvc-14.12
REM Viusal Studio 2017 v15.6 : msvc-14.13
REM Viusal Studio 2017 v15.7 : msvc-14.14
REM Viusal Studio 2017 v15.8 : msvc-14.15
REM Viusal Studio 2017 v15.9 : msvc-14.16
REM Viusal Studio 2019 v16.0 : msvc-14.2
REM Viusal Studio 2019 v16.1 : msvc-14.21



.\b2 --toolset=msvc-14.2



popd