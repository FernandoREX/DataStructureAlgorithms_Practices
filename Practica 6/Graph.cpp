#include "Graph.hpp"

Graph::Graph()
{
	// nada (por el momento)
}


bool Graph::add_vertex( Vertex v )
{
	auto ret = vertices.insert( { v.get_name(), v } );
	// 'map' no permite duplicados, así que no hay necesidad de buscarlos

	return ret.second;
}

bool Graph::add_edge_directed( std::string edge1, std::string edge2 ){
	auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){
		v1->second.add_neighbor( v2->second );
		return true;
	}
	return false;
}

bool Graph::add_edge_weighted( std::string edge1, std::string edge2, int weight ){
	auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){
		std::string w_key = edge1 + edge2;

		v1->second.add_neighbor( v2->second );
		v2->second.add_neighbor( v1->second );

		this->weights.insert( { w_key , weight } );
		return true;
	}
	return false;
}

bool Graph::add_edge( std::string edge1, std::string edge2 )
{
	bool res = false;
	// uno, o ambos nodos, no existen

	auto v1 = this->vertices.find( edge1 );
	auto v2 = this->vertices.find( edge2 );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){

		v1->second.add_neighbor( v2->second );
		v2->second.add_neighbor( v1->second );

		return true;
	}

	return res;
}

void Graph::print()
{
	for( auto v : this->vertices ){
		std::cout << "\n" << v.second.get_name() << ": ";
		v.second.print_neighbors();
	}
	std::cout << "\n\n";
}

std::map<std::string, Vertex>* Graph::get_vertices()
{
	return &(this->vertices);
}

Vertex* Graph::get_vertex( std::string name )
{
	auto v = this->vertices.find( name );
	// .find() devuelve un iterador (apuntador) a la posición donde haya
	// encontrado la coincidencia con la clave 'name'

	return &(v->second);
}

void Graph::bfs_printBack(std::string start){
	Vertex* vertex = get_vertex( start );
	std::string pred_str = vertex->get_predecesor();
	Vertex* prede = get_vertex( pred_str );
	if( prede->get_color() == Vertex::Colors::WHITE){
		std::cout << vertex->get_name() << " " << vertex->get_distance() << " " << prede->get_name() << '\n';
		Graph::bfs_printBack(pred_str);
  }else{
		std::cout << vertex->get_name() << " " << 0 << " Null" << '\n';
	}
}

void Graph::bfs( std::string start ){
	// se crean los nodos
	for (auto v = this->vertices.begin() ; v != this->vertices.end() ; v++) {
		(v->second).set_color( Vertex::Colors::BLACK ); // sin descubir
		(v->second).set_distance( 0 );
		(v->second).set_predecesor("Null");
	}

	get_vertex( start )->set_color( Vertex::Colors::GRAY ); // iniciamos a A
	std::deque<std::string> queue;
	// una 'list' serviría al mismo propósito, pero 'deque' tiene más espíritu de
	// cola que una lista plana. 'deque' es por: double ended queue
	queue.push_back( start );
	// insertamos (encolamos) al vértice de inicio en la parte trasera de la cola
	while( not queue.empty() ){ // mientras tenga elementos
	// el metodo empty ya viene en la clase deque
		std::string next_vertex = queue.front(); // elemento siguiente
	  // obtenemos el NOMBRE asociado al vértice de trabajo ...
		queue.pop_front(); // sale el elem
	  // (desencolar toma dos operaciones: .front() y .pop_front())
		Vertex* vertex = get_vertex( next_vertex ); // creamos un vertice con el obtenido en la cola
	  // obtenemos una REFERENCIA al vértice de trabajo ...
		std::list<Vertex>* v = vertex->get_neighbors(); // obtenemos sus vecinos en una lista
		// obtenemos el original de la LISTA de vértices vecinos ...
		for( auto w = v->begin(); w != v->end(); ++w ){ // recorremos la lista
			Vertex* neighbor = get_vertex( w->get_name() );

			if( neighbor->get_color() == Vertex::Colors::BLACK ){
			// si sigue sin ser descubierto
				neighbor->set_color( Vertex::Colors::GRAY ); // lo ponemos en gris
				// vertice descubierto ...
				neighbor->set_distance( vertex->get_distance() + 1 );
				// establecemos la distancia desde 'start' ...
				neighbor->set_predecesor( vertex->get_name() ); // es v
				// establecemos al predecesor ...
				queue.push_back( neighbor->get_name() );
				// encolamos al vértice recién descubierto
	    }
	  }
		vertex->set_color( Vertex::Colors::WHITE );
		// vértice visitado
	}
}
