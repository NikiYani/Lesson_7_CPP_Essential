#include <QCoreApplication>
#include <memory>
#include <iostream>
#include <string>

using namespace std;

struct Resource {
    weak_ptr<Resource> other;
};

void testWeakPtr() {
    auto firstInnerPtr = make_shared<Resource>();
    auto secondInnerPtr = make_shared<Resource>();

    firstInnerPtr->other = secondInnerPtr;
    secondInnerPtr->other = firstInnerPtr;

    secondInnerPtr->other.lock();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // weak_ptr

    testWeakPtr();

    //shared_ptr

    int *ptr = new int(100);

    shared_ptr<int> firstPtr = make_shared<int>(*ptr);

    delete ptr;

    {
        shared_ptr<int> secondPtr = firstPtr;

        cout << "firstPtr = " << *firstPtr << " secondPtr = " << *secondPtr << endl;

        *secondPtr = 9;

        cout << "firstPtr = " << *firstPtr << " secondPtr = " << *secondPtr << endl;

        cout << "count  = " << firstPtr.use_count() << endl;

    }

    cout << "firstPtr = " << *firstPtr << endl;

    cout << "count  = " << firstPtr.use_count() << endl;

    //unique_ptr

    unique_ptr<int> firstUniquePtr(new int(5));

    unique_ptr<int> secondUniquePtr(new int(8));

//    secondUniquePtr = std::move( firstUniquePtr );

    cout << "Address firstUniquePtr: " << firstUniquePtr.get() << "\n"
         << "Address secondUniquePtr: " << secondUniquePtr.get() << endl;

    if( firstUniquePtr.get() )
        cout << "firstUniquePtr = " << *firstUniquePtr << endl;
    if( secondUniquePtr.get() )
        cout << "secondUniquePtr = " << *secondUniquePtr << endl;

    return a.exec();
}
