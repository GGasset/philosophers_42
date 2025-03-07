# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 12:49:28 by ggasset-          #+#    #+#              #
#    Updated: 2025/03/04 15:14:26 by ggasset-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

ARCHIVES=

COMPILER= cc
O_FILES=constructors.o	dealloc.o  ft_atoi_s.o	main.o  observer.o  parsing.o policies.o utils.o
LINK_FLAGS= -lpthread #-fsanitize=thread
CC_SECURITY_FLAGS= -Wall -Wextra -Werror 
CC_FLAGS= -g 

LOGO=\n ▗▄▄▄▄▖    ▗▄▄▄▄▖\n▐▌        ▐▌ \n▐▌ ▝▝▜▌   ▐▌ ▝▝▜▌\n▝▚▄▄▄▞▘   ▝▚▄▄▄▞▘     \n

all: ${NAME} logo

${NAME}: ${O_FILES} ${ARCHIVES}
	${COMPILER} ${LINK_FLAGS} -o ${NAME} ${O_FILES}

%.o: %.c
	${COMPILER} ${CC_FLAGS} ${CC_SECURITY_FLAGS} -c $?

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${O_FILES}

logo:
	@echo "${LOGO}"
	@sleep .25

.PHONY: all re fclean clean libft libft-re libft-clean libft-fclean logo
