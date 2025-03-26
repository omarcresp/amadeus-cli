function(get_git_version)
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=8 --always
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_TAG
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
        if(GIT_TAG)
            # If we have a git tag like v0.1.2, extract components
            if(GIT_TAG MATCHES "^v?([0-9]+)\\.([0-9]+)\\.([0-9]+).*$")
                set(GIT_VERSION_MAJOR ${CMAKE_MATCH_1} PARENT_SCOPE)
                set(GIT_VERSION_MINOR ${CMAKE_MATCH_2} PARENT_SCOPE)
                set(GIT_VERSION_PATCH ${CMAKE_MATCH_3} PARENT_SCOPE)
                set(GIT_VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}" PARENT_SCOPE)
                set(GIT_VERSION_FOUND TRUE PARENT_SCOPE)
            else()
                # Otherwise, use the raw tag/hash
                set(GIT_VERSION "${GIT_TAG}" PARENT_SCOPE)
                set(GIT_VERSION_FOUND FALSE PARENT_SCOPE)
            endif()
            message(STATUS "Git version: ${GIT_TAG}")
        endif()
    endif()
endfunction() 