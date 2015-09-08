#include "Employee.h"

std::istream &operator>>(std::istream &is, Employee &em)
{
    is >> em.m_No >> em.m_Name >> em.m_Salary;

    if (!is)
        em = Employee();

    return is;
}

std::ostream &operator<<(std::ostream &os, const Employee &em)
{
    os << em.m_No << " " 
        << em.m_Name << " "
        << em.m_Salary;

    return os;
}

