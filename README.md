# Lvm

A simple virtual machine based on cpu  instruction  set.Includes some DIY instructions,and it is still updating.

## Building and Running :

### Linux,*nix,Mac OSX:

       $ git clone https://github.com/Leviathan1995/lvm.git
       $ make
       $ ./lvm

## Example :

### [Bubble Sort](https://github.com/Leviathan1995/Lvm/blob/master/test/sort.txt):

![image](https://github.com/Leviathan1995/lvm/raw/master/pic.png)

## Syntax
- 注释使用 '#'
- 格式: 操作码 操作数1 操作数2
- 优先级: 寄存器需要在立即数或内存地址前面 例如 OPADDB AL [10]
              
## Support Instruction:

| Instruction  |      Explanation            |          Example        |
| ------------ | --------------------------- | ------------------------|
|   OPHALT     |        stop                 |  OPHALT                 |
|   OPCLEAR    |        register=0           |  OPCLEAR AL             |
|   OPINIT     |        id=register          |  OPINIT i AL            |
|   OPINITLIST |        a={1,2,3,4,5}        |  OPINITLIST a 1,2,3,4,5 |
|   OPASSIGN   |        id=reg/num           |  OPASSIGN i 0           | 
|   OPBINADD   |        id1=id2+id3          |  OPBINADD id1 id2 id3   |
|   OPBINSUB   |        id1=id2-id3          |  OPBINSUB id1 id2 id3   |
|   OPBINMUL   |        id1=id2*id3          |  OPBINMUL id1 id2 id3   |
|   OPBINDIV   |        id1=id2/id3          |  OPBINDIV id1 id2 id3   |
|   OPADDB     |        al=al+[10]           |  OPADDB AL [10]         |
|   OPADDVB    |        al=al+1              |  OPADDVB AL 1           |
|   OPSUBB     |        al=al-[10]           |  OPSUBB AL [10]         |
|   OPSUBVB    |        al=al-1              |  OPSUBVB AL 1           |
|   OPLOAD     |        al=cl                |  OPLOAD AL CL           |
|   OPLOADVB   |        al=1                 |  OPLOADVB AL 1          |  
|   OPSTOREB   |        [10]=al              |  OPSTOREB 10 AL         |
|   OPINC      |        al=al+1              |  OPINC AL               |
|   OPDEC      |        al=al-1              |  OPDEC AL               |
|   OPCMPVB    |        cl cmp 5             |  OPCMPVB CL 5           |
|   OPJG       | if greatet jump to label    |  OPJG  cmp1 cmp2 label  |
|   OPJNG      |if not greater jump to label |  OPJNG cmp1 cmp2 label  |
|   OPPRINTR   |        output al to terminal|  OPPRINTR AL            |
|  OPPRINTRLIST|      output list to terminal|  OPPRINTRLIST list      |
|  OPEND       |        block end            |  OPEND block1           |
|  OPPAUSE     |        use debug            |  OPPAUSE                |

<h2>Lincense:</h2>
    MIT
