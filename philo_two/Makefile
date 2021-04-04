NAME				=	philo_two
DIRECTORY_SOURCES	=	sources
DIRECTORY_OBJECTS	=	objects

SOURCES				=	utils/ft_strlen.c \
						utils/ft_atos.c \
						npc/log.c \
						npc/character.c \
						npc/management.c \
						parse.c \
						main.c
OBJECTS				=	$(SOURCES:%.c=$(DIRECTORY_OBJECTS)/%.o)

COMPILE				=	cc
REMOVE				=	rm -rf

COMPILATION_FLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(DIRECTORY_OBJECTS):
	mkdir -p $(dir $(OBJECTS))

$(DIRECTORY_OBJECTS)/%.o: $(DIRECTORY_SOURCES)/%.c | $(DIRECTORY_OBJECTS)
	$(COMPILE) $(COMPILATION_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(COMPILE) -o $(NAME) $(OBJECTS) -pthread

clean:
	$(REMOVE) $(DIRECTORY_OBJECTS)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re
