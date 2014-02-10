
CXX= mpicc
CXXFLAGS= -O3 -std=c99 
LDFLAGS =  

all: mpi_ocean

mpi_ocean: mpi_ocean.c ocean_main.c
	$(CXX) $(CXXFLAGS) ocean_main.c mpi_ocean.c -o mpi_ocean $(LDFLAGS)

clean:
	rm -f mpi_ocean
