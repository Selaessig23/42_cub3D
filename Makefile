#declarations
#variables
CUR_DIR = $(shell pwd)
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Isrcs

#libraries
#add pathes of lib to cflags to find headers easily
LIBFT = libft.a
LIBFT_PATH = $(CUR_DIR)/libft
LIBFT_LIBRARY = $(CUR_DIR)/libft/libft.a
CFLAGS += -Ilibft
MLX_PATH = $(CUR_DIR)/MLX42
MLX42 = $(CUR_DIR)/MLX42/build/libmlx42.a
CFLAGS += -I$(MLX_PATH)

LDFLAGS = -lglfw
#sources
SRCS =	main.c \
			command_line_input_check.c \
			error_handling.c \
			initiate_data.c \
			create_texture.c \
			create_color.c \
			create_map.c \
			map_wallcheck.c \
			enclosure.c \
			free.c \
			parsing_utils.c \
			test.c

#variable substitution		
OBJS = $(SRCS:%.c=obj/%.o)

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

# Modify the linking rule to include LDFLAGS
$(NAME): $(OBJS) $(LIBFT_LIBRARY) $(MLX42)
	$(CC) $(OBJS) $(LIBFT_LIBRARY) $(MLX42) $(LDFLAGS) -o $@
	@echo -- prog created, try it by using ./cub3D \"*.cub\"

#%.o rule will compile one .c file to its correspondig object (.o) file: without this rule it would not update correctly
#automatic variables: $@ = the file name of the target of the rule, $< = the name of the prerequisite
#-p (parent option): This option tells mkdir to create the directory and any necessary parent directories if they do not already exist. It also suppresses error messages if the directory already exists.
#$(@D) is a special variable: if target is a file located in some directory, $(@D) will extract just the directory path from the target, 
#otherwise If the target doesn’t include a directory (i.e., it's in the current directory), $(@D) expands to . (representing the current directory).
obj/%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#The -C option is used to change the directory to the specified path before executing make. In this context, it ensures that make operates in the subfolder, not the current directory.
$(LIBFT_LIBRARY):
	make -C $(LIBFT_PATH)

$(MLX42): 
	@if [ ! -d "$(MLX_PATH)/build" ]; then \
		cmake $(MLX_PATH) -B $(MLX_PATH)/build; \
	fi
	@cmake --build $(MLX_PATH)/build -j4

#clean: This target removes the object files ($(OFILES)).
#f: "force" -->prevents the command from prompting for confirmation
clean:
	@rm -rf obj
	@make -C $(LIBFT_PATH) clean
	@echo -- Deleting All .o

# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)') 
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo -- Deleting executables

#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
