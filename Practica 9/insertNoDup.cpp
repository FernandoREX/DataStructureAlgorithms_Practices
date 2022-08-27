#include <iostream>
#include <list>
#include <utility>

const size_t m_order = 4;

/**********************Estructuras*******************/

struct Item{ // Datos
  int key;
};

struct Node{
  Node();

  static const size_t max = m_order - 1;
  static const size_t min = max/2;

  int keys[ m_order ];
  Node* children[ m_order+1 ];

  size_t cnt = 0;

  bool leaf = true;
};

Node::Node(){
  for( size_t i=0;i < m_order;  i++ ) this->keys[ i ] = 0;
  for(size_t i=0; i < m_order + 1 ; ++i ) this->children[ i ] = nullptr;
}

/**********************Clases*******************/

class B_tree{
  private:
    Node* root = nullptr;
    size_t len;
    size_t max;

    Node* insert_node( Node* node, int key );
    Node* split_node( Node* node, size_t index );
    Node* delete_node( Node* node, int key );

    std::pair<bool,int> find_node(Node* node, int key ) const;

    void traverse_node( Node* node, void (*visit)( int key ) ) const;
    void delete_tree( Node* node );
  public:
    explicit B_tree(size_t m_order);
    ~B_tree();

    bool Insert( int key );
    bool Delete( int key );
    std::pair<bool,int> Find( int key ) const;
    void Traverse( void (*visit)( int key ) ) const;
    void Delete_all();
/**********************Extras*******************/
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

std::pair<bool,int> B_tree::find_node(Node* node, int key ) const {
  size_t i = 0;
  while (i < node->cnt && key > node->keys[i]) {
    ++i;
  }
  if (i < node->cnt && key == node->keys[i])
    return std::make_pair(true, key);
  else if(node->leaf)
    return std::make_pair(false, -1);
  else
    return std::make_pair(node->children[ i ], key);
}

Node* B_tree::insert_node( Node* node, int key ){

  auto duplicated = find_node(node , key);

  if(duplicated.first != true || key != duplicated.second){
    size_t index = node->cnt;

    if (node->leaf == true) {
      while (index > 0 && key < node->keys[index - 1]) {
        node->keys[index] = node->keys[index - 1];
        --index;
      }
      node->keys[index] = key;
      ++node->cnt;

      std::cout << " Escribir en disco " << key << '\n';
    }
    else{
      while (index > 0 && key < node->keys[index - 1]) {
        --index;
      }

      std::cout << " lee el disco " << '\n';

      if(node->children[index]->cnt == Node::max){

        node->leaf = false;
        node = split_node(node, index);

        if (key > node->keys[index]) {
          ++index;
        }
      }

      insert_node(node->children[index] , key);
    }
    return node;
  }
  else{
    std::cout << " No se insertara un valor duplicado ("<<key<<")\n";
    return nullptr;
  }
}

Node* B_tree::split_node( Node* parent, size_t index ){
  Node* left = parent->children[index];

  Node* right = new Node();
  right->leaf = left->leaf;
  right->cnt = Node::min;

  for (size_t j = 0; j < Node::min; j++) {
    right->keys[j] = left->keys[j + Node::min + 1];
  }

  if (left->leaf == false) {
    for (size_t j = 0; j <= Node::min; j++) {
      right->children[j] = left->children[j + Node::min + 1];
    }
  }

  left->cnt = Node::min;

  for (size_t j = parent->cnt; j > (index) ; j--) {
    parent->children[j+1] = parent->children[j];
  }

  parent->children[index + 1] = right;

  for (size_t j = parent->cnt; j > (index) ; --j) {
    parent->keys[j] = parent->keys[j-1];
  }

  parent->keys[index] = left->keys[Node::min];

  ++parent->cnt;

  return parent;
}

Node* B_tree::delete_node( Node* node, int key ){
  return nullptr;
}

void B_tree::traverse_node( Node* node, void (*visit)( int key ) ) const {
  if( node->leaf == true ){
    for( size_t i = 0; i < node->cnt; ++i )
      visit( node->keys[ i ] );
  }
  else{
    for( size_t i = 0; i <= node->cnt; ++i ){
      traverse_node( node->children[ i ], visit );
      if( i < node->cnt ) visit( node->keys[ i ] );
    }
  }
}

void B_tree::delete_tree( Node* node ){
  if (node->leaf) {
    delete node;
  }
  else {
    size_t i = 0;
    while (node->children[i] != nullptr) {
      delete_tree( node->children[ i ]);
      node->children[i] = nullptr;
      ++i;
    }
    delete node;
  }
}

B_tree::B_tree( size_t m_order ) : max{ m_order }
{
  // nada (por el momento)
}

B_tree::~B_tree()
{
  Delete_all();
}

bool B_tree::Insert( int key ){
  if (root == nullptr) {
    root = new Node();
    root->keys[0] = key;
    root->cnt = 1;
  }
  else{
    if(root->cnt == Node::max){
      auto tmp = this->root;
      root = new Node();
      root->children[0] = tmp;
      root->leaf = false;
      root = split_node(root , 0);
    }
    root = insert_node(root, key);
  }

  return (root != nullptr);
}

bool B_tree::Delete( int key ){
  return false;
}

std::pair<bool,int> B_tree::Find( int key ) const { // : [bool, int]
  if (root == nullptr) return std::make_pair(false, 0);

  auto val = find_node(root, key);

  return val;
}

void B_tree::Traverse( void (*visit)(int key) ) const {
  if( root != nullptr ) traverse_node( root, visit );
  else std::cout << "Árbol vacío\n";
}


void B_tree::Delete_all(){
  if (root != nullptr) {
    delete_tree( root );
  }
}

int main()
{
#if 0
  int keys[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260 };
#endif

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
    std::cout << "¿Qué valor desea insertar? \t(-1 para terminar)\n$ ";
    std::cin >> key;

    if( key >= 0 ) {
      arbol.Insert( key );
      arbol.Traverse( [](int key){ std::cout << key << ", "; } );
      std::cout << "\n";
    }else{
      return 0;
    }
   }
#endif
	// ¡ No olvidar al destructor !
}
