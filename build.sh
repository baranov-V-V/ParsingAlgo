mkdir -p build
cd build
cmake -DCODE_COVERAGE=ON ../
cmake --build . --target ccov -j 8
make -j 8
mv main ../
cd ..