$celsius = <STDIN>;
chomp($celsius);
#匹配正则 m/.../
#比较数值: == , =～ 连接正则表达式和待搜索的目标字符串
#if ($celsius =~ m/^[0-9]+$/) {
#(?:) 只分组不捕获
if ($celsius =~ m/^[-+]?[0-9]+(\.[0-9]*)?$/) {
    $fahrenheit = ($celsius * 9 / 5) + 32;
    print "$celsius C is $fahrenheit F.\n";
} else {
    print "not only digits\n";
}
