#Variables for Exe
set(EXE_SRC main.cpp)
set(EXE_INC "../lib/inc")

add_executable(${EXE} ${EXE_SRC})

target_link_libraries(${EXE} PUBLIC ${LIB_QUEUE})
target_include_directories(${EXE} PUBLIC ${EXE_INC})

if(${ENABLE_WARNINGS})
    target_set_warnings(${EXE}
                        ${ENABLE_WARNINGS}
                        ${ENABLE_WARNINGS_AS_ERRORS})
endif()