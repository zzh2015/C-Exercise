//lambda:表示一个可调用的代码单元。#一个未命名的内联函数#
//[capture list](para list) -> return type {func body}
//可以忽略参数列表和返回值类型，但必须捕获列表和函数体

auto f = [] {return 42;};
cout << f() << endl; //42

[] (const string &a, const string &b) {return a.size() < b.size();}
//using
stable_sort(v.begin(), v.end(), [] (const string &a, const string &b) {return a.size() < b.size();} );

//lambda通过捕获列表来使用函数中的变量(作用于局部非static变量),捕获列表指引lambda在其内部包含访问局部变量所需要的信息
//lambda可以直接使用局部static变量和所在函数之外声明的变量
[sz] (const string &a) { return a.size() < sz; };
//using
auto wc = find_if(w.begin(), w.end(), [sz](const string &a) {return a.size() < sz;});
//隐式捕获 =,为值捕获；&,为引用捕获.
//混合使用隐式捕获和显示捕获时，捕获类型不同
[=] (const string &a) { return a.size() < sz; };
//改变捕获变量的值
void fcn3()
{
    size_t v1 = 42;
    auto f = [v1] () mutable { return ++v1;};
    v1 = 0;
    auto j = f();
}
//指定lambda返回类型, {func body} 中包含非return语句时,默认返回类型为void,
[] (int i) -> int {if (i < 0) return -i; else return i;};

//#include <functional>
//auto newCallback = bind(callable, arg_list);
//bind为一个通用函数适配器，它接受一个可调用对象，生成一个新的可调用对象来适应原对象的参数列表。
//arg_list中的_n为占位符
bool checksize(const string &s, string::size_type len)
{
    return s.size() < len;
}
//std::placeholders::_1
auto check6 = bind(checksize, _1, 6);

bool flag = check6(s); //= checksize(s, 6);
//using
auto g = bind(f, a, b, _2, c, _1);
g(X,Y); // f(a, b, Y, c, X);
//绑定引用参数
ostream &print(ostream &os, const string &s, char c)
{
    return os << s << c;
}
//ref()
for_each(w.begin(), w.end(), bind(print, ref(os), _1, ' '));


