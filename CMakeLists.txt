cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)
project(ClangReflectionTool CXX)


# TODO(v.matushkin): Remove this clang targets added by default


#find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

#message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
#message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")


set(MSVC_COMPILE_OPTIONS
    /MP
    # Don't know what to do with this warnings from llvm/clang headers
    /wd4291
    /wd4624
)


set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)


add_executable(ClangReflectionTool)
target_compile_features(ClangReflectionTool
    PRIVATE
        cxx_std_23
)
target_compile_options(ClangReflectionTool
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_COMPILE_OPTIONS}>
)
target_link_libraries(ClangReflectionTool
    PRIVATE
        clangAST
        clangASTMatchers
        clangBasic
        clangFrontend
        # clangSerialization
        clangTooling
)
target_include_directories(ClangReflectionTool
    PRIVATE
        ${INCLUDE_DIR}
        ${CLANG_INCLUDE_DIRS}
)
target_sources(ClangReflectionTool
    PRIVATE
        ${INCLUDE_DIR}/HeaderTool/CodeWriter.hpp
        ${INCLUDE_DIR}/HeaderTool/Core.hpp
        ${INCLUDE_DIR}/HeaderTool/CppDesc.hpp
        ${INCLUDE_DIR}/HeaderTool/CppWriter.hpp
        ${INCLUDE_DIR}/HeaderTool/EnumEmitter.hpp
        ${INCLUDE_DIR}/HeaderTool/EnumParser.hpp
        ${INCLUDE_DIR}/HeaderTool/MacroAttributes.hpp
        ${INCLUDE_DIR}/HeaderTool/StructEmitter.hpp
        ${INCLUDE_DIR}/HeaderTool/StructParser.hpp
    PRIVATE
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/CodeWriter.cpp
        ${SRC_DIR}/CppWriter.cpp
        ${SRC_DIR}/EnumEmitter.cpp
        ${SRC_DIR}/EnumParser.cpp
        ${SRC_DIR}/MacroAttributes.cpp
        ${SRC_DIR}/StructEmitter.cpp
        ${SRC_DIR}/StructParser.cpp
)


if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ClangReflectionTool)
endif()
