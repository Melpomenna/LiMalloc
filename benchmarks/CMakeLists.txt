set(target Benchmarks)

add_executable(${target} main.benchmarks.cpp)

target_link_libraries(${target} PRIVATE benchmark::benchmark benchmark::benchmark_main)

include(ClangTidy)
UseClangTidy(${target})
include(CompileOptionsTests)
SetCompilerOptionsTest(${target})
include(CppCheck)
UseCppCheck(${target})