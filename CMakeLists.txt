cmake_minimum_required(VERSION 3.11..3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME BxLog)
set(LIBRARY_NAME bxlog)

message(STATUS "${PROJECT_NAME} CMake...")
project(${PROJECT_NAME}
        LANGUAGES CXX
        VERSION 0.1.1
        DESCRIPTION "Small and simple logging library"
        HOMEPAGE_URL "https://www.github.com/BxNiom")

set(LIBRARY_HEADERS include/bxlog/log.hpp
        include/bxlog/log_info.hpp
        include/bxlog/log_level.hpp
        include/bxlog/log_linter.hpp
        include/bxlog/log_wrapper.hpp
        include/bxlog/logger.hpp)


set(LIBRARY_SOURCE src/log.cpp
        src/log_linter.cpp
        )

add_library(${LIBRARY_NAME} STATIC include/bxlog.hpp ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

target_compile_features(${LIBRARY_NAME} INTERFACE cxx_std_14)
set_target_properties(${LIBRARY_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14)


target_include_directories(${LIBRARY_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
        $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
        )

target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

include(GNUInstallDirs)

install(TARGETS ${LIBRARY_NAME}
        CONFIGURATIONS Release
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS ${LIBRARY_NAME}
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${LIBRARY_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bxlog)

install(FILES include/bxlog.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
            )
ENDIF ()