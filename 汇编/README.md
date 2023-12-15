
# 寄存器
    8086处理器内部有8个16位的通用寄存器，都是由16比特组成的，并分别被命名为AX、BX、CX、DX、SI、DI、BP、SP

    这8个寄存器中的前4个，即AX、BX、CX和DX，又各自可以拆分成两个8位的寄存器来使用，总共可以提供8个8位的寄存器AH、AL、BH、BL、CH、CL、DH和DL。这样一来，当需要在寄存器和寄存器之间，或者寄存器和内存单元之间进行8位的数据传送或者算术逻辑运算时，使用它们就很方便

    数据段寄存器：DS
    代码段寄存器：CS
    附加段寄存器：ES
    栈段寄存器  ：SS
    8086内部有4个段寄存器。其中，CS是代码段寄存器，DS是数据段寄存器，ES是附加段(Extra Segment)寄存器。附加段的意思是，它是额外赠送的礼物，当需要在程序中同时使用两个数据段时，DS指向一个，ES指向另一个。可以在指令中指定使用DS和ES中的哪一个，如果没有指定，则默认使用DS。SS是栈段(Stack Segment)寄存器，以后会讲到，而且非常重要

    指令指针寄存器：IP
    IP是指令指针(Instruction Pointer)寄存器，它只和CS一起使用，而且只有处理器才能直接改变它的内容。当一段代码开始执行时，CS保存代码段的段地址，IP则指向段内偏移。这样，由CS和IP共同形成逻辑地址，并由总线接口部件变换成物理地址来取得指令。然后，处理器会自动根据当前指令的长度来改变IP的值，使它指向下一条指令

    8086内部有一个6字节的指令预取队列
    处理器能够自动运行，这是控制器的功劳。为了加快指令执行速度，8086内部有一个6字节的指令预取队列，在处理器忙着执行那些不需要访问内存的指令时，指令预取部件可以趁机访问内存预取指令。这时，多达6字节的指令流可以排队等待解码和执行

    标志寄存器
    在x86-64体系结构中，RFLAGS寄存器是64位的，其中各个位的功能如下：

    CF (Carry Flag)：进位标志，记录了最近一次算术运算是否产生了进位或借位。

    PF (Parity Flag)：奇偶标志，记录了最近一次操作结果中低8位的奇偶性。

    AF (Auxiliary Carry Flag)：辅助进位标志，记录了最近一次十六进制数运算是否产生了进位或借位。

    ZF (Zero Flag)：零标志，记录了最近一次操作结果是否为零。

    SF (Sign Flag)：符号标志，记录了最近一次操作结果的符号。

    TF (Trap Flag)：陷阱标志，在单步执行模式下用于调试目的。

    IF (Interrupt Enable Flag)：中断使能标志，在置为1时允许处理器响应外部中断请求。

    DF (Direction Flag)：方向标志，控制字符串操作指令执行时数据传输的方向（0表示递增，1表示递减）。

    OF (Overflow Flag)：溢出标志，记录了最近一次有符号整数运算是否发生溢出。

    IOPL[1:0] (I/O Privilege Level Field): I/O 特权级字段，在特殊环境下用于控制对I/O端口的访问权限。

    NT (Nested Task Flag): 嵌套任务标志，在发生任务切换时用于支持任务的层次结构。

    RF (Resume Flag): 恢复标志，在处理器从断点处恢复执行时使用。

    VM (Virtual-8086 Mode Flag): 虚拟-8086模式标志，控制处理器是否以虚拟8086模式运行。

    AC (Alignment Check Flag): 对齐检查标志，用于保证数据对齐的正确性。

    VIF (Virtual Interrupt Flag)：虚拟中断标志，在处理器以虚拟8086模式运行时用于支持中断处理。

    VIP (Virtual Interrupt Pending)：虚拟中断挂起标志，在处理器以虚拟8086模式运行时用于指示有待处理的中断请求。

    ID (ID Flag)：识别标志，指示处理器是否支持CPUID指令。

## 标号
    标号代表某一行的地址



## 语法

