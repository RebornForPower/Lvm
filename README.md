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
<tr><td><em><h4>Instruction</h4></em></td><td><em><h4>Explanation</h4></em></td><td><em><h4>Example</h4><em></td></tr>
<tr><td><h6>OpHALT</h6></td><td><h6>虚拟机停止</h6></td><td><h5></h5></td></tr>
<tr><td><h6>OpCLEAR</h6></td><td><h6>寄存器清零</h6></td><td><h6>OpCLEAR AL</h6></td></tr>
<tr><td><h6>OpADDB</h6></td><td><h6>寄存器与[B]的值相加</h6></td><td><h6>OpADDB AL [10]</h6></td></tr>
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




| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |


<h2>Lincense:</h2>
    MIT
