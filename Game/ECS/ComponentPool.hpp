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
  ComponentPool(size_t t_element_size) {
    m_element_size = t_element_size;
    m_data = new char[m_element_size * MAX_ENTITIES];
  }

  ~ComponentPool() { delete[] m_data; }

  void *get(size_t index) { return m_data + index * m_element_size; }

 private:
  char *m_data;
  size_t m_element_size;
};

#endif  // ECS_COMPONENTPOOL_HPP_
