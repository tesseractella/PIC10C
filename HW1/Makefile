.PHONY: all clean

COMPILER = g++
CFLAGS = -std=c++17 -O3
TARGET = HW1
SRC = compare.cpp HW1.cpp
OBJ = compare.o HW1.o

all: $(TARGET)

#HW1: HW1.o compare.o
#	g++ -std=c++17 -O3 HW1.o compare.o -o HW1

#HW1.o: HW1.cpp
#	g++ -std=c++17 -O3 -c HW1.cpp -o HW1.o

#compare.o: compare.cpp compare.h
#	g++ -std=c++17 -O3 -c compare.cpp -o compare.o

$(TARGET): $(OBJ)
	$(COMPILER) $(CFLAGS) -c $@ $^

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) errorOutput.tex
