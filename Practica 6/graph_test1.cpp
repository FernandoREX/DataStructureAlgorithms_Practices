#include <iostream>
// para cin, cout, cerr. (leer del teclado e imprimir en la pantalla)
#include <string>
// para declarar y procesar cadenas
#include "Vertex.hpp"
#include "Graph.hpp"

using namespace std;

int main(){
	//array<string, 11>vertices={"A","B","C","D","E","F","G","H","I","J","K"};
	array<string, 11> vertices={"K","J","I","H","G","F","E","D","C","B","A"};

	array<string, 11> edges={"AE","AB","BC","BF","DH","EI","FG","FI","GJ","GK","HK"};

	Graph g;

	for( auto& v : vertices ){
		g.add_vertex( Vertex( v ) );  // se añaden los vertices al grafo
	}

	for( auto& e : edges ){ // el auto& indica que el tipo a usar debe identificarlo el compilador (solo c++11)
		g.add_edge( e.substr( 0, 1 ), e.substr( 1, 1 ) );
		// .substr( a_partir_de_dónde, cuántos_queremos_leer )
	}
	g.print(); // imprimimos

	g.bfs( "F" );
	g.bfs_printBack( "D" );
}
