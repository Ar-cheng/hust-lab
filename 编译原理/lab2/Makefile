CC = gcc
LIBS = -lm
CFLAGS = -o 

test: parser test.c
	./parser test.c

parser:lex.yy.c parser.tab.c ast.c
	${CC} ${CFLAGS} parser lex.yy.c parser.tab.c ast.c

lex.yy.c: lex.l
	flex lex.l

parser.tab.c: parser.y
	bison -d parser.y

bison: parser.y
	bison -d parser.y


debug:parser.y
	bison -d -v parser.y