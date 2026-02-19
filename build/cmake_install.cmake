# Install script for directory: /home/ji/MOBJ/tme45/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/ji/MOBJ/tme45/build/tme810")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme810")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/ji/MOBJ/tme45/build/CMakeFiles/tme810.dir/install-cxx-module-bmi-noconfig.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/ji/MOBJ/tme45/src/Indentation.h"
    "/home/ji/MOBJ/tme45/src/XmlUtil.h"
    "/home/ji/MOBJ/tme45/src/Point.h"
    "/home/ji/MOBJ/tme45/src/Box.h"
    "/home/ji/MOBJ/tme45/src/Term.h"
    "/home/ji/MOBJ/tme45/src/Net.h"
    "/home/ji/MOBJ/tme45/src/Instance.h"
    "/home/ji/MOBJ/tme45/src/Node.h"
    "/home/ji/MOBJ/tme45/src/Line.h"
    "/home/ji/MOBJ/tme45/src/Shape.h"
    "/home/ji/MOBJ/tme45/src/Symbol.h"
    "/home/ji/MOBJ/tme45/src/Cell.h"
    "/home/ji/MOBJ/tme45/src/TermShape.h"
    "/home/ji/MOBJ/tme45/src/BoxShape.h"
    "/home/ji/MOBJ/tme45/src/LineShape.h"
    "/home/ji/MOBJ/tme45/src/SaveCellDialog.h"
    "/home/ji/MOBJ/tme45/src/OpenCellDialog.h"
    "/home/ji/MOBJ/tme45/src/CellViewer.h"
    "/home/ji/MOBJ/tme45/src/CellsModel.h"
    "/home/ji/MOBJ/tme45/src/InstancesModel.h"
    "/home/ji/MOBJ/tme45/src/CellsLib.h"
    "/home/ji/MOBJ/tme45/src/InstancesWidget.h"
    "/home/ji/MOBJ/tme45/src/CellWidget.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ji/MOBJ/tme45/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
