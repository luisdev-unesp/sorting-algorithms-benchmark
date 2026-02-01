# ==============================================================================
# Variáveis de Configuração para Sorting Benchmark
# ==============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -g -I include

# Nome do executável final para este projeto
EXEC = sorter

# Arquivos fonte (dentro da pasta src)
# Adicione aqui todos os nomes dos seus arquivos .c desse projeto
SRC = src/main.c src/ordenacao.c 

# Gera a lista de arquivos objeto (.o) automaticamente
OBJ = $(SRC:.c=.o)

# ==============================================================================
# Regras de Compilação
# ==============================================================================

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)
	@echo "Executável '$(EXEC)' criado com sucesso!"

# Regra genérica para transformar .c em .o considerando a pasta src
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpando arquivos objeto e executável..."
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
