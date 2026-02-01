# ==============================================================================
# Configuração para Sorting Benchmark - UNESP
# ==============================================================================

CC = gcc
# O -I include avisa ao GCC para buscar o sorts.h na pasta include
CFLAGS = -Wall -Wextra -g -I include

# Nome do executável
EXEC = sorter

# Caminhos dos arquivos fonte na pasta src
SRC = src/main.c src/sorts.c

# Gera os nomes dos arquivos objeto (.o) automaticamente dentro de src/
OBJ = $(SRC:.c=.o)

# ==============================================================================
# Regras
# ==============================================================================

all: $(EXEC)

# Linkagem final do executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)
	@echo "Executável '$(EXEC)' criado com sucesso!"

# Regra para compilar os arquivos .c em .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos temporários
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
