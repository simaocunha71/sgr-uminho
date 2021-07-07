FLAGS= -std=c99 -Wall -Wextra -O2 -D_GNU_SOURCE
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=src
OBJ=obj
MODEL=model
CONTROLLER=controller
VIEW=view

program: show table user business review hashes reading hashcontrol sgr interpreter prog allprog
test: table user business review hashes reading hashcontrol sgr alltest

# Build show.o (requires show.c, show.h to exist)
show: $(SRC)/$(VIEW)/show.c $(INCLUDES)/$(VIEW)/show.h
	   @echo "> Compilando Show."
	   $(COMPILER) $(FLAGS) -o $(OBJ)/show.o -c $(SRC)/$(VIEW)/show.c

# Build table.o (requires table.c, table.h to exist)
table: $(SRC)/$(VIEW)/table.c $(INCLUDES)/$(VIEW)/table.h $(OBJ)/show.o
	   @echo "> Compilando Table."
	   $(COMPILER) $(FLAGS) -o $(OBJ)/table.o -c $(SRC)/$(VIEW)/table.c

# Build user.o (requires user.c and user.h)
user: $(SRC)/$(MODEL)/user.c $(INCLUDES)/$(MODEL)/user.h
	  @echo "> Compilando User."
	  $(COMPILER) $(FLAGS) -o $(OBJ)/user.o -c $(SRC)/$(MODEL)/user.c

# Build business.o (requires business.c and business.h)	
business: $(SRC)/$(MODEL)/business.c $(INCLUDES)/$(MODEL)/business.h
	      @echo "> Compilando Business."
	      $(COMPILER) $(FLAGS) -o $(OBJ)/business.o -c $(SRC)/$(MODEL)/business.c

# Build review.o (requires review.c and review.h)	
review: $(SRC)/$(MODEL)/review.c $(INCLUDES)/$(MODEL)/review.h
	    @echo "> Compilando Review."
	    $(COMPILER) $(FLAGS) -o $(OBJ)/review.o -c $(SRC)/$(MODEL)/review.c

# Build reading.o (requires hashes.c, hashes.h, user.o, business.o, review.o and glib package to exist)
hashes: $(SRC)/$(MODEL)/hashes.c $(INCLUDES)/$(MODEL)/hashes.h $(OBJ)/user.o $(OBJ)/business.o $(OBJ)/review.o 
	  @echo "> Compilando Hashes."
	  $(COMPILER) $(FLAGS) -o $(OBJ)/hashes.o $(PKG) -c $(SRC)/$(MODEL)/hashes.c

# Build reading.o (requires reading.c, reading.h, user.o, business.o, review.o, hashes.o)
reading: $(SRC)/$(MODEL)/reading.c $(INCLUDES)/$(MODEL)/reading.h
	  @echo "> Compilando Reading."
	  $(COMPILER) $(FLAGS) -o $(OBJ)/reading.o $(PKG) -c $(SRC)/$(MODEL)/reading.c

# Build sgr.o (requires user.o, business.o, review.o and glib package to exist)	
hashcontrol: $(SRC)/$(CONTROLLER)/hashcontrol.c $(INCLUDES)/$(CONTROLLER)/hashcontrol.h $(OBJ)/hashes.o
	 @echo "> Compilando Hashescontrol."
	 $(COMPILER) $(FLAGS) -o $(OBJ)/hashcontrol.o $(PKG) -c $(SRC)/$(CONTROLLER)/hashcontrol.c

# Build sgr.o (requires user.o, business.o, review.o and glib package to exist)	
sgr: $(SRC)/$(CONTROLLER)/sgr.c $(INCLUDES)/$(CONTROLLER)/sgr.h $(OBJ)/reading.o $(OBJ)/hashcontrol.o
	 @echo "> Compilando Sgr."
	 $(COMPILER) $(FLAGS) -o $(OBJ)/sgr.o $(PKG) -c $(SRC)/$(CONTROLLER)/sgr.c

# Build interpreter.o (requires sgr.o to exist)	
interpreter: $(SRC)/$(CONTROLLER)/interpreter.c $(INCLUDES)/$(CONTROLLER)/interpreter.h $(OBJ)/sgr.o $(OBJ)/show.o
	 @echo "> Compilando Interpreter."
	 $(COMPILER) $(FLAGS) -o $(OBJ)/interpreter.o $(PKG) -c $(SRC)/$(CONTROLLER)/interpreter.c

# Build main.o (requires sgr.o and glib package to exist)
prog: $(SRC)/main.c $(OBJ)/sgr.o $(OBJ)/table.o
	  @echo "> Compilando Programa."
	  $(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c	

# Build the executable 'program' depends on all 5 object files
allprog: $(OBJ)/main.o $(OBJ)/sgr.o $(OBJ)/hashcontrol.o $(OBJ)/reading.o $(OBJ)/hashes.o $(OBJ)/user.o $(OBJ)/review.o $(OBJ)/business.o $(OBJ)/table.o $(OBJ)/show.o
	     @echo "> Compilando Todo o Programa."
	     $(COMPILER) $(FLAGS) $(OBJ)/show.o $(OBJ)/table.o $(OBJ)/user.o $(OBJ)/business.o $(OBJ)/review.o $(OBJ)/hashes.o $(OBJ)/reading.o $(OBJ)/hashcontrol.o $(OBJ)/sgr.o $(OBJ)/interpreter.o $(OBJ)/main.o  $(PKG) -o program

# Build the executable 'program' depends on all 5 object files
alltest: $(OBJ)/sgr.o $(OBJ)/hashcontrol.o $(OBJ)/reading.o $(OBJ)/hashes.o $(OBJ)/user.o $(OBJ)/review.o $(OBJ)/business.o $(OBJ)/table.o 
	     @echo "> Compilando Testes."
	     $(COMPILER) $(FLAGS) $(OBJ)/table.o $(OBJ)/user.o $(OBJ)/business.o $(OBJ)/review.o $(OBJ)/hashes.o $(OBJ)/reading.o $(OBJ)/hashcontrol.o $(OBJ)/sgr.o $(SRC)/test.c $(PKG) -o test

memcheck:
	      valgrind --leak-check=yes ./program

#  Remove object files, executables (UNIX/Windows), Emacs backup files,
#+ and core files
clean:
	   @echo "> Removendo o programa."
	   rm -rf $(OBJ)/*.o program *~ *.core core
