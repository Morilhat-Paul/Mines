include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 2.6.x
  GIT_SHALLOW TRUE
)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
  GIT_TAG master
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(fmt)
add_subdirectory(sfml)
