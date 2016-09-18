#comentarios!
#agregar -O2 a los flags!

CC=gcc
CFLAGS=-c -Wall -pedantic -O2
OBJECTS=main.o printHeader.o getSupFs.o getBootTime.o parseFile.o functionOpt.o
PATHOBJECTS=$(addprefix $(ODIR)/,$(OBJECTS))
ODIR=obj
LDIR=include
SRCDIR=src

all: ksamp cppcheck

ksamp: $(OBJECTS)
	@echo
	@echo Linkeando objetos
	$(CC) $(PATHOBJECTS) -o $@

cppcheck:
	@echo
	@echo Realizando verificacion CppCheck
	@echo Los resultados de la misma se encuentran en err.txt
	cppcheck . 2> err.txt

main.o: $(SRCDIR)/main.c $(LDIR)/ksamp.h
	@echo
	@echo Compilando codigos fuente
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

printHeader.o: $(SRCDIR)/printHeader.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getSupFs.o: $(SRCDIR)/getSupFs.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

getBootTime.o: $(SRCDIR)/getBootTime.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

parseFile.o: $(SRCDIR)/parseFile.c
	$(CC) $(CFLAGS) $^ -o $(ODIR)/$@

functionOpt.o: $(SRCDIR)/functionOpt.c $(LDIR)/ksamp.h
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

clean:
	@echo Borrando archivos objeto, ksamp compilado y log de errores
	rm -rf *o $(ODIR)/*.o ksamp $(LDIR)/*.gch err.txt
