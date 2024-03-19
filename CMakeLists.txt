cmake_minimum_required(VERSION 3.20)
project(McConnectBot)

set(CMAKE_CXX_STANDARD 23)

add_executable(McConnectBot main.cpp)
add_subdirectory(external/Botcraft)

# Find packages
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Link libraries statically (except OpenSSL)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)

target_link_libraries(McConnectBot PRIVATE
        ${Boost_LIBRARIES}
        # Removed paths to static OpenSSL libraries
        botcraft
)

# Set output directory to place the binary
set_target_properties(McConnectBot PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
