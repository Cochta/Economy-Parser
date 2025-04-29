@echo off
call emsdk_env.bat
cmake -S . -B build_web ^
  "-DCMAKE_BUILD_TYPE=Release" ^
  "-DBUILD_WEB=ON" ^
  "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:\Users\Coch\Desktop\empscripten\emsdk\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\Informatique\vcpkg\scripts\buildsystems\vcpkg.cmake" ^
  "-DVCPKG_TARGET_TRIPLET=wasm32-emscripten" ^
  -G "Ninja"
cmake --build build_web
pause