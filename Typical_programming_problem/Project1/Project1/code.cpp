//
#if 1

#endif


//面试题1：赋值运算符函数
#if 0
#include <string.h>

class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);

    CMyString& operator = (const CMyString& str);

    void Print();

private:
    char* m_pData;
};

//经典解法：
#if 0
//如果传入的参数不是引用而是实例，那么从形参到实参会调用一次
//复制构造函数。把参数声明为引用可以避免这样的无谓消耗，
//能提高代码的效率。同时，我们在赋值运算符函数内不会改变
//传入的实例的状态，因此应该为传入的引用参数加上const关键字。
CMyString& CMyString::operator = (const CMyString& str)
{
    //错误写法：
	//if (*this == str) //原因：类对象之间用==运算符，但此运算符还没有被重载定义。

    if (this == &str)//1.检查是否是自我复制
        return *this;

    delete[] m_pData;//2.释放m_pData指向的原数据内容

    size_t len = strlen(str.m_pData);//3.为新字符串分配足够的内存空间
    m_pData = new char[len + 1];
    strcpy(m_pData, str.m_pData);

    return *this;//4.实现连续赋值
}
#endif

//高级解法1：
#if 0
//一旦在赋值运算符函数内部抛出一个异常，
//CMyString的实例不再保持有效的状态，这就违背了
//异常安全性(Exception Safety)原则。
CMyString& CMyString::operator = (const CMyString& str)
{
    if (this == &str)
        return *this;

    //拷贝原数据的地址
    char* DataTemp = m_pData;

    if (m_pData = new char[strlen(str.m_pData) + 1])
    {
        //若动态内存可以申请到
        delete [] DataTemp;

        strcpy(m_pData, str.m_pData);
    }

    return *this;

	/* 先用new分配新内容，再用delete释放已有的内容。这样
		只在分配内容成功之后再释放原来的内容，也就是当分配内存失败时
		我们能确保CMyString的实例不会被修改 */
}
#endif

//高级解法2：
//效率更高
#if 1
CMyString& CMyString::operator = (const CMyString& str)
{        
    if (this != &str)
    {
        CMyString strTemp(str);//调用深复制构造函数（使用new的）

        //（以下三条语句可以用自定义的Swap函数实现）
        //创建临时指针存临时对象的私有数据成员的地址
        char* pTemp = strTemp.m_pData;
        //临时对象的私有数据成员替换为当前类对象的私有数据成员的地址
        strTemp.m_pData = m_pData;
        //当前类对象的私有数据成员替换为临时对象的私有数据成员的地址
        m_pData = pTemp;
        //相当于进行了一个调换工作
    }

    //***注***
    //由于strTemp是一个局部变量，但程序运行到if的外面时也就出了
    //该变量的作用域，就会自动调用strTemp的析构函数，把strTemp.m_pData
    //所指向的内存释放掉。由于
    //strTemp.m_pData指向的内存就是实例之前m_pData的内存，
    //这就相当于自动调用析构函数释放实例的内存。

    //还可以从《Effective C++》P56 中进行理解

    return *this;

    /* 即先创建一个临时实例，再交换临时实例和原来的实例 */
}
#endif
#endif


//面试题2：实现Singleton模式
//(设计一个类，只能生成该类的一个实例)
#if 0

//错误方法：
//***注***
//静态成员变量必须进行初始化，否则会编译错误
#if 0
class Singleton
{
private:
    static Singleton* instance;

    Singleton()//书P382 好处：避免了本来将自动生成的默认的默认构造函数；
    {}//声明为私有的，就指出不允许直接用默认构造函数生成对象

public:
    //在需要实例时，调用静态函数来创建对象
    static Singleton* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }

        return instance;
    }
};
#endif

//饿汉单例：在类装载时完成了初始化，静态成员对象初始化成功
//类加载速度相比懒汉慢，但获取对象的速度快，是一种典型的以时间换取空间的做法
//优点：线程安全
//缺点：不管你用不用这个对象，他都会先创建出来，会造成浪费内存空间
#include <iostream>

using namespace std;

class Singleon
{
private:
    Singleon()
    {
        cout << "Singleon()" << endl;
    }

    static Singleon* instance;

public:
    static Singleon* GetSingleon()
    {
        return instance;
    }
    static Singleon* Destroy()
    {
        delete instance;
        instance = NULL;
    }
};

//不能在类声明中初始化不带const的静态成员变量
//对于静态类成员，可以在类声明之外使用单独的语句来进行初始化
Singleon* Singleon::instance = new Singleon();
//***注***
//此处可以调用默认构造函数，原因是在类装载时已完成了初始化

int main()
{
    //Singleon()不可访问
    //Singleon* S1 = new Singleon();

    Singleon* sl1 = Singleon::GetSingleon();
    Singleon* sl2 = Singleon::GetSingleon();
    Singleon* sl3 = Singleon::GetSingleon();
    cout << sl1 << endl;
    cout << sl2 << endl;
    cout << sl2 << endl;
    //system("pause");
    return 0;
}
#endif


//面试题3：数组中重复的数字
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> res(0);
void find_num(int* p,int n);

int main()
{
    int n;
    cin >> n;

    int* p_data = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> p_data[i];
    }

	find_num(p_data, n);

    for (int x : res)
        cout << x << " ";

    return 0;
}
void find_num(int* p, int n)
{
    //sort(p,p+n);

    //利用数组的索引与值的对应关系，记录单个数字的出现次数
    int suoyin[10] = {0};

	for (int i = 0; i < n; i++)
    {
        suoyin[p[i]]++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (suoyin[i] > 1)
            res.push_back(i);
    }

    return ;
}
//修改：
//void find_num(int* p, int n)可以改成
//bool find_num(int* p, int n)
//并在函数内加入针对无效输入的代码段
//{ if(p==nullptr)   ......    }
#endif


//面试题4：二维数组中的查找
#if 0
#include <iostream>

using namespace std;

bool Find(int (* matrix)[4], int rows, int columns, int target);

int main()
{
    int matrix[4][4] = {
        {1,2,8,9},
        {2,4,9,12},
        {4,7,10,13},
        {6,8,11,15}
    };

    bool flag = Find(matrix,4,4,7);
    
    cout<<((flag == true )? "true" : "false");

    return 0;
}
bool Find(int(*matrix)[4], int rows, int columns, int target)
{
    //每次都选择一个矩形区域的右上角的元素
    //与target数字进行比较，从而缩小查找范围
    //每次可以缩小一列的搜索范围

    if (matrix == nullptr)
        return false;

    int row, column;
    row = 0, column = columns - 1;

    while (row < rows && column >=0)
    {
        if (matrix[row][column] == target)
        {
            return true;
        }
        else if (matrix[row][column]>target)
        {
            column--;
        }
        else
        {
            row++;
        }
    }
    //***注***
    //若每次选择的是矩形区域的左上角或右下角
    //那就无法缩小搜索区域

    return false;
}
#endif


//初始化字符数组来存储字符串和初始化指针来指向字符串有何区别
#if 0
#include <stdio.h>
int main()
{
    char str1[] = "hello world";
    char str2[] = "hello world";
    const char* str3 = "hello world";
    const char* str4 = "hello world";

    if (str1 == str2)
        printf("strl and str2 are same.n");
    else
        printf("strl and str2 are not same.\n");

    if (str3 = str4)
        printf("str3 and str4 are same.\n");
    else
        printf("str3 and str4 are not same.In");

    return 0;

	//初始化数组把静态存储区的字符串拷贝到数组中，(而str1与str2两个数组的初始地址是不同的)
	//	而初始化指针只把字符串的地址拷贝给指针
}
#endif


//面试题5：替换空格
//普通解法：
//遍历，从前向后替换，但会造成越是后面的字符串
//被移动的次数越多，造成时间效率低下
#if 0
#include <iostream>
#include <string>
using namespace std;

bool replace(string &s);

int main()
{
    string s1 = "We are happy";

    if (replace(s1))
        cout << s1;

    return 0;
}
bool replace(string& s)
{
    bool flag = false;

    string seq = "%20";

    string::iterator it_tmp;
    int x;

    for (auto it = s.begin(); it != s.end(); it++)
    {
        if (*it == ' ')
        {
            s.erase(it);
            s.insert(it,seq.begin(),seq.end());

            //***注***
            //必须要加上这一句，用来更新it指向的新位置
            it = s.begin();
        }
        //Expression: cannot increment string iterator because the iterator wasinvalidated (e.g. reallocation occurred, or the string was destroyed)
        //***注***
        //在进行迭代器遍历容器时，原来的容器不应该再继续压入任何元素了，否则迭代器可能失效。
        //vector的迭代器失效的原因是，vector进行了改变容量大小（注意是capacity而非size）的操作，这个时候，
        //【会重新申请内存空间】，
        //并将原来的元素进行拷贝，这个时候指向原来位置的iterator仍旧指向原来的位置，
        //而这时原来的位置的元素早已在vector扩容操作里被删除了，故此时iterator指向的是一个未知的值，故迭代器失效
        //https ://blog.csdn.net/m0_48966435/article/details/119775625
    }

    flag = true;

    return flag;
}
#endif
//好的解法：
//先遍历一次字符串，统计出空格的总数，可以计算出
//替换之后字符串的长度
//从后往前复制，这样就能减少移动的次数，从而提高效率
#if 0
#include <iostream>
#include <string>
using namespace std;

char* replace(char* ch, int length);

int main()
{
    char s1[] = "We are happy";

    cout << replace(s1, strlen(s1)) << endl;

    char s2[] = "";
    cout << (replace(s2, strlen(s2)) == nullptr ? "ERROR" : "OK") << endl;

    char s3[] = " ";
    cout<< replace(s3, strlen(s3)) << endl;

    return 0;
}
char* replace(char* source, int length)
{
    //补充代码
    if (source == nullptr || length <= 0||source[0]=='\0')
        return nullptr;

    int space_count = 0;

    for (int i = 0; i < length; i++)
    {
        if (source[i] == ' ')
            space_count++;
    }

    char* res = new char[length + 2 * space_count+1];

    char string[3] = {'%','2','0'};
    //p2指向要存储在res中的source加长后的空字符处
    int p2 = length + 2 * space_count;
    //p1指向source末尾的空字符处
    int p1 = length;

    //有瑕疵的写法：
    //无法处理字符串中有连续多个空格
#if 0
    while (p1>=0&&p2>=0)
    {
        if (source[p1] == ' ')
        {
            res[p2--] = string[2];
            res[p2--] = string[1];
            res[p2--] = string[0];

            p1--;
        }

       res[p2]= source[p1];

       p2--;
       p1--;
    }
#endif 
     
    //修改：
#if 1
    while (p1 >= 0 && p2 >= 0)
    {
        if (source[p1] == ' ')
        {
            res[p2--] = string[2];
            res[p2--] = string[1];
            res[p2--] = string[0];
        }
        else
        {
            res[p2] = source[p1];
            p2--;
        }

        p1--;
    }
#endif

    return res;
}
#endif
//在合并两个数组(包括字符串)时，如果从前往后复制每个数字(或
//字符)则需要重复移动数字(或字符)多次，那么我们可以考虑从后往前
//复制，这样就能减少移动的次数，从而提高效率。


//面试题6：从尾到头打印链表
#if 0
#include <iostream>
#include <stack>
struct ListNode
{
    int m_nKey;
    ListNode* m_pNext;
};

void PrintListReversingly(ListNode* pHead);

int main()
{


    return 0;
}

void PrintListReversingly(ListNode* pHead)
{
    std::stack<int> st;

    if (pHead == nullptr)
        return;

    ListNode* tmp = pHead;
    while (tmp != nullptr)
    {
        st.push(tmp->m_nKey);

        tmp=tmp->m_pNext;
    }

    while (!st.empty())
    {
        std::cout << st.top();
        st.pop();
    }

    return;
}

//递归法：
#if 0
void PrintListReversingly(ListNode* pHead)
{
    if (pHead != nullptr)
    {
        if (pHead->m_pNext != nullptr)
        {
            PrintListReversingly(pHead->m_pNext);
        }

        std::cout<<pHead->m_nKey;
    }
}
#endif

#endif
//基于递归的代码看起来很简洁，但有一个问题：当链表非常长
//的时候，就会导致函数调用的层级很深，从而有可能导致函数调用栈溢出。
//显然用栈基于循环实现的代码的鲁棒性要好一些。


//面试题7：重建二叉树
#if 0
#include <iostream>
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

BinaryTreeNode* Construct(int* startPreorder, int* startInorder, int length)
{
    if (startPreorder == nullptr || startInorder == nullptr || length <= 0)
    {
        return nullptr;
    }

    return ConstructCore(startPreorder, startPreorder+length-1, startInorder, startInorder+length-1);
}
                                //前序遍历的字符数组地址                                         中序遍历的字符数组地址
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    //前序遍历的第一个数字是根节点的值
    int rootValue = startPreorder[0];

    //建立空节点
    BinaryTreeNode* root = new BinaryTreeNode();

    //为节点赋值
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = nullptr;

    //若前序遍历的数组仅一个元素
    if (startPreorder == endPreorder)
    {
        if (startInorder == endInorder && *startPreorder == *startInorder)
            return root;
        else
            throw std::exception("Invalid input");
    }

    //在中序遍历序列中找到根节点的值
    int* rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue)
    {
        ++rootInorder;
    }

    //若在中序遍历中未找到在前序遍历中出现的根节点
    if(rootInorder==endInorder&&*rootInorder!=rootValue)
        throw std::exception("Invalid input");

    //在中序遍历中
    //计算出两指针间的距离值，作为左子树的个数的值
    int leftLength = rootInorder - startInorder;
    //在前序遍历中
    //创建指针指向左子树序列的末尾的位置
    int* leftPreorderEnd = startPreorder + leftLength;

    if (leftLength > 0)
    {
        //构建左子树
        root->m_pLeft = ConstructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    }
    
    if(leftLength<endPreorder-startPreorder)
    {
        //构建右子树
        root->m_pRight = ConstructCore(leftPreorderEnd +1,endPreorder,rootInorder+1,endInorder);
    }

    return root;
}
#endif


//面试题8：二叉树的下一个节点
//对于一颗二叉树，给出一个中序遍历下的节点号，要求给出其下一个节点。
#if 0
#include <iostream>
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
    BinaryTreeNode* m_pParent;
};

BinaryTreeNode* GetNext(BinaryTreeNode* pNode)
{
    if (pNode == nullptr)
        return nullptr;

    //创建一个节点指针用于存储下一个节点的地址
    BinaryTreeNode* pNext = nullptr;

    if (pNode->m_pRight != nullptr)
    {
        //若该节点有右子树，
        //那么它的下一个节点就是它的右子树中最左的子节点
        BinaryTreeNode* pRight = pNode->m_pRight;

        while (pRight->m_pLeft != nullptr)
        {
            pRight=pRight->m_pLeft;
        }

        pNext = pRight;
    }
    else if (pNode->m_pParent != nullptr)//若有父节点
    {
        //若该节点无右子树且该节点是其父节点的左子节点，
        //那么它的下一个节点就是它的父节点
        
        //若该节点无右子树且该节点是其父节点的右子节点，
        //那么它的下一个节点就是它的指向父节点的指针一直向上遍历时，
        //一个满足如下条件的节点：
        //某个节点是其父节点的左子节点，则该节点的父节点就是满足条件的节点。

        BinaryTreeNode* pCurrent = pNode;
        BinaryTreeNode* pParent = pNode->m_pParent;

        while (pParent != nullptr && pCurrent == pParent->m_pRight)
        {
            pCurrent = pParent;
            pParent = pParent->m_pParent;
        }

        pNext = pParent;
    }

    return pNext;
}
#endif


//面试题9：用两个栈实现队列
#if 0
#include <stack>
#include <exception>
using std::stack;
using std::exception;

template <typename T> class CQucue
{
public:
    CQueue(void);
    ~CQucue(void);

    void appendTail(const T& node);
    T deleteHead();
private:
    stack<T>stack1;
    stack<T>stack2;
};

template <typename T>
void CQucue<T>:: appendTail(const T& node)
{
    stack1.push(node);
}

