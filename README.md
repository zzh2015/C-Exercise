# C-Exercise
some C++ Primer Exercise
#关联容器
1. 按关键字有序保存元素
    map 关联数组，保存键值对

    set 关键字即值

    multimap 关键字可重复的map

    multiset 关键字可重复的set

    #
    unordered_map 用哈西函数组织的map

    unordered_set 用哈西函数组织的set

    unordered_mutlimap

    unordered_multiset
2. pair类型
    pair用来生成特定类型的模板。包含在 utility 中。
    
    pair<T1, T2> p;

    pair<T1, T2> p(v1, v2);

    pair<T1, T2> p = {v1, v2};

    make_pair(v1, v2); //用v1、v2初始化pair，pair类型由v1、v2类型推断。
#动态内存与智能指针
1. 智能指针
    shared_ptr 允许多个指针指向同一个对象;

    unique_ptr 独占所指向的对象;

    weak_ptr 弱引用，伴随类指向shared_ptr 所管理的对象。
    
    1) shared_ptr 类
        
    创建智能指针:   
                    shared_ptr<string> p1; //可指向string

                    shared_ptr<list<int>> p2; //可指向list<int>
    
    //操作CP 12.1.1 P401
    
    2) make_shared函数

    在动态内存中分配一个对象，并初始化它，返回指向此对象的 shared_ptr.
    
                     shared_ptr<string> p1 = make_shared<string>(10, '0');
    
                     auto p2 = make_shared<vector<string>> ();
    
    3) shared_ptr 通过引用计数管理内存。

2. shared_ptr 和 new 结合使用

    1) 可以用 new 返回的指针来初始化智能指针 

                shared_ptr<double> p1; //空指针

                shared_ptr<int> p2(new int(1024));  //p2 指向一个值为 42 的 int
                
                shared_ptr<int> clone(int p) { return shared_ptr<int>(new int(p)); }
  

    2) 不要混合使用普通指针和智能指针

                
3. unique_ptr 必须采用直接初始化形式

                unique_ptr<int> p(new int(42)); //p指向一个int
    
    我们不能拷贝或赋值unique_ptr,但是可以通过release或reset将一个unique_ptr转移到另一个unique_ptr

                unique_ptr<string> p2(p1.release()); //p1置空，转移到p2

                unique_ptr<string> p3(new string("Tex")); p2.reset(p3.release());

                auto p = p3.release();

4. 传递unique_ptr参数 和 返回unique_ptr

                unique_ptr<int> clone(int p) {

                    return unique_ptr<int> (new int(p));

                    //unique_ptr<int> u(new int(p));

                    //return u;

                }

5. weak_ptr

    weak_ptr 绑定到一个 shared_ptr将不会改变 shared_ptr 的计数。

                auto p = make_ptr<int>(42);

                weak_ptr<int> wp(p);

    由于对象可能不存在，调用weak_ptr， 必须调用 lock：

                if (shared_ptr<int> np = wp.lock()) {//np不为空}

6. 动态数组
    
    标准库提供了一个可以管理new分配的unique_ptr版本。
                
                unique_ptr<int[]> up(new int[10]);
                
                up.release(); // 自动销毁
7. allocator类
    
    内存分配和对象构造分离。

                allocator<string> alloc;

                auto const p = alloc.allocate(n); // 分配n个未初始化的string
                
                auto q = p;
    
                alloc.construct(q++);
                
                alloc.construct(q++, 10, 'c');

                alloc.construct(q++, "hi");
               
                while (q != p) // 销毁构造的元素 
                    
                    alloc.destroy(--q);

                alloc.deallocate(p, n); //释放内存




    
    

