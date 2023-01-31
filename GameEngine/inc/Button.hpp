/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Sprite.hpp"

class Button : public Sprite {
 public:
  Button(std::string path, sf::Vector2f pos, sf::Vector2f target_size);
  bool is_pressed(sf::Vector2f mouse_pos);
  bool is_hovered(sf::Vector2f mouse_pos);
};

#endif  // !BUTTON_HPP_
