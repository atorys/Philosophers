#-------------------------NAME--------------------------/
NAME =		philo
#------------------------SOURCES------------------------/

INCLUDES =	./
VPATH =  	files \
			includes

HEADERS	=	philo.h

#--------------------FILES--------------------------/

FILES =		main.c \
			initialization.c \
			life.c \
			utils.c
O_FILES = 	$(addprefix objects/, $(FILES:.c=.o))

#-----------ADDITIONAL--------------------------------/

CFLAGS =	-Wall -Wextra -Werror -O3
W =			\033[38;2;255;255;255
WD =		\033[38;2;100;100;100
P = 		"\\"

#-----------RULES-------------------------------------/

.PHONY =	all	clean fclean re


all	:		$(NAME)

$(NAME) :	objects $(O_FILES)
			@$(CC) $(FLAGS) $(O_FILES) -o $(NAME)
			@clear ; echo "$(W);1m\n                                   compiling"; sleep 0.2; clear; echo "\n                                   compiling ."; sleep 0.2 ;clear ; echo "\n                                   compiling . . "; sleep 0.2; clear ; echo "\n                                   compiling . . .\n"; sleep 0.8;
			@echo "$(W);1m               /\        /\                            /\  ";
			@echo "       ___    / /_      / / ___    ____  ___   ___    / /_   ____  ___     ____ ";
			@echo "      / __ \ / __ \ /\ / // __ \  / /  / __ \ / __ \ / __ \ /\__  / __ \  / /  ";
			@echo "     / /_/ // / / // // // /_/ / _\ \ / /_/ // /_/ // / / // /__ / /_/ / _\ \  ";
			@echo "    /  __ //_/$(WD);1m /$(W);1m\//_//_/ \____//____/ \____//  __ //_/ $(WD);1m/$(W);1m\/ \___//_/\__\/____/$(WD);1m// ";
			@echo "   $(W);1m/ /$(WD);1m$(P)$(P)$(P)$(P)$(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)/  $(P)$(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)$(P)$(P)/ $(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P)/ $(P)$(P)$(P)$(P)$(P) $(W);1m/ /$(WD);1m$(P)$(P)$(P)$(P)$(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)/  $(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)$(P)$(P) $(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P) $(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P)$(P)/";
			@echo "   $(W);1m\/$(WD);1m//                                    $(W);1m\/$(WD);1m// ";
			@echo "   $(W);1m\n                     [ press CMD+V to start simulation]\n";
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
