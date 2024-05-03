//《C++标准库》


//C++11新特性：
/*
C：
lambda函数、智能指针、nullptr
新关键字auto、后置返回类型decltype
基于范围的for循环、
一致性初始化{}、noexcept、constexpr

类和对象：
类内初始化、初始化列表、
新关键字default、delete、override、final
移动构造函数、移动赋值运算符

Template C++：
可变参数模板、模板元编程、模板别名 

STL：
unordered_map、
cbegin()、cend()

*/


//对C-Style array 使用基于范围的for循环
#if 0
#include <iostream>

using namespace std;

int main()
{
    int array[] = { 1,2,3,4,5 };

    for (const auto& x : array)//补充：声明为一个const reference 可以避免非必要的复制操作
        cout << x << " ";

    return 0;
}
#endif


//shared_ptr的use_count()
//返回管理当前对象的不同 shared_ptr 实例(包含 this )数量。若无管理对象，则返回 0
#if 0
#include <iostream>

using namespace std;

int main()
{
    auto pNico1 = make_shared<string>("Nico");
    auto pNico2(pNico1);

    cout << pNico1.use_count() << " " << pNico2.use_count();

    //显示为2  2

    return 0;
}
#endif
//补充：
//shared_ptr<X>(new x(…))
//执行了二次分配：一次针对X,一次针对shared pointer的控制区块(用来管理使用次数)。
//如果替换为
//make_shared<X>(…)
//会快速很多，只执行一次分配而且比较安全，
// 因为“X分配成功而其控制区块却分配失败”是不可能发生的。


//shared_ptr和unique_ptr用法区别
#if 0
#include <iostream>

int main()
{
    // shared_ptr
    // get and attach shared memory for 100 ints:
    //写法一：
    std::shared_ptr<int> sp(new int[100], [](int* p)
        { delete[]p; }
    );
    //写法二：
    std::shared_ptr<int> sp1(new int[100], std::default_delete<int[]>());

    // unique_ptr
    //写法一：
    std::unique_ptr<int[]> up(new int[100]);
    //写法二：
    std::unique_ptr<int, void (*)(int*)> up1(new int[100], [](int* p) {
        delete[]p;
        });
    //错误写法：
    /*std::unique_ptr<int[], void(*)(int*)> up1(new int[100], []() {
        });*/

    for (int i = 0; i < 100; ++i) {
        sp.get()[i] = i * 42;
        //错误写法：
        //*(smp + i) = i * 42;
    }

    for (int i = 0; i < 100; ++i) {
        //写法一：
        up.get()[i] = i * 42;
        //写法二：
        up[i] = i * 42;//***注***上面若用写法二创建智能指针，就不能用该写法二访问元素
    }

    // deal with shared memory somewhere else:
    //...
    std::cout << "<return>" << std::endl;
    std::cin.get();

    // release shared memory here:
    sp.reset();
    //...
}
#endif


//weak_ptr
//用于协助管理shared_ptr所管理的对象，用于解决shared_ptr的循环引用问题
//weak_ptr允许你观察到一个对象，但不增加其引用计数，它只是指向shared_ptr
//所管理的对象的引用，当需要使用该对象时，可通过lock()方法
//理解为【共享但不拥有】
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Person {
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<weak_ptr<Person>> kids;  // weak pointer !!!

    Person(const string& n,
        shared_ptr<Person> m = nullptr,
        shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f) {
    }

    ~Person() {
        cout << "delete " << name << endl;
    }
};

shared_ptr<Person> initFamily(const string& name)
{
    shared_ptr<Person> mom(new Person(name + "'s mom"));
    shared_ptr<Person> dad(new Person(name + "'s dad"));
    shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

int main()
{
    shared_ptr<Person> p = initFamily("nico");

    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico's mom: "
        << p->mother->kids[0].lock()->name << endl;

    p = initFamily("jim");
    cout << "jim's family exists" << endl;
}
#endif


//如果你将同一个动态分配的内存地址传递给多个 shared_ptr 实例来管理，
//会导致程序出现未定义的行为，
//这是因为多个 shared_ptr 实例会各自尝试释放同一个内存地址，
//可能导致重复释放内存，从而引发问题
//一个动态分配的内存空间只能由【一组】shared_ptr管理
#if 0
#include <iostream>

using namespace std;

int main()
{
    //正确写法
    //shared_ptr<int>sp1(new int);
    //shared_ptr<int>sp2(sp1);

    //错误写法：
    //一个动态分配的内存空间由【两组】shared_ptr管理
    int* p = new int;
    shared_ptr<int>sp1(p);
    shared_ptr<int>sp2(p);

    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;

    return 0;
}
#endif


//unique_ptr
//关于其复制构造函数和赋值运算符重载函数
//实参都要用到move(...)
//补充：
//函数是接收端：实参用move(...)
//函数是供应端：return语句不需要加上move(...)


//计算程序的执行时间
#if 0
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std;

int main()
{
    auto system_start = chrono::system_clock::now();

    Sleep(5000);

    auto diff = chrono::system_clock::now() - system_start;
    //                                                               微秒
    auto sec = chrono::duration_cast<chrono::microseconds>(diff);

    cout << sec.count() << endl;

    return 0;
}
#endif


//使用array代替传统数组
#if 0
#include <iostream>
#include <array>
using namespace std;

void Print(const array<int, 5>& myarray);

int main()
{
    array<int, 5>myarray{ 1,2 };

    Print(myarray);

    return 0;
}
void Print(const array<int, 5>& myarray)
{
    for (auto x : myarray)
        cout << x << " ";
}
#endif
//补充：
/*
用array相比于常规数组的优势：
1.安全性和类型检查
array<int,5>myarray={};
cout<<myarray.at(10);//报错
而常规数组会导致不明确行为
2.便捷的传递与复制
而常规数组在传递给函数时会退化为指针
3.内置方法和功能
有size()、front()等方法
4.与其他STL兼容
可用sort()、copy()等
*/


//容器可以分为三大类：
//序列式容器
//关联式容器
//无序(关联式)容器


//从标准输入读取string，排序然后打印(去掉重复的字符串)
//自己写的方法：
#if 0
#include <iostream>
#include <string>
#include <set>
//#include <algorithm>
using namespace std;

int main()
{
    string str[10];

    string tmp;
    int index = 0;
    while (cin >> tmp)
    {
        str[index++].append(tmp);
    }

    //qsort(str,index,);//每个元素大小不一，不能用qsort()
   /* sort(str,str+index);

    for (const auto& x : str)
        cout << x << endl;*/

    set<string> se;

    for (int i = 0; i < index; ++i)
    {
        se.insert(str[i]);
    }

    for (const auto& x : se)
        cout << x << endl;

    return 0;
}
#endif
//法一：
#if 0
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{
    vector<string> coll;

    //使用串流迭代器
    // read all words from the standard input
    // - source: all strings until end-of-file (or error)
    // - destination: coll (inserting)
    copy(istream_iterator<string>(cin),    // start of source
        istream_iterator<string>(),       // end of source 
        back_inserter(coll));             // destination

    //istream_iterator<string>(cin)
    //会产生一个可从“标准输入串流(standard input stream) cin”读取数据的 stream iterator。
    //其中的 template 实参 string表示这个 stream iterator专司读取该种类型的元素(string 类
    // 型将在第13章介绍)。这些元素通过一般的 operator >>被读取进来。因此每当算法企图
    //处理下一元素时，istream iterator 就会将这种企图转化为以下行动：
    //cin >> string
    //针对 string 而执行的 input操作符通常读取以空白分隔的文字(见 13.2.10 节第 677页),
    //因此上述算法的行为将是“逐字读取”(word by word)。

    //istream_iterator<string>()
    //会调用istream iterator的 default 构造函数，产生一个代表“串流结束符”(end - of - stream)
    //的迭代器，这个东西代表的意义是：你不能再从中读取任何东西。

    // sort elements
    sort(coll.begin(), coll.end());

    // print all elements without duplicates
    // - source: coll
    // - destination: standard output (with newline between elements)
    unique_copy(coll.cbegin(), coll.cend(),           // source
        ostream_iterator<string>(cout, "\n")); // destination
}
#endif
//法二：
#if 0
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
using namespace std;

int main()
{
    // create a string set
    // - initialized by all words from standard input
    set<string> coll((istream_iterator<string>(cin)),
        istream_iterator<string>());

    // print all elements
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<string>(cout, "\n"));
}
#endif
//法三：
#if 0
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    // create a string vector
    // - initialized by all words from standard input
    vector<string> coll((istream_iterator<string>(cin)),
        istream_iterator<string>());

    // sort elements
    sort(coll.begin(), coll.end());

    // print all elements ignoring subsequent duplicates
    unique_copy(coll.cbegin(), coll.cend(),
        ostream_iterator<string>(cout, "\n"));
}
#endif
//比较
// 方法1. 使用 copy() 和 ostream_iterator与方法2. 使用基于范围的for循环
//两种输出方法
//方法1.非常简洁，一行代码即可完成任务。可以支持普通数组如copy(flag,flag+10000,ostream_iterator<bool>(cout));
// 但是，它有些局限性，例如无法进行更复杂的处理或转换输出。
//方法2.更加灵活和直观。它使代码更易读，尤其是在需要对输出进行更多控制或转换时。
// 你可以在循环内部添加逻辑，对输出进行格式化或添加其他操作。


//删除容器中的元素（要保证“斩草除根”）
#if 0
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>
using namespace std;

int main()
{
    list<int> coll;

    // insert elements from 6 to 1 and 1 to 6
    for (int i = 1; i <= 6; ++i)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    // print all elements of the collection
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;

    // remove all elements with value 3
    // - retain new end
    list<int>::iterator end = remove(coll.begin(), coll.end(), 3);

    // print resulting elements of the collection
    copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
    cout << endl;

    // print number of removed elements
    cout << "number of removed elements: "
        << distance(end, coll.end()) << endl;

    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    //“斩草除根”
    // remove "removed" elements 
    coll.erase(end, coll.end());

    // print all elements of the modified collection
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<int>(cout, " "));

    cout << endl;
}
//用单一语句来删除元素
//coll.erase(remove(coll.begin(),coll.end(),3),coll.end());

//***注***
//对于非关联式容器可以使用remove方法删除指定的元素
//remove方法【不改变集合中元素的个数】
//逻辑上是要被删除的元素被其后的元素覆盖，而末尾那些未被覆盖的元素原封不动
//但逻辑上已经不属于这个集合了
//用remove()函数搭配erase()方法可以斩草除根

//对于关联式容器可以直接使用erase方法删除元素

//最后
//对于list容器，其类中有专门的优化效率的remove()、remove_if()方法，
//因此对于算法vs成员函数
//优先选用成员函数即方法
#endif


//以函数作为算法的实参
//使用普通函数作为单参判断式(Unary Predicate)(一元谓词函数)
#if 0
#include <list>
#include <algorithm>
#include <iostream>
#include <cstdlib>      // for abs()
using namespace std;

// predicate, which returns whether an integer is a prime number
bool isPrime(int number)
{
    // ignore negative sign
    number = abs(number);

    // 0 and 1 are no prime numbers
    if (number == 0 || number == 1) {
        return false;
    }

    // find divisor that divides without a remainder
    int divisor;
    for (divisor = number / 2; number % divisor != 0; --divisor)
    {
        ;
    }

    // if no divisor greater than 1 is found, it is a prime number
    return divisor == 1;
}

int main()
{
    list<int> coll;

    // insert elements from 24 to 30
    for (int i = 24; i <= 30; ++i)
    {
        coll.push_back(i);
    }

    // search for prime number
    auto pos = find_if(coll.cbegin(), coll.cend(),  // range
        isPrime);                    // predicate
    if (pos != coll.end())
    {
        // found
        cout << *pos << " is first prime number found" << endl;
    }
    else
    {
        // not found
        cout << "no prime number found" << endl;
    }
}
#endif


//不用函数作为算法的实参
//而是使用重载<运算符作为排序依据
#if 0
#include <algorithm>
#include <deque>
#include <string>
#include <iostream>
using namespace std;

/* class Person
 */
class Person
{
private:
    string fn;    // first name
    string ln;    // last name
public:
    Person() {
    }
    Person(const string& f, const string& n)
        : fn(f), ln(n) {
    }
    string firstname() const;
    string lastname() const;
    // ...
};

inline string Person::firstname() const {
    return fn;
}

inline string Person::lastname() const {
    return ln;
}

ostream& operator<< (ostream& s, const Person& p)
{
    s << "[" << p.firstname() << " " << p.lastname() << "]";
    return s;
}


/* binary function predicate:
 * - returns whether a person is less than another person
 */
bool operator<(const Person& p1, const Person& p2)
{
    /* a person is less than another person
     * - if the last name is less
     * - if the last name is equal and the first name is less
     */
    return p1.lastname() < p2.lastname() ||
        (p1.lastname() == p2.lastname() &&
            p1.firstname() < p2.firstname());
}

int main()
{
    // create some persons
    Person p1("nicolai", "josuttis");
    Person p2("ulli", "josuttis");
    Person p3("anica", "josuttis");
    Person p4("lucas", "josuttis");
    Person p5("lucas", "otto");
    Person p6("lucas", "arm");
    Person p7("anica", "holle");

    // insert person into collection coll
    deque<Person> coll;
    coll.push_back(p1);
    coll.push_back(p2);
    coll.push_back(p3);
    coll.push_back(p4);
    coll.push_back(p5);
    coll.push_back(p6);
    coll.push_back(p7);

    // print elements
    cout << "deque before sort():" << endl;
    deque<Person>::iterator pos;
    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        cout << *pos << endl;
    }

    // sort elements
    sort(coll.begin(), coll.end());
    //sort 函数内部使用 < 运算符来确定元素的顺序。
    // 在这种情况下，sort 使用为 Person 类型重载的 operator<。
    // 这就是重载 < 运算符在这段代码中的作用：
    // 定义 Person 对象之间的排序顺序

    // print elements
    cout << "deque after sort():" << endl;
    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        cout << *pos << endl;
    }
}
#endif


//以函数作为算法的实参
//使用普通函数作为双参判断式(Binary Predicate)(二元谓词函数)
#if 0
#include <algorithm>
#include <deque>
#include <string>
#include <iostream>
using namespace std;

/* class Person
 */
class Person
{
private:
    string fn;    // first name
    string ln;    // last name
public:
    Person() {
    }
    Person(const string& f, const string& n)
        : fn(f), ln(n) {
    }
    string firstname() const;
    string lastname() const;
    // ...
};

inline string Person::firstname() const {
    return fn;
}

inline string Person::lastname() const {
    return ln;
}

ostream& operator<< (ostream& s, const Person& p)
{
    s << "[" << p.firstname() << " " << p.lastname() << "]";
    return s;
}


/* binary function predicate:
 * - returns whether a person is less than another person
 */
bool personSortCriterion(const Person& p1, const Person& p2)
{
    /* a person is less than another person
     * - if the last name is less
     * - if the last name is equal and the first name is less
     */
    return p1.lastname() < p2.lastname() ||
        (p1.lastname() == p2.lastname() &&
            p1.firstname() < p2.firstname());
}

int main()
{
    // create some persons
    Person p1("nicolai", "josuttis");
    Person p2("ulli", "josuttis");
    Person p3("anica", "josuttis");
    Person p4("lucas", "josuttis");
    Person p5("lucas", "otto");
    Person p6("lucas", "arm");
    Person p7("anica", "holle");

    // insert person into collection coll
    deque<Person> coll;
    coll.push_back(p1);
    coll.push_back(p2);
    coll.push_back(p3);
    coll.push_back(p4);
    coll.push_back(p5);
    coll.push_back(p6);
    coll.push_back(p7);

    // print elements
    cout << "deque before sort():" << endl;
    deque<Person>::iterator pos;
    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        cout << *pos << endl;
    }

    // sort elements
    sort(coll.begin(), coll.end(),    // range
        personSortCriterion);       // sort criterion

    // print elements
    cout << "deque after sort():" << endl;
    for (pos = coll.begin(); pos != coll.end(); ++pos) {
        cout << *pos << endl;
    }
}
#endif


//以函数作为算法的实参
//使用lambda作为双参判断式(Binary Predicate)(二元谓词函数)，作为排序准则
#if 0
#include <algorithm>
#include <deque>
#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    string firstname() const;
    string lastname() const;
    //...
};

int main()
{
    deque<Person> coll;
    //...

    // sort Persons according to lastname (and firstname):
    sort(coll.begin(), coll.end(),                // range
        [](const Person& p1, const Person& p2) { // sort criterion
            return p1.lastname() < p2.lastname() ||
                (p1.lastname() == p2.lastname() &&
                    p1.firstname() < p2.firstname());
        });
    //...

    //写法2：
    auto cmp = [](const Person& p1, const Person& p2) { // sort criterion
        return p1.lastname() < p2.lastname() ||
            (p1.lastname() == p2.lastname() &&
                p1.firstname() < p2.firstname());
        };

    sort(coll.begin(), coll.end(), cmp);
}
#endif
//以函数作为算法的实参
//使用函数对象作为双参判断式(Binary Predicate)(二元谓词函数)，作为排序准则
#if 0
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    string firstname() const;
    string lastname() const;
    //...
};

class Cmp
{
public:
    bool operator()(const Person& p1, const Person& p2) const
    {
        return p1.lastname() < p2.lastname() ||
            (p1.lastname() == p2.lastname() &&
                p1.firstname() < p2.firstname());
    }
};

int main()
{
    vector<Person> coll;
    //...

    // sort Persons according to lastname (and firstname):
    sort(coll.begin(), coll.end(),                // range
    Cmp());
    //...

}
#endif


//***注***
//对于关联式容器，使用lambda时有特定的写法。(所以这种情况用lambda不推荐)
//推荐写为：//对于关联容器，实现运行期指定排序准则
#if 0
#include <algorithm>
#include <set>
#include <string>
#include <iostream>
using namespace std;

class Person {
public:
    string firstname() const;
    string lastname() const;
    //...
};

int main()
{
    auto cmp = [](const Person& p1, const Person& p2) { // sort criterion
        return p1.lastname() < p2.lastname() ||
            (p1.lastname() == p2.lastname() &&
                p1.firstname() < p2.firstname());
        };

    std::set<Person, decltype(cmp)> coll(cmp);
    //由于 set 声明式需要指明 lambda类型，所以我们必须使用decltype(见3.1.11 节第 32 页), 
    // 它会为一个 lambda对象(上例的 cmp)产出类型。
    // 注意，你也必须把 lambda 对象传给coll的构造函数，
    // 否则coll会调用被传入的排序准则的 default 构造的数，而根据C++语言规则，
    // lambda没有 default 构造函数，也没有 assignment 操作符
}
#endif


//使用函数对象，实现在执行时确定函数
#if 0
#include <list>
#include <algorithm>
#include <iostream>

#include <string>

// PRINT_ELEMENTS()
// - prints optional string optstr followed by
// - all elements of the collection coll
// - in one line, separated by spaces
template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

using namespace std;

// function object that adds the value with which it is initialized
class AddValue
{
private:
    int theValue;    // the value to add
public:
    // constructor initializes the value to add
    AddValue(int v) : theValue(v)
    {}

    // the "function call" for the element adds the value
    void operator() (int& elem) const
    {
        elem += theValue;
    }
};

int main()
{
    list<int> coll;

    // insert elements from 1 to 9
    for (int i = 1; i <= 9; ++i)
    {
        coll.push_back(i);
    }

    PRINT_ELEMENTS(coll, "initialized:                ");

    // add value 10 to each element
    for_each(coll.begin(), coll.end(),    // range
        AddValue(10));               // operation

    PRINT_ELEMENTS(coll, "after adding 10:            ");

    // add value of first element to each element
    for_each(coll.begin(), coll.end(),    // range
        AddValue(*coll.begin()));    // operation

    PRINT_ELEMENTS(coll, "after adding first element: ");

    retunr 0;
}
#endif
//使用函数对象的优势：
//1.函数对象是一种带状态(with state)的函数。
//2.每个函数对象有其自己的类型。
//3.函数对象通常比寻常函数速度快。


//函数适配器bind
#if 0
#include <set>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

using namespace std;
using namespace std::placeholders;//可以使用占位符如_1

int main()
{
    set<int, greater<int>> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    deque<int> coll2;

    // Note: due to the sorting criterion greater<>() elements have reverse order:
    PRINT_ELEMENTS(coll1, "initialized: ");

    // transform all elements into coll2 by multiplying them with 10
    transform(coll1.cbegin(), coll1.cend(),      // source
        back_inserter(coll2),             // destination
        bind(multiplies<int>(), _1, 10));   // operation

    PRINT_ELEMENTS(coll2, "transformed: ");

    // replace value equal to 70 with 42
    replace_if(coll2.begin(), coll2.end(),       // range
        bind(equal_to<int>(), _1, 70),     // replace criterion
        42);                             // new value

    PRINT_ELEMENTS(coll2, "replaced:    ");

    // remove all elements with values between 50 and 80
#if 0
    coll2.erase
    (
        remove_if
        (
            coll2.begin(), coll2.end(),
            bind
            (
                logical_and<bool>(), bind(greater_equal<int>(), _1, 50), bind(less_equal<int>(), _1, 80)
            )
        ),
        coll2.end()
    );
#endif

#if 1
    coll2.erase(
        remove_if
        (coll2.begin(), coll2.end(),
            [](int num)
            {
                return num >= 50 && num <= 80;
            }
        ),
        coll2.end()
    );
#endif

    PRINT_ELEMENTS(coll2, "removed:     ");

    return 0;
}
#endif


