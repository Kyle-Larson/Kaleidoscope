cmake -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/Emscripten/emscripten/1.35.0/cmake/Modules/Platform/Emscripten.cmake" -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ./ -H. -Bembuild
cd embuild
emmake make