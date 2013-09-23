CC = g++
CFLAGS = -O3 -c
OBJS = DFiniteAutomata.o Edge.o Grammar.o HashMap.o HashMapNode.o NonTerminalSymbol.o ParsingTable.o Production.o Project.o State.o Symbol.o TerminalSymbol.o Main.o

all: syntax-parser

clean:
	rm *.o syntax-parser

syntax-parser: $(OBJS)
	$(CC) $(OBJS) -o syntax-parser

DFiniteAutomata.o: DFiniteAutomata.cc
	$(CC) $(CFLAGS) DFiniteAutomata.cc -o DFiniteAutomata.o

Edge.o: Edge.cc
	$(CC) $(CFLAGS) Edge.cc -o Edge.o

Grammar.o: Grammar.cc
	$(CC) $(CFLAGS) Grammar.cc -o Grammar.o

HashMap.o: HashMap.cc
	$(CC) $(CFLAGS) HashMap.cc -o HashMap.o

HashMapNode.o: HashMapNode.cc
	$(CC) $(CFLAGS) HashMapNode.cc -o HashMapNode.o

NonTerminalSymbol.o: NonTerminalSymbol.cc
	$(CC) $(CFLAGS) NonTerminalSymbol.cc -o NonTerminalSymbol.o

ParsingTable.o: ParsingTable.cc
	$(CC) $(CFLAGS) ParsingTable.cc -o ParsingTable.o

Production.o: Production.cc
	$(CC) $(CFLAGS) Production.cc -o Production.o

Project.o: Project.cc
	$(CC) $(CFLAGS) Project.cc -o Project.o

State.o: State.cc
	$(CC) $(CFLAGS) State.cc -o State.o

Symbol.o: Symbol.cc
	$(CC) $(CFLAGS) Symbol.cc -o Symbol.o

TerminalSymbol.o: TerminalSymbol.cc
	$(CC) $(CFLAGS) TerminalSymbol.cc -o TerminalSymbol.o

Main.o: Main.cc
	$(CC) $(CFLAGS) Main.cc -o Main.o
