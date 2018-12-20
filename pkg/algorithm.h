
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>

class algorithm {
 public:
  algorithm();
  virtual ~algorithm();

  virtual const std::string description() const = 0; 
};

algorithm::algorithm() {}
algorithm::~algorithm() {}

#endif