//STL只支持value语义，不支持reference语义

//STL的迭代器可能会因为其他动作的副作用而变得无效。例如：
//对 vector 和 deque 而言，一旦发生元素的安插、删除或重新分配。//***注***
//对无序容器而言，一旦发生 rehashing(重新散列)。

//***注***
//对于vector容器
// 安插操作：【可能】使 reference、pointer 和 iterator失效
// (译注：因为安插可能导致 vector 重新分配)。
// 你可以使用reserve()保留适当容量，避免重新分配内存。
// 如此一来，只要保留的容量尚有富余，就不必担心reference失效。
// 删除操作：vector的容量不会缩减，便可确定，【删除点之前】的
// 元素的reference、pointer 和 iterator才保持有效。(P260)
//补充：
//【安插】或【移除】元素，都会使“作用点”之后的各元素的
//  reference、pointer 和 iterator 失效。
// 如果【安插】动作甚至引发内存重新分配，那么该容器身上的
// 所有reference、 pointer 和 iterator 会失效。

//对于deque容器
//【除了头尾两端】，在任何地点【安插】或【删除】元素都将导致指向deque 元素的
// 任何 pointer、reference 和 iterator 失效。
// 不过，deque的内存重分配优于 vector, 因为其内部结构显示，
// deque 不必在内存重新分配时复制所有元素。

//(可以查看//移除元素，并避免使用一个【暂时】无效的迭代器)


//对于容器，不要以迭代器表现“第一元素的地址”
#if 0
#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<int, 5>myarray{ 0 };

    //cout << (int*)(myarray.begin() )<< endl;//迭代器无法强制转换为指针

    cout << myarray.data() << endl;

    //data()：返回指向数组首元素的指针。
    //begin()：返回指向数组第一个元素的迭代器。

    //data() 方法在使用 C 函数或者需要直接传递数组给某些 C 接口时非常有用，
    // 因为它返回一个指向数组的指针，与 C 数组的使用方式相符合。

    printf("%p\n", myarray.data());
    printf("%p\n", myarray.begin());

    return 0;
}
#endif


//使用tuple
#if 0
#include <iostream>
#include <tuple>
#include <array>
using namespace std;

int main()
{
    tuple<int, int, int> tuple1{ 1,2,3 };
    cout << get<0>(tuple1) << endl;

    tuple1 = make_tuple(4, 5, 6);
    cout << get<1>(tuple1) << endl;

    //array提供了tuple接口
    array<int, 5>a1{ 1,2,3 };
    cout << get<1>(a1) << endl;

    return 0;
}
#endif


//accumulate() 求积累值     进阶用法
//快捷打印：
// 1-2-3-4-5-6-7-8-9-10 和 10-9-8-7-6-5-4-3-2-1
#if 0
#include <iostream>
#include <vector>
#include <numeric>
#include <string>

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int sum = std::accumulate(v.begin(), v.end(), 0);

    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());

    auto dash_fold = [](std::string a, int b) {
        return std::move(a) + '-' + std::to_string(b);
        };

    //错误写法：
    /*
    auto dash_fold = [](int a, int b) {
        return std::to_string(a) + '-' + std::to_string(b);
        };
    */
    //原因：
    //accumulate()实现方法：
    /*
template<class InputIt, class T, class BinaryOperation>
constexpr // C++20 起
T accumulate(InputIt first, InputIt last, T init,
             BinaryOperation op)
{
    for (; first != last; ++first) {
        init = op(std::move(init), *first); // C++20 起有 std::move //当函数返回一个 unique_ptr 就不需要move()
    }
    return init;
}
    */

    std::string s = std::accumulate(std::next(v.begin(), 1), v.end(),
        std::to_string(v[0]), // 用首元素开始
        dash_fold);

    // 使用逆向迭代器右折叠
    std::string rs = std::accumulate(std::next(v.rbegin()), v.rend(),
        std::to_string(v.back()), // 用首元素开始
        dash_fold);

    std::cout << "sum: " << sum << '\n'
        << "product: " << product << '\n'
        << "dash-separated string: " << s << '\n'
        << "dash-separated string (right-folded): " << rs << '\n';
}
#endif
//也可以用transform()来配合accumulate()实现相同功能
#if 0
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <algorithm>

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::string firstElement = std::to_string(v[0]);

    // 使用 std::transform 将整数转换为字符串
    //***注***
    //因为accumulate()的原理上
    //是会用到容器v的第一个元素，并在其后【累积】
    //所以不妨只处理容器v中第二个元素到末尾元素
    std::vector<std::string> stringValues(v.size() - 1);
    std::transform(std::next(v.begin(), 1), v.end(), stringValues.begin(),
        [](int value) { return std::to_string(value); });

    // 使用 std::accumulate 将字符串连接起来
    std::string s = std::accumulate(stringValues.begin(), stringValues.end(),
        firstElement,
        [](std::string a, std::string b)
        {
            return std::move(a) + '-' + std::move(b);
        });

    // 使用逆向迭代器右折叠
    std::vector<std::string> reversedStringValues(v.size() - 1);
    std::transform(std::next(v.rbegin()), v.rend(),
        reversedStringValues.begin(),
        [](int value) { return std::to_string(value); });

    std::string rs = std::accumulate(reversedStringValues.begin(), reversedStringValues.end(),
        std::to_string(v.back()),
        [](std::string a, std::string b) {
            return std::move(a) + '-' + std::move(b);
        });

    std::cout
        << "dash-separated string: " << s << '\n'
        << "dash-separated string (right-folded): " << rs << '\n';
}
#endif


//swap()后，vector的所有引用、指针、迭代器都失效了
//因为这些东西都指向原本位置
#if 0
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int>v1{ 1,2,3 };
    vector<int>v2{ 4,5 };

    auto it1 = next(v1.begin());
    auto it2 = next(v2.begin());

    cout << *it1 << " " << *it2 << endl;

    v1.swap(v2);

    //交换后迭代器与引用保持与其原来的元素关联
    cout << *it1 << " " << *it2 << endl;

    return 0;
}
#endif


//deque用法
#if 0
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    // create empty deque of strings
    deque<string> coll;

    // insert several elements
    coll.assign(3, string("string"));
    coll.push_back("last string");
    coll.push_front("first string");

    // print elements separated by newlines
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<string>(cout, "\n"));
    cout << endl;

    // remove first and last element
    coll.pop_front();
    coll.pop_back();
    //最终余下3个元素

    // insert "another" into every element but the first
    for (unsigned i = 1; i < coll.size(); ++i) {
        coll[i] = "another " + coll[i];
    }

    // change size to four elements
    coll.resize(4, "resized string");
    //第一个参数指定新的大小
    //第二个参数指定用于填充调整大小操作可能会创建的任何新元素的值，
    //即字符串“resized string”。如果元素超过 4 个，多余的元素将被删除以使大小为 4。

    // print elements separated by newlines
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<string>(cout, "\n"));
}
#endif


//list用法
#if 0
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

void printLists(const list<int>& l1, const list<int>& l2)
{
    cout << "list1: ";
    copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "list2: ";
    copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << endl;
}

int main()
{
    // create two empty lists
    list<int> list1, list2;

    // fill both lists with elements
    for (int i = 0; i < 6; ++i) {
        list1.push_back(i);
        list2.push_front(i);
    }
    printLists(list1, list2);

    // insert all elements of list1 before the first element with value 3 of list2
    // - find() returns an iterator to the first element with value 3
    list2.splice(
        find(list2.begin(), list2.end(), 3),// destination position       
        list1);                          // source list
    printLists(list1, list2);

    // move first element of list2 to the end
    list2.splice(
        list2.end(),        // destination position
        list2,              // source list
        list2.begin());     // source position
    printLists(list1, list2);

    // sort second list, assign to list1 and remove duplicates
    list2.sort();
    list1 = list2;
    list2.unique();
    printLists(list1, list2);

    // merge both sorted lists into the first list
    list1.merge(list2);
    printLists(list1, list2);
}
#endif


//forward_list用法
#if 0
#include <forward_list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

void printLists(const string& s, const forward_list<int>& l1,
    const forward_list<int>& l2)
{
    cout << s << endl;
    cout << " list1: ";
    copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << " list2: ";
    copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    // create two forward lists
    forward_list<int> list1 = { 1, 2, 3, 4 };
    forward_list<int> list2 = { 77, 88, 99 };
    printLists("initial:", list1, list2);

    // insert six new element at the beginning of list2
    list2.insert_after(list2.before_begin(), 99);
    list2.push_front(10);
    list2.insert_after(list2.before_begin(), { 10,11,12,13 });
    printLists("6 new elems:", list1, list2);

    // insert all elements of list2 at the beginning of list1
    list1.insert_after(list1.before_begin(),
        list2.begin(), list2.end());
    printLists("list2 into list1:", list1, list2);

    // delete second element and elements after element with value 99
    list2.erase_after(list2.begin());
    list2.erase_after(
        find(list2.begin(), list2.end(), 99),
        list2.end());
    printLists("delete 2nd and after 99:", list1, list2);

    // sort list1, assign it to list2, and remove duplicates
    list1.sort();
    list2 = list1;
    list2.unique();
    printLists("sorted and unique:", list1, list2);

    // merge both sorted lists into list1
    list1.merge(list2);
    printLists("merged:", list1, list2);
}
#endif


//Set 和 multiset 不提供任何操作函数可以直接访问元素。

//lower_bound()、upper_bound()、equal_range()
#if 0
#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int> c;

    c.insert(1);
    c.insert(2);
    c.insert(4);
    c.insert(5);
    c.insert(6);

    //lower_bound(3) 返回一个迭代器，指向第一个 >= 3 的元素。
    //在集合中，第一个>= 3 的元素是 4。
    cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
    //upper_bound(3) 返回第一个 > 3 的元素的迭代器。
    // 在集合中，第一个 > 3 的元素也是 4。
    cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
    //***理解***
    //equal_range(3) 返回一对迭代器，表示值为 3 的元素范围。
    //在本例中，由于不存在值为 3 的元素，
    //因此两个迭代器都指向第一个不小于 3 的元素，即 4。
    cout << "equal_range(3): " << *c.equal_range(3).first << " "
        << *c.equal_range(3).second << endl;
    cout << endl;

    cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
    cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
    cout << "equal_range(5): " << *c.equal_range(5).first << " "
        << *c.equal_range(5).second << endl;
}
#endif


//对于关联容器，实现运行期指定排序准则
#if 0
#include <iostream>
#include <set>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

// type for runtime sorting criterion
class RuntimeCmp
{
public:
    enum cmp_mode { normal, reverse };
private:
    cmp_mode mode;
public:
    // constructor for sorting criterion
    // - default criterion uses value normal
    RuntimeCmp(cmp_mode m = normal) : mode(m)
    {}
    // comparison of elements
    // - member function for any element type
    template <typename T>
    bool operator() (const T& t1, const T& t2) const
    {
        return mode == normal ? t1 < t2 : t2 < t1;
    }
    // comparison of sorting criteria
    bool operator== (const RuntimeCmp& rc) const
    {
        return mode == rc.mode;
    }
};

// type of a set that uses this sorting criterion
typedef set<int, RuntimeCmp> IntSet;

int main()
{
    // create, fill, and print set with normal element order
    // - uses default sorting criterion
    IntSet coll1 = { 4, 7, 5, 1, 6, 2, 5 };
    PRINT_ELEMENTS(coll1, "coll1: ");

    // create sorting criterion with reverse element order
    RuntimeCmp reverse_order(RuntimeCmp::reverse);

    // create, fill, and print set with reverse element order
#if 0 
    IntSet coll2(reverse_order);
    coll2 = { 4, 7, 5, 1, 6, 2, 5 };
#endif

    //或者写为：
#if 1
    set<int, RuntimeCmp> coll2({ 4, 7, 5, 1, 6, 2, 5 }, reverse_order);
#endif

    PRINT_ELEMENTS(coll2, "coll2: ");

    // assign elements AND sorting criterion
    coll1 = coll2;
    coll1.insert(3);
    PRINT_ELEMENTS(coll1, "coll1: ");

    // just to make sure...
    //对于set来说，由于 std::set 被设计为具有唯一的键，键同时也是值。
    // 因此，对于 std::set ，您可以在大多数情况下互换使用 key_comp 或 value_comp ，
    // 而不会出现明显差异
    //key_comp 方法：返回一个比较函数，该函数仅比较集合中元素的键
    //value_comp 方法：返回一个比较值的比较函数
    if (coll1.value_comp() == coll2.value_comp())
    {
        cout << "coll1 and coll2 have the same sorting criterion"
            << endl;
    }
    else
    {
        cout << "coll1 and coll2 have a different sorting criterion"
            << endl;
    }
}
#endif


//补充：对于sort()，用函数对象作为排序准则
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class sortregulation 
{
public:
    bool operator()(const string& s1, const string& s2) const
    {
        // 实现比较逻辑，例如按照字符串长度排序
        return s1.length() < s2.length();
    }
};

int main() 
{
    vector<string> DataInput;

    int NumSize;
    cin >> NumSize;

    string str = "";
    for (int i = 1; i <= NumSize; ++i) 
    {
        cin >> str;
        DataInput.push_back(str);
    }

    // 使用sortregulation的实例作为比较函数
    sort(DataInput.begin(), DataInput.end(), sortregulation());//使用默认的默认构造函数创建函数对象

    // 输出排序后的结果，用于验证排序是否正确
    for (const auto& s : DataInput)
    {
        cout << s << endl;
    }
}
#endif


//使用算法和lambda来操作map元素
//lambda的形参的新式写法
#if 0
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    map<string, float> strmap{ {"abc",1.1188},{"def",2.1} };

    //写法一：
    for_each(strmap.begin(), strmap.end(),
        [](const pair<const string, float>& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });

    //写法二：
    for_each(strmap.begin(), strmap.end(),
        [](const map<string, float>::value_type& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });

    //写法三：
    for_each(strmap.begin(), strmap.end(),
        [](const decltype(strmap)::value_type& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });

    return 0;
}
#endif


//六种方法向map或multimap内安插内容
#if 0
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    map<string, float> strmap{ {"abc",1.1188},{"def",2.1} };

    strmap.insert({ "a",1.1 });
    strmap.insert(map<string, float>::value_type("b", 2.2));
    strmap.insert(decltype(strmap)::value_type("c", 3.3));
    strmap.insert(pair<const string, float>("d", 4.4));
    strmap.insert(make_pair("e", 5));
    strmap["f"] = 6;//***注***
    //这种元素安插方式比惯常的 map安插方式慢，7.8.2节第340页
    //曾经谈过，原因是新元素必须先使用default 构造函数将 value 初始化，
    //而该初值马上又被真正的 value 覆盖。

    strmap["g"];
    //“operator[]的索引类型不必是整数”并不是它和寻常 array 唯一不同之处。如果你
    //选择某 key 作为索引，容器内却没有相应元素，那么map会自动安插一个新元素，
    // 其value将被其类型的 default 构造函数初始化。
    // 因此，你不可以指定一个“不具 default 构造函数”的value 类型。
    // 注意，基础类型都有一个 default 构造函数，设立初值0(见 3.2.1 节第 37页)。

    for_each(strmap.begin(), strmap.end(),
        [](const decltype(strmap)::value_type& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });

    return 0;
}
#endif


//移除元素，并避免使用一个【暂时】无效的迭代器
//(因为该迭代器指向了一个被删除的元素的位置)
//***注***
//如果某元素被删除，所有容器(除了vector和deque)
//都保证迭代器以及用以指向【未被删除的元素】的reference继续保持有效。
//而指向被删除的元素的迭代器都要进行该段代码展示的操作。
//补充：
//对于 vector,只有删除点之前的元素才保持有效。
#if 0
#include <iostream>
#include <map>
#include <algorithm>
#include <vector> 
using namespace std;

int main()
{
    map<string, float> strmap{ {"abc",1.1188},{"def",2.1} };

    strmap.insert({ "a",1.1 });
    strmap.insert(map<string, float>::value_type("b", 2.2));
    strmap.insert(decltype(strmap)::value_type("c", 3.3));
    strmap.insert(pair<const string, float>("d", 4.4));
    strmap.insert(make_pair("e", 5));

    for_each(strmap.begin(), strmap.end(),
        [](const decltype(strmap)::value_type& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });
    cout << endl;

    //错误的移除元素写法：
#if 0
    for (auto pos = strmap.begin(); pos != strmap.end(); ++pos)
    {
        if (pos->first == "a")
        {
            strmap.erase(pos);//pos会不再成为一个有效的迭代器，此后未对pos
        }                                 //重新设值就直接使用，会造成运行期间错误
    }
#endif

    //错误的处理写法：
#if 0
    for (auto pos = strmap.begin(); pos != strmap.end(); ++pos)
    {
        if (pos->first == "a")
        {
            pos = strmap.erase(pos);
        }

        if (abs(pos->second - 4.4) <= 0.00001)
        {
            pos = strmap.erase(pos);
        }

        //***注***
        //以下代码运行时会报错
        /*
        if (abs(pos->second - 5) <= 0.00001)
        {
            //因为erase()作用后，pos值为strmap.end()。++pos后指向无效位置。
            pos = strmap.erase(pos);
        }
        */
    }
#endif

    //正确写法：
    for (auto pos = strmap.begin(); pos != strmap.end(); )
    {
        if (pos->first == "a" || abs(pos->second - 4.4) <= 0.00001)
        {
            //***理解***
            //指向被擦除元素的引用和迭代器被非法化。其他引用和迭代器不受影响。
            //erase()返回一个迭代器指向【其后继的】元素
            //pos由此得到更新
            pos = strmap.erase(pos);
        }
        else
            ++pos;
    }

    for (auto pos = strmap.begin(); pos != strmap.end(); )
    {
        if (abs(pos->second - 5) <= 0.00001)
        {
            pos = strmap.erase(pos);
        }
        else
        {
            ++pos;
        }
    }

    strmap.erase("abc");

    for_each(strmap.begin(), strmap.end(),
        [](const decltype(strmap)::value_type& pa)
        {
            cout << pa.first << " " << pa.second << endl;
        });

    cout << endl;

    vector<int> vec{ 1,2,3,4,5,6,7,8,9 };

    for (auto i = vec.begin(); i != vec.end();)
    {
        if (*i == 3 || *i == 8)
            i = vec.erase(i);
        else
            ++i;
    }

    //错误写法：
    // for (auto i = vec.begin(); i != vec.end();++i)
    // {
    //     if (*i == 3 || *i == 8)
    //         i = vec.erase(i);
    // }

    copy(vec.cbegin(), vec.cend(),
        ostream_iterator<int>(cout, "\n"));

    return 0;
}
#endif


//multimap当做字典
#if 0
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // create multimap as string/string dictionary
    multimap<string, string> dict;

    // insert some elements in random order
    dict.insert({ {"day","Tag"}, {"strange","fremd"},
                    {"car","Auto"}, {"smart","elegant"},
                    {"trait","Merkmal"}, {"strange","seltsam"},
                    {"smart","raffiniert"}, {"smart","klug"},
                    {"clever","raffiniert"} });

    // print all elements
    cout.setf(ios::left, ios::adjustfield);
    cout << ' ' << setw(10) << "english "
        << "german " << endl;

    cout << setfill('-') << setw(20) << ""
        << setfill(' ') << endl;

    for (const auto& elem : dict) {
        cout << ' ' << setw(10) << elem.first
            << elem.second << endl;
    }
    cout << endl;

    // print all values for key "smart"
    //查找key对应的所有value值（前提是有这个key，若没有则不合适（详见：//lower_bound()、upper_bound()、equal_range()））
    string word("smart");
    cout << word << ": " << endl;
    for (auto pos = dict.lower_bound(word); pos != dict.upper_bound(word);
        ++pos)
    {
        cout << "    " << pos->second << endl;
    }

    // print all keys for value "raffiniert"
    //查找value对应的所有key值
    word = ("raffiniert");
    cout << word << ": " << endl;
    for (const auto& elem : dict)
    {
        if (elem.second == word)
        {
            cout << "    " << elem.first << endl;
        }
    }
}
#endif


//使用map、string并于运行期指定排序准则
#if 0
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// function object to compare strings
// - allows you to set the comparison criterion at runtime
// - allows you to compare case insensitive
class RuntimeStringCmp
{
public:
    // constants for the comparison criterion
    //                        普通模式    大小写无关模式
    enum cmp_mode { normal, nocase };
private:
    // actual comparison mode
    const cmp_mode mode;

    // auxiliary function to compare case insensitive
    static bool nocase_compare(char c1, char c2)
    {
        return toupper(c1) < toupper(c2);
    }
public:
    // constructor: initializes the comparison criterion
    RuntimeStringCmp(cmp_mode m = normal) : mode(m)
    {}

    // the comparison
    bool operator() (const string& s1, const string& s2) const
    {
        if (mode == normal)
        {
            return s1 < s2;
        }
        else
        {
            //lexicographical_compare() 字典序比较
            return lexicographical_compare(s1.begin(), s1.end(),
                s2.begin(), s2.end(), nocase_compare);
        }
    }
};

// container type:
// - map with
//       - string keys
//       - string values
//       - the special comparison object type
typedef map<string, string, RuntimeStringCmp> StringStringMap;

// function that fills and prints such containers
void fillAndPrint(StringStringMap& coll);

