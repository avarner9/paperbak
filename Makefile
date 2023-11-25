CXX=i686-w64-mingw32-g++-win32
CXXFLAGS=-Wall -Wextra -O3 -g

CXX_OBJECTS=Main.o Ecc.o Crc16.o Printer.o Decoder.o Fileproc.o Controls.o Scanner.o Service.o fnsplitmerge.o
RES_OBJECTS=PaperBak.o

paperbak.exe : $(CXX_OBJECTS) $(RES_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ /usr/i686-w64-mingw32/lib/libcomdlg32.a /usr/i686-w64-mingw32/lib/libgdi32.a /usr/i686-w64-mingw32/lib/libwinspool.a /usr/i686-w64-mingw32/lib/libcomctl32.a

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

%.o : %.rc
	i686-w64-mingw32-windres -i $< -o $@

%.o : %.res
	i686-w64-mingw32-windres -i $< -o $@
