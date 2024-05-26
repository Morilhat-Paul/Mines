set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCES "*.cpp" "*/*.cpp")

add_executable(Mines ${SOURCES})
target_link_libraries(Mines PRIVATE fmt::fmt)
target_link_libraries(Mines PRIVATE sfml-graphics)
target_include_directories(Mines PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_features(Mines PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET Mines
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
