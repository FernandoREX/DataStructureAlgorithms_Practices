// Comando para compilar:  gcc -Wall -std=c99 -o pru.out ColaP.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct
{
	int dato;
	int index;
	int ban;

}Cola;

bool insertar( Cola* cola, int frente, int atras, int band, int tam, int dato)
{
	if (frente == atras && band == 1) 
	{ 
		printf("cola llena\n"); 
		return false;
	}
	else {
		cola[atras].dato = dato;
		cola[atras].index = atras;
		cola[atras].ban = 1;
		
		return true;
	}
	return false;
}

int enqueue(Cola* COLA, int TAM_MAX, int DEN, int atras, int frente)
{
	int band = 0;

	for (int i = 0; i < DEN ; i++)
	{
		
		if (insertar(COLA, frente, atras, band, TAM_MAX, i + 54 / 5) == true) // modificar (i + 54 / 5) esos son los datos a ingresar a la cola
		{
			
			atras = (atras + 1) % TAM_MAX;

			
		}

	}

	return atras;
}

int dequeue(Cola* COLA, int atras, int frente, int band, int tam )
{
	if (frente == atras && COLA[frente].ban == 0) 
	{ 
		printf("cola vacia.......\n"); 
	}
	else 
	{
		int dato = COLA[frente].dato;
		//printf("Dato Obtenido: %d \n", dato);
		COLA[frente].ban = 0;
		frente = (frente + 1) % tam;
		return frente;
	}
	return 0;
}

#define TAM_MAX 9

int main()
{
	Cola COLA[TAM_MAX];
	int atras = 0;
	int frente = 0;

	atras = enqueue(COLA, TAM_MAX, 8, atras, frente);

	printf("atras: %d \n", atras);

	frente = dequeue(COLA, atras, frente, COLA[frente].ban, TAM_MAX);
	printf("frente: %d \n", frente);
	frente = dequeue(COLA, atras, frente, COLA[frente].ban, TAM_MAX);
	printf("frente: %d \n", frente);
	frente = dequeue(COLA, atras, frente, COLA[frente].ban, TAM_MAX);
	printf("frente: %d \n", frente);
	frente = dequeue(COLA, atras, frente, COLA[frente].ban, TAM_MAX);
	printf("frente: %d \n", frente);
	printf("atras: %d \n", atras);

	atras = enqueue(COLA, TAM_MAX, 4, atras, frente);
	printf("\natras: %d \n", atras);
	printf("\nfrente: %d \n\n", frente);

	for (int i = 0; i < 9; i++)
	{
		printf("Valor: %d \n", COLA[i].dato);
		printf("indice: %d \n", COLA[i].index);
	}


}