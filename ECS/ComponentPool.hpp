/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#ifndef ECS_COMPONENTPOOL_HPP_
#define ECS_COMPONENTPOOL_HPP_

#include <vector>

#include "ECS.hpp"

class ComponentPool {
 public:
  ComponentPool(size_t elementsize) {
    elementSize = elementsize;
    data = new char[elementSize * MAX_ENTITIES];
  }

  ~ComponentPool() { delete[] data; }

  void *get(size_t index) { return data + index * elementSize; }

 private:
  char *data;
  size_t elementSize;
};

#endif  // ECS_COMPONENTPOOL_HPP_
