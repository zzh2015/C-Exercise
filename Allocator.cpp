#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    allocator<string> alloc;

    auto const p = alloc.allocate(5); // 分配5个未初始化的string

    auto q = p;

    string str;

    cout << "cin 5 strings:" << endl;
    while (cin>>str && q!=p+4) 
        alloc.construct(q++, str); //构造string

    cout << "cout strings:" << endl;
    for (auto tmp=p; tmp!=p+4; )
        cout << *tmp++ << endl;

    while (q != p)
        alloc.destroy(--q); //销毁构造的元素

    alloc.deallocate(p, 5); //释放内存

    cout << "leave main" << endl;

    return 0;
}
