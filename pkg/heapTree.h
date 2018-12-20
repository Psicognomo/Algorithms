
#ifndef HEAP_TREE
#define HEAP_TREE

#include <iostream>
#include <vector>

template < class T >
class heapTree {
 public:
  heapTree();
  heapTree(const heapTree&);
  virtual ~heapTree();

  int size() const;
  void add(T);

  virtual T pop();
  void print() const;

 protected:
  virtual void bubbleUp(int) = 0;
  virtual void bubbleDw(int) = 0;

  inline bool hasParent(const int) const;
  inline bool hasLeftChild(const int) const;
  inline bool hasRightChild(const int) const;

  inline T get(const int) const;
  inline T getParent(const int) const;
  inline T getLeftChild(const int) const;
  inline T getRightChild(const int) const;

  inline const int getParentIndex(const int) const;
  inline const int getLeftChildIndex(const int) const;
  inline const int getRightChildIndex(const int) const;

  inline void increaseSize();
  inline void decreaseSize();

  void swap(const int,const int);

 protected:
  int m_size;
  std::vector< T > m_elements;
};

template < class T >
heapTree< T >::heapTree() 
: m_size(0) {}

template < class T >
heapTree< T >::heapTree( const heapTree& other ) 
: m_size( other.m_size ),
  m_elements( m_elements.begin(), m_elements.end() ) {}  

template < class T >
heapTree< T >::~heapTree() {}

template < class T >
int heapTree< T >::size() const { return m_size; }

template < class T >
void heapTree< T >::add( T toAdd ) {
  m_elements.push_back( toAdd );
  this->increaseSize();
  this->bubbleUp( this->size() );
}

template < class T >
bool heapTree< T >::hasParent( const int index ) const { return index > 1; }

template < class T >
bool heapTree< T >::hasLeftChild( const int index ) const { return 2*index <= m_size; }

template < class T >
bool heapTree< T >::hasRightChild( const int index ) const { return 2*index + 1 <= m_size; }

template < class T >
T heapTree< T >::get( const int index ) const { return m_elements.at( index - 1 ); }

template < class T >
T heapTree< T >::getParent( const int index ) const { 
  return this->get( this->getParentIndex( index ) );
}

template < class T >
T heapTree< T >::getLeftChild( const int index ) const {
  return this->get( this->getLeftChildIndex( index ) );
}

template < class T >
T heapTree< T >::getRightChild( const int index ) const {
  return this->get( this->getRightChildIndex( index ) );
}

template < class T >
const int heapTree< T >::getParentIndex( const int index ) const { return index/2; }

template < class T >
const int heapTree< T >::getLeftChildIndex( const int index ) const { return 2*index; }

template < class T >
const int heapTree< T >::getRightChildIndex( const int index ) const { return 2*index + 1; }

template < class T >
void heapTree< T >::increaseSize() { m_size++; }

template < class T >
void heapTree< T >::decreaseSize() { m_size--; }

template < class T >
T heapTree< T >::pop() { 
  T output = m_elements.at(0);
  m_elements.at(0) = m_elements.at( m_size - 1 );
  m_elements.pop_back();
  this->decreaseSize();
  this->bubbleDw( 1 );
  return output;
}

template < class T >
void heapTree< T >::print() const {
  std::cout<<"[ ";
  for (unsigned int i=0; i<m_elements.size(); i++)
    std::cout<<m_elements.at(i) <<" ";
  std::cout<<"]";
  std::cout<<std::endl;
}

template < class T >
void heapTree< T >::swap( const int indexA,const int indexB ) {
  T tmpValue = m_elements.at( indexA - 1 );
  m_elements.at( indexA - 1 ) = m_elements.at( indexB - 1 );
  m_elements.at( indexB - 1 ) = tmpValue;
}

#endif
