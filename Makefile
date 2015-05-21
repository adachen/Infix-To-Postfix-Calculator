# MAKE FILE - Ada Chen #
# Creates executable called assignment #
all:
	g++ Test.cpp InfixToPostfixCalculator.cpp InfixToPostfixCalculator.h LinkedStack.cpp LinkedStack.h Node.cpp Node.h PreconditionViolatedException.cpp PreconditionViolatedException.h StackInterface.h -o assignment

clean: 
	rm -rf *o assignment
