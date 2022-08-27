
#include "Queue.h"


/**
 * @brief Crea una cola nueva.
 */
Queue* Queue_New()
{
	Queue* p = malloc( sizeof( Queue ) );
	
	if( NULL != p ){
		p->queue = DLL_New();
	}

	return p;
}

/**
 * @brief Destruye una cola existente.
 *
 * @param this Referencia a un objeto Queue
 */
void Queue_Delete( Queue* this )
{
	DLL_Delete( this->queue );
}

/**
 * @brief Inserta un elemento en la cola.
 *
 * @param this Referencia a un objeto Queue.
 * @param value El valor a insertar.
 *
 * @return false si se agotó la memoria y el valor no se pudo insertar. true en
 * caso contrario.
 */
bool Queue_Enqueue( Queue* this, Item value )
{
	return DLL_InsertBack( this->queue, value );
}

/**
 * @brief Extrae un elemento de la cola.
 *
 * @param this Referencia a un objeto Queue.
 * @param value Receptáculo para el valor extraído.
 *
 * @return false si la cola está vacía. true en caso contrario.
 */
bool Queue_Dequeue( Queue* this, Item* value )
{
	return DLL_RemoveFront( this->queue, value );
}

/**
 * @brief 'Observa' al valor en el frente de la cola.
 *
 * @param this Referencia a un objeto Queue.
 * @param value Receptáculo para el valor observado.
 *
 * @return false si la cola está vacía. true en caso contrario.
 */
bool Queue_Peek( Queue* this, Item* value )
{
	return DLL_Peek( this->queue, value );
}

/**
 * @brief Indica si la cola está vacía o no.
 *
 * @param this Referencia a un objeto Queue.
 *
 * @return true si la cola está vacía. false en caso contrario.
 */
bool Queue_IsEmpty( Queue* this )
{
	return DLL_IsEmpty( this->queue );
}

/**
 * @brief Indica el número de elementos actuales en la cola.
 *
 * @param this Referencia a un objeto Queue.
 *
 * @return El número de elementos actualmente en la cola.
 */
size_t Queue_Len( Queue* this )
{
	return DLL_Len( this->queue );
}

/**
 * @brief Vacía la cola, pero no la destruye.
 *
 * @param this Referencia a un objeto Queue.
 */
void Queue_MakeEmpty( Queue* this )
{
	DLL_Purge( this->queue );
}

