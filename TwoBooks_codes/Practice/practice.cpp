//二叉树层序遍历
#if 0
#include <iostream>
#include <queue>

using std::queue;

struct BinaryTreeNode
{
    double                 m_dbValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};
//***注***
//BinaryTreeNode结构体必须要和Tree.h中声明的一致

__declspec(dllexport) BinaryTreeNode* CreateBinaryTreeNode(double dbValue);
__declspec(dllexport) void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
__declspec(dllexport) void DestroyTree(BinaryTreeNode* pRoot);

/*
注：
链接器使用的是Typical_programming_problem.lib  文件
这个文件用于链接到Typical_programming_problem.dll文件，.dll 文件：是运行时必须的实际库文件。
*/

void breadthFirst(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;

    queue<BinaryTreeNode*>BTN;
    BTN.push(rootNode);

    int cnt = 1;
    int this_level_elements = 0;

    while (!BTN.empty())
    {
        std::cout << BTN.front()->m_dbValue << ' ';
        BinaryTreeNode* tmp = BTN.front();
        BTN.pop();
        --cnt;

        if (!tmp)
            break;

        if (tmp->m_pLeft)
        {
            BTN.push(tmp->m_pLeft);
            ++this_level_elements;
        }
        if (tmp->m_pRight)
        {
            BTN.push(tmp->m_pRight);
            ++this_level_elements;
        }

        if (!cnt)
        {
            std::cout << std::endl;

            cnt = this_level_elements;
            this_level_elements = 0;
        }
    }
}

int main()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

    ConnectTreeNodes(pNode1, pNode2, pNode3);
    ConnectTreeNodes(pNode2, pNode4, nullptr);
 
    breadthFirst(pNode1);

    DestroyTree(pNode1);

    return 0;
}
#endif


//更高效的赋值运算符重载函数
#if 0
#include <cstring>
#include <algorithm>
#include <iostream>

class CMyString
{
public:
    CMyString(char* pData = nullptr)
    {
        m_pData = pData;
    }

    CMyString(const CMyString& str)
    {
        const char* SourceString = str.m_pData;

        if (SourceString)
        {
            size_t totalLength = strlen(SourceString) + 1;
            m_pData = new char[totalLength];
            std::copy(SourceString, SourceString + totalLength, m_pData);
        }
        else
            m_pData = nullptr;
    }

    ~CMyString(void)
    {
        if (m_pData != nullptr)
            delete[] m_pData;
    }

    CMyString& operator = (const CMyString& str);

    void Print()
    {
        std::cout<<m_pData<<std::endl;
    }

private:
    char* m_pData;
};

CMyString& CMyString::operator = (const CMyString& str)
{
    const char* SourceString = str.m_pData;

    if(this== &str)
    {
        /*类的成员函数可以访问同类的所有对象实例的私有和保护成员*/
        return *this;
    }

    auto tmp = new char[std::strlen(SourceString)+1];

    if (tmp)
    {
        std::copy(SourceString, SourceString+ strlen(SourceString)+1, tmp);

        delete [] m_pData;
        m_pData = tmp;
    } 

    return *this;
}


int main()
{
    char* string = new char [7] {"aabbcc"};

    CMyString CMS1(string);

    CMyString CMS2;
    CMS2 = CMS1;
    CMS2.Print();

    CMyString CMS3(CMS2);
    CMS3.Print();
    
    return 0;
}
#endif


//数字与字符串的转换
#if 0
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string str("aabbcc");

    str += to_string(123);

    const char* zifuchuan = str.c_str();
    cout << zifuchuan << endl;

    char* zifuchaun_1 = const_cast<char*>(str.c_str());
    cout << zifuchaun_1 << endl;

    ostringstream oss;
    oss << 2024;
    str.clear();
    str = oss.str();
    cout << str << endl;

    return 0;
}
#endif


//数组中重复的数字
#if 0
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool IsDuplicated(const vector<int>& data)
{
    if (data.empty())
        throw new exception("Error!");

    //vector<pair<int,int>>hash(data.size());
    unordered_map<int, int> hash;

    for (auto x : data)
    {
        if (hash.find(x) == hash.end())
            hash[x] = 1;
        else
            hash[x]++;
    }

    return (hash.size() != data.size());
}

