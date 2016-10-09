#comentarios!
#agregar -O2 a los flags!

CC=gcc
CFLAGS=-c -Wall -pedantic -O2
OBJECTS=main.o split_line.o read_line.o execute.o launch.o builtins.o
PATHOBJECTS=$(addprefix $(ODIR)/,$(OBJECTS))
ODIR=obj
LDIR=include
SRCDIR=src

all: shell cppcheck

shell: $(OBJECTS)
	@echo
	@echo Linkeando objetos
	$(CC) $(PATHOBJECTS) -o $@

cppcheck:
	@echo
	@echo Realizando verificacion CppCheck
	@echo Los resultados de la misma se encuentran en err.txt
	cppcheck . 2> err.txt

main.o: $(SRCDIR)/main.c $(LDIR)/main_includes.h
	@echo
	@echo Compilando codigos fuente
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

split_line.o: $(SRCDIR)/split_line.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

read_line.o: $(SRCDIR)/read_line.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

execute.o: $(SRCDIR)/execute.c $(LDIR)/builtins.h $(LDIR)/launch.h
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

builtins.o: $(SRCDIR)/builtins.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

launch.o: $(SRCDIR)/launch.c
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@


clean:
	@echo Borrando archivos objeto, ksamp compilado y log de errores
	rm -rf *o $(ODIR)/*.o shell $(LDIR)/*.gch err.txt
