# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etisha <etisha@student.21-school.>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 18:03:10 by etisha            #+#    #+#              #
#    Updated: 2021/12/27 18:03:16 by etisha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

HEADER = minitalk.h

SERVER = server

SRC_FILES_SERVER = server.c

CLIENT = client

SRC_FILES_CLIENT = client.c

OBJ_BONUS = server_bonus.o client_bonus.o

RM = rm -f

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRC_FILES_SERVER:.c=.o)
	$(CC) $(CFLAGS) -o $@ $<

$(CLIENT): $(SRC_FILES_CLIENT:.c=.o)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRC_FILES_SERVER:.c=.o) $(SRC_FILES_CLIENT:.c=.o) $(OBJ_BONUS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

bonus:
	make SRC_FILES_SERVER="server_bonus.c" SRC_FILES_CLIENT="client_bonus.c" all

.PHONY: all clean fclean re bonus
