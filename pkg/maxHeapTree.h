
#ifndef MAX_HEAP_TREE
#define MAX_HEAP_TREE

#include "heapTree.h"

template < class T >
class maxHeapTree : public heapTree< T > {
 public:
  maxHeapTree();
  maxHeapTree(const maxHeapTree&);
  virtual ~maxHeapTree();

  const T max() const;

 private:
  virtual void bubbleUp(int);
  virtual void bubbleDw(int);
};

template < class T >
maxHeapTree< T >::maxHeapTree() {}

template < class T >
maxHeapTree< T >::maxHeapTree( const maxHeapTree &other ) 
: heapTree< T >( other ) {}

template < class T >
maxHeapTree< T >::~maxHeapTree() {}

template < class T >
void maxHeapTree< T >::bubbleUp( int index ) {
  if ( not this->hasParent( index ) ) return;
  if ( this->get(index) < this->getParent( index ) ) return;

  const int indexParent = this->getParentIndex( index );
  this->swap( index,indexParent );
  this->bubbleUp( indexParent );
}

template < class T >
void maxHeapTree< T >::bubbleDw( int index ) {
  if ( not this->hasLeftChild( index ) ) return;

  int indexChild = this->getLeftChildIndex( index );
  if ( this->hasRightChild( index ) &&
       this->getRightChild( index ) > this->getLeftChild( index ) )
    indexChild = this->getRightChildIndex( index );

  if ( this->get(index) > this->get(indexChild) ) return;

  this->swap( index,indexChild );
  this->bubbleDw( indexChild );
}

template < class T >
const T maxHeapTree< T >::max() const { return this->get(1); }

#endif