### x86
    into、int3、intn、iret、cli、sti、hlt、not和test等。

    iret：中断返回指令
        IRET 是 x86 架构中的一条指令，用于从中断或异常处理程序返回到先前被中断的代码位置。它的作用是恢复被中断时的上下文，并继续执行被中断的程序。

        IRET 指令执行时会从堆栈中弹出之前保存的标志寄存器 (EFLAGS)、指令指针 (EIP) 和段选择子等内容，并将控制权返回到被中断的程序。

        在保护模式下，IRET 也会还原任务状态段 (Task State Segment, TSS) 中的相关信息以支持任务切换和多任务处理。

        总而言之，IRET 指令是用于从中断或异常处理过程返回到原始执行点并恢复正常执行流程的关键指令

    sti:设置中断标志位。它通常用于打开处理器的中断功能
            在大多数x86架构的汇编语言中，STI指令没有任何操作数
            执行STI指令后，处理器会将EFLAGS寄存器中的IF（Interrupt Flag）位设置为1，以允许外部中断的响应。这样，当有可屏蔽中断发生时，处理器会检查IF位是否为1，
        并根据情况进入相应的中断服务 程序。需要注意的是，在使用STI指令时需要小心，并确保在适当的时候关闭中断标志位（使用CLI指令）。不正确地操作中断标志位可能
        导致意外的结果或安全问题。另外，请注意不同体系结构和编译器可能具有不同的汇编语言规范和特性，因此建议参考特定平台和文档来了解精确的用法和行为。


    CLI:用于清除中断标志位。它通常用于禁用处理器的中断功能
        在大多数x86架构的汇编语言中，CLI指令没有任何操作数
        执行CLI指令后，处理器会将EFLAGS寄存器中的IF（Interrupt Flag）位设置为0，以禁止外部中断的响应。这样，当有可屏蔽中断发生时，处理器不会进入相应的中断服务程序。
        需要注意的是，在使用CLI指令时需要小心，并确保在适当的时候重新启用中断标志位（使用STI指令）。正确地管理和控制中断标志位对于确保系统的正常运行和安全性至关重要。
        另外，请注意不同体系结构和编译器可能具有不同的汇编语言规范和特性，因此建议参考特定平台和文档来了解精确的用法和行为。

    x86处理器指令，如in、out、shl、shr、rol、ror、jmp、call、ret等

    shl:shl 是 x86 汇编指令中的一个逻辑左移指令（Shift Left）。它将给定操作数向左移动指定的位数，用零填充右侧空出来的位
        shl 的语法为：
            shl destination, count
        其中 destination 是要进行左移操作的目标操作数，可以是寄存器或内存位置；count 是左移的位数，可以是立即数或者存储在 CL 寄存器中。需要注意的是，对于 32 位和 64 位操作数，最多只能进行 31 位的左移。

    shr:shr 是 x86 汇编指令中的一个逻辑右移指令（Shift Right）。它将给定操作数向右移动指定的位数，用零填充左侧空出来的位
        shr 的语法为：
            shr destination, count
        其中 destination 是要进行右移操作的目标操作数，可以是寄存器或内存位置；count 是右移的位数，可以是立即数或者存储在 CL 寄存器中。需要注意的是，对于 32 位和 64 位操作数，最多只能进行 31 位的右移。



    rol:rol 是 x86 汇编指令中的循环左移指令（Rotate Left）。它将给定操作数向左循环移动指定的位数
        rol 的语法为：
            rol destination, count
        其中 destination 是要进行循环左移操作的目标操作数，可以是寄存器或内存位置；count 是循环左移的位数，可以是立即数或者存储在 CL 寄存器中。需要注意的是，对于 32 位和 64 位操作数，最多只能进行 31 位的循环左移

    ror:ror 是 x86 汇编指令中的循环右移指令（Rotate Right）。它将给定操作数向右循环移动指定的位数
        ror 的语法为：
            ror destination, count
        其中 destination 是要进行循环右移操作的目标操作数，可以是寄存器或内存位置；count 是循环右移的位数，可以是立即数或者存储在 CL 寄存器中。需要注意的是，对于 32 位和 64 位操作数，最多只能进行 31 位的循环右移

    jmp:jmp 是汇编语言中的跳转指令，用于无条件地将控制流转移到程序中的其他位置
        jmp 的语法为：
            jmp destination
        其中 destination 可以是一个标号（通常对应于代码中的某个位置），也可以是一个寄存器或内存地址。执行 jmp 指令后，程序将会直接跳转到 destination 所指定的位置，并继续执行该位置处的指令

    jne:jne 是汇编语言中的条件跳转指令，用于在满足特定条件时执行跳转操作。它的全称是 "Jump if Not Equal"，意思是如果前一个比较指令的结果不等，则进行跳转
        jne 的语法为：
            jne destination
        其中 destination 可以是一个标号（通常对应于代码中的某个位置），也可以是一个寄存器或内存地址。执行 jne 指令后，程序将会根据前一个比较指令的结果来决定是否进行跳转。如果比较结果不等，则跳转到 destination 所指定的位置继续执行；如果相等，则继续顺序执行下一条指令。

        以下是一些示例：
                cmp eax, ebx   ; 将 eax 和 ebx 进行比较
                jne not_equal  ; 如果不相等则跳转到标号为 "not_equal" 的位置
                ; 如果相等，则继续执行下面的指令

                test ecx, ecx  ; 将 ecx 和自身进行按位与操作
                jne nonzero    ; 如果结果非零则跳转到标号为 "nonzero" 的位置
                ; 如果为零，则继续执行下面的指令

                jmp next       ; 无条件跳转到标号为 "next" 的位置

                not_equal:
                    ...
                    jmp end     ; 跳转到标号为 "end" 的位置

                nonzero:
                    ...
                    jmp end     ; 跳转到标号为 "end" 的位置

                next:
                    ...
                end:

    call:call 是汇编语言中的过程调用指令，用于将控制权转移至一个指定的子程序（过程或函数）并在子程序执行完毕后返回
        call 的语法为：
            call destination
        其中 destination 可以是一个标号（通常对应于代码中的某个位置），也可以是一个寄存器或内存地址。执行 call 指令后，当前指令的下一条指令地址会被保存到栈中，并将控制权转移到 destination 所指定的位置开始执行子程序

        以下是一个示例：
            call subroutine  ; 调用名为 "subroutine" 的子程序
            ; 执行该子程序的代码

            jmp next         ; 子程序执行完毕后跳转到标号为 "next" 的位置

            subroutine:
                ...
                ret           ; 返回到调用点

            next:
                ...

    ret:ret 是汇编语言中的指令，用于从子程序（过程或函数）返回到调用点。它通常与 call 指令一起使用，完成过程的调用和返回操作
        ret 的语法为：
            ret
        执行 ret 指令时，它会从栈中弹出保存的返回地址，并将控制权转移到该地址所指定的位置继续执行代码

        以下是一个示例：
            call subroutine  ; 调用名为 "subroutine" 的子程序

            ...

            subroutine:
                ...
                ret           ; 返回到调用点
        在上面的示例中，通过使用 call 指令调用了名为 "subroutine" 的子程序。当遇到 ret 指令时，它会从栈中弹出之前保存的返回地址，并将控制权转移到该地址所指定的位置，继续执行后续的代码。

        通过正确使用 call 和 ret 指令配合，我们可以实现过程/函数的调用和返回，在程序中实现模块化和重复利用代码

    定义段
    NASM编译器使用汇编指令“SECTION”或者“SEGMENT”来定义段。它的一般格式是
        SECTION 段名称 或 SEGMENT 段名称



