
.PHONY: install

libctools.so: io.c memory.c
	${CC} $^ ${CFLAGS} -shared -fpic -Wl,-soname,libctools.so -o $@

install:
	mkdir -p ${DESTDIR}/usr/lib
	install libctools.so ${DESTDIR}/usr/lib
	mkdir -p ${DESTDIR}/etc/include/ctools
	install core.h ${DESTDIR}/etc/include/ctools
