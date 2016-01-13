##
## Makefile for gomoku in /home/terran_j/rendu/ia_gomoku
##
## Made by terran_j
## Login   <terran_j@epitech.net>
##
## Started on  Tue Oct 27 11:16:18 2015 terran_j
## Last update Thu Nov 26 20:29:51 2015 terran_j
##

NAME	=	gomoku

SRC	=       src/start/main.cpp \
		src/graphics/sfml.cpp \
		src/referee/Board.cpp \
		src/referee/Piece.cpp \
		src/referee/Referee.cpp \
		src/game/Player.cpp \
		src/IAminmax/IAminmax.cpp

OBJ	=       $(SRC:.cpp=.o)

CXX  =          g++

CXXFLAGS +=	-Wall -Wextra -Werror -I ./includes/ -std=gnu++11

LDFLAGS =       -lpthread -lX11 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

make:   all

$(NAME):$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all:    $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
