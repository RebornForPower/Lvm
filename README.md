# Lvm

       --- a simple virtual machine 
                            by:leviathan
##Building and Running :

###Linux,*nix,Mac OSX:

       $ git clone https://github.com/Leviathan1995/lvm.git
       $ make
       $ ./lvm

##Example :

###Source code:
       start : OPCLEAR AL     #AL=0
               OPCLEAR CL     #CL=0
               OPLOADVB CL 1  #CL=1
               OPLOADVB AL 1  #AL=1     将值存入寄存器中
       add:    OPLOAD AL CL   #AL=CL
               OPADDB AL 10   #AL=AL+[10]
               OPSTOREB 10 AL #[10]=AL  将寄存器内容加载到内存
               OPINC CL       #CL=CL+1
               OPCMPVB CL 4   #CMP 4
               OPJG    quit
               OPJNG    add
       quit:   OPPRINTR AL
               OPHALT
               
###Out:
![image](https://github.com/Leviathan1995/lvm/raw/master/span.png)

##Syntax
- 注释使用#
- 格式: 操作码 操作数1 操作数2
- 当同时使用寄存器与立即数两个操作数时,寄存器为操作数1,立即数为操作数2
              
##Support Instruction:

| Instruction  | Explanation            |   Example        |
| ------------ | ---------------------- | -------------    |
|   OpHALT     |     虚拟机停止         |  OpHALT          |
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
