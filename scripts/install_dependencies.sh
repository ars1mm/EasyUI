#!/bin/bash

# Function to detect Linux distribution
detect_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo $ID
    elif [ -f /etc/lsb-release ]; then
        . /etc/lsb-release
        echo $DISTRIB_ID
    else
        echo "unknown"
    fi
}

# Function to install packages based on distribution
install_packages() {
    local distro=$(detect_distro)
    case "$distro" in
        "ubuntu"|"debian")
            echo "Installing dependencies for Ubuntu/Debian..."
            sudo apt-get update
            sudo apt-get install -y \
                build-essential \
                cmake \
                libx11-dev \
                pkg-config
            ;;
        "fedora")
            echo "Installing dependencies for Fedora..."
            sudo dnf install -y \
                gcc \
                gcc-c++ \
                cmake \
                libX11-devel \
                make \
                pkg-config
            ;;
        "arch"|"manjaro")
            echo "Installing dependencies for Arch Linux..."
            sudo pacman -Sy --noconfirm \
                base-devel \
                cmake \
                libx11 \
                pkg-config
            ;;
        "opensuse"|"suse")
            echo "Installing dependencies for openSUSE..."
            sudo zypper install -y \
                gcc \
                gcc-c++ \
                cmake \
                libX11-devel \
                make \
                pkg-config
            ;;
        *)
            echo "Unsupported distribution. Please install the following packages manually:"
            echo "- C compiler (gcc)"
            echo "- CMake"
            echo "- X11 development files"
            echo "- pkg-config"
            exit 1
            ;;
    esac
}

# Main script
echo "Installing EasyUI dependencies..."
install_packages

if [ $? -eq 0 ]; then
    echo "Dependencies installed successfully!"
    exit 0
else
    echo "Failed to install dependencies."
    exit 1
fi