int main()
{
    // create a container with the default comparison criterion
    StringStringMap coll1;//使用一个RuntimeStringCmp的函数对象，以默认的normal为初值
    fillAndPrint(coll1);

    // create an object for case-insensitive comparisons
    RuntimeStringCmp ignorecase(RuntimeStringCmp::nocase);
    // create a container with the case-insensitive comparisons criterion
    StringStringMap coll2(ignorecase);
    //***理解***
    //使用的是   explicit map(const Compare & comp, const Allocator & alloc = Allocator());
    //使用一个类型为RuntimeStringCmp的函数对象，并以nocase为初值。nocase会令
    //这个函数对象以“大小写无关”模式完成字符串的比较和排序。

    fillAndPrint(coll2);
}

void fillAndPrint(StringStringMap& coll)
{
    // insert elements in random order
    coll["Deutschland"] = "Germany";
    coll["deutsch"] = "German";
    coll["Haken"] = "snag";
    coll["arbeiten"] = "work";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Unternehmen"] = "enterprise";
    coll["unternehmen"] = "undertake";
    coll["gehen"] = "walk";
    coll["Bestatter"] = "undertaker";

    // print elements
    cout.setf(ios::left, ios::adjustfield);
    for (const auto& elem : coll)
    {
        cout << setw(15) << elem.first << " "
            << elem.second << endl;
    }
    cout << endl;
}
#endif


//无序关联容器的布局操作
#if 0
#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_multiset<int>unset;

    //最大负载因子（因子↑，哈希表空间利用率↑，性能可能↓）
    unset.max_load_factor(0.7);

    //准备100/最大负载因子个元素的大小的bucket(桶)，
    // 以避免在没超过100个元素就rehash()
    unset.rehash(100 / 0.7);
    //准备100个元素大小的bucket
    unset.reserve(100);

    return 0;
}
#endif


//无序关联容器，提供自己的Hash函数和等价准则
#if 0
#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

#include <functional>

// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
template <typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
template <typename... Types>
inline std::size_t hash_val(const Types&... args)
{
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

class Customer
{
private:
    string fname;
    string lname;
    long   no;
public:
    Customer(const string& fn, const string& ln, long n)
        : fname(fn), lname(ln), no(n)
    {}

    friend ostream& operator << (ostream& strm, const Customer& c)
    {
        return strm << "[" << c.fname << "," << c.lname << ","
            << c.no << "]";
    }

    friend class CustomerHash;
    friend class CustomerEqual;
};

class CustomerHash
{
public:
    std::size_t operator() (const Customer& c) const
    {
        return hash_val(c.fname, c.lname, c.no);
    }
};

class CustomerEqual
{
public:
    bool operator() (const Customer& c1, const Customer& c2) const
    {
        return c1.no == c2.no;
    }
};

int main()
{
    // unordered set with own hash function and equivalence criterion
    unordered_set<Customer, CustomerHash, CustomerEqual> custset;

    custset.insert(Customer("nico", "josuttis", 42));

    PRINT_ELEMENTS(custset);
}
#endif


//使用Lambda作为Hash函数和等价准则
#if 0
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
template <typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val(std::size_t& seed, const T& val)
{
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
template <typename... Types>
inline std::size_t hash_val(const Types&... args)
{
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

class Customer
{
private:
    string fname;
    string lname;
    long   no;
public:
    Customer(const string& fn, const string& ln, long n)
        : fname(fn), lname(ln), no(n)
    {}

    string firstname() const
    {
        return fname;
    };

    string lastname() const
    {
        return lname;
    };

    long number() const
    {
        return no;
    };

    friend ostream& operator << (ostream& strm, const Customer& c)
    {
        return strm << "[" << c.fname << "," << c.lname << ","
            << c.no << "]";
    }
};

int main()
{
    // lambda for user-defined hash function
    auto hash = [](const Customer& c) {
        return hash_val(c.firstname(), c.lastname(), c.number());
        };

    // lambda for user-defined equality criterion
    auto eq = [](const Customer& c1, const Customer& c2) {
        return c1.number() == c2.number();
        };

    // create unordered set with user-defined behavior
    unordered_set<Customer, decltype(hash), decltype(eq)>
        custset(10, hash, eq);
    //***理解***
    //必须使用decltype产生 lambda类型，使得以传递它作为 unordered 容器声明式的
    //template 实参。
    //而 lambda并不存在 default 构造函数和 assignment 操作符。
    //因此，你也必须将lambda传给构造函数。
    //而由于它们被设计为第二和第三实参，因此这种情况下你必须指明最初的 bucket 大小，
    //本例为10。

    //补充：//对于关联式容器，使用lambda时有特定的写法。(所以这种情况用lambda不推荐)
    
    custset.insert(Customer("nico", "josuttis", 42));
    PRINT_ELEMENTS(custset);

}
#endif


//使用Bucket接口
//可以访问内部的桶（buckets）。
//每个桶是一个存储元素的容器，可以将具有【相同哈希值的元素】存储在同一个桶中。
//***注***
// 相同哈希值的元素【也可能是不同的键】，它们只是发生了哈希冲突，
// 而哈希表的内部机制确保它们在同一个桶中得到存储。在查找元素时，
// 哈希表会根据键的相等性来确定具体是哪个元素。

// 在 std::unordered_multimap 中，
// 相同哈希值的元素被存储在同一个桶中，而同一个桶中的元素可能具有不同的键。
// 因此，同一个桶中存储的元素的键不一定相同，但它们具有相同的哈希值。
#if 0
#include <iostream>
#include <iomanip>
#include <iterator>
#include <typeinfo>

#include <unordered_set>
#include <unordered_map>
#include <string>

// generic output for pairs (map elements)
template <typename T1, typename T2>
std::ostream& operator << (std::ostream& strm, const std::pair<T1, T2>& p)
{
    return strm << "[" << p.first << "," << p.second << "]";
}

template <typename T>
void printHashTableState(const T& cont)
{
    // basic layout data:
    std::cout << "size:            " << cont.size() << "\n";
    std::cout << "buckets:         " << cont.bucket_count() << "\n";
    std::cout << "load factor:     " << cont.load_factor() << "\n";
    std::cout << "max load factor: " << cont.max_load_factor() << "\n";

    // iterator category:
    if (typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
        == typeid(std::bidirectional_iterator_tag))
    {
        std::cout << "chaining style:  doubly-linked" << "\n";
    }
    else
    {
        std::cout << "chaining style:  singly-linked" << "\n";
    }

    // elements per bucket:
    std::cout << "data: " << "\n";
    for (auto idx = 0u; idx != cont.bucket_count(); ++idx)
    {
        std::cout << " b[" << std::setw(2) << idx << "]: ";

        for (auto pos = cont.begin(idx); pos != cont.end(idx); ++pos)
        {
            std::cout << *pos << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


int main()
{
    // create and initialize an unordered set
    std::unordered_set<int> intset = { 1,2,3,5,7,11,13,17,19 };
    printHashTableState(intset);

    // insert some additional values (might cause rehashing)
    intset.insert({ -7,17,33,4 });
    printHashTableState(intset);

    using std::string;
    // create and initialize an unordered multimap as dictionary
    std::unordered_multimap<string, string> dict = {
                  {"day","Tag"},
                  {"strange","fremd"},
                  {"car","Auto"},
                  {"smart","elegant"},
                  {"trait","Merkmal"},
                  {"strange","seltsam"}
    };
    printHashTableState(dict);

    // insert some additional values (might cause rehashing)
    dict.insert({ {"smart","raffiniert"},
                 {"smart","klug"},
                 {"clever","raffiniert"}
        });
    printHashTableState(dict);

    // modify maximum load factor (might cause rehashing)
    dict.max_load_factor(0.7);
    printHashTableState(dict);
}
#endif


//使容器STL化的三大方法：侵入式，非侵入式，包裹法
//侵入式
//自定义数据结构内直接嵌入STL所需的函数或接口。
//这种方法改变了原始数据结构，使其适应STL的规范。
#if 0
#include <iostream>
#include <vector>

// 自定义侵入式数据结构
class MyData 
{
public:
    int value;

    // 添加适应STL规范的成员函数
    void push_back(int val)
    {
        value = val;
    }
};

int main()
{
    std::vector<MyData> myVector;

    MyData data1, data2, data3;
    data1.push_back(10);
    data2.push_back(20);
    data3.push_back(30);

    myVector.push_back(data1);
    myVector.push_back(data2);
    myVector.push_back(data3);

    for (const auto& item : myVector) {
        std::cout << item.value << " ";
    }
    std::cout << std::endl;

    return 0;
}
#endif
//非侵入式法
// 不修改原始数据结构，而是使用STL的适配器或特化函数来处理自定义数据结构。
#if 0
#include <iterator>
#include <vector>
#include <iostream>

int main()
{
    int vals[] = { 33, 67, -4, 13, 5, 2 };

    // use begin() and end() for ordinary C arrays
    std::vector<int> v(std::begin(vals), std::end(vals));

    //等价于以下写法 （适用于C++11之前）
    //std::vector<int> v(vals, vals+sizeof(vals)/sizeof(vals[0]));

    // use global begin() and end() for containers:
    std::copy(std::begin(v), std::end(v),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
#endif
//包裹法
//通过创建一个包裹类，将自定义数据结构包裹在内部，
// 然后在包裹类中实现STL所需的函数或接口
#if 0
#include <iostream>
#include <vector>

// 自定义数据结构
struct MyData
{
    int value;
};

// 包裹类
class MyDataWrapper 
{
public:
    MyDataWrapper(int val=0) : data{ val } 
    {}

    // 添加适应STL规范的成员函数
    void push_back(int val) 
    {
        data.value = val;
    }

    MyData getData() const
    {
        return data;
    }

private:
    MyData data;
};

int main() 
{
    std::vector<MyDataWrapper> myVector;

    MyDataWrapper data1, data2(0), data3(1);

    data1.push_back(20);
    data2.push_back(20);
    data3.push_back(30);

    myVector.push_back(data1);
    myVector.push_back(data2);
    myVector.push_back(data3);

    for (const auto& item : myVector)
    {
        std::cout << item.getData().value << " ";
    }
    std::cout << std::endl;

    return 0;
}
#endif


//通常STL容器提供的是value语义，而不是reference语义
//STL容器要实现Reference语义
//方法一：采用【智能指针】
#if 0
#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <algorithm>

class Item
{
private:
    std::string name;
    float  price;

public:
    Item(const std::string& n, float p = 0) : name(n), price(p)
    {}

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string& n)
    {
        name = n;
    }

    float getPrice() const
    {
        return price;
    }

    float setPrice(float p)
    {
        price = p;
        return p;
    }
};

template <typename Coll>
void printItems(const std::string& msg, const Coll& coll)
{
    std::cout << msg << std::endl;

    for (const auto& elem : coll)
    {
        std::cout << ' ' << elem->getName() << ": "
            << elem->getPrice() << std::endl;
    }
}

int main()
{
    using namespace std;

    // two different collections sharing Items
    typedef shared_ptr<Item> ItemPtr;

    set<ItemPtr> allItems;
    deque<ItemPtr> bestsellers;

    // insert objects into the collections
    // - bestsellers are in both collections
    bestsellers = {
        ItemPtr(new Item("Kong Yize",20.10)),
         ItemPtr(new Item("A Midsummer Night's Dream",14.99)),
         ItemPtr(new Item("The Maltese Falcon",9.88))
    };

    allItems = {
        ItemPtr(new Item("Water",0.44)),
        ItemPtr(new Item("Pizza",2.22))
    };
    allItems.insert(bestsellers.begin(), bestsellers.end());

    // print contents of both collections
    printItems("bestsellers:", bestsellers);
    printItems("all:", allItems);
    cout << endl;

    // double price of bestsellers
    for_each(bestsellers.begin(), bestsellers.end(),
        [](shared_ptr<Item>& elem) {
            elem->setPrice(elem->getPrice() * 2);
        });

    // print contents of both collections
    printItems("bestsellers:", bestsellers);
    printItems("all:", allItems);
    cout << endl;

    // replace second bestseller by first item with name "Pizza"
    bestsellers[1] = *(find_if(allItems.begin(), allItems.end(),
        [](shared_ptr<Item> elem)
        {
            return elem->getName() == "Pizza";
        }));

    //***注***
    //使用shared_ptr<>会让事情变复杂。例如，面对set 使用find(),会找出拥有相等
    //value 的元素，现在比较的却是内部(由new返回)的 pointer 
    // allItems.find(ItemPtr(new Item("Pizza",2.22)))   //can'tbe successful
    //以下写法也不适用
    //bestsellers[1] = find(allItems.begin(), allItems.end(),string("Pizza"));

    // set price of first bestseller
    bestsellers[0]->setPrice(44.77);

    // print contents of both collections
    printItems("bestsellers:", bestsellers);
    printItems("all:", allItems);
}
#endif


//Reference Wrapper （引用外覆器）
//声明于<functional>中的 class std::reference_wrapper<>主要用来
//“喂” reference 给function template, 后者原本以by value方式接受参数。
// 对于一个给定类型T, 这个 class提供ref()用以隐式转换为T&, 
// 一个 cref()用以隐式转换为 const T&, 这往往允许 
// function template 得以操作 reference 而不需要另写特化版本。
#if 0
#include <iostream>

using namespace std;

template<typename T>
void f1(T val);

int main()
{
    int num = 1;

    f1<int>(num);
    cout << num << endl;

    f1(ref(num));//ref()
    cout << num << endl;

    return 0;
}

template<typename T>
void f1(T val)
{
    ++val;
}
#endif


//实现Reference语义
//方法二：使用 class reference_wrapper<> 
//优点：不需要智能指针
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Item
{
private:
    std::string name;
    float  price;

public:
    Item(const std::string& n, float p = 0) : name(n), price(p)
    {}

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string& n)
    {
        name = n;
    }

    float getPrice() const
    {
        return price;
    }

    float setPrice(float p)
    {
        price = p;
        return p;
    }
};

template <typename Coll>
void printItems(const std::string& msg, const Coll& coll)
{
    std::cout << msg << std::endl;

    for (const auto& elem : coll)
    {
        //需要使用get()方法，访问存储的引用
        std::cout << ' ' << elem.get().getName() << ": "
            << elem.get().getPrice() << std::endl;
    }
}

int main()
{
    using namespace std;

    //reference_wrapper<Item>: 这是一个模板类，它包装了对 Item 类型对象的引用。
    // reference_wrapper 允许将引用作为对象进行传递，
    // 而不是传递引用时会自动发生的解引用。
    // 这对于在容器中存储引用是很有用的，因为容器通常要求元素是可复制的，
    // 而引用则通常不是可复制的。
    //这种设计常常用于需要在容器中存储引用而不是复制对象的情况，
    // 例如，当你想要在容器中保存对象的引用，并且希望通过引用修改原始对象时。
    vector<reference_wrapper<Item>>books;

    Item book1("bookname", 12.99);
    //向容器安插元素，但是安插的是个引用
    books.push_back(book1);

    printItems("books:", books);
    cout << endl;

    //***注***
    //直接修改book1对象的内容，
    //若vector容器中存的不是该对象的引用，默认存的是拷贝的value即拷贝的对象
    //那就不会影响vector容器中的该对象中存的内容。
    //而该例存的是该对象的引用，那就会影响vector容器中的该对象中存的内容。
    book1.setPrice(9.99);

    cout << books[0].get().getPrice() << endl;

    printItems("books:", books);
    cout << endl;

    //***注***
    //创建以下vector的尝试，无法通过编译
    //vector<Item&>books_test;
    //books_test.push_back(book1);
    //book1.setPrice(10.5);
    //cout << books_test[0].getPrice() << endl;
}
#endif


//小结：
//各种容器的使用时机

//默认情况下应该使用 vector。vector的内部结构最简单，并允许随机访问，
//所以数据的访问十分方便灵活，数据的处理也够快。

//如果经常要在序列头部和尾部安插和移除元素，应该采用deque。如果你希望元素
//被移除时，容器能够自动缩减内部内存用量，那么也该采用deque。

//如果需要经常在容器中段执行元素的安插、移除和移动，可考虑使用list。

//如果你经常需要根据某个准则查找元素，应当使用“依据该准则进行hash”的
//unordered set 或 multiset

//如果想处理 key/value pair,请采用unordered(multi)map。如果元素次序很重要，可采用
//(multi)map

//补充：
//map 使用红黑树（Red-Black Tree）作为底层数据结构，
// 它保持元素的有序状态，因此在查找操作时具有 O(log n) 的时间复杂度。
//unordered_map 使用哈希表作为底层数据结构，它通过哈希函数将键映射到桶（buckets），
//并在桶中进行搜索。在理想情况下（哈希函数均匀分布），
// 查询操作的平均时间复杂度为 O(1)。但在最坏情况下，
// 可能需要 O(n) 的时间复杂度，例如当哈希冲突严重时。
//因此，在大多数情况下，unordered_map 提供了比 map 更快的查询速度，
//但是在保持元素顺序或者需要有序遍历时，map 会更适合。


//随机访问迭代器的特殊能力
#if 0
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> coll;

    // insert elements from -3 to 9
    for (int i = -3; i <= 9; ++i)
    {
        coll.push_back(i);
    }

    // print number of elements by processing the distance between beginning and end
    // - NOTE: uses operator - for iterators
    cout << "number/distance: " << coll.end() - coll.begin() << endl;

    // print all elements
    // - NOTE: uses operator < instead of operator !=
    vector<int>::iterator pos;
    for (pos = coll.begin(); pos < coll.end(); ++pos)
    {
        cout << *pos << ' ';
    }
    cout << endl;

    // print all elements
    // - NOTE: uses operator [] instead of operator *
    for (int i = 0; i < coll.size(); ++i)
    {
        cout << coll.begin()[i] << ' ';
    }
    cout << endl;

    // print every second element
    // - NOTE: uses operator +=
    for (pos = coll.begin(); pos < coll.end() - 1; pos += 2)
    {
        cout << *pos << ' ';
    }
    cout << endl;
    //***注***
    //以2个单位为跨度来向前增加迭代器的位置时要注意
    //若写为
    //for(pos= coll.begin();pos< coll.end(); pos += 2)
    //而容器中含奇数个元素，会有不明确行为
    //原因：
    //将迭代器移至“起点更前面”会导致不明确行为。同样道理，
    //如果表达式pos += 2将迭代器移至end()之后，也会导致不明确行为。
}
#endif


//迭代器的相关辅助函数
//由于vector、array、string的迭代器
//通常被实现为寻常pointer, 而 C++并不允许你修改任何基础类型
//(包括 pointer)的临时值，但对于 struct 和class 则允许。
//因此，如果迭代器被实现为寻常 pointer, 则编译失败；如果被实现为 class, 则编译成功。
//为了保证移植，可以使用C++11提供的next()
//next()好处之一：
#if 0
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v{ 3, 4, 1 };

    auto it = v.begin();
    auto nx = std::next(it, 2);
    std::cout << *it << ' ' << *nx << '\n';

    std::sort(std::next(v.begin()), v.end());
    for (auto x : v)
        std::cout << x << ' ';

    //***注***
    // 尽管表达式 ++c.begin() 通常能编译，然而不保证会这么做： 
    // c.begin() 是右值表达式，而无老式输入迭代器 (LegacyInputIterator) 
    // 要求指定右值的自增保证进行。
    // 尤其是迭代器以指针实现或其 operator++ 为【左值引用限定】时，
    //  ++c.begin() 不能编译，而 std::next(c.begin()) 可以。
}
#endif


//根据迭代器种类，选择最佳的前进/后退方案：advance()
//***注***
//前进：next()    后退：prev()       函数
//内部将对一个临时对象调用advance()
#if 0
#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<int> coll;

    // insert elements from 1 to 9
    for (int i = 1; i <= 9; ++i) 
    {
        coll.push_back(i);
    }

    list<int>::iterator pos = coll.begin();

    // print actual element
    cout << *pos << endl;

    // step three elements forward
    advance(pos, 3);

    // print actual element
    cout << *pos << endl;

    // step one element backward
    advance(pos, -1);

    // print actual element
    cout << *pos << endl;
}
#endif


//next()好处之二：
//对于没有operator +和operator -  的这些容器
//可以用next()来确定遍历到某个位置时停止
#if 0
#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<int> coll;//仅有双向迭代器

    // insert elements from 1 to 9
    for (int i = 1; i <= 9; ++i)
    {
        coll.push_back(i);
    }

    auto pos = coll.begin();
    while (pos != coll.end() && std::next(pos) != coll.end())
    {
        cout << *pos << ' ';

        ++pos;
    }
    cout << endl;
    //***注意***
    //next(pos)返回的是个临时值，不会改变pos的值

    //forward 和 bidirectional 迭代器不提供 operator +和 -
    //如果不用next()，你就需要创建一个临时对象的协助来判断
    auto pos_1 = coll.begin();
    auto nextPos = pos_1;
    ++nextPos;
    while (pos_1 != coll.end() && nextPos != coll.end())
    {
        cout << *pos_1 << ' ';

        ++pos_1;
        ++nextPos;
    }

}
#endif
//补充：advance()和next()的区别
//advance() 返回void，会真正地修改传递给它的迭代器，将其移动到指定位置。
//next() 返回一个新的迭代器，指向原始迭代器移动指定步数后的位置。
//这个函数不会修改原始的迭代器，而是返回一个指向移动后位置的新迭代器。


//根据迭代器种类，选择最佳的计算距离的方案：distance()


//交换两个迭代器所指的元素的值
#if 0
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    list<int> coll;

    // insert elements from 1 to 9
    for (int i = 1; i <= 9; ++i)
    {
        coll.push_back(i);
    }

    PRINT_ELEMENTS(coll);

    // swap first and second value
    iter_swap(coll.begin(), next(coll.begin()));

    PRINT_ELEMENTS(coll);

    // swap first and last value
    iter_swap(coll.begin(), prev(coll.end()));

    PRINT_ELEMENTS(coll);
}
#endif


//迭代器适配器(iterator adapter)
//将正常的迭代器转化成反向迭代器
#if 0
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // create list with elements from 1 to 9
    vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // find position of element with value 5
    vector<int>::const_iterator pos;
    pos = find(coll.cbegin(), coll.cend(), 5);

    // print value to which iterator pos refers
    cout << "pos:  " << *pos << endl;

    // convert iterator to reverse iterator rpos
    vector<int>::const_reverse_iterator rpos(pos);

    // print value to which reverse iterator rpos refers
    cout << "rpos: " << *rpos << endl << endl;

    //***注***
    //转换前后迭代器逻辑位置发生了变化
    //当我们把pos 转换为rpos,它们的物理位置指向同一点，但它们所代表的意义
    //(或说它们所代表的逻辑位置)不同了

    //***理解***
    //rbegin()指向容器的最末元素的下一个位置，而对其解引用后值为最末元素的值
    //rend()指向容器的第一个元素的位置，而对其解引用后值为第一个元素前的一个位置

    //为什么rend()指向容器的第一个元素的位置？
    //因为遍历容器，一般我们需要采用“最末元素的下一位置”。
    // 然而对 reverse 迭代器而言，这个位置位于第一元素之前。
    // 糟糕的是，这个位置可能并不存在，因为容器并不要求其第一元素之前的位置合法
    //所以对于反向迭代器，物理上rend()指向容器的第一个元素的位置(该位置一定合法)，
    //但是逻辑上解释为第一个元素前的一个位置。
    //由于物理意义和逻辑意义不同，而解引用解的是逻辑意义，
    //因此逻辑上其 value(也就是其所指元素值)也就移到了前一个元素身上。
}
#endif


