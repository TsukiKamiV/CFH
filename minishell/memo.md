20250301

主要负责测试的部分：
从void parse_line(t_shell_data *data)开始的部分，先逐字标记和储存命令行中的内容，再根据引号类型，是否有环境变量，redirection等内容，把这些字符储存进command table
项目要求部分还原POSIX Bash的功能，MAC OS的bash在引号处理上与POSIX不同

-- 目前已知待添加的最大功能：需要修改parse_line，让它能够接收它调用的下层函数的返回值，返回值应该能包含在遍历和处理过程中检测到的命令行语法错误类型。
例如：在tokens_into_cmd_annex中，调用了set_error打印了错误信息但只返回NULL。
最终这个返回值也要在minishell_mainloop中被用于判断command table是否创建成功

-- 其他字符处理的错误：

1. (已解决）echo "home is: $HOME" 命令中的扩展内容不能正确显示；但echo "$HOME is home"可以 

2. 以下命令都应显示home：
	echo 'ho'"me"
	echo 'hom'e
	echo 'h''o''m''e'
	'e'"cho" home
	"echo" "home"
	....
	但：
	echo "$HOM""E" 只显示E
	echo '$HOM'"E" 显示$HOME
	echo $"HOME"   显示HOME
	
3. 虽然做了一部分管理backslash "\"的功能，但不需要做任何相关的测试，分号也不用测试

4. 在minishell_mainloop的172行有一个被注释掉的print_command_table，解开后即可清楚看到command table的组成了

----------------------------------------------------------------

20250303

更新目前最需要解决的问题 （仍然与上面的第2点有关）

- 当命令是 echo "$USER""HELLO"时，输出应该是 luyaoHELLO ，也就是说echo 后面的所有参数只要没被空格或者分隔符（pipe or redirector）分隔开，都应该当作同一个token。
然后，在token_handling/tokenize_input.c/parse_line中调用expand_cmd_token一系列函数时，不能简单地处理接收到的需要扩展的环境变量，而要根据引号状态和关系分割后再扩展，并在必要的时候拼接。

-----------------------------------------------------------------
上面的问题基本解决，已知测试都已通过，待做更多测试
