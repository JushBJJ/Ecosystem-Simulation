CFLAGS:=\
	-Wall\
	-Wextra\
	-pedantic\
	-Wshadow\
	-Wpointer-arith\
	-Wcast-align \
	-Wwrite-strings\
	-Wmissing-prototypes\
	-Wmissing-declarations \
	-Wredundant-decls\
	-Wnested-externs\
	-Winline\
	-Wno-long-long \
	-Wconversion\
	-Wstrict-prototypes\

Executable_Name = Simulation

ifdef ComSpec

	# Windows
	rm = erase /F
	Path_Seperator = \\
	PS = $(strip $(Path_Seperator))
	Current_Directory = $(shell cd)/

	# Directories
	BUILD_DIR = ./build/
	SRC_DIR = ./src/
	TEST_DIR = ./test/
	HDR_DIR = $(SRC_DIR)headers/
	Animal_SRC = $(SRC_DIR)Animal/
	Enviorment_SRC = $(SRC_DIR)Enviorment/

	VPATHX = $(SRC_DIR) $(Animal_SRC) $(Enviorment_SRC)
	VPATH = $(subst /,\,$(VPATHX))

	# Files
	SRC_FILES = $(wildcard $(Animal_SRC)*.c $(Enviorment_SRC)*.c $(SRC_DIR)*.c)
	HEADER_FILES = $(wildcard $(SRC_DIR)*.h $(Enviorment_SRC)*.h $(Animal_SRC)*.h $(HDR_DIR)*.h)
	OBJ_FILESX = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))
	OBJ_FILES = $(subst /,\,$(OBJ_FILESX))

	# Compiling and Executable
	CC = gcc
	CFLAGS += -DWindows -I$(HDR_DIR)
	EXECUTABLEX = $(Current_Directory)$(BUILD_DIR)$(Executable_Name).exe
	EXECUTABLE = $(subst /,\,$(EXECUTABLEX))

endif
ifndef ComSpec

	# Linux or similar
	rm = rm -f

	# Directories
	BUILD_DIR = ./build/
	SRC_DIR = ./src/
	HDR_DIR = $(SRC_DIR)headers/
	TEST_DIR = ./test/
	Animal_SRC = $(SRC_DIR)Animal/
	Enviorment_SRC = $(SRC_DIR)Enviorment/
	Current_Directory = $(shell pwd)/

	VPATH = $(SRC_DIR) $(Animal_SRC) $(Enviorment_SRC)

	# Files
	SRC_FILES = $(wildcard $(Animal_SRC)*.c $(Enviorment_SRC)*.c $(SRC_DIR)*.c)
	HEADER_FILES = $(wildcard $(SRC_DIR)*.h $(Enviorment_SRC)*.h $(Animal_SRC)*.h $(HDR_DIR)*.h)
	OBJ_FILES = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))
	OBJ_FILESX = $(OBJ_FILES)

	# Compiling and Executable
	CC = gcc
	EXECUTABLE=$(Current_Directory)$(BUILD_DIR)$(Executable_Name)
	CFLAGS += -DLinux -I$(HDR_DIR)
endif

.PHONY: clean build all debug
.SUFFIX: .c .o
.PRECIOUS: $(SRC_FILES) $(HEADER_FILES)

build: clean $(OBJ_FILESX)
	$(CC) $(CFLAGS) $(OBJ_FILESX) -o $(EXECUTABLE)

info:
	@echo PS: $(PS)
	@echo VPATH: $(VPATH)
	@echo SRC_FILES: $(SRC_FILES)
	@echo OBJ_FILES: $(OBJ_FILES)
	@echo RM: $(rm)
	@echo CFLAGS: $(CFLAGS)
	@echo EXECUTABLE: $(EXECUTABLE)
	@echo OS: $(OS)

debug: CFLAGS+=-DDEBUG -g
debug: all
	gdb -ex "target exec $(EXECUTABLE)" -ex "run"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

run: build
	$(EXECUTABLE)

clean:
	$(rm) $(OBJ_FILES) $(EXECUTABLE)