//反向迭代器的应用
//使用一对迭代器，正向和逆向打印找出的元素
#if 0
#include <iterator>
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

void print(int elem)
{
    cout << elem << ' ';
}

int main()
{
    // create deque with elements from 1 to 9
    deque<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // find position of element with value 2
    deque<int>::const_iterator pos1;
    pos1 = find(coll.cbegin(), coll.cend(),  // range
        2);                          // value

    // find position of element with value 7
    deque<int>::const_iterator pos2;
    pos2 = find(coll.cbegin(), coll.cend(),  // range
        7);                          // value

    // print all elements in range [pos1,pos2)
    for_each(pos1, pos2,     // range
        print);         // operation
    cout << endl;

    // convert iterators to reverse iterators
    deque<int>::const_reverse_iterator rpos1(pos1);
    deque<int>::const_reverse_iterator rpos2(pos2);

    cout << "*rpos1=" << *rpos1 << endl;

    // print all elements in range [pos1,pos2) in reverse order
    for_each(rpos2, rpos1,   // range
        print);         // operation
    cout << endl;
    //***理解***
    //物理位置不变，但是逻辑位置改变，打印出的内容正好符合预期。

    //使用base()将反向迭代器转化为正常迭代器
    deque<int>::const_iterator rrpos1(rpos1.base());

    cout << "*rrpos1=" << *rrpos1 << endl;
}
#endif


//back_insert_iterator、back_inserter()的应用
//只能用在vector、deque、list、string上
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    vector<int> coll;

    // create back inserter for coll
    // - inconvenient way
    back_insert_iterator<vector<int> > iter(coll);

    // insert elements with the usual iterator interface
    *iter = 1;
    iter++;
    *iter = 2;
    iter++;
    *iter = 3;
    PRINT_ELEMENTS(coll);

    // create back inserter and insert elements
    // - convenient way
    back_inserter(coll) = 44;
    back_inserter(coll) = 55;
    PRINT_ELEMENTS(coll);


    // use back inserter to append all elements again
    // - reserve enough memory to avoid reallocation
    //***注***
    //安插型迭代器确实能安插元素到容器中，
    //但是【对于vector等内存可能需要重新分配的容器】
    //back inserter 在安插元素时，可能会造成指向该 vector的其他迭代器失效。
    //因此，如果提前不申请足够空间，这个算法可能会形成“源端迭代器失效”状态。
    coll.reserve(2 * coll.size());

    copy(coll.begin(), coll.end(), back_insert_iterator<vector<int>>(coll));
    PRINT_ELEMENTS(coll);

    coll.reserve(2 * coll.size());

    copy(coll.begin(), coll.end(), back_inserter(coll));
    PRINT_ELEMENTS(coll);

    //还可以使用vector容器自己的insert方法
    //（传入的是个指向自身的某个元素的迭代器时，也要注意操作后迭代器可能会失效）
}
#endif


//front_insert_iterator、front_inserter()的应用
//只能用在deque、list、forward list
#if 0
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    list<int> coll;

    // create front inserter for coll
    // - inconvenient way
    front_insert_iterator<list<int> > iter(coll);

    // insert elements with the usual iterator interface
    *iter = 1;
    iter++;
    *iter = 2;
    iter++;
    *iter = 3;

    PRINT_ELEMENTS(coll);

    // create front inserter and insert elements
    // - convenient way
    front_inserter(coll) = 44;
    front_inserter(coll) = 55;

    PRINT_ELEMENTS(coll);

    // use front inserter to insert all elements again
    copy(coll.begin(), coll.end(),    // source
        front_inserter(coll));       // destination

    PRINT_ELEMENTS(coll);
}
#endif
//***注***
//补充：
/*
上述代码使用了std::list，一个双向链表。不像std::vector，std::list的插入操作不会导致
元素的内存位移，因此不会使现有迭代器失效。
这就是为什么在使用std::front_inserter(coll)插入元素时不需要预先预留空间。
在std::list中，无论是向前插入还是向后插入，都不会使已有的迭代器失效。
这是因为链表结构的特性，插入和删除一个元素只需要改变相邻元素的链接方式，
而不需要移动其他元素。
总的来说：
对于std::list这类链表结构的容器，插入操作不会使迭代器失效，所以无需预先预留空间。
但对于vector、deque、string这类可能需要内存重新分配的容器，
插入操作可能会使迭代器失效，因此最好预先预留足够的空间。

std::list和std::forward_list这类链表容器通常不需要进行内存重新分配，
因为链表结构允许在不影响其他元素的情况下插入或删除元素。
同样，std::set、std::map、std::multiset和std::multimap这些基于树的容器
也通常不会在插入或删除操作中使迭代器失效，除非是正在被操作的那个具体元素的迭代器
*/


//insert_iterator、inserter()应用
//general inserter 【对所有标准容器均适用】(只有 array 和 forward list 除外),
// 因为那些容器都提供有insert()成员函数(见8.7.1节第413页)。
// 然而对 associative 和 unordered 容器而言，安插位置只是个提示，
// 因为在这两种容器中元素的真正位置视其value而定。
#if 0
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    set<int> coll;

    // create insert iterator for coll
    // - inconvenient way
    insert_iterator<set<int> > iter(coll, coll.begin());

    // insert elements with the usual iterator interface
    *iter = 1;
    iter++;
    *iter = 2;
    iter++;
    *iter = 3;

    PRINT_ELEMENTS(coll, "set:  ");

    // create inserter and insert elements
    // - convenient way
    inserter(coll, coll.end()) = 44;
    inserter(coll, coll.end()) = 55;

    PRINT_ELEMENTS(coll, "set:  ");

    // use inserter to insert all elements into a list
    list<int> coll2;
    copy(coll.begin(), coll.end(),           // source
        inserter(coll2, coll2.begin()));     // destination

    PRINT_ELEMENTS(coll2, "list: ");

    // use inserter to reinsert all elements into the list before the second element
#if 0
    copy(coll.begin(), coll.end(),           // source
        inserter(coll2, ++coll2.begin()));   // destination
#endif
    copy(coll.begin(), coll.end(),           // source
        inserter(coll2, next(coll2.begin())));   // destination

    PRINT_ELEMENTS(coll2, "list: ");

    auto pos = coll2.end();
    for (int i = 1; i < 9; ++i)
    {
        //错误写法：
        //coll2.insert(pos,i);
        //正确写法：
        pos = coll2.insert(pos, i);
        ++pos;
    }

    //***注***
    //安插动作完成后，general inserter 获得刚被安插的那个元素的位置，相当于
    //pos = container.insert(pos,value);
    //++pos;
    //这样使为了确保该迭代器的位置始终有效。如果
    //没有这一赋值动作，在 deque、vector 和 string中，
    //该 general inserter本身可能会失效。因为每一次安插动作都会
    //(或至少可能会)使指向容器的所有迭代器失效。

    PRINT_ELEMENTS(coll2, "list: ");
}
#endif


//使用ostream_iterator
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    // create ostream iterator for stream cout
    // - values are separated by a newline character
    ostream_iterator<int> intWriter(cout, "\n");

    // write elements with the usual iterator interface
    *intWriter = 42;
    intWriter++;
    *intWriter = 77;
    intWriter++;
    *intWriter = -5;

    // create collection with elements from 1 to 9
    vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // write all elements without any delimiter
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<int>(cout));
    cout << endl;

    // write all elements with " < " as delimiter
    copy(coll.cbegin(), coll.cend(),
        ostream_iterator<int>(cout, " < "));
    cout << endl;
}
#endif


//使用istream_iterator
#if 0
#include <iostream>
#include <iterator>
using namespace std;

int main()
{
    // create istream iterator that reads integers from cin
    istream_iterator<int> intReader(cin);

    // create end-of-stream iterator
    istream_iterator<int> intReaderEOF;

    // while able to read tokens with istream iterator
    // - write them twice
    while (intReader != intReaderEOF)
    {
        cout << "once:       " << *intReader << endl;
        cout << "once again: " << *intReader << endl;
        ++intReader;
    }

    //***注***
    // 若输入字符a将导致程序结束。由于格式错误，stream不再处于 good 状态，
    // 于是 istream迭代器 intReader 就和 end - of - stream 迭代器 intReaderEOF 相同，
    // 使得循环条件为 false, 进而结束循环。
}
#endif


//利用advance()和istream_iterator来跳过指定个数的输入内容
#if 0
#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    istream_iterator<string> cinPos(cin);
    ostream_iterator<string> coutPos(cout, " ");

    // while input is not at the end of the file
    // - write every third string
    while (cinPos != istream_iterator<string>())
    {
        // ignore the following two strings
        advance(cinPos, 2);
        //***注***
        //若指向EOF的后一个位置，程序会崩溃

        // read and write the third string
        if (cinPos != istream_iterator<string>())
        {
            *coutPos++ = *cinPos++;
        }
    }
    cout << endl;

    //***注***  若输入：
/*
a
b
c
d
e
f
g
h
*/
//程序会在输入到d时，立即输出c
//分析：
//while 循环开始，从输入中【读取了】 a 但被忽略，同理b也被忽略
//读取到c，通过输出迭代器输出到屏幕，但由于输入迭代器仍将检测输入的内容
//因此不会马上输出c。等到输入迭代器再读取一个string格式的内容后，才输出c
//或者直接键入^Z后，输出c

//若输入：
/*
a b c d e f g h
*/
//则输出c f
}
#endif


//以函数对象为排序准则
#if 0
#include <iostream>
#include <string>
#include <set>
using namespace std;

class Person
{
private:
    string fn;    // first name
    string ln;    // last name
public:
    Person()
    {}
    Person(const string& f, const string& n)
        : fn(f), ln(n)
    {}
    string firstname() const;
    string lastname() const;
    // ...
};

inline string Person::firstname() const
{
    return fn;
}

inline string Person::lastname() const
{
    return ln;
}

ostream& operator<< (ostream& s, const Person& p)
{
    s << "[" << p.firstname() << " " << p.lastname() << "]";
    return s;
}


/* class for function predicate
 * - operator () returns whether a person is less than another person
 */
class PersonSortCriterion
{
public:
    bool operator() (const Person& p1, const Person& p2) const {
        /* a person is less than another person
         * - if the last name is less
         * - if the last name is equal and the first name is less
         */
        return p1.lastname() < p2.lastname() ||
            (p1.lastname() == p2.lastname() &&
                p1.firstname() < p2.firstname());
    }
};

int main()
{
    Person p1("nicolai", "josuttis");
    Person p2("ulli", "josuttis");
    Person p3("anica", "josuttis");
    Person p4("lucas", "josuttis");
    Person p5("lucas", "otto");
    Person p6("lucas", "arm");
    Person p7("anica", "holle");

    // declare set type with special sorting criterion
    typedef set<Person, PersonSortCriterion> PersonSet;

    // create such a collection
    PersonSet coll;
    //***理解***
    //coll构造函数会自动产生 class PersonSortCriterion的一个实例(instance),
    // 所有元素都将以此为排序准则进行排序

    //写法二：
    /*
    PersonSortCriterion PSC;
    set<Person, PersonSortCriterion> coll(PSC);
    */
    //详细见//对于关联容器，实现运行期指定排序准则

    coll.insert(p1);
    coll.insert(p2);
    coll.insert(p3);
    coll.insert(p4);
    coll.insert(p5);
    coll.insert(p6);
    coll.insert(p7);

    // do something with the elements
    // - in this case: output them
    cout << "set:" << endl;
    PersonSet::iterator pos;
    for (pos = coll.begin(); pos != coll.end(); ++pos)
    {
        cout << *pos << endl;
    }
}
#endif


//函数对象拥有内部状态(Internal State)
#if 0
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

class IntSequence
{
private:
    int value;
public:
    IntSequence(int initialValue)    // constructor
        : value(initialValue)
    {}

    int operator() ()
    {               // "function call"
        return value++;
    }
};

int main()
{
    list<int> coll;

    // insert values from 1 to 9
    generate_n(back_inserter(coll),  // start
        9,                    // number of elements
        IntSequence(1));      // generates values, starting with 1

    PRINT_ELEMENTS(coll);

    // replace second to last element but one with values starting at 42
    generate(next(coll.begin()),     // start
        prev(coll.end()),       // end
        IntSequence(42));       // generates values, starting with 42

    PRINT_ELEMENTS(coll);
}
#endif


//for_each()独门绝技：可以传回其函数对象
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// function object to process the mean value
class MeanValue
{
private:
    long num;    // number of elements
    long sum;    // sum of all element values
public:
    // constructor
    MeanValue() : num(0), sum(0)
    {}

    // "function call"
    // - process one more element of the sequence
    void operator() (int elem)
    {
        ++num;          // increment count
        sum += elem;    // add value

        std::cout << "num=" << num << " sum=" << sum << std::endl;
    }

