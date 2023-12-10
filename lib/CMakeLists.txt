file(GLOB DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/*")

# get all folder and add them as subdirectory
foreach(DIR ${DIRECTORIES})
    if(IS_DIRECTORY ${DIR})
        get_filename_component(HEAD "${DIR}" NAME)
        message("Head of path for ${DIR}: ${HEAD}")
        add_subdirectory(${HEAD})
    endif()
endforeach()