template <typename T>
T CQucue<T>::deleteHead()
{
    T head;

    if (stack2.empty())
    {
        while (!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }

    if (stack2.empty())
        throw new exception("Error, queue is empty.");

    head = stack2.top();
    stack2.pop();

    return head;
}
#endif


//用两个队列实现栈
//由于栈是后进先出，向队列推入元素后，
//若要弹出，则要弹出的应该是最后推入的元素。
//那么需要让queue1不断弹出队头元素到queue2，
//直到仅剩1个元素，而其他元素都进入了queue2，
//清空queue1。
//同样再次弹出元素时，queue2要不断向queue1弹出元素。
//直到queue2仅剩1个元素，然后该元素值可以作为返回值。
//queue2清空。这样就实现了栈的先进先出功能。
#if 1

#endif


//面试题10：斐波那契数列
#if 0
#include <iostream>

long long Fibo(int n);
int main()
{
    int n;
    std::cin >> n;

    long long res=Fibo(n);

    std::cout << res << std::endl;

    return 0;
}

//不太好的解法：
#if 0
long long Fibo(int n)
{
    //long long num;

    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return Fibo(n-1)+Fibo(n-2);

    //return num;
}
#endif
//画出求F(10)时的递归调用树，可以发现：
//重复的节点数太多即重复的计算太多

//较好的解法
//避免重复的计算，那就把已经得到的中间项保存起来，那么就不能用递归了
//选择用循环
#if 1
long long Fibo(int n)
{
    int res[2] = {0,1};
    if(n<2)
    return res[n];

    long long NMinusOne = 1;
    long long NMinusTwo = 0;
    long long N;  //0  1  1  2  3  5  8

    for (long long i = 2; i <= n; ++i)
    {
        N = NMinusOne + NMinusTwo;

        NMinusTwo = NMinusOne;
        NMinusOne = N;
    }

    return N;
}
#endif

#endif


//青蛙跳台阶问题
//青蛙可以跳1档也可以跳2档
#if 0
#include <iostream>

using namespace std;

int Cal(int n);

int main()
{
    int n;
    cin >> n;

    cout << Cal(n)<<endl;

    return 0;
}
int Cal(int n)
{
    //  1  2  3  5  8
    int num[3] = {0,1,2};
    if(n<3)
    return num[n];

    long long NMinusOne = 2;
    long long NMinusTwo = 1;
    long long N;  

    for (long long i = 3; i <= n; ++i)
    {
        N = NMinusOne + NMinusTwo;

        NMinusTwo = NMinusOne;
        NMinusOne = N;
    }

    return N;
}
#endif


//用小矩形去覆盖大矩形的方法数量，本质还是斐波那契数列
#if 1

#endif


//实现快速排序算法
//核心：先在数组中选一个数字，再将比选择的数字大的数字移到数组右边
//将比选择的数字小的数字移到数组左边
//快速排序其实就是我们前面认为最慢的冒泡排序的升级，它们都属于交换排序类。
//即它也是通过不断比较和移动交换来实现排序的，只不过它的实现，
//增大了记录的比较和移动的距离，将关键字较大的记录从前面直接移动到后面，
//关键字较小的记录从后面直接移动到前面，从而减少了总的比较次数和移动交换次数。
#if 0
#include <iostream>
#include <exception>
#include <ctime>
using namespace std;

int RandomInRange(int a,int b)
{
    srand((unsigned int)time(0));
    // 生成 [0, max]
    //int x = rand() % (max + 1);

    // 生成 [1, max]
    //int x = 1 + rand() % (max);

    // 生成 [min, max] 范围的随机数
    //int x = min + rand() % (max - min + 1);

    int x = a + rand() % (b-a+1);
    return x;
}

void Swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//***begin和end都指的是索引值***
int Partition(int data[], int length,int begin,int end)
{
    if (data == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //生成一个在指定范围内的随机数
    int index = RandomInRange(begin,end);
    //该随机数作为索引值对应的数字与数组末尾的数字交换
    //那么数组末尾的数字就是随机索引值对应的数字
    Swap(&data[index],&data[end]);

    //创建枢轴small存储索引值，其初始值比begin小1，如：begin为0，则small为-1
    int small = begin - 1;
    
    //索引值从头开始，逐渐增加
    for (index = begin; index < end; ++index)
    {
        //若当前索引值指向的数字比随机索引值指向的数字小
        if (data[index] <= data[end])//注意是小于等于
        {
            //增加small的值
            ++small;

            //若small不为当前的索引值
            if (small  !=  index)
                Swap(&data[index],&data[small]);//互换元素，目的是
            //让索引值small左侧的值都小于该索引值所对应的值
        }        
    }
	//让small再增加1
	++small;
	//让随机索引值指向的数字移动到small指向的位置上
	Swap(&data[small], &data[end]);

    //返回枢轴所在位置
    return small;
}
//https://www.youtube.com/watch?v=duln2xAZhBA

void QuickSort(int data[], int length, int begin, int end)
{
    if (begin == end)
        return;

    int index = Partition(data, length, begin, end);

    if (index > begin)
        QuickSort(data, length, begin, index - 1);
    if(index < end)
        QuickSort(data, length, index+1, end);
}

int main()
{
    int data[] = {6,5,5,4,3,1,2};

    QuickSort(data, sizeof(data)/4, 0, 0 + (sizeof(data)/4)-1);

    for (auto x : data)
        cout << x << " ";

    //for (int index = 0; index < 7; index++)
    //    cout << data[index] << " ";

    return 0;
}
#endif


//对于一个较小范围内的数字序列，要求排序，时间复杂度为O(n)
#if 0
void SortAges(int* ages, int length)
{
    if (ages == nullptr || length <= 0)
        return;

    const int OldestAge = 99;

    //创建一个数组存储各年龄的出现次数
    int TimesOfAge[OldestAge + 1] = {0};//一定要先初始化

    for (int i = 0; i < length; ++i)
    {
        TimesOfAge[ages[i]]++;
    }

    //***注***
    //利用索引本就有序，对数组的内容重新进行填充
    int index = 0;
    for (int i = 0; i < OldestAge; ++i)
    {
        for (int j = 0; j < TimesOfAge[i]; ++j)
        {
            ages[index] = i;
            ++index;
        }
    }
}
#endif


//如果面试题是要求在排序的数组(或者部分排序的数组)中查找一个数字
//或者统计某个数字出现的次数，那么我们都可以尝试用二分查找算法。
//面试题11：旋转数组的最小数字
//在旋转数组中，由于是把递增排序数组前面的若干个数字搬到数组的后面，
//因此第一个数字总是大于或者等于最后一个数字。
#if 0
#include <iostream>
#include <exception>
using namespace std;

int Min(int* numbers, int length);
int MinInOrder(int* number, int length);

int main()
{
    int num[] = {3,4,5,1,2};

    cout << Min(num, sizeof(num) / 4)<<endl;

    //int* p = nullptr;
    //cout << Min(p, 1);

    int num2[] = { 1,2,3,4,5 };
    cout << Min(num2, 5)<<endl;

    int num3[] = { 1,0,1,1,1 };
    cout << Min(num3, 5) << endl;

    return 0;
}
//二分查找法，时间复杂度为O(logn)
#if 0
int Min(int* numbers, int length)
{
    if (numbers == nullptr||length<=0)
        throw new exception("Error !");

    int p1, p2;
    p1 = 0, p2 = length - 1;

    int mid;
    while (p2 - p1 != 1)
    {
        mid = p1 + (p2 - p1) / 2;
        if (numbers[mid] >= numbers[p1])
            p1 = mid;//如果该中间元素位于前面的递增子数组，
        //那么它应该大于或者等于第一个指针指向的元素。此时数组中最小的元素
        //应该位于该中间元素的后面。我们可以把第一个指针指向该中间元素，
        //这样可以缩小寻找的范围。移动之后的第一个指针仍然位于前面的递增子数组。
        else
            p2 = mid;
    }

    return numbers[p2];
}
#endif
//瑕疵：若把排序数组的前面0个数字搬到后面，那么该代码无法支持。
//修改：
#if 0
int Min(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        throw new exception("Error !");

    int p1, p2;
    p1 = 0, p2 = length - 1;

    //初始化为首元素的索引值，以支持移动0个数字的情况
    int mid=p1;

    //首元素需要大于等于末尾的元素才能进入循环
    while (p2 - p1 != 1&&numbers[p1]>=numbers[p2])
    {
        mid = p1 + (p2 - p1) / 2;
        if (numbers[mid] >= numbers[p1])
            p1 = mid;
        else
            p2 = mid;
    }

    return numbers[mid];
}
#endif
//瑕疵：若出现p1与p2与中间的数字相同的情况，如1，0，1，1，1，1
//则代码无法支持
#if 1
int Min(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        throw new exception("Error !");

    int p1, p2;
    p1 = 0, p2 = length - 1;

    //初始化为首元素的索引值，以支持移动0个数字的情况
    int mid = p1;

    //首元素需要大于等于末尾的元素才能进入循环
    while (p2 - p1 != 1 && numbers[p1] >= numbers[p2])
    {
        mid = p1 + (p2 - p1) / 2;

        //处理最特殊的情况：p1与p2与中间的数字相同
        if (numbers[p1] == numbers[p2] && numbers[p1] == numbers[mid])
            return MinInOrder(numbers,length);

        if (numbers[mid] >= numbers[p1])
            p1 = mid;
        else
            p2 = mid;
    }

    return numbers[mid];
}

//针对特殊情况，只能采用顺序查找方法
int MinInOrder(int* number, int length)
{
    int min = number[0];

    for (int i = 0;i < length; i++)
    {
        min = min < number[i] ? min : number[i];
    }

    return min;
}
#endif
#endif


//面试题12：矩阵中的路径
//用dfs模板做
#if 0
#include <iostream>

using namespace std;

const char target[4] = {'b','f','c','e'};

char book[3][4];

char path[4];
bool hasPath(int index,int row,int column);
bool check(const char* ch1,const char* ch2);

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

char matrix[3][4] = { {'a','b','t','g'},{'c','f','c','s'},{'j','d','e','h'} };

int main()
{
    book[0][0] = 1;
    cout<<hasPath(0, 0, 0);

    return 0;
}
bool hasPath(int index, int row, int column)
{
    if (check(path, target))
    {
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        int r = row + dx[i];
        int c = column + dy[i];

        if (!book[r][c] && r < 3 && c < 4 && r >=0 && c >= 0&&
            matrix[r][c] == target[index])
        {
            book[r][c] = 1;
            path[index] = matrix[r][c];                     

            if (hasPath(index + 1, r, c))
            {
                return true;
            }
        }
        else
            continue;
    }

    return false;
}
bool check(const char* ch1, const char* ch2)
{
    for (int i = 0; i < 4; i++)
    {
        if (ch1[i] != ch2[i])
            return false;
    }

    return true;
}
#endif
//用回溯法模板做
#if 0
#include <iostream>
#include <vector>
using namespace std;

bool hasPath(int index, int row, int column);
bool check(const char* ch1, const char* ch2);

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

//以下写法不行
//bool hasPath(char[][] matrix, );

//***注***
//这样写利于动态调整矩阵的大小，且列与行都可动态变化
bool hasPath(vector<vector<char>>& matrix, int row, int col,
    const char* target);

//核心代码块
bool hasPathCore(vector<vector<char>>& matrix, int row, int col,
    int r, int c, const char* target, int index, bool** visit);

int main()
{
	//char matrix[3][4] = { {'a','b','t','g'},{'c','f','c','s'},{'j','d','e','h'} };

    vector<vector<char>>matrix = {{'a','b','t','g'},{'c','f','c','s'},{'j','d','e','h'}};

	const char target[5] = { 'b','f','c','e','\0'};

    cout << hasPath(matrix, 3,  4, target);

    return 0;
}

bool hasPath(vector<vector<char>>& matrix, int row, int col,
    const char* target)
{
    if (matrix.size() == 0 || row < 1 || col < 1 || target == nullptr)
        return false;

    //这样写失败
    //bool(*visit)[col] = new bool[row][col];

    bool** visit = new bool* [row];
    for (int i = 0; i < row; i++)
    {
        visit[i] = new bool[col];
    }

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            visit[i][j] = false;

    int index = 0;

    //路径可以从矩阵的任意一格开始
    for(int r=0;r<row;r++)
        for (int c = 0; c < col; c++)
        {
            if (hasPathCore(matrix, row, col, r, c, target, index, visit))
                return true;
            else
                visit[r][c] == false;//取消已访问的标记
        }

    for (int i = 0; i < row; i++)      
		delete [] visit[i];

    return false;
}

bool hasPathCore(vector<vector<char>>& matrix, int row, int col, 
    int r, int c, const char* target, int index, bool** visit)
{
    if (target[index] == '\0')
        return true;

    bool flag = false;

    if (r >= 0 && r < row && c >= 0 && c < col &&
        matrix[r][c] == target[index] && !visit[r][c])
    {
        //标记为已访问
        visit[r][c] = true;

        for (int i = 0; i < 4; i++)
        {
            int r1 = r + dx[i];
            int c1 = c + dy[i];

            if (r1 >= 0 && r1 < row && c1 >= 0 && c1 < col)
            {
                flag = hasPathCore(matrix, row, col, r1, c1, target, index + 1, visit);
                
                //必须写如下语句，否则递归回溯后，最后的返回值还是false
                if (flag)
                    return flag;
            }
            else
                continue;

            if (!flag)
                visit[r1][c1] = false;
        }
    }

    return flag;
}
#endif


//面试题13：机器人的运动范围
#if 0
#include <iostream>
#include <vector>
using namespace std;

int movingCount(int threshold, int row, int col);

//***注***
//必须写成是指向visit数组的引用
int movingCountCore(int threshold, int row, int col,int r, int c, vector<vector<bool>>& visit);

bool check(int threshold, int row, int col, int r, int c, vector<vector<bool>>& visit);
bool DigitOK(int threshold, int r, int c);

int main()
{
    cout << movingCount(5,10,10);

    return 0;
}

int movingCount(int threshold, int row, int col)
{
    int count=0;

    if (row < 0 || col < 0 || threshold < 0)
        return count;

    //***注***
	//创建一个行为row，列为col，初始值为false的二维数组
    //方法一：创建并直接初始化
    vector<vector<bool>>visit    (row,vector<bool>(col, false));

    //***注***
    //方法二：用resize来提前构建
    //vector<vector<int>> new_mat(r);//注意这个r是不可缺少的，规定其有多少行
    //for (int i = 0; i < r; i++) //二维vector的初始化时有要求的
    //{
    //    new_mat[i].resize(c);
    //}

	//方法三：每行不一定几个数，就是想对每行的列进行操作
	//	这样也可以，但是在声明时，行数一定要有！！然后push_back就可以了！
	//	vector<vector<int>>mat(r);//每行的定义
	//mat[i].push_back(1);//这就是该第i+1行的插入一个元素，值为1

    count = movingCountCore(threshold,row,col,0,0,visit);

    for (auto x : visit)
    {
        for (auto y : x)
            cout << y;
        cout << endl;
    }

    return count;
}

int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};

int movingCountCore(int threshold, int row, int col, int r, int c, vector<vector<bool>> &visit)
{
    int count = 0;

    if (check(threshold, row, col, r, c, visit))
    {
        visit[r][c] = true;
        //cout << visit[r][c] << endl;
        
//***注***
//由于在递归过程中的入栈退栈行为，导致以下代码得出的数字不正确
//若一定要用此代码块，则要用到全局变量count

 /*       for (int i = 0; i < 4; i++)
        {
            int r1 = r + dx[i];
            int c1 = c + dy[i];

            if (check(threshold, row, col, r1, c1, visit))
            {
                cout << r1<<"，" << c1 <<" " << count << " " << endl;
                count=1+movingCountCore(threshold, row, col, r1, c1, visit);                
                cout << endl;
                cout << r1<<"，" << c1 <<" " << count << " " << endl<<endl;
            }
            else
                continue;
        }
*/

        cout << r << "，" << c << " " << count << " " << endl;
        //这样写能得到正确答案
        count = 1 + movingCountCore(threshold, row, col, r-1, c, visit)
            + movingCountCore(threshold, row, col, r , c-1, visit)
            + movingCountCore(threshold, row, col, r +1, c, visit)
            + movingCountCore(threshold, row, col, r , c+1, visit);
    }

    return count;
}
bool check(int threshold, int row, int col, int r, int c, vector<vector<bool>> &visit)
{
    if (r >= 0 && r < row && c>=0 && c < col && DigitOK(threshold, r, c)&& !visit[r][c])
        return  true;
    else
        return  false;
}
bool DigitOK(int threshold, int r, int c)
{
    int res = 0;

    while (r)
    {
        res += r % 10;
        r /= 10;
    }

    while (c)
    {
        res += c % 10;
        c /= 10;
    }

    return res<=threshold?true:false;
}
#endif


//面试题14：剪绳子
#if 0
#include <iostream>

using namespace std;
int maxProuct(int length);

int main()
{
    int length = 8;

    cout << maxProuct(length);

    return 0;
}

//动态规划解法：
//虽然绳子可以剪若干刀，但每剪一刀后分成的两个部分的长度
//都有其对应的能得到最大乘积数字对应的剪法，
//可以理解成一个问题能分解成多个子问题，每个子问题都存在最优解
#if 0
int maxProuct(int length)
{
    if (length <= 1)
        return 0;
    if (length == 2)
        return 1;
    if (length == 3)
        return 2;

    //创建一个动态数组以存储各个长度的绳子计算出的中间值
    int* product = new int[length + 1] {0};

    //***注***
    //此处product[1]为1，因为其要作为剪完后得到的部分的长度值，
    //而不是作为要对长度为1的绳子分割后可得到的最大乘积值
    //product[2]和product[3]同理
    product[1] = 1;
    product[2] = 2;
    product[3] = 3;

    //绳子的长度
    for (int i = 4; i <= length; i++)
    {
        //创建变量max以存储已计算出的值来用于比较
        int max = 0;

        //创建一个分割点j
        for (int j = 1; j <= i / 2; j++)
        {
           int num = product[j] * product[i-j];

           max = max > num ? max : num;
        }

        product[i] = max;
    }

	//return product[length];

    //for (int i = 0; i <= length; i++)
    //    cout << product[i] << " ";       

    int res = product[length];
    delete []product;

    return res;
}
#endif

//贪心算法
//按照如下的策略来剪绳子，则得到的各段绳子的长度的乘积
//将最大：当n≥5时，我们尽可能多地剪长度为3的绳子；当剩下的绳子
//长度为4时，把绳子剪成两段长度为2的绳子。
#if 0
int maxProuct(int length)
{
    if (length <= 1)
        return 0;
    if (length == 2)
        return 1;
    if (length == 3)
        return 2;

    int time_of_3 = length / 3;

    if (length - time_of_3 * 3 == 1)
    {
        time_of_3 -= 1;
    }

    int time_of_2 = (length - time_of_3 * 3) / 2;

    return (int)(pow(3, time_of_3)) * (int)(pow(2,time_of_2));
}
#endif

#endif


//将十进制数字用字母A~Z表示
#if 0
#include <iostream>
#include <vector>
using namespace std;

vector<char> convert(int num);

int main()
{
    int num = 27;

    vector<char> res = convert(num);

    for (auto i = res.begin(); i != res.end(); i++)
    {
        cout << *i;
    }

    return 0;
}
vector<char> convert(int num)
{
    vector<char> chv;

    while (num)
    {
        chv.push_back(num % 26 - 1 + 'A');
        num /= 26;
    }

    return chv;
}
#endif


//面试题15：二进制中1的个数
#if 0
#include <iostream>
#include <vector>
using namespace std;

int number_of_one(int num);

int main()
{
    int num = 9;
    cout << number_of_one(num);

    return 0;
}

//解法一：将num看成十进制数，用取余的方法转换成二进制
#if 0
int number_of_one(int num)
{
    vector<int> binary;

    int cnt = 0;
    do
    {
        int tmp = num % 2;

        if (tmp == 1)
            cnt++;

        binary.push_back(tmp);
        num /= 2;

    } while (num);

	return cnt;
}
#endif

//解法二：将num看成二进制数，用位运算计算1的个数
#if 0
int number_of_one(int num)
{
    int  cnt = 0;

    while (num)
    {
        if (num & 0x01)
            cnt++;

        num >>= 1;//***注***
    }                      //除法效率比移位运算要低得多，实际编程中要尽量避免使用乘除法，
                           //而是用移位运算来替代
    return cnt;
}
#endif
//瑕疵：若最高位为1，则会陷入死循环

//更完善的解法：
//不对给出的数字本身进行移位运算，而是对flag进行移位，用来判断每位是否为1
#if 0
int number_of_one(int num)
{
    int cnt = 0;

    int flag = 1;

    while (flag)
    {
        if (num & flag)
            cnt++;

         flag<<= 1;
    }

    return cnt;
}
#endif

//技巧性更强的解法：
// ***记***
//把一个整数减去1,再和原整数做与运算，会把该整数最右边的1变成0。
//那么一个整数的二进制表示中有多少个1,就可以进行多少次这样的操作。
#if 1
int number_of_one(int num)
{
    int cnt = 0;

    while (num)
    {
        cnt++;
        num = (num - 1) & num;
    }

    return cnt;
}
#endif
#endif


//一个二进制数要改变多少位才能得到另一个二进制数
#if 0
#include<iostream>

using namespace std;

int need_change(int num1,int num2);
int number_of_one(int num);

int main()
{
    int num1 = 10;
    int num2 = 13;

    cout << need_change(num1,num2);

    return 0;
}
//不使用for循环，而使用异或运算，然后统计数中的1的个数
int need_change(int num1, int num2)
{
    int tmp = num1 ^ num2;

    return number_of_one(tmp);
}
int number_of_one(int num)
{
    int cnt = 0;

    while (num)
    {
        cnt++;
        num = (num - 1) & num;
    }

    return cnt;
}
#endif


//用栈实现二叉树的深度优先遍历
#if 0
#include <iostream>
#include<stack>
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

//前序遍历——递归
void preorder(BinaryTreeNode * rootNode)
{
    if (!rootNode)
        return;

    //根->左->右
    std::cout << rootNode->m_nValue << " ";
    preorder(rootNode->m_pLeft);
    preorder(rootNode->m_pRight);
}

//前序遍历——使用栈
void preorder2(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* tempNode = rootNode;

    while (!nodeStack.empty() || tempNode)
    {
        if (tempNode)
        {
            std::cout << tempNode->m_nValue << " ";
            nodeStack.push(tempNode);
            tempNode = tempNode->m_pLeft;//根->左
        }
        else 
        {
            tempNode = nodeStack.top();
            nodeStack.pop();
            tempNode = tempNode->m_pRight;//右
        }
    }
}

//中序遍历——递归
void inorder(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;
    //左->根->右	
    inorder(rootNode->m_pLeft);
    std::cout << rootNode->m_nValue << " ";
    inorder(rootNode->m_pRight);
}

//中序遍历 --栈
template<typename T>
void inorder2(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* tempNode = rootNode;

    while (!nodeStack.empty() || tempNode)
    {
        if (tempNode) {
            nodeStack.push(tempNode);
            tempNode = tempNode->m_pLeft;//左
        }
        else {
            tempNode = nodeStack.top();
            nodeStack.pop();
            std::cout << tempNode->m_nValue << " ";
            tempNode = tempNode->m_pRight;//根->右
        }
    }
}

//后序遍历——递归
void postorder(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;
    //左->右->根	
    postorder(rootNode->m_pLeft);
    postorder(rootNode->m_pRight);
    std::cout << rootNode->m_nValue << " ";
}

//后序遍历——栈
void postorder2(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* curNode = rootNode; //当前节点
    BinaryTreeNode* preNode = nullptr; //之前访问过的节点，用来存

    //把cur移动到左子树最下边
    while (curNode)
    {
        nodeStack.push(curNode);
        curNode = curNode->m_pLeft;
    }

    while (!nodeStack.empty())
    {
        //走到这里，cur空，并已经遍历到左子树底端
        curNode = nodeStack.top();
        nodeStack.pop();

        //无右或右已访问才访问根节点
        if (!curNode->m_pRight || curNode->m_pRight == preNode)
        {
            std::cout << curNode->m_nValue << " ";
            preNode = curNode;
        }
        //右子树未访问
        else {
            //根节点再次入栈
            nodeStack.push(curNode);
            //进入右子树
            curNode = curNode->m_pRight;
            //把cur移动到右子树的左子树最下边
            while (curNode)
            {
                nodeStack.push(curNode);
                curNode = curNode->m_pLeft;
            }
        }
    }
}
//————————————————
//版权声明：本文为CSDN博主「龚建波」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/gongjianbo1992/article/details/88378805
#endif


//用链表实现二叉树的广度优先遍历(层序遍历)
#if 0
#include <iostream>
#include<queue>
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

void breadthFirst(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    nodeQueue.push(rootNode);

    while (!nodeQueue.empty())
    {
        tempNode = nodeQueue.front();
        std::cout << tempNode->m_nValue << " ";

        nodeQueue.pop();

        if (tempNode->m_pLeft)
            nodeQueue.push(tempNode->m_pLeft);
        if (tempNode->m_pRight)
            nodeQueue.push(tempNode->m_pRight);
    }
}
#endif


//***注***
//代码的规范性：书写清晰、布局清晰、命名合理
//代码的完整性：功能测试、边界测试、错误处理
//代码的鲁棒性：采取防御性编程处理无效的输入


//面试题16：数值的整数次方
#if 0
#include <iostream>
#include <exception>
using namespace std;

double Power(double base,int exponent);

bool g_InvalidInput = false;
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

int main()
{
    cout << Power(0, 0) << endl;
	//cout << Power(0, -1) << endl;
    cout << Power(2,3)<<endl;
    cout << Power(-1,3)<<endl;
    cout << Power(-1.1,3)<<endl;

    cout << Power(-1, -2) << endl;;
    cout << Power(-2, -2) << endl;;

    return 0;
}

#if 0
double Power(double base, int exponent)
{
    if (base == 0 && exponent == 0)
        return 1;

    if (base == 0 && exponent < 0)
        throw new exception("Error!");

    double res = base;
	int i = exponent;
	while (i >= 2)
	{
		res *= base;

		--i;
	}

    return res;
}
#endif
//瑕疵：没有考虑指数是负数的情况
//指数还可能是负数
#if 0
double Power(double base, int exponent)
{
    if (base == 0 && exponent == 0)
        return 1;

    if (base == 0 && exponent < 0)
        throw new exception("Error!");

    double res = base;
    int i = exponent;
    while (i >= 2)
    {
        res *= base;

        --i;
    }

    if (i < 0)
    {
        i = -i;
    
        while (i >= 2)
        {
            res *= base;

            --i;
        }

        res = 1.0 / res;
    }

    return res;
}
#endif

bool equal(double num1, double num2)
{
    if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
        return true;
    else
        return false;
}

//求数的n次方的效率更高的解法：
double Power(double base, int exponent)
{
    g_InvalidInput = false;

    if (equal(base, 0.0) && exponent < 0)
    {
        g_InvalidInput = true;
        return 0.0;
    }

    unsigned int absExponent = (unsigned int)(exponent);
    if (exponent < 0)
        absExponent = (unsigned int)(-exponent);

    double result = PowerWithUnsignedExponent(base, absExponent);

    if (exponent < 0)
        result = 1.0 / result;

    return result;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent == 1)
        return base;

    //n为偶数时，a的n次方等于a的n/2次方乘以a的n/2次方
    //n为奇数时，a的n次方等于a的n/2次方乘以a的n/2次方乘以a
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;

    if ((exponent & 0x1) == 1)
        result *= base;

    return result;
}
//优化代码的细节：
//1.使用了公式求a的n次方，比仅用循环求要少2倍时间
//2.用移位运算代替乘除运算
//3.用位与运算代替求余运算来判断数的奇偶性
#endif


//面试题17：打印从1到最大的n位数
#if 0
#include <iostream>
#include <exception>
#include <algorithm>
using namespace std;

void Paint_1_to_n(long  long n);

bool Increment(char* number);
void PrintNumber(char* number);

void Recursively(char* number, int length, int index);

int main()
{
    long long n;
    cin >> n;

    Paint_1_to_n(n);

    return 0;
}

//没有考虑大数问题
//即当输入的n很大的时候，我们求最大的n位数时，
//用整型(int)或者长整型(long long)都会溢出
#if 0
void Paint_1_to_n(long  long n)
{
    if (n<1)
        throw new exception("Invaild data !");

    long long nmax=1;
    while (n>=1)
    {
        nmax *= 10;
        --n;
    }

    for (long long i = 1; i < nmax; i++)
        printf("%lld ",i);

    return;
}
#endif

//解法1：
//利用字符串的模拟加法
#if 0
void Paint_1_to_n(long  long n)
{
    if (n < 1)
        throw new exception("Invaild data !");

    //创建number字符数组来存储数字字符   

    //***注***
    //以下写法会将第一个元素设置为字符0，而其余元素设置为ASCII值0，即对应字符'\0'
    //char* number = new char[n + 1]{'0'};

    char* number = new char[n + 1];
    fill(number, number + n + 1,'0');

    //for (int i = 0; i < n; i++)
    //    cout << number[i];

    //数字的最低位的后一位的元素内容为0
    //就可以正常用strlen()计算字符串长度
    number[n] = '\0';

    while (!Increment(number))
    {
        PrintNumber(number);
    }

    delete[]number;
}

bool Increment(char* number)
{
    //创建溢出位标志
    bool isOverflow = false;

    //存进位值
    int nTake = 0;

    int Length = strlen(number);

    //数字字符的索引从最低位开始，向高位移动
    for (int i = Length - 1; i >= 0; i--)
    {
        //创建变量Sum存该位当前的值
        int Sum = number[i] - '0' + nTake;

        //若索引指向数字的最低位
        if (i == Length - 1)
            Sum++;

        //若该位上的值再增1后，到10，则要进行处理
        if (Sum >= 10)
        {
            //若该位是最高位
			//***注***
		    //这种判断方法时间效率好，为O(1)
            //若用strcmp()判断，时间效率为O(n)
            if (i == 0)
                isOverflow = true;
            else
            {
                //Sum到10时，该位要变为0
                Sum -= 10;
                //向前进1位
                nTake = 1;
                //设置该位上的值
                number[i] = Sum + '0';
            }
        }
        else
        {
            number[i] = Sum + '0';
            //退出循环
            break;
        }
    }

    return isOverflow;
}
void PrintNumber(char* number)
{
    int Length = strlen(number);

    //数字开头非0的标记
    bool flag=false;

    //遍历数字字符数组
    for (int i = 0; i < Length; i++)
    {
        //***注***
        //若写成这样：
        //  if (number[i] == '0' && !flag)
        //则数字若为010，则打印不出10         
        
        //数字仅满足开头至少有一个是非0时，才打印
        if (number[i] != '0' && !flag)
            flag = true;

        if (flag)
            printf("%c",number[i]);
    }

    printf("\t");
}
#endif

//解法2：
//将问题转化成数字的全排列，并用递归实现全排列
#if 1
void Paint_1_to_n(long  long n)
{
    if (n < 1)
        throw new exception("Invaild data !");

    //创建number字符数组来存储数字字符   
    char* number = new char[n + 1];

    //fill(number, number + n + 1, '0');

    //数字的最低位的后一位的元素内容为0
    //就可以正常用strlen()计算字符串长度
    number[n] = '\0';

    for (int i = 0; i < 10; ++i)
    {
        //数字最高位从0到9遍历
        number[0] = i + '0';
                                //数字长度，索引值
        Recursively(number,n,0);
    }

    delete[]number;
}

void Recursively(char* number, int length, int index)
{
    if (index == length - 1)
    {
        PrintNumber(number);
        return;
    }

    //数字除最高位之外的位均从0开始递增到9
    for (int i = 0; i < 10; ++i)
    {
        number[index + 1] = i + '0';

        Recursively(number,length,index+1);
    }
}

void PrintNumber(char* number)
{
    int Length = strlen(number);

    //数字开头非0的标记
    bool flag = false;

    //遍历数字字符数组
    for (int i = 0; i < Length; i++)
    {
        //***注***
        //若写成这样：
        //  if (number[i] == '0' && !flag)
        //则数字若为010，则打印不出10         

        //数字仅满足开头至少有一个是非0时，才打印
        if (number[i] != '0' && !flag)
            flag = true;

        if (flag)
            printf("%c", number[i]);
    }

    printf("\t");
}
#endif
#endif


//面试题18：删除链表的节点
#if 0
#include <iostream>
#include <exception>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted);

int main()
{

    return 0;
}

//***注***
//寻找链表中符合要求的节点，时间效率O(n)，这是不变的
//现在要优化的是已经找到该符合要求的节点的地址，要在O(1)内进行删除操作
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (pListHead == nullptr || pToBeDeleted == nullptr)
        throw new exception("Error !");

    //由于链表的节点不含前一个节点的指针，所以
    //常规的方法是顺序遍历每个节点，找到要删除的节点后
    //先对其前一个节点的m_pNext指针进行设置
    //但时间复杂度为O(n)，因为要遍历到要删除的节点的前一个节点

    //可以不遍历，而是将要删除的节点的下一个节点的内容都
    //赋值给要删除的节点。相当于删除了该节点。
    //这种方法不用释放要删除的节点的内存空间

    //若要删除的节点是    非仅一个节点的链表也    非链表的尾节点
    if (pToBeDeleted->m_pNext != nullptr)
    {
        //tmp指向要删除的节点的下一个节点
        ListNode* tmp = pToBeDeleted->m_pNext;

        //下一个节点的内容赋给要删除的节点
        pToBeDeleted->m_nValue = tmp->m_nValue;
        //下一个节点的指向其再下一个节点的指针的值赋给要删除的节点的m_pNext成员
        pToBeDeleted->m_pNext = tmp->m_pNext;

        //删除要删除的节点的下一个节点
        delete tmp;

        //***注***
        //要附加下一句话
        //因为上一句只是释放了tmp指针所指向的内存空间，而
        //tmp就会成为野指针
        //“野指针”不是 NULL 指针，是指向“垃圾”内存的指针。
        tmp = nullptr;
    }
    else if (pToBeDeleted->m_pNext==nullptr)//若要删除的是仅一个节点的链表
    {
        delete pToBeDeleted;

        pToBeDeleted = nullptr;

        *pListHead = nullptr;
    }
    else//若要删除的是尾节点
    {
        //只能用遍历的方法
        ListNode* tmp = *pListHead;

        while (tmp)
        {
            if ((tmp)->m_pNext == pToBeDeleted)
            {
                tmp->m_pNext = nullptr;

                delete pToBeDeleted;
                pToBeDeleted = nullptr;

                break;
            }

            tmp = tmp->m_pNext;
        }
    }

    return;
}
#endif


//删除链表中重复的节点
#if 0
#include <iostream>
#include <exception>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

//***注***
//这个函数需要输入待删除链表的头节点。
//头节点可能与后面的节点重复，也就是说头节点也可能被删除，
//因此删除函数应该声明为void deleteDuplication(ListNode * *pHead), 
//而不是void deleteDuplication(ListNode* pHead)。
void DeleteDuplication(ListNode** pHead)
{
    //若指向头指针的指针内容为nullptr或头指针内容为nullptr(没有节点)
    if (pHead == nullptr || *pHead == nullptr)
        return;

    //创建一个指向当前节点的前一个节点的指针
    ListNode* pPreNode = nullptr;
    //创建一个指向当前节点的指针
    ListNode* pNode = *pHead;

    while (pNode != nullptr)
    {
        //创建一个指向当前节点的后一个节点的指针
        ListNode* pNextNode = pNode->m_pNext;

        //创建一个标记，表明节点是否该删除
        bool needDelete = false;

        //若当前节点有后一个节点且其后一个节点的内容与当前节点内容相同
        if (pNextNode != nullptr && pNextNode->m_nValue == pNode->m_nValue)
            needDelete = true;//标记此节点该删除

        //若当前节点的后一个节点内容与当前节点的内容不同
        if (!needDelete)
        {
            //当前节点的前一个节点的指针设置为当前节点的地址
            pPreNode = pNode;
            pNode = pNode->m_pNext;//当前节点的指针向后移动一个节点的位置
        }
        else//若当前节点有后一个节点且其后一个节点的内容与当前节点内容相同
        {
            int value = pNode->m_nValue;

            //创建一个指向应该删除的节点的指针pToBeDeleted，其被初始化为当前节点的地址
            ListNode* pToBeDeleted = pNode;

            //若pToBeDeleted不为无效内容且pToBeDeleted指向的节点的内容
            //与当前指针指向的节点的内容相同
            while (pToBeDeleted != nullptr && pToBeDeleted->m_nValue == value)
            {
                //pNextNode指向当前节点的后一个节点
                pNextNode = pToBeDeleted->m_pNext;

                //释放当前节点所指向的内存空间
                delete pToBeDeleted;
                pToBeDeleted = nullptr;

                //pToBeDeleted存当前节点的后一个节点，这样的话，当前节点的后一个节点
                //也会被删除
                pToBeDeleted = pNextNode;
            }

            //下面要处理被删除的节点的前一个节点的m_pNext数据成员，使这个节点
            //最终存pNextNode指向的节点的地址，完成链表的重连

            //若从第一个节点开始，要删除若干个节点
            if (pPreNode == nullptr)
                *pHead = pNextNode;
            else//若不是从第一个节点开始删除
                pPreNode->m_pNext = pNextNode;

            //当前节点指向链表中重复的数个节点后的一个节点
            pNode = pNextNode;
        }
    }
}
#endif


//面试题19：正则表达式匹配
#if 0
#include <iostream>

using namespace std;

                //字符串         模式，即正则表达式
bool match(char* str, char* pattern);
bool matchCore(char* str, char* pattern);

int main()
{


    return 0;
}

/*
bool match(char* str, char* pattern)
{
    if (str == nullptr || pattern == nullptr)
        return false;

    if (*str == '\0' || *pattern == '\0')
        return true;

    if (str[0] == pattern[0])
    {
        if (pattern[1] == '*')
        {
            match(str+1,pattern+2);
        }
        else if(pattern[1]=='.')
        {
            match(str+);
        }
    }
}
*/

bool match(char* str, char* pattern)
{
    if (str == nullptr || pattern == nullptr)
        return false;

    return matchCore(str,pattern);
}

//假设字符串为aaa
bool matchCore(char* str, char* pattern)
{
    //若字符串与正则表达式都遍历到了最后
    if (*str == '\0' && *pattern == '\0')
        return true;

    //若正则表达式先遍历到了最后
    if (*str != '\0' && *pattern == '\0')
        return false;

    //情况分为正则表达式pattern指针指向的位置后的第1个字符是'*'和不是'*'
    if (pattern[1] == '*')
    {        
		//if (str[0] == pattern[0] || (pattern[0] == '.' && str[0] != '\0'))

        //若当前两指针指向的字符相同  或  正则表达式字符为'.'且字符串未遍历到末尾
        if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        {
            //测试字符串该位置后的第1个字符和正则表达式该位置后的第2个字符
            return matchCore(str + 1, pattern + 2) ||
                //测试字符串该位置后的第1个字符和正则表达式该位置的字符
                matchCore(str + 1, pattern) ||//因为正则表达式可能是a*
                //测试字符串该位置的字符和正则表达式该位置后的第2个字符
                matchCore(str, pattern + 2)//因为正则表达式可能是a*a*
                ;
        }
        else
            //测试字符串该位置的字符和正则表达式该位置后的第2个字符
            return matchCore(str,pattern+2);//因为正则表达式可能是b*a*
    }

    //正则表达式pattern指针指向的位置后的第1个字符不是'*'
    if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str+1,pattern+1);
}
#endif


//面试题20：表示数值的字符串
#if 0
#include <iostream>
//#include <string>
using namespace std;

bool isNum(const char* str);
bool scanInteger(const char** str);
bool scanUnsignedInteger(const char** str);

int main()
{
    char data[20] = { '\0' };
    cin.getline(data,20);

    //if(stoi(str))

    cout << isNum(data);

    //const int** pp;
    //int* p = 0x0;
    //pp = &p;

    return 0;
}

//有许多情况，如何分类？
//由于情况很多，所以不能直接用一个循环遍历来草草判断
//要找到规律：
//小数点后者e或E前后的数字可以用遍历扫描解决，
//小数点后的或者e或E后的数字部分也要用遍历扫描的话，
//那可以将遍历扫描设计成一个模块
bool isNum(const char* str)
{
    if (str == nullptr)
        return false;

    //数字的开头有可能出现正负号，因此要进行处理，
    //若有正负号，则要将指针向后移动一位的距离，
    //继续判断无符号的部分
    bool flag = scanInteger(&str);

    //经过如上的代码段，str指针已经指向了小数点或e或E
    //但若输入数字.123，则前面代码的flag=false;
    if (*str == '.')
    {
        ++str;

        //要照顾到多种情况，比如
        //  .123     123. 
        flag = scanInteger(&str) || flag;

    }

    if (*str == 'e' || *str == 'E')
    {
        ++str;

        //***注***
        //此处用与，因为不能接受   .e1   
        flag = scanInteger(&str) && flag;
    }

    //不能接受10e+5.4
    return flag && *str == '\0';
}

bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-')
        ++(*str);//***注***
    //此处str声明为const，即不能改变str指向的内容，而str指针是可以改变的
    //即不能出现**str = 0x00;即指向数字字符串的指针所存储的位置不能变
    //而指向数字字符串的指针存储的内容可以变。    
    //即指针可以指向下一个字符

    return scanUnsignedInteger(str);
}

//该函数用来扫描字符串中0~9的数位
bool scanUnsignedInteger(const char** str)
{
    //创建before指针指向扫描时一开始的字符
    const char* before = *str;

    while (**str != '\0' && **str >= '0' && **str <= '9')
    {
        ++(*str);
    }

    //若指向字符串的指针后移了，那么字符串中确实存在0~9的字符，
    //可以继续进行下面的判断
    return *str > before;
}
#endif


//面试题21：调整数组顺序使奇数位于偶数前面
#if 0
#include <iostream>

using namespace std;

//void Reorder(int* pData, int length);

void Swap(int* a, int* b);

void Reorder(int* pData, int length, bool (*pfun)(int n));
bool isEven(int n);

int main()
{
    int length;
    cin >> length;
    cin.get();

    int* data = new int[length] {0};
    int index = 0;
    int num;

    //***注***
    //错误写法：
    //cin.get()读取的是字符，而且
    //把数字之间的用于分割的空格也视为输入了
    //while (index<length&&(( num=cin.get() )!= '\n'))
    //{        
    //    data[index++] = num - '0';
    //}

    while (index < length)
    {
        if (!(cin >> num))
        {
            cin.clear();

            while (cin.get() != '\n')
                continue;

            continue;
        }

        data[index++] = num;
    }

    Reorder(data, length,isEven);

    for (int i = 0; i < length; ++i)
    {
        cout << data[i]<<"\t";
    }

    delete[]data;

    return 0;
}

#if 0
void Reorder(int* pData, int length)
{
    if (pData == nullptr || length <= 0)
        return;

    int p1, p2;
    p1 = 0, p2 = length - 1;

    //输入1，2，3，4，5
    while (p1 < p2)
    {
        //若p1指向的是奇数
        if (pData[p1] & 0x01)
            ++p1;
        else if (!(pData[p1] & 0x01) && pData[p2] & 0x01)//一偶，一奇
        {
            Swap(&pData[p1], &pData[p2]);
            ++p1, --p2;
        }
        else//一偶，一偶
            --p2;

        //一奇，一奇
        //整合到情况一

        //一奇，一偶
        //整合到情况一
    }
}

void Swap(int* a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}
#endif

//法二：
#if 0
void Reorder(int* pData, int length)
{
	if (pData == nullptr || length == 0)
		return;

	int* pBegin = pData;
	int* pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		// 向后移动pBegin，直到它指向偶数
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)
			pBegin++;

		// 向前移动pEnd，直到它指向奇数
		while (pBegin < pEnd && (*pEnd & 0x1) == 0)
			pEnd--;

		if (pBegin < pEnd)
		{
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}
#endif

//***注***
//将单一函数进行解耦，将该函数的职责进行分离。
//可以提高代码的重用性，利于功能的扩展
void Reorder(int* pData, int length, bool (*pfun)(int n))
{
    if (pData == nullptr || length == 0)
        return;

    int* pBegin = pData;
    int* pEnd = pData + length - 1;

    while (pBegin < pEnd)
    {
        // 向后移动pBegin，直到它指向偶数
        while (pBegin < pEnd && (*pfun)(*pBegin))
            pBegin++;

        // 向前移动pEnd，直到它指向奇数
        while (pBegin < pEnd && !pfun(*pEnd))
            pEnd--;

        if (pBegin < pEnd)
        {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}
bool isEven(int n)
{
    return n & 0x01;
}
#endif


//***注***
//提高代码的鲁棒性的有效途径是进行防御性编程
//防御性编程是一种编程习惯，是指预见在什么地方可能会出现问题，
//并为这些可能出现的问题制定处理方式。


//面试题22：链表中倒数第k个节点
#if 0
#include <iostream>
#include <exception>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* FindNode(ListNode* pListHead, unsigned int k);

int main()
{


    return 0;
}

//一般能想到的是遍历链表两次，一次遍历得到链表总节点数n
//一次遍历得到从头开始的第n-k+1个节点(相当于是倒数第k个节点)

//想到每次遍历时前进一个节点都用指针去指向
//但这样也是提前需要开辟一个大内存空间去存指针的

//能不能用两个指针去完成这件事？
//因为链表总是要遍历到最后的一个节点的
//而最后一个节点可以做为开始计数的节点，那就用指针1去指向
//而指针2始终将与指针1相隔k-1个节点的距离(注意链表的内存的内存空间不连续！！！)

//相当于两个指针形成一段固定距离的区域    (尺取法)
//指针1从头结点开始走，走k-1个节点的距离后，指针2开始与指针1一起走
//直到指针1到达尾节点，则指针2指向的结点就是要求的倒数第k个节点
ListNode* FindNode(ListNode** pListHead, int k)
{
    if (pListHead == nullptr || k <= 0||*pListHead==nullptr)
        throw new exception("Invaild data !");

    ListNode* p1 = *pListHead;
    ListNode* p2 = *pListHead;

    //p1先走k-1个节点
    for (int i = 1; i < k; ++i)  //***注***
    {                                      //有符号与无符号数字做算数运算时会隐式转换成无符号数字
        p1 = p1->m_pNext;   //结果也是解释成无符号数字

        if(p1==nullptr)
            throw new exception("Invaild data !");//注意代码的鲁棒性
    }

    while (p1->m_pNext != nullptr)
    {
        p2 = p2->m_pNext;
        p1 = p1->m_pNext;
    }

    return p2;
}
#endif


//求链表的中间节点
//解法：
//定义两个指针，一个指针一次走一步，另一个指针一次走两步。
//当走得快的指针走到链表的末尾时，走得慢的指针正好在链表的中间。


//面试题23：链表中环的入口节点
//***注***
//需要分三步走
#if 0
#include <iostream>
#include <exception>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* MeetingNode(ListNode* pHead);
ListNode* EntryNodeOfLoop(ListNode* pHead);

int main()
{


    return 0;
}

//先找到环中的任意一个节点
ListNode* MeetingNode(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* pSlow = pHead;
    ListNode* pFast = pHead->m_pNext;

    if (pFast == nullptr)
        return nullptr;

    while (pSlow!=pFast)
    {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;

        /*if (pSlow == nullptr)
            return nullptr;*/
        if (pFast == nullptr)
            return nullptr;
    }

    return pSlow;
}

//找到环中的任意一个节点后，得出环中节点的数目
//进而找到环的入口节点
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* meetingNode = MeetingNode(pHead);

    if (meetingNode == nullptr)
        return nullptr;

    int cnt = 1;
    ListNode* tmp = meetingNode->m_pNext;

    //计算出环中节点的个数
    while (tmp != meetingNode)
    {
        ++cnt;
        tmp = tmp->m_pNext;
    }

    //***注***
    //再找到环的入口节点
    //方法：
    //创建两个指针，一个指针先移动环中节点的数目个节点，
    //然后另一个指针再同第一个指针一起移动
    //它们相遇后的节点就是环的入口节点

    ListNode* p1 = pHead;
    ListNode* p2 = pHead;

    while (cnt--)
        p1 = p1->m_pNext;

    while (p1 != p2)
    {
        p1 = p1->m_pNext;
        p2 = p2->m_pNext;
    }

    return p1;
}
#endif


//面试题24：反转链表
#if 0
#include <iostream>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead);

int main()
{
    ListNode* p = new ListNode;
    p->m_nValue = 1;

    ListNode* p1 = new ListNode;
    p1->m_nValue = 2;
    p1->m_pNext = nullptr;

    p->m_pNext = p1;

    ListNode* p2 = new ListNode;
    p2->m_nValue = 3;
    p2->m_pNext = nullptr;

    p1->m_pNext = p2;

    ListNode* res=ReverseList(p);

    cout << res->m_nValue << " " << res->m_pNext->m_nValue 
        <<" "<<res->m_pNext->m_pNext->m_nValue << endl;

    return 0;
}

#if 0
//***注***
//思考
//假如有节点 i ->  j -> k
//则操作后变成  i <- j <- k
//则在操作节点 i 和 j 时需要有临时指针去保存原本j指向的下一个节点k的地址
ListNode* ReverseList(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* i = pHead;
    ListNode* j = i->m_pNext;

    //整个链表仅有1个节点
    if (j == nullptr)
        return pHead;
        
    ListNode* tmp = j->m_pNext;
    //整个链表仅有2个节点
    if (tmp == nullptr)
    {
        j->m_pNext = i;
        i->m_pNext = nullptr;

        return j;
    }

    //整个链表有3个及以上个节点
    //情况：
    //i <- j <- k -> L
    //i <- j <- k <- L

    ListNode* tmp1;

    while (tmp != nullptr)
    {
        //趁指向没变时存指向的下一个节点存储的位置
        tmp1=tmp->m_pNext;
        //然后再改变指向
        tmp->m_pNext = j;

        j->m_pNext = i;

        if (i == pHead)
        {
            i->m_pNext = nullptr;
            i = j;//  i 前进
        }
        else
            i = j;

        j = tmp;//  j 前进

        tmp = tmp1;//tmp前进
    }

    return j;
}
#endif

#if 1
ListNode* ReverseList(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;

    while (pNode != nullptr)
    {
        ListNode* pNext = pNode->m_pNext;

        //若到达链表末尾的节点
        if (pNext == nullptr)
            pReversedHead = pNode;

        //指针指向改变
        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }

}
#endif
#endif


//浮点数之间如何判断相等
#if 0
#include <iostream>
#include <cmath>
using namespace std;

void fun(double* a, double* b)
{

}

int main()
{
    double i, j;
    i = 1.1, j = 1.2;

    fun(&i,&j);

    //***注****
    //错误写法：
    if (i == j)
    {

    }

    //错误原因：
    //浮点数经过很多次运算后，你认为他俩相等，
    //但计算机因为误差的原因，可能会造成两个数字不相等
    //比如：
    // a = 1.1     b = 1.1
    //但计算机中实际二进制表示的可能是1.09999999和1.1000000001


    //正确方法1：
    if(abs(i - j) < 0.000001)

    //正确方法2：化为整数法
    //运算前现将两个数字进行扩大
    //最后输出时才将结果缩小

    return 0;
}
#endif


//面试题25：合并两个排序的链表
#if 0
#include "List.h"
#include <iostream>

using namespace std;

ListNode* Merge(ListNode* pHead1, ListNode* pHead2);

int main()
{
    // list1: 1->3->5
    // list2: 2->4
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode3);
    ConnectListNodes(pNode3, pNode5);

    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode4 = CreateListNode(4);
    //ListNode* pNode6 = CreateListNode(6);

    ConnectListNodes(pNode2, pNode4);
    //ConnectListNodes(pNode4, pNode6);

    ListNode* pMergedHead = Merge(pNode1, pNode2);

    PrintList(pMergedHead);

    DestroyList(pMergedHead);

    return 0;
}

//解法一：
//合并时是以其中一个链表为基础，进行合并
#if 0
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;

    ListNode* pNode1, *pNode2;

    pNode1 = pHead1;
    pNode2 = pHead2;

    ListNode* tmp1,*tmp2;

    bool OnlyOne = true;
    ListNode* Begin = nullptr;

    while (pNode1 != nullptr && pNode2 != nullptr)
    {
        if (pNode1->m_nValue <= pNode2->m_nValue)
        {
            //解决以下情况：
            //若链表一为 1 2 5 7
            //   链表二为 3 4 6 8
            while (pNode1->m_pNext!=nullptr&&pNode1->m_pNext-> m_nValue <= pNode2->m_nValue)
            {
                pNode1 = pNode1->m_pNext;
            }

            //考虑头结点是哪个链表的头结点
            if (OnlyOne)
            {
                Begin = pNode1;
                OnlyOne = false;
            }

            tmp1 = pNode1->m_pNext;

            pNode1->m_pNext = pNode2;

            tmp2 = pNode2->m_pNext;

            pNode2->m_pNext = tmp1;

            pNode1 = tmp1;
            pNode2 = tmp2;

        }
        else
        {
            //解决以下情况：
            //若链表一为 3 4 6 8
            //   链表二为 1 2 5 7
            while (pNode2->m_pNext!=nullptr&&pNode2->m_pNext->m_nValue <= pNode1->m_nValue)
            {
                pNode2 = pNode2->m_pNext;
            }

            //考虑头结点是哪个链表的头结点
            if (OnlyOne)
            {
                Begin = pNode2;
                OnlyOne = false;
            }

            tmp2 = pNode2->m_pNext;

            pNode2->m_pNext = pNode1;

            tmp1 = pNode1->m_pNext;

            pNode1->m_pNext = tmp2;                        

            pNode1 = tmp1;
            pNode2 = tmp2;
        }
    }

    return Begin;
}
#endif

//解法二：
//利用递归，单独生成一个合并后的链表
//好处：
//可以避免节点之间断连后再连上的复杂指针操作问题
//不必考虑以下问题
//若链表一为 3 4 6 8
//   链表二为 1 2 5 7
//优化了时间复杂度
#if 1
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    //***注***
    //处理两个链表长度不一致的问题
    if (pHead1 == nullptr)
        return pHead2;

    if (pHead2 == nullptr)
        return pHead1;

    //创建一个节点，并由pMergedHead指针指向
    ListNode* pMergedHead = nullptr;

    if (pHead1->m_nValue < pHead2->m_nValue)
    {
        pMergedHead = pHead1;
        pMergedHead->m_pNext = Merge(pHead1->m_pNext,pHead2);
    }
    else
    {
        pMergedHead = pHead2;
        pMergedHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
    }

    return pMergedHead;
}
#endif
#endif


//面试题26：树的子结构
//思路：
//需要对一颗树进行遍历
//需要在树A中找到和树B的根节点值一样的节点后，继续判断两者的子树结构和内容是否相等
#if 0
#include <iostream>
#include <cmath>
#include "Tree.h"
using namespace std;

bool HasSubtree(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2);
bool Equal(double a,double b);

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
    ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
    ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

    BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);

    ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
    ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

    cout<<HasSubtree(pNodeA1,pNodeB1);

    DestroyTree(pNodeA1);
    DestroyTree(pNodeB1);

    return 0;
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    //用递归的方式去遍历树
    bool res = false;

    if (pRoot1 != nullptr && pRoot2 != nullptr)
    {
        //***注***
        //错误写法：
        //if(pRoot1->m_dbValue==pRoot2->m_dbValue)
        //错误原因：
        //计算机表示小数都有误差，不能直接用等号去判断两个小数是否相等

        //正确写法：
        if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
            res = DoesTree1HaveTree2(pRoot1,pRoot2);

        if (!res)
            res = HasSubtree(pRoot1->m_pLeft,pRoot2);

        if (!res)
            res = HasSubtree(pRoot1->m_pRight,pRoot2);
    }

    return res;
}

bool Equal(double a, double b)
{
    return abs(a - b) < 0.0000001;
}

//在根节点确定值相同的前期下，继续
//递归判断两棵子树结构与其他元素是否相同
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    //树2已经遍历完了
    if (pRoot2==nullptr)
        return true;

    //树1已经遍历完了
    if (pRoot1 == nullptr)
        return false;

    //错误写法：
    //if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
    //    return true;
    //else
    //    return false;

    //正确写法：
    if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
        return false;

    //原因：若写成错误写法，那么只要两个根节点相同，则直接返回true，
    //不会再进行后续的判断

    bool flag = false;

    flag = DoesTree1HaveTree2(pRoot1->m_pLeft,pRoot2->m_pLeft);
    if(flag)
	flag = DoesTree1HaveTree2(pRoot1->m_pRight, pRoot1->m_pRight);

    return flag;
}
#endif


//面试题27：二叉树的镜像
//难点：
//满二叉树似乎可以通过层序遍历进行节点的值之间的交换？
//思路错误了。
//值的交换可以不是用单单赋值的方式来操作，而是用交换左右子树的方式
//实现值的交换
//遍历方式可以用前序遍历
#if 0
#include <iostream>
#include "Tree.h"
#include <queue>
#include <stack>
using namespace std;

void breadthFirst(BinaryTreeNode* rootNode);
void Mirror(BinaryTreeNode* rootNode);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);


    breadthFirst(pNodeA1);
    cout << endl;
    Mirror(pNodeA1);
    breadthFirst(pNodeA1);

    DestroyTree(pNodeA1);

    return 0;
}
void breadthFirst(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    nodeQueue.push(rootNode);

    while (!nodeQueue.empty())
    {
        tempNode = nodeQueue.front();
        std::cout << tempNode->m_dbValue << " ";

        nodeQueue.pop();

        if (tempNode->m_pLeft)
            nodeQueue.push(tempNode->m_pLeft);
        if (tempNode->m_pRight)
            nodeQueue.push(tempNode->m_pRight);
    }
}
#if 0
void Mirror(BinaryTreeNode* rootNode)
{
    if (rootNode == nullptr)
        return;

    //若扫描到叶子节点，则不用做后续的子节点交换
    if (rootNode->m_pLeft == nullptr && rootNode->m_pRight == nullptr)
        return;

    //交换当前节点下的左右节点
    BinaryTreeNode* tmp = rootNode->m_pLeft;

    rootNode->m_pLeft = rootNode->m_pRight;
    rootNode->m_pRight = tmp;

    Mirror(rootNode->m_pLeft);
    Mirror(rootNode->m_pRight);
}
#endif

//用循环来实现
#if 1
void Mirror(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* tempNode = rootNode;

    while (!nodeStack.empty() || tempNode)
    {
        if (tempNode)
        {
            //std::cout << tempNode->m_dbValue << " ";

            //若扫描到叶子节点，则不用做后续的子节点交换
            if (tempNode->m_pLeft != nullptr || tempNode->m_pRight != nullptr)
            {
                //交换当前节点下的左右节点
                BinaryTreeNode* tmp = tempNode->m_pLeft;

                tempNode->m_pLeft = tempNode->m_pRight;
                tempNode->m_pRight = tmp;
            }

            nodeStack.push(tempNode);

            tempNode = tempNode->m_pLeft;//根->左
        }
        else
        {
            //将已经扫描过的某子树的无左子节点的节点保存后弹出
            tempNode = nodeStack.top();
            nodeStack.pop();

            tempNode = tempNode->m_pRight;//右
        }
    }
}
#endif
#endif


//面试题28：对称的二叉树
//对称的前提是结构左右对称和节点的值左右对称
//用二叉树的镜像来判断，只能判断结构上的对称，还要判断节点的值是否对称
#if 0
#include <iostream>
#include "Tree.h"
#include <queue>
using namespace std;

//void breadthFirst(BinaryTreeNode* rootNode);
bool isSymmetric(BinaryTreeNode* p);
bool isSymmetricCore(BinaryTreeNode* rootNode1,BinaryTreeNode* rootNode2);
bool Equal(double a, double b);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);

    //breadthFirst(pNodeA1);
    //cout << endl;

    cout<<isSymmetric(pNodeA1);

    DestroyTree(pNodeA1);

    return 0;
}
bool isSymmetric(BinaryTreeNode* p)
{
    return isSymmetricCore(p,p);
}
//方法：
//通过比较二叉树的含nullptr的内容的前序遍历和含nullptr内容的对称前序遍历的内容
//来判断二叉树是否对称
bool isSymmetricCore(BinaryTreeNode* rootNode1, BinaryTreeNode* rootNode2)
{
    if (rootNode1 == nullptr && rootNode2 == nullptr)
        return true;

    if (rootNode1 == nullptr || rootNode2 == nullptr)
        return false;

    if (!Equal(rootNode1->m_dbValue, rootNode2->m_dbValue))
        return false;
    else
        return true;

    //***注***
    //正常前序遍历是根左右，而对称前序遍历是根右左

    return isSymmetricCore(rootNode1->m_pLeft, rootNode2->m_pRight) &&
        isSymmetricCore(rootNode1->m_pRight,rootNode2->m_pLeft);
}
bool Equal(double a, double b)
{
    return abs(a - b) < 0.0000001;
}
#endif


//面试题29：顺时针打印矩阵
#if 0
#include <iostream>

using namespace std;

void PrintMatrix(int** matrix, int row, int col);
void PrintMatrixInCircle(int** matrix, int row, int col, int start);

int main()
{
    int row, col;
    cin >> row >> col;

    int** matrix = new int* [row];

    for (int i = 0; i < row; ++i)
    {
        matrix[i] = new int[col];

		for (int j = 0; j < col; ++j)
        {
            matrix[i][j] = 1 + j + i * col;
        }
    }

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            cout<<matrix[i][j]<<'\t';
        }
        cout << endl;
    }
    cout << endl;

    PrintMatrix(matrix,row,col);

    return 0;
}

void PrintMatrix(int** matrix, int row, int col)
{
    if (matrix == nullptr || row < 1 || col < 1)
        return;

	//由于每一圈的终止位置的坐标值都会变，所以要找到
    //每一圈终止打印的条件，这有难度
    //若单用一个循环，那是无法完成打印任务的
    //int r, c;
    //r = c = 0;
    //while (1)
    //{
    //    if (c < col)
    //    {
    //        cout << matrix[r][c]<<'\t';
    //        ++c;
    //    }
    //}

    //创建代表行号的变量start
    //作用一：
    //以行号作为开始打印的起始位置，比如从索引为0的行开始打印，从索引为1的行开始打印
    //作用二：
    //由于要打印的每一圈的左上角的元素的坐标都是两个相同的值，如(0，0)、(1，1)等
    //所以start也可以用来作为打印开始的条件
    //作用三：
    //打印结束的条件需要观察和找规律后得出
    //对于5*5和6*6的矩阵来说，虽然最后一圈会只有一个数字或会有四个数字，
    //但是最后一圈左上角的数字所在的坐标一定满足
    //row>start*2  &&  col>start*2
    //所以start也可以用来作为打印结束的条件

    int start = 0;

    while (row > start * 2 && col > start * 2)
    {
        PrintMatrixInCircle(matrix,row,col,start);

        ++start;
    }
}

//按圈打印
void PrintMatrixInCircle(int** matrix, int row, int col, int start)
{
    //打印上方行
    for (int c = start; c < col - start; ++c)
    {
        cout << matrix[start][c] << ' ';
    }

    //打印右侧的列
    for (int r = start+1; r < row - start; ++r)
    {
        cout << matrix[r][col-start-1] << ' ';
    }

    //打印下方行
    for (int c = col-start-1-1; c >= start; --c)
    {
        cout << matrix[row-start-1][c] << ' ';
    }

    //打印左侧的行
    for (int r = row - start - 1 - 1; r > start; --r)
    {
        cout << matrix[r][start] << ' ';
    }
}
#endif


//面试题30：包含min函数的栈
#if 0
#include <iostream>
#include <algorithm>
#include <exception>
using namespace std;

template<typename T> 
class MyStack
{
private:
    enum {MAXN=20};
    T items[MAXN];
    int m_top;

public:
    MyStack();
    ~MyStack();

    bool push(const T& item);
    void pop(void);
    T top(void);
    int size(void);

protected:

};


template<typename T>
class StackWithMin
{
private:
    MyStack<T> m_data;//数据栈
    MyStack<T> m_min;//辅助栈

public:
    StackWithMin();
    ~StackWithMin();

    bool push(const T& item);
    void pop(void);
    T min(void);
};

template<typename T>
MyStack<T>::MyStack():m_top(0)
{
    fill(items,items+MAXN,0xffff);
}

template<typename T>
MyStack<T>::~MyStack()
{}

template<typename T>
bool MyStack<T>::push(const T& item)
{
    if (m_top >= MAXN)
        return false;

    items[m_top++] = item;

    return true;
}

template<typename T>
void MyStack<T>::pop(void)
{
    if (m_top == 0)
        throw new exception("illegal operation");

    --m_top;

    return;
}

template<typename T>
T MyStack<T>::top(void)
{
    return items[m_top-1];
}

template<typename T>
int MyStack<T>::size(void)
{
    return m_top;
}

template<typename T>
StackWithMin<T>::StackWithMin()
{}

template<typename T>
StackWithMin<T>::~StackWithMin()
{}

//可以把每次的最小元素(之前的最小元素和新压入栈的元素两者的较小值)
//保存起来放到辅助栈MyStack对象中
template<typename T>
bool StackWithMin<T>::push(const T& item)
{
    m_data.push(item);

    //***注***
    //m_min对象无法访问m_top这个私有数据成员,
    //将m_top声明为protected也不行
    //原因：
    // 私有继承所提供的特性确实比包含多。
    // 例如，假设类包含保护成员 （可以是数据成员，也可以是成员函数），
    // 则这样的成员在派生类中是可用的，但在继承层次结构外是不可用的。
    // 如果使用组合将这样的类包含在另一个类中，则后者将不是派生类，
    // 而是位于继承层次结构之外，因此不能访问保护成员。但
    // 通过继承得到的将是派生类，因此它能够访问保护成员。
    // 所以只能用size()方法
    if ( m_min.size() == 0 || m_data.top() < m_min.top())
    {
        m_min.push(item);
    }
    else
        m_min.push(m_min.top());

    //***注***
    //辅助栈每次压入的都是栈中元素和当前待压入元素的较小元素

    return true;
}

template<typename T>
void StackWithMin<T>::pop(void)
{
    m_data.pop();
    m_min.pop();
}

template<typename T>
T StackWithMin<T>::min(void)
{
    return m_min.top();
}

int main()
{
    StackWithMin<int> st;

	for (int i = 0; i < 22; ++i)
		st.push(i);

    cout << st.min();

    return 0;
}
#endif
//可以用assert()在运行阶段对断言进行检查，如果为 true，
//显示一条消息，否则调用 abort()


//面试题31：栈的压入、弹出序列
#if 0
#include <iostream>
#include <stack>
using namespace std;

bool IsPopOrder(const int* pPush,const int* pPop,int nLength);

int main()
{
    int yazhan[] = {1,2,3,4,5};
    int tanchu[] = {4,5,3,2,1};

    //cout << sizeof(yazhan) / sizeof(int);
    cout << IsPopOrder(yazhan,tanchu,sizeof(yazhan)/sizeof(int));

    int tanchu_1[] = {4,3,5,2,1};
    cout << IsPopOrder(yazhan,tanchu_1,5);

    return 0;
}

//自己写的解法：
#if 0
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    if (pPush == nullptr || pPop == nullptr || nLength <= 0)
        return false;

    stack<int> stk;

    int i = 0;

    //遍历pPush序列
	for (int index = 0; index < nLength; index++)
    {
        if (pPush[index] == pPop[i])
        {
            stk.push(pPush[index]);

            stk.pop();

            ++i;

            while (!stk.empty()&& stk.top() == pPop[i])
            {
                stk.pop();

                ++i;
            }

            continue;
        }

        stk.push(pPush[index]);
    }

    while (!stk.empty())
    {
        if (stk.top() == pPop[i])
        {
            stk.pop();
            ++i;
        }
        else
            return false;
    }

    return true;
}
#endif

//书上的解法：
#if 1
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    if (pPush == nullptr || pPop == nullptr || nLength <= 0)
        return false;

    stack<int>stk;

    //直接用指针作为判断循环终止的条件
    /*const int* pNextPush = pPush;
    const int* pNextPop = pPop;

    while (pNextPop - pPop < nLength)
    {

    }*/

    bool flag = false;

    int i = 0;

    //或者
    //用索引作为判断循环终止的条件，
    //遍历的是pPop序列
    for (int index = 0; index < nLength; ++index)
    {
        //若辅助栈为空，或辅助栈的栈顶元素不等于pPop[index]
        while (stk.empty() || stk.top() != pPop[index])
        {
            if (i == nLength)
                break;

            stk.push(pPush[i]);
            ++i;
        }

        //若辅助栈已经装完了pPush序列，仍和pPop[index]不相等
        if (stk.top() != pPop[index])
            break;

        //若辅助栈的栈顶元素与pPop[index]相等
        stk.pop();
    }

    if (stk.empty())
        flag = true;

    return flag;
}
#endif

#endif


//面试题32：从上到下打印二叉树
#if 0
#include <iostream>
#include "Tree.h"
#include <queue>
using namespace std;

void breadthFirst(BinaryTreeNode* rootNode);
void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);
    //                   1
    //            2           3
    //                     4
    //                           5

    breadthFirst(pNodeA1);

    cout << endl;

    PrintFromToptoBottom(pNodeA1);

    DestroyTree(pNodeA1);

    return 0;
}

void breadthFirst(BinaryTreeNode* rootNode)
{
    if (rootNode == nullptr)
        return;

    queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tmpNode = rootNode;

    nodeQueue.push(rootNode);

    while (!nodeQueue.empty())
    {
        if(tmpNode)
        cout << tmpNode->m_dbValue << " ";
        
        if(tmpNode->m_pLeft)
        nodeQueue.push(tmpNode->m_pLeft);

        if(tmpNode->m_pRight)
        nodeQueue.push(tmpNode->m_pRight);

        nodeQueue.pop();

        if(!nodeQueue.empty())
        tmpNode = nodeQueue.front();
    }

    return;
}

