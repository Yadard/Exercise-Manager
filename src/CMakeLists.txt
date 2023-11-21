set(SOURCE main.c)

IF(WIN32)
    set(SOURCE ${SOURCE} win_loader.c)
ELSE(WIN32)
    set(SOURCE ${SOURCE} linux_loader.c)    
ENDIF(WIN32)

message("SRC: ${SOURCE}")

add_executable(lista ${SOURCE})

install(TARGETS lista DESTINATION ${BINARY_DIR})
