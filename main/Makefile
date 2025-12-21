# =========================
# Toolchain
# =========================
CC      = gcc
FLEX    = flex
BISON   = bison

# =========================
# Directories
# =========================
SRC_DIR     = src
LEXER_DIR   = $(SRC_DIR)/lexer
PARSER_DIR  = $(SRC_DIR)/parser
SEM_DIR     = $(SRC_DIR)/semantic
BUILD_DIR   = build
TEST_DIR    = tests

# =========================
# Sources
# =========================
LEX_SRC     = $(LEXER_DIR)/lexer.l
YACC_SRC    = $(PARSER_DIR)/parser.y

OBJS        = $(BUILD_DIR)/parser.tab.o \
              $(BUILD_DIR)/lex.yy.o \
              $(BUILD_DIR)/symtable.o \
              $(BUILD_DIR)/quadruple.o

TARGET      = $(BUILD_DIR)\compiler.exe

CFLAGS      = -Wall -g -I$(BUILD_DIR) -I$(SEM_DIR)

# =========================
# Default target
# =========================
all: $(BUILD_DIR) $(TARGET)

# =========================
# Link
# =========================
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# =========================
# Bison (MUST run first)
# =========================
$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: $(YACC_SRC) | $(BUILD_DIR)
	$(BISON) -d $(YACC_SRC)
	cmd /c move /Y parser.tab.c $(BUILD_DIR)
	cmd /c move /Y parser.tab.h $(BUILD_DIR)

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Flex (depends on parser.tab.h)
# =========================
$(BUILD_DIR)/lex.yy.c: $(LEX_SRC) $(BUILD_DIR)/parser.tab.h | $(BUILD_DIR)
	$(FLEX) $(LEX_SRC)
	cmd /c move /Y lex.yy.c $(BUILD_DIR)

$(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Semantic sources
# =========================
$(BUILD_DIR)/symtable.o: $(SEM_DIR)/symtable.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/quadruple.o: $(SEM_DIR)/quadruple.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Utilities
# =========================
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

clean:
	cmd /c del /Q lex.yy.c parser.tab.c parser.tab.h 2>nul
	cmd /c del /Q $(BUILD_DIR)\*.o $(BUILD_DIR)\compiler.exe 2>nul

test: $(TARGET)
	@for %%f in ($(TEST_DIR)\*.c) do ( \
		echo Running %%f && \
		$(TARGET) < %%f \
	)

.PHONY: all clean test