int main()
{
    vector<int> DataInput{2,3,1,0,2,5,3};

    cout << IsDuplicated(DataInput);

    return 0;
}
#endif


//替换空格
#if 0
#include <iostream>

using namespace std;

shared_ptr<char[]> replace(const char* data)
{
    if (data == nullptr)
        exit(1);

    int spaceCnt = 0;
    int i;
    for (i = 0; data[i] != '\0'; ++i)
    {
        isspace(data[i]) ? spaceCnt++ : spaceCnt;
    }

    shared_ptr<char[]> res =make_shared<char[]>(i - spaceCnt);
    int index = 0;
    for (i = 0; data[i] != '\0'; ++i)
    {
        if (isspace(data[i]))
            continue;
        res[index++] = data[i];
    }

    return res;
}

int main()
{
    char string[] = "We are happy";

    shared_ptr<char[]>res = replace(string);

    cout << res.get();

    return 0;
}
//报错：
//=":无法从”Ux(*const )“转换为”char
#endif
#if 0
#include <iostream>
#include <cctype>
using namespace std;

shared_ptr<char[]> replace(const char* data)
{
    if (data == nullptr)
        exit(1);

    int spaceCnt = 0;
    int i;
    for (i = 0; data[i] != '\0'; ++i)
    {
        isspace(data[i]) ? spaceCnt++ : spaceCnt;
    }
    //问题在于：
    //shared_ptr<char[]> res = make_shared<char[]>(i - spaceCnt);
    //***注***
    //make_shared 不能直接用于数组，因为它不支持为动态数组分配内存。

    shared_ptr<char[]> res(new char[i - spaceCnt+1]);

    int index = 0;
    for (i = 0; data[i] != '\0'; ++i)
    {
        if (isspace(data[i]))
            continue;
        res[index++] = data[i];
    }
    res[index] = '\0';

    return res;
}

int main()
{
    char string[] = "We are happy";

    shared_ptr<char[]>res = replace(string);

    cout << res.get();

    return 0;
}
#endif


//剪绳子
#if 0
#include <iostream>

using  namespace std;

int CalMaxMultiply(int n)
{
    if (n == 0||n==1)
        return -1;

    if (n == 2)
        return 1;
    if (n == 3)
        return 2;

    shared_ptr<int[]> res(new int [n + 1] {0});

    res[1]=1, res[2] = 2, res[3] = 3;

    for (int i = 4; i <= n; ++i)
    {
        int max = 0;

        for (int j = 1; j <= i / 2; ++j)
        {
            int tmp = res[j] * res[i - j];
            max >= tmp ? max : max = tmp;
        }

        res[i] = max;
    }

    return res[n];
}

int main()
{
    int length = 8;

    cout << CalMaxMultiply(length) << endl;

    return 0;
}
#endif


//将十进制数字用字母A~Z表示
#if 0
#include <iostream>
#include <vector>
using namespace std;

vector<char> MyConvert(int num)
{
    if (num < 0)
        //throw exception("Error");
        throw bad_exception();

    vector<char>res;

	while (num)
    {
        res.push_back((num % 26)  -1 + 'A');
        
        num /= 26;
    }

    return res;
}

int main()
{
    int num = 26;

    vector<char> res;

    res = MyConvert(num);

    for (auto it = res.crbegin(); it != res.crend(); ++it)
        cout << *it;
    cout << endl;

    return 0;
}
#endif


//二进制中1的个数
#if 0
#include <iostream>

using namespace std;

inline int CalOneOfNum(int num)
{
    int flag = 1;
    int cnt = 0;
    int i = 0;
    while (i != 32)
    {
        if (flag & num)
            ++cnt;

        flag <<= 1;
        ++i;
    }

    return cnt;
}

int main()
{
    int num = -1;

    cout << CalOneOfNum(num);

    return 0;
}
#endif


//
#if 1

#endif
