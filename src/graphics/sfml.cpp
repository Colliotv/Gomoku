//
// sfml.cpp for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:24:47 2015 terran_j
// Last update Thu Nov 26 22:06:45 2015 terran_j
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

  sf::Texture *texture0 = new sf::Texture();
  texture0->loadFromFile("textures/background2.jpg");
  sf::Sprite background2(*texture0);
  this->_background2 = background2;

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

  if (!font->loadFromFile("textures/arial.ttf"))
    return (-1);
  this->_scores.setFont(*font);
  this->_scoreWhite.setFont(*font);
  this->_scoreBlack.setFont(*font);
  this->_victory.setFont(*font);
  this->_playerTurn.setFont(*font);

  return (0);
}

void	SFML::startMenu()
{
  sf::Vector2i position;
  sf::Event e;
  bool play = false;

  this->IsSound = true;
  this->IsAI = true;
  this->AreExtraRules = true;

  sf::Texture *texture0 = new sf::Texture();
  texture0->loadFromFile("textures/soundon.png");
  sf::Sprite soundon(*texture0);

  sf::Texture *texture1 = new sf::Texture();
  texture1->loadFromFile("textures/soundoff.png");
  sf::Sprite soundoff(*texture1);

  sf::Texture *texture2 = new sf::Texture();
  texture2->loadFromFile("textures/pvp.png");
  sf::Sprite pvp(*texture2);

  sf::Texture *texture3 = new sf::Texture();
  texture3->loadFromFile("textures/pvia.png");
  sf::Sprite pvia(*texture3);

  sf::Texture *texture4 = new sf::Texture();
  texture4->loadFromFile("textures/rules.png");
  sf::Sprite rules(*texture4);

  sf::Texture *texture5 = new sf::Texture();
  texture5->loadFromFile("textures/norules.png");
  sf::Sprite norules(*texture5);

  sf::Texture *texture6 = new sf::Texture();
  texture6->loadFromFile("textures/newgame.png");
  sf::Sprite newgame(*texture6);

  this->_window->clear(sf::Color::Black);
  this->_background2.setPosition(0, 0);
  this->_window->draw(this->_background2);

  soundon.setPosition(600, 300);
  this->_window->draw(soundon);

  pvia.setPosition(600, 400);
  this->_window->draw(pvia);

  rules.setPosition(600, 500);
  this->_window->draw(rules);

  newgame.setPosition(600, 600);
  this->_window->draw(newgame);

  this->_window->display();

  this->SoundIsHere = false;
  while (!play)
  {
    while (this->window().pollEvent(e))
    {
      if (e.type == sf::Event::MouseButtonPressed)
      {
        position = this->getPosition();

        if (position.x > 600 && position.x < 900
            && position.y > 300 && position.y < 380)
        {
          this->IsSound = !this->IsSound;
          if (this->IsSound)
          {
            soundon.setPosition(600, 300);
            this->_window->draw(soundon);
            this->_window->display();
          }
          else
          {
            soundoff.setPosition(600, 300);
            this->_window->draw(soundoff);
            this->_window->display();
          }
        }

        if (position.x > 600 && position.x < 900
            && position.y > 400 && position.y < 480)
        {
          this->IsAI = !this->IsAI;
          if (this->IsAI)
          {
            pvia.setPosition(600, 400);
            this->_window->draw(pvia);
            this->_window->display();
          }
          else
          {
            pvp.setPosition(600, 400);
            this->_window->draw(pvp);
            this->_window->display();
          }
        }

        if (position.x > 600 && position.x < 900
            && position.y > 500 && position.y < 580)
        {
          this->AreExtraRules = !this->AreExtraRules;
          if (this->AreExtraRules)
          {
            rules.setPosition(600, 500);
            this->_window->draw(rules);
            this->_window->display();
          }
          else
          {
            norules.setPosition(600, 500);
            this->_window->draw(norules);
            this->_window->display();
          }
        }

        if (position.x > 600 && position.x < 900
            && position.y > 600 && position.y < 680)
        {
          play = true;
          break;
        }
      }
      else if (e.type == sf::Event::Closed)
        this->closeLib();
      else
      if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)
        this->closeLib();
    }
  }
}

