rm -rf build
rm -rf LunarLander
rm -rf log.csv
mkdir build
cd build
cmake ..
make


cd ..
cp build/bin/LunarLander .
./LunarLander