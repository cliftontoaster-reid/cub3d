CC = clang
CFLAGS = -Wall -Wextra -Werror -std=gnu17 -pipe
LDFLAGS = -lm -lX11 -lXext
RM ?= rm -rf

MODE ?= debug
ifeq ($(MODE),release)
	CFLAGS  += -O3 -g3 -D_FORTIFY_SOURCE=2
	LDFLAGS += -Wl,-z,relro -Wl,-z,now
else ifeq ($(MODE),debug)
	CFLAGS  += -O0 -g3 -fstack-protector-strong -fstack-clash-protection -Warray-bounds -Wformat-security -fno-omit-frame-pointer
else
	$(error "Invalid MODE specified: $(MODE). Use 'debug' or 'release'.")
endif

FSAN ?= true
ifeq ($(FSAN),true)
	CFLAGS  += -fsanitize=address,undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address,undefined
endif

V ?= false
# if not false or true, error
ifeq ($(V),true)
else ifeq ($(V),false)
else
	$(error "Invalid V specified: $(V). Use 'true' or 'false'.")
endif

SAN_FLAGS =
ifeq ($(FSAN),true)
	SAN_FLAGS = -fsan
endif

# Tools optimization
## Prefer clang, fall back to gcc, then cc
ifneq (, $(shell which clang))
	CC      = clang
else ifneq (, $(shell which gcc))
	CC      = gcc
else
	CC      = cc
endif
## If mold is available, use it as a drop-in replacement for 'ld'
ifneq (, $(shell which mold))
	LDFLAGS += -fuse-ld=mold
endif

# Project
NAME = cub3d
VERSION = 0.1.0-exp.1

# Folders
SRC_DIR = src
TEST_DIR = tests
TARGET = x86_64-linux-gnu
ORIGIN_DIR = target
TROUPLET = $(TARGET)-$(MODE)$(SAN_FLAGS)
OFFICE_DIR = $(ORIGIN_DIR)/$(TROUPLET)
WAREHOUSE_DIR = $(ORIGIN_DIR)/warehouse
TARGET_DIR = $(OFFICE_DIR)/$(NAME)
OBJ_DIR = $(TARGET_DIR)/obj
TEST_OBJ_DIR = $(TARGET_DIR)/tobj
BENCH_OBJ_DIR = $(TARGET_DIR)/bobj
DEP_DIR = $(TARGET_DIR)/dep
BIN_DIR = $(TARGET_DIR)/bin
TMP_DIR = $(TARGET_DIR)/tmp
SCRIPT_DIR = scripts
INC_DIR = include

# Source files
SRC := $(shell find $(SRC_DIR) -type f -name '*.c')
TSRC := $(shell find $(TEST_DIR) -type f -name '*.c')
BSRC := $(shell find bench -type f -name '*.c')
# INC := $(shell find $(INC_DIR) -type f -name '*.h' -not -name '*.int.h')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
DEP := $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRC))
TOBJ := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TSRC))
TDEP := $(patsubst $(TEST_DIR)/%.c,$(DEP_DIR)/%.d,$(TSRC))
BOBJ := $(patsubst bench/%.c,$(BENCH_OBJ_DIR)/%.o,$(BSRC))
BDIR_DEPS := $(patsubst bench/%.c,$(DEP_DIR)/bench/%.d,$(BSRC))
BDEP := $(patsubst bench/%.c,$(DEP_DIR)/bench/%.d,$(BSRC))

# Per-benchmark binaries (one binary per source file in bench/)
BENCH_BINS := $(patsubst bench/%.c,$(BIN_DIR)/bench-%.bench,$(BSRC))

INCLUDE = -I$(INC_DIR)

DIRS = $(OBJ_DIR) $(DEP_DIR) $(BIN_DIR) $(TMP_DIR) $(TEST_OBJ_DIR) $(INCLUDE_OUT) $(BENCH_OBJ_DIR)

