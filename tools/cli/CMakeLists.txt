set(CLI_DIR ${CMAKE_CURRENT_LIST_DIR})
set(Sources
        ${Sources}
        ${CLI_DIR}/cli.cc)

add_executable(zcw_cli ${Sources} ${Headers})