#include <omp.h>
#include <iostream>
#include <cstdlib>

int main()
{
	static long nsteps=1000000;
	double step;

	int i; 
	double x;
	double pi;
	double sum = 0.0;
	step = 1.0/(double) nsteps;
	omp_set_num_threads(8);
	#pragma omp parallel for private(x) reduction(+:sum)
	for (i=0;i< nsteps; ++i)
		{
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	pi = step * sum;
	std::cout<<"pi is "<<pi<<"\n";
}
