cmake_minimum_required(VERSION 3.26)
project(McConnectBot)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set up vcpkg toolchain
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

# Find necessary packages
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

# Include your directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

# Add your executable
add_executable(McConnectBot main.cpp)

# Link libraries
target_link_libraries(McConnectBot PRIVATE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
