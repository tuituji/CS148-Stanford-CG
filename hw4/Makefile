CPP = g++
LD = g++
EIGEN_DIR = eigen3.1.1/
CPPFLAGS = -O3 -fPIC -I$(EIGEN_DIR) -DEIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
LDFLAGS = -O3
INCLUDE = -Iinclude/
LIB = -lpng
TARGET = hw4
OBJS = objs/main.o objs/image.o objs/shape.o objs/sphere.o objs/scene.o

default: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIB) -o $(TARGET)
	
objs/main.o: src/main.cpp
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/main.cpp -o objs/main.o

objs/image.o: src/Image.cpp include/Image.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Image.cpp -o objs/image.o

objs/shape.o: src/Shape.cpp include/Shape.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Shape.cpp -o objs/shape.o

objs/sphere.o: src/Sphere.cpp include/Sphere.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Sphere.cpp -o objs/sphere.o

objs/scene.o: src/Scene.cpp include/Scene.h
	$(CPP) -c $(CPPFLAGS) $(INCLUDE) src/Scene.cpp -o objs/scene.o

clean:
	rm $(OBJS) hw4 -f
