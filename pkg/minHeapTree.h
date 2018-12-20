
#ifndef MIN_HEAP_TREE
#define MIN_HEAP_TREE

#include "heapTree.h"

template < class T >
class minHeapTree : public heapTree< T > {
 public:
  minHeapTree();
  minHeapTree(const minHeapTree&);
  virtual ~minHeapTree();

  const T min() const;

 private:
  virtual void bubbleUp(int);
  virtual void bubbleDw(int);
};

template < class T >
minHeapTree< T >::minHeapTree() {}

template < class T >
minHeapTree< T >::minHeapTree( const minHeapTree &other ) 
: heapTree< T >( other ) {}

template < class T >
minHeapTree< T >::~minHeapTree() {}

template < class T >
void minHeapTree< T >::bubbleUp( int index ) {
  if ( not this->hasParent( index ) ) return;
  if ( this->get(index) >= this->getParent( index ) ) return;

  const int indexParent = this->getParentIndex( index );
  this->swap( index,indexParent );
  this->bubbleUp( indexParent );
}

template < class T >
void minHeapTree< T >::bubbleDw( int index ) {
  if ( not this->hasLeftChild( index ) ) return;

  int indexChild = this->getLeftChildIndex( index );
  if ( this->hasRightChild( index ) &&
       this->getRightChild( index ) < this->getLeftChild( index ) )
    indexChild = this->getRightChildIndex( index );

  if ( this->get(index) < this->get(indexChild) ) return;

  this->swap( index,indexChild );
  this->bubbleDw( indexChild );
}

template < class T >
const T minHeapTree< T >::min() const { return this->get(1); }

#endif
