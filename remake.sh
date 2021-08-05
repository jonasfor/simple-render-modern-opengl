

echo "Installing Shaders test..."
sudo rm -rf build
mkdir build
cd build
echo "cmake -DCMAKE_BUILD_TYPE=Debug  .."
sudo cmake ..
sudo make
echo "Done!"
echo " "
echo "******************************"
