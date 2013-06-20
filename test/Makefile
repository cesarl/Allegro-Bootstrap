NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror -MMD

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image -lGLU

CPPFLAGS	+=	-I. -I/usr/include/allegro5 -I../src/debug -I../src/manager -I../src/utilities

SRCS		=	../src/debug/ILogger.cpp \
			../src/debug/Exception.cpp \
			../src/manager/Resource.cpp \
			../src/utilities/Vector3d.cpp \
			main.cpp


OBJS		=	$(SRCS:.cpp=.o)

DEPS		=	$(SRCS:.cpp=.d)

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			# @$(CC) $(SRCS) -MMD $(LDFLAGS) $(CPPFLAGS)
			@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(CPPFLAGS)
			@$(ECHO) '\033[1;37;44m> Compiled {\033[4m$(NAME)}\033[0m'

clean		:
			@$(RM) $(OBJS) $(DEPS)
			@$(ECHO) '\033[1;37;41m> Directory cleaned\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[1;37;41m> Remove executable\033[0m'

re		:	fclean all

.PHONY		:	all clean re

-include $(DEPS)
