#完整的正则表达式由两种字符构成：特殊字符(元字符);普通文本字符
#完整的正则表达式由小的构建模块单元组成。
#
#行的起始和结束
^,$
^git,以git开始的行
git$,以git结尾的行
^cat$ 一行仅cat
^$ 空行
^
gr[ea]y 匹配 grey,gray
#排除型字符组
[^...]代替[...]
[^1-6] 排除1-6
#用点号匹配任意字符
.
在字符组内部，元字符的定义和意义是不一样的
- 不接在开头用来表示范围
#写正则表达式时，需要在对欲检索文本的了解程度和检索精确性之间求平衡

#多选结构
#匹配任意子表达式
|
[grey|gray]
^(From|Subject|Date):
起始行为From Subject Date
grep '^(From|Subject|Date):' typescript -Eni
#egrep -i 不区分大小写

#元字符序列
\<\>
\<cat\> 匹配cat
\<cat 匹配cat开头
cat\> 匹配cat结尾

#可选项元素
#color和colour
grep colou?r reg.txt -nE
#July fourth/Jul 4th
grep '(July|Jul)*(fourth|4|4th)' reg.txt -nE
grep 'July?*(fourth|4(th)?)'

#其他量词:重复出现
+：之前紧邻的元素出现一次或者多次
*：之前紧邻的元素出现任意多次或者不出现

#括号及反向引用
括号：限制多选的范围；将若干字符组合成为一个单元，受问号或星号之类量词的作用
#the theory
#\<([a-z]+)([0-9]+).+\1\2\> \1,\2用来表示第一组 第二组括号匹配的文本
grep '\<([a-z]+).+\1\>' reg.txt -En

#神奇的转义
\,使元字符失去特殊含义，成为普通字符

#匹配24小时制
grep '([01][0-9]|2[0-3]):[0-5][0-9]' reg.txt -nE
grep '\$[0-9]+\.[0-9][0-9]'