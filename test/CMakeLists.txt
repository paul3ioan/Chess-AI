set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

#add_executable(${BINARY} ${TEST_SOURCES} Starting_Position.cpp Starting_Position.h)
add_executable(${BINARY} ${TEST_SOURCES} Position2.cpp Position2.h)
#add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest_main)