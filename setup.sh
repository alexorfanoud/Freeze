#! /bin/bash

FZ_ROOT_PATH=$(pwd)/

echo 'Setting the root path variables...'
if grep -q "#define FZ_ROOT_PATH" $FZ_ROOT_PATH\Freeze/Core.hpp 
then
    echo 'Root path already set.'
else
    echo '#define FZ_ROOT_PATH std::string("'$FZ_ROOT_PATH'")' >> $FZ_ROOT_PATH\Freeze/Core.hpp
fi
echo $'#! /bin/bash \n'$FZ_ROOT_PATH\build/Sandbox/SandboxExec > run.sh && chmod +x run.sh
echo 'Updating submodules...'
git submodule init && git submodule update

echo 'Starting compilation...'
mkdir build
cd build
cmake .. && make
