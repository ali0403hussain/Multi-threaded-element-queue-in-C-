cmake_minimum_required(VERSION 3.22)

#Project Parameters- define
set(PROJECT_NAME "QueueExercise")
set(PROJECT_VERSION 1.0.0)

#Project Parameters Config
project(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX
)

#Project CMake Config
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_CXX_EXTENSIONS          OFF)
set(CMAKE_BUILD_TYPE              Debug)

#Project Files Varibale
set(EXE ${PROJECT_NAME})
set(LIB_QUEUE "LibraryQueue")

#%%%%%%%%%%%%%%%%% Enable CMake Features %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#Defining Path for cmake features
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

#Enable warnings and treat warnings as error
option(ENABLE_WARNINGS "Enable Warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable Warnings as Errors" ON)

#Enable Sanitizers
option(ENABLE_SANITIZE_ADDR "Enable Sanitizer address" ON)
option(ENABLE_SANITIZE_UNDEF "Enable Sanitizer Undefined" ON)

#Enable Fetch content
option(ENABLE_FETCH "Enable Fetch Content" ON)

#Enable Unit Test
option(ENABLE_UNIT_TEST "Enable Unit Testing" ON)

#%%%%%%%%%%%%%%%%% Enable CMake Features Ends %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if(${ENABLE_WARNINGS})
    include(warnings)
    message(STATUS "Warnings Enabled for:${CMAKE_CXX_COMPILER_ID}")
endif()

if((${NABLE_SANITIZE_ADDR}) OR (${ENABLE_SANITIZE_UNDEF}))
    include(Sanitizers)
    add_sanitizers_flags()
endif()

if(${ENABLE_FETCH})
    include(FetchContent)
    include(addlibUseFetch)
    message(STATUS "Fetch Content available:")

    add_fetch_ext_lib(
        googletest
        https://github.com/google/googletest
        v1.14.0
        "${PROJECT_SOURCE_DIR}/external/googletest"
        TRUE
    )
endif()

if(${ENABLE_UNIT_TEST})
    set(TEST_EXE    "UnitTest")
    add_subdirectory(test)
endif()

add_subdirectory(src)