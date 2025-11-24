# CopyAssets.cmake
# Helper function to copy assets directory to build directory

function(copy_assets_post_build TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                ${CMAKE_SOURCE_DIR}/assets
                $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
        COMMENT "Copying assets into build directory"
        VERBATIM
    )
endfunction()
