#include "VirtualDemo.h"

using namespace std;

int main(void)
{  
    string s1("1111-abcd"), s2("2222-disc"); 
    BaseQ base(s1, 200.0f);
    DerivedQ derived(s2, 400.0f, 0.87f);

    float coupon = 25.0f;

    BaseQ &b = base;
    BaseQ *pb = &derived;

    b.Print();
    cout << "the price is: " << b.GetPrice(coupon) << std::endl;

    pb->Print();
    cout << "the price is: " << pb->GetPrice(coupon) << std::endl;

    pb->PrintAuthorInfo();

    return 0;
}

