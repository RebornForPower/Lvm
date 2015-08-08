#include "Lmachine.h"
#include "Assembler.h"
#include <boost/regex.hpp>

using namespace std;

int main()
{
	Lmachine *lmachine = new Lmachine;
	Assembler *assembler = new Assembler;
	if (lmachine->Init())//虚拟机初始化
	{
		assembler->Init(lmachine->CodeFileName, lmachine);
		assembler->Run_Assembler();
		lmachine->LmachineRun();
	}
	else
		return 0;
}
