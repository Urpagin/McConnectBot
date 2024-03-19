cmake_minimum_required(VERSION 3.20)
project(McConnectBot)

set(CMAKE_CXX_STANDARD 23)

# Add the executable
add_executable(McConnectBot main.cpp)

# Include Botcraft as a subdirectory
add_subdirectory(external/Botcraft)

# Find required packages
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Specify the directories where the linker should look for libraries
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Link the executable with the required libraries
target_link_libraries(McConnectBot PRIVATE
        ${Boost_LIBRARIES}
        OpenSSL::SSL
        ZLIB::ZLIB
        botcraft  # Dynamically linked
        # Add here other .so libraries if necessary, e.g., libprotocolCraft.so
)

set_target_properties(McConnectBot PROPERTIES
        INSTALL_RPATH "$ORIGIN/libs:/usr/local/lib:/usr/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
)