    // return mean value
    double value()
    {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

int main()
{
    vector<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // process and print mean value
    MeanValue mv = for_each(coll.begin(), coll.end(),  // range
        MeanValue());              // operation

    cout << "mean value: " << mv.value() << endl;

    //***理解***
    //for_each()的实现：
    /*
    template<class InputIt, class UnaryFunction>
    UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
    {
        for (; first != last; ++first) {
            f(*first);
        }
        return f; // C++11 起隐式移动
    }               // (此例中调用MeanValue的自动提供的复制构造函数)
    */
}
#endif


//remove_if()碰上函数对象作为谓词 (Predicate)会出现的问题
#if 0
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

class Nth {    // function object that returns true for the nth call
private:
    int nth;       // call for which to return true
    int count;     // call counter
public:
    Nth(int n) : nth(n), count(0)
    {}
    bool operator() (int)
    {
        return ++count == nth;
    }
};

int main()
{
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    PRINT_ELEMENTS(coll, "coll:        ");

    // remove third element
    list<int>::iterator pos;
    pos = remove_if(coll.begin(), coll.end(),  // range
        Nth(3));                  // remove criterion
    coll.erase(pos, coll.end());

    PRINT_ELEMENTS(coll, "3rd removed: ");

    //结果为：1 2 4 5 7 8 9 10
    //理解：
    //remove_if()的实现
    /*
    template <typename ForwIter,typename Predicate>
    ForwIter std::remove_if(ForwIter beg,ForwIter end,
    Predicate op)
    {
        beg = find_if(beg,end,op);

        if(beg == end){
        return beg;
        }
        else {
        ForwIter next = beg;
        return remove_copy_if(++next,end,beg,op);//提高代码的复用性和遵循单一责任原则
        }
    }
    */
    // 使用find_if()查找应被移除的第一个元素。然而，
    // 接下来remove_copy_if()使用传入的 predicate op的拷贝去处理剩余元素，
    // 这时原始状态下的Nth再次被使用，因而
    // 会移除剩余元素中的第3个元素，也就是整体的第6个元素。

    //解决方法：使用remove_copy_if()
    pos = remove_copy_if(coll.begin(), coll.end(),  // range
        coll.begin(), Nth(3));                  // remove criterion
    coll.erase(pos, coll.end());

    PRINT_ELEMENTS(coll, "3rd removed: ");

    //使用lambda更直观：
    int cnt = 0;
    pos = remove_if(coll.begin(), coll.end(), [&cnt](int)
        {
            return ++cnt == 3;
        });
    coll.erase(pos, coll.end());

    PRINT_ELEMENTS(coll, "3rd removed: ");
}
/*
remove_copy_if的实现：
template<class InputIt, class OutputIt, class UnaryPredicate>
OutputIt remove_copy_if
(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p)
{
    for (; first != last; ++first) {
        if (!p(*first)) {
            *d_first++ = *first;
        }
    }
    return d_first;
}
*/
#endif
//区别：
//remove_if 用于从容器中移除元素，而 remove_copy_if 则是将不满足条件的元素
//复制到另一个容器中。需要注意的是，remove_if 不会真正删除元素，
//而是将它们移到容器末尾，需要结合 erase 操作来真正删除。


//bind()嵌套合成更复杂的函数对象
#if 0
#include <functional>
#include <iostream>

int main()
{
    auto plus10 = std::bind(std::plus<int>(),
        std::placeholders::_1,
        10);
    std::cout << "+10:    " << plus10(7) << std::endl;

    auto plus10times2 = std::bind(std::multiplies<int>(),
        std::bind(std::plus<int>(),
            std::placeholders::_1,
            10),
        2);
    std::cout << "+10 *2: " << plus10times2(7) << std::endl;

    auto pow3 = std::bind(std::multiplies<int>(),
        std::bind(std::multiplies<int>(),
            std::placeholders::_1,
            std::placeholders::_1),
        std::placeholders::_1);
    std::cout << "x*x*x:  " << pow3(7) << std::endl;

    auto inversDivide = std::bind(std::divides<double>(),
        std::placeholders::_2,
        std::placeholders::_1);
    std::cout << "invdiv: " << inversDivide(49, 7) << std::endl;
}
#endif
//改用Lambda来实现更复杂的计算
#if 0
#include <iostream>

int main()
{
    auto plus10 = [](int i) {
        return i + 10;
        };
    std::cout << "+10:    " << plus10(7) << std::endl;

    auto plus10times2 = [](int i) {
        return (i + 10) << 1;
        };
    std::cout << "+10 *2: " << plus10times2(7) << std::endl;

    auto pow3 = [](int i) {
        return i * i * i;
        };
    std::cout << "x*x*x:  " << pow3(7) << std::endl;

    auto inversDivide = [](double d1, double d2) {
        return d2 / d1;
        };
    std::cout << "invdiv: " << inversDivide(49, 7) << std::endl;
}
#endif


//bind()调用全局函数
//使用search()函数检验一个字符串是否是另一个字符串的子串，
//即查找第一个子区间
//***注***
//search() 强调的是查找第一个匹配，而 find_end() 强调的是查找最后一个匹配
#if 0
#include <iostream>
#include <algorithm>
#include <functional>
#include <locale>
#include <string>
using namespace std;
using namespace std::placeholders;

char myToupper(char c)
{
    /*
    std::locale loc;
    return std::use_facet<std::ctype<char> >(loc).toupper(c);
    */
    return toupper(c);
}

int main()
{
    string s("Internationalization");
    string sub("Nation");

    // search substring case insensitive
    string::iterator pos;
    pos = search(s.begin(), s.end(),           // string to search in
        sub.begin(), sub.end(),       // substring to search
        bind(equal_to<char>(),       // compar. criterion
            bind(myToupper, _1),
            bind(myToupper, _2)));
    if (pos != s.end()) {
        cout << "\"" << sub << "\" is part of \"" << s << "\""
            << endl;
    }
}
#endif
//用lambda来实现调用全局函数
#if 0
#include <iostream>
#include <algorithm>
#include <locale>
#include <string>
using namespace std;

char myToupper(char c)
{

    return toupper(c);
}

int main()
{
    string s("Internationalization");
    string sub("Nation");

    // search substring case insensitive
    string::iterator pos;
    pos = search(s.begin(), s.end(),           // string to search in
        sub.begin(), sub.end(),       // substring to search
        [](char c1, char c2) {      // compar. criterion
            return myToupper(c1) == myToupper(c2);
        });
    if (pos != s.end()) {
        cout << "\"" << sub << "\" is part of \"" << s << "\""
            << endl;
    }

    //find_first_of   ”似乎“也可以？
    pos = find_first_of(s.begin(), s.end(),           // string to search in
        sub.begin(), sub.end(),       // substring to search
        [](char c1, char c2) {      // compar. criterion
            return myToupper(c1) == myToupper(c2);
        });

    if (pos != s.end())
    {
        cout << "\"" << sub << "\" is part of \"" << s << "\""
            << endl;
    }
}
#endif


//search()和find_first_of()的区别
#if 0
#include <iostream>
#include <string>

int main()
{
    std::string str = "Hello world";
    std::string sub_str = "world";

    // 使用 find_first_of() 
    //寻找等于 str 中字符之一的首个字符。
    size_t pos = str.find_first_of(sub_str);
    if (pos != std::string::npos) {
        std::cout << "Substring found at position: " << pos << std::endl;
    }
    else {
        std::cout << "Substring not found" << std::endl;
    }

    //***注***
    //没有find_last_of()函数，仅string有该方法
    //想要实现寻找最后一个等于 str 中字符之一的首个字符的元素位置
    //对于非string对象，可以用STL函数
    /*
    find_first_of(s.rbegin(), s.rend(),           // string to search in
        sub.begin(), sub.end(),       // substring to search
    */
    //（反向迭代器）

    // 使用 find()方法相当于使用search() 
    //  在字符串中查找完全匹配指定子串的第一个位置
    pos = str.find(sub_str);
    if (pos != std::string::npos) 
    {
        std::cout << "Substring found at position: " << pos << std::endl;
    }
    else
    {
        std::cout << "Substring not found" << std::endl;
    }

    return 0;
}
#endif


//bind()调用成员函数
//不直观，个人更喜欢用lambda
#if 0
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
using namespace std::placeholders;

class Person {
private:
    string name;
public:
    Person(const string& n) : name(n) {
    }
    void print() const {
        cout << name << endl;
    }
    void print2(const string& prefix) const {
        cout << prefix << name << endl;
    }
    //...
};

int main()
{
    vector<Person> coll
        = { Person("Tick"), Person("Trick"), Person("Track") };

    // call member function print() for each person
    for_each(coll.begin(), coll.end(),
        bind(&Person::print, _1));
    cout << endl;

    // call member function print2() with additional argument for each person
    for_each(coll.begin(), coll.end(),
        bind(&Person::print2, _1, "Person: "));
    cout << endl;

    // call print2() for temporary Person
    bind(&Person::print2, _1, "This is: ")(Person("nico"));
}
#endif
//用lambda实现调用成员函数
#if 0
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
public:
    Person(const string& n) : name(n) {
    }
    void print() const {
        cout << name << endl;
    }
    void print2(const string& prefix) const {
        cout << prefix << name << endl;
    }
    //...
};

int main()
{
    vector<Person> coll
        = { Person("Tick"), Person("Trick"), Person("Track") };

    // call member function print() for each person
    for_each(coll.begin(), coll.end(),
        [](const Person& p) {
            p.print();
        });
    cout << endl;

    // call member function print2() with additional argument for each person
    for_each(coll.begin(), coll.end(),
        [](const Person& p) {
            p.print2("Person: ");
        });
}
#endif


//function<> 模板类
#if 0
#include <iostream>
#include <algorithm>
#include <list>
#include <functional>
using namespace std;

bool check(int elem);

int main()
{
    list<int> link_list{ 1,2,3,4,5,6 };

    //auto pos=find_if(link_list.begin(),link_list.end(),check);
    auto pos = find_if(link_list.begin(), link_list.end(),
        function<bool(int)>(check));
    //可以不使用function<>
    //当需要存储不同类型的可调用对象、
    // 将它们作为参数传递给函数或通过传递可调用对象为
    // 用户提供自定义行为的灵活性时， std::function 的使用变得更加相关

    cout << *pos << endl;

    return 0;
}
bool check(int elem)
{
    if (elem == 3)
        return true;
    else
        return false;
}
#endif
//function<> 模板类 补充示例
//function<> 模板类它提供了一个通用的多态函数包装器。
// 它可以存储、复制和调用任何可调用的目标函数、lambda表达式、
// bind表达式或其他函数对象，以及指向成员函数的指针和指向数据成员的指针。
#if 0
#include <iostream>
#include <functional>
#include <vector>

// A simple function
void print_hello() 
{
    std::cout << "Hello, World!" << std::endl;
}

// A function with a parameter
void print_number(int i) 
{
    std::cout << "Number: " << i << std::endl;
}

// A function that returns a value
int add(int x, int y) 
{
    return x + y;
}

// A functor (function object)
struct Multiply
{
    int operator()(int x, int y) 
    {
        return x * y;
    }
};

int main() 
{
    // Assign a simple function to std::function
    std::function<void()> f1 = print_hello;
    f1(); // Outputs: Hello, World!

    // Assign a function with a parameter to std::function
    std::function<void(int)> f2 = print_number;
    f2(42); // Outputs: Number: 42

    // Assign a function that returns a value
    std::function<int(int, int)> f3 = add;
    std::cout << "Add result: " << f3(3, 4) << std::endl; // Outputs: Add result: 7

    // Assign a lambda expression to std::function
    std::function<int(int, int)> f4 = [](int x, int y) { return x - y; };
    std::cout << "Lambda result: " << f4(10, 5) << std::endl; // Outputs: Lambda result: 5

    // Assign a functor to std::function
    std::function<int(int, int)> f5 = Multiply();
    std::cout << "Multiply result: " << f5(6, 7) << std::endl; // Outputs: Multiply result: 42

    return 0;
}
#endif


//search_n()
//在范围 [first, last) 中搜索 count 个等同元素的序列，
//每个都等于给定的值 value 或者 满足二元谓词
#if 0
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "")
{
    std::cout << optstr;

    for (const auto& elem : coll)
    {
        std::cout << elem << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    deque<int> coll;

    coll = { 1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6 };
    PRINT_ELEMENTS(coll);

    // find three consecutive elements with value 7
    deque<int>::iterator pos;
    pos = search_n(coll.begin(), coll.end(),    // range
        3,                           // count
        7);                          // value

    // print result
    if (pos != coll.end())
    {
        cout << "three consecutive elements with value 7 "
            << "start with Num." << distance(coll.begin(), pos) + 1
            << ". element" << endl;
    }
    else
    {
        cout << "no four consecutive elements with value 7 found"
            << endl;
    }

    // find four consecutive odd elements
    pos = search_n(coll.begin(), coll.end(),    // range
        4,                           // count
        0,                           // value
        [](int elem, int value) // criterion   ***注***
        {
            return elem % 2 == 1;
        });
    //***注***
    // 必须写成二元谓词
    //不能写成
    /*
    pos = search_n(coll.begin(), coll.end(),    // range
        4,                           // count
        0,                           // value
        [](int elem) // criterion
        {
            return elem % 2 == 1;
        });
        */

        //因为有如下写法：
        //找出四个值大于3的连续元素
#if 0
    pos = search_n(coll.begin(), coll.end(), // range
        4, // count
        3, // value
        greater<int>()); // criterion   二元谓词
#endif

    // print result
    if (pos != coll.end())
    {
        cout << "first four consecutive odd elements are: ";
        for (int i = 0; i < 4; ++i, ++pos)
        {
            cout << *pos << ' ';
        }
    }
    else
    {
        cout << "no four consecutive elements with value > 3 found";
    }
    cout << endl;
}
#endif


//search()以更复杂的准则查找某个子序列
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

// checks whether an element is even or odd
bool checkEven(int elem, bool even)
{
    if (even) {
        return elem % 2 == 0;
    }
    else {
        return elem % 2 == 1;
    }
}

int main()
{
    vector<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll, "coll: ");

    // arguments for checkEven()
    // - check for: "even odd even"
    bool checkEvenArgs[3] = { true, false, true };

    // search first subrange in coll
    vector<int>::iterator pos;
    pos = search(coll.begin(), coll.end(),       // range
        checkEvenArgs, checkEvenArgs + 3, // subrange values
        checkEven);                     // subrange criterion

    // loop while subrange found
    while (pos != coll.end())
    {
        // print position of first element
        cout << "subrange found starting with element "
            << distance(coll.begin(), pos) + 1
            << endl;

        // search next subrange in coll
        pos = search(++pos, coll.end(),              // range
            checkEvenArgs, checkEvenArgs + 3, // subr. values
            checkEven);                     // subr. criterion
    }
}
#endif


//查找最后一个子区间（search()查的是第一个子区间）：find_end() 
#if 0
#include <iostream>
#include <deque>
#include <list>
#include <algorithm>

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    deque<int> coll;
    list<int> subcoll;

    INSERT_ELEMENTS(coll, 1, 7);
    INSERT_ELEMENTS(coll, 1, 7);

    INSERT_ELEMENTS(subcoll, 3, 6);

    PRINT_ELEMENTS(coll, "coll:    ");
    PRINT_ELEMENTS(subcoll, "subcoll: ");

    // search last occurrence of subcoll in coll
    deque<int>::iterator pos;
    pos = find_end(coll.begin(), coll.end(),         // range
        subcoll.begin(), subcoll.end());  // subrange

    // loop while subcoll found as subrange of coll
    deque<int>::iterator end(coll.end());
    while (pos != end) {
        // print position of first element
        cout << "subcoll found starting with element "
            << distance(coll.begin(), pos) + 1
            << endl;

        //找倒数第二个符合的子字符串位置
        // search next occurrence of subcoll
        end = pos;
        pos = find_end(coll.begin(), end,               // range
            subcoll.begin(), subcoll.end()); // subrange
    }
}
#endif


//顺序无所谓情况下，两区间的元素是否相等：is_permutation() 
#if 0
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

bool bothEvenOrOdd(int elem1, int elem2)
{
    return elem1 % 2 == elem2 % 2;
}

int main()
{
    vector<int> coll1;
    list<int> coll2;
    deque<int> coll3;

    coll1 = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    coll2 = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    coll3 = { 11, 12, 13, 19, 18, 17, 16, 15, 14, 11 };

    PRINT_ELEMENTS(coll1, "coll1: ");
    PRINT_ELEMENTS(coll2, "coll2: ");
    PRINT_ELEMENTS(coll3, "coll3: ");

    // check whether both collections have equal elements in any order
    if (is_permutation(coll1.cbegin(), coll1.cend(), // first range
        coll2.cbegin())) {            // second range
        cout << "coll1 and coll2 have equal elements" << endl;
    }
    else {
        cout << "coll1 and coll2 don't have equal elements" << endl;
    }

    // check for corresponding number of even and odd elements
    if (is_permutation(coll1.cbegin(), coll1.cend(), // first range
        coll3.cbegin(),               // second range
        bothEvenOrOdd)) {             // comparison criterion
        cout << "numbers of even and odd elements match" << endl;
    }
    else {
        cout << "numbers of even and odd elements don't match" << endl;
    }
}
#endif


//检验类的算法：all_of()、any_of()、none_of()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    vector<int> coll;
    vector<int>::iterator pos;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll, "coll: ");

    // define an object for the predicate (using a lambda)
    auto isEven = [](int elem)
        {
            return elem % 2 == 0;
        };

    // print whether all, any, or none of the elements are/is even
    cout << boolalpha << "all even?:  "
        << all_of(coll.cbegin(), coll.cend(), isEven) << endl;
    cout << "any even?:  "
        << any_of(coll.cbegin(), coll.cend(), isEven) << endl;
    cout << "none even?: "
        << none_of(coll.cbegin(), coll.cend(), isEven) << endl;
}
#endif


//使用copy()作为标准输入设备和标准输出设备之间的数据筛检程序。
//程序读取 string, 并以一行一个的方式打印它们
#if 0
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

int main()
{
    copy(istream_iterator<string>(cin),         // beginning of source
        istream_iterator<string>(),            // end of source
        ostream_iterator<string>(cout, "\n"));  // destination
}
#endif


//unique_ptr的复制构造函数、赋值运算符重载函数的实参需要使用move()
// move() 来体现移动语义的细节
#if 0
#include <iostream>
#include <vector>
#include <list>

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr;
    for (auto elem : coll) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    vector<string> coll1 = { "Hello", "this", "is", "an", "example" };
    list<string> coll2;

    // copy elements of coll1 into coll2
    // - use back inserter to insert instead of overwrite
    // - use copy() because the elements in coll1 are used again
    copy(coll1.cbegin(), coll1.cend(),         // source range
        back_inserter(coll2));                // destination range

    // print elements of coll2
    // - copy elements to cout using an ostream iterator
    // - use move() because these elements in coll2 are not used again
    //使用move()，因为coll2中的这些元素不会再次使用
    move(coll2.cbegin(), coll2.cend(),         // source range
        ostream_iterator<string>(cout, " "));  // destination range
    cout << endl;
    //***注***
    //coll2的元素在它们初次被输出后，状态就变得【不确定】，
    // 因为这里用的是move()。
    //然而并不意味着coll2容器不能再出现在以后的代码中，
    //coll2的大小仍然是5, 所以我们可以再次调用move()覆盖(overwrite)这些元素。

    //验证输出：
    copy(coll2.cbegin(), coll2.cend(),
        ostream_iterator<string>(cout, " "));
    cout << endl;
    //输出内容正常，结果表明：
    //move() 并不总是会移动元素。
    // 它只是告诉编译器，【如果可能的话，可以使用移动语义来处理。】
    // 但在这种情况下，ostream_iterator 对元素进行输出，
    // 并没有真正的移动元素。
    //因此，虽然使用了 move()，但元素仍然保留在 coll2 中，
    // 所以第二个 copy() 调用输出了 coll2 中的元素。

    // copy elements of coll1 into coll2 in reverse order
    // - now overwriting (coll2.size() still fits)  先要保证移入的容器的容量足够
    // - use move() because the elements in coll1 are not used again
    move(coll1.crbegin(), coll1.crend(),       // source range
        coll2.begin());                       // destination range

    // print elements of coll2 again
    // - use move() because the elements in coll2 are not used again
    move(coll2.cbegin(), coll2.cend(),         // source range
        ostream_iterator<string>(cout, " "));  // destination range
    cout << endl;
}
#endif


//互换某两个区间的元素 swap_ranges
//(如果要将相同类型的两个容器内的所有元素都互换，应使用swap()成员函数)
#if 0
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> coll1;
    deque<int> coll2;

    INSERT_ELEMENTS(coll1, 1, 9);
    INSERT_ELEMENTS(coll2, 11, 23);

    PRINT_ELEMENTS(coll1, "coll1: ");
    PRINT_ELEMENTS(coll2, "coll2: ");

    // swap elements of coll1 with corresponding elements of coll2
    deque<int>::iterator pos;
    pos = swap_ranges(coll1.begin(), coll1.end(),  // first range
        coll2.begin());              // second range

    //***注***
    //将coll1的元素和coll2的对应元素交换。 
    // 元素个数为distance(coll1.begin(), coll1.end())
    // coll2 之内的其余元素不变动。 
    // swap_ranges()算法返回coll2中第一个未被改动的元素。

    PRINT_ELEMENTS(coll1, "\ncoll1: ");
    PRINT_ELEMENTS(coll2, "coll2: ");
    if (pos != coll2.end()) {
        cout << "first element not modified: "
            << *pos << endl;
    }

    // mirror first three with last three elements in coll2
    swap_ranges(coll2.begin(), coll2.begin() + 3,    // first range
        coll2.rbegin());                   // second range

    PRINT_ELEMENTS(coll2, "\ncoll2: ");
}
#endif


//fill()和generate()的区别
//std::fill(myVector.begin(), myVector.end(), 5);

//使用 lambda 函数作为生成器函数，依次填充向量的每个元素
//int value = 0;
//std::generate(myVector.begin(), myVector.end(), [&value]() { return value++; });

//fill() 用于将范围内的元素设置为给定值，
//而 generate() 则用于使用生成器函数来填充范围内的元素


//旋转元素rotate()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    vector<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll, "coll:      ");

    // rotate one element to the left
    rotate(coll.begin(),      // beginning of range
        coll.begin() + 1,  // new first element
        coll.end());       // end of range
    PRINT_ELEMENTS(coll, "one left:  ");

    // rotate two elements to the right
    rotate(coll.begin(),      // beginning of range
        coll.end() - 2,    // new first element
        coll.end());       // end of range
    PRINT_ELEMENTS(coll, "two right: ");

    // rotate so that element with value 4 is the beginning
    rotate(coll.begin(),                     // beginning of range
        find(coll.begin(), coll.end(), 4),  // new first element
        coll.end());                      // end of range
    PRINT_ELEMENTS(coll, "4 first:   ");
}
#endif


//对元素重新洗牌 random_shuffle()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i) {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll, "coll:     ");

    // shuffle all elements randomly
    random_shuffle(coll.begin(), coll.end());

    PRINT_ELEMENTS(coll, "shuffled: ");

    // sort them again
    sort(coll.begin(), coll.end());
    PRINT_ELEMENTS(coll, "sorted:   ");

    // shuffle elements with default engine
    default_random_engine dre;
    shuffle(coll.begin(), coll.end(),  // range
        dre);                      // random-number generator

    PRINT_ELEMENTS(coll, "shuffled: ");
}
#endif


//将元素向前搬 partition()、stable_partition()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> coll1;
    vector<int> coll2;

    INSERT_ELEMENTS(coll1, 1, 9);
    INSERT_ELEMENTS(coll2, 1, 9);
    PRINT_ELEMENTS(coll1, "coll1: ");
    PRINT_ELEMENTS(coll2, "coll2: ");
    cout << endl;

    // move all even elements to the front
    vector<int>::iterator pos1, pos2;
    pos1 = partition(coll1.begin(), coll1.end(),         // range
        [](int elem) {                        // criterion
            return elem % 2 == 0;
        });
    pos2 = stable_partition(coll2.begin(), coll2.end(),  // range
        [](int elem) {                // criterion
            return elem % 2 == 0;
        });

    //partition()和stable_partition()都将元素分为两组
    //返回值指向第二组元素首元素的迭代器。

    //stable_partition()保持了奇数元素和偶数元素的相对次序，
    // 这一点和partition()不同。

    // print collections and first odd element
    PRINT_ELEMENTS(coll1, "coll1: ");
    cout << "first odd element: " << *pos1 << endl;
    PRINT_ELEMENTS(coll2, "coll2: ");
    cout << "first odd element: " << *pos2 << endl;
}
#endif
//更多用法，见//面试题76：数组中第k大的数字         //实现快速排序算法


//根据谓词函数，划分两个子区间 partition_copy()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> coll = { 1, 6, 33, 7, 22, 4, 11, 33, 2, 7, 0, 42, 5 };
    PRINT_ELEMENTS(coll, "coll: ");

    // destination collections:
    vector<int> evenColl;
    vector<int> oddColl;

    // copy all elements partitioned accordingly into even and odd elements
    partition_copy(coll.cbegin(), coll.cend(), // source range
        back_inserter(evenColl),   // destination for even elements
        back_inserter(oddColl),    // destination for odd elements
        [](int elem) {              // predicate: check for even elements
            return elem % 2 == 0;
        });

    PRINT_ELEMENTS(evenColl, "evenColl: ");
    PRINT_ELEMENTS(oddColl, "oddColl:  ");
}
#endif


//在 main 函数中直接使用 STL 的 std::partition 函数来实现
//快速排序算法的partition()的相同功能
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int arr[] = { 3, 6, 8, 2, 5, 1, 7, 4 };
    int length = sizeof(arr) / sizeof(arr[0]);
    int begin = 0;
    int end = length - 1;

    //1. 取一个随机的索引值
    srand(time(0));
    int rd_index = begin + rand() % (end - begin + 1);

    //补充：
    //可以用C++的随机数产生引擎，见//使用C++中的随机数

    //2. 将随机索引值对应的值移到数组末尾，做为比较标尺
    Swap(&arr[rd_index], &arr[end]);

    //3. 使用 STL 的 partition 函数进行分区
    auto partition_point = std::partition(arr + begin, arr + end + 1,
        [&](int x) { return x <= arr[end]; });

    // 枢轴值的位置
    int pivot_index = partition_point - arr;

    //4. 将枢轴值放到正确的位置上
    Swap(&arr[pivot_index], &arr[end]);

    std::cout << "Pivot index: " << pivot_index << std::endl;

    for (int i = 0; i < length; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
//https://chat.openai.com/share/7de1e374-2091-4aca-8e3f-2dc0f1e86ab9
//实战：
//面试题76：数组中第k大的数字
#endif


//sort()和stable_sort()的区别
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << setw(5) << right << elem;
    }
    std::cout << std::endl;
}

using namespace std;

bool lessLength(const string& s1, const string& s2)
{
    return s1.length() < s2.length();
}

int main()
{
    // fill two collections with the same elements
    vector<string> coll1 = { "1xxx", "2x", "3x", "4x", "5xx", "6xxxx",
                             "7xx", "8xxx", "9xx", "10xxx", "11", "12",
                             "13", "14xx", "15", "16", "17" };
    vector<string> coll2(coll1);

    PRINT_ELEMENTS(coll1, "on entry:\n ");

    // sort (according to the length of the strings)
    sort(coll1.begin(), coll1.end(),           // range
        lessLength);                          // criterion

    stable_sort(coll2.begin(), coll2.end(),    // range
        lessLength);                   // criterion

    //stable_sort()在排序后保持了元素的相对位置

    PRINT_ELEMENTS(coll1, "\nwith sort():\n ");
    PRINT_ELEMENTS(coll2, "\nwith stable_sort():\n ");
}
#endif


