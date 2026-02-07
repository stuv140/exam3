add_executable(MyCont MyAllocator.cpp)

target_include_directories(MyCont PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS MyCont RUNTIME DESTINATION bin)
