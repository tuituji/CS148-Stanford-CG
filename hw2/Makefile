CPP = g++
LD = g++
CPPFLAGS = -O3 -fPIC
LDFLAGS = -O3 -lGL -lGLU
LIB = -lglut
TARGET = hw2
OBJS = main.o

default: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIB) -o $(TARGET)
	
main.o: main.cpp
	$(CPP) -c $(CPPFLAGS) main.cpp

clean:
	rm main.o hw2 -f
