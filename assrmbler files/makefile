assemler_flags = gcc -g -Wall -pedantic -ansi
flags = gcc -c -Wall -pedantic -ansi
headers = line_read.h store.h analyze_str.h helper.h first_pass.h second_pass.h freecode.h pre_assembler.h FinalCreator.h
assembler_objects = line_read.o analyze_str.o freecode.o helper.o first_pass.o second_pass.o assembler.o FinalCreator.o pre_assembler.o

assembler : ${assembler_objects}
	${assemler_flags} ${assembler_objects} -o assembler

assembler.o: assembler.c ${headers}
	${flags} assembler.c -o assembler.o

line_read.o: line_read.c line_read.h $(headers)
	${flags} line_read.c -o line_read.o

analyze_str.o: analyze_str.c analyze_str.h ${headers}
	${flags} analyze_str.c -o analyze_str.o

helper.o: helper.c helper.h ${headers}
	${flags} helper.c -o helper.o

first_pass.o: first_pass.c first_pass.h ${headers}
	${flags} first_pass.c -o first_pass.o

second_pass.o: second_pass.c second_pass.h ${headers}
	${flags} second_pass.c -o second_pass.o

FinalCreator.o: FinalCreator.c FinalCreator.h ${headers}
	${flags} FinalCreator.c -o FinalCreator.o

pre_assembler.o: pre_assembler.c pre_assembler.h ${headers}
	${flags} pre_assembler.c -o pre_assembler.o

freecode.o: freecode.c freecode.h ${headers}
	${flags} freecode.c -o freecode.o
