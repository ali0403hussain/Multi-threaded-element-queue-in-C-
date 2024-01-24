#Variables for Test
set(TEST_SRC Test.cpp)
set(TEST_INC "..src/lib/inc"
             "${googletest_SOURCE_DIR}/include)")

add_executable(${TEST_EXE} ${TEST_SRC})

target_link_libraries(${TEST_EXE} PUBLIC ${LIB_QUEUE} GTest::gtest_main)
target_include_directories(${TEST_EXE} PUBLIC ${TEST_INC})

if(${ENABLE_WARNINGS})
    target_set_warnings(${TEST_EXE}
                        ${ENABLE_WARNINGS}
                        ${ENABLE_WARNINGS_AS_ERRORS})
endif()