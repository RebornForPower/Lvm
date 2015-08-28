# Lvm

       --- a simple virtual machine 

<h2>Building and Running :</h2>

<h4>Linux,*nix,Mac OSX:<h4>

        $ git clone https://github.com/Leviathan1995/lvm.git
        $ make
        $ ./lvm


<h2>Support instruction:<h2>

<table>
<tbody>
<tr><td><em>Instruction</em></td><td><em>Explanation</em></td><td><em>Example<em></td></tr>
<tr><td><h5>OpHALT</td><td><h5>虚拟机停止<h5></td><td><h5></h5></td></tr>
<tr><td><h5>OpCLEAR</td><td><h5>寄存器清零<h5></td><td><h5>OpCLEAR AL</h5></td></tr>
<tr><td><h5>OpADDB</td><td><h5>寄存器与[B]的值相加<h5></td><td><h5>OpADDB AL [10]</h5></td></tr>
<tr><td><h5>OpLOAD</td><td><h5>寄存器之间赋值<h5></td><td><h5>OpLOAD AL CL</h5></td></tr>
<tr><td><h5>OpLOADVB</td><td><h5>立即数赋值寄存器<h5></td><td><h5>OpLOADVB AL 1</h5></td></tr>
<tr><td><h5>OpSTOREB</td><td><h5>寄存器的值存入[B]<h5></td><td><h5>OpSTOREB 10 AL</h5></td></tr>
<tr><td><h5>OpINC</td><td><h5>自增1<h5></td><td><h5>OpINC AL</h5></td></tr>
<tr><td><h5>OpCMPVB</td><td><h5>寄存器与[B]相比较<h5></td><td><h5>OpCMPVB CL 5</h5></td></tr>
<tr><td><h5>OpJG</td><td><h5> 大于则跳转<h5></td><td><h5> OpJG</h5></td></tr>
<tr><td><h5>OpJNG</td><td><h5>不大于则跳转<h5></td><td><h5>OpJNG</h5></td></tr>
<tr><td><h5>OpPRINTR</td><td><h5>输出寄存器的值至终端<h5></td><td><h5>OpPRINTR AL</h5></td></tr>
</tbody>
</table>


<h2>Lincense:</h2>
    MIT
