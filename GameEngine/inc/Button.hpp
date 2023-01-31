/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Sprite.hpp"

#define GRAY sf::Color(128, 128, 128)
#define WHITE sf::Color(255, 255, 255)

class Button : public Sprite {
 public:
  Button(std::string t_path, sf::Vector2f t_pos, sf::Vector2f t_target_size);
  bool is_pressed(sf::Vector2f t_mouse_pos);
  bool is_hovered(sf::Vector2f t_mouse_pos);
};

#endif  // !BUTTON_HPP_
