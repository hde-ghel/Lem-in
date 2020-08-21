# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hde-ghel <hde-ghel@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/17 16:02:33 by hde-ghel          #+#    #+#              #
#    Updated: 2020/03/05 20:22:44 by hde-ghel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
#FLAGS = -Wall -Werror -Wextra
FLAGS = -fsanitize=address
LIBFT = $(LIBDIR)libft.a
SRCDIR = ./src/
OBJDIR = ./objs
LIBDIR = ./libft/
INCL = ./include/

OBJLIB = $(shell find libft -type f | grep -E "\.o")
FILES = $(shell find src -type f | grep -E "\.c$$" | sed 's/src//g')
SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))
SRCSUBDIR = $(shell find ./src -type d)
OBJSUBDIR = $(SRCSUBDIR:./src%=./objs%)
LONGEST = $(shell echo $(notdir $(SRC)) | tr " " "\n" | \
	awk '{if (lenght > x) {x = lenght; y = $$0}}END{print y}' | wc -c )

colcyan = "\033[96m"
colgreen = "\033[32m"
colred = "\033[32m"
colmag = "\033[1;35m"
colreset = "\033[0;0m"

all: lib $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(INCL)
	@printf $(colmag)
	@printf "Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $<
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]$(colreset)
	@printf "\r"

lib:
	@make -C $(LIBDIR)

$(OBJSUBDIR):
	@mkdir $@

$(NAME): $(OBJSUBDIR) $(OBJ)
	@printf $(colcyan)
	@printf "Lem-in OBJ creation     "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) -I $(INCL)
	@printf "Lem-in OBJ compilation  "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"


clean:
	@rm -rf $(OBJDIR)
	@printf $(colcyan)
	@printf "Deleting Lem-in OBJ     "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"
	@make -C $(LIBDIR) clean
	@printf $(colcyan)
	@printf "Deleting libft OBJ      "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"

fclean: clean
	@rm -rf $(NAME)
	@printf $(colcyan)
	@printf "Deleting lemin          "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"
	@rm -rf $(LIBFT)
	@printf $(colcyan)
	@printf "Deleting libft.a        "
	@printf $(colcyan)[$(colgreen)✔$(colcyan)]
	@printf "                                \n"

re: fclean all

norm:
	@norminette $(SRCDIR) $(INCL)

.PHONY: norm clean fclean re all
