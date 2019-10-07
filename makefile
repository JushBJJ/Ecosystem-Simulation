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
	-DDEBUG\

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

	Organisms_SRC = $(SRC_DIR)Organisms/
	Enviorment_SRC = $(SRC_DIR)Enviorment/
	Debug_SRC = $(SRC_DIR)Debug/

	VPATHX = $(SRC_DIR) $(Organisms_SRC) $(Enviorment_SRC)
	VPATH = $(subst /,\,$(VPATHX))

	# Files
	SRC_FILES = $(wildcard $(Organisms_SRC)*.c $(Enviorment_SRC)*.c $(SRC_DIR)*.c *.c $(Debug_SRC)*.c)
	HEADER_FILES = $(wildcard $(SRC_DIR)*.h $(Enviorment_SRC)*.h $(Organisms_SRC)*.h $(HDR_DIR)*.h)
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

	Organisms_SRC = $(SRC_DIR)Organisms/
	Enviorment_SRC = $(SRC_DIR)Enviorment/
	 = $(SRC_DIR)Win32/
	Debug_SRC = $(SRC_DIR)Debug/

	Current_Directory = $(shell pwd)/

	VPATH = $(SRC_DIR) $(Organisms_SRC) $(Enviorment_SRC)

	# Files
	SRC_FILES = $(wildcard $(Organisms_SRC)*.c $(Enviorment_SRC)*.c $(SRC_DIR)*.c *.c $(Debug_SRC)*.c)
	HEADER_FILES = $(wildcard $(HDR_DIR)*.h)
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

build: $(OBJ_FILESX)
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
debug: build
	gdb -ex "target exec $(EXECUTABLE)" -ex "run"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

run: build
	$(EXECUTABLE)

clean:
	$(rm) $(OBJ_FILES) $(EXECUTABLE)