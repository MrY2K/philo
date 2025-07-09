##########################################################################################################
#                                         >   PHILOSOPHERS    <                                          #
##########################################################################################################
################################################ MANDATORY #############################################

################################################
#                 DIRECTORIES                  #
################################################

SRC_DIR      = src
HELPER_DIR   = $(SRC_DIR)/helpers
BUILD_DIR    = $(SRC_DIR)/build
INCLUDE_DIR  = $(SRC_DIR)/include

################################################
#                  FILES                       #
################################################

NAME         = philo

# Define source files and their dependencies
SRCS         = $(SRC_DIR)/main.c \
				$(HELPER_DIR)/error_managment.c \
				$(HELPER_DIR)/utils.c \
				$(HELPER_DIR)/utils_2.c \
				$(SRC_DIR)/01_input_managment.c \
				$(SRC_DIR)/02_init.c \
				$(SRC_DIR)/03_routines.c \
				$(SRC_DIR)/04_routines.c \
				$(SRC_DIR)/05_routines.c

HEADER		 = $(INCLUDE_DIR)/philo.h \
				$(INCLUDE_DIR)/includes.h \
				$(INCLUDE_DIR)/prototypes.h \
				$(INCLUDE_DIR)/structs.h


OBJS         = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS         = $(OBJS:.o=.d)

################################################
#             COMPILER SETTINGS                #
################################################

CC           = cc
# CFLAGS       = -Wall -Wextra -Werror # -Ofast -fsanitize=address -Wunreachable-code -fsanitize=thread

CFLAGS       = -Wall -Wextra -Werror -Wunreachable-code -pthread -g -fsanitize=thread
# CFLAGS       = -Wall -Wextra -Werror -Wunreachable-code -pthread 
# CFLAGS       = -Wall -Wextra -Werror -Wunreachable-code -pthread -g -fsanitize=address


################################################
#                   RULES                      #
################################################

all: $(BUILD_DIR) $(NAME) $(HEADER)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "$(GREEN)Created build directory$(RESET)"

# Linking
$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDE_DIR) -o $(NAME)
	@echo "$(GREEN)Built $(RESET)"
	@echo "$${PHILO_ART}"

# Compiling into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

################################################
#                 CLEANING                     #
################################################

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(RED)Cleaned build directory$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed executable$(RESET)"

re: fclean all

################################################
#                 .PHONY                       #
################################################

.PHONY: clean

################################################
#                 COLORS                       #
################################################

GREEN = \033[0;32m
RED   = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

define PHILO_ART
$(YELLOW)▄▄▄▄  ▐▌   ▄ █  ▄▄▄   ▄▄▄  ▄▄▄  ▄▄▄▄  ▐▌   ▗▞▀▚▖ ▄▄▄ ▄▄▄ $(RESET)
$(YELLOW)█   █ ▐▌   ▄ █ █   █ ▀▄▄  █   █ █   █ ▐▌   ▐▛▀▀▘█   ▀▄▄  $(RESET)
$(YELLOW)█▄▄▄▀ ▐▛▀▚▖█ █ ▀▄▄▄▀ ▄▄▄▀ ▀▄▄▄▀ █▄▄▄▀ ▐▛▀▚▖▝▚▄▄▖█   ▄▄▄▀ $(RESET)
$(YELLOW)█     ▐▌ ▐▌█ █                  █     ▐▌ ▐▌              $(RESET)
$(YELLOW)▀                               ▀                        $(RESET)
endef

export PHILO_ART
                                                    