# 查看可执行文件内容的命令和一些工具

    使用hexdump或xxd命令：这些命令可以以十六进制格式显示文件的内容。在终端中执行以下命令：

    hexdump -C executable_file
    或者
    xxd executable_file
    这将以16进制形式显示文件的内容。

    使用objdump命令：这个命令用于反汇编可执行文件，将机器代码转换回对应的汇编指令。在终端中执行以下命令：

    objdump -d executable_file
    这将显示可执行文件中的汇编指令和相关信息。

    使用readelf命令：这个命令用于查看ELF（Executable and Linkable Format）格式的可执行文件的详细信息，包括程序头、段表、符号表等。在终端中执行以下命令：

    readelf -a executable_file
    这将显示可执行文件的各个部分及其属性。

    请注意，上述方法主要适用于Linux和类Unix系统。对于其他操作系统，可能需要使用相应平台上特定的工具或调试器来查看可执行文件的内容。


# 数据结构

## 存储器段描述符
        struct SegmentDescriptor {
        unsigned int limit_low: 16;      // 段限长低16位
        unsigned int base_low: 24;       // 段基址低24位
        unsigned int type: 4;            // 段类型
        unsigned int s: 1;               // 存储器段标志（0表示系统段，1表示代码或数据段）
        unsigned int dpl: 2;             // 特权级别（0-3为内核态，4-7为用户态）
        unsigned int p: 1;               // 存在位（指示该段是否存在于内存中）
        unsigned int limit_high: 4;      // 段限长高4位
        unsigned int avl: 1;             // 可用位（可以由操作系统自行使用）
        unsigned int l: 1;               // 长模式标志（启用时表示该代码段支持64位模式）
        unsigned int db: 1;              // 默认操作数大小标志（0表示16位操作数，1表示32位操作数或64位操作数）
        unsigned int g: 1;               // G位（控制单位：字节还是4KB页）
        unsigned int base_high :8 ;      // 段基址高8位
    };





