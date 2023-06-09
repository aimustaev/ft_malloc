# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimustaev <aimustaev@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:07:02 by aimustaev         #+#    #+#              #
#    Updated: 2023/05/09 12:40:56 by aimustaev        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################## HOST ############################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

############################## VAR #############################################

NAME = libft_malloc.so

HOSTLIB = libft_malloc_$(HOSTTYPE).so

SRC = calloc.c \
	find_header.c \
	free.c \
	init_malloc.c \
	malloc.c \
	mmaps.c \
	realloc.c \
	show_alloc_mem.c \
	mutex.c

SRCDIR = src/

OBJDIR = obj

CFLAGS = -Wall -Wextra -g -Werror

LDFLAGS = -shared

DEP = libft/incl/libft.h \
	includes/malloc.h \
	includes/malloc_struct.h

CC = gcc

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

LIB = -Llibft -lft

LIB_TEST = -L . -lft_malloc

INCL = -I libft/incl -I includes

############################## COLORS ##########################################

BY = "\033[33;1m"
BR = "\033[31;1m"
BG = "\033[32;1m"
BB = "\033[34;1m"
BM = "\033[35;1m"
BC = "\033[36;1m"
BW = "\033[37;1m"
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
C = "\033[36m"
M = "\033[35m"
KW = "\033[37;5m"
KR = "\033[31;5m"
KG = "\033[32;5m"
KB = "\033[34;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

############################## RULES ###########################################

all: ${NAME}
	@echo ${G}Success"   "[${NAME}]${X}

libft/%:
	@make -C libft

${NAME}: ${HOSTLIB}
	@echo ${C}Linking"   "[${HOSTLIB}]...${X}
	@ln -fs ${HOSTLIB} ${NAME}

${HOSTLIB}: ${OBJ} ${DEP} libft/libft.a
	@echo ${B}Compiling [${HOSTLIB}]...${X}
	@${CC} ${LDFLAGS} ${LIB} ${INCL} -o $@ ${OBJ}

${OBJDIR}/%.o: ${SRCDIR}%.c ${DEP} libft/libft.a
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} ${INCL} -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	@/bin/rm -f ${NAME}
	@/bin/rm -f ${HOSTLIB}

test: libft/libft.a ${NAME}
	@${CC} ${INCL} ${LIB_TEST} test.c -o test
	@./run.sh ./test

bench: libft/libft.a ${NAME}
	@${CC} ${INCL} ${LIB_TEST} test.c -o test
	@./run.sh /usr/bin/time -l ./test
# &| grep 'page reclaims's

re: fclean all

.PHONY: all clean fclean re test test
