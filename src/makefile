CC=gcc
CFLAGS=-O3 -Wall -std=c99 -DBUILD_DLL
LDFLAGS=-shared -static-libgcc -s
SOURCES=mymath.c filters.c forward.c integer.c ionogram.c myfiles.c mytime.c seans.c seans2.c seans3.c seans3c3.c seansH.c seansIV.c seansRd.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=albom.dll

all: $(SOURCES) $(TARGET)

clean:
	-rm *.o
	-rm $(TARGET)
	-rm lib$(TARGET).a
	-rm -r bin

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -Wl,--out-implib=lib$(TARGET).a $(LDFLAGS)
	-mkdir bin
	-cp $(TARGET) bin
	-cp lib$(TARGET).a bin
