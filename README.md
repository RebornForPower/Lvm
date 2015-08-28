# Lvm

       --- a simple virtual machine 

##Building and Running :

###Linux,*nix,Mac OSX:

       $ git clone https://github.com/Leviathan1995/lvm.git
       $ make
       $ ./lvm
##Support Instruction:

| Instruction  | Explanation            |   Example        |
| ------------ | ---------------------- | -------------    |
|   OpHALT     |     虚拟机停止         |                  |
|   OpCLEAR    |     寄存器清零         |  OpCLEAR AL      |
|   OpADDB     |     寄存器与[B]的值相加|  OpADDB AL [10]  |
|   OpLOAD     |     寄存器之间赋值     |  OpLOAD AL CL    |
|   OpLOADVB   |     立即数赋值寄存器   |  OpLOADVB AL 1   |
|   OpSTOREB   |     寄存器的值存入[B]  |  OpSTOREB 10 AL  |
|   OpINC      |     自增1              |  OpINC AL        |
|   OpCMPVB    |     寄存器与[B]比较    |  OpCMPVB CL 5    |
|   OpJG       |     大于则跳转         |  OpJG            |
|   OpJNG      |     不大于则跳转       |  OpJNG           |
|   OpPRINTR   |  输出寄存器的值至终端  |  OpPRINTR AL     |
<h2>Lincense:</h2>
    MIT
