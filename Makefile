# Makefile du Projet DES

CC = gcc
CFLAGS = -c -g -Wall
NOM = -o $@

ODIR  = binaires
DESDIR = DES
K48DIR = K16_48
K56DIR = K16_56
K64DIR = K64
FCTDIR = Fonctions

DOC = Documentation
SITE = $(DOC)/html

run: clean principal

all : creation des doc

principal : des
			./des
#Compil final

des: $(ODIR)/projet_des.o $(ODIR)/K64.o $(ODIR)/fonctions.o $(ODIR)/Permutation.o $(ODIR)/fonction_f.o $(ODIR)/algo_keyschedule.o $(ODIR)/Des.o $(ODIR)/K16_48.o $(ODIR)/K16_56.o 
	 $(CC) -o des $^
	 
#Creation main.o

$(ODIR)/projet_des.o: projet_des.c $(DESDIR)/Messages.h  $(DESDIR)/Tables_Permu.h
	$(CC) $(CFLAGS) $(NOM) projet_des.c
	
#Creation fonctions.o

$(ODIR)/fonctions.o: $(FCTDIR)/fonctions.c $(FCTDIR)/fonctions.h
	$(CC) $(CFLAGS) $(NOM) $(FCTDIR)/fonctions.c

#Creation Permutation.o

$(ODIR)/Permutation.o: $(DESDIR)/Permutation.c $(DESDIR)/Permutation.h 
	$(CC) $(CFLAGS) $(NOM) $(DESDIR)/Permutation.c

#Creation fonction_f.o
	
$(ODIR)/fonction_f.o: $(DESDIR)/fonction_f.c $(DESDIR)/fonction_f.h 
	$(CC) $(CFLAGS) $(NOM) $(DESDIR)/fonction_f.c
	
#Creation Des.o	
	
$(ODIR)/Des.o: $(DESDIR)/Des.c $(DESDIR)/Des.h 
	$(CC) $(CFLAGS) $(NOM) $(DESDIR)/Des.c

#Creation algo_keyschedule.o

$(ODIR)/algo_keyschedule.o: $(DESDIR)/algo_keyschedule.c $(DESDIR)/algo_keyschedule.h 
	$(CC) $(CFLAGS) $(NOM) $(DESDIR)/algo_keyschedule.c

#Creation K16_48.o
	
$(ODIR)/K16_48.o: $(K48DIR)/K16_48.c $(K48DIR)/K16_48.h 
	$(CC) $(CFLAGS) $(NOM) $(K48DIR)/K16_48.c
	
#Creation K16_56.o	
	
$(ODIR)/K16_56.o: $(K56DIR)/K16_56.c $(K56DIR)/K16_56.h 
	$(CC) $(CFLAGS) $(NOM) $(K56DIR)/K16_56.c
	
#Creation K64.o	
	
$(ODIR)/K64.o: $(K64DIR)/K64.c $(K64DIR)/K64.h 
	$(CC) $(CFLAGS) $(NOM) $(K64DIR)/K64.c

creation:
	mkdir -p $(ODIR)
	mkdir -p $(DOC)

doc :
	doxygen
	
site:
	xdg-open $(SITE)/index.html

cleanAll:clean
	rm -rf $(ODIR)
	rm -rf $(DOC)

clean:
	rm -f des
	rm -f $(ODIR)/*.o
