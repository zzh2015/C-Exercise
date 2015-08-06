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
        
    创建智能指针:   shared_ptr<string> p1; //可指向string

                    shared_ptr<list<int>> p2; //可指向list<int>
    
    //操作CP 12.1.1 P401
    
    2) make_shared函数

    在动态内存中分配一个对象，并初始化它，返回指向此对象的 shared_ptr.
    
    shared_ptr<string> p1 = make_shared<string>(10, '0');
    
    auto p2 = make_shared<vector<string>> ();
    
    3) shared_ptr 通过引用计数管理内存。

    
    

