all: showdb2.c
	gcc -Wall -Wpointer-arith -Wmissing-prototypes -Wstrict-prototypes -fno-strict-aliasing -fno-strict-overflow -fno-delete-null-pointer-checks -Wempty-body -g3 -o showdb2 showdb2.c -lrpm -lrpmio -lsqlite3 -lgcrypt -lbz2 -lz -llzma -llua -lm -lzstd -lpopt -laudit -ldl -lpthread -Wl,-rpath -Wl,/usr/local/lib

clean: 
	$(RM) showdb2
