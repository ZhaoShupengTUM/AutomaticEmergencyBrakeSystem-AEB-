# Locate header.
find_path(JSONCPP_INCLUDE_DIR jsoncpp/json/json.h
    HINTS /usr/include)

# Locate library.
find_library(JSONCPP_LIBRARY NAMES jsoncpp
    HINTS /usr/lib/x86_64-linux-gnu /usr/lib /usr/lib64)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSONCPP DEFAULT_MSG JSONCPP_INCLUDE_DIR JSONCPP_LIBRARY)

# Add imported target.
if(JSONCPP_FOUND)
    set(JSONCPP_INCLUDE_DIRS "${JSONCPP_INCLUDE_DIR}")

    if(NOT JSONCPP_FIND_QUIETLY)
        message(STATUS "JSONCPP_INCLUDE_DIRS ........... ${JSONCPP_INCLUDE_DIR}")
        message(STATUS "JSONCPP_LIBRARY ................ ${JSONCPP_LIBRARY}")
    endif()

    if(NOT TARGET jsoncpp::jsoncpp)
        add_library(jsoncpp::jsoncpp UNKNOWN IMPORTED)
        set_target_properties(jsoncpp::jsoncpp PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${JSONCPP_INCLUDE_DIRS}")

        set_property(TARGET jsoncpp::jsoncpp APPEND PROPERTY
            IMPORTED_LOCATION "${JSONCPP_LIBRARY}")
    endif()
endif()