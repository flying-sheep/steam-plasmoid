project(plasma-steamplasmoid)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(QT_MIN_VERSION "5.3.0")

find_package(ECM 0.0.11 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)

include(KDECMakeSettings)

include(KDECompilerSettings)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Quick
    QuickWidgets
    DBus
    Widgets
)

set(KF5_MIN_VERSION "5.2.0")

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    Plasma
    PlasmaQuick
    DocTools
    KCMUtils
    KIO
)

###########

message("QML_INSTALL_DIR: ${QML_INSTALL_DIR}") # /usr/lib/qt/qml/
message("PLASMA_DATA_INSTALL_DIR: ${PLASMA_DATA_INSTALL_DIR}")


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/org/kde/plasma/private/steam)


set(steamplugin_SRCS
    plugin/backend.cpp
    plugin/gamesmodel.cpp
    plugin/steamplugin.cpp
    plugin/texttoken.cpp)


add_library(steamplugin SHARED ${steamplugin_SRCS})

add_custom_command(TARGET steamplugin PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/plugin/qmldir $<TARGET_FILE_DIR:steamplugin>)

target_link_libraries(steamplugin
                      Qt5::Core
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Widgets
                      KF5::KIOCore
                      KF5::KIOWidgets)

############

plasma_install_package(org.kde.plasma.steam org.kde.plasma.steam)
install(DIRECTORY ${PROJECT_BINARY_DIR}/org DESTINATION ${QML_INSTALL_DIR})
