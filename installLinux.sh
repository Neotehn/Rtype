#!/bin/bash

install_folder=~/dependencies
mkdir -p $install_folder

# Update package list and install packages
sudo apt-get update
sudo apt-get install -y libgl1-mesa-dev libglx-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libogg-dev libsfml-dev libxrandr-dev libx11-dev libxcursor-dev xvfb cmake

# Move installed packages to the created folder
sudo cp /usr/include/SFML $install_folder/
sudo cp /usr/lib/x86_64-linux-gnu/ $install_folder/
sudo cp /usr/share/SFML $install_folder/

# Print installation summary
echo "Packages installed to: $install_folder"
