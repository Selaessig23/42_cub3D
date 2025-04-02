#declarations
#variables
CUR_DIR = $(shell pwd)
NAME = cub3D
CC = cc
CFLAGS =  -g -Iinclude -Isrcs

#libraries
#add pathes of lib to cflags to find headers easily
LIBFT = libft.a
LIBFT_PATH = $(CUR_DIR)/libft
LIBFT_LIBRARY = $(CUR_DIR)/libft/libft.a
LIBFT_CREATE = libft.a
CFLAGS += -Ilibft
MLX_PATH = $(CUR_DIR)/MLX42
MLX42 = $(CUR_DIR)/MLX42/build/libmlx42.a
CFLAGS += -I$(MLX_PATH)
LDFLAGS = -lglfw -lm

#sources
SRCS =	main.c \
			parsing/command_line_input_check.c \
			parsing/initiate_data.c \
			parsing/create_texture.c \
			parsing/create_color.c \
			parsing/create_map.c \
			parsing/map_wallcheck.c \
			parsing/map_playercheck.c \
			parsing/enclosure.c \
			parsing/parsing_utils.c \
			initiate_mlx.c \
			handlers.c\
			locomotion.c \
			renderer/minimap/minimap.c \
			renderer/minimap/mm_draw_grid.c \
			renderer/minimap/mm_draw_player.c \
			renderer/cub3d/background.c \
			renderer/cub3d/dda.c \
			renderer/cub3d/texture_cast.c \
			renderer/cub3d/raycasting.c \
			renderer/color_pixel.c \
			vector/vector_add.c  \
			vector/vector_div.c  \
			vector/vector_ln.c   \
			vector/vector_mult.c \
			vector/vector_new.c  \
			vector/vector_norm.c \
			vector/vector_rot.c  \
			vector/vector_sub.c \
			cleanup.c \
			free.c \
			error_handling.c \
			test.c \

#variable substitution
OBJS = $(SRCS:%.c=obj/%.o)

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

# Modify the linking rule to include LDFLAGS
$(NAME): $(LIBFT_LIBRARY) $(MLX42) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBFT_LIBRARY) $(MLX42)
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
#!important to note: if the program can't find any of the dependencies it will do all: always running libft-make (=updating correctly)
# $(LIBFT_LIBRARY): libft
$(LIBFT_LIBRARY): $(LIBFT_CREATE)
	@$(MAKE) -s -C libft


$(LIBFT_CREATE):
#	@echo CREATE OR UPDATE LIBFT

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
	@make -C $(MLX_PATH)/build clean || true
	@echo -- Deleting All .o

# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)')
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	rm -rf $(MLX_PATH)/build
	@echo -- Deleting executables

#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