//书上解法：
void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    nodeQueue.push(pTreeRoot);

    while (!nodeQueue.empty())
    {
        //先拿元素
        tempNode = nodeQueue.front();

        std::cout << tempNode->m_dbValue << " ";

        //后弹出
        nodeQueue.pop();

        if (tempNode->m_pLeft)
            nodeQueue.push(tempNode->m_pLeft);
        if (tempNode->m_pRight)
            nodeQueue.push(tempNode->m_pRight);
    }
}
#endif


//分行从上到下打印二叉树
#if 0
#include <iostream>
#include "Tree.h"
#include <queue>
using namespace std;

void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);
    //                   1
    //            2           3
    //                     4
    //                           5

    PrintFromToptoBottom(pNodeA1);

    DestroyTree(pNodeA1);

    return 0;
}

//如何按层打印？
//方法：创建变量x来存储每层等待打印的节点数量
//难点：一层有四个节点，那怎么办？
//当变量x值降为0后，打印换行符

void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    int num_of_ele_of_this_level = 0;
    int cnt=1;
    nodeQueue.push(pTreeRoot);

    while (!nodeQueue.empty())
    {
        //先拿元素
        tempNode = nodeQueue.front();
        //后弹出
        nodeQueue.pop();

        std::cout << tempNode->m_dbValue << " ";

        cnt--;

        if (tempNode->m_pLeft)
        {
			nodeQueue.push(tempNode->m_pLeft);
            ++num_of_ele_of_this_level;
        }
        if (tempNode->m_pRight)
        {
            nodeQueue.push(tempNode->m_pRight);
            ++num_of_ele_of_this_level;
        }

        if (!cnt)
        {
            cout << endl;

            cnt = num_of_ele_of_this_level;

            num_of_ele_of_this_level = 0;
        }
    }
}
#endif


//之字形打印二叉树
#if 0
#include <iostream>
#include "Tree.h"
#include <queue>
#include <stack>
using namespace std;

void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNodeA8 = CreateBinaryTreeNode(8);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, nullptr, pNodeA4);
    ConnectTreeNodes(pNodeA3, pNodeA5, pNodeA6);
    ConnectTreeNodes(pNodeA5, pNodeA7, pNodeA8);

    //                   1
    //            2           3
    //                4    5    6
    //                    7  8    

    Print_in_zigzag_pattern(pNodeA1);

    DestroyTree(pNodeA1);

    return 0;
}

#if 0
void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    queue<BinaryTreeNode*> nodeQueue;
    stack<BinaryTreeNode*> nodeStack;

    //记录层号
    int odd_even = 1;

    //记录某层应该打印的节点数量
    int num_of_this_level = 0;

    //记录某层还有多少节点数量没有被打印
    int cnt = 1;

    nodeQueue.push(pTreeRoot);

    BinaryTreeNode* p_tmpNode = nullptr;

    while (!nodeQueue.empty()||!nodeStack.empty())
    {
        if (odd_even & 0x01)
        {
            p_tmpNode = nodeQueue.front();
            nodeQueue.pop();
        }
        else
        {
            p_tmpNode = nodeStack.top();
            nodeStack.pop();
        }

        cout << p_tmpNode->m_dbValue << " ";

        if (p_tmpNode->m_pLeft)
        {
            if (odd_even & 0x01)
                nodeStack.push(p_tmpNode->m_pLeft);
            else
                nodeQueue.push(p_tmpNode->m_pLeft);

            ++num_of_this_level;
        }

        //错误点：
        //当遍历到值为3的节点时，要向队列压入节点，但这就会造成队列中各节点的值
        //为5  6  4

        if (p_tmpNode->m_pRight)
        {
            if (odd_even & 0x01)
                nodeStack.push(p_tmpNode->m_pRight);
            else
                nodeQueue.push(p_tmpNode->m_pRight);

            ++num_of_this_level;
        }

        cnt--;

        if (!cnt)
        {
            cout << endl;

            cnt = num_of_this_level;
            num_of_this_level = 0;

			odd_even++;
        }

    }
}
#endif

//自己的解法：
//在不改变遍历左子节点再遍历右子节点的顺序下，
//增加一个辅助栈来修正元素顺序
#if 0
void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    queue<BinaryTreeNode*> nodeQueue;
    stack<BinaryTreeNode*> nodeStack;
    stack<BinaryTreeNode*> aux_Stack;

    //记录层号
    int odd_even = 1;

    //记录某层应该打印的节点数量
    int num_of_this_level = 0;

    //记录某层还有多少节点数量没有被打印
    int cnt = 1;

    nodeQueue.push(pTreeRoot);

    BinaryTreeNode* p_tmpNode = nullptr;

    while (!nodeQueue.empty() || !nodeStack.empty())
    {
        if (odd_even & 0x01)
        {
            p_tmpNode = nodeQueue.front();
            nodeQueue.pop();
        }
        else
        {
            p_tmpNode = nodeStack.top();

            //***注***
            //辅助栈用来颠倒元素顺序
            //打印仍打印的是nodeStack中的元素
            aux_Stack.push(nodeStack.top());

            nodeStack.pop();
        }

        cout << p_tmpNode->m_dbValue << " ";

        cnt--;

        //根据层号的奇偶性来做不同的操作
        if (odd_even & 0x01)
        {
            if (p_tmpNode->m_pLeft)
            {
                nodeStack.push(p_tmpNode->m_pLeft);
                num_of_this_level++;
            }
            if (p_tmpNode->m_pRight)
            {
                nodeStack.push(p_tmpNode->m_pRight);
                num_of_this_level++;
            }
        }
        else
        {
            if (!cnt)//当层号为偶数，且该层节点都被打印完了，那就可以向队列压入节点的值了
            {
                while (!aux_Stack.empty())
                {
					p_tmpNode = aux_Stack.top();

					if (p_tmpNode->m_pLeft)
					{
						nodeQueue.push(p_tmpNode->m_pLeft);
                        num_of_this_level++;
					}
                    
                    if (p_tmpNode->m_pRight)
					{
						nodeQueue.push(p_tmpNode->m_pRight);
                        num_of_this_level++;
					}

					aux_Stack.pop();
                }

            }
        }

        if (!cnt)
        {
            cout << endl;

            cnt = num_of_this_level;
            num_of_this_level = 0;

            odd_even++;
        }

    }
}
#endif

//解法二：
//改变遍历顺序，当遍历奇数层时，压入栈的顺序为先遍历左子节点再遍历右子节点
//当遍历偶数层时，压入栈的顺序为先遍历右子节点再遍历左子节点
//而且不用队列，而是总共使用两个栈
#if 0
void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;
    
    stack<BinaryTreeNode*> nodeStack[2];

    //表示当前所使用的栈
    int current = 0;
    //next变量用于指定将使用哪个栈来存元素
    int next = 1;

    nodeStack[current].push(pTreeRoot);
    BinaryTreeNode* p_tmpNode = nullptr;

    while (!nodeStack[0].empty() || !nodeStack[1].empty())
    {
        p_tmpNode = nodeStack[current].top();
        nodeStack[current].pop();

        cout << p_tmpNode->m_dbValue << " ";

        if (current == 0)
        {
            if (p_tmpNode->m_pLeft)
            {
                nodeStack[next].push(p_tmpNode->m_pLeft);
            }
            if (p_tmpNode->m_pRight)
            {
                nodeStack[next].push(p_tmpNode->m_pRight);
            }
        }
        else
        {
            if (p_tmpNode->m_pRight)
            {
                nodeStack[next].push(p_tmpNode->m_pRight);
            }
            if (p_tmpNode->m_pLeft)
            {
                nodeStack[next].push(p_tmpNode->m_pLeft);
            }
        }

        //不再利用num_of_this_level变量和cnt变量来设置换行符

        if (nodeStack[current].empty())
        {
            cout << endl;

            current = 1 - current;
            next = 1 - next;
        }
    }
}
#endif
#endif


//面试题33：二叉搜索树的后序遍历序列
#if 0
#include <iostream>
#include "Tree.h"

using namespace std;

bool VerifySquenceOfBST(int* sequence,int length);

int main()
{
    /*
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNodeA8 = CreateBinaryTreeNode(8);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, nullptr, pNodeA4);
    ConnectTreeNodes(pNodeA3, pNodeA5, pNodeA6);
    ConnectTreeNodes(pNodeA5, pNodeA7, pNodeA8);
    */

    //                   1
    //            2           3
    //                4    5    6
    //                    7  8    

    int seq[] = {5,7,6,9,11,10,8};


    cout<<VerifySquenceOfBST(seq,sizeof(seq)/sizeof(int));

    //DestroyTree(pNodeA1);

    return 0;
}

//二叉树搜索树的元素排列的规范为
//某个节点的左子树的所有节点的值比其小，右子树的所有节点的值比其大。

//二叉树的后序遍历的特点是：
//序列的最后一个元素就是根节点的值，序列除末尾的值，其他的值若小于根节点的值
//则为根节点的左子树，反之，则为右子树
//而且在子树中，仍存在此规律

//自己的解法：
#if 0
bool VerifySquenceOfBST(int* sequence, int length)
{
    if (sequence==nullptr||length<=0)
        return false;

    //创建变量存储当前树的根节点的值
    int root = sequence[length-1];

    //确定左右子树的序列的内容长度
    int i;
    for (i = 0; ; ++i)
    {
        if (sequence[i] >= root)//***注***   此处要写成大于等于，否则会进入死循环
            break;
    }

    int j = i;
    for (   ; j<length-1 ; ++j)
    {
        if (sequence[j] < root)
            return false;
    }

    bool flag = true;
    //若某节点存在左子树
    if(i>=1&&sequence[i]!=root)
		flag = VerifySquenceOfBST(sequence, i);

    //若某节点存在右子树
    if (flag&&j != i)
        flag = VerifySquenceOfBST(sequence+i,   j-i);

    return flag;
}
#endif

//解法二：
#if 1
bool VerifySquenceOfBST(int* sequence, int length)
{
    if (sequence == nullptr || length <= 0)
        return false;

    int root = sequence[length - 1];

    int i;
    for (i = 0; i<length-1; ++i)
    {
        if (sequence[i] > root)
            break;
    }

    int j = i;
    for (; j < length - 1; ++j)
    {
        if (sequence[j] < root)
            return false;
    }

    bool left = true;
    if (i > 0)
        left = VerifySquenceOfBST(sequence,i);

    bool right = true;
    if (i < length - 1)
        right = VerifySquenceOfBST(sequence+i,j-i);

    return left && right;
}
#endif
#endif


//面试题34：二叉树中和为某一值的路径
//思路：
//当用前序遍历的方式访问到某一节点时，我们把该节点添加到路径上，
//并累加该节点的值。如果该节点为叶节点，并且路径中节点值的和刚好等于输入的整数，
//则当前路径符合要求，我们把它打印出来。如果当前节点不是叶节点，则
//继续访问它的子节点。当前节点访问结束后，递归函数将自动回到它的父
//节点。因此，我们在函数退出之前要在路径上删除当前节点并减去当前节
//点的值，以确保返回父节点时路径刚好是从根节点到父节点。我们不难看
//出保存路径的数据结构实际上是一个栈，因为路径要与递归调用状态一
//致，而递归调用的本质就是一个压栈和出栈的过程。
#if 0
#include <iostream>
#include <vector>
#include <stack>
#include "Tree.h"

using namespace std;

void FindPath(BinaryTreeNode* pRoot,int exceptedSum);
void FindPathCore(BinaryTreeNode*pRoot, int exceptedSum, 
    vector<int>& vec, int CurrentSum);

int main()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA8 = CreateBinaryTreeNode(8);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA3, pNodeA5, pNodeA6);
	ConnectTreeNodes(pNodeA5, pNodeA7, pNodeA8);

//                   1
//            2           3
//                4    5    6
//                    7  8    

    FindPath(pNodeA1,16);

    DestroyTree(pNodeA1);

    return 0;
}
void FindPath(BinaryTreeNode* pRoot, int exceptedSum)
{
    if (!pRoot)
        return;

    //stack<int> path;
    vector<int> path;

    int CurrentSum = 0;

    FindPathCore(pRoot,exceptedSum,path,CurrentSum);
}

void FindPathCore(BinaryTreeNode* pRoot, int exceptedSum,
    vector<int>& vec, int CurrentSum)
{
    vec.push_back(pRoot->m_dbValue);
    CurrentSum += pRoot->m_dbValue;

    //若当前总和等于期望的总和，且pRoot指向了树的叶子结点
    if (CurrentSum == exceptedSum&&pRoot->m_pLeft==nullptr
        &&pRoot->m_pRight==nullptr)
    {
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    if (pRoot->m_pLeft)
        FindPathCore(pRoot->m_pLeft,exceptedSum,vec,CurrentSum);

    if(pRoot->m_pRight)
        FindPathCore(pRoot->m_pRight,exceptedSum,vec,CurrentSum);

    vec.pop_back();//用vector容器来实现栈
}
#endif


//分治法——分解让复杂问题简单化
//面试题35：复杂链表的复制
#if 0
#include <iostream>
#include <unordered_map>
//#include "List.h"
struct ComplexListNode
{
    int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};

using namespace std;

ComplexListNode* CreateComplexListNode(int value);
void ConnectComplexListNode(ComplexListNode* pCurrent, ComplexListNode* pNext);
void RandomlyConnectComplexListNode(ComplexListNode* pCurrent, ComplexListNode* pNext);
void PrintList(ComplexListNode* pHead);

ComplexListNode* Clone(ComplexListNode* pHead);

int main()
{
    ComplexListNode* pNode1 = CreateComplexListNode(1);
    ComplexListNode* pNode2 = CreateComplexListNode(2);
    ComplexListNode* pNode3 = CreateComplexListNode(3);
    ComplexListNode* pNode4 = CreateComplexListNode(4);
    ComplexListNode* pNode5 = CreateComplexListNode(5);

    ConnectComplexListNode(pNode1,pNode2);
    ConnectComplexListNode(pNode2,pNode3);
    ConnectComplexListNode(pNode3,pNode4);
    ConnectComplexListNode(pNode4,pNode5);
    
    RandomlyConnectComplexListNode(pNode1,pNode3);
    RandomlyConnectComplexListNode(pNode2,pNode5);
    RandomlyConnectComplexListNode(pNode4,pNode2);

    PrintList(pNode1);
    cout << endl<<endl;
    ComplexListNode* pClone = Clone(pNode1);

    PrintList(pClone);

    return 0;
}

ComplexListNode* CreateComplexListNode(int value)
{
    ComplexListNode* pNode = new ComplexListNode();
    pNode->m_nValue = value;
    pNode->m_pNext = nullptr;
    pNode->m_pSibling = nullptr;

    return pNode;
}

void ConnectComplexListNode(ComplexListNode* pCurrent, ComplexListNode* pNext)
{
    if (pCurrent == nullptr)
    {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->m_pNext = pNext;
}

void RandomlyConnectComplexListNode(ComplexListNode* pCurrent, ComplexListNode* pNext)
{
    if (pCurrent == nullptr)
    {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->m_pSibling = pNext;
}

void PrintList(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while (pNode != nullptr)
    {
        printf("The value of this node is: %d.\n", pNode->m_nValue);

        if (pNode->m_pSibling != nullptr)
            printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
        else
            printf("This node does not have a sibling.\n");

        printf("\n");

        pNode = pNode->m_pNext;
    }
}

//法一：
//由于原节点和新的拷贝的节点是一一对应关系，所以可以用哈希表，在遍历
//原节点的同时，创建并向哈希表存入原节点和新创建的节点
#if 0
ComplexListNode* Clone(ComplexListNode* pHead)
{
    ComplexListNode* cur = pHead;

    //创建哈希表
    unordered_map<ComplexListNode*, ComplexListNode*> hash;

    //保存原节点和拷贝的结点
    //(原节点序列作为键)
    while (cur)
    {
        ComplexListNode* tmp=new ComplexListNode;
        tmp->m_nValue = cur->m_nValue;

        hash.insert(make_pair(cur,tmp));//make_pair()返回含有指定值的 std::pair 对象

        cur = cur->m_pNext;
    }

    cur = pHead;
    //修改拷贝的节点的指针成员指向的内存空间
    while (cur)
    {
        //***注***
        //可以用数组表示法(将键用作索引)来访问存储的值
        //访问拷贝的节点的m_pNext指针
        //(拷贝的节点的m_pNext指针原来存的是原链表的被拷贝的节点的下一个节点的地址)
        //m_pNext存拷贝的下一个节点的地址
        hash[cur]->m_pNext = hash[cur->m_pNext];

        //同理，修改被拷贝节点的m_pSibling指针指向的内存空间
        hash[cur]->m_pSibling = hash[cur->m_pSibling];

        cur = cur->m_pNext;
    }

    return (*(hash.begin())).first;

    //return hash[pHead];
}
#endif

//法二：
//不使用辅助空间的情况下实现O(n)的时间复杂度
#if 1
void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;

    while (pNode != nullptr)
    {
        ComplexListNode* pClone = new ComplexListNode;

        pClone->m_nValue = pNode->m_nValue;
        pClone->m_pNext = pNode->m_pNext;
        pClone->m_pSibling = nullptr;

        pNode->m_pNext = pClone;
        pNode = pClone->m_pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;

    while (pNode != nullptr)
    {
        ComplexListNode* pClone = pNode->m_pNext;

        if (pNode->m_pSibling)
        {
            pClone->m_pSibling = pNode->m_pSibling->m_pNext;
        }

        pNode = pClone->m_pNext;
    }
}

//将拷贝的各个节点从链表中抽离
//瑕疵：导致原链表断裂
#if 0
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    /*
    cout << "测试" << endl;
    ComplexListNode* pNode = pHead->m_pNext;
    printf("The value of this node is: %d.\n", pNode->m_nValue);

    if (pNode->m_pSibling != nullptr)
        printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
    else
        printf("This node does not have a sibling.\n");

    printf("\n");
    */

    ComplexListNode* CopyedNode = pHead->m_pNext;

    ComplexListNode* tmp=pHead->m_pNext;

    while (tmp->m_pNext)
    {
        tmp = CopyedNode->m_pNext->m_pNext;
        CopyedNode->m_pNext = tmp;

        CopyedNode = tmp;
    }

    /*
    cout << "测试"<<endl;
    pNode = pHead->m_pNext;
    printf("The value of this node is: %d.\n", pNode->m_nValue);

    if (pNode->m_pSibling != nullptr)
        printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
    else
        printf("This node does not have a sibling.\n");

    printf("\n");
    */

    return pHead->m_pNext;
}
#endif

//将一个链表分离为两个链表
#if 1
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    //pNode用于遍历原链表
    ComplexListNode* pNode = pHead;
    //pClonedHead指向克隆链表的头部
    ComplexListNode* pClonedHead = nullptr;
    //pClonedNode用于遍历克隆链表
    ComplexListNode* pClonedNode = nullptr;

    if (pNode != nullptr)
    {
        //将pClonedHead和pClonedNode都指向pNode的下一个节点，即克隆链表的第一个节点
        // （因为克隆链表的第一个节点是原链表的第二个节点）
        pClonedHead = pClonedNode = pNode->m_pNext;
        //更新pNode的m_pNext指针，将其指向下一个节点（原链表中的下下个节点）
        pNode->m_pNext = pClonedNode->m_pNext;
        //pNode指向链表的第3个节点
        pNode = pNode->m_pNext;
    }

    //                  pClonedHead
    //                  pClonedNode      pNode
    //       1                  1'                    2                     2'

    while (pNode != nullptr)
    {
        //将pClonedNode的m_pNext指针指向pNode的下一个节点，
        //从而将克隆链表的下一个节点链接到下一个被克隆节点。
        pClonedNode->m_pNext = pNode->m_pNext;

        //更新pClonedNode和pNode，使它们分别指向克隆链表和原链表中的下一个节点。
        pClonedNode = pClonedNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;

        pNode = pNode->m_pNext;
    }

    return pClonedHead;
}
#endif

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}
#endif
#endif


//面试题36：二叉搜索树与双向链表
#if 0
#include <iostream>
#include <exception>
#include "Tree.h"

using namespace std;

BinaryTreeNode* Convert(BinaryTreeNode* pNode);
void ConvertNode(BinaryTreeNode* pNode,BinaryTreeNode** pLastNodeInList);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(14);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(16);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
    ConnectTreeNodes(pNodeA3, pNodeA6, pNodeA7);

    //将二叉搜索树转换成双向链表，
    //那么树的某个节点的左子节点将位于该节点之前，即
    //该节点的指向左子节点的指针调整为指向双向链表前一个节点的指针
    //该节点的指向右节点的指针也同理需要调整
     
    //根节点和叶子结点的两个指针【可能】需要特殊处理

    BinaryTreeNode* List=Convert(pNodeA1);

    //***注***
    //不能写以下语句，因为二叉树结构变成了双向链表结构，
    //当从值为10的节点开始，遍历并释放节点到值为4的节点后，
    //会再次遍历到值为6的节点，并试图进行二次释放内存空间，这会导致错误。
    //DestroyTree(pNodeA1);

    return 0;
}

BinaryTreeNode* Convert(BinaryTreeNode* pNode)
{
    if (!pNode)
        throw new exception("Error!");

    BinaryTreeNode* pLastNodeInList = nullptr;
    ConvertNode(pNode,&pLastNodeInList);

    //创建pHeadNodeInList指针指向链表的首个节点
    BinaryTreeNode* pHeadNodeInList = pLastNodeInList;
    while (pHeadNodeInList != nullptr && pHeadNodeInList->m_pLeft != nullptr)
    {        
        pHeadNodeInList = pHeadNodeInList->m_pLeft;
    }

    return pHeadNodeInList;
}

void ConvertNode(BinaryTreeNode* pNode, BinaryTreeNode** pLastNodeInList)
{
    if (!pNode)
        return;

    BinaryTreeNode* cur = pNode;

    //以递归的方式进行中序遍历
    if (cur->m_pLeft != nullptr)
        ConvertNode(cur->m_pLeft,pLastNodeInList);

    //***难点***
    //到达中序遍历序列的首元素时，应该作何处理？

    //双向链表的首节点的指向前一个节点的指针赋为nullptr
    //非首节点的指向前一个节点的指针赋为前一个节点的地址
    //但是无需进行分类处理，以下一条语句就可以完成
    cur->m_pLeft = *pLastNodeInList;

    //若pLastNodeInList指向非首节点，则设置该节点的指向后一个节点的指针
    //指向当前cur指向的位置
    if (*pLastNodeInList != nullptr)
        (*pLastNodeInList)->m_pRight = cur;

    //*pLastNodeInList前进一个节点的距离
    *pLastNodeInList = cur;

    //小结：
    //cur指针处理指向的节点的指向前一个节点的指针
    //*pLastNodeInList指针处理指向的节点的指向后一个节点的指针
    //两个指针一前一后，逐渐向后移动

    if (cur->m_pRight != nullptr)
        ConvertNode(cur->m_pRight,pLastNodeInList);
}
#endif


//面试题37：序列化二叉树
#if 0
#include <iostream>
#include <fstream>
#include "Tree.h"
#include <queue>
//void serialize(BinaryTreeNode* pNode);

void serialize(BinaryTreeNode* pNode,std::ostream& stream);
bool ReadStream(std::istream& stream, int* number);
void deserialize(BinaryTreeNode** pNode, std::istream& stream);
void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot);

int main()
{
    BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(6);

    ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
    ConnectTreeNodes(pNodeA2, pNodeA4, nullptr);
    ConnectTreeNodes(pNodeA3, pNodeA5, pNodeA6);

	std::ofstream fout("test.txt");

    if (!fout.is_open())
    {
        std::cerr << "error 1\n";
        exit(EXIT_FAILURE);
    }

    serialize(pNodeA1,fout);
    fout.close();
    std::cout << "Serialize has done!\n";
    DestroyTree(pNodeA1);

/**************************************************************/
    BinaryTreeNode* pNodeA;

    std::ifstream fin("test.txt");

    if (!fin.is_open())
    {
        std::cerr << "error 2\n";
        exit(EXIT_FAILURE);
    }

	deserialize(&pNodeA,fin);
    PrintFromToptoBottom(pNodeA);

    return 0;
}

#if 0
void serialize(BinaryTreeNode* pNode)
{
    if (!pNode)
    {
        std::cout << "$, ";
        return;
    }

    std::cout << pNode->m_dbValue << ", ";

    //if (pNode->m_pLeft)
	serialize(pNode->m_pLeft);

    //if (pNode->m_pRight)
	serialize(pNode->m_pRight);
}
#endif

#if 1
void serialize(BinaryTreeNode* pNode, std::ostream& stream)
{
    if (!pNode)
    {
        stream << "$, ";
        return;
    }

    stream << pNode->m_dbValue << ", ";

    //if (pNode->m_pLeft)
    serialize(pNode->m_pLeft, stream);

    //if (pNode->m_pRight)
    serialize(pNode->m_pRight, stream);
}
#endif

//***注***
//istream类和ostream类的复制构造函数都被设置为protected，
//所以外部无法访问这些函数，只能写成引用的形式。
void deserialize(BinaryTreeNode** pNode, std::istream& stream)
{
	int number;

    if (ReadStream(stream, &number))
    {
        //BinaryTreeNode* tmp = new BinaryTreeNode;
        //*pNode = tmp;

        *pNode = new BinaryTreeNode;

        (*pNode)->m_dbValue = (int)number;
        (*pNode)->m_pLeft = nullptr;
        (*pNode)->m_pRight = nullptr;

        deserialize(&((*pNode)->m_pLeft),stream);
        deserialize(&((*pNode)->m_pRight),stream);
    }
}

//从文件输入流中将字符逐个提取
bool ReadStream(std::istream& stream, int* number)
{
	if (stream.eof())
		return false;

    char buffer[32] = {'\0'};

    //创建ch变量来暂存字符
	char ch;
	stream >> ch;
	int i = 0;

	while (!stream.eof() && ch != ',')
	{
		buffer[i++] = ch;
		stream >> ch;
	}

	bool isNumeric = false;

	if (i > 0 && buffer[0] != '$')
	{
		*number = atoi(buffer);
		isNumeric = true;
	}

	return isNumeric;
}

void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    int num_of_ele_of_this_level = 0;
    int cnt = 1;
    nodeQueue.push(pTreeRoot);

	BinaryTreeNode* Nodata=new BinaryTreeNode;
    Nodata->m_dbValue = 1.11111;
    Nodata->m_pLeft = nullptr;
    Nodata->m_pRight = nullptr;

    while (!nodeQueue.empty())
    {
        //先拿元素
        tempNode = nodeQueue.front();
        //后弹出
        nodeQueue.pop();

        if (tempNode->m_dbValue != 1.11111)
            std::cout << tempNode->m_dbValue << " ";
        else
            std::cout << "nullptr ";

        cnt--;

        if (tempNode->m_pLeft)
        {
            nodeQueue.push(tempNode->m_pLeft);
			++num_of_ele_of_this_level;
        }
        else if(tempNode!=Nodata)
        {
            nodeQueue.push(Nodata);
			++num_of_ele_of_this_level;
        }


        if (tempNode->m_pRight)
        {
            nodeQueue.push(tempNode->m_pRight);
			++num_of_ele_of_this_level;
        }
        else if (tempNode != Nodata)
        {
            nodeQueue.push(Nodata);
			++num_of_ele_of_this_level;
        }

        if (!cnt)
        {
            std::cout << std::endl;

            cnt = num_of_ele_of_this_level;

            num_of_ele_of_this_level = 0;
        }
    }
}

#endif


//面试题38：字符串的排列
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

void Print(char* ch,int length);
void Permutation(char* pStr);
void Permutation(char* pStr, char* pBegin);

int main()
{
    char data[3] = {'a','b','c'};

    //Print(data,sizeof(data)/sizeof(char));

    cout << endl;

    char data2[] = "abcd";

    Permutation(data2);
}
void Print(char* ch, int length)
{
    if (!ch||length<=0)
        return;

    do
    {
        for (int i = 0; i < length; ++i)
            cout << ch[i] << ' ';

        cout << endl;
    } while (next_permutation(ch, ch + length));
}

void Permutation(char* pStr)
{
    if (!pStr)
        return;

    Permutation(pStr,pStr);
}

