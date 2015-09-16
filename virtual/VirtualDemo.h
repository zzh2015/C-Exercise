#ifndef VIRTUALDEMO_H
#define VIRTUALDEMO_H

#include <iostream>
#include <string>

class BaseQ {
    public:
        BaseQ() = default;
        BaseQ(std::string &s, float p) :
            m_ISBN(s), m_Price(p) {}
        virtual ~BaseQ() = default;

        void Print() const { std::cout << "ISBN: " << m_ISBN << " "; }
        virtual float GetPrice(float coupon) const { return m_Price-coupon; }

        virtual void PrintAuthorInfo() final { std::cout << "zzh" << std::endl; }
    protected:
        float m_Price;

    private:
        std::string m_ISBN;
};

class DerivedQ : public BaseQ {
    public:
        DerivedQ() = default;
        DerivedQ(std::string &s, float p, float d) :
            BaseQ(s, p), m_Discount(d) {}
        ~DerivedQ() = default;

        float GetPrice(float coupon) const  override { 
            return m_Price*m_Discount-coupon; }

    protected:

    private:
        float m_Discount;
};

#endif //VIRTUALDEMO_H

