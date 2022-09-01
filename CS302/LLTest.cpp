#include "LL.h"
#include <iostream>

int main()
{
    LL<int> l1;
    LL<int>::Iterator it, nil;

    for (int i = 0; i < 10; i++)
        l1.tailInsert(i + 1);

    LL<int> l2(l1);

    l2.headInsert(12);

    std::cout << "l1\n";

    for (it = l1.begin(); it != nil; it++)
        std::cout << *it << "\n";

    std::cout << "\nl2 (reversed)\n";

    for (it = l2.end(); it != nil; it--)
        std::cout << *it << "\n";

    std::cout << "\n";

    l1 = l2;

    l1.tailInsert(50);

    std::cout << "l1\n";

    for (it = l1.begin(); it != nil; it++)
        std::cout << *it << "\n";

    std::cout << "\nl2 (reversed)\n";

    for (it = l2.end(); it != nil; it--)
        std::cout << *it << "\n";

    std::cout << "\n";

    return 0;
}