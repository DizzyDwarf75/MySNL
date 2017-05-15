# SNL-Compiler
Exercise for Compiler course of Jilin University

运行环境
1:codeblocks 
2:python 3
3:Google Chrome

实现目标
1:词法分析
2:递归向下分析
3:LL1向下分析
4:语法树结构
5:语法树的图形化显示

开发思路
(1)在写词法分析时,采用 python 解析 pre.html 内的文法 
	完成主体代码的生成,并在 MySNL.cbd 工程下完善。
(2)在浏览器下,显示词法分析树


开发过程
1:codebloks 工程 在 MySNL 文件夹下 MySNL.cbd
2:在 pg 文件夹 下
	主要有 gene.py Mygene.py
	(1)gene.py 主要生成 递归向下 的 parser.h parser.cpp 文件
	(2)Mygene.py 主要生成 LL1递归向下 的  myParse.h (完成代码主体90%的编写)


基本输入:code文件夹下的源Snl代码文本格式
基本输出:
(1)词法分析过程在命令行下输出.
(2)递归向下法判断源程序是否正确, 出错报错,命令行下输出.
(3)LL1向下分析判断对错,并输出语法分析树,在 outputtree 文件夹下输出 为 Myout.txt
(4)命令行到当前目录 python 运行 help.py 
	运行 生成 TreeData.json 
	浏览器打开 Show.html 并打开 TreeData.json
	即可看到 语法树 的 图形化 展示




