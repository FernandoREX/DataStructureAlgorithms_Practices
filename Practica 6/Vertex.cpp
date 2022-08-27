
#include "Vertex.hpp"

Vertex::Vertex( std::string _name ) : name{ _name }
{
	// nada (por el momento)
}

void Vertex::add_neighbor( Vertex v )
{
	this->neighbors.push_back( v );
}

std::list<Vertex>* Vertex::get_neighbors()
{
	return &(this->neighbors);
}

std::string Vertex::get_name()
{
	return this->name;
}

void Vertex::print_neighbors()
{
	for( auto v : this->neighbors )
		std::cout << v.get_name() << "-> ";
	std::cout << "Null";
}

void Vertex::set_distance( int distance ) // in lab
{
	this->distance = distance;
}

void Vertex::set_color( Vertex::Colors color ) // in lab
{
	this->color = color;
}

void Vertex::set_predecesor( std::string predecesor ) // in lab
{
	this->predecesor = predecesor;
}

int Vertex::get_distance() // in lab
{
	return this->distance;
}

Vertex::Colors Vertex::get_color() // in lab
{
	return this->color;
}

std::string Vertex::get_predecesor() // in lab
{
	return this->predecesor;
}

void Vertex::print()
{
	std::string color_as_string;

	switch( this->color ){
		case Vertex::Colors::BLACK: color_as_string = "BLACK"; break;
		case Vertex::Colors::GRAY: color_as_string = "GRAY"; break;
		case Vertex::Colors::WHITE: color_as_string = "WHITE"; break;
	}
  std::cout << ".n: " << this->name << ", ";
  std::cout << ".d: " << this->distance << ", ";
  std::cout << ".c: " << color_as_string << ", ";
  std::cout << ".p: " << this->predecesor << std::endl;
}
