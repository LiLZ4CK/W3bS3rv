NAME = Webserev

CC = c++ -std=c++98

FLAGS = -Wall -Wextra -Werror

SRC =	*.cpp\
		../Parsing/*.cpp

all : $(NAME)
$(NAME) : $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(NAME)

fclean :
	rm -f $(NAME)

re : fclean all