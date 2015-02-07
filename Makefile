CC = g++ -O2 -Wno-deprecated

tag = -i


ifdef linux
tag = -n
endif

BIN = ./bin/
SRC = ./source/

test.out: 	Record.o \
			Comparison.o \
			ComparisonEngine.o \
			Schema.o \
			File.o \
			DBFile.o \
			y.tab.o \
			lex.yy.o \
			test.o \
			BaseFile.o \
			HeapDBFile.o
			$(CC) -o $(BIN)test.out \
			$(BIN)Record.o \
			$(BIN)Comparison.o \
			$(BIN)ComparisonEngine.o \
			$(BIN)Schema.o \
			$(BIN)File.o \
			$(BIN)DBFile.o \
			$(BIN)y.tab.o \
			$(BIN)lex.yy.o \
			$(BIN)test.o \
			$(BIN)BaseFile.o \
			$(BIN)HeapDBFile.o -lfl

#main: Record.o Comparison.o ComparisonEngine.o Schema.o File.o y.tab.o lex.yy.o main.o BaseFile.o DBFile.o HeapDBFile.o
	##$(CC) -o main Record.o Comparison.o ComparisonEngine.o Schema.o File.o y.tab.o lex.yy.o main.o BaseFile.o DBFile.o  -lfl

test.o: $(SRC)test.cc $(SRC)DBFile.cc
	$(CC) -g -c $(SRC)test.cc -o $(BIN)test.o

#main.o: main.cc DBFile.cc
#	$(CC) -g -c main.cc

Comparison.o: $(SRC)Comparison.cc
	$(CC) -g -c $(SRC)Comparison.cc -o $(BIN)Comparison.o

ComparisonEngine.o: $(SRC)ComparisonEngine.cc
	$(CC) -g -c $(SRC)ComparisonEngine.cc -o $(BIN)ComparisonEngine.o

DBFile.o: $(SRC)DBFile.cc $(SRC)HeapDBFile.cc
	$(CC) -g -c $(SRC)DBFile.cc -o $(BIN)DBFile.o

File.o: $(SRC)File.cc
	$(CC) -g -c $(SRC)File.cc -o $(BIN)File.o

Record.o: $(SRC)Record.cc
	$(CC) -g -c $(SRC)Record.cc -o $(BIN)Record.o

Schema.o: $(SRC)Schema.cc
	$(CC) -g -c $(SRC)Schema.cc -o $(BIN)Schema.o

BaseFile.o: $(SRC)BaseFile.cc
	$(CC) -g -c $(SRC)BaseFile.cc -o $(BIN)BaseFile.o

HeapDBFile.o: $(SRC)HeapDBFile.cc $(SRC)BaseFile.cc
	$(CC) -g -c $(SRC)HeapDBFile.cc -o $(BIN)HeapDBFile.o


y.tab.o: $(SRC)Parser.y
	yacc -d $(SRC)Parser.y
	mv y.tab.c $(SRC)y.tab.c
	mv y.tab.h $(SRC)y.tab.h
	sed $(tag) $(SRC)y.tab.c -e "s/  __attribute__ ((__unused__))$$/# ifndef __cplusplus\n  __attribute__ ((__unused__));\n# endif/"
	g++ -c $(SRC)y.tab.c -o $(BIN)y.tab.o

lex.yy.o: $(SRC)Lexer.l
	lex  $(SRC)Lexer.l
	mv lex.yy.c $(SRC)lex.yy.c
	gcc  -c $(SRC)lex.yy.c -o $(BIN)lex.yy.o

clean:
	rm -f $(BIN)*.o
	rm -f $(BIN)*.out
	rm -f $(BIN)y.tab.c
	rm -f $(BIN)lex.yy.c
	rm -f $(BIN)y.tab.h


###Google Test Integration#########

# Points to the root of fused Google Test, relative to where this file is.
GOOGLE_TEST_FUSED_SRC = ./googleTest/fused-src

# Paths to the fused gtest files.
GOOGLE_TEST_FUSED_H = $(GOOGLE_TEST_FUSED_SRC)/gtest/gtest.h
GOOTLE_TEST_FUSED_TEST_ALL_CC = $(GOOGLE_TEST_FUSED_SRC)/gtest/gtest-all.cc


# Where to find gtest_main.cc.
GTEST_MAIN_CC = ./googleTest/src/gtest_main.cc
# Flags passed to the preprocessor.
# We have no idea here whether pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I$(GOOGLE_TEST_FUSED_SRC) -DGTEST_HAS_PTHREAD=0

# Flags passed to the C++ compiler.
CXXFLAGS += -g

$(GOOGLE_TEST_FUSED_H) : ./googleTest/scripts/fuse_gtest_files.py $(GOOGLE_TEST_FUSED_SRC)

$(GOOTLE_TEST_FUSED_TEST_ALL_CC) : ./googleTest/scripts/fuse_gtest_files.py $(GOOGLE_TEST_FUSED_SRC)

gtest-all.o : $(GOOGLE_TEST_FUSED_H) $(GOOTLE_TEST_FUSED_TEST_ALL_CC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GOOGLE_TEST_FUSED_SRC)/gtest/gtest-all.cc -o $(BIN)gtest-all.o

gtest_main.o : $(GOOGLE_TEST_FUSED_H) $(GTEST_MAIN_CC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GTEST_MAIN_CC) -o $(BIN)gtest_main.o


UnitTest.o : $(SRC)DBFile.cc $(SRC)DBFile.h $(SRC)UnitTest.cc $(GOOGLE_TEST_FUSED_H)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC)UnitTest.cc  -o $(BIN)UnitTest.o -lgtest_main

UnitTest : 	Record.o Comparison.o \
				ComparisonEngine.o File.o \
				y.tab.o lex.yy.o \
				BaseFile.o HeapDBFile.o \
				DBFile.o UnitTest.o \
				gtest-all.o gtest_main.o
				#mv gtest-all.o $(BIN)gtest-all.o
				#mv gtest_main.o $(BIN)gtest_main.o
	$(CC) -o $(BIN)UnitTest.out \
	$(BIN)UnitTest.o $(BIN)Record.o \
	$(BIN)Comparison.o $(BIN)ComparisonEngine.o \
	$(BIN)File.o $(BIN)y.tab.o \
	$(BIN)lex.yy.o $(BIN)BaseFile.o \
	$(BIN)HeapDBFile.o $(BIN)DBFile.o $(BIN)UnitTest.o \
	$(BIN)gtest-all.o $(BIN)gtest_main.o
