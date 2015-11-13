//
// sfml.cpp for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:24:47 2015 terran_j
// Last update Fri Nov 13 23:34:23 2015 terran_j
//

#include "graphics/sfml.hh"
#include "referee/Board.hh"
SFML::SFML()
{}

SFML::~SFML()
{}

int	SFML::initLib(unsigned int x, unsigned int y)
{
  sf::RenderWindow *n;
  sf::Font *font = new sf::Font();

  n = new sf::RenderWindow(sf::VideoMode(x, y),
      "Gomoku",
      sf::Style::Titlebar | sf::Style::Close);

  this->_window = n;
  this->_x = x;
  this->_y = y;

  sf::Texture *texture1 = new sf::Texture();
  texture1->loadFromFile("textures/background.jpg");
  sf::Sprite background(*texture1);
  this->_background = background;

  sf::Texture *texture2 = new sf::Texture();
  texture2->loadFromFile("textures/white.png");
  sf::Sprite white(*texture2);
  this->_white = white;

  sf::Texture *texture3 = new sf::Texture();
  texture3->loadFromFile("textures/black.png");
  sf::Sprite black(*texture3);
  this->_black = black;

  this->_window->clear(sf::Color::Black);
  this->_background.setPosition(0, 0);
  this->_window->draw(this->_background);
  this->_window->display();

  if (!font->loadFromFile("textures/arial.ttf"))
    return (-1);
  this->_actions.setFont(*font);

  return (0);
}

void	SFML::refreshImg(std::map<std::string, int, int> _pions, referee::Board& board)
{
  sf::Vector2i pixelPos;

  //
  _pions = _pions;
  //

  this->_window->clear(sf::Color::Black);

  this->_background.setPosition(0, 0);
  this->_window->draw(this->_background);

  referee::Piece::Position p({0, 0});
  while (p.x < 19)
  {
    while (p.y < 19)
    {
      pixelPos = XYToPixels(p.x, p.y);

      if (board[p].is_black())
        putBlack(pixelPos);
      else if (board[p].is_white())
        putWhite(pixelPos);
      ++p.y;
    }
    p.y = 0;
    ++p.x;
  }

  this->_window->draw(this->_actions);
  this->_window->display();
}

void	SFML::affActions(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_actions.setString(toAff);
  this->_actions.setCharacterSize(40);
  this->_actions.setColor(sf::Color::White);
  this->_actions.setPosition(x, y);
}

void    SFML::closeLib()
{
  this->_music->stop();
  delete(this->_music);
  this->_window->close();
}

sf::Vector2i	SFML::getPosition()
{
  sf::Window *window;
  sf::Vector2i position;

  window = dynamic_cast<sf::Window*>(this->_window);
  position = sf::Mouse::getPosition(*window);
  return (position);
}

sf::Vector2i	SFML::pixelToBoardPos(sf::Vector2i position)
{
  int size = 42; // en pixel
  int it = 0;
  sf::Vector2i gridPos;

  position.x = position.x - 46;
  position.y = position.y - 150;

  while (it <= 18)
  {
    if (position.x >= size * it and position.x <= size * (it + 1))
      gridPos.x = it;
    if (position.y >= size * it and position.y <= size * (it + 1))
      gridPos.y = it;
    it += 1;
  }

  if (position.x < 0 or position.x > 782 or position.y < 0 or position.y > 782)
  {
    gridPos.x = -1; // hors de la map
    gridPos.y = -1; // hors de la map
  }

  std::cout << "coord reelles: x: " << gridPos.x << " et y: " << gridPos.y << std::endl; // atej

  return (gridPos);
}

sf::Vector2i	SFML::XYToPixels(int x, int y)
{
  sf::Vector2i pixelPos;

  pixelPos.x = 68 + x * 42 - 19;
  pixelPos.y = 174 + y * 42 - 19;

  return (pixelPos);
}

void	SFML::putWhite(sf::Vector2i pos)
{
  this->_white.setPosition(pos.x, pos.y);
  this->_window->draw(this->_white);
}

void	SFML::putBlack(sf::Vector2i pos)
{
  this->_black.setPosition(pos.x, pos.y);
  this->_window->draw(this->_black);
}