# NASM

## 伪指令
    当前的伪指令有'DB','DW','DD','DQ'和 ‘DT’，它们对应的未初始化指令是'RESB','RESW','RESD','RESQ'和'REST'，'INCBIN' 命令，'EQU'命令和'TIEMS'前缀

    在 NASM 中，`DB', `DW', `DD', `DQ'和`DT'经常被用来在输出文件中声明已初始化 
    的数据，你可以多种方式使用它们： 
    db 0x55 ; just the byte 0x55 
    db 0x55,0x56,0x57 ; three bytes in succession 
    db 'a',0x55 ; character constants are OK 
    db 'hello',13,10,'$' ; so are string constants 
    dw 0x1234 ; 0x34 0x12 
    dw 'a' ; 0x41 0x00 (it's just a number) 
    dw 'ab' ; 0x41 0x42 (character constant) 
    dw 'abc' ; 0x41 0x42 0x43 0x00 (string) 
    dd 0x12345678 ; 0x78 0x56 0x34 0x12 
    dd 1.234567e20 ; floating-point constant 
    dq 1.234567e20 ; double-precision float 
    dt 1.234567e20 ; extended-precision float

    'DQ'和'DT'不接受数值常数或字符串常数作为操作数。

    这些伪指令开辟的内存在当前段
    具体存储位置取决于你在代码中定义数据段和选择合适的内存地址来存储数据。例如，如果你在代码中声明了一个数据段并将其设置为可读写的数据段，
    那么指定的双字0x123456将被存储在该数据段的下一个可用内存位置。

    以下是一个示例代码片段：

    ```assembly
    section .data
    my_data dd 0x123456

    section .text
    global _start

    _start:
        ; 在这里进行程序逻辑操作
    ```

    在上述示例中，我们在.data节中定义了一个标签为my_data的双字变量，并初始化为0x123456。当程序加载到内存时，在.data节之后，my_data变量将占据相应的内存位置。

    需要注意的是，在不同环境和操作系统下，具体内存地址分配可能有所不同。因此，具体位置可能会因上下文而异。



    `RESB'类的伪指令: 声明未初始化的数据。

    `RESB', `RESW', `RESD', `RESQ' and `REST'被设计用在模块的 BSS 段中：它们声明 
    未初始化的存储空间。每一个带有单个操作数，用来表明字节数，字数，或双字数 
    或其他的需要保留单位。就像在 2.2.7 中所描述的，NASM 不支持 MASM/TASM 的扣留未 
    初始化空间的语法'DW ?'或类似的东西：现在我们所描述的正是 NASM 自己的方式。 
    'RESB'类伪指令的操作数是有严格的语法的，参阅 3.8。
    比如： 
    buffer: resb 64 ; reserve 64 bytes 
    wordvar: resw 1 ; reserve a word 
    realarray resq 10 ; array of ten reals


    `INCBIN':包含其他二进制文件

    'INCBIN'是从老的 Amiga 汇编器 DevPac 中借过来的：它将一个二进制文件逐字逐句地 
    包含到输出文件中。这能很方便地在一个游戏可执行文件中包含中图像或声音数 
    据。它可以以下三种形式的任何一种使用： 
    incbin "file.dat" ; include the whole file 
    incbin "file.dat",1024 ; skip the first 1024 bytes 
    incbin "file.dat",1024,512 ; skip the first 1024, and 
    ; actually include at most 512







