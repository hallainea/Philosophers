SOURCES				=	srcs/utils/ft_strlen.c \
						srcs/utils/ft_atos.c \
						srcs/npc/character.c \
						srcs/npc/management.c \
						srcs/parse.c \
						srcs/main.c
OBJECTS				=	${SOURCES:.c=.o}

NAME				=	philo_one

COMPILE				=	cc
REMOVE				=	rm -f

COMPILATION_FLAGS	=	-Wall -Wextra -Werror

.c.o:
	${COMPILE} ${COMPILATION_FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	${COMPILE} -o ${NAME} ${OBJECTS} -pthread

clean:
	${REMOVE} ${OBJECTS}

fclean: clean
	${REMOVE} ${NAME}

re: fclean all

.PHONY: all clean fclean re
