CFLAGS =			-Wall -Wextra -Werror -fsanitize=address -g

 

LIBS =				-L./libft -lft -L /usr/include -lreadline

HDRS =				minishell.h pipex.h get_next_line.h

HDRS_DIR =			./includes/

INCLUDE = 			-I ${HDRS_DIR}

CC =				cc -D MAIN=0

ifeq ($(MAKECMDGOALS), test)
CC =				cc -D TEST=0
endif

ifeq ($(MAKECMDGOALS), gdb)
CC =				cc -D GDB=0
endif

RM =				rm -rf

NAME =				minishell

# NAME_TEST =			minishell

# NAME_GDB =			minishell

# NAME_MAIN =			minishell

SRC =				parser/expand_dolar.c parser/token_list.c parser/parser.c exec/exec.c parser/env_list.c\
					pipex/pipex.c pipex/parents.c pipex/fork.c\
					utils/error_managment.c pipex/validation.c pipex/get_next_line.c\
					pipex/get_next_line_utils.c export/export.c export/export_utils.c\
					export/update.c export/unset.c\
					export/same_for_export.c env/env.c exit/exit.c cd/cd.c main.c\
					echo/echo.c pwd/pwd.c

# SRC_PWD =			pwd.c

# SRC_ECHO =			echo.c

SRC_DIR =			./src/

# PWD_DIR =			pwd/

# ECHO_DIR =			echo/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

# SOURCES_PWD =		$(addprefix ${PWD_DIR}, ${SRC_PWD})

# SOURCES_ECHO =		$(addprefix ${ECHO_DIR}, ${SRC_ECHO})

BUILDIR = ./obj/

BUILDIRS =			echo/ cd/ env/ pwd/ utils/ pipex/ exec/ parser/ export/ exit/ libft/

BLDRS =				$(addprefix ${BUILDIR}, ${BUILDIRS})

BINDIR =			./bin/

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

# OBJS_PWD =			$(addprefix ${BUILDIR}, ${SOURCES_PWD:.c=.o})

# OBJS_ECHO =			$(addprefix ${BUILDIR}, ${SOURCES_ECHO:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

.PHONY:				clean all fclean re

all:				${BUILDIR} ${BLDRS} ${LIBFT} ${NAME}

main:				all

test:				all

gdb:				all

${LIBFT}:
					${MAKE} -C ${LIBFTDIR}

${NAME}:			${OBJS} ${HEADERS} 
					#${CC} ${CFLAGS} ${LIBS} ${OBJS} -o $@				#MacOS
					${CC} ${CFLAGS} ${OBJS} -o $@ ${LIBS}				#Linux

${BUILDIR}:
					mkdir -p $@

${BLDRS}:
					mkdir -p $@

${BINDIR}:
					mkdir -p ${BINDIR}

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

clean:
					${MAKE} clean -C ${LIBFTDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					${RM} ${BINDIR}
					${RM} ${NAME}

re:					fclean all