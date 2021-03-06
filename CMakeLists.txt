cmake_minimum_required ( VERSION 2.8.5 )
cmake_policy (SET CMP0048 NEW)
project ( fixpoint )


find_package ( PkgConfig )

pkg_check_modules ( CRYPT REQUIRED libcrypto++ )
# find_package( libcryptopp REQUIRED )
include_directories ( ${CRYPT_INCLUDE_DIRS} )
add_compile_options ( ${CRYPT_CFLAGS_OTHER} )

find_package ( Clang REQUIRED )
include_directories ( SYSTEM ${CLANG_INCLUDE_DIRS} )
set(CLANG_LIBS clangFrontend clangDriver clangSerialization clangParse clangCodeGen clangSema clangAnalysis clangEdit clangAST clangLex clangBasic)

find_package ( LLVM REQUIRED )
include_directories ( SYSTEM ${LLVM_INCLUDE_DIRS} ) 
add_definitions( ${LLVM_DEFINITIONS} )
llvm_map_components_to_libnames( llvm_libs support irreader )

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
  wabt
  GIT_REPOSITORY https://github.com/WebAssembly/wabt
  GIT_TAG        main
  )
set(BUILD_TESTS off)
set(BUILD_LIBWASM off)
FetchContent_MakeAvailable(wabt)

FetchContent_Declare(
  absl
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG        master
  )
FetchContent_MakeAvailable(absl)

include ( etc/build_type.cmake )
include ( etc/cflags.cmake )
include ( etc/clang_format.cmake )

include_directories (SYSTEM "${CMAKE_BINARY_DIR}/_deps/wabt-src")
include_directories (SYSTEM "${CMAKE_BINARY_DIR}/_deps/wabt-build")

include_directories (SYSTEM "${CMAKE_BINARY_DIR}/_deps/absl-src")
include_directories (SYSTEM "${CMAKE_BINARY_DIR}/_deps/absl-build")

include_directories ("${PROJECT_SOURCE_DIR}/src/util")
include_directories ("${PROJECT_SOURCE_DIR}/src/runtime")
include_directories ("${PROJECT_SOURCE_DIR}/src/component")
include_directories ("${PROJECT_SOURCE_DIR}/src/compiler")
include_directories ("${PROJECT_SOURCE_DIR}/src/wasm-rt")
include_directories ("${PROJECT_SOURCE_DIR}/src/storage")

add_subdirectory ("${PROJECT_SOURCE_DIR}/src/util")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/wasm-rt")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/runtime")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/component")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/compiler")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/tester")
