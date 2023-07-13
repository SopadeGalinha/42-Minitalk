# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 17:09:17 by jhogonca          #+#    #+#              #
#    Updated: 2023/07/13 17:09:17 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CLIENT = client
SERVER = server

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CLIENT_SRCS = srcs/client.c srcs/utils.c
SERVER_SRCS = srcs/server.c srcs/utils.c

CLIENT_OBJS = ${CLIENT_SRCS:.c=.o}
SERVER_OBJS = ${SERVER_SRCS:.c=.o}

all: ${CLIENT} ${SERVER}

${CLIENT}: ${CLIENT_OBJS}
	${CC} ${CFLAGS} -o ${CLIENT} ${CLIENT_OBJS}
	printf "Client \033[0;32m [OK]\n\033[0m"

${SERVER}: ${SERVER_OBJS}
	${CC} ${CFLAGS} -o ${SERVER} ${SERVER_OBJS}
	printf "Server \033[0;32m [OK]\n\033[0m"

clean:
	${RM} ${CLIENT_OBJS} ${SERVER_OBJS}
	printf "clean  \033[0;35m [OK]\n\033[0m"

fclean: clean
	${RM} ${CLIENT} ${SERVER}
	printf "fclean \033[0;35m [OK]\n\033[0m"

re: fclean all

norm:
	printf "\033[0;32mRunning Norminette\n\n\033[0m"
	norminette -R CheckForbiddenSourceHeader utils.c client.c server.c

.PHONY: clean fclean all re norm