find_package(Qt5 COMPONENTS Core DBus REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (
    ${PROJECT_BINARY_DIR}
    ${FCITX4_FCITX_UTILS_INCLUDE_DIRS}
    ${FCITX4_FCITX_CONFIG_INCLUDE_DIRS}
    ${FCITX4_FCITX_INCLUDE_DIRS}
    ${LIBINTL_INCLUDE_DIR}
    )

set( fcitx_libpinyin_sources
    eim.cpp
    config.cpp
    bus.cpp
    keyboardInterface.cpp
    keyboardbus.cpp
    )

add_definitions( -DLOCALEDIR=\"${CMAKE_INSTALL_PREFIX}/share/locale\" )

fcitx_add_addon_full(littlesun DESC
SOURCES ${fcitx_libpinyin_sources}
IM_CONFIG littlesun.conf
LINK_LIBS PkgConfig::DBus ${LIBINTL_LIBRARIES} Qt5::Core Qt5::DBus X11 Xtst
)
