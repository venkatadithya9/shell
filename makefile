all: main.o prompt.o echo.o cd.o ls.o pinfo.o token.o cmdbrk.o hismngr.o history.o setenv.o unsetenv.o jobs.o kjob.o pipefind.o funlist.o overkill.o fg.o bg.o ctrlczhandler.o
	gcc -g main.o prompt.o echo.o cd.o ls.o pinfo.o token.o cmdbrk.o hismngr.o history.o setenv.o unsetenv.o jobs.o kjob.o pipefind.o funlist.o overkill.o fg.o bg.o ctrlczhandler.o -o ava

main.o:
	gcc -c main.c

prompt.o:
	gcc -c prompt.c

echo.o:
	gcc -c echo.c
	
cd.o:
	gcc -c cd.c

ls.o:
	gcc -c ls.c

pinfo.o:
	gcc -c pinfo.c

token.o:
	gcc -c token.c

cmdbrk.o:
	gcc -c cmdbrk.c

hismngr.o:
	gcc -c hismngr.c

history.o:
	gcc -c history.c

setenv.o:
	gcc -c setenv.c

unsetenv.o:
	gcc -c unsetenv.c

jobs.o:
	gcc -c jobs.c

kjob.o:
	gcc -c kjob.c

pipefind.o:
	gcc -c pipefind.c

funlist.o:
	gcc -c funlist.c

overkill.o:
	gcc -c overkill.c

fg.o:
	gcc -c fg.c

bg.o:
	gcc -c bg.c

ctrlczhandler.o:
	gcc -c ctrlczhandler.c

clean:
	rm -rf *o all
	rm -r ava