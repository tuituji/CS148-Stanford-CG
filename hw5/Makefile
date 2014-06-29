CPP = g++
LD = g++
EIGEN_DIR = eigen3.1.1/
CPPFLAGS = -O3 -fPIC -I$(EIGEN_DIR) -DEIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET 
LDFLAGS = -O3 -lGL -lGLU
INCLUDE = -Iglfw-2.7.6/include
LIB = -lpng -lglut -lglfw -L.
TARGET = hw5
OBJS = objs/main.o

default: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIB) -o $(TARGET)
	
objs/main.o: main.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) main.cpp -o objs/main.o

clean:
	rm $(OBJS) hw5 -f
