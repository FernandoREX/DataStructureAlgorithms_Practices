#pragma once
#include <iostream>
#include <string>
#include <list>
#include <utility>

class Vertex{
	public:
		enum class Colors { BLACK, GRAY, WHITE };

	private:
		mutable std::string       name;

		mutable std::list<Vertex> neighbors;
		int         distance{ 0 };
		Colors      color{ Colors::BLACK };
		mutable std::string predecesor{ "Nil" };

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
		int         get_distance();
		Colors      get_color();
		std::string get_predecesor();
};
