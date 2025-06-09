set(target ${CMAKE_MEMORY_LIBRARY_NAME})

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	if (CMAKE_ENABLE_TESTING_LOG_OUT)
		message(STATUS "Enable log for tests")
		add_definitions(-DENABLE_TESTING_LOG_OUT=1)
	endif()
endif()

if (LINUX OR APPLE)
    SET(PRIM_SOURCE details/Unix/prim.c)
else()
    SET(PRIM_SOURCE details/Windows/prim.c)
endif()

add_library(${target} 
    SHARED
    memory.c
    details/memory_impl.c
    details/linked_list.c
    details/os.c
    ${PRIM_SOURCE}
)

include(ClangTidy)
UseClangTidy(${target})
include(CompileOptions)
SetCompilerOptions(${target})
include(CppCheck)
UseCppCheck(${target})