//pStr始终指向字符串的首元素
//pBegin指向正在考虑排列的字符串中的当前位置的指针
//pBegin指向的元素不断地与其指向的元素的后面的每一个元素进行交换
void Permutation(char* pStr, char* pBegin)
{
    if (*pBegin == '\0')
        printf("%s\n", pStr);
    else
    {
        for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
        {
            char tmp = *pCh;
            *pCh = *pBegin;
            *pBegin = tmp;

            Permutation(pStr,pBegin+1);

            //***注1***
            //将字符交换回其原始位置，以确保循环的下一次迭代使用原始字符串
            tmp = *pCh;
            *pCh = *pBegin;
            *pBegin = tmp;
        }
    }
}
//不添加注1        和           添加注1语句块的运行区别        
//abc                                         abc                                    abcd
//acb                                         acb                                    abdc
//cab                                         bac                                    acbd
//cba                                         bca                                    acdb
//abc                                         cba                                    adcb
//acb                                         cab                                    adbc
#endif


//字符串的所有组合
#if 0
#include<iostream>  
#include<vector>  
#include<cstring>  
#include<assert.h>  

using namespace std;

void Combination(char* string);
void Combination(char* string, int number, vector<char>& result);

int main(void)
{
    char str[] = "abc";

    Combination(str);
    
    return 0;
}

//在求n个字符的长度为m(1≤m≤n)的组合的时候，我们把这n个字符分成两部分：
//第一个字符和其余的所有字符。
//如果组合里包含第一个字符，则下一步在剩余的字符里选取m - 1个字符；
//如果组合里不包含第一个字符，则下一步在剩余的n - 1个字符里选取m个字符。

//可以把求n个字符组成长度为m的组合的问题分解成两个子问题，
//分别求n - 1个字符中长度为m-1的组合，以及
// 求n-1个字符中长度为m的组合。这两个子问题都可以用递归的方式解决。
void Combination(char* string)
{
    assert(string != NULL);

    vector<char> result;

    int m, length = strlen(string);

    //求长度为length的字符的长度为i的组合
    for (m = 1; m <= length; ++m)
        Combination(string, m, result);
}

void Combination(char* string, int number, vector<char>& result)
{
    assert(string != NULL);

    if (number == 0)
    {
        static int num = 1;
        printf("第%d个组合\t", num++);

        vector<char>::iterator iter = result.begin();
        for (; iter != result.end(); ++iter)
            printf("%c", *iter);
        printf("\n");

        return;
    }

    if (*string == '\0')
        return;

    result.push_back(*string);

    //如果包含第一个字符，则下一步在剩余的字符里面选取number-1个字符
    Combination(string + 1, number - 1, result);  

    result.pop_back();  //出去第一个字符

    //如果不包含第一个字符，则下一步在剩余的字符里面选取number个字符  
    Combination(string + 1, number, result); 
}
#endif


//八皇后问题
#if 0
#include <iostream>
#include<cmath>
using namespace std;

//c[x]=y，表示皇后放在第x行，第y列
//棋盘8x8，n为8
//创建cnt记录符合的情况数量
int c[20], n = 8, cnt = 0;

void search(int r);
void print(void);

int main()
{
    //从第1行开始进行模拟
    search(0);
    cout << cnt << endl;
    return 0;
}

//回溯法解题
//递归调用search()
void search(int r) 
{
    //若已经模拟到第9行(r比行数少1)
    if (r == n) 
    {
        print();
        ++cnt;
        return;
    }

    for (int i = 0; i < n; ++i) 
    {
        //第r+1行第i+1列放置皇后
        c[r] = i;

        int ok = 1;

        //对r+1行之前的行进行遍历
        for (int row = 0; row < r; ++row)
        {
            //若列相同或两者互为对角线
            if (c[r] == c[row] || abs(r - row) == abs(c[r] - c[row]))
            {
                //该行放的不对，要重新放
                ok = 0;
                break;
            }
        }

        if (ok) 
            search(r + 1);
    }
}

void print()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j == c[i])
                cout << "1 ";
            else 
                cout << "0 ";
        }
        cout << endl;
    }
    cout << endl;
}
#endif


//面试题39：数组中出现次数超过一半的数字
#if 0
#include <iostream>
//#include <vector>
#include <unordered_map>
using namespace std;

//自己的解法：用哈希表
void FindNum(int* p_data,int length);

int MoreThanHalfNum(int* number,int length);

int main()
{
    int data[] = {1,2,3,2,2,2,5,4,2};

    FindNum(data,sizeof(data)/sizeof(int));

    cout << endl;

    cout<<MoreThanHalfNum(data,sizeof(data)/sizeof(int));

    return 0;
}

#if 1
void FindNum(int* p_data,int length)
{
    if (!p_data || length <= 0)
        return;

    //vector<int> cnt[2];
    unordered_map<int, int> hash;

    for (int i = 0; i < length; ++i)
    {
        //哈希表的查询时间是O(1)
        if(hash.find(p_data[i]) == hash.end())
        hash.insert(make_pair(p_data[i], 1));
        else
        {
            hash[p_data[i]]+=1;  
        }
    }

    for (auto it = hash.begin(); it != hash.end(); ++it)
    {
        //if (it->second > length / 2)
        if (it->second > length >>1)
            cout << it->first;
    }
}
#endif

//解法二：基于Partition()的时间复杂度为O(n)的算法
#if 0
int RandomInRange(int a, int b)
{
    srand((unsigned int)time(0));
    // 生成 [0, max]
    //int x = rand() % (max + 1);

    // 生成 [1, max]
    //int x = 1 + rand() % (max);

    // 生成 [min, max] 范围的随机数
    //int x = min + rand() % (max - min + 1);

    int x = a + rand() % (b - a + 1);
    return x;
}

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//***begin和end都指的是索引值***
int Partition(int data[], int length, int begin, int end)
{
    if (data == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //生成一个在指定范围内的随机数
    int index = RandomInRange(begin, end);
    //该随机数作为索引值对应的数字与数组末尾的数字交换
    //那么数组末尾的数字就是随机索引值对应的数字
    Swap(&data[index], &data[end]);

    //创建枢轴small存储索引值，其初始值比begin小1，如：begin为0，则small为-1
    int small = begin - 1;

    //索引值从头开始，逐渐增加
    for (index = begin; index < end; ++index)
    {
        //若当前索引值指向的数字比随机索引值指向的数字小
        if (data[index] <= data[end])//注意是小于等于
        {
            //增加small的值
            ++small;

            //若small不为当前的索引值
            if (small != index)
                Swap(&data[index], &data[small]);//互换元素，目的是
            //让索引值small左侧的值都小于该索引值所对应的值
        }
    }
    //让small再增加1
    ++small;
    //让随机索引值指向的数字移动到small指向的位置上
    Swap(&data[small], &data[end]);

    //返回枢轴所在位置
    return small;
}

int MoreThanHalfNum(int* number, int length)
{
    if (number == nullptr || length <= 0)
        return 0;

    //存储排序好的数组的中位数字应所在的索引值
    int middle = length / 2;

    int start = 0;
    int end = length - 1;

    int index = Partition(number,length,start,end);

    //若枢轴不为middle
    while (index != middle)
    {
        //***注***（理解有难度）
        //若当前选择的 pivot（枢纽元素）位于中位数的索引（middle）的右侧
        //表示在数组的左半部分中存在中位数元素的候选。
        //因为排序后的数组中，中位数元素将位于数组的左半部分（索引小于 middle 的位置）
        //所以需要在左半部分继续搜索。
        
        if (index > middle)
        {
            end = index - 1;
            index=Partition(number,length,start,end);
        }
        else
        {
            start = index + 1;
            index = Partition(number,length,start,end);
        }
    }

    int result = number[index];

    return result;
}
#endif

//解法三：根据数组特点，找到相关数字的规律
//由于数组中有一个数字出现的次数超过数组长度的一半，
//也就是说它出现的次数比其他所有数字出现次数的和还要多
//我们遍历到下一个数字的时候，
//如果下一个数字和我们之前保存的数字相同，则次数加1。如果下一个数字
//和我们之前保存的数字不同，则次数减1。如果次数为零，那么我们需要保
//存下一个数字，并把次数设为1。由于我们要找的数字出现的次数比其他所
//有数字出现的次数之和还要多，那么要找的数字肯定是最后一次把次数设
//为1时对应的数字。
int MoreThanHalfNum(int* number, int length)
{
    if (number == nullptr || length <= 0)
        return 0;

    int result = number[0];
    int times = 1;

    for (int i = 1; i < length; ++i)
    {
        if (times == 0)
        {
            result = number[i];
            times = 1;
        }
        else if (number[i] == result)
            times++;
        else
            times--;
    }

    return result;
}
#endif


//面试题40：最小的k个数
#if 0
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

void FindSmallestSixNum(int* number,int length,int k);
void GetLeastNumbers(const vector<int>& data, int k);

int main()
{
    int data[] = {4,5,1,6,2,7,3,8};

    int k;
    cin >> k;

    FindSmallestSixNum(data,sizeof(data)/sizeof(int),k);

    cout << endl;
    vector<int> data_1 = {4, 5, 1, 6, 2, 7, 3, 8};
    GetLeastNumbers(data_1,k);

    return 0;
}

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//解法一：使用Partition函数
int Partition(int* number, int length, int begin, int end)
{
    if (number == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //1.取一个随机的索引值
    srand(time(0));
    int rd_index = begin + rand()%(end - begin + 1);

    //2.将随机索引值对应的值移到数组末尾，做为比较标尺
    Swap(&number[rd_index], &number[end]);

    //3.创建枢轴small存索引值
    int small = begin - 1;

    //4.遍历数组
    //***注***从第一个元素遍历到倒数第二个元素
    for (int index = begin; index < end; ++index)
    {
        if (number[index] <= number[end])
        {
            ++small;

            Swap(&number[index],&number[small]);
        }
    }

    //5.枢纽值再加1
    ++small;

    //6.原来随机的索引值对应的数字  回到  现在枢纽值代表的位置
    Swap(&number[small],&number[end]);

    //这样就确保了数组中索引值比枢纽值小的各个位置的值都比枢纽值对应的值要小（或等于）
    return small;
}

void FindSmallestSixNum(int* number, int length,int k)
{
    if (number == nullptr || length <= 0)
        return;

    int index = Partition(number,length,0,length-1);

    int start = 0;
    int end = length - 1;

    while (index != k - 1)
    {
        if (index <= k - 1)
        {
            //***必写如下语句***
            start = index + 1;

            index=Partition(number,length,start,end);
        }
        else
        {
            //***必写如下语句***
            end = index - 1;

            index = Partition(number, length, start, end);
        }
    }

    for (int i = 0; i <= index; ++i)
        cout << number[i] << " ";
}

//解法二：维护一个容器，【该容器要能在O(1)时间内查找到容器中的最大值】
//但需要O(logk)时间完成删除和插入操作。
//创建一个大小为k的数据容器来存储最小的k个数字，接下来每次
//从输入的n个整数中读入一个数。如果容器中已有的数字少于k个，
//则直接把这次读入的整数放入容器之中；如果容器中已有k个数字了，
//也就是容器已满，此时我们不能再插入新的数字而只能替换已有的数字。
// 找出这已有的k个数中的最大值，然后拿这次待插入的整数和最大值进行比
//较。如果待插入的值比当前已有的最大值小，则用这个数替换当前已有的
//最大值；如果待插入的值比当前已有的最大值还要大，那么这个数不可能是
//最小的k个整数之一，于是我们可以抛弃这个整数。
//此方法还适用于处理海量数据

//用基于红黑树的multiset实现
#if 1
void GetLeastNumbers(const vector<int>& data, int k)
{
    if (data.empty() || k <= 0)
        return;

    //***注***
    //set容器的元素默认从小到大存放，现改为由大到小存放
    multiset<int, greater<int>> intSet;

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (intSet.size() < k)
            intSet.insert(*it);
        else
        {
            if (*it < *intSet.begin())
            {
                intSet.erase(intSet.begin());
                intSet.insert(*it);
            }
        }
    }
    
	while (!intSet.empty())
	{
		cout << *intSet.rbegin() << " ";

        //写法1：
		//intSet.erase(--(intSet.rbegin().base()));
        //写法2：
		intSet.erase(next(intSet.rbegin()).base());
	}
}
//***注***
//begin()和cbegin()的区别：
//begin 将返回 iterator 或 const_iterator ，具体取决于调用它的对象的 const 限定。
//cbegin 将无条件返回 const_iterator

//如何在erase()方法中使用反向迭代器来删除元素？
//intSet.erase(intSet.rbegin());   //报错
//解决方法：
//需要应用偏移量base()  或者  next()
#endif

//用基于二叉堆的优先队列实现
#if 0
void GetLeastNumbers(const vector<int>& data, int k)
{
    if (data.empty() || k <= 0)
        return;

    //***注***
    //priority_queue容器的元素默认从大到小存放

    //***以下是改为由小到大存放***
    //priority_queue<int, vector<int>, greater<int>> pq;

    priority_queue<int> pq;

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (pq.size() < k)
            pq.push(*it);
        else
        {
            if (*it < pq.top())
            {
                pq.pop();
                pq.push(*it);
            }
        }
    }

    while (!pq.empty())
    {
        cout << pq.top() << " ";

        pq.pop();
    }

}
#endif
#endif


//面试题41：数据流中的中位数
//可以用数组配合快速排序算法
//可以用排序的链表
//可以用二叉搜索树，或其优化版AVL树（方法是利用中序遍历，将数据都存入数组中）
//但是AVL树实现难，考虑：
//如果能够保证数据容器左边的数据都小于右边的数据，那么即使左、右两边
//内部的数据没有排序，也可以根据
//【左边最大的数】及【右边最小的数】得到中位数。
//因此，要实现一个最大堆和最小堆
#if 0
#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T> 
class DynamicArray
{
private:
    vector<T> min;
    vector<T> max;

public:
    void insert(T num);
    T GetMedian(void);
};

template<typename T>
void DynamicArray<T>::insert(T num)
{
    //若当前最大堆和最小堆的元素个数之和为偶数（注：0也是偶数），
    //则将新数据插入到最小堆
    if (((max.size() + min.size()) & 0x1) == 0)
    {
        //若新数据比最大堆中的数据要小
        if (max.size() > 0 && num < max[0])
        {
            //可以先把这个新的数据插入最大堆，接着把最大堆中最大的数字拿出来
            //插入最小堆。由于【最终插入最小堆的数字是原最大堆中最大的数字】，这样
            //就保证了最小堆中所有数字都大于最大堆中的数字

            max.push_back(num);

            //函数对 [first, last) 范围内的迭代器指定的序列进行重新排序，
            //以形成按 operator< 排序的新堆。 [first, last - 1) 范围内的迭代器
            //必须指定一个现有堆，也按 operator< 排序。
            //因此， first != last 必须为 true，并且 *(last - 1) 是要添加到（推入）堆的元素。
            //若有第三个参数，则将用此函数进行比较
            push_heap(max.begin(),max.end(),less<T>());

            num = max[0];

            //交换在位置 first 的值和在位置 last-1 的值，并令子范围 [first, last-1) 变为堆。
            //这拥有从范围 [first, last) 所定义的堆移除首个元素的效果。
            pop_heap(max.begin(),max.end(),less<T>());
            //将最大堆中的最大值删去
            max.pop_back();
        }

        min.push_back(num);
        push_heap(min.begin(),min.end(),greater<T>());
    }
    else//否则，插入到最大堆
    {
        //若新数据比最小堆中的数据要大
        if (min.size() > 0 && num > min[0])
        {
            //可以先把这个新的数据插入最小堆，接着把最小堆中最小的数字拿出来
            //插入最大堆。由于最终插入最大堆的数字是原最小堆中最小的数字，这样
            //就保证了最大堆中所有数字都小于最小堆中的数字

            min.push_back(num);

            push_heap(min.begin(), min.end(), greater<T>());

            num = min[0];

            //交换在位置 first 的值和在位置 last-1 的值，并令子范围 [first, last-1) 变为堆。
            //这拥有从范围 [first, last) 所定义的堆移除首个元素的效果。
            pop_heap(min.begin(), min.end(), greater<T>());
            //将最小堆中的最小值删去
            min.pop_back();
        }

        max.push_back(num);
        push_heap(max.begin(), max.end(), less<T>());
    }
}

template<typename T>
T DynamicArray<T>::GetMedian(void)
{
    int size = max.size() + min.size();

    if (size == 0)
        throw exception("Error\n");

    T res;

    if ((size & 0x1) == 1)
        res = min[0];//因为最大堆和最小堆元素总和为偶数时，定义新数据插入到最小堆
    else                  //所以元素总数为奇数时，中位数在最小堆的首元素
        res = (max[0] + min[0]) / 2;//***注***double类型的话就没法用移位操作符了
                                                    //所以/2更有通用性
    return res;
}

int main()
{
    DynamicArray<double> numbers;

    numbers.insert(5);
    try
    {
        cout << numbers.GetMedian()<<endl;
    }
    catch (exception&)
    {
        cout << "failed" << endl;
    }

    numbers.insert(6);
    try
    {
        cout << numbers.GetMedian()<<endl;
    }
    catch (exception&)
    {
        cout << "failed" << endl;
    }

    numbers.insert(7);
    numbers.insert(8);
    numbers.insert(9);
    numbers.insert(10);
    try
    {
        cout << numbers.GetMedian()<<endl;
    }
    catch (exception&)
    {
        cout << "failed"<<endl;
    }

    return 0;
}
#endif


//面试题42：连续子数组的最大和
#if 0
#include <iostream>
#include <exception>
using namespace std;
int FindGreatestSum(int* pData, int length);

int main()
{
    int data[] = {1,-2,3,10,-4,7,2,-5};

    try
    {
        cout << FindGreatestSum(data,8);
    }
    catch(exception&)
    {
        cout << "Error!\n";
    }

    return 0;
}

int FindGreatestSum(int* pData, int length)
{
    if (pData == nullptr || length <= 0)
        throw exception();

    //int begin = 0;
    //int sum = pData[0];

    //for (int i = 1; i < length; ++i)
    //{
    //    if (sum + pData[i] > sum)
    //    {
    //        sum = sum + pData[i];
    //    }
    //    else
    //        ;
    //}

//难点：不知道应该从数组的第几个元素开始截取，到哪个元素就结束
//遍历到负数时只是暂时的会让sum值变小，但该负数后面的元素可能会让sum进一步变大
//该如何取舍？也不能用双指针思想做

//动态规划思想：
//状态方程：max( dp[ i ] ) = getMax(    max( dp[ i -1 ] ) + arr[ i ] ,    arr[ i ] )
//上面式子的意义是：我们从头开始遍历数组，遍历到数组元素 arr[i] 时，
//连续的最大的和可能为 max(dp[i - 1]) + arr[i] ，也可能为 arr[i] ，
//做比较即可得出哪个更大，取最大值。时间复杂度为 n。

    int sum = pData[0];
    int Max = pData[0];

    for (int i = 1; i < length; ++i)
    {
        //***注***
        //以下语句使sum能暂存求得的和的同时确定了从数组的第几个元素开始求和
        sum = max(sum+pData[i],pData[i]);

        Max = (sum >= Max) ? sum : Max;
    }
 
    return Max;
}
#endif


//面试题43：1~n整数中1出现的次数
#if 0
#include <iostream>
#include <exception>
#include <algorithm>
using namespace std;

int Numberof1(int n);
int Numberof1Core(const char* strN);

int main()
{
    int n;
    int cnt = 0;

    try
    {
        cin >> n;
        cnt = Numberof1(n);
    }
    catch(const char* ch)
    {
        do
        {
            cout << *ch;
            ch++;
        } while (*ch);
    }

    cout << cnt;

    return 0;
}
int Numberof1(int n)
{
    if (n < 1)
        throw "Error1 !\n";

    //先将数字数据转换成字符存储
    char strN[50]{'\0'};
    sprintf_s(strN,"%d",n);

    return Numberof1Core(strN);
}

int PowerBase10(unsigned int n)
{
    int result = 1;

    for (unsigned int i = 0; i < n; ++i)
        result *= 10;

    return result;
}

int Numberof1Core(const char* strN)
{
    if (strN==nullptr||*strN=='\0')
        return 0;

    //存储最高位的数字值，用于数字的分割。比如
    //数字n为21345那么，应分为1~1345和1346~11345和11346~21345
    //***注***
    //第二部分和第三部分，1的计数，理解有难度：
    //后两段中，后四位出现1的次数应该为2*( C4 1 )*10^3=8000
    //因为这个可以看作一个排列问题：
    //四位数字中出现1的排列。然后对于重复的数字，比如1101，
    //本应该去重只计算1次，但是由于我们算的是出现1的次数，1101出现3次，
    //而我们在千、百、个位各计一次是正好的。所以问题转化为：四位分别是1时，
    //其他位随便排列，记一次。

    int first = *strN - '0';

    int length = strlen(strN);

    if (length == 1 && first == 0)
        return 0;

    if (length == 1 && first > 0)
        return 1;

    // 假设strN是"21345"
    // numFirstDigit是数字10000-19999的第一个位中1的数目
    int numFirstDigit = 0;
    if (first > 1)
        numFirstDigit = PowerBase10(length - 1);
    else if (first == 1)
        numFirstDigit = atoi(strN + 1) + 1;

    // numOtherDigits是01346-21345除了第一位之外的数位中1的数目
    int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
    // numRecursive是1-1345中1的数目
    int numRecursive = Numberof1Core(strN + 1);

    return numFirstDigit + numOtherDigits + numRecursive;
}
#endif


//面试题44：数字序列中某一位的数字
#if 0
#include <iostream>
#include <cmath>
using namespace std;

char FindNumber(int n);

typedef struct
{
    int weishu;
    int yvxia;
}Data;

Data FindWeiShu(int n);

int main()
{
    int n;
    cin >> n;

    cout << FindNumber(n);

    return 0;
}

char FindNumber(int n)
{
    if (n < 0)
        throw exception();

    //第一步：
    //找到第n位数字应该在几位数之内
    //同时找到是该位数长度数字序列下的多少位
    Data data = FindWeiShu(n);

    //第二步：
    //计算某长度数字的起始数字
    int begin;
    if (data.weishu == 1)
        begin = 0;
    else
        begin= pow(10, data.weishu - 1);

    //第三步：
    //某长度下的数字的第x个数字
    int x_num = data.yvxia / data.weishu;
    //第x个数字的第几位
    int x_weishu_num = data.yvxia % data.weishu;

    char ch[50] = {'\0'};
    sprintf_s(ch, "%d", begin+x_num);

    return ch[x_weishu_num];
}

Data FindWeiShu(int n)
{
    int left = 0;
    int right = 1;
    int weishu = 1;

    //***注***0~9有10个数字
	n -= weishu * (pow(10, right) - pow(10, left)+1);

    while (n>=0)
    {
        ++right, ++left,++weishu;

		//                  位数*该位数下有几个数字
        int tmp= weishu * (pow(10, right) - pow(10, left));

        if (n - tmp >= 0)
        {
            n -= tmp;
        }
        else
            break;
    }

    Data data;
    data.weishu = weishu;
    data.yvxia = abs(n);//加abs是为了当n等于5时，yvxia成员得到的值为5而不是-5

    return data;
}
#endif


//面试题45：把数组排成最小的数
//解法：
//要确定一个规则判断m和n哪个应该排在前面，
//而不是仅仅比较这两个数字的值哪个更大。
//举例：
//两个数字m和n能拼接成数字mn和nm。如果mn<nm,
//那么我们应该打印出mn, 也就是m应该排在n的前面，我们定义此时m小于n; 
//反之，如果nm < mn, 则我们定义n小于m; 如果mn = nm, 则m等于n
#if 0
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include<exception>
using namespace std;
const int MaxLengthOfNum = 10;

void PrintMinNumber(const int* numbers, int length);
int mycompare(const void* a, const void* b);

int main()
{
    int array[] = {3,32,321};

    PrintMinNumber(array,sizeof(array)/sizeof(int));

    return 0;
}

void PrintMinNumber(const int* numbers, int length)
{
    if (numbers == nullptr || length < 1)
        throw exception();

    //***注***
    //为解决大数问题，需要将每个数字以字符的形式表示
    //创建指向字符数组的指针
    //错误写法：
    //char** strNumbers = new char[MaxLengthOfNum][length];
    //正确写法：
    char** strNumbers = new char* [length];

    for (int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[MaxLengthOfNum];

        sprintf(strNumbers[i], "%d", numbers[i]);
    }

    //然后，使用对字符的排序函数，对各字符进行排序。
    //***注***
    //qsort()函数，能对strNumbers所指向的数组以升序排序，
    //或按照自定义的比较方法来排序
    qsort(strNumbers,length,sizeof(char*),mycompare);

    char Print[MaxLengthOfNum];
    strncpy(Print,strNumbers[0],MaxLengthOfNum-1);
    Print[MaxLengthOfNum-1] = '\0';

    //***注***
    //strncat后附来自 src 所指向的字符数组的至多 count 个字符，
    //到 dest 所指向的空终止字节字符串的末尾，若找到空字符则停止
    //始终后附终止空字符到末尾（故函数可写入的最大字节数是 count+1 ）。
    int available = MaxLengthOfNum-strlen(Print)-1;

    if(length>1)
        for (int i = 1; i < length; ++i)
        {
            int Len = strlen(strNumbers[i]);
            if (available >= Len)
                strncat(Print,strNumbers[i],available);

            available -= Len-1;
        }

    cout << Print;

    //***注***
    //最后别忘了释放动态分配的内存
    //释放字符数组
    for (int i = 0; i < length; ++i)
    {
        delete [] strNumbers[i];
    }

    //释放字符数组指针组成的数组
    delete[] strNumbers;
}

int mycompare(const void* a, const void* b)
{
    //***注***
    //错误写法：
    //const char* arg1 = (const char*)a;
    //const char* arg2 = (const char*)b; 

    //***正确写法***
    //理解：qsort()函数的实现需要两个指向待排序数组的元素的指针
    //数组中的元素已经是指针，因此a和b就是指针的指针
    const char* arg1 = *(const char**)a;//先强制类型转换为指针的指针，再做解引用行为
    const char* arg2 = *(const char**)b;

    char* tmp1 = new char[MaxLengthOfNum];
    char* tmp2 = new char[MaxLengthOfNum];

    strcpy(tmp1,arg1);
    strcpy(tmp2,arg2);

    if (strlen(tmp1) + strlen(tmp2) >= MaxLengthOfNum)
        exit(1);

    strcat(tmp1,arg2);
    strcat(tmp2,arg1);

    int res=strcmp(tmp1,tmp2);

    if (res<0) 
        return -1;
    if (res>0) 
        return 1;

    return 0;

    // return (arg1 > arg2) - (arg1 < arg2); // 可行的简写
    // return arg1 - arg2; // 错误的简写（若给出 INT_MIN 则会失败）
}
#endif


//面试题46：把数字翻译成字符串
//思路：
//核心：条件判断版斐波那契数列（青蛙跳台问题），
//把翻译1个数字和翻译2个数字看成跳1阶和跳2阶，
//只有当数字匹配 >= 10且 <= 25时能跳2阶，dp[n] = dp[n - 1] + dp[n - 2] 
//否则最后只能跳1阶，因此与前一个结果相同，dp[n] = dp[n - 1]
#if 0
#include <iostream>
#include <string>
using namespace std;

int translate(int num);

int main()
{
    int num;
    cin >> num;

    cout << translate(num);

    return 0;
}
int translate(int num)
{
    if (num < 0)
        return -1;

    //***注***
    //用to_string()函数快速将数字值转化为字符存储
    string str = to_string(num);
      
    int Length = str.size();
    
    //***
    unique_ptr<int[]> dp(new int[Length+1]);

    //比如数字12有两种跳法，12能匹配字母，因此dp[2]=dp[1]+dp[0]
    //而因为数字为一位的时dp[1]=1，因此推出dp[0]=1
    dp[0] = 1;
    dp[1] = 1;

    if (Length == 1)
        return 1;

    //dp的索引值代表第几个数字，从第二个数字开始，即从dp[2]开始
    //那么str应截取第1个到第2个数字
    for (int i = 2; i <= Length; ++i)
    {
        string tmp = str.substr(i-2,2);//***注***i-2相当于是第i-1个数字开始，向后取两位

        if (tmp.compare("10") >= 0 && tmp.compare("25") <= 0)
            dp[i] = dp[i - 1] + dp[i - 2];
        else
            dp[i] = dp[i-1];
    }

    return dp[Length];
}
#endif


//面试题47：礼物的最大价值
//像是01背包问题，但又不是
//此题用动态规划来做
//4 4
//1 10 3 8
//12 2 9 6
//5 7 4 11
//3 7 16 5
#if 0
#include <iostream>
#include <vector>
using namespace std;

int GetMaxValue(vector<vector<int>>qipan,int rows, int cols);

