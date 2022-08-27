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

#include <vector>

#include <algorithm>

class Graph
{
private:
	mutable std::map<std::string, Vertex> vertices;

	size_t dfs_recursive( Vertex* v, size_t time );
	size_t dfs_recursive_to( Vertex* v , size_t time , std::vector<Vertex*>* list );

public:
  enum class Kind { UNDIRECTED, DIRECTED };

	Graph();

	bool add_vertex( Vertex v );

	bool add_edge(std::string from, std::string to, Graph::Kind kindx = Graph::Kind::UNDIRECTED);

	std::map<std::string, Vertex> *get_vertices();

	Vertex* get_vertex( std::string name );

	void print();

	void bfs( std::string name );
	void dfs( std::string start );
	std::vector<Vertex*> dfs_to( Vertex* v );
	void dfs_print( Vertex* start );
};
