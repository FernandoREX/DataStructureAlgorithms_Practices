/*
* Ejemplo completo de [CHAPMAN08, pp 85, fig 4.47]
*/

#include <stdio.h>

#include <time.h>
// para el tiempo

#include <stdlib.h>
// para system()

#include <omp.h>

void print_time( size_t id, char* txt )
{
  time_t raw_time;
  time( &raw_time );

  struct tm* time_info = localtime( &raw_time );
  printf( "Thread %ld %s barrier at %02d:%02d:%02d\n",
  id, txt,
  time_info->tm_hour, time_info->tm_min, time_info->tm_sec );
}


int main()
{
  #pragma omp parallel num_threads( 4 )
  {
    size_t id = omp_get_thread_num();
    if( id < omp_get_num_threads() / 2 ) system( "sleep 3" );
    print_time( id, "before" );

    //#pragma omp barrier // --- barrera explícita (punto de sincronizacion)

    print_time( id, "after" );
  } // --- Implicit barrier
}
