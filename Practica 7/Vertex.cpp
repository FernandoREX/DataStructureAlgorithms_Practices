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
	std::cout << "Nil";
}

void Vertex::set_distance( int distance )
{
	this->distance = distance;
}

void Vertex::set_color( Vertex::Colors color )
{
	this->color = color;
}

void Vertex::set_predecesor( std::string predecesor )
{
	this->predecesor = predecesor;
}
/************************Mi Codigo**************************/
void Vertex::set_finish_time( size_t time ){
	this->finish_time = time;
}
void Vertex::set_discovery_time( size_t time ){
	this->discovery_time = time;
}

size_t Vertex::get_finish_time( ) const {
	return this->finish_time;
}
size_t Vertex::get_discovery_time( ) const {
	return this->discovery_time;
}
/***********************************************************/
int Vertex::get_distance()
{
	return this->distance;
}

Vertex::Colors Vertex::get_color()
{
	return this->color;
}

std::string Vertex::get_predecesor()
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

#if 0
	std::cout << "    Nombre: " << this->name << std::endl;
	std::cout << " Distancia: " << this->distance << std::endl;
	std::cout << "     Color: " << color_as_string << std::endl;
	std::cout << "Predecesor: " << this->predecesor << std::endl;
#endif
   std::cout << ".n: " << this->name << ", ";
   std::cout << ".d: " << this->distance << ", ";
   std::cout << ".c: " << color_as_string << ", ";
   std::cout << ".p: " << this->predecesor << std::endl;
}
