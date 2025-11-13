#include <iostream>
#include "SingleLL.h"
using namespace std;

class A
{
    int x;
    double y;
public:
    A(int x, double y) : x(x), y(y) {}
    bool operator==(const A& other) const
    {
        return (x == other.x && y == other.y);
    }
    friend ostream& operator<<(ostream& out, const A& a2);
};
ostream& operator<<(ostream& out, const A& a2) {
    out << "(" << a2.x << ", " << a2.y << ")  ";
    return out;
}


int main()
{
    // Test 2 pass
    cout << "===== Testing SingleLL<A> =====\n\n";

    SingleLL<A> list;

    cout << "Push front A(1, 1.1)\n";
    list.push_front(A(1, 1.1));
    cout << list << "\n\n";

    cout << "Push front A(2, 2.2)\n";
    list.push_front(A(2, 2.2));
    cout << list << "\n\n";

    cout << "Push back A(3, 3.3)\n";
    list.push_back(A(3, 3.3));
    cout << list << "\n\n";

    cout << "Insert at position 1: A(9, 9.9)\n";
    list.insert_at(1, A(9, 9.9));
    cout << list << "\n\n";

    cout << "Remove at position 2\n";
    list.remove_at(2);
    cout << list << "\n\n";

    cout << "Search for A(1, 1.1): "
        << (list.search(A(1, 1.1)) ? "Found" : "Not Found")
        << "\n\n";

    cout << "List size: " << list.size() << "\n\n";

    cout << "Pop front\n";
    list.pop_front();
    cout << list << "\n\n";

    cout << "Pop back\n";
    list.pop_back();
    cout << list << "\n\n";

    cout << "===== Testing Copy Constructor =====\n";
    SingleLL<A> copyList = list;
    cout << "copyList: " << copyList << "\n\n";

    cout << "===== Testing Copy Assignment =====\n";
    SingleLL<A> assignList;
    assignList = list;
    cout << "assignList: " << assignList << "\n\n";

    cout << "===== Testing Move Constructor =====\n";
    SingleLL<A> moveList = std::move(list);
    cout << "moveList: " << moveList << "\n";
    cout << "list after move: " << list << "\n\n";

    cout << "===== Testing Move Assignment =====\n";
    SingleLL<A> moveAssignList;
    moveAssignList = std::move(copyList);
    cout << "moveAssignList: " << moveAssignList << "\n";
    cout << "copyList after move: " << copyList << "\n\n";

    cout << "All tests completed!\n";

    // Test 1 pass
    //cout << "===== Testing Constructors =====\n";
    //SingleLL<int> list1;                    // empty
    //cout << "list1: " << list1 << "\n";

    //SingleLL<int> list2(10);               // single value constructor
    //cout << "list2: " << list2 << "\n";

    //cout << "\n===== Testing push_front =====\n";
    //list1.push_front(3);
    //list1.push_front(2);
    //list1.push_front(1);
    //cout << "list1 after push_front: " << list1 << "\n";

    //cout << "\n===== Testing push_back =====\n";
    //list1.push_back(4);
    //list1.push_back(5);
    //cout << "list1 after push_back: " << list1 << "\n";

    //cout << "\n===== Testing pop_front =====\n";
    //list1.pop_front();
    //cout << "list1 after pop_front: " << list1 << "\n";

    //cout << "\n===== Testing pop_back =====\n";
    //list1.pop_back();
    //cout << "list1 after pop_back: " << list1 << "\n";

    //cout << "\n===== Testing insert_at =====\n";
    //list1.insert_at(0, 99);       // insert at head
    //list1.insert_at(2, 77);       // insert in middle
    //list1.insert_at(list1.size(), 55);  // insert at end
    //cout << "list1 after insert_at: " << list1 << "\n";

    //cout << "\n===== Testing remove_at =====\n";
    //list1.remove_at(0);           // remove head
    //list1.remove_at(1);           // remove middle
    //list1.remove_at(list1.size() - 1); // remove last
    //cout << "list1 after remove_at: " << list1 << "\n";

    //cout << "\n===== Testing search =====\n";
    //cout << "Search 3: " << (list1.search(3) ? "Found" : "Not Found") << "\n";
    //cout << "Search 100: " << (list1.search(100) ? "Found" : "Not Found") << "\n";

    //cout << "\n===== Testing size() =====\n";
    //cout << "Size of list1: " << list1.size() << "\n";

    //cout << "\n===== Testing Copy Constructor =====\n";
    //SingleLL<int> list3 = list1;  // deep copy
    //cout << "list3 (copy of list1): " << list3 << "\n";

    //cout << "\n===== Testing Copy Assignment =====\n";
    //SingleLL<int> list4;
    //list4 = list1;
    //cout << "list4 (assigned from list1): " << list4 << "\n";

    //cout << "\n===== Testing Move Constructor =====\n";
    //SingleLL<int> list5 = std::move(list1);
    //cout << "list5 (moved from list1): " << list5 << "\n";
    //cout << "list1 after move: " << list1 << "\n";

    //cout << "\n===== Testing Move Assignment =====\n";
    //SingleLL<int> list6;
    //list6 = std::move(list2);
    //cout << "list6 (moved from list2): " << list6 << "\n";
    //cout << "list2 after move: " << list2 << "\n";

    //cout << "\n===== Testing clear() =====\n";
    //list3.clear();
    //cout << "list3 after clear: " << list3 << "\n";

    //cout << "\n===== All tests complete! =====\n";

	return 0;
}