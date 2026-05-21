#Nombre ejecutable
TARGET = minikernel
#Compilador
CC = gcc
#Flags de compilación
CFLAGS = -Wall -pthread
#Carpeta del proyecto	
SRC_DIR = src
#Lista de archivos fuente
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/queue.c $(SRC_DIR)/cpu.c $(SRC_DIR)/metrics.c
#Archivo objeto
OBJS = $(SRCS:.c=.o)

#Regla defecto
all: $(TARGET)

#Crear Ejecutable Final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
#Crear .o a partir de .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#Limpiar archivos objeto y ejecutable
clean:
	rm -f $(SRC_DIR)/*-o $(TARGET)
#Ejecucion directa
run: $(TARGET)
	./$(TARGET)