int main(){
	FILE *ranNames;
	ranNames = fopen("random_names.txt", "r");
	char names[80];
	char *str;

	Map* mapa = Create( TAM_TABLE );
  if( mapa == NULL ){
    printf( "Error creando la tabla hash.\n" );
    exit( 1 );
  }

	int i = 0;
	while( fgets( names, 80, ranNames ) != NULL ){
	 	if(Insert(mapa , *str)){
			++i;
			printf("\nFactor de carga = %0.2f para el valor %s\n", LoadFactor(mapa) , names);
		}
 	}

	for(i = 0; i < 50; i++){
		if(Search(mapa , names) == names){
			printf("si se encontro la llave: %s\n", names);
		}else{
			printf("No se encontro la llave: %s\n", names);
		}
	}

	printf("El numero de colisiones para la busqueda fue: %d\n", g_bColisiones);

	printf("\nnumero de colisiones al insertar: %d\n", g_colisiones);


#if 0
  assert( Insert( mapa, 123 ) == true );
  assert( Insert( mapa, 170 ) == true );
  assert( Insert( mapa, 340 ) == true );
  assert( Insert( mapa, 510 ) == true );
  assert( Insert( mapa, 510 ) == false ); // duplicado

  assert( Search( mapa, 123 ) == 123 ); // sí está

  assert( Search( mapa, 100 ) == -1 ); // no está

  assert( Remove( mapa, 123 ) == true ); // no está implementada, va a fallar
#endif


  Destroy( mapa );
  mapa = NULL;
	fclose(ranNames);
	return 0 ;
}
