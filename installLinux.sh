#!/bin/bash

install_folder=~/dependencies
mkdir -p $install_folder

# Update package list and install packages
sudo apt-get update
sudo apt-get install -y libgl1-mesa-dev libglx-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libogg-dev libsfml-dev libxrandr-dev libx11-dev libxcursor-dev xvfb cmake

# Print installation summary
echo "Packages installed"
