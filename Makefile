CXX = clang++
CFLAGS = -std=c++11 -c -stdlib=libc++

lib:
	$(CXX) IMTComponent.cpp $(CFLAGS)
