
add_library(lista2 SHARED lista.c)

install(TARGETS lista2 DESTINATION ${BINARY_DIR})