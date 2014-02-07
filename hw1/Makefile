
CXX= gcc
CXXFLAGS= -O3 -std=c99
LDFLAGS =  

all: serial_ocean omp_ocean_dyn omp_ocean_stat

serial_ocean: serial_ocean.c ocean_main.c
	$(CXX) $(CXXFLAGS) ocean_main.c serial_ocean.c -o serial_ocean $(LDFLAGS)

omp_ocean_dyn: omp_ocean_dyn.c ocean_main.c
	$(CXX) $(CXXFLAGS) -fopenmp ocean_main.c omp_ocean_dyn.c -o omp_ocean_dyn $(LDFLAGS)

omp_ocean_stat: omp_ocean_stat.c ocean_main.c
	$(CXX) $(CXXFLAGS) -fopenmp ocean_main.c omp_ocean_stat.c -o omp_ocean_stat $(LDFLAGS)

clean:
	rm -f serial_ocean
	rm -f omp_ocean_dyn
	rm -f omp_ocean_stat
