CFLAGS =			-Wall -Wextra -Werror -fsanitize=address -g

 

LIBS =				-L./libft -lft -L /usr/include -lreadline

HDRS =				minishell.h pipex.h get_next_line.h

HDRS_DIR =			./includes/

INCLUDE = 			-I ${HDRS_DIR}

CC =				cc

RM =				rm -rf

PWD_CMD =			pwd

PWD =				$(addprefix ${BINDIR}, ${PWD_CMD})

ECHO =				$(addprefix ${BINDIR}, ${ECHO_CMD})

NAME =				minishell

SRC =				parser/token_list.c parser/token_list2.c parser/parser.c parser/parser2.c parser/parser3.c parser/parser4.c parser/parser5.c parser/parser6.c parser/parser7.c exec/exec.c parser/env_list.c pipex/pipex.c pipex/parents.c pipex/fork.c\
					utils/error_managment.c pipex/validation.c pipex/get_next_line.c\
					pipex/get_next_line_utils.c export/export.c export/export_utils.c export/update.c export/unset.c export/unset_utils.c\
					export/same_for_export.c env/env.c exit/exit.c main.c cd/cd.c echo/echo.c pwd/pwd.c

SRC_PWD =			pwd.c

SRC_DIR =			./src/

PWD_DIR =			pwd/

ECHO_DIR =			echo/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

SOURCES_PWD =		$(addprefix ${PWD_DIR}, ${SRC_PWD})

SOURCES_ECHO =		$(addprefix ${ECHO_DIR}, ${SRC_ECHO})

BUILDIR = ./obj/

BUILDIRS =			echo/ cd/ env/ pwd/ utils/ pipex/ exec/ parser/ export/ exit/ libft/

BLDRS =				$(addprefix ${BUILDIR}, ${BUILDIRS})

BINDIR =			./bin/

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

OBJS_PWD =			$(addprefix ${BUILDIR}, ${SOURCES_PWD:.c=.o})

OBJS_ECHO =			$(addprefix ${BUILDIR}, ${SOURCES_ECHO:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

.PHONY:				clean all fclean re

all:				${BUILDIR} ${BLDRS} ${LIBFT} ${NAME}

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

${PWD}:				${OBJS_PWD} ${HEADERS} 
					#${CC} ${CFLAGS} ${LIBS} ${OBJS_PWD} -o $@
					${CC} ${CFLAGS} ${OBJS_PWD} -o $@ ${LIBS}

${ECHO}:			${OBJS_ECHO} ${HEADERS} 
					#${CC} ${CFLAGS} ${LIBS} ${OBJS_ECHO} -o $@
					${CC} ${CFLAGS} ${OBJS_ECHO} -o $@ ${LIBS}

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${PWD_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${CD_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${ECHO_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

clean:
					${MAKE} clean -C ${LIBFTDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					${RM} ${BINDIR}
					${RM} ${NAME}

re:					fclean all
