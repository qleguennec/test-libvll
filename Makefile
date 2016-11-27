PROJECT		=	test-libvll
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/test-libvll

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g

BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

PRINT		=	@printf COL$(PROJECT)$(END)'\t'
PRPROJ		=	$(subst COL, $(BLUE), $(PRINT))
PRRM		=	$(subst COL, $(CYAN), $(PRINT))

SRCEX		=
SRC			=	$(filter-out $(SRCEX), $(filter %.c, $(shell ls)))
OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))

LIBLINK		=	-lprintf -lvll -lvect -lft
LIBS		=	$(addprefix $(BUILDDIR)/, $(addsuffix .a, $(subst -l, lib, $(LIBLINK))))

all: $(NAME)

$(BUILDDIR)/%.a: %
	$(PRPROJ)
	BINDIR=$(CURDIR)/$(BUILDDIR) BUILDDIR=$(CURDIR)/$(BUILDDIR) \
		make --no-print-directory -C $<

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	$(PRPROJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBS)
	$(PRPROJ)
	$(CC) $(CFLAGS) -L$(BUILDDIR) $(LIBLINK) $(OBJECTS) $(LIBLINK) -o $(NAME)
	@printf "OK\t"$(NAME)'\n'

.PHONY: clean sclean fclean re r ex

clean:
	$(PRRM)
	rm -rf $(BUILDDIR)

sclean:
	$(PRRM)
	rm -rf $(OBJECTS)

fclean: clean
	$(PRRM)
	rm -rf $(NAME)

r: sclean all

ex: r
	$(NAME)

re: fclean all
