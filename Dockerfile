# Use a base image with MinGW-w64 installed, or start from a base Linux image and install MinGW-w64
FROM fedora:latest

# Install MinGW-w64 and other build tools
RUN dnf update -y && \
    dnf install -y mingw64-gcc mingw64-gcc-c++ make cmake autoconf automake libtool && \
    dnf clean all

# Set the WORKDIR to your project directory inside the container
WORKDIR /project

# By default, run a shell. You can override this command when running the container.
CMD ["/bin/bash"]
