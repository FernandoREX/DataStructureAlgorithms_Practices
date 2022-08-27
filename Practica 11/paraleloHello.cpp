#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>

void hello();

int main(int argc, char const *argv[]){

	if( argc < 2 ){
		printf( "Usage:\n"
			"%s num_threads\n"
			"num_threads is the number of threads\n", argv[0] );
		return 0;
	}

	int thread_count = strtol( argv[1], NULL, 10 );

	#pragma omp parallel num_threads( thread_count )
	{
		hello();
	}

}

void hello()
{
	int my_rank = omp_get_thread_num();

	int thread_count = omp_get_num_threads();

	//printf("Hola desde el nucleo %d de %d\n", my_rank, thread_count);
	std::cout <<" Hola desde el nucleo " << my_rank << " de " << thread_count<<'\n';
}