# if colours
ifeq ($(shell tput colors 2>/dev/null),256)
	RESET = \033[0m
	BOLD = \033[1m
	RED = \033[31m
	GREEN = \033[32m
	YELLOW = \033[33m
	BLUE = \033[34m
else
	RESET =
	BOLD =
	RED =
	GREEN =
	YELLOW =
	BLUE =
endif

.PHONY: all clean fclean re install uninstall dirs criterion libft bench run_bench

# libft library (cloned from git and built with make)
LIBFT_REPO_URL = https://github.com/cliftontoaster-reid/libft.git
LIBFT_DEPO = $(WAREHOUSE_DIR)/libft
LIBFT_MODULE_DIR = $(OFFICE_DIR)/libft
LIBFT_SRC_DIR = $(LIBFT_MODULE_DIR)/src
LIBFT_ARCHIVE = $(LIBFT_MODULE_DIR)/libft.a
LIBFT_INCLUDE_DIR = $(LIBFT_MODULE_DIR)
INCLUDE += -I$(LIBFT_INCLUDE_DIR)

MLX_REPO_URL = https://github.com/42Paris/minilibx-linux.git
MLX_DEPO = $(WAREHOUSE_DIR)/minilibx
MLX_MODULE_DIR = $(OFFICE_DIR)/minilibx
MLX_SRC_DIR = $(MLX_MODULE_DIR)/src
MLX_ARCHIVE = $(MLX_MODULE_DIR)/libmlx.a
MLX_INCLUDE_DIR = $(MLX_MODULE_DIR)
INCLUDE += -I$(MLX_INCLUDE_DIR)
LDFLAGS += -L$(MLX_MODULE_DIR) -lmlx -lX11 -lXext -lm

# Criterion test framework (precompiled distribution)
# We download the prebuilt tar.xz and extract it into the target install dir
CRITERION_VERSION = 2.4.2
CRITERION_TARBALL_URL = https://github.com/Snaipe/Criterion/releases/download/v$(CRITERION_VERSION)/criterion-$(CRITERION_VERSION)-linux-x86_64.tar.xz
CRITERION_DEPO = $(WAREHOUSE_DIR)/criterion
CRITERION_MODULE_DIR = $(OFFICE_DIR)/criterion
CRITERION_TMP_DIR = $(CRITERION_MODULE_DIR)/tmp
CRITERION_TARBALL = $(CRITERION_TMP_DIR)/criterion-$(CRITERION_VERSION)-linux-x86_64.tar.xz
CRITERION_INSTALL_DIR = $(CRITERION_MODULE_DIR)/bin

all: dirs $(NAME)

-include $(DEP)

# It is a file that tells make which version is currently linked
# If it was release and you attempt debug, it will see the file is missing
# then it will delete the other file flags and build the correct one
.linkflag_$(TROUPLET):
	@$(RM) -f .linkflag_*
	@touch $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ${LIBFT_ARCHIVE} ${MLX_ARCHIVE}
	@mkdir -p $(@D) $(dir $(DEP_DIR)/$*.d)
	@$(CC) $(CFLAGS) -fPIC -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@ $(INCLUDE) -D 'VERSION="$(VERSION)"'
	@if [ "$(V)" = "true" ]; then \
		echo -e "$(BOLD)Compiled$(RESET) $(BLUE)$<$(RESET) -> $(GREEN)$@$(RESET) $(BOLD)$(RED)$(DEP_DIR)/$*.d$(RESET)"; \
	fi

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c ${LIBFT_ARCHIVE} ${MLX_ARCHIVE} ${CRITERION_INSTALL_DIR}
	@mkdir -p $(@D) $(dir $(DEP_DIR)/$*.d)
	@$(CC) $(CFLAGS) -fPIC -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@ $(INCLUDE) -I$(CRITERION_INSTALL_DIR)/include
	@if [ "$(V)" = "true" ]; then \
		echo -e "$(BOLD)Compiled$(RESET) $(YELLOW)test$(RESET) $(BLUE)$<$(RESET) -> $(GREEN)$@$(RESET) $(BOLD)$(RED)$(DEP_DIR)/$*.d$(RESET)"; \
	fi

$(BENCH_OBJ_DIR)/%.o: bench/%.c ${LIBFT_ARCHIVE} ${MLX_ARCHIVE} ${CRITERION_INSTALL_DIR}
	@mkdir -p $(@D) $(dir $(DEP_DIR)/bench/$*.d)
	@$(CC) $(CFLAGS) -fPIC -MMD -MP -MF $(DEP_DIR)/bench/$*.d -c $< -o $@ $(INCLUDE) -I$(CRITERION_INSTALL_DIR)/include
	@if [ "$(V)" = "true" ]; then \
		echo -e "$(BOLD)Compiled$(RESET) $(YELLOW)bench$(RESET) $(BLUE)$<$(RESET) -> $(GREEN)$@$(RESET) $(BOLD)$(RED)$(DEP_DIR)/bench/$*.d$(RESET)"; \
	fi

$(BIN_DIR)/$(NAME): $(OBJ)  $(INCLUDED_FILES)
	@$(CC) -o "$@" $(OBJ) $(LIBFT_ARCHIVE) $(LDFLAGS) -D 'VERSION=\"$(VERSION)\"'
	@echo -e "$(BOLD)Linked$(RESET) $(NAME)"

$(NAME): .linkflag_$(TROUPLET) $(BIN_DIR)/$(NAME)
	@cp $(BIN_DIR)/$(NAME) ./$(NAME)
	@echo -e "$(BOLD)Copied$(RESET) $(GREEN)$(NAME)$(RESET) to project root."

dirs:
	@$(foreach d, $(DIRS), mkdir -p "$(d)";)

clean:
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@echo -e "$(BOLD)Removed object and dependency files.$(RESET)"

fclean: clean
	@$(RM) -r $(ORIGIN_DIR)
	@echo -e "$(BOLD)Removed target directory.$(RESET)"
	@$(RM) ./$(NAME) .linkflag_*
	@echo -e "$(BOLD)Removed link flag.$(RESET)"

re: fclean all

# Download and extract precompiled Criterion for running tests
criterion: $(CRITERION_INSTALL_DIR)

$(CRITERION_INSTALL_DIR):
	@mkdir -p "$(CRITERION_TMP_DIR)" "$(CRITERION_INSTALL_DIR)"
	@# Download tarball if missing, silently
	@if [ ! -f "$(CRITERION_TARBALL)" ]; then \
		if command -v curl >/dev/null 2>&1; then \
			curl -L -o "$(CRITERION_TARBALL)" "$(CRITERION_TARBALL_URL)" > /dev/null 2>&1; \
		else \
			wget -O "$(CRITERION_TARBALL)" "$(CRITERION_TARBALL_URL)" > /dev/null 2>&1; \
		fi; \
	fi
	@# Extract into the install dir (overwrite if necessary)
	@tar -xJf "$(CRITERION_TARBALL)" -C "$(CRITERION_INSTALL_DIR)" --strip-components=1
	@echo -e "$(BOLD)Criterion v$(CRITERION_VERSION) installed to:$(RESET) $(GREEN)$(CRITERION_INSTALL_DIR)$(RESET)"

# Clone and build libft library
libft: $(LIBFT_ARCHIVE)
mlx: $(MLX_ARCHIVE)

$(LIBFT_ARCHIVE):
	@echo -e "$(BOLD)Building libft library...$(RESET)"
	@mkdir -p "$(LIBFT_MODULE_DIR)"
	@# Clone libft if not already present
	@if [ ! -d "$(LIBFT_MODULE_DIR)/.git" ]; then \
		git clone "$(LIBFT_REPO_URL)" "$(LIBFT_MODULE_DIR)" > /dev/null 2>&1; \
	fi
	@# Build libft with make fully silently
	@$(MAKE) -C "$(LIBFT_MODULE_DIR)" all OBJ_DIR="$(LIBFT_MODULE_DIR)/target" CACHE_DIR="$(LIBFT_MODULE_DIR)/cache" CC="$(CC)" CFLAGS="$(CFLAGS)" > /dev/null 2>&1
	@echo -e "$(BOLD)Built libft:$(RESET) $(GREEN)$(LIBFT_ARCHIVE)$(RESET)"

$(MLX_ARCHIVE):
	@echo -e "$(BOLD)Building minilibx library...$(RESET)"
	@mkdir -p "$(MLX_MODULE_DIR)"
	@# Clone minilibx if not already present
	@if [ ! -d "$(MLX_MODULE_DIR)/.git" ]; then \
		git clone "$(MLX_REPO_URL)" "$(MLX_MODULE_DIR)" > /dev/null 2>&1; \
	fi
	@# Build minilibx with make fully silently
	@$(MAKE) -C "$(MLX_MODULE_DIR)" all CC="$(CC)" > /dev/null 2>&1
	@echo -e "$(BOLD)Built minilibx:$(RESET) $(GREEN)$(MLX_ARCHIVE)$(RESET)"

test: criterion all $(TOBJ) $(TDEP)
	@$(CC) -o $(BIN_DIR)/$(NAME).test $(TOBJ) $(filter-out $(OBJ_DIR)/main.o,$(OBJ)) -L$(CRITERION_INSTALL_DIR)/lib -lcriterion $(LDFLAGS) -lXtst -D 'VERSION=\"$(VERSION)\"' \
		$(LIBFT_ARCHIVE) $(MLX_ARCHIVE)
	@echo -e "$(BOLD)Linked test executable:$(RESET) $(GREEN)$(BIN_DIR)/$(NAME).test$(RESET)"

run_test/%:
	@echo "Running tests in virtual X11 display ($*-bit depth)..."
	@export DISPLAY_DEPTH=$* && LD_LIBRARY_PATH=$(BIN_DIR):$(CRITERION_INSTALL_DIR)/lib xvfb-run --auto-servernum --server-args='-screen 0 1024x768x$*' $(BIN_DIR)/$(NAME).test --V

run_tests: test
	$(MAKE) run_test/24
	@echo "All tests completed."

bench: criterion all $(BENCH_BINS)

$(BIN_DIR)/bench-%.bench: $(BENCH_OBJ_DIR)/%.o $(filter-out $(OBJ_DIR)/main.o,$(OBJ)) ${LIBFT_ARCHIVE} ${MLX_ARCHIVE} ${CRITERION_INSTALL_DIR}
	@$(CC) -o $@ $(BENCH_OBJ_DIR)/$*.o $(filter-out $(OBJ_DIR)/main.o,$(OBJ)) $(LDFLAGS) -D 'VERSION="$(VERSION)"' \
		$(LIBFT_ARCHIVE) $(MLX_ARCHIVE)
	@echo -e "$(BOLD)Linked bench executable:$(RESET) $(GREEN)$@$(RESET)"

run_bench/%:
	@echo "Running benchmark"
	@./$(BIN_DIR)/bench-$*.bench

run_bench:
	@$(MAKE) bench MODE=release FSAN=false
	@echo -e "$(BOLD)Bench binaries built:$(RESET) $(GREEN)$(BENCH_BINS)$(RESET)"
	@for b in $(BENCH_BINS); do \
		echo -e "$(BOLD)Running bench:$(RESET) $$b"; \
		"$$b"; \
	done

format:
	@echo "Formatting source files with clang-format..."
	@find $(SRC_DIR) $(INC_DIR) $(TEST_DIR) -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
	@echo "Source files formatted."

compile_commands.json: Makefile $(SRC) $(INC)
	@echo "Generating compile_commands.json ..."
	@bear -- $(MAKE) fclean all CC=clang
	@echo "compile_commands.json generated."

make_perf_maps: $(TMP_DIR)/genMap
	@echo "Generating performance maps for use with Linux perf..."
	@ s=8; while [ $$s -le 512 ]; do \
		$(TMP_DIR)/genMap $$s $$s assets/maps/perf/$${s}_[0..2999].cub; \
		s=$$((s*2)); \
	done
	@echo "Performance maps generated in $(TARGET_DIR)/maps."

$(TMP_DIR)/genMap: $(SCRIPT_DIR)/genMapClaude.go
	@mkdir -p $(TMP_DIR)
	@echo "Building genMap (optimized): $(TMP_DIR)/genMap"
	@# Build with trimmed paths and stripped symbols for maximum practical optimization/size reduction
	@CGO_ENABLED=0 go build -trimpath -ldflags="-s -w" -o $(TMP_DIR)/genMap $(SCRIPT_DIR)/genMapClaude.go
	@echo "Built $(TMP_DIR)/genMap"