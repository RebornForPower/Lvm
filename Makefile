Lvm:Main.o Lmachine.o Assembler.o Token.o
	g++ Main.o Lmachine.o Assembler.o Token.o -o Lvm /usr/local/lib/libboost_regex.a
Main.o:src/Main.cpp src/Lmachine.h src/Assembler.h
	g++ -c src/Main.cpp
Lmachine.o:src/Lmachine.cpp src/Lmachine.h src/Global.h
	g++ -c src/Lmachine.cpp
Assembler.o:src/Assembler.cpp src/Assembler.h src/Lmachine.h src/Global.h
	g++ -c src/Assembler.cpp
Token.o:src/Token.cpp src/Token.h
	g++ -c src/Token.cpp
