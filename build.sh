mkdir -p build
cd build

if [ $1 == "Makefile" ]; then
    echo "Using makefile"

    cmake ..
    make
else
    echo "Using Ninja"

    cmake .. -G "Ninja"
    ninja
fi