# ClangReflectionTool

A playground for an attempt to replace a handwritten c++ parser with Clang AST analyzer  
for my [Hesternal.HeaderTool](https://github.com/Hesternal/Hesternal/tree/master/Hesternal/Source/Tools/Hesternal.HeaderTool) which generates reflection data from .ixx modules.

The parser was a mistake(who could've taught), but it was a necessity since compiler support for modules  
still lacking, to put it lightly. And a couple of weeks ago Clang couldn't even compile my simple  
module interface partition that imported `<type_traits>` and `<concepts>` as a header units.

But right now it looks like writing a small c++ parser for a custom task is simpler than to integrate `LibTooling`.
Especially right now I have no idea on how to build/integrate/distribute it.

## Building clang from source

Since there is no necessary llvm/clang binaries for Windows we need to build it from source.
(probably right now I should do it anyway to get fixes/updates for modules).

My current build setup:
- [llvm-project main branch commit](https://github.com/llvm/llvm-project/tree/6747fc07d1aa94e22622e278e5a02ba70675ac9b) and this [CMakePresets.json](extra/CMakePresets.json)
- latest Visual Studio Preview version (currently it is 17.5.0 Preview 5.0)

```shell
# generate Visual Studio solution for Clang, then build and install it
cmake llvm --preset=visual-studio-msvc

# generate solution for this ClangReflectionTool
cmake . --preset=vs-msvc
```

## Running the tool

``` shell
ClangReflectionTool -p <PATH_TO_COMPILE_COMMANDS_JSON_DIR> <PATH_TO_FILE>
```
It will generate `Generated.cpp` file with `ToString` functions for all enums and a fake serialization `operator<<` for all structs.

If your file includes headers and/or imports modules(mine do) you need to create `compile_commands.json` to get correct AST.  
And of course, if you are using modules you are doomed, since you need to discover module import dependencies.  
There is a way to do that using a preview CMake API and (still not merged?) [Clang patches](https://gitlab.kitware.com/cmake/cmake/-/issues/18355#note_1287272)  
Probably there is also a way to do it with MSVC, but seems like you need to use Clang compiler arguments in compilation database anyway.

I just wrote a simple [compile_commands.json](extra/compile_commands.json) by hand for my `Hesternal` project.

## TODO

- How to add custom "tags"/attributes/markers ?
  - `__attribute__((annotate(“”)))` or `[[clang::annotate("")]]`  
  is useless for me since I don't like this syntax for structs/classes:
  ```cpp
  struct [[clang::annotate("")]] StructName
  {
  };
  ```
  - using macro is also not a simple task, since I'm new to llvm/clang
    - how to connect preprocessor and AST ?
    - how to add `PPCallbacks` using `ClangTool` ? if it's possible at all
  - I can add custom attributes for Clang, but then I could never get rid of building it from source even when modules support will be mature enough.
