//
// main.cpp for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:16:54 2015 terran_j
// Last update Fri Nov 13 23:20:57 2015 terran_j
//

#include <thread>
#include <iostream>
#include "graphics/sfml.hh"
#include "referee/Referee.hh"

int	main()
{
  referee::Referee _referee;
  SFML *lib = new SFML();
  std::map<std::string, int, int> _pions;
  sf::Vector2i position;
  sf::Vector2i gridPos;

  lib->_music = new sf::Music();
  if (!lib->_music->openFromFile("textures/music.ogg"))
    return (-1);
  lib->_music->play();

  // a virer:
  _pions = _pions;
  //

  XInitThreads();
  if (lib->initLib(WIDTH, HEIGHT) == -1)
    return (-1);

  //menu a faire ici

  // boucle de jeu:
  while (lib->window().isOpen()) {
    sf::Event e;
    while (lib->window().pollEvent(e)) {
      if (e.type == sf::Event::MouseButtonPressed) {
        position = lib->getPosition();
        gridPos = lib->pixelToBoardPos(position);
        if (gridPos.x!=-1 and gridPos.y!=-1) {
          // envoyer gridPos a lyoko ici:
          _referee.place_at(referee::Piece::Position({gridPos.x, gridPos.y}));
          // puis si il confirme que c'est good il me renvoie la map completée

          // puis j'affiche la map dans refresh image:
          lib->affActions("Coucou", 900, 150);
          lib->refreshImg(_pions, _referee.board()); // faudra virer les pions partt
        }
      } else
      if (e.type == sf::Event::Closed)
        lib->closeLib();
      else
      if (e.type == sf::Event::KeyPressed)
        lib->closeLib();
    }
  }

  return (0);
}
