# Lvm

       --- A simple virtual machine based on cpu instruction set.Includes some DIY instructions,and it 
       is still updating.
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
               OPLOADVB AL 1  #AL=1     put 1 to AL
       add:    OPLOAD AL CL   #AL=CL
               OPADDB AL 10   #AL=AL+[10]
               OPSTOREB 10 AL #[10]=AL  
               OPINC CL       #CL=CL+1
               OPCMPVB CL 4   #CMP 4
               OPJG    quit
               OPJNG    add
       quit:   OPPRINTR AL
               OPHALT
               
###Out:
![image](https://github.com/Leviathan1995/lvm/raw/master/span.png)

##Syntax
- 注释使用 '#'
- 格式: 操作码 操作数1 操作数2
- 优先级: 寄存器需要在立即数或内存地址前面 例如 OPADDB AL [10]
              
##Support Instruction:

| Instruction  | Explanation            |   Example        |
| ------------ | ---------------------- | -------------    |
|   OPHALT     |   stop                 |  OPHALT          |
|   OPCLEAR    |   register=0           |  OPCLEAR AL      |
|   OPADDB     |   al=al+[10]           |  OPADDB AL [10]  |
|   OPLOAD     |   al=cl                |  OPLOAD AL CL    |
|   OPLOADVB   |   al=1                 |  OPLOADVB AL 1   |
|   OPSTOREB   |   [10]=al              |  OPSTOREB 10 AL  |
|   OPINC      |   al=al+1              |  OPINC AL        |
|   OPCMPVB    |   cl cmp 5             |  OPCMPVB CL 5    |
|   OPJG       |   if greatet jump      |  OPJG            |
|   OPJNG      |   if not greater jump  |  OPJNG           |
|   OPPRINTR   |   output al to terminal|  OPPRINTR AL     |
<h2>Lincense:</h2>
    MIT
