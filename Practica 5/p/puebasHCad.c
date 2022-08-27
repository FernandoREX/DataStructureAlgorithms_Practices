// Recuperar datos en linux: ./h.out >> hash_m_13.txt
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

// es la función de resolución de colisiones
int Linear_Probing(char* key, int index, int m)
{
	return index + 1;
}

int Quadratic_Probing(char* key, int index, int m) 
{
	return (index * index);
}


uint32_t h_simple(char* key, uint32_t m)
{
	int i;
	for (i = 0; *key; key++) {
		i = 131 * i + (*key);
	}
	return i % m;
}

uint32_t h_kof(char* s, uint32_t len) {
	int sum = 0;
	for (size_t i = 0; i < strlen(s); i++) {
		sum = sum + (*s * pow(31, strlen(s) - i - 1));
	}
	return sum % len;
}


int main()
{
	uint32_t tam = 11;
	char nombres[10][32] =
	{
		"Flor Burnley",
		"Carma Vuong",
		"Lynsey Zaragosa",
		"Hilaria Laury",
		"Stephane Mcnamara",
		"Madelaine Gaulke",
		"Ernestina Varghese",
		"Melodie Purtee",
		"Vinnie Roepke",
		"Gay Sadler"
	};

	for (size_t i = 0; i < 10; i++)
	{
		uint32_t indice = h_kof(nombres[i], tam);

		fprintf(									//imprimir, pero en archivo 
			stderr,									//es la pantalla
			"i[%ld] = %d \n",						//cadena de siempre
			i, indice);								// variables a imprimir
		printf("Nombre: %s \n", nombres[i]);

	}

}
