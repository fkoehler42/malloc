# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 11:46:03 by fkoehler          #+#    #+#              #
#*   Updated: 2016/12/14 16:50:32 by hponcet          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #


SRC =

vpath %.c ./src

FLAGS = -Wall -Werror -Wextra

# FILES
NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so
OBJS = $(SRC:.c=.o)
O2 = $(addprefix $(OPATH), $(OBJS))

# DIRECTORIES
LIBFT = ./libft/
OPATH = ./obj/
INC = ./includes/
LIBINC = $(LIBFT)$(INC)
LIB	= $(LIBFT)libft.a

# PROCESS
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME)

$(NAME): $(LIB) $(O2)
	@ar rc $(NAME) $(O2)
	@ranlib $(NAME)
	@echo "\033[0;32m$(NAME) compilation done !\033[0;m"
	@ln -s $(SYMLINK) $@
	@echo "\033[0;32m$(SYMLINK) symbolic link created !\033[0;m"

$(LIB):
	@echo "\033[0;32mWaiting, libft is in compilation...\033[0;m"
	@make -C $(LIBFT)

$(OPATH)%.o: %.c
	@gcc $(FLAGS) -I $(INC) -I $(LIBINC) -o $@ -c $(NAME)

clean:
	@rm -f $(O2)
	@echo "\033[0;32mObject files deleted !\033[0;m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;32m$(NAME) deleted !\033[0;m"
	-@make fclean -C $(LIBFT)
	@echo "\033[0;32mLibft cleaned.\033[0;m"

re: fclean all
