Lvm:lvm_main.o lvm_lmachine.o lvm_assembler.o lvm_global.o
		g++ -g  lvm_main.o lvm_lmachine.o lvm_assembler.o lvm_global.o   -o Lvm
lvm_main.o:src/lvm_main.cpp src/lvm_lmachine.h src/lvm_assembler.h
		g++ -std=c++11  -g -c src/lvm_main.cpp
lvm_lmachine.o:src/lvm_lmachine.cpp src/lvm_lmachine.h
		g++ -std=c++11 -g -c src/lvm_lmachine.cpp
lvm_assembler.o:src/lvm_assembler.cpp src/lvm_assembler.h
		g++ -std=c++11 -g -c src/lvm_assembler.cpp
lvm_global.o:src/lvm_global.cpp src/lvm_global.h
		g++ -std=c++11 -g -c src/lvm_global.cpp
clean:
	rm -f *.o Lvm
