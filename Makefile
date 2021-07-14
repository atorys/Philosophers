#-------------------------NAME--------------------------/
NAME =		philo
#------------------------SOURCES------------------------/

INCLUDES =	./
VPATH =  	files \
			includes

HEADERS	=	philo.h

#--------------------FILES--------------------------/

FILES =
O_FILES = 	$(addprefix objects/, $(FILES:.c=.o))

#-----------ADDITIONAL--------------------------------/

CFLAGS =	-Wall -Wextra -Werror -O3
W =			\033[38;2;255;255;255
P =			\033[38;2;255;74;150
P2 =		\033[38;2;200;74;180
P3 =		\033[38;2;150;74;210
P4 =		\033[38;2;100;74;240

#-----------RULES-------------------------------------/

.PHONY =	all	clean fclean re


all	:		$(NAME)

$(NAME) :	objects $(O_FILES)
			@$(CC) $(FLAGS) $(O_FILES) -o $(NAME)
			@clear ;
			@printf %s ./$(NAME) | pbcopy


objects :
			@mkdir $@

objects/%.o :	%.c $(HEADERS)
			    gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@


#-------CLEAN

clean :
			@rm -rf objects/
			@echo "removing [objects]"

fclean :	clean
			@rm -f $(NAME)
			@echo "removing [philo]"

re :        fclean all
