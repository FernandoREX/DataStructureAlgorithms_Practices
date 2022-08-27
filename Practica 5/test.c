#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <string.h>

int h_kof( char* s , int m){
  int l = strlen(s);
  int suma = 0;
  int i = 0;
  for(i = 0; i<l; i++){
    suma = suma + ( * pow(31, l - i - 1));
  }
  return suma;
}

int h_gon( char* s, int m ){
  int l = strlen(s);
  int i = 0;
  for ( i = 0 ; *s; s++) {
    i = 131*i + *s;
  }
  return i%l;
}
/*int probe( int key, int index, int m ){

}
int probe( int key, int index, int m ){

}
int probe( int key, int index, int m ){

}
*/
int main(int argc, char const *argv[]) {
  FILE *ranNames = fopen("random_names.txt", "r");
	char names[100];
	char *str;
  while(fgets(names , 100 , ranNames) != NULL){
    printf("%s\n", names[1]);
  }
  fclose(ranNames);
  return 0;
}
