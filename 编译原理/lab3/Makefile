CC = gcc
LIBS = -lm
CFLAGS = -g -o 

test: parser test.c
	./parser test.c

test11: parser test1.c
	./parser test1.c

test22: parser test2.c
	./parser test2.c

parser:lex.yy.c parser.tab.c ast.c
	${CC} ${CFLAGS} parser ast.c parser.tab.c lex.yy.c semantic.c
	
lex.yy.c: lex.l
	flex lex.l

parser.tab.c: parser.y
	bison -d parser.y

bison: parser.y
	bison -d parser.y


debug:parser.y
	bison -d -v parser.y

clean:
	rm lex.yy.c parser.tab.c parser.tab.h parser

tar:
	zip -q -r U201714480-朱志成.zip .