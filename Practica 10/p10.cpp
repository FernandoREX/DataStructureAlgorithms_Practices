#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

struct Alumno{
  char nombre[32];
  int semestre;
  float promedio;
  void print(){
    std::cout << this->nombre << " * " << this->semestre << " * " << this->promedio;
    std::cout << " " << '\n';
  }
};

struct Grupo{
  char profesor[32];
  int grupo;
  char semestre[32];
  int anio;
  bool finalizado;
  float promedioGrupo;
  std::vector<Alumno> alumnos;
};

void serialize_xml(std::string base_name, std::vector<Alumno>& group){
  FILE* hand = fopen( (base_name + ".xml").c_str() , "w");
  fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" , hand);
  fputs( "  <grupo03>\n" , hand);
  for ( auto al : group ) {
    fputs("    <alumno>\n" , hand);
    fputs("      <nombre>", hand);
    fputs(al.nombre, hand);
    fputs("</nombre>\n", hand);
    fputs("      <semestre>", hand);
    fprintf(hand , "%d", al.semestre);
    fputs("</semestre>\n", hand);
    fputs("      <promedio>", hand);
    fprintf(hand, "%0.2f", al.promedio);
    fputs("</promedio>\n", hand);
    fputs("    </alumno>\n", hand);
  }
  fputs( "  </grupo03>" , hand);
  fclose( hand );
}

void serialize_csv(std::string base_name, std::vector<Alumno>& group){
  FILE* hand = fopen( (base_name + ".csv").c_str() , "w");
  for(auto a: group)
    fprintf(hand, "%s, %d, %0.2f\n", a.nombre, a.semestre, a.promedio);
  fclose( hand );
}

void serialize_yaml( Grupo& g, std::string base_name ){
  base_name += ".yaml";
  FILE* hand = fopen( base_name.c_str() , "w");

  fprintf(hand, "---\nprofesor: \"%s\"\ngrupo: %d\nsemestre: \"%s\"\nanio: %d\nfinalizado: %s\nalumnos: ", g.profesor, g.grupo, g.semestre,g.anio, g.finalizado ? "Yes" : "No");

  for( auto al : g.alumnos )
    fprintf(hand, "\n  - nombre: \"%s\"\n    semestre: %d\n    promedio: %0.2f\n", al.nombre, al.semestre , al.promedio);

  fprintf( hand, "\npromedioGrupo: %0.2f\n...", g.promedioGrupo);

  fclose( hand );
}

void serialize_json( Grupo& g, std::string base_name ){
  base_name += ".json";
  FILE* hand = fopen( base_name.c_str() , "w");

  fprintf(hand, "{\n\"profesor\" : \"%s\",\n\"grupo\" : %d,\n\"semestre\" : \"%s\",\n\"anio\" : %d,\n\"finalizado\" : %s,\n\"alumnos\" : [", g.profesor, g.grupo, g.semestre,g.anio, g.finalizado ? "true" : "false");

  size_t i = g.alumnos.size();

  for( auto al : g.alumnos ){
    --i;
    if (i>0)
      fprintf(hand, "\n{\n\t\"nombre\" : \"%s\",\n\t\"semestre\" : %d,\n\t\"promedio\" : %0.2f\n},", al.nombre, al.semestre , al.promedio);
    else
      fprintf(hand, "\n{\n\t\"nombre\" : \"%s\",\n\t\"semestre\" : %d,\n\t\"promedio\" : %0.2f\n}", al.nombre, al.semestre , al.promedio);
  }

  fprintf( hand, "\n],\n\"promedioGrupo\" : %0.2f\n}", g.promedioGrupo);

  fclose( hand );
}

void serialize_bin(std::string name, std::vector<Alumno>& al){
  name += ".bin";
  FILE* binHand = fopen( name.c_str() , "wb" );

  fwrite( &al, sizeof( Alumno ), al.size() , binHand );

  fclose( binHand );
}

void read_bin(std::string name){
  name += ".bin";
  FILE* binHand = fopen( name.c_str() , "rb" );

  if (binHand == NULL) {
    fclose( binHand );
    return;
  }

  std::vector<Alumno> alumno;
  fread( &alumno, sizeof(Alumno), 1, binHand);

  for(auto a : alumno){
    a.print();
  }

  fclose( binHand );
}

void read_csv(std::string baseFile){
  baseFile += ".csv";

  FILE* file_in = fopen( baseFile.c_str() , "r" );

  if (file_in == NULL) {
    fclose(file_in);
    return;
  }

  char nombre[80];
  int semestre;
  float promedio;

  for (size_t i = 0; i < 3; i++) {
    fscanf( file_in, "%79[^,],%d,%f\n", nombre, &semestre, &promedio );
    std::cout << nombre << ',' << semestre << ',' << promedio << '\n';
  }

  fclose(file_in);
}

void read_yaml(std::string baseFile){
  baseFile += ".yaml";
  FILE* file_in = fopen( baseFile.c_str() , "r" );

  if (file_in == NULL) {
    fclose(file_in);
    return;
  }

  char input[80];
  while (!feof( file_in )) {
    fgets(input, 80, file_in);
    printf("%s", input);
  }
  std::cout << '\n';

  fclose( file_in );
}

void read_json(){

}

void read_xml(std::string baseFile){
  baseFile += ".xml";
  FILE* file_in = fopen( baseFile.c_str() , "r" );

  if (file_in == NULL) {
    fclose(file_in);
    return;
  }

  char input[80];
  while (!feof( file_in )) {
    fgets(input, 80, file_in);
    printf("%s", input);
  }
  std::cout << '\n';

  fclose( file_in );
}

int main(int argc, char const *argv[]){

  if (argc < 1) {
    std::cout << "No se ha dado un nombre para los archivos" << '\n';
    return 0;
  }

  std::string nombre_base = argv[ 1 ];

  std::vector<Alumno> alumnos;

  Grupo grupo03( Grupo{"Fco" , 3, "2021-1" , 2020 , false , 0.0});


  alumnos.push_back( Alumno{"Bart", 4 , 6.0} );
  alumnos.push_back( Alumno{"Lisa", 4 , 6.0} );
  alumnos.push_back( Alumno{"Milhouse", 4 , 6.0} );

  grupo03.alumnos.push_back( alumnos[0] );
  grupo03.alumnos.push_back( alumnos[1] );
  grupo03.alumnos.push_back( alumnos[2] );

  // serialize_xml(nombre_base, alumnos);
  // serialize_json(grupo03, nombre_base);
  // serialize_csv(nombre_base, alumnos);
  // serialize_yaml(grupo03, nombre_base);
  serialize_bin(nombre_base, alumnos);

  // read_xml(nombre_base);
  read_bin(nombre_base);
  // read_csv(nombre_base);
  // read_json(nombre_base);
  // read_yaml(nombre_base);

  return 0;
}
