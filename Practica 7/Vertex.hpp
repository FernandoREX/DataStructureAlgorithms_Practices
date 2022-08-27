#pragma once

#include <iostream>
// para cin, cout, cerr. (leer del teclado e imprimir en la pantalla)

#include <string>
// para declarar y procesar cadenas

#include <list>
// para los arreglos []

#include <utility>
// para la clase pair

//----------------------------------------------------------------------
//  Class Vertex
//----------------------------------------------------------------------
class Vertex
	{
	public:
		enum class Colors { BLACK, GRAY, WHITE };

	private:
		mutable std::string       name;

		mutable std::list<Vertex> neighbors;

		mutable std::string predecesor{ "Nil" };
		int         distance{ 0 };
		size_t			discovery_time{ 0 };
		size_t			finish_time{ 0 };
		Colors      color{ Colors::BLACK };

	public:
		            Vertex( std::string name );
		std::string get_name();

		void        add_neighbor( Vertex v );
		void        print_neighbors();
		void        print();

		std::list<Vertex>* get_neighbors();

		void        set_distance( int distance );
		void        set_color( Vertex::Colors color );
		void        set_predecesor( std::string predecesor );
		void        set_finish_time( size_t t );
		void        set_discovery_time( size_t t );

		size_t      get_finish_time() const;
		size_t      get_discovery_time() const;
		int         get_distance();
		Colors      get_color();
		std::string get_predecesor();
};