//部分排序partial_sort()、partial_sort_copy()
#if 0
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << right << elem;
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    deque<int> coll;

    INSERT_ELEMENTS(coll, 3, 7);
    INSERT_ELEMENTS(coll, 2, 6);
    INSERT_ELEMENTS(coll, 1, 5);
    PRINT_ELEMENTS(coll);

    // sort until the first five elements are sorted
    partial_sort(coll.begin(),      // beginning of the range
        coll.begin() + 5,    // end of sorted range
        coll.end());       // end of full range
    PRINT_ELEMENTS(coll);

    //***注***
    //partial_sort(coll.begin(), coll.begin() + 5, coll.end())
    //不等于
    //sort(coll.begin(), coll.begin() + 5)
    //而应理解为：
    //全部排好序的序列取其前5个元素，其余元素排序按一定方式排列，
    // 不一定有序

    // sort inversely until the first five elements are sorted
    partial_sort(coll.begin(),      // beginning of the range
        coll.begin() + 5,    // end of sorted range
        coll.end(),        // end of full range
        greater<int>());   // sorting criterion
    PRINT_ELEMENTS(coll);

    // sort all elements
    partial_sort(coll.begin(),      // beginning of the range
        coll.end(),        // end of sorted range
        coll.end());       // end of full range
    PRINT_ELEMENTS(coll);
}
#endif


//只需要n个最大或最小元素，但不要求它们必须处于排序状态(sorted), 
//使用nth_element()
#if 0
#include <iostream>
#include <deque>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << right << elem;
    }
    std::cout << std::endl;
}

int main()
{
    deque<int> coll;

    INSERT_ELEMENTS(coll, 3, 7);
    INSERT_ELEMENTS(coll, 2, 6);
    INSERT_ELEMENTS(coll, 1, 5);
    PRINT_ELEMENTS(coll);

    // extract the four lowest elements
    nth_element(coll.begin(),     // beginning of range
        coll.begin() + 3,   // element that should be sorted correctly
        coll.end());      // end of range

    //***理解***
    //第二个实参nth 所指向的元素被更改为假如 [first, last) 已排序
    //则该位置会出现的元素。
    //这个新的 nth 元素前的所有元素小于或等于新的 nth 元素后的所有元素。

    // 使第4个位置上的元素就位，也就是说所有在位置4之前的元素
    // 都小于等于它，所有在位置n之后的元素都大于等于它。
    // 这样，就得到了“根据n位置上的元素”分割开来的两个子序列，
    // 第一子序列的元素统统小于第二子序列的元素。

    // print them
    cout << "the four lowest elements are:  ";
    copy(coll.cbegin(), coll.cbegin() + 4,
        ostream_iterator<int>(cout, " "));
    cout << endl;

    // extract the four highest elements
    nth_element(coll.begin(),     // beginning of range
        coll.end() - 4,     // element that should be sorted correctly
        coll.end());      // end of range

    // print them
    cout << "the four highest elements are: ";
    copy(coll.cend() - 4, coll.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;

    // extract the four highest elements (second version)
    nth_element(coll.begin(),     // beginning of range
        coll.begin() + 3,   // element that should be sorted correctly
        coll.end(),       // end of range
        greater<int>());  // sorting criterion

    // print them
    cout << "the four highest elements are: ";
    copy(coll.cbegin(), coll.cbegin() + 4,
        ostream_iterator<int>(cout, " "));
    cout << endl;
}
#endif


//使用heap相关算法
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T>
inline void INSERT_ELEMENTS(T& coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void PRINT_ELEMENTS(const T& coll,
    const std::string& optcstr = "")
{
    std::cout << optcstr << endl;
    for (auto elem : coll)
    {
        std::cout << right << elem << ' ';
    }
    std::cout << std::endl;
}

using namespace std;

int main()
{
    vector<int> coll;

    INSERT_ELEMENTS(coll, 3, 7);
    INSERT_ELEMENTS(coll, 5, 9);
    INSERT_ELEMENTS(coll, 1, 4);

    PRINT_ELEMENTS(coll, "on entry:           ");

    // convert collection into a heap
    make_heap(coll.begin(), coll.end());
    //在范围 [first, last) 中构造最大堆

    PRINT_ELEMENTS(coll, "after make_heap():  ");

    // pop next element out of the heap
    pop_heap(coll.begin(), coll.end());
    coll.pop_back();

    PRINT_ELEMENTS(coll, "after pop_heap():   ");

    // push new element into the heap
    coll.push_back(17);
    push_heap(coll.begin(), coll.end());

    PRINT_ELEMENTS(coll, "after push_heap():  ");

    // convert heap into a sorted collection
    // - NOTE: after the call it is no longer a heap
    sort_heap(coll.begin(), coll.end());

    PRINT_ELEMENTS(coll, "after sort_heap():  ");
}
//已经有了priority_queue为什么还要有make_heap等heap方法
/*
priority_queue 是 STL 中的一个容器适配器，它提供了一系列封装好的堆操作，
例如 push、pop、top 等，使得用户可以直接使用一个
最大堆或最小堆而不需要关心底层的实现细节。
而 make_heap、push_heap、pop_heap 等函数则是算法，
用于在普通容器（如 vector）上实现堆操作。使用这些函数，
用户可以将任何随机访问容器（如数组或向量）转换为一个堆，并在上面执行堆操作

可以将已有的容器转换为一个堆，不需要将数据复制到 priority_queue 中。
这可以在不改变容器类型的情况下，对现有数据应用堆操作
使用 make_heap 等函数在容器上操作，可以直接访问和修改容器中的数据，
而 priority_queue 则不允许直接访问底层容器。
*/
#endif


//已排序区间的搜索算法
//检查某个元素是否存在：binary_search()
//***注***
//binary_search()的实现中要调用std::lower_bound()
//而std::lower_bound()的实现是使用二分搜索算法来查找给定值
//在已排序序列中的插入位置。
//因此可以将binary_search()作为普通二分搜索算法的代替
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    list<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll);

    //***注***
    //使用binary_search()前区间必须已经排序！

    // check existence of element with value 5
    if (binary_search(coll.cbegin(), coll.cend(), 5))
    {
        cout << "5 is present" << endl;
    }
    else
    {
        cout << "5 is not present" << endl;
    }

    // check existence of element with value 42
    if (binary_search(coll.cbegin(), coll.cend(), 42))
    {
        cout << "42 is present" << endl;
    }
    else
    {
        cout << "42 is not present" << endl;
    }
}
#endif


//已排序的区间
//检查数个元素是否存在（区间2是否为区间1的子集）：includes()
//若已排序范围 [first2, last2) 是已排序范围 [first1, last1) 的子序列则返回 true
//***注***
//要与search()区分
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    list<int> coll;
    vector<int> search;

    INSERT_ELEMENTS(coll, 1, 9);
    PRINT_ELEMENTS(coll, "coll:   ");

    search.push_back(3);
    search.push_back(4);
    search.push_back(7);
    PRINT_ELEMENTS(search, "search: ");

    // check whether all elements in search are also in coll
    if (includes(coll.cbegin(), coll.cend(),  //区间1
        search.cbegin(), search.cend()))      //区间2
    {
        cout << "all elements of search are also in coll"
            << endl;
    }
    else
    {
        cout << "not all elements of search are also in coll"
            << endl;
    }

    auto pos = std::search(coll.cbegin(), coll.cend(), search.cbegin(), search.cend());

    if (pos != coll.end())
        cout << "all elements of search are also in coll"
        << endl;
    else
        cout << "not all elements of search are also in coll"
        << endl;
}
#endif
//***小结***
//已排序区间，区间2中所有元素形成的序列是否在区间1中都有
// (子序列不必相接(连续))：includes()
//区间2中所有元素形成的序列是否在区间1中有
// (子序列需要相接(连续))：search()
//区间2中某个元素是否在区间1中有：find_first_of()


//已排序的区间
//查找第一个或最后一个可能的位置：lower_bound()、upper_bound()
//可以配合insert()方法使用，实现在指定位置插入元素而不破坏已排序的状态
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    list<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    INSERT_ELEMENTS(coll, 1, 9);

    coll.sort();

    PRINT_ELEMENTS(coll);

    // print first and last position 5 could get inserted
    auto pos1 = lower_bound(coll.cbegin(), coll.cend(),
        5);
    auto pos2 = upper_bound(coll.cbegin(), coll.cend(),
        5);

    cout << "5 could get position "
        << distance(coll.cbegin(), pos1) + 1
        << " up to "
        << distance(coll.cbegin(), pos2) + 1
        << " without breaking the sorting" << endl;

    // insert 3 at the first possible position without breaking the sorting
    coll.insert(lower_bound(coll.begin(), coll.end(),
        3),
        3);

    // insert 7 at the last possible position without breaking the sorting
    coll.insert(upper_bound(coll.begin(), coll.end(),
        7),
        7);

    PRINT_ELEMENTS(coll);
}
#endif
//一次性查出第一个或最后一个可能的位置：equal_range()
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    list<int> coll;

    INSERT_ELEMENTS(coll, 1, 9);
    INSERT_ELEMENTS(coll, 1, 9);
    coll.sort();
    PRINT_ELEMENTS(coll);

    // print first and last position 5 could get inserted
    pair<list<int>::const_iterator, list<int>::const_iterator> range;
    range = equal_range(coll.cbegin(), coll.cend(),
        5);

    cout << "5 could get position "
        << distance(coll.cbegin(), range.first) + 1
        << " up to "
        << distance(coll.cbegin(), range.second) + 1
        << " without breaking the sorting" << endl;
}
#endif


//已排序的容器
//合并算法：merge()、set_union()、set_intersection()、
// set_difference()、set_symmetric_difference()
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    vector<int> c1 = { 1, 2, 2, 4, 6, 7, 7, 9 };
    deque<int>  c2 = { 2, 2, 2, 3, 6, 6, 8, 9 };

    // print source ranges
    cout << "c1:                         ";
    copy(c1.cbegin(), c1.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "c2:                         ";
    copy(c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << '\n' << endl;

    // sum the ranges by using merge()
    cout << "merge():                    ";
    merge(c1.cbegin(), c1.cend(),
        c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;

    //求并集
    // unite the ranges by using set_union()
    cout << "set_union():                ";
    set_union(c1.cbegin(), c1.cend(),
        c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;

    //求交集
    // intersect the ranges by using set_intersection()
    cout << "set_intersection():         ";
    set_intersection(c1.cbegin(), c1.cend(),
        c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;

    //求差集
    // determine elements of first range without elements of second range
    // by using set_difference()
    cout << "set_difference():           ";
    set_difference(c1.cbegin(), c1.cend(),
        c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;
    //求出在第一个列表中而不在第二个列表中存在的元素

    //求区间S1,S2的对称差集
    // determine difference the ranges with set_symmetric_difference()
    cout << "set_symmetric_difference(): ";
    set_symmetric_difference(c1.cbegin(), c1.cend(),
        c2.cbegin(), c2.cend(),
        ostream_iterator<int>(cout, " "));
    cout << endl;
    //输出：
    // 1 2 3 4 6 7 7 8

    //对称差集指的是只属于S1或S2,但不同时属于S1和S2的

    //***注***
    //输出中 2 出现的原因可能是集合 c1 中有两个值为 2 的元素，
    // 而集合 c2 中只有一个值为 2 的元素
    //这样的话 2 也会被视为属于对称差集
    //同理对称差集中也有6这个数字
}
#endif


//对已排序的区间，就地一分为二进行合并：inplace_merge()
#if 0
#include "algostuff.hpp"
using namespace std;

int main()
{
    list<int> coll;

    // insert two sorted sequences
    INSERT_ELEMENTS(coll, 1, 7);
    INSERT_ELEMENTS(coll, 1, 8);
    PRINT_ELEMENTS(coll);

    // find beginning of second part (element after 7)
    list<int>::iterator pos;
    pos = find(coll.begin(), coll.end(),    // range
        7);                          // value

    ++pos;

    // merge into one sorted range
    inplace_merge(coll.begin(), pos, coll.end());
    //已排序源区间 [beg1,end1beg2) 和[end1beg2,end2)的元素合并，
    // 使区间    [beg1,end2)    成为两者之总和(且形成已排序状态)。

    PRINT_ELEMENTS(coll);
}
//输出：
/*
1 2 3 4 5 6 7 1 2 3 4 5 6 7 8
1 1 2 2 3 3 4 4 5 5 6 6 7 7 8
*/
#endif


//一个用户自定义的Stack类
#if 0
#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <exception>

template <typename T>
class Stack
{
protected:
    std::deque<T> c;        // container for the elements

public:
    //***注***
    // //创建嵌套类
    // exception class for pop() and top() with empty stack
    class ReadEmptyStack : public std::exception
    {
    public:
        //***注***
        //最后写 throw() 表示该函数不会抛出任何异常
        virtual const char* what() const throw()
        {
            return "read empty stack";
        }
    };

    // number of elements
    typename std::deque<T>::size_type size() const
    {
        return c.size();
    }

    // is stack empty?
    bool empty() const
    {
        return c.empty();
    }

    // push element into the stack
    void push(const T& elem)
    {
        c.push_back(elem);
    }

    // pop element out of the stack and return its value
    T pop()
    {
        if (c.empty())
        {
            throw ReadEmptyStack();
        }

        T elem(c.back());

        c.pop_back();

        return elem;
    }

    // return value of next element
    T& top()
    {
        if (c.empty())
        {
            throw ReadEmptyStack();
        }
        return c.back();
    }
};

#endif /* STACK_HPP */
#endif


//一个用户自定义的Queue类
#if 0
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>
#include <exception>

template <typename T>
class Queue
{
protected:
    std::deque<T> c;        // container for the elements

public:
    // exception class for pop() and front() with empty queue
    class ReadEmptyQueue : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "read empty queue";
        }
    };

    // number of elements
    typename std::deque<T>::size_type size() const
    {
        return c.size();
    }

    // is queue empty?
    bool empty() const
    {
        return c.empty();
    }

    // insert element into the queue
    void push(const T& elem)
    {
        c.push_back(elem);
    }

    // remove next element from the queue and return its value
    T pop()
    {
        if (c.empty())
        {
            throw ReadEmptyQueue();
        }

        T elem(c.front());

        c.pop_front();

        return elem;
    }

    // return value of next element
    T& front()
    {
        if (c.empty())
        {
            throw ReadEmptyQueue();
        }

        return c.front();
    }
};
#endif /* QUEUE_HPP */
#endif


//将bitset当作一组标志
#if 0
#include <bitset>
#include <iostream>
using namespace std;

int main()
{
    // enumeration type for the bits
    // - each bit represents a color
    enum Color {
        red, yellow, green, blue, white, black, //...,
        numColors
    };

    // create bitset for all bits/colors
    bitset<numColors> usedColors;//创建bitset类对象，默认每一位都为0

    // set bits for two colors
    usedColors.set(red);
    usedColors.set(blue);
    //***理解***
    //bitset类中的方法声明：bitset& set( std::size_t pos, bool value = true );
    // 形参pos相当于index
    //usedColors.set(red);表示bitset类对象的第1个元素值设为1

    // print some bitset data
    cout << "bitfield of used colors:   " << usedColors << endl;
    cout << "number   of used colors:   " << usedColors.count() << endl;
    cout << "bitfield of unused colors: " << ~usedColors << endl;//翻转所有位

    //to_string()方法：
    std::cout << usedColors.to_string() << '\n'
        << usedColors.to_string('*') << '\n'
        << usedColors.to_string('O', 'X') << '\n';

    //***注***
    //bitset的bitset<N>::all, std::bitset<N>::any, std::bitset<N>::none 这些方法
    //时间复杂度都是O(N)
    // if any color is used
    if (usedColors.any()) {
        // loop over all colors
        for (int c = 0; c < numColors; ++c) {
            // if the actual color is used
            if (usedColors[(Color)c]) {
                //...
            }
        }
    }
}
#endif


//bitset的特色功能：用bitset表述二进制
#if 0
#include <bitset>
#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main()
{
    // print some numbers in binary representation
    cout << "267 as binary short:     "
        << bitset<numeric_limits<unsigned short>::digits>(267)
        << endl;

    cout << "267 as binary long:      "
        << bitset<numeric_limits<unsigned long>::digits>(267)
        << endl;

    cout << "10,000,000 with 24 bits: "
        << bitset<24>(1e7) << endl;

    //用数值类型初始化bitset类对象
    //*** (bitset类对象存储的是数值类型的二进制表示)***
    //使用to_string()方法将bitset类对象输出为string类对象
    // write binary representation into string
    string s = bitset<42>(12345678).to_string();
    cout << "12,345,678 with 42 bits: " << s << endl;

    //用C-string类型初始化bitset类对象
    //*** (bitset类对象存储的是C-string类型指示的二进制内容) ***
    //使用to_ullong()方法将bitset类对象输出为unsigned long long整数类型
    // transform binary representation into integral number
    cout << "\"1000101011\" as number:  "
        << bitset<100>("1000101011").to_ullong() << endl;
}
#endif


//string类的能力和用法
//提炼临时文件名
#if 0
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    string filename, basename, extname, tmpname;

    const string suffix("tmp");

    // for each command-line argument (which is an ordinary C-string)
    for (int i = 1; i < argc; ++i)
    {
        // process argument as filename
        filename = argv[i];

        // search period in filename
        string::size_type idx = filename.find('.');
        //***注***
        //此处必须使用string::size_type类型
        //不能以 int或 unsigned 作为返回值类型；否则返回值与string::npos之间的
        //比较可能无法正确执行。这是因为npos被设计为size_type类型的 -1
        //不幸的是size_type(由string的分配器定义出)必须是个无正负号整数类型
        //于是-1 被转换为无正负号整数类型，npos 也就成了该类型的最大无正负号值。
        //然而实际值取决于类型size_type的真实定义。
        // 不幸的是对于不同的操作系统，这些最大值类型和值可能都不相同。
        // 事实上(unsigned long) - 1和(unsigned short) - 1 不同。

        //因此，对于：
        //idx == std::string::npos
        //如果 idx的值为 - 1, 由于 idx和字符串 string::npos类型不同，
        // 比较结果可能会是 false

        if (idx == string::npos)
        {
            // filename does not contain any period
            tmpname = filename + '.' + suffix;
        }
        else
        {
            // split filename into base name and extension
            // - base name contains all characters before the period
            // - extension contains all characters after the period
            basename = filename.substr(0, idx);
            extname = filename.substr(idx + 1);

            //***理解***
            //find()方法返回要搜索的字符在string类对象中的index值

            //filename.substr(0, idx);
            //返回 [0, 0+idx) 
            //filename.substr(idx + 1);
            //返回 [pos, size())

            if (extname.empty())
            {
                // contains period but no extension: append tmp
                tmpname = filename;
                tmpname += suffix;
            }
            else if (extname == suffix)
            {
                // replace extension tmp with xxx
                tmpname = filename;
                tmpname.replace(idx + 1, extname.size(), "xxx");
            }
            else
            {
                // replace any extension with tmp
                tmpname = filename;
                tmpname.replace(idx + 1, string::npos, suffix);
                //***注***
                //string::npos必须要写类名string
            }
        }

        // print filename and temporary name
        cout << filename << " => " << tmpname << endl;
    }
}
#endif


//提炼单词并反向打印（可同时查看//面试题58：翻转字符串）
#if 0
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    //所有间隔字符被定义于一个特殊的 string 常量内：
    const string delims(" \t,.;");
    string line;

    // for every line read successfully
    while (getline(cin, line))
    {
        string::size_type begIdx, endIdx;

        // search beginning of the first word
        begIdx = line.find_first_not_of(delims);

        // while beginning of a word found
        while (begIdx != string::npos)
        {
            //***注***
            //从index为begIdx开始，寻找等于delims中任一字符的字符所在的位置
            // 此范围能包含空字符。
            // search end of the actual word
            endIdx = line.find_first_of(delims, begIdx);

            if (endIdx == string::npos)
            {
                // end of word is end of line
                endIdx = line.length();
            }

            // print characters in reverse order
            for (int i = endIdx - 1; i >= static_cast<int>(begIdx); --i)
            {
                cout << line[i];
            }

            cout << ' ';

            // search beginning of the next word
            begIdx = line.find_first_not_of(delims, endIdx);
        }

        cout << endl;
    }
}
#endif


//用C-string字符串初始化string对象
//结尾带不带空字符？
#if 0
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1("abc");
    cout << str1.length() << endl;

    //说明str1一开始就分配了多余的空间用于存储内容
    cout << sizeof(str1) << endl;

    for (int i = 0; i < 4; ++i)
        if (str1[i] == '\0')
            cout << "\\0" << ' ';
        else if (isalpha(str1[i]))
            cout << str1[i] << ' ';
        else
            cout << "?" << ' ';

    cout << endl;

    //***注***
    //理解：
    //只有单实参的 const char*版本才将字符'\0'视为string的结尾特殊符号，
    // 其他所有情况下'\0'都不被视为特殊字符
    //std::string s1("nico");      // initializes s1 with:'n'  'i'  'c'  'o'
    //std::string s2("nico", 5);  //initializes s2 with:'n'  'i'  'c'  'o'  '\0'
    //std::string s3(5, '\0');       //initializes s3 with:'\0'  '\0'  '\0'  '\0'  '\0'

    //前面的代码测试的情况显示：
    //即使s1仅存4个元素，但
    //s1若要显示s1[4]还是会返回一个空字符的。(在C++11中定义是这样的行为)

    string str2("abc", 4);
    cout << str2.length() << endl;

    for (int i = 0; i < 5; ++i)
        if (str2[i] == '\0')
            cout << "\\0" << ' ';
        else if (isalpha(str2[i]))
            cout << str2[i] << ' ';
        else
            cout << "?" << ' ';

    //回答：
    //用C-string字符串初始化std::string对象时，不会带有空字符（\0）。
    // std::string对象会根据传入的C-string字符串的长度自动确定其自身的长度，
    // 并不需要额外的空字符来表示结束。
    //但若使用类似string str2("abc",4);这样来初始化string对象
    //没指定的内容会用空字符填入。

    return 0;
}
#endif


