# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#    Updated: 2017/09/21 18:51:41 by fkoehler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FILES
SRC = allocation.c \
	block_infos.c \
	blocks.c \
	data_protection.c \
	deallocation.c \
	malloc.c \
	zone_infos.c \
	zones.c

NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so
OBJS = $(SRC:.c=.o)
O2 = $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
vpath %.c ./src
LIBPATH = ./libft/
OPATH = ./obj/
INC = ./includes/
LIBINC = $(LIBPATH)$(INC)
LIB	= $(LIBPATH)libft.a

# COMPILATION
CC = gcc
FLAGS = -Wall -Werror -Wextra

# PROCESS
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME)

$(NAME): $(LIB) $(O2)
	@ar rc $(NAME) $(O2)
	@ranlib $(NAME)
	@echo "\033[0;34m$(NAME) compilation done !\033[0;m"
	@ln -s $@ $(SYMLINK)
	@echo "\033[0;34m$(SYMLINK) symbolic link created !\033[0;m"

$(LIB):
	@echo "\033[0;34mWaiting, libft is in compilation...\033[0;m"
	@make -C $(LIBPATH)

$(OPATH)%.o: %.c
	@$(CC) $(FLAGS) -I $(INC) -I $(LIBINC) -c $< -o $@

clean:
	@rm -f $(O2)
	@echo "\033[0;34mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME) $(SYMLINK)
	@echo "\033[0;34m$(NAME) and $(SYMLINK) deleted !\033[0;m"
	-@make fclean -C $(LIBPATH)
	@echo "\033[0;34mLibft cleaned.\033[0;m"

re: fclean all
