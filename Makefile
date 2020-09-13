# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: floris <marvin@42.fr>                        +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/11 12:44:37 by floris        #+#    #+#                  #
#    Updated: 2020/09/11 20:27:42 by mvan-eng      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VM_LOC = ./srcs/vm/
VM_NAME = corewar

ASM_LOC = ./srcs/asm
ASM_NAME = $(ASM_LOC)/asm

all: $(VM_NAME) $(ASM_NAME)

corewar:
	make -C $(VM_LOC)
	cp $(VM_LOC)$(VM_NAME) .

$(ASM_NAME):
	make -C $(ASM_LOC)

fclean: clean
	@make -C $(VM_LOC) fclean
	@make -C $(ASM_LOC) fclean

clean:
	@make -C $(VM_LOC) fclean
	@make -C $(ASM_LOC) fclean
	
re: fclean all
