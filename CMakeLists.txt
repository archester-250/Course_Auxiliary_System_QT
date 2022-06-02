cmake_minimum_required(VERSION 3.5)

project(Course_Auxiliary_System_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(D:/0.CODES/Course_Auxiliary_System/eigen-3.4.0)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Course_Auxiliary_System_QT_zh_CN.ts)

set(Course_Auxiliary_System_QT
  addActivity.ui
  addClock.ui
  seeallActivities.ui
  seeTodayActivities.ui
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  studentlogin.cpp
  studentlogin.h
  studentlogin.ui
  systemchoose.cpp
  systemchoose.h
  systemchoose.ui
  inclass.cpp
  inclass.h
  inclass.ui
  todaycourseinfo.h
  todaycourseinfo.cpp
  todaycourseinfo.ui
  searchcourse.h
  searchcourse.cpp
  searchcourse.ui
  seehomework.h
  seehomework.cpp
  seehomework.ui
  uploadhomework.h
  uploadhomework.cpp
  uploadhomework.ui
  openfile.h
  openfile.cpp
  openfile.ui
  outofclass.h
  outofclass.cpp
  outofclass.ui
  adminlogin.cpp
  adminlogin.h
  adminlogin.ui
  adminmenu.cpp
  adminmenu.h
  adminmenu.ui
  seeallcourses.cpp
  seeallcourses.h
  seeallcourses.ui
  seeallstudents.cpp
  seeallstudents.h
  seeallstudents.ui
  addcourse.cpp
  addcourse.h
  addcourse.ui
  addhomework.cpp
  addhomework.h
  addhomework.ui
  seecoursedoc.cpp
  seecoursedoc.h
  seecoursedoc.ui
  addcoursedoc.h
  addcoursedoc.cpp
  addcoursedoc.ui
  studentregister.h
  studentregister.cpp
  studentregister.ui
  adminregister.cpp
  adminregister.h
  adminregister.ui
  src/activity.cpp
  src/activity.h
  src/admin.cpp
  src/admin.h
  src/ant.cpp
  src/compression.cpp
  src/compression.h
  src/course.cpp
  src/course.h
  src/dij.cpp
  src/hashmap.h
  src/input.cpp
  src/input.h
  src/login.cpp
  src/login.h
  src/MD5.cpp
  src/MD5.h
  src/navigation.cpp
  src/navigation.h
  src/prepocess.cpp
  src/prepocess.h
  src/student.cpp
  src/student.h
  src/thread.h
  src/utils.cpp
  src/utils.h
  src/main.cpp
  ${TS_FILES}
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Course_Auxiliary_System_QT
        MANUAL_FINALIZATION
        ${Course_Auxiliary_System_QT}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Course_Auxiliary_System_QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Course_Auxiliary_System_QT SHARED
            ${Course_Auxiliary_System_QT}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Course_Auxiliary_System_QT
            ${Course_Auxiliary_System_QT}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Course_Auxiliary_System_QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Course_Auxiliary_System_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Course_Auxiliary_System_QT)
endif()