//string的安插元素方法
#if 0
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str{ "bc" };

    //不可用的写法：
    //str.insert(0,'a');
    //str.insert('a');
    //str.insert("a");

    //正确写法：
    str.insert(0, "a");

    cout << str << endl;

    return 0;
}
#endif


//用string类中相关方法进行字符到数值的转换
//补充：
//用to_string()函数进行数值到字符的转换
#if 0
#include <string>
#include <iostream>
#include <limits>
#include <exception>

int main()
{
    try {
        // convert to numeric type
        std::cout << std::stoi("  77") << std::endl;
        std::cout << std::stod("  77.7") << std::endl;
        std::cout << std::stoi("-0x77") << std::endl;

        // use index of characters not processed
        std::size_t idx;
        std::cout << std::stoi("  42 is the truth", &idx) << std::endl;
        std::cout << " idx of first unprocessed char: " << idx << std::endl;

        // use bases 16 and 8
        std::cout << std::stoi("  42", nullptr, 16) << std::endl;
        std::cout << std::stol("789", &idx, 8) << std::endl;
        std::cout << " idx of first unprocessed char: " << idx << std::endl;

        // convert numeric value to string
        long long ll = std::numeric_limits<long long>::max();
        std::string s = std::to_string(ll);  // converts maximum long long to string
        std::cout << s << std::endl;

        // try to convert back
        std::cout << std::stoi(s) << std::endl;  // throws out_of_range
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
#endif


//unique()函数需要结合erase()使用   （remove()也要结合erase()）
#if 0
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    // create constant string
    const string hello("Hello, how are you?");

    // initialize string s with all characters of string hello
    string s(hello.cbegin(), hello.cend());

    // ranged-based for loop that iterates through all the characters
    for (char c : s) {
        cout << c;
    }
    cout << endl;

    // reverse the order of all characters inside the string
    reverse(s.begin(), s.end());
    cout << "reverse:       " << s << endl;

    // sort all characters inside the string
    sort(s.begin(), s.end());
    cout << "ordered:       " << s << endl;

    //错误写法：
    //unique(s.begin(), s.end());
    //cout << s << endl;

    //正确写法：
    // remove adjacent duplicates
    // - unique() reorders and returns new end
    // - erase() shrinks accordingly
    s.erase(
        unique(s.begin(), s.end()),
        s.end());
    cout << "no duplicates: " << s << endl;
    //理解：
    //unique()从来自范围 [first, last) 的相继等价元素组消除首元素外的元素，
    //并返回范围的新逻辑结尾的尾后迭代器。

    //unique()保持剩余元素的相对顺序，且不更改容器的物理大小。
    //指向范围的新逻辑结尾和物理结尾之间元素的迭代器仍然可解引用，
    // 但元素自身拥有【未指定值】。
    // 调用 unique 后有时会调用容器的 erase 成员函数，
    // 它擦除未指定值并减小容器的物理大小，以匹配其新的逻辑大小。
}
#endif


//不使用getline()，向string对象输入多行数据，且不忽略空白字符的方法
#if 0
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <locale>
using namespace std;

int main()
{
    string input;

    //禁用流 str 中的 skipws 标志
    //禁用有格式输入函数所做的跳过前导空白符（默认启用）。在输出上无效果。
    // don't skip leading whitespaces
    cin.unsetf(ios::skipws);

    // read all characters while compressing whitespaces
    //const locale& loc(cin.getloc());    // locale

    //使用unique_copy函数从标准输入流cin中读取字符，
    // 并将其复制到容器input中，但是只保留连续的不同字符。
    // 在这个特定的例子中，unique_copy函数还接受了一个谓词函数作为参数，
    // 用于定义何为"相邻的重复字符"。
    unique_copy(istream_iterator<char>(cin),  // beginning of source
        istream_iterator<char>(),     // end of source
        back_inserter(input),         // destination
        [=](char c1, char c2) {      // criterion for adj. duplicates
            //return isspace(c1, loc) && isspace(c2, loc);
            return isspace(c1) && isspace(c2);
        });

    // process input
    // - here: write it to the standard output
    cout << input;

    cout << endl;
    for (auto it = input.begin(); it != input.end(); ++it)
        if (*it == ' ')
            cout << "[space]";
        else if (*it == '\n')
            cout << "[\\n]";
        else if (*it != '\n')
            cout << *it;
}
//测试：
//输入：
/*
        a          b
      c          d
^Z
*/
//输出：
/*
 a b
c d

[space]a[space]b[\n]c[space]d[\n]
*/
//***注***
//第二行开始的空白字符被忽略了
#endif


//打开文件读取数据，并写入数据到文件
#if 0
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("DataReceive.txt");

    if (!fin.is_open())
        cout << "Can not open DataReceive.txt !" << endl;

    string str;

    //不好的写法：
#if 0
    while (fin)
    {
        getline(fin, str);

        cout << str << endl;
    }
    //原因：
    //读到EOF时eof()为1，fail()也为1，fin的布尔值才为false
#endif
//输出：
/*
            a              b
      c               d
      c               d
*/

//合适的写法：
    getline(fin, str);
    while (fin)
    {
        cout << str << endl;

        getline(fin, str);
    }
    //输出：
    /*
                a              b
          c               d
    */

    //清除标志位
    fin.clear();
    //回到文件开头
    fin.seekg(0);

    ofstream fout("DataOutput.txt", ios_base::out | ios_base::app);
    if (!fout.is_open())
        cout << "Can not open DataOutput.txt !" << endl;

    getline(fin, str);
    while (fin)
    {
        cout << str << endl;

        fout << str << '\n';
        //fout << str.c_str()<<'\n';

        getline(fin, str);
    }

    fin.close(); // 关闭文件流
    fout.close();

    return 0;
}
#endif


//使用string stream
//用途：
//以“独立于真实I/O设备以外”的方式来处理I/O。
// 例如output的文字格式可以在 string 中设定，
// 然后再将string发送至某个输出通道。
// 也可以逐行读取 input, 并以 string stream 处理每一行。
#if 0
#include <iostream>
#include <sstream>//ostringstream类
#include <bitset>
using namespace std;

int main()
{
    ostringstream os;

    // decimal and hexadecimal value
    os << "dec: " << 15 << hex << " hex: " << 15 << endl;
    //str()方法：将缓冲区内容当做一个string返回
    cout << os.str() << endl;

    // append floating value and bitset
    bitset<15> b(5789);
    os << "float: " << 4.67 << " bitset: " << b << endl;

    // overwrite with octal value
    //运用seekp()将涂写位置设于stream 起始处，
    // 这么一来后继的 operator<< 就把输出写到 string 头部，
    // 于是覆盖了原本的string stream 头部内容。未被覆盖的字符依然有效。
    os.seekp(0);

    os << "oct: " << oct << 15;
    cout << os.str() << endl;

    //补充：
    //要删除 stream 的现有内容，可利用函数str()将崭新内容赋予缓冲区：
    //strm.str("");
}
#endif


//Input string stream的主要用途
//格式化地从既有string中读取数据
//应用场景：
//文件中每行数据先存入string对象，再将string内容设置为缓冲区内容
//再对缓冲区内容进行格式化的读取处理（见面试题36：后缀表达式）
#if 0
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    int x;
    float f;

    string str = "1.12";

    //将string内容设置为缓冲区内容
    istringstream is(str);

    is >> x >> f;

    cout << x << ' ' << f << endl;

    return 0;
}
#endif
/*
可以方便地将字符串分割成各种部分，
或者将字符串中的数字提取出来并转换为数值类型。
这在处理文本数据或者解析格式化的输入时非常有用。
*/
//解析格式化的输入
#if 0
#include <iostream>
#include <sstream>
#include <string>

struct Student
{
    std::string name;
    int age;
    float score;
};

int main()
{
    // 假设这是一个包含学生信息的文本文件
    std::string studentData = "Alice,20,85.5\nBob,22,78.2\nCharlie,21,90.0";

    std::istringstream iss(studentData); // 使用istringstream从字符串中读取数据

    std::string line;
    while (std::getline(iss, line))// 逐行读取数据
    {
        std::istringstream lineStream(line);
        std::string name;
        int age;
        float score;

        // 使用流操作符将每一行的数据提取出来
        if (std::getline(lineStream, name, ',') &&
            lineStream >> age &&
            lineStream.ignore(1) && // 忽略逗号
            lineStream >> score)
        {

            // 创建学生对象并输出信息
            Student student{ name, age, score };
            std::cout << "Name: " << student.name << ", Age: " << student.age << ", Score: " << student.score << std::endl;
        }
    }

    return 0;
}

#endif


//使用C++中的随机数
#if 0
#include <random>//第一步：包含随机数程序库
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    //第二步：提供产生随机数的引擎
    // create default engine as source of randomness
    std::default_random_engine dre;

    //第三步：使用均匀分布，得到指定范围的随机数
    // uniform_int_distribution：用于生成整数类型的随机数。
    // 你可以指定生成随机数的范围，包括范围内的所有整数。
    // use engine to generate integral numbers between 10 and 20 (both included)
    std::uniform_int_distribution<int> di(10, 20);
    for (int i = 0; i < 20; ++i) {
        std::cout << di(dre) << " ";
    }
    std::cout << std::endl;

    //uniform_real_distribution：用于生成浮点数类型的随机数。
    // 你可以指定生成随机数的范围，在指定的范围内生成均匀分布的浮点数。
    // use engine to generate floating-point numbers between 10.0 and 20.0
    // (10.0 included, 20.0 not included)
    std::uniform_real_distribution<double> dr(10, 20);
    for (int i = 0; i < 8; ++i) {
        std::cout << dr(dre) << " ";
    }
    std::cout << std::endl;

    //使用随机数生成引擎来打乱容器内元素次序
    // use engine to shuffle elements
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    //...
    std::shuffle(v.begin(), v.end(),  // range
        dre);                // source of randomness
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
#endif
//补充：
//使用C标准随机值生成器会造成的问题(P912)
//当商被当作n且为小整数时，许多伪随机数生成器制造出来的余数并不很随机。
//如果n是大数，且被生成之最大值并非均匀地可被n除尽，
//那么某些余数的出现率会远高于其他。


//并发编程
//高级接口：async()、future
//低层接口：thread、promise

//并行运行func1()、func2()
#if 0
#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

int doSomething(char c)
{
    // random-number generator (use c as seed to get different sequences)
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    // loop to print character after a random period of time
    for (int i = 0; i < 10; ++i)
    {
        //当前线程暂停时间
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }

    return c;
}

int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}

int main()
{
    std::cout << "starting func1() in background"
        << " and func2() in foreground:" << std::endl;

    //将以下写法：
    //int result = func1()+func2();
    //改成：

    //第一步：
    // 异步启动func1()
    // start func1() asynchronously (now or later or never):
    std::future<int> result1(std::async(func1));
    //理解：
    //使用 std::async()尝试启动 func1()于后台，并将结果赋值给某个 std::future对象
    //async()尝试将其所获得的函数立刻【异步启动】于一个分离线程内。
    // 因此概念上func1()在这里被启动了，不会造成main()停滞。
    // 基于两个原因，返回 future 对象是必要的：
    /*
        1.它允许你取得“传给 async()的那个函数”的未来结果——
            也许是个返回值，也许是个异常。
            这个 future object已受到“被启动函数”返回类型的特化，
            如果被启动的是个返回“无物”的后台任务(background task),
            这就会是 std::future<void>。
        2.它必须存在，确保“目标函数”或快或慢终会被调用。
            注意先前我说async()尝试启动目标函数。
            如果这样的事情没发生，稍后我们需要这个 future 对象才能强迫启动之
            (当我们需要函数的运行结果或当我们想要确保该函数被执行时)。
     */

     //第二步：
     //正常启动func2()于前台
    int result2 = func2();    // call func2() synchronously (here and now)

    //第三步：
    // 使用get()方法，意思是欲明确索求目标函数的结果
    // print result (wait for func1() to finish and add its result to result2)
    int result = result1.get() + result2;

    // get()被调用，以下三件事情之一会发生；
    /*
     1.如果 func1()被 async()启动于一个分离线程中并且已结束，你会立刻获得其结果。
     2.如果func1()被启动但尚未结束，get()会引发停滞(block)
        待 func1()结束后获得结果。
     3.如果 func1()尚未启动，会被强迫启动如同一个同步调用；
         get()会引发停滞直至产生结果。
     这样的行为很重要，因为这确保了在单线程环境中，
     或是当async()无法启动新线程时(不论基于任何理由), 程序仍能有效运作。
     */

     /*
     因此，
     std::future<int> result1(std::async(func1));
     和
     result1.get()
     的组合允许你以某种方式优化程序：
     (1)如果可能，当 main 线程的下一个语句被处理时func1()被并行运行，
     (2)如果无法并行运行，那么func1()会在 get()被调用时
     被循序调用(called sequentially)。
     这就意味着无论如何都能保证至少在 get()执行后一定会调用
     func1()——不是异步就是同步。
     */

     //补充：
     /*
     以下或许不是你要的：
     std::future<int> result1(std::async(func1));

     int result = func2()+ result1.get();//might call func2() after func1() ends

     由于上述第二个语句右侧的核算顺序，result1.get()有可能在 func2()之前被调用
     */

     //整体运行时间是func1()和func2()运行时间中的较大者  加上 计算总和的时间
    std::cout << "\nresult of func1()+func2(): " << result
        << std::endl;
}
#endif
//补充：
//Launch(发射)策略
/*
//指示async()被调用时应明确地以异步方式启动目标函数：（该做法不必非得调用get()）
// force func1() to start asynchronously now or throw std::system_error

std::future<long> result1 = std::async(std::launch:: async, func1);

//指示强制延缓执行(deferred execution)：
以 std::launch:deferred为发射策略传给 async()。下面的做法允许你延缓func1()直到你对f调用get() :

std::future<…> f(std::async(std::launch::deferred,
        func1));                                                     //defer func1 until get()

//这保证 func1()绝不会在没有get()(或 wait(); 见第953页)的情况下启动。
*/


//处理后台操作所产生的异常，只需使用get()做出“以同步方式调用该操作”
//所做的相同动作即可
#if 0
#include <future>
#include <list>
#include <iostream>
#include <exception>

using namespace std;

void task1()
{
    // endless insertion and memory allocation
    // - will sooner or later raise an exception
    // - BEWARE: this is bad practice
    list<int> v;
    while (true)
    {
        for (int i = 0; i < 1000000; ++i)
        {
            v.push_back(i);
        }
        cout.put('.').flush();
    }
}

