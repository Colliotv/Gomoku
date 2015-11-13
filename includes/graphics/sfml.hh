//
// sfml.hh for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:21:22 2015 terran_j
// Last update Fri Nov 13 22:12:55 2015 terran_j
//

#ifndef SFML_HH__
# define SFML_HH__

#include <map>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <X11/Xlib.h>
#include <iostream>

#define WIDTH 1500
#define HEIGHT 1000

class SFML;

//typedef void (SFML::*mapFPtr)(int, int);

namespace referee { class Board; }

class SFML
{
public:
  sf::Music *_music; // faire setter getter plus tard

  SFML();
  ~SFML();

  SFML &operator=(SFML const &) = default;
  SFML(const SFML &) = default;
  SFML(SFML &&) = default;

  int initLib(unsigned int x, unsigned int y);
  int getEvent();
  void refreshImg(std::map<std::string, int, int> _pions, referee::Board&);
  void affActions(const std::string &toAff, unsigned int x, unsigned int y);
  void closeLib();
  sf::Vector2i getPosition();
  sf::Vector2i pixelToBoardPos(sf::Vector2i position);
  sf::Vector2i XYToPixels(int x, int y);
  void putWhite(sf::Vector2i pos);
  void putBlack(sf::Vector2i pos);

private:
  sf::RenderWindow *_window;
  int _x;
  int _y;
  sf::Sprite _background;
  sf::Sprite _white;
  sf::Sprite _black;
  sf::Text _actions;
};

#endif
