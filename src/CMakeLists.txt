CPMAddPackage(
  NAME SDL2
  GITHUB_REPOSITORY libsdl-org/SDL
  GIT_TAG release-2.30.0
  OPTIONS
    "SDL_SHARED OFF"
    "SDL_STATIC ON"
    "SDL_TEST OFF"
)

file(GLOB_RECURSE src_list "**.cpp")
add_executable(chip8 ${src_list})
target_include_directories(chip8 PRIVATE ../include)
target_link_libraries(chip8 PRIVATE project_options project_warnings SDL2::SDL2)