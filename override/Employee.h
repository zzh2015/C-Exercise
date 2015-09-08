#ifndef EMPLOYYE_H
#define EMPLOYYE_H

#include <iostream>
#include <string>

class Employee {
    public:
       Employee() {
           m_No = 0;
           m_Name = "";
           m_Salary = 0.0f;
       }
       Employee(int no, std::string name, float salary) : 
           m_No(no), m_Name(name), m_Salary(salary) {}
       ~Employee() = default;

       friend std::istream &operator>>(std::istream &is, Employee &em);
       friend std::ostream &operator<<(std::ostream &os, const Employee &em);

    protected:

    private:
        int m_No;
        std::string m_Name;
        float m_Salary;
};

#endif  //EMPLOYYE_H

