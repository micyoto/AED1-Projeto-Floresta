# Makefile

# Nome do executável
exec = simula

# Compilador e flags
CC      = gcc
CFLAGS  = -Iinclude -Wall -Wextra -std=c11
LDFLAGS =

# Fontes e objetos
SRCS = src/main.c src/entrada_saida.c src/fogo.c src/animal.c
OBJS = $(SRCS:.c=.o)

# Regra padrão: compila tudo
default: all

all: $(exec)

$(exec): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regra genérica para .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o programa
run: $(exec)
	./$(exec)

# Limpeza de artefatos
authclean: clean

clean:
	rm -f $(OBJS) $(exec) output.dat

.PHONY: all run clean default
