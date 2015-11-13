//
// main.cpp for gomoku in /home/terran_j/rendu/ia_gomoku
//
// Made by terran_j
// Login   <terran_j@epitech.net>
//
// Started on  Tue Oct 27 11:16:54 2015 terran_j
// Last update Tue Nov 10 19:25:40 2015 terran_j
//

#include <thread>
#include <iostream>
#include "graphics/sfml.hh"
#include "referee/Referee.hh"

int	main()
{
    referee::Referee _referee;
    SFML *lib = new SFML();
    unsigned int key;
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
    bool pressed = false;
    while ((key = lib->getEvent()) != 4242424242)
    {
        if (!pressed and sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            position = lib->getPosition();
            gridPos = lib->pixelToBoardPos(position);
            if (gridPos.x != -1 and gridPos.y != -1)
            {
                // envoyer gridPos a lyoko ici:
                _referee.place_at(referee::Piece::Position({gridPos.x, gridPos.y}));
                // puis si il confirme que c'est good il me renvoie la map completée


                referee::Piece::Position p({0, 0});
                while (p.x < 19) {
                    while (p.y < 19) {
                        if (_referee.board()[p].is_white()) {
                            lib->putWhite(position);
                        } else
                        if (_referee.board()[p].is_black()) {
                            lib->putBlack(position);
                        }
                        ++p.y;
                    }
                    ++p.x;
                }
                // puis j'affiche la map dans refresh image

            }
        }
        pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        lib->affActions("Coucou", 900, 150);
        lib->refreshImg(_pions);
    }

    // tmp: (patcher les event pour que ca passe dans closeLib sans ca si je quitte)
    lib->closeLib();
    //

    return (0);
}
