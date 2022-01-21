foreach(icon littlesun)
    install(FILES ${icon}.png RENAME fcitx-${icon}.png
            DESTINATION share/icons/hicolor/48x48/status/)
    install(FILES ${icon}.png
            DESTINATION share/fcitx/imicon)
endforeach()

#if (LIBPINYIN_TOOLS_FOUND)

#set(_LIBPINYIN_TABLE art gb_char history nature scitech
#                     culture gbk_char life society economy geology merged
#                     sport)

#foreach(f ${_LIBPINYIN_TABLE})
#    set(_LIBPINYIN_TABLE_FILES ${_LIBPINYIN_TABLE_FILES} "${f}.table")
#    set(_LIBPINYIN_BIN_FILES ${_LIBPINYIN_BIN_FILES} "${f}.bin")
#    set(_LIBPINYIN_GEN_BIN_FILES ${_LIBPINYIN_GEN_BIN_FILES} "${CMAKE_CURRENT_BINARY_DIR}/${f}.bin")
#endforeach()

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/table.conf.in ${CMAKE_CURRENT_BINARY_DIR}/table.conf @ONLY)

#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bigram.db
#              ${_LIBPINYIN_GEN_BIN_FILES}
#              ${CMAKE_CURRENT_BINARY_DIR}/phrase_index.bin
#              ${CMAKE_CURRENT_BINARY_DIR}/pinyin_index.bin
#              ${CMAKE_CURRENT_BINARY_DIR}/addon_phrase_index.bin
#              ${CMAKE_CURRENT_BINARY_DIR}/addon_pinyin_index.bin
#              ${CMAKE_CURRENT_BINARY_DIR}/table.conf
#        DESTINATION ${FCITX_LIBPINYIN_ZHUYIN_DATADIR})

#endif()
