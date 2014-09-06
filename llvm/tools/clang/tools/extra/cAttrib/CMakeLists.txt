set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

add_clang_executable(cAttrib
  cAttrib.cpp
  )
target_link_libraries(cAttrib
  clangTooling
  clangBasic
  clangASTMatchers
  )
