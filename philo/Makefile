CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

NAME = philo

INCLUDES = ./includes/
HEADER = $(INCLUDES)philosopher.h

SRCS_DIR = ./
SRCS = \
	$(SRCS_DIR)about_time.c		\
	$(SRCS_DIR)dining.c			\
	$(SRCS_DIR)exception.c		\
	$(SRCS_DIR)ft_atoi.c			\
	$(SRCS_DIR)init.c		\
	$(SRCS_DIR)main.c			\
	$(SRCS_DIR)print_act.c			\
	$(SRCS_DIR)thread.c	\
	$(SRCS_DIR)monitor.c	\
	
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) $^ -o $(NAME)


%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : 
	make clean
	rm -f $(NAME) 

re :
	make fclean 
	make all

.PHONY : all clean fclean re