
CXX= gcc
CXXFLAGS= -O3
LDFLAGS = -lpthread

all: pthreads_ocean

pthreads_ocean: pthreads_ocean.c ocean_main.c
	$(CXX) $(CXXFLAGS) ocean_main.c pthreads_ocean.c -o pthreads_ocean $(LDFLAGS)

clean:
	rm -f pthreads_ocean
