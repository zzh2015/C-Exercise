#ifndef __STRBLOB_H__
#define __STRBLOB_H__

#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <vector>

class StrBlob {
    public:
        typedef std::vector<std::string>::size_type size_type;

        StrBlob();
        StrBlob(std::initializer_list<std::string> il);

        size_type size() const {return data->size();}
        
        //添加删除元素
        void push_back(const std::string &t) {data->push_back(t);}
        void pop_back();

        //元素访问
        std::string &front();
        std::string &back();

        //返回data迭代器
        std::vector<std::string>::iterator begin() const {return data->begin();} 
        std::vector<std::string>::iterator end() const {return data->end();} 

    private:
        std::shared_ptr<std::vector<std::string>> data;

        //data[i]不合法,抛出异常
        void check(size_type i, const std::string &msg) const;
};

#endif
