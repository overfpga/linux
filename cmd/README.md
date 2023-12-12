# linux 常用命令




## strace


## 查看可执行文件内容的命令

    要查看C语言可执行文件的内容，可以使用一些工具和命令：

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







