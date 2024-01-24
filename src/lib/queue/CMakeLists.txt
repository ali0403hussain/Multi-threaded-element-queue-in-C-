#Variables for Lib
set(LIB_QUEUE_SRC Queue.cpp)
set(LIB_QUEUE_INC_PATH "../inc")

add_library(${LIB_QUEUE} STATIC ${LIB_QUEUE_SRC})
target_include_directories(${LIB_QUEUE} PUBLIC ${LIB_QUEUE_INC_PATH})