/*Copyright (C)
 * 2019 - eda1 dot fiunam at yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */


#include <iostream>
// para std::cout y std::cin

#include <utility>
// para std::pair

const size_t m_order = 4;
// orden máximo (máximo número de hijos en el nodo) porque así está definido en
// los libros. Internamente al programa utilizamos en número de claves


// no la vamos a usar en este ejemplo, pero la he dejado aquí para futuras actualizaciones
struct Item
{
   int key;
};



//----------------------------------------------------------------------
//  Class Node
//----------------------------------------------------------------------
struct Node
{
   Node();
   // constructor por defecto: pondrá a ceros a keys y children. Es muy probable
   // que esto no sea necesario, pero lo haremos por seguridad

   int keys[ m_order ];
   // las primeras m_order - 1 entradas son válidas; la última entrada se usa
   // cuando se parte el nodo.
   // [DESHPANDExx]

   Node* children[ m_order + 1 ];
   // siempre hay un hijo más que claves

   size_t cnt = 0;
   // lleva la cuenta de las claves insertadas en el nodo

   bool leaf = true;

   static const size_t max = m_order - 1;
   // número máximo de CLAVES en el nodo

   static const size_t min = max / 2;
   // número mínimo de CLAVES en el nodo
};

Node::Node()
{
   for( size_t i = 0; i < m_order; ++i ) this->keys[ i ] = 0;
   for( size_t i = 0; i < m_order + 1; ++i ) this->children[ i ] = nullptr;
}

//----------------------------------------------------------------------
//  Class B_tree
//----------------------------------------------------------------------
class B_tree
{
private:
   Node* root = nullptr;

   size_t m_order;
   // no se usa en esta implementación

   Node* insert_node( Node* node, int key );
   Node* split_node( Node* node, size_t index );
   Node* delete_node( Node* node, int key );
   std::pair<bool,int> find_node( Node* node, int key ) const;
   void traverse_node( Node* node, void (*visit)( int key ) ) const;

public:
   explicit B_tree( size_t m_order );
   ~B_tree();

   bool Insert( int key );
   bool Delete( int key );
   std::pair<bool,int> Find( int key ) const;
   void Traverse( void (*visit)(int key) ) const;
   void Delete_all();

   // operaciones para depuración:

   void print_keys( const Node* ) const;
   Node* get_root() const;
};


Node* B_tree::get_root() const
{
   return this->root;
}

void B_tree::print_keys( const Node* node ) const
{
   if( node->cnt == 0 ){
      std::cerr << "Nodo vacío\n";
   } else{
      std::cerr << "\n<";
      for( size_t i = 0; i < node->cnt; ++i ){
         std::cerr << node->keys[ i ] << ", ";
      }
      std::cerr << ">\n";
   }
}


B_tree::B_tree( size_t m_order ) : m_order{ m_order }
{
   // nada (por el momento)
}

B_tree::~B_tree()
{
   // llamar a ::Delete_all()
}

bool B_tree::Insert( int key )
{
}

Node* B_tree::insert_node( Node* node, int key )
{
}

Node* B_tree::split_node( Node* parent, size_t index )
{
}

void B_tree::traverse_node( Node* node, void (*visit)( int key ) ) const
{

}

void B_tree::Traverse( void (*visit)(int key) ) const
{

}

void B_tree::Delete_all()
{

}

bool B_tree::Delete( int key )
{
}


std::pair<bool,int> B_tree::Find( int key ) const
{

}

std::pair<bool,int> B_tree::find_node( Node* node, int key ) const
{

}




int main()
{
   B_tree arbol( m_order );

    int keys[13] = { 500,700,900,1100,600,650,1000,800,550,625,675,1200,1150};

   for( int k : keys ){
      arbol.Insert( k );
      arbol.print_keys( arbol.get_root() );
   }

   arbol.Traverse( [](int key){ std::cout << key << ", "; } );

#if 0
   for( int i = 10; i < 270; i += 10 ){
      arbol.Insert( i );
      arbol.Traverse( [](int key){ std::cout << key << ", "; } );
      std::cout << "\n";
   }

   while( 1 ){
      int key;
      std::cout << "¿Qué valor desea insertar? -1 para terminar\n$ ";
      std::cin >> key;

      if( key >= 0 ) {
         arbol.Insert( key );
         arbol.Traverse( [](int key){ std::cout << key << ", "; } );
         std::cout << "\n";
      } else{
         return 0;
      }
   }
#endif

#if 0
//   int keys[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260 };
#endif

	// ¡ No olvidar al destructor !
}
