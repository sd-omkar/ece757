
CC = cc
LD = cc 

# don't modify this line
CCFLAGS = -c -xopenmp -xO3 
LDFLAGS = -xopenmp -xO3

# add other CFLAGS here
# CCFLAGS += -DEXAMPLE

# list your binaries here
BINARIES = hello increment addmatrix 
OPATH = .generated
LINK_MESSAGE = "\033[32;1m\n***Making binary \033[33m%s\033[32m...\n\033[m"
COMPILE_MESSAGE = "\033[32;1m\n*Compiling \033[33m%s\033[32m...\n\033[m"

# list OBJFILES here for each binary
OBJFILES_HELLO = $(OPATH)/hello.o 
OBJFILES_INCREMENT = $(OPATH)/increment.o
OBJFILES_ADDMATRIX = $(OPATH)/matrixmain.o \
					 $(OPATH)/addmatrix.o \
					 $(OPATH)/printmatrix.o

all: $(OPATH) $(BINARIES)
	@printf "\033[34;1m\nMy work here is done.\n\033[m"

$(OPATH):
	@printf "\033[32;1m\nMaking \033[33m$(OPATH)/ \033[32mpath for object files...\n\033[m"
	mkdir $(OPATH)

# binary targets are like this
hello: $(OPATH) $(OBJFILES_HELLO)
	@printf $(LINK_MESSAGE) "hello"
	$(LD) $(LDFLAGS) $(OBJFILES_HELLO) -o hello

increment: $(OPATH) $(OBJFILES_INCREMENT)
	@printf $(LINK_MESSAGE) "increment"
	$(LD) $(LDFLAGS) $(OBJFILES_INCREMENT) -o increment

addmatrix: $(OPATH) $(OBJFILES_ADDMATRIX)
	@printf $(LINK_MESSAGE) "addmatrix"
	$(LD) $(LDFLAGS) $(OBJFILES_ADDMATRIX) -o addmatrix

$(OPATH)/hello.o: hello.c 
	@printf $(COMPILE_MESSAGE) "hello.c"
	$(CC) $(CCFLAGS) hello.c -o $(OPATH)/hello.o

$(OPATH)/increment.o: increment.c
	@printf $(COMPILE_MESSAGE) "increment.c"
	$(CC) $(CCFLAGS) increment.c -o $(OPATH)/increment.o

$(OPATH)/matrixmain.o: matrixmain.c
	@printf $(COMPILE_MESSAGE) "matrixmain.c"
	$(CC) $(CCFLAGS) matrixmain.c -o $(OPATH)/matrixmain.o

$(OPATH)/addmatrix.o: addmatrix.c
	@printf $(COMPILE_MESSAGE) "addmatrix.c"
	$(CC) $(CCFLAGS) addmatrix.c -o $(OPATH)/addmatrix.o

$(OPATH)/printmatrix.o: printmatrix.c
	@printf $(COMPILE_MESSAGE) "printmatrix.c"
	$(CC) $(CCFLAGS) printmatrix.c -o $(OPATH)/printmatrix.o

clean:
	@printf "\033[34;1m\nCleaning up...\n\033[m"
	-rm -rf core* $(BINARIES)
	-rm -rf $(OPATH)
	
