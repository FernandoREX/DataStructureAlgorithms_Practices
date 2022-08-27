#include <iostream>
// para cin, cout, cerr. (leer del teclado e imprimir en la pantalla)

#include <string>
// para declarar y procesar cadenas

#include "Vertex.hpp"
#include "Graph.hpp"


int main()
{
	Graph g;

	std::array<std::string, 10> vertices = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
	for( auto& v : vertices ){ g.add_vertex( Vertex( v ) ); }

	std::array<std::string, 12 > edges = {"AB","BF","FG","GC","GJ","JF","FI","IH","HD","DE","EA","EH"};
	for( auto& e : edges ){ g.add_edge( e.substr( 0, 1 ), e.substr( 1, 1 ), Graph::Kind::DIRECTED ); }
	// .substr( a_partir_de_dónde, cuántos_queremos_leer )

	g.print( );
	
	g.dfs( "A" );
	std::cout << "DFS" << '\n';
	g.dfs_print( g.get_vertex("A") );

	g.dfs_to( g.get_vertex("A") );
	std::cout << "DFS TO" << '\n';
	g.dfs_print( g.get_vertex("A") );
}
