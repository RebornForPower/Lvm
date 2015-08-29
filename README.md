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
|   OPHALT     |     虚拟机停止         |  OPHALT          |
|   OPCLEAR    |     寄存器清零         |  OPCLEAR AL      |
|   OPADDB     |     寄存器与[B]的值相加|  OPADDB AL [10]  |
|   OPLOAD     |     寄存器之间赋值     |  OPLOAD AL CL    |
|   OPLOADVB   |     立即数赋值寄存器   |  OPLOADVB AL 1   |
|   OPSTOREB   |     寄存器的值存入[B]  |  OPSTOREB 10 AL  |
|   OPINC      |     自增1              |  OPINC AL        |
|   OPCMPVB    |     寄存器与[B]比较    |  OPCMPVB CL 5    |
|   OPJG       |     大于则跳转         |  OPJG            |
|   OPJNG      |     不大于则跳转       |  OPJNG           |
|   OPPRINTR   |  输出寄存器的值至终端  |  OPPRINTR AL     |
<h2>Lincense:</h2>
    MIT
