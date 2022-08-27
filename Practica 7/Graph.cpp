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

bool Graph::add_edge( std::string from, std::string to, Graph::Kind kind )
{
	bool res = false;
	// uno, o ambos nodos, no existen

	auto v1 = this->vertices.find( from );
	auto v2 = this->vertices.find( to );

	if( v1 != this->vertices.end() and v2 != this->vertices.end() ){
		v1->second.add_neighbor( v2->second );

      if( kind == Graph::Kind::UNDIRECTED ) v2->second.add_neighbor( v1->second );

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
	std::cout << "\n";
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

#ifdef DEBUG
// función auxiliar para imprimir el contenido de la cola
static void print_queue( std::deque<std::string> queue )
{
   std::cout << "El contenido de la cola es: ";
   for( auto q : queue ){
      std::cout << q << ", ";
   }
   std::cout << "\n";
}
#endif

void Graph::bfs( std::string start )
{
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

void Graph::dfs( std::string start )
{
	for (auto it = this->vertices.begin() ; it != this->vertices.end() ; it++) {
		(it->second).set_color( Vertex::Colors::BLACK );
		(it->second).set_distance( 0 );
		(it->second).set_predecesor("Null");
		(it->second).set_discovery_time( 0 );
		(it->second).set_finish_time( 0 );
	}

	size_t time = 0;

	Vertex* v = get_vertex( start );

	time = dfs_recursive( v , time );
}

size_t Graph::dfs_recursive( Vertex* v, size_t time )
{
  v->set_discovery_time( ++time );
  v->set_color( Vertex::Colors::GRAY );

	std::list<Vertex>* neighbors = v->get_neighbors();

  for( auto u = neighbors->begin(); u != neighbors->end(); ++u ){
		std::string key = u->get_name();
		Vertex* neighbor = this->get_vertex( key );

    if( neighbor->get_color() == Vertex::Colors::BLACK ){
      neighbor->set_predecesor( v->get_name() );
      time = dfs_recursive( neighbor , time );
    }
  }

  v->set_color( Vertex::Colors::WHITE );
  v->set_finish_time( ++time );
	return time;
}

std::vector<Vertex*> Graph::dfs_to( Vertex* v )
{
	for (auto it = this->vertices.begin() ; it != this->vertices.end() ; it++) {
		(it->second).set_color( Vertex::Colors::BLACK ); // sin descubir
		(it->second).set_distance( 0 );
		(it->second).set_predecesor("Null");

		(it->second).set_discovery_time( 0 ); // añadido
		(it->second).set_finish_time( 0 ); // añadido
	}

	size_t time = 0;

	std::vector<Vertex*> list;

	time = this->dfs_recursive_to( v , time , &list);

	std::sort( list.begin() , list.end());

	return list;
}

size_t Graph::dfs_recursive_to( Vertex* start , size_t time , std::vector<Vertex*>* list )
{
	start->set_discovery_time( ++time );
	start->set_color( Vertex::Colors::WHITE );

	std::list<Vertex>* neighbors = start->get_neighbors();

  for( auto u = neighbors->begin(); u != neighbors->end(); ++u ){
		std::string key = u->get_name();
		Vertex* neighbor = this->get_vertex( key );

    if( neighbor->get_color() == Vertex::Colors::BLACK ){
			neighbor->set_predecesor( start->get_name());
      time = dfs_recursive_to( neighbor , time , list);
    }
  }
	start->set_finish_time(++time);
	list->push_back( start );
	return time;
}

void Graph::dfs_print( Vertex* start ){
	std::cout << "Vertex: " << start->get_name();
	std::cout << " discovery time: " << start->get_discovery_time();
	std::cout << " finish time: " << start->get_finish_time();
	std::cout << " Predecesor: " << start->get_predecesor() << '\n';

	start->set_color( Vertex::Colors::BLACK );
	std::list<Vertex>* neighbors = start->get_neighbors();

  for( auto u = neighbors->begin(); u != neighbors->end(); ++u ){
		std::string key = u->get_name();
		Vertex* neighbor = this->get_vertex( key );

    if( neighbor->get_color() == Vertex::Colors::WHITE ){
      dfs_print( neighbor );
    }
  }
}
