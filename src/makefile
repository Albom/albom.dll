CC=gcc
CFLAGS=-O3 -Wall -std=c99 -DBUILD_DLL
LDFLAGS=-shared -static-libgcc -s
SOURCES=mymath.c filters.c forward.c integer.c ionogram.c myfiles.c mytime.c s_old_file.c s_new_file.c seans3.c seans3c3.c h_file.c iv_file.c rd_file.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=albom.dll

all: $(SOURCES) $(TARGET)

clean:
	-rm *.o
	-rm -r bin

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -Wl,--out-implib=lib$(TARGET).a $(LDFLAGS)
	-mkdir bin
	-mv $(TARGET) bin
	-mv lib$(TARGET).a bin
