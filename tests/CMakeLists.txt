set(target Tests)

if (LINUX OR APPLE)
    SET(OS_DEPENDS_TESTS unix.tests.cpp)
else()
    SET(OS_DEPENDS_TESTS windows.tests.cpp)
endif()

add_executable(${target} 
        main.tests.cpp
        linked_list.tests.cpp
        ${OS_DEPENDS_TESTS})

target_link_libraries(${target} PRIVATE
	GTest::gtest_main
	${CMAKE_MEMORY_LIBRARY_NAME}
)

include(ClangTidy)
UseClangTidy(${target})
include(CompileOptionsTests)
SetCompilerOptionsTest(${target})
include(CppCheck)
UseCppCheck(${target})

include(GoogleTest)
gtest_discover_tests(${target})