void	SFML::endMenu()
{
  if (this->IsSound == true)
  {
    this->_music = new sf::Music();
    if (!this->_music->openFromFile("textures/music.ogg"))
      return;
    this->_music->play();
    this->SoundIsHere = true;
  }

  this->_window->clear(sf::Color::Black);
  this->_background.setPosition(0, 0);
  this->_window->draw(this->_background);
  this->_window->display();
}

void	SFML::refreshImg(referee::Board& board, referee::Piece::identity identity, int white_points, int black_points, referee::Piece::identity victory)
{
  sf::Vector2i pixelPos;
  sf::Vector2i scoresPosWhite;
  sf::Vector2i scoresPosBlack;

  scoresPosWhite.x = 900;
  scoresPosWhite.y = 210;
  scoresPosBlack.x = 900;
  scoresPosBlack.y = 255;

  this->_window->clear(sf::Color::Black);

  this->_background.setPosition(0, 0);
  this->_window->draw(this->_background);

  if (victory == referee::Piece::identity::none) {

    this->affScores("Scores", 900, 150);

    // aff pion blanc:
    this->putWhite(scoresPosWhite);
    this->affScoreWhite(std::to_string(white_points), 1000, 200);

    // aff pion noir:
    this->putBlack(scoresPosBlack);
    this->affScoreBlack(std::to_string(black_points), 1000, 250);

    // aff qui joue:
    if (identity == referee::Piece::identity::white)
      this->affPlayerTurn("White Turn", 900, 500);
    if (identity == referee::Piece::identity::black)
      this->affPlayerTurn("Black Turn", 900, 500);

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

    this->_window->draw(this->_scores);
    this->_window->draw(this->_scoreWhite);
    this->_window->draw(this->_scoreBlack);
    this->_window->draw(this->_playerTurn);

  }
  else
  {
    if (victory == referee::Piece::identity::white)
    {
      this->affVictory("White victory !", 400, 400);
    }
    else
    {
      this->affVictory("Black victory !", 400, 400);
    }
    this->_background2.setPosition(0, 0);
    this->_window->draw(this->_background2);
    this->_window->draw(this->_victory);
  }

  this->_window->display();
}

void	SFML::affScores(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_scores.setString(toAff);
  this->_scores.setCharacterSize(40);
  this->_scores.setColor(sf::Color::White);
  this->_scores.setPosition(x, y);
}

void	SFML::affScoreWhite(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_scoreWhite.setString(toAff);
  this->_scoreWhite.setCharacterSize(40);
  this->_scoreWhite.setColor(sf::Color::White);
  this->_scoreWhite.setPosition(x, y);
}

void	SFML::affScoreBlack(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_scoreBlack.setString(toAff);
  this->_scoreBlack.setCharacterSize(40);
  this->_scoreBlack.setColor(sf::Color::White);
  this->_scoreBlack.setPosition(x, y);
}

void	SFML::affVictory(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_victory.setString(toAff);
  this->_victory.setCharacterSize(120);
  this->_victory.setColor(sf::Color::White);
  this->_victory.setPosition(x, y);
}

void	SFML::affPlayerTurn(const std::string &toAff, unsigned int x, unsigned int y)
{
  this->_playerTurn.setString(toAff);
  this->_playerTurn.setCharacterSize(80);
  this->_playerTurn.setColor(sf::Color::White);
  this->_playerTurn.setPosition(x, y);
}

void    SFML::closeLib()
{
  if (this->SoundIsHere == true)
  {
    this->_music->stop();
    delete(this->_music);
  }
  this->_window->close();
  exit(0);
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
