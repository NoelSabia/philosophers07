CC		= gcc
CFLAGS	= -Wall -Wextra #-Werror -01 -02 -03
NAME	= philo

SRC_PATH = src/
OBJ_PATH = obj/

SRC		= main.c \
			helperfunctions.c \
			initialize.c \
			monitoring.c \
			philo_routine.c \
			destroy.c \

SRCm	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INCS	= -I ./includes/

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all