int main()
{
    cout << "starting 2 tasks" << endl;
    cout << "- task1: process endless loop of memory consumption" << endl;
    cout << "- task2: wait for <return> and then for task1" << endl;

    auto f1 = async(task1);  // start task1() asynchronously (now or later or never)

    cin.get();  // read a character (like getchar())

    cout << "\nwait for the end of task1: " << endl;
    try
    {
        f1.get();  // wait for task1() to finish (raises exception if any)
    }
    catch (const exception& e)
    {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
}
#endif


//class std::future提供了“处理并发运算之未来结果”的能力。然而
//你只能处理该结果一次。第二次调用get()会导致不可预期的行为
//有时候，多次处理“并发运算之未来结果”是合理的，特别当多个其他线程都想
//处理这份结果时。基于这个目的，C++标准库提供了class std::shared_future, 
// 于是你可以多次调用get(), 导致相同结果，或导致抛出同一个异常
#if 0
#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

int queryNumber()
{
    // read number
    cout << "read number: ";
    int num;
    cin >> num;

    // throw exception if none
    if (!cin)
    {
        throw runtime_error("no number read");
    }

    return num;
}

void doSomething(char c, shared_future<int> f)
{
    try
    {
        // wait for number of characters to print
        int num = f.get();  // get result of queryNumber()

        for (int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch (const exception& e)
    {
        cerr << "EXCEPTION in thread " << this_thread::get_id()
            << ": " << e.what() << endl;
    }
}

int main()
{
    try
    {
        //启动一个线程来查询一个数字
        // start one thread to query a number
        shared_future<int> f = async(queryNumber);
        //shared future可以以寻常的 future为初值，
        // 于是 future的状态(state)会被搬移到 shared future 身上
        //就内部而言，所有 shared future object共享所谓 shared state,
        // 后者由 async()建立，用来存放目标函数的运行结果
        // (也存放函数本身——如果它被推迟执行的话)。

        // start three threads each processing this number in a loop
        auto f1 = async(launch::async, doSomething, '.', f);
        auto f2 = async(launch::async, doSomething, '+', f);
        auto f3 = async(launch::async, doSomething, '*', f);
        //***注***
        // 每一次 doSomething()被调用，
        // 便通过传入之第二参数shared future的成员函数get(),
        // 等待及处理 queryNumber()的执行结果：

        // wait for all loops to be finished
        f1.get();
        f2.get();
        f3.get();
    }
    catch (const exception& e)
    {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout << "\ndone" << endl;
}
#endif


//使用thread
#if 0
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

void doSomething(int num, char c)
{
    try
    {
        // random-number generator (use c as seed to get different sequences)
        default_random_engine dre(42 * c);
        uniform_int_distribution<int> id(10, 1000);
        for (int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
            //...
        }
    }
    // make sure no exception leaves the thread and terminates the program
    catch (const exception& e)
    {
        cerr << "THREAD-EXCEPTION (thread "
            << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "THREAD-EXCEPTION (thread "
            << this_thread::get_id() << ")" << endl;
    }
}

int main()
{
    try
    {
        thread t1(doSomething, 5, '.');  // print five dots in separate thread
        cout << "- started fg thread " << t1.get_id() << endl;
        //t1线程负责打印 "....."

        // print other characters in other background threads
        for (int i = 0; i < 5; ++i)
        {
            thread t(doSomething, 10, 'a' + i); // print 10 chars in separate thread
            cout << "- detach started bg thread " << t.get_id() << endl;
            t.detach();  // detach thread into the background
        }
        //5个线程负责打印a到e共50个字母

        cin.get();  // wait for any input (return)

        cout << "- join fg thread " << t1.get_id() << endl;
        t1.join();  // wait for t1 to finish
    }
    catch (const exception& e)
    {
        cerr << "EXCEPTION: " << e.what() << endl;
    }
}
//***注***
//多个线程会共享数据区和堆，每个线程维护自己的栈。
#endif

//关于线程的ID
// 实现(implementation)有可能在被申请时才动态生成这些ID,而不是在thread 
// 被启动时就生成之，那么 main thread 的编号就取决于先前对 thread ID的申请次数
// 
// 因此，识别线程(例如主线程 master thread)的唯一办法是，
// 将线程启动时的 ID存储下来，以此为唯一识别值：
/*
std::thread::id masterThreadID;

void doSomething()
{
if(std::this_thread::get_id()== masterThreadID)
{
    ...
}

std::thread master(doSomething);
masterThreadID = master.get_id();
std::thread slave(doSomething);
*/


//用来传递运行结果和异常的一般性机制：promise
#if 0
#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>

void doSomething(std::promise<std::string>& p)
{
    try {
        // read character and throw exception if 'x'
        std::cout << "read char ('x' for exception): ";

        char c = std::cin.get();
        if (c == 'x')
        {
            throw std::runtime_error(std::string("char ") + c + " read");
        }

        std::string s = std::string("char ") + c + " processed";

        p.set_value_at_thread_exit(std::move(s));    // store result
    }
    catch (...)
    {
        p.set_exception_at_thread_exit(std::current_exception());  // store exception
    }
}

int main()
{
    try {
        // create a promise to 【store】 the outcome
        std::promise<std::string> p;
        //存string的值或一个异常，并可被 future object 取其数据当作线程结果。

        // create a future to 【process】 the outcome
        std::future<std::string> f(p.get_future());
        //创建一个future对象，通过p.get_future()获取promise对象的future，
        // 用于获取线程的结果。这里的 f 将会持有异步任务的未来结果。

        // start a thread using the promise to store the outcome
        std::thread t(doSomething, std::ref(p));
        //***注***
        //创建一个新的线程，线程的执行函数是doSomething，
        // 并传递了一个std::reference_wrapper<std::promise<std::string>>类型的参数，
        // 引用了之前创建的promise对象p。使其状态可以被改变。
        // 这个线程将会执行异步任务。

        t.detach();
        //...

        // process the outcome
        std::cout << "result: " << f.get() << std::endl;
        //通过get(),我们可以取得“被存储的结果”,或是令“被存储的异常”再次被抛出
    }
    catch (const std::exception& e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "EXCEPTION " << std::endl;
    }
    //***注***
    //catch (...)用于捕获任何可能发生的异常，不管是标准异常（派生自std::exception）
    // 还是其他类型的异常。这样做可以确保即使出现了未预期的异常类型，
    // 程序也可以通过输出错误信息来进行适当的处理，而不至于直接崩溃
}
#endif
//问题：
//C++多线程编程，已经有了future为什么还要promise
/*
std::future 是一个用来获取异步操作结果的机制。
当你启动一个异步任务时，你可以通过 std::async 或其他方式获取一个 std::future 对象，
这个对象会在任务完成后持有结果。通过 std::future，你可以等待异步操作完成，
并获取其结果，这样你就可以在主线程中处理该结果。

std::promise 则用于在一个线程中设置异步操作的结果，在另一个线程中获取这个结果。
你可以将一个 std::promise 和 std::future 关联起来，
通过 std::promise 设置值，然后在其他地方通过相应的 std::future 获取这个值。

使用 std::promise 的场景通常是这样的：
你有一个函数执行的线程（例如，一个后台线程），而另一个函数在这个线程完成后需要
使用这个函数的结果。在这种情况下，你可以通过 std::promise 在一个线程中设置结果，
并通过与其关联的 std::future 在另一个线程中获取这个结果。

换句话说，std::promise 允许你在一个线程中设置一个值（通常是异步任务的结果），
而 std::future 则允许你在另一个线程中等待并获取这个值。
这种分离的设计使得异步编程更加灵活和方便。
*/


//packaged_task<>
//尝试立即启动于后台


// 并发
// 使用多线程(multiple thread)几乎总是会伴随“数据的并发访问”(concurrent data access)。
// 线程有可能提供数据给其他线程处理，或是备妥必要的先决条件(precondition)
// 用以启动其他进程(process)。
// 第一条规则：
// 多个线程并发处理相同的数据而又不曾同步化(synchronization),
// 那么唯一安全的情况就是：所有线程只读取数据。

//当两个或更多线程并发处理相同的变量或对象或成员，而且至少其中一个线程改动了它，
// 而你又不曾同步化(synchronize)该处理动作，你就可能有了深深的麻烦。
// 这就是C++ 所谓的 data race。
// C++11标准中定义的 data race 是“不同线程中的两个互相冲突的动作，
// 其中至少一个动作不是atomic(不可切割的), 而且无一个动作发生在另一动作之前”。
// Data race 总是导致不可预期的行为。

//Concurrent Data Access (并发数据访问)为什么造成问题
//C++,总是个抽象层，一个像 C++这样的标准具体描述了语句和操作的影响，
// 但并非等同于其所产生的汇编码(assembler code)。标准描述的是 what 而不是how。
//编译器都可以将代码无限优化，只要程序行为外观上相同(这些优化只考虑在单线程情况下)。
// 因此，被生成的代码是个黑盒子，是可以化的变，只要可观测行为保持稳定
//任何实现(implementation)可以自由忽视国际标准(International Standard)的任何规定，
// 只要最终成果貌似遵守了那些规定

//什么情况下可能出错：
//Unsynchronized data access(未同步化的数据访问):
// 并行运行的两个线程读和写同一笔数据，不知道哪一个语句先来。
//Half-written data(写至半途的数据):
// 某个线程正在读数据，另一个线程改动它，于是读取中的线程甚至
// 可能读到改了一半的数据，读到一个半新半旧值。
//Reordered statement(重新安排的语句) :语句和操作有可能被重新安排次序(reordered),
//也许对于每一个单线程正确，但对于多个线程的组合却破坏了预期的行为。

//除非另有说明，C++标准库提供的函数通常不支持“写或读”动作
// 与另一个“写”动作(写至同一笔数据)并发执行。
//并发处理同一容器内的不同元素是可以的(但vector<bool>例外)。因此，不同的线程
//可以并发读和/或写同一容器内的不同元素。例如，每个线程可以处理某些事然后将结果
//存储于一个共享的 vector 内专属该线程的某元素。
//并发处理 string stream、file stream或 stream buffer 会导致不可预期的行为。
// 但是格式化输入自和输出至某个标准stream(它和C I/O同步化了，见15.14.1节第845页)
// 是可以的，虽然这可能导致插叙的字符

//C++的vollatile对于解决并发数据访问产生的问题无效
//volatile 关键字主要用于告知编译器不要对标记为 volatile 的变量进行优化，
// 以确保每次访问该变量时都从内存中读取其最新值，而不是使用缓存的值。
// 然而，volatile 并不能保证线程安全或解决并发数据访问的问题。

//线程同步化技术：
//Mutex、lock
//条件变量
//Atomic


//使用Mutex和Lock
//为了获得独占式的资源访问能力，相应的线程必须锁定(lock) mutex,
// 这样可以防止其他线程也锁定mutex, 直到第一个线程解锁(unlock) mutex。

//传统的mutex和lock用法的缺点：
// 你应该确保异常——它会终止独占——也解除(unlock)相应的 mutex, 
// 否则资源就有可能被永远锁住。此外也可能出现deadlock 情景：
// 两个线程在释放它们自己的lock 之前彼此等待对方的 lock。

//解决：
//根据RAII守则(Resource Acquisition Is Initialization),构造函数将获得资源，而析构函数
//甚至当“异常造成生命期结束”它也总是会被调用——则负责为我们释放资源
// 使用C++标准库提供的
//class std::lock_guard
#if 0
#include <future>
#include <mutex>
#include <iostream>
#include <string>

std::mutex printMutex;  // enable synchronized output with print()

void print(const std::string& s)
{
    // ...

    //lock应该被限制在可能之最短周期内，因为它们会阻塞(block)其他代码的并行运行机会
    {
        std::lock_guard<std::mutex> lg(printMutex);
        for (char c : s)
        {
            std::cout.put(c);
        }
        std::cout << std::endl;
    }
    //令每次对print()的调用都独占地写出所有字符
    //实现【输出同步化(synchronize)】

    //...
}

int main()
{
    auto f1 = std::async(std::launch::async,
        print, "Hello from a first thread");

    auto f2 = std::async(std::launch::async,
        print, "Hello from a second thread");

    print("Hello from the main thread");

    //***注***
    //lock 的次序仍旧不明确，因此上述三行输出有可能以任何次序出现。
}
#endif


//死锁是怎么产生的？
//有如下接口：
/*
class DatabaseAccess
{
private:
std::mutex dbMutex;
… //state of database access

public:
void createTable(…)
{
std::lock_guard<std::mutex>lg(dbMutex);
}
void insertData(…)
{
std::lock_guard<std::mutex>lg(dbMutex);
}
};

当我们引入一个 public成员函数而它可能调用其他 public 成员函数，情况变得复杂：
void createTableAndInsertData(…)
{
std::lock_guard<std::mutex>lg(dbMutex);
createTable(…);   //ERROR:deadlock because dbMutex is locked again
}

调用createTableAndInsertData()会造成 deadlock(死锁),因为它锁住 dbMutex 之后调
用createTable(),造成后者尝试再次 lock dbMutex,那将会 block(阻塞)直到 dbMutex
变为可用，而这绝不会发生，因为 createTableAndInsertData()会 block(阻塞)直到
createTable()完成。
*/


//使用递归的Lock  (Recursive Lock)解决死锁
#if 0
#include <mutex>

class DatabaseAccess
{
private:
    std::recursive_mutex dbMutex;
public:
    void createTable()
    {
        std::lock_guard < std::recursive_mutex> lg(dbMutex);
    }
    void insertData()
    {
        std::lock_guard<std::recursive_mutex> lg(dbMutex);
    }
    void createTableAndinsertData()
    {
        std::lock_guard<std::recursive_mutex> lg(dbMutex);

        createTable();//OK:no deadlock
    }
};
//借着使用recursive_mutex,上述行为不再有问题。
// 这个 mutex 允许同一线程多次锁定，并在最近一次(last)相应的 unlock()时释放 lock 
#endif


//尝试性的lock以及带时间性的lock


//处理多个lock   使用全局的lock()函数


//保证一次仅有一个lock拥有mutex ：class unique_lock


//多线程环境下的缓式初始化(lazy initialization)
#if 0
class X
{
private:
    mutable std::once_flag initDataFlag;
    void initData()const
    {};
public:
    int getData() const
    {
        std::call_once(initDataFlag, &X::initData, this);
        // once flag 对象当作第一实参传给call_once()是为了确保传入的机能只被执行一次。
        // 因此，如果第一次调用成功，下一次调用又带着相同的 once flag,
        // 传入的机能就不会被调用——即使该机能与第一次有异
    }
};
#endif


//Future(见18.1节第946页)允许你停下来(to block)直到另一线程提供某笔数据
// 或直到另一线程结束。然而 future 从某线程传递数据到另一线程只能一次。
// 事实上 future的主要目的是处理线程的【返回值或异常】

//Condition variable(条件变量),它可用来同步化线程之间的数据流逻辑依赖关系
// (logical dependencies in data flow between threads)。


//让某线程等待另一个线程的一个粗浅方法
//使用ready flag之类的标记
#if 0
class x
{
    bool readyFlag;
    std::mutex readyFlagMutex;

public:

    void dosomething()
    {
        std::unique_lock<std::mutex> ul(readyFlagMutex);

        // wait until readyFlag is true:
        while (!readyFlag)
        {
            ul.unlock();
            std::this_thread::yield();//hint to reschedule to the next thread
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ul.lock();
        }
    } //release lock
};
//这通常意味着等待中的线程(waiting thread)需要轮询(poll)
// 其所需要的数据或条件是否已达到。这不是好的解决方法。
//等待中的线程(waiting thread)消耗宝贵的CPU时间重复检验 flag,且当它锁住mutex时
// “负责设置 ready flag”的那个线程会被阻塞(blocked)。
// 此外我们也很难找出适当的 sleep 周期：两次检查若间隔太短则线程仍旧太浪费CPU
// 时间于检查动作上，若太长则也许等待的 task 已完成而线程却还继续 sleeping, 
// 导致发生延误。
#endif


//使用Condition Variable(条件变量) 同步化线程之间的数据流逻辑依赖关系
//一个线程可以唤醒(wake up)一或多个其他等待中的线程(waiting thread)。
#if 0
//第一步：包含<condition_variable> 和 <mutex>头文件
#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>

//第二步，创建flag检查数据是否真的备妥
bool readyFlag;
//补充：
/*
condition variable 也许有所谓假醒(spurious wakeup)。
也就是某个 condition variable 的 wait动作有可能在该 condition variable
尚未被 notified 时便返回。假醒无法被测定，以使用者的观点来看它们实质上是随机的。
然而它们通常发生于 thread library 无法可靠确定某个 waiting thread 不遗漏任何
notification时。由于遗漏 notification 便代表 condition variable 无用，
thread library 宁愿在线程的 wait 之中唤醒它而不愿承受风险。”
因此，发生 wakeup 不一定意味着线程所需要的条件已经掌握了。更确切地说，
在wakeup之后你仍然需要代码去验证“条件实际已达成”。
因此(例如)我们必须检查数据是否真正备妥，或是我们仍需要诸如ready flag之类的东西。
*/

//第三步：创建锁和条件变量
std::mutex readyMutex;
std::condition_variable readyCondVar;

void thread1()
{
    // do something thread2 needs as preparation
    std::cout << "<return>" << std::endl;
    std::cin.get();

    //第四步：锁住，更新flag，解锁，通知条件变量

    // signal that thread1 has prepared a condition
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;//***为什么对于基本数据类型也要这样？***见//使用atomic来取代mutex和lock
    } // release lock

    //那个用来激发“条件终于满足”的线程(或多线程之一)必须调用notify_one()或notify_all()
    readyCondVar.notify_one();
    //唤醒一个或所有等待中的线程(waiting thread)。
    //***注***
    //通知动作不需要被安排在 lock 保护区内。
}

void thread2()
{
    //第五步：以一个 unique_lock锁住 mutex,一面检查条件一面等待被通知，然后释放锁

    // wait until thread1 is ready (readyFlag is true)
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        //***注***
        //此处必须使用unique_lock，不可使用lock_guard,
        // 因为 wait()的内部会明确地对 mutex 进行解锁和锁定。

        //那个“等待条件被满足”的线程必须调用
        readyCondVar.wait(ul, []() { return readyFlag; });// wait()内部会不断调用该第二实参，直到它返回 true

        //这段代码相当于
        /*
        {
            std::unique_lock<std::mutex> ul(readyMutex);
            while(!readyFlag)
            {
                readyCondVar.wait(ul);
            }
        }// release lock
        */

        //补充：
        /*
        std::condition_variable::wait()函数的内部需要在等待期间解锁互斥量，
        并在条件满足时重新锁定互斥量。而std::lock_guard无法手动解锁，
        它只能在构造时锁定互斥量，在析构时自动释放锁。
        这就意味着如果在std::lock_guard的作用域内调用wait()函数，
        它将尝试在等待期间重新解锁已经被锁定的互斥量，
        而std::lock_guard不支持手动解锁，从而导致未定义的行为。

        因此，为了能够在等待期间手动解锁并在条件满足时重新锁定互斥量，
        必须使用std::unique_lock。std::unique_lock允许在其生命周期内
        手动控制锁的获取和释放，这与std::condition_variable的要求相符合。
        */

    } // release lock

    // do whatever shall happen after thread1 has prepared things
    std::cout << "done" << std::endl;
}

int main()
{
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
}
#endif
//补充：
/*
unique_lock内部持有mutex的状态：locked,unlocked。
unique_lock比lock_guard占用空间和速度慢一些，因为其要维护mutex的状态

unique_lock 在使用上比lock_guard更具有弹性，和 lock_guard 相比，
unique_lock 主要的特色在于：
unique_lock 不一定要拥有 mutex，所以可以通过
default constructor 建立出一个空的 unique_lock。
unique_lock 虽然一样不可复制（non-copyable），但是它是可以转移的（movable）。
所以，unique_lock 不但可以被函数回传，也可以放到 STL 的 container 里。

另外，unique_lock 也有提供 lock()、unlock() 等函数，可以用来手动加锁解锁mutex
unique_lock本身还可以用于std::lock参数，
因为其具备lock、unlock、try_lock成员函数,这些函数不仅完成
针对mutex的操作还要更新mutex的状态。
*/


//使用 Condition Variable(条件变量)实现多线程 Queue
#if 0
#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <queue>

//创建一个queue被并发使用
std::queue<int> queue;

std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
    // push different values (val til val+5 with timeouts of val milliseconds into the queue
    for (int i = 0; i < 6; ++i)
    {
        {
            std::lock_guard<std::mutex> lg(queueMutex);
            queue.push(val + i);
        } // release lock

        //condition variable 用来在“有新元素可用”时激发和唤醒某一个线程
        queueCondVar.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(val));
    }
}

void consumer(int num)
{
    // pop values if available (num identifies the consumer)
    while (true)
    {
        int val;
        {
            //***注***
            //所有等待某个 condition variable 的线程都必须使用相同的 mutex;
            // 当 wait()家族的某个成员被调用时该mutex 必须被 unique_lock 锁定，
            // 否则会发生不明确的行为。
            std::unique_lock<std::mutex> ul(queueMutex);

            queueCondVar.wait(ul, [] { return !queue.empty(); });

            val = queue.front();
            queue.pop();
        } // release lock

        std::cout << "consumer " << num << ": " << val << std::endl;
    }
}

int main()
{
    //三个线程都把数值推入(push)某个 queue,另两个线程则是从中读取数据

    // start three providers for values 100+, 300+, and 500+
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 500);

    // start two consumers printing the values
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);

    //***注***
    //两个 consumer的输出并非同步，所以字符有可能交错。
    // 也请注意，并发等待者(线程)的被通知次序是不确定的。
}
#endif


//使用atomic来取代mutex和lock
//在//使用Condition Variable(条件变量) 同步化线程之间的数据流逻辑依赖关系
//中有如下代码块：
/*
    // signal that thread1 has prepared a condition
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;
    } // release lock
*/
//1.
//一般而言，即使面对基本数据类型，读和写也不是 atomic(不可切割的)
//因此你可能读到一个被写一半的 bool值，C++ standard 说这会带来不明确的行为。
//2.
//编译器生成的代码有可能改变操作次序，所以供应端(线程)有可能在供应数据之前
// 就先设置 ready flag, 而消费端(线程)亦有可能在侦测 ready flag 之前就处理该数据。


//使用atomic的高层接口，它所提供的操作将使用默认保证，不论内存访问次序如何。
// 这个默认保证提供了顺序一致性(sequential consistency), 意思是在线程之中
// atomic 操作保证一定“像代码出现的次序”那样地发生。
// 因此 18.4.3 节第 986 页所说的重排语句也就不会出现。

//重写//使用Condition Variable(条件变量) 同步化线程之间的数据流逻辑依赖关系
//atomic的高级接口：store()、load()
#if 0
#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>
#include <atomic>

std::atomic_bool readyFlag(false);
//***注***
//总是应该将 atomic object 初始化，
// 因为其 default 构造函数并不完全初始化它
// (倒不是其初值不明确，而是其lock 未被初始化)。

std::mutex readyMutex;
std::condition_variable readyCondVar;

void thread1()
{
    std::cout << "<return>" << std::endl;
    std::cin.get();

    readyFlag.store(true);
    //***注***
    /*
    比较：
    readyFlag.store(true);
    这是一种原子操作，将true存储到readyFlag中。
    它确保在存储期间没有其他线程可以同时访问或修改readyFlag的值。
    这个操作返回void，因此它不会返回任何值。
    readyFlag = true;
    这是普通的赋值操作。在单线程环境下可能是安全的，
    但在多线程环境下可能会导致竞态条件。
    在多线程环境下，如果有其他线程同时访问或修改readyFlag，
    可能会导致未定义的行为或程序错误。
    */

    readyCondVar.notify_one();
}

void thread2()
{
    {
        //***注***
        //使用condition variable 时我们仍然需要 mutex 才能保护对 
        // condition variable 的消费 (即使readyFlag现在是个 atomic object)
        std::unique_lock<std::mutex> ul(readyMutex);

        readyCondVar.wait(ul, []() { return readyFlag.load(); });

    }
    std::cout << "done" << std::endl;
}

int main()
{
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
}
#endif


//atomic 的store()、load()方法的细节
#if 0
#include <atomic>    // for atomics
#include <future>    // for async() and futures
#include <thread>    // for this_thread
#include <chrono>    // for durations
#include <iostream>

long data;
std::atomic<bool> readyFlag(false);

void provider()
{
    // after reading a character
    std::cout << "<return>" << std::endl;
    std::cin.get();

    // provide some data
    data = 42;

    // and signal readiness
    readyFlag.store(true);
    //***注***
    //store()会对影响所及的内存区执行一个所谓 release 操作，确保此前所有内存操作(all prior memory operations)
    // 不论是否为 atomic, 在store发挥效用之前都变成“可被其他线程看见”。
    //***理解***
    //这意味着在执行store()之后，其他线程可以看到该线程之前所有的内存修改，
    // 无论这些修改是否为原子操作。
    // 这样可以确保【内存的一致性】，避免了出现数据不一致或者竞态条件的情况。
}

void consumer()
{
    // wait for readiness and do something else
    while (!readyFlag.load())
    {
        std::cout.put('.').flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    //load()会对影响所及的内存区执行一个所谓 acquire 操作，确保随后所有内存操作(all following memory operations)
    // 不论是否为 atomic, 在 load 之后都变成“可被其他线程看见"。

    //***理解***
    //由于data的设值发生在 provider()将readyFlag存储(store)为 true之前，
    //而对 data的处理发生在 consumer()将true载入(loaded)放进 readyFlag之后，
    // 因此对data的处理保证发生在 data已提供之后

    // and process provided data
    std::cout << "\nvalue : " << data << std::endl;
}

int main()
{
    // start provider and consumer
    auto p = std::async(std::launch::async, provider);
    auto c = std::async(std::launch::async, consumer);
}
#endif


//补充：
/*

long data;
std::atomic<bool> readyFlag(false);

data = 42; //provide some data
readyFlag.store(true); //and signal readiness

while(!readyFlag.load()){ //loop until ready
}
std::cout << data << std::endl; //and process provided data

使用默认的内存处理次序(default memory order),于是保证顺序一致性(sequential consistency)

事实上，我们真正调用的是：

data = 42;
readyFlag.store(true,std::memory_order_seq_cst);

while(!readyFlag.load(std::memory_order_seq_cst)){
}
std::cout << data << std::endl;

上述操作都有一个可有可无的实参用来指定内存次序(memory order),默认实参值
是std::memory_order_seq_cst(代表 sequential consistent memory order顺序一致的内存次序)。

如果指定另一种内存处理次序(memory order),我们就可以削弱(weaken)对次序的保证，
在我们的例子中这就足以(例如)要求 provider(数据供应者)不推迟 atomic store之后的操作
(not delay operations past the atomic store),而 consumer(数据消费者)不会在
atomic load 之后带来向前操作(not bring forward operations following the atomic load):

data = 42;
readyFlag.store(true,std::memory_order_release);

和

while(!readyFlag.load(std::memory_order_acquire)){
}
std::cout << data << std::end1;

然而如果放宽(relaxing)atomic操作次序上的所有约束，会导致不明确的行为：
// ERROR:undefined behavior:
data = 42;
readyFlag.store(true,std::memory_order_relaxed);

原因是 std::memory_order_relaxed 不保证此前所有内存操作
(all prior memory operations)在store发挥效用前都变得“可被其他线程看见”。
因此 provider 线程有可能在设置ready flag 之后才写 data,
于是 consumer 线程有可能在 data 正被写时读它，这就会造成data race

*/


//atomic的低层接口
//如上所述，ad、store、exchange、CAS 及 fetch等操作提供了一个增补能力：
// 它们允许你额外传递一个内存次序(memory order)实参。
//这些低层接口是为真正的并发专家准备的

