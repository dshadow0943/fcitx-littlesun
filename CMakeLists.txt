cmake_minimum_required(VERSION 3.6)
project(fcitx-littlesun)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Fcitx 4.2.8 REQUIRED)
pkg_check_modules(DBus "dbus-1" REQUIRED IMPORTED_TARGET)

_fcitx_add_uninstall_target()

set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -fvisibility=hidden ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -fvisibility=hidden ${CMAKE_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed ${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--as-needed ${CMAKE_MODULE_LINKER_FLAGS}")

configure_file(config.h.in config.h)

add_subdirectory(po)
add_subdirectory(src)
add_subdirectory(data)

##---------------- 以下为用CPack打包成deb包的内容 ----------------##
# 指定deb包的版本号
set(_VERSION_MAJOR 1)
set(_VERSION_MINOR 0)
set(_VERSION_PATCH 1)
set(CPACK_PACKAGE_VERSION_MAJOR "${_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${_VERSION_PATCH}")
# 指定CPack生成的是deb包（还可以是其他包如 <.7z> <.zip> 等）
set(CPACK_GENERATOR "DEB")
# 指定包名
set(CPACK_PACKAGE_NAME "fcitx-littlesun")
# 指定程序名，就是程序安装后的名字
set(CPACK_DEBIAN_PACKAGE_NAME "fcitx-littlesun")
# 指定运行的计算机架构
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
# 指定所需的依赖
 set(CPACK_DEBIAN_PACKAGE_DEPENDS "libx11-dev, libdbus-1-dev, fcitx-libs-dev")
# 设置包作者的联系方式
set(CPACK_PACKAGE_CONTACT "dshadow@foxmail.com")
# 设置维护人
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "members of dshadow@foxmail.com")
# 指定需要安装的文件
#INSTALL(TARGETS LinkLibraryDemo PrinterInt PrinterChar
#        RUNTIME DESTINATION /tmp/cmake_demo
#        #LIBRARY DESTINATION /tmp/cmake_demo    # 通常，编译器只会在 </usr/lib> 和 </lib> 中找头文件，如果
#        #ARCHIVE DESTINATION /tmp/cmake_demo    # 将库文件放在其他目录，可能会引起找不到库文件错误
#        )

include(CPack)
