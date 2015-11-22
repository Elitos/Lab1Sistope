#DIR_OUTPUT
#DIR_SRC
#NAME_EXEC
main: src/main.o src/functionsfather.o src/functionschild.o
	@gcc -o build/main -I src/ src/main.o src/functionsfather.o 
	@gcc -o build/child -I src/ src/functionschild.o
	@rm src/*.o
	@echo "Compilacion realizada"
	
build/main.o: src/main.c
	@gcc -o src/main.o src/main.c -c

build/functionfather.o: src/functionsfather.c
	@gcc -o src/functionsfather.o src/functionsfather.c -c

build/functionschild.o: src/functionschild.c
	@gcc -o src/functionschild.o src/functionschild.c -c
