#ifndef __TEXT_QUERY_H__
#define __TEXT_QUERY_H__

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class QueryResult;

extern std::ostream& print(std::ostream&, const QueryResult&);

class TextQuery {
    public:
        using line_no = std::vector<std::string>::size_type;

        TextQuery(std::ifstream&);
        QueryResult query(const std::string &) const;

    private:
        std::shared_ptr<std::vector<std::string>> file; //file line contents
        std::map<std::string, 
            std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {

    friend std::ostream& print(std::ostream&, const QueryResult&);

    public:
        using line_no = std::vector<std::string>::size_type;
        QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : 
            sought(s), lines(p), file(f)  {}

    private:
        std::string sought;
        std::shared_ptr<std::set<line_no>> lines;
        std::shared_ptr<std::vector<std::string>> file;
};


#endif

