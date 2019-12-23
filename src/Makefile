CXX=g++
CPPFLAGS=-O3 -Wall -std=c++11
RM=rm -rf
OBJS=main.o Btree.o StandardBTree.o SplayTree.o

all: $(OBJS)
	$(CXX) -o main.exe $(OBJS)

main.o: main.cpp 
	$(CXX) -c $(CPPFLAGS) main.cpp

Btree.o: Btree.cpp Btree.h
	$(CXX) -c $(CPPFLAGS) Btree.cpp

StandardBtree.o: StandardBtree.cpp StandardBtree.h
	$(CXX) -c $(CPPFLAGS) StandardBtree.cpp

Splaytree.o: Splaytree.cpp Splaytree.h
	$(CXX) -c $(CPPFLAGS) Splaytree.cpp

clean:
	$(RM) $(OBJS) main ../output/*