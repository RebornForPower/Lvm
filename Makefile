lvmachine:main.o lmachine.o assembler.o global.o
		g++ -g  main.o lmachine.o assembler.o global.o   -o lvmachine
main.o:lvm/main.cpp lvm/lmachine.h lvm/assembler.h
		g++ -std=c++11 -g -c lvm/main.cpp
lmachine.o:lvm/lmachine.cpp lvm/lmachine.h
		g++ -std=c++11 -g -c lvm/lmachine.cpp
assembler.o:lvm/assembler.cpp lvm/assembler.h
		g++ -std=c++11 -g -c lvm/assembler.cpp
global.o:lvm/global.cpp lvm/global.h
		g++ -std=c++11 -g -c lvm/global.cpp
clean:
	rm -f main.o lmachine.o assembler.o global.o lvmachine
