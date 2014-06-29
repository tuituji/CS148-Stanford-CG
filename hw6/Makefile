CPP = g++
LD = g++
EIGEN_DIR = eigen3.1.1/
CPPFLAGS = -O3 -fPIC -Iinclude/ -I$(EIGEN_DIR) -DEIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET 
LDFLAGS = -O3 -lpng
INCLUDE = -DNO_FREETYPE
LIB = -lpng
TARGET = hw6
OBJS = objs/main.o objs/pngwriter.o objs/image.o

default: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIB) -o $(TARGET)
	
objs/main.o: src/main.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/main.cpp -o objs/main.o

objs/pngwriter.o: src/pngwriter.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/pngwriter.cpp -o objs/pngwriter.o

objs/image.o:  src/image.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/image.cpp -o objs/image.o

clean:
	rm $(OBJS) hw6 -f