int main()
{
    int row, col;
    cin >> row >> col;

    vector< vector<int>> qipan(row, vector<int>(col, 0));

    for (int r = 0; r < row; ++r)
        for (int c = 0; c < col; ++c)
            cin >> qipan[r][c];

    cout<<GetMaxValue(qipan,row,col);

    return 0;
}

int GetMaxValue(vector<vector<int>>dp, int rows, int cols)
{
    //因为是从左上角到右下角，方向只能是向右或者向下，
    // 所以可以对除了左上角的元素之外的元素
    //进行动态规划
    for(int row = 0; row<rows; ++row)
        for (int col = 0; col < cols; ++col)
        {
            if (row == 0 && col == 0)
                continue;

            if (row == 0)
            {
                dp[row][col] = max(dp[row][col], dp[row][col - 1] + dp[row][col]);
                continue;
            }
            if (col == 0)
            {
                dp[row][col] = max(dp[row][col], dp[row - 1][col] + dp[row][col]);
                continue;
            }

            dp[row][col] = max(dp[row-1][col]+dp[row][col], 
                dp[row][col - 1] + dp[row][col]);
        }

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            cout << dp[r][c] << '\t';
        }
        cout << endl;
    }

    return dp[rows-1][cols-1];
}

//解法二：只用一维数组作为辅助空间（空间上优化）
//在草稿纸上写写画画更易于理解
#if 0
int maxValue(vector<vector<int>>& grid) 
{
    int m = grid.size(), n = grid[0].size();

    vector<int> dp(n, 0);

    for (int i = 0; i < m; i++) 
    {
        //***注***dp[0]存的是到grid[i][0]处能获得的最大价值
        dp[0] += grid[i][0];

        for (int j = 1; j < n; j++) 
        {
            dp[j] = max(dp[j - 1], dp[j]) + grid[i][j];
        }
    }
    return dp[n - 1];
}
#endif
#endif


//面试题48：最长不含重复字符的子字符串
#if 0
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int LongestSubString(string& str);

int main()
{
    string str = {"arabcacfr"};

    cout << LongestSubString(str);

    return 0;
}

int LongestSubString(string& str)
{
    if (str == "")
        return -1;

    //创建curLength变量存当前模拟进程下的符合要求的长度
    //创建maxLength变量存最大符合要求的长度
    int curLength = 0, maxLength=0;

    //创建数组，存每个字符出现的位置
    unique_ptr<int[]>position(new int[26]);

    fill(position.get(), position.get() + 26, -1);

    for (int i = 0; i < str.length(); ++i)
    {
        //创建PreIndex表示某个字母上一次出现的位置
        //(第一次出现时，PrevIndex值为-1)
        int PrevIndex = position[str[i]-'a'];

        //若某个字母是第一次出现或者
        //【某字母的位置与某字母上一次出现的位置的距离
        // 大于当前记录的最长不含重复字符的字符串的长度】
        if (PrevIndex<0 || i - PrevIndex>curLength)
            ++curLength;
        else
        {
            //存储一下符合条件的最大长度
            if (curLength > maxLength)
                maxLength = curLength;

            //***注***
            //将curLength的值截短为两个相同的字符的距离之差
            curLength = i - PrevIndex;
        }

        //某字符上一次出现的位置用当前出现的位置代替
        position[str[i]-'a'] = i;
    }

	//存储一下符合条件的最大长度
    if (curLength > maxLength)
        maxLength = curLength;

    return maxLength;
}
#endif


//面试题49：丑数
#if 0
#include <iostream>
#include <vector>
using namespace std;

bool isUgly(int num);
int PrintTheCorrespondingUglyNumber(int WhichOne);
int PrintTheCorrespondingUglyNumber_improved(int WhichOne);

int main()
{
    int n;
    cin >> n;

    //cout<< PrintTheCorrespondingUglyNumber(n)<<endl;

    cout << PrintTheCorrespondingUglyNumber_improved(n) << endl;

    return 0;
}

bool isUgly(int num)
{
    //***错误写法***
    //if (num % 2 != 0)
    //    return false;
    //if (num % 3 != 0)
    //    return false;
    //if (num % 5 != 0)
    //    return false;

    //丑数只能被2、3或5整除
    while (num % 2 == 0)
        num >>=1;
    while (num % 3 == 0)
        num /= 3;
    while (num % 5 == 0)
        num /= 5;

    return num==1?true:false;
}
int PrintTheCorrespondingUglyNumber(int WhichOne)
{
    if (WhichOne <= 0)
        return -1;

    int number = 1;
    int cnt = 1;

    while (cnt != WhichOne)
    {
        ++number;

        if (isUgly(number))
            ++cnt;
    }

    return number;
}

int PrintTheCorrespondingUglyNumber_improved(int WhichOne)
{
	if (WhichOne <= 0)
		return 0;

	//int* pUglyNumbers = new int[WhichOne];

    //***注***
    //可以使用vector或智能指针来自动管理内存并避免潜在的内存泄漏
    vector<int> pUglyNumbers(WhichOne);

	pUglyNumbers[0] = 1;
	int nextUglyIndex = 1;

	//int* pMultiply2 = pUglyNumbers;
	//int* pMultiply3 = pUglyNumbers;
	//int* pMultiply5 = pUglyNumbers;

    //创建三个指针，这些指针用于
    //通过解引用后将当前丑数分别乘以 2、3 和 5 来跟踪下一个候选丑数
    vector<int> ::iterator pMultiply2;
    pMultiply2 = pUglyNumbers.begin();
    auto pMultiply3 = pUglyNumbers.begin();
    auto pMultiply5 = pUglyNumbers.begin();

	while (nextUglyIndex < WhichOne)
	{
		//int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
		//pUglyNumbers[nextUglyIndex] = min;

        //***难点***
        //以下语句是为了将丑数按从小到大的顺序生成并存储
        //需要和下面三个while语句块配合
		int Min = min(min(*pMultiply2 * 2, *pMultiply3 * 3), *pMultiply5 * 5);

		pUglyNumbers[nextUglyIndex] = Min;

        //通过将 *pMultiply2 所指向的数乘以2，检查是否小于等于
        //当前已生成的丑数序列中的最后一个数。
        //如果是，表示当前 *pMultiply2 所指向的数乘以2后不大于当前已生成的最大丑数，
        //因此需要将 *pMultiply2 指针向后移动一位，以便下一次计算
        
        //目的是确保生成的丑数序列是按照升序排列的。
        //通过不断地更新这三个指针，可以保证【下一个丑数是当前已生成
        //丑数序列中的某个数乘以2、3或5得到的最小值】
		while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
			++pMultiply2;
		while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
			++pMultiply3;
		while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
			++pMultiply5;

        //将指针移动并指向下一个丑数应填入的位置
		++nextUglyIndex;
	}

	int ugly = pUglyNumbers[nextUglyIndex - 1];

	return ugly;
}
#endif


//面试题50：第一个只出现一次的字符
#if 0
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void AppearOnlyOnce(const string& str);

int main()
{
    string str;
    cin >> str;

    AppearOnlyOnce(str);

    return 0;
}

#if 0
void AppearOnlyOnce(const string& str)
{
    if (str == "")
        return;

    unordered_map<char, int> hash;

    for (auto i = str.begin(); i != str.end(); ++i)
    {
        //时间复杂度：O(1)
        if (hash.find(*i) == hash.end())
            hash.insert(make_pair(*i, 1));
        else
            ++(hash[*i]);
    }

    for (auto i = str.begin(); i != str.end(); ++i)
    {
        if (hash[*i] == 1)
        {
            cout << *i << " ";
            
            return;
        }
    }
	
    cout << "none !" << endl;

    return;
}
#endif

//法二：维护一个基于数组的简易哈希表
#if 1
void AppearOnlyOnce(const string& str)
{
    if (str == "")
        return;

    //大到足够容下所有ASCII字符对应的值
    const int Size = 256;
    int hashTable[Size] = {0};

    for (auto it = str.begin(); it != str.end(); ++it)
    {
        ++hashTable[*it];
    }

    for (auto it = str.begin(); it != str.end(); ++it)
    {
        if(hashTable[*it]==1)
        {
            cout << *it;
            return;
        }
    }

    cout << "None!";
    return;
}
#endif
#endif


//归并排序
#if 0
#include <iostream>
#include <vector>

using namespace std;

void MergeSort(vector<int>& Array, int front, int end);
void Merge(vector<int>& Array, int front, int mid, int end);

int main()
{
    vector<int> vec{ 3,5,1,2,8,5 };

    MergeSort(vec, 0, vec.size() - 1);

    for (auto x : vec)
        cout << x << " ";

    return 0;
}

//                                                      front ,end 均为索引值
void MergeSort(vector<int>& Array, int front, int end)
{
    //当前子数组中有零个或一个元素，并且它已经排序
    if (front >= end)
        return;

    int mid = front + (end - front) / 2;

    //MergeSort()递归地将数组划分为更小的子数组，直到它们被排序，
    MergeSort(Array, front, mid);
    MergeSort(Array, mid + 1, end);
    //然后使用 Merge 函数将它们合并在一起
    Merge(Array, front, mid, end);
}

void Merge(vector<int>& Array, int front, int mid, int end)
{
    // preconditions:
    // Array[front...mid] is sorted
    // Array[mid+1 ... end] is sorted
    // Copy Array[front ... mid] to LeftSubArray
    // Copy Array[mid+1 ... end] to RightSubArray
    vector<int> LeftSubArray(Array.begin() + front, Array.begin() + mid + 1);
    vector<int> RightSubArray(Array.begin() + mid + 1, Array.begin() + end + 1);

#if 0

    //在合并之前将 numeric_limits<int>::max() 附加到 Left 和 Right 子数组的末尾，
    //numeric_limits<int>::max() 是整型中的最大值，
    //在合并过程中它充当了一个标记来表示子数组的结束。
    //可以确保在合并过程中，当元素进行比较和合并时，算法不需要检查它是否
    //已到达任何子数组的末尾。 max() 哨兵值充当合并过程中的自然停止点，
    //防止索引越界错误并简化合并逻辑
    LeftSubArray.insert(LeftSubArray.end(), numeric_limits<int>::max());
    RightSubArray.insert(RightSubArray.end(), numeric_limits<int>::max());

    //我们这里以第一次拆分的两个分组为例，其实也就是归并的最后一步。
    //第一次拆分之后的两个序列就是[3 5 1]和[2 8 5]了；
    //但是大家要注意，我们在对这两个序列进行归并时，他们应该是早就排好序了！
    //因为是递归拆分，在最后一次拆分的时候序列都是单独的元素，所以到归并的最后一步时，
    //也就是左边的序列应该是[1 3 5]，右边的序列应该是[2 5 8]
    // Pick min of LeftSubArray[idxLeft] and RightSubArray[idxRight], and put into Array[i]
    //取LeftSubArray[idxLeft]和RightSubArray[idxRight]中的min，即较小者，放入Array[i]中
    int idxLeft = 0, idxRight = 0;
    for (int i = front; i <= end; i++)
    {
        if (LeftSubArray[idxLeft] < RightSubArray[idxRight])
        {
            Array[i] = LeftSubArray[idxLeft];
            idxLeft++;
        }
        else
        {
            Array[i] = RightSubArray[idxRight];
            idxRight++;
        }
        //***注***
        //哨兵值：2147483647充当合并过程中的自然停止点，
        //防止vector的索引越界错误并简化合并逻辑
    }

#endif

#if 1
    //不使用哨兵值的合并过程
    int n1 = mid - front + 1;  //n1值为前半段的元素个数
    int n2 = end - mid;          //n2为后半段的元素个数

    int i = 0, j = 0, k = front;

    while (i < n1 && j < n2)
    {
        if (LeftSubArray[i] <= RightSubArray[j])
        {
            Array[k] = LeftSubArray[i];
            i++;
        }
        else
        {
            Array[k] = RightSubArray[j];
            j++;
        }
        k++;
    }

    // 将剩余元素复制回数组
    while (i < n1)
    {
        Array[k] = LeftSubArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        Array[k] = RightSubArray[j];
        j++;
        k++;
    }

#endif
}
#endif


//面试题51：数组中的逆序对
//将某个数字拿出并和后面的每个数字相比较，时间复杂度是O(n^2)
//思路：
//第一步：把数组分隔成子数组，统计出子数组内部的逆序数对数
//第二步：统计两个相邻子数组之间的逆序数对数，并要进行排序
//此排序为【归并排序】
#if 0
#include <iostream>

using namespace std;

int InversePairs(int* data,int length);
int InversePairsCore(int* data,int* copy, int istart, int iend);

int main()
{
    int data[] = {7,5,6,4};

    cout << InversePairs(data,sizeof(data)/sizeof(int));

    return 0;
}
int InversePairs(int* data, int length)
{
    if (data == nullptr||length<=0)
        return -1;

    //创建由智能指针管理的copy数组，存输入数组的备份内容（副本）
    unique_ptr<int[]>copy(new int [length]);

    for (int i = 0; i < length; ++i)
        copy[i] = data[i];

    int cnt = InversePairsCore(data,copy.get(), 0,length-1);

    return cnt;
}
int InversePairsCore(int* data, int* copy, int startindex, int endindex)
{
    if (startindex == endindex)
    {
        copy[startindex] = data[startindex];
        return 0;
    }

    //length存计算得到的数组长度的一半
    int length = (endindex - startindex) / 2;

    //将数组分隔成两个子数组
    int left = InversePairsCore(copy,data,startindex,startindex+length);
    //对于左子数组，运行到  int end = ...  时
    //最终startIndex为0，endIndex为1，length为0
    //即已经分隔到了仅为两个元素的子数组
    int right = InversePairsCore(copy,data,startindex+length+1,endindex);
    //子数组仅含两个元素时，执行上面的InversePairsCore()后，会跳入第一个if
    //语句块中的return，然后跳回，上面的InversePairsCore()处理右子数组
    //右子数组也会分隔成左右子数组

    //变量i表示【前半段】最后一个元素的索引位置
    int i = startindex + length;
    //变量j表示【后半段】最后一个元素的索引位置
    int j = endindex;

    int indexCopy = endindex;

    int cnt = 0;

    while (i >= startindex && j >= startindex + length + 1)
    {
        //若第一个子数组中的数字大于第二个子数组中的数字，则
        //构成逆序数对，逆序数对数等于第二个子数组中剩余数字的个数
        if (data[i] > data[j])
        {
            cnt += j - startindex - length;

            //将较大的数字从后往前复制到辅助数组
            copy[indexCopy] = data[i];

            --indexCopy, --i;
        }
        else
        {
            copy[indexCopy] = data[j];

            --indexCopy, --j;
        }
    }

    // 将剩余元素复制回数组
    for (;i >= startindex; --i)
        copy[indexCopy--] = data[i];

    for (;j >= startindex+length+1; --j)
        copy[indexCopy--] = data[j];

     //逆序数对数等于子数组内部的逆序数对数和两个相邻子数组之间的逆序数对数
    return cnt+left + right ;
}
#endif


//面试题52：两个链表的第一个公共节点
#if 0
#include <iostream>
#include "List.h"
#include <exception>
#include <stack>
#include <cmath>
using namespace std;

ListNode* FindFirstCommonNode(const ListNode* pNode1,const ListNode* pNode2);

int main()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);
    ListNode* pNode6 = CreateListNode(6);
    ListNode* pNode7 = CreateListNode(7);

// 第一个公共结点在链表中间
// 1 - 2 - 3  \
//                 6 - 7
//     4 - 5   /
    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode6);

    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);
    ConnectListNodes(pNode6, pNode7);

    cout<<FindFirstCommonNode(pNode1, pNode4)->m_nValue;

    return 0;
}

//普通方法：
//第一链表上顺序遍历每个节点，每遍历到一个节点，就在第二个链表上顺序遍历每个节点。
//如果在第二个链表上有一个节点和第一个链表上的节点一样，
//则说明两个链表在这个节点上重合。时间复杂度O(mn)
//优化解法：
//观察合并后和合并前两个链表的状态，得到
//合并后两个链表的所有节点都是重合的，那么只要【从末尾开始】
//向前比较，最后一个相同的节点就是第一个公共节点
//如何从末尾开始比较？
//考虑数据结构——>栈        时间复杂度O(m+n)
#if 0
ListNode* FindFirstCommonNode(const ListNode* pNode1, const ListNode* pNode2)
{
    if (pNode1 == nullptr || pNode2 == nullptr)
        throw exception();

    stack<ListNode*> AuxStk1;
    stack<ListNode*> AuxStk2;
    
    ListNode* tmpListNode = const_cast<ListNode*>(pNode1);

    while (tmpListNode != nullptr)
    {
        AuxStk1.push(tmpListNode);

        tmpListNode = tmpListNode->m_pNext;
    }

    tmpListNode = const_cast<ListNode*>(pNode2);

    while (tmpListNode != nullptr)
    {
        AuxStk2.push(tmpListNode);

        tmpListNode = tmpListNode->m_pNext;
    }

    bool flag = false;
    ListNode* FirstCommonNode = nullptr;

    while ((AuxStk1.top())->m_nValue == (AuxStk2.top())->m_nValue)
    {
        flag = true;
        FirstCommonNode = AuxStk1.top();

        AuxStk1.pop(), AuxStk2.pop();
    }

    if (!flag)
        cout << "No match!"<<endl;

    return FirstCommonNode;
}
#endif

//解法二：
//再次观察两个将在某一节点及其之后开始合并的链表
//除了可以从后向前遍历，找到最后一个公共的节点，还可以选择
//仍从前向后遍历，在较长的链表上先遍历几个节点，然后两个节点一同向后遍历
//找到第一个相同的节点，该方法与用栈的方法时间复杂度相同
#if 1
ListNode* FindFirstCommonNode(const ListNode* pNode1, const ListNode* pNode2)
{
    if (pNode1 == nullptr || pNode2 == nullptr)
        throw exception();

    int length_1=0;
    int length_2 = 0;

    ListNode* tmpListNode = const_cast<ListNode*>(pNode1);

    while (tmpListNode != nullptr)
    {
        ++length_1;
        tmpListNode = tmpListNode->m_pNext;
    }

    tmpListNode = const_cast<ListNode*>(pNode2);
    while (tmpListNode != nullptr)
    {
        ++length_2;
        tmpListNode = tmpListNode->m_pNext;
    }

    int difLength=abs(length_1-length_2);

    ListNode* tmpListNodeAnother;

    if(length_2>=length_1)
    {
        while (difLength--)
        {
            tmpListNode = tmpListNode->m_pNext;
        }

        tmpListNodeAnother = const_cast<ListNode*>(pNode1);
    }
    else
    {
        tmpListNode = const_cast<ListNode*>(pNode1);

        while (difLength--)
        {
            tmpListNode = tmpListNode->m_pNext;
        }

        tmpListNodeAnother = const_cast<ListNode*>(pNode2);
    }

	while (tmpListNode != nullptr && (tmpListNode->m_nValue != tmpListNodeAnother->m_nValue))
	{
		tmpListNode = tmpListNode->m_pNext;
		tmpListNodeAnother = tmpListNodeAnother->m_pNext;
	}

	if (tmpListNode == nullptr)
	{
		cout << "None!";
		return nullptr;
	}
	else
		return tmpListNode;
}
#endif
#endif


//面试题53：在排序数组中查找数字出现的次数
#if 0
#include <iostream>

using namespace std;

int AppearTimes(int* ,int length,int num);
int GetFirstK(int*, int length,int k,int begidx,int endidx);
int GetLastK(int*, int length,int k,int begidx,int endidx);

int main()
{
    int data[] = {1,2,3,3,3,3,4,5};
    int k = 6;

    try
    {
        cout << AppearTimes(data, sizeof(data) / sizeof(int), k);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    };

    return 0;
}

//一般的解法，时间复杂度为O(n)
//有更快的解法，即用【变异的二分法】确定第一个k的位置和最后一个k的位置
//这样，时间复杂度可以降到O(logn)
int AppearTimes(int* data, int length, int k)
{
    if (data == nullptr || length <= 0)
        throw exception("Error input!\n");

    int First = GetFirstK(data, length, k, 0, length - 1);
    int Last = GetLastK(data, length, k, 0, length - 1);

    //***注***
    //注意程序的【完整性】
    //即要考虑数组中没有要查找的数字的情况
    if (First == -1 || Last == -1)
        throw exception("no matched number!");

    return Last - First + 1;
}

int GetFirstK(int*data, int length, int k, int begidx, int endidx)
{
    if (begidx > endidx)
        return -1;

    int middleidx = begidx+(endidx-begidx) / 2;
    int middledata = data[middleidx];

    //***注***
    //使用变异的二分法，确定k第一次出现的索引值
    
    //若中间的数字就是所要计算出现次数的数字
    //如果中间数字等于k呢?我们需要判断这个k是不是最后一个k, 
    //也就是中间数字的下一个数字是不是也等于k。如果下一个数字不是k, 
    //则中间数字就是最后一个k；否则下一轮我们还是要在数组的后半段中去查找。
    if (middledata == k)
    {
        //判断该数字是不是第一个数字，判断该中间数字的前一个数字是不是还是k
        if (middleidx == 0 || data[middleidx - 1] != k)
            return middleidx;
        else
            endidx = middleidx - 1;
    }
    else if (middledata > k)
        endidx = middleidx - 1;
    else
        begidx = middleidx + 1;

    //递归寻找
    return GetFirstK(data,length,k,begidx,endidx);

    //***注***
    //此语句块有两个return
}
int GetLastK(int*data, int length, int k, int begidx, int endidx)
{
    if (begidx > endidx)
        return -1;

    int middleidx = begidx+(endidx - begidx) / 2;
    int middledata = data[middleidx];

    //***注***
    //使用变异的二分法，确定k最后一次出现的索引值

    //若中间的数字就是所要计算出现次数的数字
    if (middledata == k)
    {
        //判断该数字是不是最后一个数字，判断该中间数字的后一个数字是不是还是k
        if (middleidx == endidx || data[middleidx + 1] != k)
            return middleidx;
        else
            begidx = middleidx + 1;
    }
    else if (middledata > k)
        endidx = middleidx - 1;
    else
        begidx = middleidx + 1;

    //递归寻找
    return GetLastK(data, length, k, begidx, endidx);
}
#endif


//0~n-1中缺失的数字
//一个长度为n-1的递增排序数组中的所有数字都是唯一的，
//并且每个数字都在范围0～n - 1之内，
//在范围0～n-1内的n个数字中有且只有一个数字不在该数组中。
// 解释：
//【本来】在范围0～n-1内的n个数字，
//【现在】在范围0~n内的n个数字，【可以得出】有且只有一个数字不在该数组中。
//相当于说每个数字原来应该与其索引值是一一对应的
//可以用二分查找法，找与索引值不对应的数字
#if 0
#include <iostream>

using namespace std;

int FindTheNumber(int* ,int length);

int main()
{
    //长度为n-1=12   n=13
    //每个数字在0~12之内
    int data [12] = {0,1,2,3,5,6,7,8,9,10,11,12};

    cout << FindTheNumber(data,sizeof(data)/sizeof(int))<<endl;

    int data_1[] = { 0,1,2,3,4,5,7};

    cout << FindTheNumber(data_1, sizeof(data_1) / sizeof(int))<<endl;

    return 0;
}
int FindTheNumber(int* data, int length)
{
    if (data == nullptr || length <= 0)
        return -1;

    int begidx, endidx, mididx;
    begidx = 0, endidx = length - 1, mididx = begidx + (endidx - begidx) / 2;

    while (begidx <= endidx)
    {
        if (data[mididx] > mididx && data[mididx - 1] == mididx - 1)
            return mididx;
        else if(data[mididx] > mididx)
        {
            endidx = mididx - 1;
        }
        else//data[mididx]==mididx 的情况
        {
            begidx = mididx + 1;
        }

        mididx = begidx + (endidx - begidx) / 2;
    }

    return -1;
}
#endif
//***注***
//二分法可以由递归或者循环来表示


//数组中数值和下标相等的元素
#if 0
#include <iostream>

using namespace std;

int FindValueEqualIndex(int* data,int length);

