@echo off
call emsdk_env.bat
cmake -S . -B build_web ^
  -G Ninja ^
  "-DCMAKE_BUILD_TYPE=Release" ^
  "-DBUILD_WEB=ON" ^
  "-DCMAKE_SIZEOF_VOID_P=4" ^
  "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:\Informatique\emsdk\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\Informatique\vcpkg\scripts\buildsystems\vcpkg.cmake" ^
  "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten"
cmake --build build_web
pause