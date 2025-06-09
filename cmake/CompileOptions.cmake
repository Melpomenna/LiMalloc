function(__SetCompileOptionsMSVC target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE 
                                    /nologo
                                    /W4
                                    /WX 
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
                                    /WX
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


function(__SetCompileOptionsMacOS target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE
                                    -Wall
                                    -Werror
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
                                    -Werror
                                    -Wextra
                                    -O2
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        endif()
endfunction()


function(__SetCompileOptionsLinux target)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            message(STATUS "Use compile arguments for module name: ${target}, preset:Debug")
            target_compile_options(${target} 
                                    PRIVATE
                                    -W4
                                    -Werror
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
                                    -Werror
                                    -Wextra
                                    -O2
                                    -fno-rtti
                                    -fstack-protector-all
                                )
        endif()
endfunction()

function(SetCompilerOptions target)
    message(STATUS "Use compiler options")

    if(MSVC)
        __SetCompileOptionsMSVC(${target})
    elseif(APPLE)
        __SetCompileOptionsMacOS(${target})
    elseif(LINUX)
        __SetCompileOptionsLinux(${target})
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