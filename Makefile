CXX = clang++
CFLAGS = -std=c++11 -stdlib=libc++

lib:
	$(CXX) MTComponent.cpp -c $(CFLAGS)
