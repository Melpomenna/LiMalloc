function(__SetCompileOptionsTestMSVC target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE 
                                    /nologo
                                    /W4
                                    /Z7
                                    /RTC1
                                    /permissive
                                    /sdl
                                    /fsanitize=address 
                                    /analyze
                                    /external:templates-
                                    /analyze:external-
                                    /external:W0
                                    /Od
                                    /MP
                                )
        elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Release")
            target_compile_options(${target} 
                                    PRIVATE
                                    /nologo
                                    /W4
                                    /permissive
                                    /sdl
                                    /O2 
                                    /analyze 
                                    /external:templates-
                                    /analyze:external-
                                    /external:W0
                                    /MP
                                )
        endif()
endfunction()


function(__SetCompileOptionsTestMacOS target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE
                                    -Wall
                                    -Wextra
                                    -g
                                    -O0
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Release")
            target_compile_options(${target} 
                                    PRIVATE
                                    -Wall
                                    -Wextra
                                    -O2
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        endif()
endfunction()


function(__SetCompileOptionsTestLinux target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE
                                    -Wall
                                    -Wextra
                                    -g
                                    -O0
                                    -fsanitize=adress,thread
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Release")
            target_compile_options(${target} 
                                    PRIVATE
                                    -Wall
                                    -Wextra
                                    -O2
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        endif()
endfunction()

function(SetCompilerOptionsTest target)
    message(STATUS "Use compiler options")

    if(MSVC)
        __SetCompileOptionsTestMSVC(${target})
    elseif(APPLE)
        __SetCompileOptionsTestMacOS(${target})
    elseif(LINUX)
        __SetCompileOptionsTestLinux(${target})
    endif()


    get_property(${target}_COMPILE_OPTIONS TARGET ${target} PROPERTY COMPILE_OPTIONS)

    set(TARGET_COMPILE_OPTIONS ${${target}_COMPILE_OPTIONS})

    message(STATUS "Compiler options for ${target} ${TARGET_COMPILE_OPTIONS}")

    set_target_properties(
            ${target}
            PROPERTIES
            CXX_STANDARD ${CMAKE_CXX_STANDARD}
            C_STANDARD ${CMAKE_C_STANDARD}
            CXX_STANDARD_REQUIRED ON
            C_STANDARD_REQUIRED ON
            CXX_EXTENSIONS ON
            C_EXTENSIONS OUTPUT_NAME
            COMPILE_OPTIONS "${TARGET_COMPILE_OPTIONS}"
    )
endfunction()