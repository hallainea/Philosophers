NAME				=	philo_one

DIRECTORY_SOURCES	=	sources
DIRECTORY_OBJECTS	=	objects

SOURCES				=	utils/ft_strlen.c \
						utils/ft_atos.c \
						npc/log.c \
						npc/character.c \
						npc/management.c \
						parse.c \
						clean.c \
						main.c
OBJECTS				=	$(SOURCES:%.c=$(DIRECTORY_OBJECTS)/%.o)

COMPILE				=	cc
REMOVE				=	rm -rf

COMPILATION_FLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(DIRECTORY_OBJECTS):
	mkdir -p $(dir $(OBJECTS))

$(DIRECTORY_OBJECTS)/%.o: $(DIRECTORY_SOURCES)/%.c | $(DIRECTORY_OBJECTS)
	@printf "\e[33m"
	@printf "Compile\t$< -> $@\n"
	$(COMPILE) $(COMPILATION_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@printf "\e[32m"
	@printf "Build\t$(NAME)\n"
	$(COMPILE) -o $(NAME) $(OBJECTS) -pthread
	@printf "\e[39m"

run: all
	./$(NAME)

clean:
	@printf "\e[31m"
	@printf "Remove\t$(DIRECTORY_OBJECTS)\n"
	$(REMOVE) $(DIRECTORY_OBJECTS)

fclean: clean
	@printf "Remove\t$(NAME)\n"
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all run clean fclean re
.SILENT: