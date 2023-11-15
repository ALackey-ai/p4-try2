add_executable(myprogram main.cpp)

## Link the library to the executable to create the final binary
target_link_libraries(myprogram lab)
add_sanitizers(myprogram)
