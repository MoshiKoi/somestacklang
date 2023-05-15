add_library(TokenIterator token_iterator.cpp)
add_library(Parse parse.cpp)
add_library(Math math.cpp)

add_executable(main main.cpp)
target_link_libraries(main TokenIterator Parse Math)