int main()
{
    int data[] = {-3,-1,1,3,5};

    try 
    {
		cout<<FindValueEqualIndex(data, sizeof(data) / sizeof(int));
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}
int FindValueEqualIndex(int* data, int length)
{
    if (data == nullptr || length <= 0)
        throw exception("Error data!\n");

    int begidx, endidx, mididx;
    begidx = 0, endidx = length - 1, mididx = begidx + (endidx - begidx) / 2;

    while (begidx <= endidx)
    {
        if (data[mididx] < mididx)
        {
            begidx = mididx + 1;
        }
        else if (data[mididx] > endidx)
        {
            endidx = mididx - 1;
        }
        else
            return data[mididx];

        mididx = begidx + (endidx - begidx) / 2;
    }

    throw exception("No matched data!\n");
}
#endif
//***注***
//总结：单调递增或单调递减的数组，查找特定数据可以用二分法或变异二分法，减小时间复杂度


//面试题54：二叉搜索树的第k大节点（***题目意思是寻找第k小的节点***）
//思路：考察的是中序遍历（左根右）
#if 0
#include <iostream>
#include "Tree.h"
#include <iomanip>
using namespace std;

BinaryTreeNode* FindTheKLargestNode(BinaryTreeNode* pBTNode,int k);
BinaryTreeNode* FindTheKLargestNodeCore(BinaryTreeNode* pBTNode, int& k);

int main()
{
    BinaryTreeNode* p1 = CreateBinaryTreeNode(5);
    BinaryTreeNode* p2 = CreateBinaryTreeNode(3);
    BinaryTreeNode* p3 = CreateBinaryTreeNode(7);
    BinaryTreeNode* p4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* p5 = CreateBinaryTreeNode(4);
    BinaryTreeNode* p6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* p7 = CreateBinaryTreeNode(8);

    ConnectTreeNodes(p1,p2,p3);
    ConnectTreeNodes(p2,p4,p5);
    ConnectTreeNodes(p3,p6,p7);

    int k = 3;
    BinaryTreeNode* tmp = FindTheKLargestNode(p1,k);

    cout<<noshowpoint;
    setprecision(0);
    if (tmp != nullptr)
        cout << tmp->m_dbValue << endl;

    DestroyTree(p1);

    return 0;
}
BinaryTreeNode* FindTheKLargestNode(BinaryTreeNode* pBTNode,int k)
{
    if (pBTNode == nullptr||k<=0)
        throw exception("Error data!\n");

    return FindTheKLargestNodeCore(pBTNode,k);
}

//***注***   使用的是k的引用，就是说操作的是原来的k
BinaryTreeNode* FindTheKLargestNodeCore(BinaryTreeNode* pBTNode, int& k)
{
    //自己想的解法：
    //将排序二叉树进行中序遍历，将指向各节点的指针和该节点的值存入map容器
    //再根据要求返回第k大的节点

    //书上解法：
    //寻找第k小的节点，

    BinaryTreeNode* target = nullptr;

    if (pBTNode->m_pLeft != nullptr)
        target = FindTheKLargestNodeCore(pBTNode->m_pLeft,k);

    //遍历到二叉树最左边的节点时
    if (target == nullptr)
    {
        if (k == 1)
            target = pBTNode;

        --k;
    }
    //***注***
    //通过递减k的值，得到第k小的节点的指针

    //若还没找到，就往右子树找
    if (target == nullptr && pBTNode->m_pRight != nullptr)
        target = FindTheKLargestNodeCore(pBTNode->m_pRight,k);

    return target;
}
//***注***
//该算法只能得到第k小，不能改进以得到第k大的节点
#endif


//面试题55：二叉树的深度
//deep = log2(num) + 1;//***注***n个节点求深度公式 
#if 0
#include <iostream>
#include <cmath>
#include "Tree.h"
using namespace std;

int CalDepth(BinaryTreeNode* pNode);
int CalNodes(BinaryTreeNode* pNode);

int main()
{
    BinaryTreeNode* p1 = CreateBinaryTreeNode(5);
    BinaryTreeNode* p2 = CreateBinaryTreeNode(3);
    BinaryTreeNode* p3 = CreateBinaryTreeNode(7);
    BinaryTreeNode* p4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* p5 = CreateBinaryTreeNode(4);
    BinaryTreeNode* p6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* p7 = CreateBinaryTreeNode(8);

    ConnectTreeNodes(p1, p2, p3);
    ConnectTreeNodes(p2, p4, p5);
    ConnectTreeNodes(p3, p6, p7);

    try
    {
        cout << CalDepth(p1);
    }
    catch(exception& e)
    {
        cout << e.what();
    };

    DestroyTree(p1);

    return 0;
}

//解法一：
//计算节点个数，再计算深度
#if 0
int CalDepth(BinaryTreeNode* pNode)
{
    if (pNode == nullptr)
        throw exception("No data!\n");

    int cntNodes = CalNodes(pNode);

    return log2(cntNodes) + 1;
}
int CalNodes(BinaryTreeNode* pNode)
{
    //***注***
    //要记忆：
    if (!pNode)
        return 0;
    return CalNodes(pNode->m_pLeft) + CalNodes(pNode->m_pRight) + 1;

    //可以对照面试题13
}
#endif

//解法二：
//从另外一个角度来理解树的深度。如果一棵树只有一个节点，那么它的深度为1。
//如果根节点只有左子树而没有右子树，那么树的深度应该是其左子树的深度加1; 
//同样，如果根节点只有右子树而没有左子树，那么树的深度应该是其右子树的深度加1。
//如果既有右子树又有左子树，那么该树的深度就是其左、右子树深度的较大值再加1。
#if 1
int CalDepth(BinaryTreeNode* pNode)
{
    if (pNode == nullptr)
        return 0;

    int nleft = CalDepth(pNode->m_pLeft);
    int nright = CalDepth(pNode->m_pRight);

    return  (nleft > nright) ? (nleft + 1) : (nright + 1);
}
#endif
#endif


//判断是否为平衡二叉树
//如果某二叉树中任意节点的左、右子树的深度相差不超过1, 那么它就是一棵平衡二叉树。
#if 0
#include <iostream>
#include "Tree.h"
using namespace std;

int CalDepth(BinaryTreeNode* pNode);

bool JudgeTheTree(BinaryTreeNode* pNode);
bool JudgeTheTreeCore(BinaryTreeNode* pNode);

bool JudgeTheTree(BinaryTreeNode* pNode, int* pDeep);

int main()
{
    BinaryTreeNode* p1 = CreateBinaryTreeNode(5);
    BinaryTreeNode* p2 = CreateBinaryTreeNode(3);
    BinaryTreeNode* p3 = CreateBinaryTreeNode(7);
    BinaryTreeNode* p4 = CreateBinaryTreeNode(2);
    BinaryTreeNode* p5 = CreateBinaryTreeNode(4);
    BinaryTreeNode* p6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* p7 = CreateBinaryTreeNode(8);

    ConnectTreeNodes(p1, p2, p3);
    ConnectTreeNodes(p2, p4, p5);
    ConnectTreeNodes(p3, p6, p7);

    cout << JudgeTheTree(p1);

    DestroyTree(p1);

    return 0;
}

#if 0
bool JudgeTheTree(BinaryTreeNode* pNode)
{
    if (pNode == nullptr)
        return false;

    return JudgeTheTreeCore(pNode);
}
bool JudgeTheTreeCore(BinaryTreeNode* pNode)
{
    //已经遍历到叶子结点
    if (pNode == nullptr)
        return true;

    int Left = CalDepth(pNode->m_pLeft);
    int Right = CalDepth(pNode->m_pRight);

    if (abs(Left - Right) > 1)
        return false;

    return JudgeTheTreeCore(pNode->m_pLeft) && JudgeTheTreeCore(pNode->m_pRight);
}

int CalDepth(BinaryTreeNode* pNode)
{
    if (pNode == nullptr)
        return 0;

    int nleft = CalDepth(pNode->m_pLeft);
    int nright = CalDepth(pNode->m_pRight);

    return  (nleft > nright) ? (nleft + 1) : (nright + 1);
}
#endif
//上述代码的问题是
//会导致一个节点被遍历多次，时间效率不高

//更好的解法：
//使用【后序遍历】
//在遍历到一个节点之前我们就已经遍历了它的左、右子树。只要在遍历每个节点的时候
//记录它的深度(某一节点的深度等于它到叶节点的路径的长度), 我们就可以一边遍历
//一边判断每个节点是不是平衡的。
bool JudgeTheTree(BinaryTreeNode* pNode)
{
    int depth = 0;
    return JudgeTheTree(pNode,&depth);
}

bool JudgeTheTree(BinaryTreeNode* pNode,int* pDeep)
{
    if (pNode == nullptr)
    {
        *pDeep = 0;
        return true;
    }

    int left, right;

    //在递归地进行后序遍历时，同时得到某一节点的深度，也就判断了一棵树是不是平衡二叉树
    if (JudgeTheTree(pNode->m_pLeft, &left) && JudgeTheTree(pNode->m_pRight, &right))
    {
        if (abs(left - right) <= 1)
        {
            *pDeep = 1 + (left>right?left:right);
            return true;
        }
    }

    return false;
}
#endif


//面试题56：数组中数字出现的次数
//一个整型数组里除两个数字之外，其他数字都出现了两次。请写程序
//找出这两个只出现一次的数字。要求时间复杂度是O(n), 空间复杂度是O(1)。

//思路：
//考虑某个数组只有一个数字出现了一次，而其他数字都出现了两次。
//那么找出这个数字可以用异或做。
//现在的问题转化为如何将给出的数组分成两个子数组，
//而且两个子数组均只有一个数字出现了一次，而其他数字都出现了两次。
//可以照常从头到尾对每个数字进行异或运算，最终得到的结果为
//两个仅出现一次的数字的异或值
//那么可以寻找该值的第一个为1的位置，对每个数字的该位都进行判断
//因为两个相同的数字的任意一位都是相同的，我们不可能把两个相同的数字分配到两个子数组中去
//所以得到两个子数组
//每个子数组仅有一个数字出现一次，而其他数字都出现了两次。
#if 0
#include <iostream>

using namespace std;

void FindCorrespondingNums(int* data,int length);
inline int Cal_XOR(int* data, int length);
inline int FindTheFirstBitIs1(int num);

int main()
{
    int data[] = {2,4,3,6,3,2,5,5};

    try
    {
		FindCorrespondingNums(data, sizeof(data) / sizeof(int));
    }
    catch (exception& e)
    {
        cout << e.what();
    }

    return 0;
}
void FindCorrespondingNums(int* data, int length)
{
    if (data == nullptr || length <= 0)
        throw exception("Error!");

    int cal_xor = Cal_XOR(data,length);

    int wei = FindTheFirstBitIs1(cal_xor);

    //错误写法：
    //int basis_of_determination = 0x80000000;
    //while (wei--)
    //    basis_of_determination >>= 1;
    //负数进行左移时，最高位还是1

    int basis_of_determination = 0x40000000;
    while (wei!=1)
    {
        basis_of_determination >>= 1;
        --wei;
    }

    int num1 = 0;//与0异或值不变，所以初值设置为0
    int num2 = 0;
    for (int i = 0; i < length; ++i)
    {
        if (data[i] & basis_of_determination)//***注***
            num1 ^= data[i];                      //两个只出现一次的数字，两个数字一定不相同
        else                                               //所以一定可以满足一个某位为1，另一个某位为0
            num2 ^= data[i];
    }

    cout << num1 << "\t" << num2 << endl;

    return;
}

inline int Cal_XOR(int* data, int length)
{
    int num = 0;

    while (length--)
    {
        num ^= data[length];
    }

    return num;
}

inline int FindTheFirstBitIs1(int num)
{
    //INT_MAX为2147483647，即01111111111111111111111111111111
    // 
    //***注***
    //参考面试题15
    int flag = 0x40000000;      //即01000000000000000000000000000000

    int wei_index = 1;

    int tmp = flag & num;
    while (!tmp)
    {
        flag >>= 1;

        tmp = flag & num;
        ++wei_index;
    }

    return wei_index;
}
//***注***
//也可以改为寻找二进制数字最后一个为1的位的位置
#if 0
unsigned int FindTheFirstBitIs1(int num)
{
    int indexBit = 0;
    while (((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
    {
        num = num >> 1;
        ++indexBit;
    }

    return indexBit;
}
#endif
#endif


//数组中唯一只出现一次的数字
//在一个数组中除一个数字只出现一次之外，其他数字都出现了三次。
//请找出那个只出现一次的数字。

//思路：
//位异或可以处理出现两次的数字，但不能处理出现三次的数字。
//继续用位运算的想法：
//如果一个数字出现三次，那么它的二进制表示的每一位(0或者1)
//也出现三次。如果把所有出现三次的数字的二进制表示的每一位都分别
//加起来，那么每一位的和都能被3整除。
#if 0
#include <iostream>

using namespace std;

void FindCorrespondingNums(int* data, int length);

int main()
{
    int data[] = { 2,4,3,6,3,2,5,5,2,3,5 };

    try
    {
        FindCorrespondingNums(data, sizeof(data) / sizeof(int));
    }
    catch (exception& e)
    {
        cout << e.what();
    }

    return 0;
}
void FindCorrespondingNums(int* data, int length)
{
    if (data == nullptr || length <= 0)
        throw exception("Error!");

    int bitArray[32] = { 0 };

    //遍历数组中的数字，将数字的二进制表示的每一位都分别加起来
    for (int i = 0; i < length; ++i)
    {
		int mask = 1;
        for (int j = 31; j >= 0; --j)
        {
            if (mask & data[i])
                ++bitArray[j];

            mask <<= 1;
        }
    }

    int res = 0;
    for (int j = 31; j >= 0; --j)
    {
        if(bitArray[j]%3!=0)//仅出现一次的数字，对3取余一定不为0
        {
            int tmp = 1;
            tmp <<= 31 - j;

            res |= tmp;//***注***通过  或运算  或者  异或运算  来得到符合的数字
        }
    }

//得到符合数字法二：
#if 0
    int result = 0;
    for (int i = 0; i < 32; ++i)
    {
        result = result << 1;
        result += bitArray[i] % 3;
    }

#endif

    cout << res << endl;

    return;
}
#endif


//面试题57：和为s的数字
//输入一个递增排序的数组和一个数字s，在数组中查找两个数，
//使得它们的和正好是s。如果有多对数字的和等于s, 则输出任意一对即可。
#if 0
#include <iostream>

using namespace std;

void FindTwoNumbers(int* data, int length,int s);

int main()
{
    int data[] = {1,2,4,7,11,15};
    int s = 15;

    try
    {
		FindTwoNumbers(data, sizeof(data)/sizeof(int), s);
    }
    catch(exception& e)
    {
        cout<<e.what();
    }

    return 0;
}
void FindTwoNumbers(int* data, int length,int s)
{
    if (data == nullptr || length <= 0)
        throw exception("Error!");

    //***思路***
    //利用已经递增排序的数组这一条件
    //用双指针思想，结合二分法的截取数据段的条件判断来做

    int begidx, endidx;
    begidx = 0, endidx = length - 1;
    int tmp;

    while (begidx < endidx)
    {
		tmp = data[begidx] + data[endidx];

        if (tmp == s)
        {
			cout << data[begidx] << " " << data[endidx] << endl;

            return;
        }
        else if (tmp > s)
            --endidx;
        else
            ++begidx;
    }

    cout << "No matched number(s) !\n";

    return;
}
#endif


//输入一个正数s，打印出所有和为s的连续正数序列(至少含有两个数)。
//例如，输入15, 由于1 + 2 + 3 + 4 + 5 = 4 + 5 + 6 = 7 + 8 = 15, 
//所以打印出3个连续序列1～5、4~6和7~8。
#if 0
#include <iostream>

using namespace std;

void FindSequenceOfPositiveNumbers(int s);
inline int CntBegToEnd(int b, int e);

int main()
{
    int s = 15;

    try
    {
        FindSequenceOfPositiveNumbers(s);
    }
    catch (exception& e)
    {
        cout << e.what();
    }

    return 0;
}
void FindSequenceOfPositiveNumbers(int s)
{
    if (s <= 0)
        throw exception("Invalid input!");

    //***思路***
    //利用连续递增的正数序列这一条件
    //用双指针思想，结合二分法的截取数据段的条件判断来做

    int begnum, endnum;
    begnum = 1, endnum = 2;
    int tmp,flag=false;

    while (begnum < endnum)//***注***   不能写<=
    {
        tmp=CntBegToEnd(begnum, endnum);

        if (tmp == s)
        {
            cout << begnum << " " << endnum << endl;

            flag = true;

            ++begnum;
            ++endnum;
        }
        else if (tmp > s)
            ++begnum;
        else
            ++endnum;
    }

    if(!flag)
    cout << "No matched number(s) !\n";

    return;
}
inline int CntBegToEnd(int b, int e)
{
    return ((b + e) * (e - b + 1)) >> 1;
}
//***注***
//考虑到每次操作之后的序列和操作之前的序列相比大部分数字都是一样的，
//只是增加或者减少了一个数字，因此我们可以在前一个序列的和的基础上
//求操作之后的序列的和。这样可以减少很多不必要的运算，从而提高代码的效率。
#if 0
void FindContinuousSequence(int sum)
{
    if (sum < 3)
        return;

    int small = 1;
    int big = 2;
    int middle = (1 + sum) / 2;
    int curSum = small + big;

    while (small < middle)
    {
        if (curSum == sum)
            PrintContinuousSequence(small, big);

        while (curSum > sum && small < middle)
        {
            curSum -= small;
            small++;

            if (curSum == sum)
                PrintContinuousSequence(small, big);
        }

        big++;
        curSum += big;
    }
}
#endif
#endif


//面试题58：翻转字符串
//翻转单词顺序
//输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
//为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a
//student.",则输出"student.a am I"。
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

char* reverse_word_order(char* target);
char* reverse_all(char* begidx,char* endidx);

int main()
{
    //***注***
    //如果打算修改字符串，就不要用指针指向字符串字面量。
    //const char* data="I am a student.";

    //初始化字符数组来存储字符串
    char data[] = "I am a student.";

    cout << reverse_word_order(data);

    return 0;
}

char* reverse_word_order(char* target)
{
    if (target == nullptr)
        return const_cast<char*>("Error input!");

    //计算字符串长度（不含末尾空字符）
    char* tmp = target;
    int length = 0;

    //错误写法：
    //while (tmp)

    while(*tmp!='\0')
    {
        ++length;
        ++tmp;
    }

    //先翻转所有字符
    reverse_all(target,target+length);

    //再对每一个单词的字符进行翻转
    char* begidx, *endidx;
    begidx = endidx = target;

    //写法一：
#if 0
    while(*endidx!='\0')
    {
        //***注***
        //优先判断是否到字符串末尾，再判断是否为空格字符
        while (*endidx != '\0' &&*endidx != ' ')
            ++endidx;

        reverse_all(begidx,endidx);

        //越过空格字符
        if(*endidx != '\0')
			++endidx;

        begidx = endidx;
    }
#endif

    //写法二：
#if 1
    // 翻转句子中的每个单词
    char* pBegin, * pEnd;
    pBegin = pEnd = target;
    while (*pBegin != '\0')
    {
        //若一个单词已经完成翻转操作
        if (*pBegin == ' ')
        {
            pBegin++;
            pEnd++;
        }//若pEnd指针达到一个单词的末尾
        else if (*pEnd == ' ' || *pEnd == '\0')
        {
            reverse_all(pBegin, pEnd);
            pBegin = pEnd;
        }
        else//pEnd指针未达到一个单词的末尾
            pEnd++;
    }
#endif

    return target;
}

char* reverse_all(char* begidx, char* endidx)
{
    //endidx原来指向末尾的空字符或指向空格字符，
    //因此要先向前移动一个字符单位
    --endidx;

    while (begidx<endidx)
    {
        char tmp = *begidx;
        *begidx = *endidx;
        *endidx = tmp;

        ++begidx;
        --endidx;
    }

    //处理完后变成：
    //.tneduts a ma I

    return const_cast<char*>("OK");
}
#endif


//左旋转字符串。
//字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
//请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串
//"abcdefg"和数字2, 该函数将返回左旋转两位得到的结果"cdefgab"。
#if 0
#include <iostream>
#include <deque>
using namespace std;

char* AnticlockwiseString(char* source,int n);
char* Reverse(char* begidx, char* endidx);

int main()
{
    char data[] = "abcdefg";

    int weishu = 2;

    cout << AnticlockwiseString(data,weishu);

    return 0;
}

//自己的解法：
//要依靠deque容器，而且要进行两次赋值操作
#if 0
char* AnticlockwiseString(char* source, int n)
{
    if (source == nullptr || n < 0)
        return nullptr;

    char* tmp = source;
    int length=0;
    while (*tmp != '\0')
    {
        ++length,++tmp;
    }//（可以用strlen()函数）

    if (n > length)
        return const_cast < char*> ("Error !\n");

    //创建一个双端队列，用于存储不含末尾空字符的字符串数据
    deque<char>deq;

    tmp = source;
    while(*tmp!='\0')
		deq.push_back(*tmp++);

    while (n--)
    {
        char tmp = deq.front();
        deq.pop_front();
        deq.push_back(tmp);
    }

    deq.push_back('\0');

    int index = 0;
    for (auto i = deq.begin(); i != deq.end(); ++i)
        source[index++] = *i;

    return source;
}
#endif

//需要一定技巧的解法：
//abcdefg 变成
//cdefgab
//上面字符串翻转得到bagfedc
//观察得到：相当于对原字符串的 ab 和 cdefg 分别进行翻转处理后再整体进行翻转处理
//因此只需要调用3次前面的Reverse函数就可以实现字符串的左旋转功能。
#if 1
char* AnticlockwiseString(char* source, int n)
{
    if (source == nullptr || n < 0)
        return nullptr;
    int length = strlen(source);

    if (n >= length)
        return nullptr;

    int substr1_beg = 0;
    int substr1_end = n - 1; 

    int substr2_beg = n;
	int substr2_end = length - 1;

    Reverse(source+substr1_beg, source+substr1_end);
    Reverse(source+substr2_beg, source+substr2_end);
    Reverse(source, source+length-1);

    return source;
}

char* Reverse(char* begidx, char* endidx)
{
    while (begidx < endidx)
    {
        char tmp = *begidx;
        *begidx = *endidx;
        *endidx = tmp;

        ++begidx;
        --endidx;
    }

    return const_cast<char*>("OK");
}
#endif
#endif


//面试题59：队列的最大值
//滑动窗口的最大值
//给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。
//例如，如果输入数组{ 2,3,4,2,6,2,5,1 }及滑动窗口的大小3,
//那么一共存在6个滑动窗口，它们的最大值分别为{ 4,4,6,6,6,5 }
#if 0
#include <iostream>
#include <queue>
using namespace std;

void TheMaxNumInSlidingWindow(int* data,int n,int WindowLength);

int main()
{
    int data[] = {2,3,4,2,6,2,5,1};
    int WindowLength = 3;

    try
    {
        TheMaxNumInSlidingWindow(data,sizeof(data)/sizeof(int), WindowLength);
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}

//解法一：
//使用priority_queue容器
#if 0
void TheMaxNumInSlidingWindow(int* data, int dataLength, int WindowLength)
{
    if (data == nullptr || WindowLength > dataLength||WindowLength<=0)
        throw exception("Error input!");

    //priority_queue<int> pq;

    //int i;
    //for ( i = 0; i < WindowLength; ++i)
    //    pq.push(data[i]);

    //cout << pq.top()<<", ";

    /*
    while (i != dataLength)
    {
        pq.;//优先队列无法将最先推入队列的元素弹出，
        //一方面是没有该功能的方法，另一方面是数据已经排好序了
        pq.push(data[i++]);

        cout << pq.top() << ", ";
    }
    */

    //该难点的解决方法：
    //转换思路，没有必要定位滑动窗口最左侧的元素位置并将该元素
    //在每次窗口滑动时删去。
    //真正影响输出的是优先队列的队首元素，当发生窗口滑动时，
    //要判断队首元素的在原数组中的索引值是否在窗口外，如果是，
    //就删去这个最大的元素即可。
    //因此，优先队列的每个元素是个结构体（或pair对象），
    //包含元素值和该元素的索引值

    priority_queue<pair<int,int>> pq;

    int i;
    for ( i = 0; i < WindowLength; ++i)
        pq.emplace(data[i],i);

    //***注***
    //push() 将已构造对象的副本作为参数添加到队列中，它采用队列元素类型的对象。
    //emplace() 在队列末尾就地构造一个新对象。它将队列的元素类型构造函数所采用的参数作为参数。

    cout << pq.top().first<<", ";

    while(i != dataLength)
    {
        pq.emplace(data[i], i);

        //***注***
        //判断当前窗口中的最大值对应的索引值是否
        //位于窗口最左侧的左侧
        //注意用的是while循环
        while (pq.top().second <= i - WindowLength)
        {
            pq.pop();
        }
        
        if (i != dataLength - 1)
            cout << pq.top().first << ", ";
        else
            cout << pq.top().first;

        ++i;
    }

    return;
}
#endif

//解法二：
//使用deque容器
//顺着方法一的思路继续进行优化。
//由于我们需要求出的是滑动窗口的最大值，
// 如果当前的滑动窗口中有两个下标 i 和 j，其中 i 在 j 的左侧，
// 并且 i 对应的元素不大于 j 对应的元素，那么会发生什么呢？
//当滑动窗口向右移动时，只要 nums[i] 还在窗口中，那么 nums[j] 一定也还在窗口中，
//这是 nums[i] 在 nums[j] 的左侧所保证的。
//因此，由于 nums[j] 的存在，nums[i] 一定不会是滑动窗口中的最大值了，
//我们可以将 nums[i] 永久地移除
//这样就能保证双端队列的首元素一直是当前窗口状态下的最大值，就不需要优先队列了
void TheMaxNumInSlidingWindow(int* data, int dataLength, int WindowLength)
{
    if (data == nullptr || WindowLength > dataLength || WindowLength <= 0)
        throw exception("Error input!");

    deque <int> index;

    for (int i = 0; i < WindowLength; ++i)
    {
        //若index中有数据，且当前要推入的元素值大于等于上一个元素的值
        while (!index.empty() && data[i] >= data[index.back()])
            index.pop_back();//index中存的某尾元素弹出，即窗口中最大值不可能是该值

        index.push_back(i);
    }
    //在窗口生成后，index中存的是该窗口范围内的最大值对应的索引值

    //窗口开始滑动
    for (int i = WindowLength; i < dataLength; ++i)
    {
        cout << data[index.front()] << ", ";

        //若index中有数据，且当前要推入的元素值大于等于上一个元素的值
        while (!index.empty() && data[i] >= data[index.back()])
            index.pop_back();//index中存的某尾元素弹出，即窗口中最大值不可能是该值
                
        //若index中有数据，判断最大值对应的索引值是否在窗口范围外
        if (!index.empty() && index.front() <= i - WindowLength)
            index.pop_front();

        //无论index中是否有数据，或当前要推入的元素值小于上一个元素的值
        index.push_back(i);
    }

    cout << data[index.front()];

    return;
}
#endif


//队列的最大值
//请定义一个队列并实现函数max得到队列里的最大值，要求函数max、
//push_back和pop_front的时间复杂度都是O(1)。
//相当于要用deque实现priority_queue
#if 0
#include <iostream>
#include <deque>

template <typename T> 
class QueueWithMax
{
private:
    struct DataProperty
    {
        T number;
        int index;
    };

    //***注1***
    //以下为错误写法
    //using std::deque;
    //using namespace std;
    //一般类内使用using都是为了让派生类不遮掩(不隐藏)基类的同名方法

    std::deque<DataProperty> data;
    std::deque<DataProperty> MaxIsTheTopElement;

    int CurrentIndex;

public:
    QueueWithMax();
    void push_back(T num);
    void pop_front();
    T max() const;
};

template <typename T>
QueueWithMax<T>::QueueWithMax() :CurrentIndex(0)
{}

template <typename T>
void QueueWithMax<T>::push_back(T num)
{
    //若MaxIsTheTopElement中有数据，且当前要推入的元素值大于等于上一个元素的值
    while (!MaxIsTheTopElement.empty() && num >= MaxIsTheTopElement.back().number )
        MaxIsTheTopElement.pop_back();//MaxIsTheTopElement存的末尾元素弹出，
    //即窗口中最大值不可能是该值

    //***注2***
    //错误写法
    //MaxIsTheTopElement.emplace(num,CurrentIndex);
    //原因：emplace()方法需要用到某元素类型的构造函数，而结构体没有构造函数可用

    DataProperty tmp = {num,CurrentIndex};

    MaxIsTheTopElement.push_back(tmp);
    data.push_back(tmp);

    ++CurrentIndex;
}

template <typename T>
void QueueWithMax<T>::pop_front()
{
    if (MaxIsTheTopElement.empty() || data.empty())
        throw std::exception("Empty Container!\n");

    //MaxIsTheTopElement容器的元素弹出，考虑上一题的和滑动窗口的左侧边界比较
    //在此处由于有一个data容器，因此只要判断弹出的是否是和data容器弹出的元素相同即可
    if (MaxIsTheTopElement.front().index == data.front().index)
        MaxIsTheTopElement.pop_front();

    data.pop_front();

    //***注3***
    //此处CurrentIndex值不用递减
    //因为该变量是用于判断data容器要弹出的元素和MaxIsTheTopElement容器要弹出的元素
    //是否有相同的CurrentIndex值做为判断弹出的元素是否相同，若CurrentIndex递减了
    //会造成MaxIsTheTopElement中的值错误弹出的情况
}

template <typename T>
T QueueWithMax<T>::max() const
{
    if (MaxIsTheTopElement.empty())
        throw std::exception("Empty Container!\n");

    return MaxIsTheTopElement.front().number;
}

int main()
{
    QueueWithMax<int> queue;

#ifdef  _DEBUG
    queue.push_back(2);    
    queue.push_back(3);
    queue.push_back(4);
    queue.push_back(2);
    queue.pop_front();
    queue.pop_front();
    queue.pop_front();
    queue.push_back(6);
    queue.push_back(2);
    queue.push_back(5);
    queue.pop_front();
    queue.pop_front();
    queue.pop_front();
    queue.push_back(1);
#endif

    return 0;
}
#endif


//面试题60：n个骰子的点数
//把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。
//输入n, 打印出s的所有可能的值出现的概率。
#if 0
#include <iostream>
#include <memory>
#include <iomanip>
#include <algorithm>
using namespace std;

//规定一个骰子能得到的最大值
const int g_maxValue = 6;

void PrintProbability(int number);
void Probability(int num, unique_ptr< int[] >&);
void Probability(int original, int current, int sum, unique_ptr< int[] >& pProbabilities);

void PrintProbability_Solution2(int number);
void PrintProbability_Solution3(int number);

int main()
{
    //n个骰子，求能得到的所有可能的值的概率
    int  n= 3;

    PrintProbability(n);
    cout << endl;
    PrintProbability_Solution2(n);
    cout << endl;
    PrintProbability_Solution3(n);

    return 0;
}
void PrintProbability(int number)
{
    if (number < 1)
        return;

    //创建maxSum存投掷 number 次骰子可能获得的最大总和
    int maxSum = number * g_maxValue;

    //用智能指针管理动态分配的内存，
    //存储可能出现的不同总和的计数。
    unique_ptr< int[] > pProbabilities(new int [maxSum - number + 1] {0});
    //假设n为2，那么数值范围为2~12，需要11个存储位置

    //***注***
    //使用了C++11的一致性初始化(Uniform Initialization)

    Probability(number,pProbabilities);

    auto total = pow((double)g_maxValue, number);
    for (int i = number; i <= maxSum; ++i)
    {
        double ratio = (double)pProbabilities[i - number] / total;

        //printf("%d: %e\n", i, ratio);
        cout << i<<": ";
        cout << scientific;
        cout << ratio<<endl;
    }
}

void Probability(int num, unique_ptr< int[] >& pPro)
{
    //把n个骰子分为两堆，第一堆只有一个，另一堆有n-1个
    //对于第一堆：
    //遍历每个可能的骰子面的值，从 1 到 g_maxValue。
    for (int i = 1; i <= g_maxValue; ++i)
        Probability(num, num, i, pPro);
}

//对于剩下的另一堆即n-1个骰子
//仍然分成两堆，第一堆只有一个；第二堆有n-2个。我们把上一轮那个单独骰子的
//点数和这一轮单独骰子的点数相加，再和剩下的n - 2个骰子来计算点数和。
void Probability(int original, int current, int sum, unique_ptr< int[] >& pProbabilities)
{
    //***理解***
    // original 表示最初的投掷次数，current 表示当前剩余的投掷次数，sum 表示当前累积的总和。
    // 如果当前剩余的投掷次数 current 等于 1，则将当前累积的总和 sum - original 作为索引，
    // 在 pProbabilities 数组中相应位置的次数加 1。
	// 如果当前的投掷次数 current 大于 1，则使用循环递归调用自身，
    // 每次递归将当前的投掷次数减 1，累积的总和增加当前骰子面的值 i
    if (current == 1)
    {
        pProbabilities[sum - original]++;
    }
    else
    {
        for (int i = 1; i <= g_maxValue; ++i)
        {
            Probability(original, current - 1, i + sum, pProbabilities);
        }
    }
}

//法二：
#if 1
void PrintProbability_Solution2(int number)
{
    if (number < 1)
        return;

    //使用一个二维数组 pProbabilities ,
    //其中的一维数组存储骰子投掷后每个和值出现的次数
    //另一个一维数组用于辅助存储值
    //而且两个一维数组交替成为辅助数组
    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];

    for (int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }

    //使用 flag 变量进行交替的标记，用于标识当前正在更新的数组行。
    //一开始是pProbabilities[0]数组用作辅助数组
    int flag = 0;
    for (int i = 1; i <= g_maxValue; ++i)
        pProbabilities[flag][i] = 1;

    //使用动态规划的思想，通过循环计算每个投掷次数下各个和值出现的次数。
    //外层循环 k 表示当前投掷的次数，内层循环用于计算出现的次数。
    for (int k = 2; k <= number; ++k)
    {
        //在计算当前投掷次数下各个和值出现的次数时，
        //首先将新的数组行中小于次数 k 的位置的次数置为 0。
        //这些位置的元素要进行更新
        for (int i = 0; i < k; ++i)
            pProbabilities[1 - flag][i] = 0;
        //***注***
        //1-flag用于交替将某个一维数组内容置为0

        // 每次投掷的骰子面的值都在 1 到 g_maxValue 之间，
        // 所以 i 表示可能的总和值的范围是从 k（最小可能的和值，即每次都投掷到 1 的情况下的和值）
        // 到 g_maxValue * k（每次都投掷到 g_maxValue 的情况下的最大和值）。
        
        // 在范围为 k 到 g_maxValue * k 之间的位置上，
        // 计算每个和值出现的次数。
        // 这是通过遍历前一个数组行中的和值，
        // 在当前和值的位置上累加可能的骰子面的值所得到的次数来实现的
        for (int i = k; i <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;

            // 新的数组行中
            // j 表示当前投掷的骰子的点数，
            // 从 1 开始递增，直到当前和值 i 或骰子的面数 g_maxValue 较小的那个值。
            // 这是因为当投掷的骰子面的值大于当前的和值 i 或者超过了骰子的面数 g_maxValue 时，
            // 就不需要考虑这个值，因为它不会对当前和值产生影响。
            for (int j = 1;  j <= i && j <= g_maxValue;  ++j)
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
        }

        flag = 1 - flag;
    }

    double total = pow((double)g_maxValue, number);
    for (int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = (double)pProbabilities[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }

    delete[] pProbabilities[0];
    delete[] pProbabilities[1];

    return;
}
#endif

//法三：
//参考https://cloud.tencent.com/developer/article/1947235
void PrintProbability_Solution3(int number)
{
    //因为最后的结果只与前一个动态转移数组有关，所以这里只需要设置一个一维的动态转移数组
    //原本dp[i][j]表示的是前i个骰子的点数之和为j的概率，现在只需要最后的状态的数组，
    //所以就只用一个一维数组dp[j]表示n个骰子下每个结果的概率。
    
    //初始是1个骰子情况下的点数之和情况，就只有6个结果，所以用dp的初始化的size是6个
    double* dp = new double[6];

    //只有一个数组
    fill(dp, dp + 6,1/6.0);

    int length = 6;

    //从第2个骰子开始，这里number表示number个骰子，
    //先从第二个的情况算起，然后再逐步求3个、4个···n个的情况
    // i 表示当总共i个骰子时的结果
    for (int i = 2; i <= number; i++) 
    {
        //每次的点数之和范围会有点变化，点数之和的值最大是i*6，最小是i*1，i之前的结果值是不会出现的；
        //比如i=3个骰子时，最小就是3了，不可能是2和1，而最大值是18，需要的存储空间是18-3+1=16
        //所以点数之和的值的个数是6*i-(i-1)，化简：5*i+1
        //当有i个骰子时的点数之和的值数组先假定是temp
        double* temp = new double[5 * i + 1] {0};
        //***注***
        //i为2时，temp[0]代表和值为2的概率，i为3时，temp[0]代表和值为3的概率

        //从i-1个骰子的点数之和的值数组入手，计算i个骰子的点数之和数组的值
        //***注***
        //i-1个骰子的点数之和的各个和值的概率即dp数组的第j个值，
        //它所影响的是i个骰子时的temp[j+k]的值

        //***注***
        //错误写法：
        //for (int j = 0; j < sizeof(dp)/sizeof(dp[0]); j++)
        //【这样只能求静态数组的长度，而不能求动态数组的长度】

        for (int j = 0; j < length; j++)
        {
            //比如只有1个骰子时，dp[1]是代表当骰子点数之和为2时的概率，
            //它会对当有2个骰子时的点数之和为3、4、5、6、7、8产生影响，
            //因为当有一个骰子的值为2时，另一个骰子的值可以为1~6，
            //产生的点数之和相应的就是3~8；
            //如dp[2]代表点数之和为3时的概率，
            //它会对有2个骰子时的点数之和为4、5、6、7、8、9产生影响；
            //所以k在这里就是对应着第i个骰子出现时可能出现六种情况     
            for (int k = 0; k < 6; k++) 
            {
                //这里记得是加上dp数组值与1/6的乘积，1/6是第i个骰子投出某个值的概率
                temp[j + k] += dp[j] * (1.0 / 6.0);
            }
        }

        //i个骰子的点数之和全都算出来后，要将temp数组移交给dp数组，
        // dp数组就会代表i个骰子时的可能出现的点数之和的概率；
        // 用于计算i+1个骰子时的点数之和的概率

        delete[]dp;

        dp = temp;
        length = 5 * i + 1;
    }

    for (int i = number; i <= g_maxValue * number; ++i)
    {
        printf("%d: %e\n", i, dp[i-number]);
    }
}
#endif


//面试题61：扑克牌中的顺子
//解题思路：
//首先把数组排序；其次统计数组中0的个数(即大小王个数)
//最后统计排序之后的数组中相邻数字之间的空缺总数。如果空缺的总数
//小于或者等于0的个数，那么这个数组就是连续的；反之则不连续。
//或者
//首先把数组排序；其次统计数组中0的个数(即大小王个数)
//然后用两个指针来比较相邻数字的差值，
//对差值的情况进行分类处理
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

bool isContinuous(int* numbers,int length);

int main()
{
    int ceshi[] = {1,3,4,0,5};
    cout << isContinuous(ceshi,sizeof(ceshi)/sizeof(int))<<endl;
    int ceshi_1[] = {2,3,4,0,0,5};
    cout << isContinuous(ceshi_1,sizeof(ceshi_1)/sizeof(int))<<endl;

    return 0;
}
bool isContinuous(int* numbers,int length)
{
    if(numbers ==nullptr || length <=0)
		return false;

    if (length == 1)
        return true;

    sort(numbers,numbers+length);

    int CntZero = 0;
    for (int i = 0; i < length; ++i)
    {
        if (numbers[i] == 0)
            ++CntZero;
    }

    //***
    //让两个指针直接定位在非大小王的最小的两个数字处
    int* theBeg = numbers+CntZero;
    int* theEnd = numbers + CntZero + 1;
    int difference_value = *theEnd - *theBeg;

	while (theEnd!=numbers+length)
	{
        //如果相差0，直接判false
        //如果相差1，就继续移动两个指针
        //如果相差2，CntZero必须大于等于1
        //如果相差3，CntZero必须大于等于2
        //...
        if (difference_value == 0)
            return false;
        //else if (difference_value == 2)
        //{
        //    if (CntZero >= 1)
        //        --CntZero;
        //    else
        //        return false;
        //}
        //else if(difference_value == 3)
        //{
        //    if (CntZero >= 2)
        //        CntZero-=2;
        //    else
        //        return false;
        //}
        //简化为以下代码块，以支持多个大小王的情况
		else if (difference_value >= 2)
		{
			if (CntZero >= difference_value-1)
				CntZero-= difference_value-1;
			else
				return false;
		}

        ++theBeg;
        ++theEnd;
        difference_value = *theEnd - *theBeg;
	}

    return true;
}
//***注***
//要进一步提升速度，可以不用sort()，而改用长度为14的哈希表，这样在O(n)
//的时间内可完成排序
#endif


//面试题62：圆圈中最后剩下的数字
#if 0
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int LastRemaining(int n,int m);

int main()
{
    int n, m;
    //cin >> n >> m;
    n = 5, m=3;
    cout << LastRemaining(n,m);

    return 0;
}

int LastRemaining(int n, int m)
{
    if (n <= 0 || m <= 0)
        return - 1;

    //圆圈中仅一个数字
    if (n == 1)
        return 0;

    list<int> circle;

    for (int i = 0; i < n; ++i)
    {
        circle.push_back(i);
    }

    //创建gostep代表指针移动的次数
    int gostep;
    //创建指针指向要删除的元素所在的位置
    // ***(若m为1则不移动)***
    auto erase_pos = circle.begin();
    for (gostep = 1; gostep != m; ++gostep)
    {
        ++erase_pos;

        if (erase_pos == circle.end())
            erase_pos = circle.begin();
    }

#ifdef _DEBUG
    for_each(circle.begin(), circle.end(), [](int& num) {cout << num << " "; });
    cout << endl;
#endif

    while (circle.size() != 1)
    {
		//***错误写法***
		//list的迭代器不是随机访问迭代器
		//auto next_pos = erase_pos+1;

        //可以写为auto next_pos = ++erase_pos ;    --erase_pos ;     ...     erase_pos=next_pos;

        circle.erase(erase_pos++);
#ifdef _DEBUG
        for_each(circle.begin(), circle.end(), [](int& num)  {cout << num << " "; });
        cout << endl;
#endif

        if (erase_pos == circle.end())
            erase_pos = circle.begin();

        for (gostep = 1; gostep != m; ++gostep)
        {
            ++erase_pos;

            if (erase_pos == circle.end())
                erase_pos = circle.begin();
        }
    }

    return *(circle.begin());
}
#endif


//面试题63：股票的最大利润
//思路：在扫描到第i个元素值时，能够记住之前的i-1个数字中的最小值
#if 0
#include <iostream>

using namespace std;

int MaxProfit(int* stk,int length);

int main()
{
    int stock[] = {9,11,8,5,7,12,16,14};

    cout << MaxProfit(stock,sizeof(stock)/sizeof(int));

    return 0;
}
int MaxProfit(int* stk, int length)
{
    if (stk == nullptr || length < 2)
        return -1;

    int TmpMinValue = stk[0];
    int TmpMaxValue = stk[1];

    if (length == 2)
        return TmpMaxValue - TmpMinValue;

    //从第三个元素开始遍历
    for (int i = 2; i < length; ++i)
    {
        TmpMinValue = TmpMinValue < stk[i] ? TmpMinValue : stk[i];
        TmpMaxValue = TmpMaxValue > stk[i] ? TmpMaxValue : stk[i];
    }

    return TmpMaxValue - TmpMinValue;
}
#endif


//面试题64：求1+2+3+...+n
#if 0
#include <iostream>

using namespace std;

//解法一：利用构造函数和static成员变量代替直接使用循环
class Tmp
{
private:
    //***注***
    //利用了静态成员变量仅在初始化时执行一次初始化语句，之后不会再重复执行
    //的特点，来记录每次要累加的值N，和总和Sum
    static int N;
    static int Sum;

public:
    Tmp()
    {
        ++N;
        Sum += N;
    }

    static void Reset()
    {
        N = Sum = 0;
    }

    int GetSum()
    {
        return Sum;
    }
};

int Tmp::N = 0;
int Tmp::Sum = 0;

//***注***
//在类内声明方法为static的作用：
//无需实例化对象就可以调用，
//普通的成员函数需要通过类的实例化对象才能调用，
//而静态成员函数可以直接通过类名来调用，无需创建类的对象实例。

//在类内声明变量为static的作用：
//在执行时不依赖于任何特定的对象，
//因此对于全局操作非常有用。

int Sum_solution_1(int n)
{
    //创建一个Tmp类数组，包含n个Tmp类对象，
    //那么这些类对象都会由构造函数来生成
    //构造函数会调用n次
    unique_ptr<Tmp[]> t(new Tmp[n]{});
    
    //***注***
    //错误写法：
    //return t->GetSum();

    //理解：
    //t 是一个指向 Tmp 类型数组的 unique_ptr 对象，它管理这个数组的内存
    //但【它本身并不是 Tmp 类的对象】，因此不能直接访问类中的方法。
    //要访问类的方法，你需要通过 unique_ptr 持有的指针间接地访问数组元素，
    //并在该元素上调用相应的方法
    return t[0].GetSum();
}

//解法二：利用虚函数代替直接使用递归（其中递归中一定会有用到if的地方来判断何时递归终止）
class A;
A* Array[2];

class A
{
public:
    virtual int Sum(int n) 
    {
        return 0;
    }
};

class B :public A
{
public:
    virtual int Sum(int n) override
    {
        //两次取反运算
        //n为100  !n为0  !!n为1
        //n为0      !n为1  !!n为0
        return Array[!!n]->Sum(n-1) + n;
    }
};

int Sum_solution_2(int n)
{
    A a;
    B b;
    Array[0] = &a;
    Array[1] = &b;

    return Array[1]->Sum(n);
}

//解法三：使用函数指针来代替直接使用递归
typedef int (*pFun)(int);

int Sum_solution_3_terminate(int n)
{
    return 0;
}

int Sum_solution_3(int n)
{
    pFun funArray[2] = { Sum_solution_3_terminate ,Sum_solution_3 };

    //错误写法：
    //return funArray[!!n](--n) + n;
    return funArray[!!n](n-1) + n;
}

//解法四：模板元编程，在编译期确定值
template<int n>
class Sum_solution_4
{
public:
    enum Value {N=Sum_solution_4<n-1>::N+n};

    Sum_solution_4()
    {}

};

//模板具体化
template<>class Sum_solution_4<1>
{
public:
    enum {N=1};
};

int main()
{
    int n = 100;

    cout<<Sum_solution_1(n)<<endl;
    cout<<Sum_solution_2(n)<<endl;
    cout<<Sum_solution_3(n)<<endl;

    //错误写法：
    //Sum_solution_4<n> s4;    //原因：非模板类型参数必须为常量值
    Sum_solution_4<100> s4;    
    cout<< s4.N <<endl;

    return 0;
}
#endif


//面试题65：不用加减乘除做加法
//思路：“三步走”对于二进制也适用
//第一步：各位相加但不进行进位
//第二步：记下进位数
//第三步：将前面两个步骤的结果相加
#if 0
#include <iostream>

using namespace std;

int Add(int num1,int num2);

int main()
{
    int num1 = 5;
    int num2 = 17;

    cout << Add(num1,num2);

    return 0;
}
//  5+17=22
// 0000 0101
// 0001 0001
// 0001 0110
//第一次循环：
//XOR_res                  =0001 0100
//OperationAfterAnd =0000 0010
//第二次循环：
//XOR_res                  =0001 0110
//OperationAfterAnd =0000 0000

// 17+17=34
// 0001 0001
// 0001 0001
// 0010 0010

// -1+2=1
//1111 1111 1111 1111 1111 1111 1111 1111 
//0000 0000 0000 0000 0000 0000 0000 0010
//0000 0000 0000 0000 0000 0000 0000 0001
//第一次循环：
//XOR_res                  =1111 1111 1111 1111 1111 1111 1111 1101 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 0100
//第二次循环：
//XOR_res                  =1111 1111 1111 1111 1111 1111 1111 1001 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 1000
//直到某次循环
//XOR_res                  =0000 0000 0000 0000 0000 0000 0000 0001 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 0000

//不够完整的方法：(不能解决相加的数字有负数的情况)
#if 0
int Add(int num1, int num2)
{
    int XOR_res = num1 ^ num2;

    //记下进位的位置并进行移位
    int OperationAfterAnd = (num1 & num2) << 1;

    return XOR_res | OperationAfterAnd;
}
#endif

#if 1
int Add(int num1, int num2)
{
    int XOR_res, OperationAfterAnd;

    while (num2)
    {
        //第一步也是第三步
        //存储非进位和
        XOR_res = num1 ^ num2;
        //第二步
        //对于两个数的某位要进位的处理
        OperationAfterAnd = (num1 & num2) << 1;

        num1 = XOR_res;
        num2 = OperationAfterAnd;
    }  

    return num1;
}
#endif
#endif


//面试题66：构建乘积数组
//给定一个数组A[0,1,…n-1],请构建一个数组B[0,1,…n-1],其中B中的元素
//B[i] =  A[0]×A[1]×…×A[ i - 1]×A[i + 1]×…×A[n - 1]。不能使用除法。
//解法：
//B[i] = A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]
//看成A[0]×A[1]×…×A[i - 1] 和 A[i + 1]×…×A[n - 2]×A[n - 1]两部分的乘积。
//这两部分分别用数组C和数组D表示
//其中数组C[i]的计算自上而下
//其中数组D[i]的计算自下而上
//【数组B看成由一个矩阵来创建】
#if 0
#include <iostream>
#include <vector>
using namespace std;

void Multiply(const vector<int>& va,vector<int>& vb);

int main()
{
    vector<int> A{ 1,2,3,4,5,6 };
    vector<int>B(6,0);

    try
    {
		Multiply(A, B);
    }
    catch(exception& e)
    {
        cout<<e.what();
    }

    for (auto const& x : B)
        cout << x << " ";

    return 0;
}

#if 0
void Multiply(const vector<int>& va, vector<int>& vb)
{
    if (va.size() == 0)
        throw exception("Error!");

    vector<int>C(va.size(),1);

    auto ic = C.begin()+1;
    int tmp = 1;
    for (auto const& x : va)
    {
        tmp *= x;
        *ic++ = tmp;

        if (ic == C.end())
            break;
    }

#ifdef _DEBUG
    for (auto x : C)
        cout << x << " ";
    cout << endl;
#endif

    vector<int>D(va.size(), 1);

    auto id = D.end() - 2;
    tmp = 1;
    for (auto i = va.cend()-1; i >= va.cbegin(); --i)
    {
        tmp *= *i;

        //错误写法：
        //*id-- = tmp;
        //Expression: can't decrement vector iterator before begin

        *id = tmp;

        if (id == D.begin())
            break;
        else
            --id;
    }

#ifdef _DEBUG
    for (auto x : D)
        cout << x << " ";
    cout << endl;
#endif

    int index = 0;
    for (auto& x : vb)
    {
        x = C[index] * D[index];
        ++index;
    }

    return;
}
#endif
#if 1
void Multiply(const vector<int>& input, vector<int>& output)
{
    int length1 = input.size();
    int length2 = output.size();

    if (length1 == length2 && length2 > 1)
    {
        //将矩阵C[i]计算好，不创建矩阵C，而是直接在输出矩阵B上操作
        output[0] = 1;
        for (int i = 1; i < length1; ++i)
        {
            output[i] = output[i - 1] * input[i - 1];
        }

        for (auto x : output)
            cout << x << " ";
        cout << endl;

        //将矩阵D[i]计算好，对输出矩阵的操作是从B[4]开始，到B[0]结束
        double temp = 1;
        for (int i = length1 - 2; i >= 0; --i)
        {
            temp *= input[i + 1];
            output[i] *= temp;
        }

        for (auto x : output)
            cout << x << " ";
        cout << endl;
    }
}
#endif
#endif


//面试题67：自己写一个atoi()功能的函数
#if 0
#include <iostream>

using namespace std;

enum Flag{VALID,INVALID,USER_OVERFLOW};
Flag flag = VALID;

int StrToInt(const char* str);

int main()
{
    const char str [] = "-123 4";

    cout << StrToInt(str) << endl;
    cout << StrToInt("-123junk-  123") << endl;
    cout << StrToInt("   -123") << endl;
    cout << StrToInt("1-1") << endl;
    cout << StrToInt("  +1+1") << endl;
    cout << StrToInt("  +1 1") << endl;
    cout << StrToInt("junk") << endl;
    cout << StrToInt("-") << endl;
    cout << StrToInt("") << endl;
    cout << StrToInt("123456789123456789") << endl;

    return 0;
}
int StrToInt(const char* str)
{
    //要考虑到的基本的输入用例：
    //nullptr   、 ""  、 +  、 -  、溢出
    if (str == nullptr||str=="")
    {
        flag = INVALID;

        return 0;
    }

    const char* traverse = str;

    while (isspace(*traverse))
        ++traverse;

    if (!isdigit(*traverse) && !(*traverse == '+') && !(*traverse == '-'))
    {
        flag = INVALID;

        return 0;
    }

    bool Positive = 1;
    bool RunOnlyOnce = 1;
    //***注***
    //声明为long long来判断对于int类型是否溢出
    long long res = 0;
    while (*traverse != '\0')
    {
        if (RunOnlyOnce)
        {    if (*traverse == '+')
                ++traverse;
            else if (*traverse == '-')
            {
                ++traverse;
                Positive = 0;
            }

            RunOnlyOnce = 0;
		}

        //***注***
        //第二种处理方法：
        //可以不用写RunOnlyOnce，而是将上面的代码块从循环中摘出，然后
        //循环以及后面的代码块移到 int StrToIntCore(const char* str, bool Positive)中

        //为"-123junk-  123"  做代码完整性的补充
        if (!isdigit(*traverse) && !isspace(*traverse))
            break;

        if (isdigit(*traverse))
        {
            res = res * 10 + (*traverse) - '0';
        }

        ++traverse;
    }

    //***注***
    //numeric_limits<int>::min()式子被声明为 constexpr ，表达式核定于编译期。
    if(res<numeric_limits<int>::min()||res>numeric_limits<int>::max())
    {
        flag= USER_OVERFLOW;

        return 0;
    }

    return Positive ? res : -res;
}
#endif


//面试题68：树中两个节点的最低公共祖先
//注意不是二叉树
#if 0
#include <iostream>
#include <list>
#include <vector>

struct TreeNode
{
    int                                      m_nValue;
    std::vector<TreeNode*>    m_vChildren;
};

 TreeNode* CreateTreeNode(int value);
 void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
 void PrintTreeNode(const TreeNode* pNode);
 void PrintTree(const TreeNode* pRoot);
 void DestroyTree(TreeNode* pRoot);

using namespace std;

const TreeNode* GetLastCommonParent(const TreeNode* pRoot, const TreeNode* pNode1, const TreeNode* pNode2);
bool GetNodePath(const TreeNode* pRoot, const TreeNode* pNode, list<const TreeNode*>& path);
const TreeNode* GetLastCommonNode
(
    const list<const TreeNode*>& path1,
    const list<const TreeNode*>& path2
);

int main()
{
    TreeNode* pNode1 = CreateTreeNode(1);
    TreeNode* pNode2 = CreateTreeNode(2);
    TreeNode* pNode3 = CreateTreeNode(3);
    TreeNode* pNode4 = CreateTreeNode(4);
    TreeNode* pNode5 = CreateTreeNode(5);
    TreeNode* pNode6 = CreateTreeNode(6);
    TreeNode* pNode7 = CreateTreeNode(7);
    TreeNode* pNode8 = CreateTreeNode(8);
    TreeNode* pNode9 = CreateTreeNode(9);
    TreeNode* pNode10 = CreateTreeNode(10);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode1, pNode3);

    ConnectTreeNodes(pNode2, pNode4);
    ConnectTreeNodes(pNode2, pNode5);

    ConnectTreeNodes(pNode4, pNode6);
    ConnectTreeNodes(pNode4, pNode7);

    ConnectTreeNodes(pNode5, pNode8);
    ConnectTreeNodes(pNode5, pNode9);
    ConnectTreeNodes(pNode5, pNode10);

// 形状普通的树
//              1
//            /   \
//           2     3
//       /       \
//      4          5
//     / \        / |  \
//    6   7    8  9  10

    PrintTree(pNode1);
    cout << endl;

    const TreeNode* pResult = GetLastCommonParent(pNode1, pNode6, pNode8);
    cout << pResult->m_nValue<<endl;

    DestroyTree(pNode1);

    return 0;
}

const TreeNode* GetLastCommonParent(const TreeNode* pRoot, 
    const TreeNode* pNode1, const TreeNode* pNode2)
{
    if (pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr)
        return nullptr;

    list<const TreeNode*> path1;
    GetNodePath(pRoot, pNode1, path1);

    list<const TreeNode*> path2;
    GetNodePath(pRoot, pNode2, path2);

    return GetLastCommonNode(path1, path2);
}

//用递归找出到某节点的唯一路径
bool GetNodePath(const TreeNode* pRoot, const TreeNode* pNode, 
    list<const TreeNode*>& path)
{
    if (pRoot == pNode)
        return true;

    path.push_back(pRoot);

    bool found = false;

    //不是二叉树的处理方法
    vector<TreeNode*>::const_iterator i = pRoot->m_vChildren.begin();
    while (!found && i < pRoot->m_vChildren.end())
    {
        found = GetNodePath(*i, pNode, path);
        ++i;
    }

    if (!found)
        path.pop_back();

    return found;
}

const TreeNode* GetLastCommonNode(const list<const TreeNode*>& path1,
    const list<const TreeNode*>& path2)
{
    list<const TreeNode*>::const_iterator iterator1 = path1.begin();
    list<const TreeNode*>::const_iterator iterator2 = path2.begin();

    const TreeNode* pLast = nullptr;

    //***注***
    //理解从头开始找的意义
    //第一次iterator1和iterator2不同时，那上一次就是最后一个公共节点
    //与面试题52对比
    while (iterator1 != path1.end() && iterator2 != path2.end())
    {
        if (*iterator1 == *iterator2)
            pLast = *iterator1;

        iterator1++;
        iterator2++;
    }

    return pLast;
}

// 创建树节点
TreeNode* CreateTreeNode(int value) 
{
    TreeNode* pNode = new TreeNode();
    pNode->m_nValue = value;
    return pNode;
}

// 连接树节点，将 pChild 添加为 pParent 的子节点
void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild) 
{
    if (pParent != nullptr) 
    {
        pParent->m_vChildren.push_back(pChild);
    }
}

// 打印单个节点
void PrintTreeNode(const TreeNode* pNode) 
{
    if (pNode != nullptr) 
    {
        std::cout << "Node value: " << pNode->m_nValue << std::endl;
        std::cout << "Children: ";
        for (const auto& child : pNode->m_vChildren) 
        {
            std::cout << child->m_nValue << " ";
        }
        std::cout << std::endl;
    }
    else 
    {
        std::cout << "Null node" << std::endl;
    }
}

// 打印整个树
void PrintTree(const TreeNode* pRoot) 
{
    if (pRoot == nullptr) 
    {
        std::cout << "Empty tree" << std::endl;
        return;
    }

    std::cout << "Tree structure:" << std::endl;
    PrintTreeNode(pRoot);

    for (const auto& child : pRoot->m_vChildren) 
    {
        PrintTree(child);
    }
}

// 销毁整个树
void DestroyTree(TreeNode* pRoot) 
{
    if (pRoot == nullptr) 
    {
        return;
    }

    for (auto& child : pRoot->m_vChildren) 
    {
        DestroyTree(child);
    }

    delete pRoot;
}
#endif

/***************************************End************************************************/

//《剑指Offer 数据结构与算法》


//面试题3：前n个数字二进制形式中1的个数
#if 1
#include <iostream>
#include <vector>
using namespace std;

void CountBits(int num,vector<int>& );

int main()
{
    unsigned int num;
    cin >> num;

    //数字0到数字num
    vector<int> vec(num+1);

    try
    {
        CountBits(num, vec);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    for (const auto& x : vec)
        cout << x << " ";

    return 0;
}
//解法一：
//根据i&(i-1)+1 
//将i的二进制形式中最右边的1变成0，也就是说，
//整数i的二进制形式中1的个数比“i & （i - 1）”的二进制形式中1的个数多1
//用O(1)的时间计算出数字i的二进制有多少位的值为1
#if 0
void CountBits(int num, vector<int>& vec)
{
    if (num < 0)
        throw exception("Invalid number");

	vec[0] = 0;

    if (num == 0)
    {
        return;
    }

    for (int i = 1; i <= num; ++i)
    {
        vec[i] = vec[i & (i - 1)] + 1;
    }

    //错误理解：
    //vec[i] = vec[i & (i - 1)] + 1;等价于vec[i] = vec[i - 1] + 1;
    //反例：
    //i为4时，i & (i - 1)为0

    return;
}
#endif

//解法二：
//如果正整数i是一个偶数，那么i相当于将“i / 2”左移一位的结果，因此偶数i和“i / 2”
//的二进制形式中1的个数是相同的。如果i是奇数，那么i相当于将“i / 2”左移一位之后
//再将最右边一位设为1的结果，因此奇数i的二进制形式中1的个数比“i / 2”的1的个数多1。
#if 1
void CountBits(int num, vector<int>& vec)
{
    if (num < 0)
        throw exception("Invalid number");

    vec[0] = 0;

    for (int i = 1; i <= num; ++i)
    {
        vec[i] = vec[ i >>1 ] + (i&1);//***注***小括号必须加
    }

    return;
}
#endif
#endif