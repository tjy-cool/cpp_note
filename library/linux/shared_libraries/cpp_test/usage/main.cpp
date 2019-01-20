#include <iostream>
#include "Caluator.h"

using namespace std;

int main()
{
    Caluator cal;   // 新建一个计算器对象
    cout << " 12 + 23 = "     << cal.add(12 , 23)      << endl;
    cout << " 12.3 - 23.5 = " << cal.subtract(12 , 23) << endl;
    cout << " 12.12 * 23 = "  << cal.multiply(12 , 23) << endl;
    cout << " 12.0 / 23 = "   << cal.divide(12 , 23)   << endl;
    return 0;
}