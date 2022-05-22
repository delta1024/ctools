CC = gcc
CFLAGS = -shared -fpic
SRC_DIR = CtoolsLib
LIB_INSTALL_LOCATION = /usr/lib/ctools
HEADER_INSTALL_LOCATION = /usr/include/ctools
LD_CONF_LOCATION = /etc/ld.so.conf.d/ctools.conf
TARGET = target/debug

define MY_LIB_SRC
io.c
memory.c
endef

MY_LIB_SRC := $(addprefix ${SRC_DIR}/,$(MY_LIB_SRC))

.PHONY: install uninstall clean #all 

#all:  | ${TARGET}

${TARGET}/libctools.so: ${MY_LIB_SRC} | ${TARGET}
	${CC} $^ ${CFLAGS} -I${SRC_DIR} -o $@

${TARGET}:
	mkdir -p $@

install:
	mkdir -p ${LIB_INSTALL_LOCATION}
	mkdir -p ${HEADER_INSTALL_LOCATION}
	install ${TARGET}/libctools.so ${LIB_INSTALL_LOCATION}
	install ${SRC_DIR}/core.h ${HEADER_INSTALL_LOCATION}
	printf "${LIB_INSTALL_LOCATION}\n" > ${LD_CONF_LOCATION}
	ldconfig

uninstall:
	rm -rf ${LIB_INSTALL_LOCATION}
	rm ${LD_CONF_LOCATION}
	rm -rf ${HEADER_INSTALL_LOCATION}
	ldconfig
clean:
	rm -rf target
