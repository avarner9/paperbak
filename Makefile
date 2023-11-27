CXX=i686-w64-mingw32-g++-win32
CXXFLAGS=-Wall -Wextra -O3 -g

CC=i686-w64-mingw32-gcc-win32
CFLAGS=-Wall -O3 -g

LDFLAGS=-static-libgcc -static-libstdc++

CXX_OBJECTS=Main.o Ecc.o Crc16.o Printer.o Decoder.o Fileproc.o Controls.o Scanner.o Service.o fnsplitmerge.o
RES_OBJECTS=PaperBak.o Options.o Resource.o
C_OBJECTS = dummycrypto.o bzip2/blocksort.o bzip2/huffman.o bzip2/crctable.o bzip2/randtable.o bzip2/compress.o bzip2/decompress.o bzip2/bzlib.o

paperbak.exe : $(CXX_OBJECTS) $(C_OBJECTS) $(RES_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ /usr/i686-w64-mingw32/lib/libcomdlg32.a /usr/i686-w64-mingw32/lib/libgdi32.a /usr/i686-w64-mingw32/lib/libwinspool.a /usr/i686-w64-mingw32/lib/libcomctl32.a

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o : %.rc
	i686-w64-mingw32-windres -i $< -o $@

%.o : %.res
	i686-w64-mingw32-windres -i $< -o $@
