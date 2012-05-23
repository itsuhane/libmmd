TARGET = core-clang-bare-test.o
SOURCE = main.cc
CXX = clang++
CPP_FLAGS = -I../../include
CXX_FLAGS = -std=c++11 -pedantic -Wall
test : build clean
build : $(TARGET)
clean :
	-rm $(TARGET)
$(TARGET) : $(SOURCE)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -o $(TARGET) -c $(SOURCE)
.PHONY : build clean test
.DEFAULT: test
