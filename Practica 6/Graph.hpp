#pragma once
#include <iostream>
// para cin, cout, cerr. (leer del teclado e imprimir en la pantalla)
#include <string>
// para declarar y procesar cadenas
#include <list>
// para los arreglos []
#include <map>
// para los diccionarios (tablas hash)
#include "Vertex.hpp"
// la clase Graph _usa_ a la clase Vertex
#include <deque>
// el algoritmo BFS utiliza colas

class Graph{
	private:
		mutable std::map<std::string, Vertex> vertices;
		mutable std::map<std::string, int> weights;
	public:
		Graph();
	//	Graph( std::vector<Vertex> vertices );
		bool add_vertex( Vertex v );
		bool add_edge( std::string edge1, std::string edge2 );
		bool add_edge_directed( std::string edge1, std::string edge2 );
		bool add_edge_weighted( std::string edge1, std::string edge2, int weight );

		std::map<std::string, Vertex> *get_vertices();

		Vertex* get_vertex( std::string name );

		void print();
		void bfs_printBack( std::string start );
		void bfs( std::string start );
};
