// Recuperar datos en linux: ./h.out >> hash_m_13.txt
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>

// es la función de resolución de colisiones
int Linear_Probing(int key, int index, int m)
{
	return index + 1;
}

int Quadratic_Probing(int key, int index, int m)
{
	return (index * index);
}


uint32_t h_Div(uint32_t key, uint32_t m) //uint32_t: entero sin signo
{                                        // int32_t: entero con signo
	return key % m;
}

/*
uint32_t h_Ms(uint32_t key, uint32_t m)
{
	uint32_t n = 2;
	uint32_t res = ( (key * key) % (uint32_t)pow(10, m) ) / (uint32_t)pow(10, 2 * n - m - 1);
	return res;
}*/

int myPow(int n)
{
	int x = 1;

	for (int i = n; i > 0; --i)
		x = 10 * x;

	return x;
}

int H_MS(int key, int size, int digits)
{
	int key_square = key * key;
	// es la clave elevada al cuadrado: 521^2 =271441

	int n = digits;
	// es el número de dígitos máximo de la clave

	int m = 3 * n / 2;
	// es el punto medio. El 3 y el 2 son constantes.

	int x = key_square % myPow(m);
	// es un resultado intermedio

	int mid_square_digits = x / myPow(2 * n - m - 1);

	return mid_square_digits % size;
}

int main()
{

	uint32_t tam = 17;

	//H_DIV
	/*
	for (size_t i = 8; i < 28; i++)
	{
		uint32_t indice = h_Div(i, tam);	//es el indice hash

		fprintf(							//imprimir, pero en archivo 
			stdout,							//es la pantalla
			"i[%ld] = %d \n",				//cadena de siempre
			i, indice);						// variables a imprimir
	}*/

	//H_MS

	for (size_t Cod_Barras = 8; Cod_Barras < 28; Cod_Barras++)
	{
		uint32_t indice = H_MS(Cod_Barras, tam, 2);	//es el indice hash

		fprintf(									//imprimir, pero en archivo 
			stderr,									//es la pantalla
			"i[%ld] = %d \n",						//cadena de siempre
			Cod_Barras, indice);					// variables a imprimir
	}

}
