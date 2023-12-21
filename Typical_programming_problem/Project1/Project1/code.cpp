//
#if 1

#endif


//������1����ֵ���������
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

//����ⷨ��
#if 0
//�������Ĳ����������ö���ʵ������ô���βε�ʵ�λ����һ��
//���ƹ��캯�����Ѳ�������Ϊ���ÿ��Ա�����������ν���ģ�
//����ߴ����Ч�ʡ�ͬʱ�������ڸ�ֵ����������ڲ���ı�
//�����ʵ����״̬�����Ӧ��Ϊ��������ò�������const�ؼ��֡�
CMyString& CMyString::operator = (const CMyString& str)
{
    //����д����
	//if (*this == str) //ԭ�������֮����==������������������û�б����ض��塣

    if (this == &str)//1.����Ƿ������Ҹ���
        return *this;

    delete[] m_pData;//2.�ͷ�m_pDataָ���ԭ��������

    size_t len = strlen(str.m_pData);//3.Ϊ���ַ��������㹻���ڴ�ռ�
    m_pData = new char[len + 1];
    strcpy(m_pData, str.m_pData);

    return *this;//4.ʵ��������ֵ
}
#endif

//�߼��ⷨ1��
#if 0
//һ���ڸ�ֵ����������ڲ��׳�һ���쳣��
//CMyString��ʵ�����ٱ�����Ч��״̬�����Υ����
//�쳣��ȫ��(Exception Safety)ԭ��
CMyString& CMyString::operator = (const CMyString& str)
{
    if (this == &str)
        return *this;

    //����ԭ���ݵĵ�ַ
    char* DataTemp = m_pData;

    if (m_pData = new char[strlen(str.m_pData) + 1])
    {
        //����̬�ڴ�������뵽
        delete [] DataTemp;

        strcpy(m_pData, str.m_pData);
    }

    return *this;

	/* ����new���������ݣ�����delete�ͷ����е����ݡ�����
		ֻ�ڷ������ݳɹ�֮�����ͷ�ԭ�������ݣ�Ҳ���ǵ������ڴ�ʧ��ʱ
		������ȷ��CMyString��ʵ�����ᱻ�޸� */
}
#endif

//�߼��ⷨ2��
//Ч�ʸ���
#if 1
CMyString& CMyString::operator = (const CMyString& str)
{        
    if (this != &str)
    {
        CMyString strTemp(str);//������ƹ��캯����ʹ��new�ģ�

        //�������������������Զ����Swap����ʵ�֣�
        //������ʱָ�����ʱ�����˽�����ݳ�Ա�ĵ�ַ
        char* pTemp = strTemp.m_pData;
        //��ʱ�����˽�����ݳ�Ա�滻Ϊ��ǰ������˽�����ݳ�Ա�ĵ�ַ
        strTemp.m_pData = m_pData;
        //��ǰ������˽�����ݳ�Ա�滻Ϊ��ʱ�����˽�����ݳ�Ա�ĵ�ַ
        m_pData = pTemp;
        //�൱�ڽ�����һ����������
    }

    //***ע***
    //����strTemp��һ���ֲ����������������е�if������ʱҲ�ͳ���
    //�ñ����������򣬾ͻ��Զ�����strTemp��������������strTemp.m_pData
    //��ָ����ڴ��ͷŵ�������
    //strTemp.m_pDataָ����ڴ����ʵ��֮ǰm_pData���ڴ棬
    //����൱���Զ��������������ͷ�ʵ�����ڴ档

    //�����Դӡ�Effective C++��P56 �н������

    return *this;

    /* ���ȴ���һ����ʱʵ�����ٽ�����ʱʵ����ԭ����ʵ�� */
}
#endif
#endif


//������2��ʵ��Singletonģʽ
//(���һ���ֻ࣬�����ɸ����һ��ʵ��)
#if 0

//���󷽷���
//***ע***
//��̬��Ա����������г�ʼ���������������
#if 0
class Singleton
{
private:
    static Singleton* instance;

    Singleton()//��P382 �ô��������˱������Զ����ɵ�Ĭ�ϵ�Ĭ�Ϲ��캯����
    {}//����Ϊ˽�еģ���ָ��������ֱ����Ĭ�Ϲ��캯�����ɶ���

public:
    //����Ҫʵ��ʱ�����þ�̬��������������
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

//��������������װ��ʱ����˳�ʼ������̬��Ա�����ʼ���ɹ�
//������ٶ����������������ȡ������ٶȿ죬��һ�ֵ��͵���ʱ�任ȡ�ռ������
//�ŵ㣺�̰߳�ȫ
//ȱ�㣺�������ò�����������������ȴ���������������˷��ڴ�ռ�
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

//�������������г�ʼ������const�ľ�̬��Ա����
//���ھ�̬���Ա��������������֮��ʹ�õ�������������г�ʼ��
Singleon* Singleon::instance = new Singleon();
//***ע***
//�˴����Ե���Ĭ�Ϲ��캯����ԭ��������װ��ʱ������˳�ʼ��

int main()
{
    //Singleon()���ɷ���
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


//������3���������ظ�������
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

    //���������������ֵ�Ķ�Ӧ��ϵ����¼�������ֵĳ��ִ���
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
//�޸ģ�
//void find_num(int* p, int n)���Ըĳ�
//bool find_num(int* p, int n)
//���ں����ڼ��������Ч����Ĵ����
//{ if(p==nullptr)   ......    }
#endif


//������4����ά�����еĲ���
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
    //ÿ�ζ�ѡ��һ��������������Ͻǵ�Ԫ��
    //��target���ֽ��бȽϣ��Ӷ���С���ҷ�Χ
    //ÿ�ο�����Сһ�е�������Χ

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
    //***ע***
    //��ÿ��ѡ����Ǿ�����������Ͻǻ����½�
    //�Ǿ��޷���С��������

    return false;
}
#endif


//��ʼ���ַ��������洢�ַ����ͳ�ʼ��ָ����ָ���ַ����к�����
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

	//��ʼ������Ѿ�̬�洢�����ַ��������������У�(��str1��str2��������ĳ�ʼ��ַ�ǲ�ͬ��)
	//	����ʼ��ָ��ֻ���ַ����ĵ�ַ������ָ��
}
#endif


//������5���滻�ո�
//��ͨ�ⷨ��
//��������ǰ����滻���������Խ�Ǻ�����ַ���
//���ƶ��Ĵ���Խ�࣬���ʱ��Ч�ʵ���
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

            //***ע***
            //����Ҫ������һ�䣬��������itָ�����λ��
            it = s.begin();
        }
        //Expression: cannot increment string iterator because the iterator wasinvalidated (e.g. reallocation occurred, or the string was destroyed)
        //***ע***
        //�ڽ��е�������������ʱ��ԭ����������Ӧ���ټ���ѹ���κ�Ԫ���ˣ��������������ʧЧ��
        //vector�ĵ�����ʧЧ��ԭ���ǣ�vector�����˸ı�������С��ע����capacity����size���Ĳ��������ʱ��
        //�������������ڴ�ռ䡿��
        //����ԭ����Ԫ�ؽ��п��������ʱ��ָ��ԭ��λ�õ�iterator�Ծ�ָ��ԭ����λ�ã�
        //����ʱԭ����λ�õ�Ԫ��������vector���ݲ����ﱻɾ���ˣ��ʴ�ʱiteratorָ�����һ��δ֪��ֵ���ʵ�����ʧЧ
        //https ://blog.csdn.net/m0_48966435/article/details/119775625
    }

    flag = true;

    return flag;
}
#endif
//�õĽⷨ��
//�ȱ���һ���ַ�����ͳ�Ƴ��ո�����������Լ����
//�滻֮���ַ����ĳ���
//�Ӻ���ǰ���ƣ��������ܼ����ƶ��Ĵ������Ӷ����Ч��
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
    //�������
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
    //p2ָ��Ҫ�洢��res�е�source�ӳ���Ŀ��ַ���
    int p2 = length + 2 * space_count;
    //p1ָ��sourceĩβ�Ŀ��ַ���
    int p1 = length;

    //��覴õ�д����
    //�޷������ַ���������������ո�
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
     
    //�޸ģ�
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
//�ںϲ���������(�����ַ���)ʱ�������ǰ������ÿ������(��
//�ַ�)����Ҫ�ظ��ƶ�����(���ַ�)��Σ���ô���ǿ��Կ��ǴӺ���ǰ
//���ƣ��������ܼ����ƶ��Ĵ������Ӷ����Ч�ʡ�


//������6����β��ͷ��ӡ����
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

//�ݹ鷨��
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
//���ڵݹ�Ĵ��뿴�����ܼ�࣬����һ�����⣺������ǳ���
//��ʱ�򣬾ͻᵼ�º������õĲ㼶����Ӷ��п��ܵ��º�������ջ�����
//��Ȼ��ջ����ѭ��ʵ�ֵĴ����³����Ҫ��һЩ��


//������7���ؽ�������
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
                                //ǰ��������ַ������ַ                                         ����������ַ������ַ
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    //ǰ������ĵ�һ�������Ǹ��ڵ��ֵ
    int rootValue = startPreorder[0];

    //�����սڵ�
    BinaryTreeNode* root = new BinaryTreeNode();

    //Ϊ�ڵ㸳ֵ
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = nullptr;

    //��ǰ������������һ��Ԫ��
    if (startPreorder == endPreorder)
    {
        if (startInorder == endInorder && *startPreorder == *startInorder)
            return root;
        else
            throw std::exception("Invalid input");
    }

    //����������������ҵ����ڵ��ֵ
    int* rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue)
    {
        ++rootInorder;
    }

    //�������������δ�ҵ���ǰ������г��ֵĸ��ڵ�
    if(rootInorder==endInorder&&*rootInorder!=rootValue)
        throw std::exception("Invalid input");

    //�����������
    //�������ָ���ľ���ֵ����Ϊ�������ĸ�����ֵ
    int leftLength = rootInorder - startInorder;
    //��ǰ�������
    //����ָ��ָ�����������е�ĩβ��λ��
    int* leftPreorderEnd = startPreorder + leftLength;

    if (leftLength > 0)
    {
        //����������
        root->m_pLeft = ConstructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    }
    
    if(leftLength<endPreorder-startPreorder)
    {
        //����������
        root->m_pRight = ConstructCore(leftPreorderEnd +1,endPreorder,rootInorder+1,endInorder);
    }

    return root;
}
#endif


//������8������������һ���ڵ�
//����һ�Ŷ�����������һ����������µĽڵ�ţ�Ҫ���������һ���ڵ㡣
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

    //����һ���ڵ�ָ�����ڴ洢��һ���ڵ�ĵ�ַ
    BinaryTreeNode* pNext = nullptr;

    if (pNode->m_pRight != nullptr)
    {
        //���ýڵ�����������
        //��ô������һ���ڵ����������������������ӽڵ�
        BinaryTreeNode* pRight = pNode->m_pRight;

        while (pRight->m_pLeft != nullptr)
        {
            pRight=pRight->m_pLeft;
        }

        pNext = pRight;
    }
    else if (pNode->m_pParent != nullptr)//���и��ڵ�
    {
        //���ýڵ����������Ҹýڵ����丸�ڵ�����ӽڵ㣬
        //��ô������һ���ڵ�������ĸ��ڵ�
        
        //���ýڵ����������Ҹýڵ����丸�ڵ�����ӽڵ㣬
        //��ô������һ���ڵ��������ָ�򸸽ڵ��ָ��һֱ���ϱ���ʱ��
        //һ���������������Ľڵ㣺
        //ĳ���ڵ����丸�ڵ�����ӽڵ㣬��ýڵ�ĸ��ڵ�������������Ľڵ㡣

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


//������9��������ջʵ�ֶ���
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


//����������ʵ��ջ
//����ջ�Ǻ���ȳ������������Ԫ�غ�
//��Ҫ��������Ҫ������Ӧ������������Ԫ�ء�
//��ô��Ҫ��queue1���ϵ�����ͷԪ�ص�queue2��
//ֱ����ʣ1��Ԫ�أ�������Ԫ�ض�������queue2��
//���queue1��
//ͬ���ٴε���Ԫ��ʱ��queue2Ҫ������queue1����Ԫ�ء�
//ֱ��queue2��ʣ1��Ԫ�أ�Ȼ���Ԫ��ֵ������Ϊ����ֵ��
//queue2��ա�������ʵ����ջ���Ƚ��ȳ����ܡ�
#if 1

#endif


//������10��쳲���������
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

//��̫�õĽⷨ��
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
//������F(10)ʱ�ĵݹ�����������Է��֣�
//�ظ��Ľڵ���̫�༴�ظ��ļ���̫��

//�ϺõĽⷨ
//�����ظ��ļ��㣬�ǾͰ��Ѿ��õ����м������������ô�Ͳ����õݹ���
//ѡ����ѭ��
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


//������̨������
//���ܿ�����1��Ҳ������2��
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


//��С����ȥ���Ǵ���εķ������������ʻ���쳲���������
#if 1

#endif


//ʵ�ֿ��������㷨
//���ģ�����������ѡһ�����֣��ٽ���ѡ������ִ�������Ƶ������ұ�
//����ѡ�������С�������Ƶ��������
//����������ʵ��������ǰ����Ϊ������ð����������������Ƕ����ڽ��������ࡣ
//����Ҳ��ͨ�����ϱȽϺ��ƶ�������ʵ������ģ�ֻ��������ʵ�֣�
//�����˼�¼�ıȽϺ��ƶ��ľ��룬���ؼ��ֽϴ�ļ�¼��ǰ��ֱ���ƶ������棬
//�ؼ��ֽ�С�ļ�¼�Ӻ���ֱ���ƶ���ǰ�棬�Ӷ��������ܵıȽϴ������ƶ�����������
#if 0
#include <iostream>
#include <exception>
#include <ctime>
using namespace std;

int RandomInRange(int a,int b)
{
    srand((unsigned int)time(0));
    // ���� [0, max]
    //int x = rand() % (max + 1);

    // ���� [1, max]
    //int x = 1 + rand() % (max);

    // ���� [min, max] ��Χ�������
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

//***begin��end��ָ��������ֵ***
int Partition(int data[], int length,int begin,int end)
{
    if (data == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //����һ����ָ����Χ�ڵ������
    int index = RandomInRange(begin,end);
    //���������Ϊ����ֵ��Ӧ������������ĩβ�����ֽ���
    //��ô����ĩβ�����־����������ֵ��Ӧ������
    Swap(&data[index],&data[end]);

    //��������small�洢����ֵ�����ʼֵ��beginС1���磺beginΪ0����smallΪ-1
    int small = begin - 1;
    
    //����ֵ��ͷ��ʼ��������
    for (index = begin; index < end; ++index)
    {
        //����ǰ����ֵָ������ֱ��������ֵָ�������С
        if (data[index] <= data[end])//ע����С�ڵ���
        {
            //����small��ֵ
            ++small;

            //��small��Ϊ��ǰ������ֵ
            if (small  !=  index)
                Swap(&data[index],&data[small]);//����Ԫ�أ�Ŀ����
            //������ֵsmall����ֵ��С�ڸ�����ֵ����Ӧ��ֵ
        }        
    }
	//��small������1
	++small;
	//���������ֵָ��������ƶ���smallָ���λ����
	Swap(&data[small], &data[end]);

    //������������λ��
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


//����һ����С��Χ�ڵ��������У�Ҫ������ʱ�临�Ӷ�ΪO(n)
#if 0
void SortAges(int* ages, int length)
{
    if (ages == nullptr || length <= 0)
        return;

    const int OldestAge = 99;

    //����һ������洢������ĳ��ִ���
    int TimesOfAge[OldestAge + 1] = {0};//һ��Ҫ�ȳ�ʼ��

    for (int i = 0; i < length; ++i)
    {
        TimesOfAge[ages[i]]++;
    }

    //***ע***
    //���������������򣬶�������������½������
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


//�����������Ҫ�������������(���߲������������)�в���һ������
//����ͳ��ĳ�����ֳ��ֵĴ�������ô���Ƕ����Գ����ö��ֲ����㷨��
//������11����ת�������С����
//����ת�����У������ǰѵ�����������ǰ������ɸ����ְᵽ����ĺ��棬
//��˵�һ���������Ǵ��ڻ��ߵ������һ�����֡�
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
//���ֲ��ҷ���ʱ�临�Ӷ�ΪO(logn)
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
            p1 = mid;//������м�Ԫ��λ��ǰ��ĵ��������飬
        //��ô��Ӧ�ô��ڻ��ߵ��ڵ�һ��ָ��ָ���Ԫ�ء���ʱ��������С��Ԫ��
        //Ӧ��λ�ڸ��м�Ԫ�صĺ��档���ǿ��԰ѵ�һ��ָ��ָ����м�Ԫ�أ�
        //����������СѰ�ҵķ�Χ���ƶ�֮��ĵ�һ��ָ����Ȼλ��ǰ��ĵ��������顣
        else
            p2 = mid;
    }

    return numbers[p2];
}
#endif
//覴ã��������������ǰ��0�����ְᵽ���棬��ô�ô����޷�֧�֡�
//�޸ģ�
#if 0
int Min(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        throw new exception("Error !");

    int p1, p2;
    p1 = 0, p2 = length - 1;

    //��ʼ��Ϊ��Ԫ�ص�����ֵ����֧���ƶ�0�����ֵ����
    int mid=p1;

    //��Ԫ����Ҫ���ڵ���ĩβ��Ԫ�ز��ܽ���ѭ��
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
//覴ã�������p1��p2���м��������ͬ���������1��0��1��1��1��1
//������޷�֧��
#if 1
int Min(int* numbers, int length)
{
    if (numbers == nullptr || length <= 0)
        throw new exception("Error !");

    int p1, p2;
    p1 = 0, p2 = length - 1;

    //��ʼ��Ϊ��Ԫ�ص�����ֵ����֧���ƶ�0�����ֵ����
    int mid = p1;

    //��Ԫ����Ҫ���ڵ���ĩβ��Ԫ�ز��ܽ���ѭ��
    while (p2 - p1 != 1 && numbers[p1] >= numbers[p2])
    {
        mid = p1 + (p2 - p1) / 2;

        //����������������p1��p2���м��������ͬ
        if (numbers[p1] == numbers[p2] && numbers[p1] == numbers[mid])
            return MinInOrder(numbers,length);

        if (numbers[mid] >= numbers[p1])
            p1 = mid;
        else
            p2 = mid;
    }

    return numbers[mid];
}

//������������ֻ�ܲ���˳����ҷ���
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


//������12�������е�·��
//��dfsģ����
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
//�û��ݷ�ģ����
#if 0
#include <iostream>
#include <vector>
using namespace std;

bool hasPath(int index, int row, int column);
bool check(const char* ch1, const char* ch2);

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

//����д������
//bool hasPath(char[][] matrix, );

//***ע***
//����д���ڶ�̬��������Ĵ�С���������ж��ɶ�̬�仯
bool hasPath(vector<vector<char>>& matrix, int row, int col,
    const char* target);

//���Ĵ����
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

    //����дʧ��
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

    //·�����ԴӾ��������һ��ʼ
    for(int r=0;r<row;r++)
        for (int c = 0; c < col; c++)
        {
            if (hasPathCore(matrix, row, col, r, c, target, index, visit))
                return true;
            else
                visit[r][c] == false;//ȡ���ѷ��ʵı��
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
        //���Ϊ�ѷ���
        visit[r][c] = true;

        for (int i = 0; i < 4; i++)
        {
            int r1 = r + dx[i];
            int c1 = c + dy[i];

            if (r1 >= 0 && r1 < row && c1 >= 0 && c1 < col)
            {
                flag = hasPathCore(matrix, row, col, r1, c1, target, index + 1, visit);
                
                //����д������䣬����ݹ���ݺ����ķ���ֵ����false
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


//������13�������˵��˶���Χ
#if 0
#include <iostream>
#include <vector>
using namespace std;

int movingCount(int threshold, int row, int col);

//***ע***
//����д����ָ��visit���������
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

    //***ע***
	//����һ����Ϊrow����Ϊcol����ʼֵΪfalse�Ķ�ά����
    //����һ��������ֱ�ӳ�ʼ��
    vector<vector<bool>>visit    (row,vector<bool>(col, false));

    //***ע***
    //����������resize����ǰ����
    //vector<vector<int>> new_mat(r);//ע�����r�ǲ���ȱ�ٵģ��涨���ж�����
    //for (int i = 0; i < r; i++) //��άvector�ĳ�ʼ��ʱ��Ҫ���
    //{
    //    new_mat[i].resize(c);
    //}

	//��������ÿ�в�һ�����������������ÿ�е��н��в���
	//	����Ҳ���ԣ�����������ʱ������һ��Ҫ�У���Ȼ��push_back�Ϳ����ˣ�
	//	vector<vector<int>>mat(r);//ÿ�еĶ���
	//mat[i].push_back(1);//����Ǹõ�i+1�еĲ���һ��Ԫ�أ�ֵΪ1

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
        
//***ע***
//�����ڵݹ�����е���ջ��ջ��Ϊ���������´���ó������ֲ���ȷ
//��һ��Ҫ�ô˴���飬��Ҫ�õ�ȫ�ֱ���count

 /*       for (int i = 0; i < 4; i++)
        {
            int r1 = r + dx[i];
            int c1 = c + dy[i];

            if (check(threshold, row, col, r1, c1, visit))
            {
                cout << r1<<"��" << c1 <<" " << count << " " << endl;
                count=1+movingCountCore(threshold, row, col, r1, c1, visit);                
                cout << endl;
                cout << r1<<"��" << c1 <<" " << count << " " << endl<<endl;
            }
            else
                continue;
        }
*/

        cout << r << "��" << c << " " << count << " " << endl;
        //����д�ܵõ���ȷ��
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


//������14��������
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

//��̬�滮�ⷨ��
//��Ȼ���ӿ��Լ����ɵ�����ÿ��һ����ֳɵ��������ֵĳ���
//�������Ӧ���ܵõ����˻����ֶ�Ӧ�ļ�����
//��������һ�������ֽܷ�ɶ�������⣬ÿ�������ⶼ�������Ž�
#if 0
int maxProuct(int length)
{
    if (length <= 1)
        return 0;
    if (length == 2)
        return 1;
    if (length == 3)
        return 2;

    //����һ����̬�����Դ洢�������ȵ����Ӽ�������м�ֵ
    int* product = new int[length + 1] {0};

    //***ע***
    //�˴�product[1]Ϊ1����Ϊ��Ҫ��Ϊ�����õ��Ĳ��ֵĳ���ֵ��
    //��������ΪҪ�Գ���Ϊ1�����ӷָ��ɵõ������˻�ֵ
    //product[2]��product[3]ͬ��
    product[1] = 1;
    product[2] = 2;
    product[3] = 3;

    //���ӵĳ���
    for (int i = 4; i <= length; i++)
    {
        //��������max�Դ洢�Ѽ������ֵ�����ڱȽ�
        int max = 0;

        //����һ���ָ��j
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

//̰���㷨
//�������µĲ����������ӣ���õ��ĸ������ӵĳ��ȵĳ˻�
//����󣺵�n��5ʱ�����Ǿ����ܶ�ؼ�����Ϊ3�����ӣ���ʣ�µ�����
//����Ϊ4ʱ�������Ӽ������γ���Ϊ2�����ӡ�
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


//��ʮ������������ĸA~Z��ʾ
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


//������15����������1�ĸ���
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

//�ⷨһ����num����ʮ����������ȡ��ķ���ת���ɶ�����
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

//�ⷨ������num���ɶ�����������λ�������1�ĸ���
#if 0
int number_of_one(int num)
{
    int  cnt = 0;

    while (num)
    {
        if (num & 0x01)
            cnt++;

        num >>= 1;//***ע***
    }                      //����Ч�ʱ���λ����Ҫ�͵ö࣬ʵ�ʱ����Ҫ��������ʹ�ó˳�����
                           //��������λ���������
    return cnt;
}
#endif
//覴ã������λΪ1�����������ѭ��

//�����ƵĽⷨ��
//���Ը��������ֱ��������λ���㣬���Ƕ�flag������λ�������ж�ÿλ�Ƿ�Ϊ1
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

//�����Ը�ǿ�Ľⷨ��
// ***��***
//��һ��������ȥ1,�ٺ�ԭ�����������㣬��Ѹ��������ұߵ�1���0��
//��ôһ�������Ķ����Ʊ�ʾ���ж��ٸ�1,�Ϳ��Խ��ж��ٴ������Ĳ�����
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


//һ����������Ҫ�ı����λ���ܵõ���һ����������
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
//��ʹ��forѭ������ʹ��������㣬Ȼ��ͳ�����е�1�ĸ���
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


//��ջʵ�ֶ�������������ȱ���
#if 0
#include <iostream>
#include<stack>
struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

//ǰ����������ݹ�
void preorder(BinaryTreeNode * rootNode)
{
    if (!rootNode)
        return;

    //��->��->��
    std::cout << rootNode->m_nValue << " ";
    preorder(rootNode->m_pLeft);
    preorder(rootNode->m_pRight);
}

//ǰ���������ʹ��ջ
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
            tempNode = tempNode->m_pLeft;//��->��
        }
        else 
        {
            tempNode = nodeStack.top();
            nodeStack.pop();
            tempNode = tempNode->m_pRight;//��
        }
    }
}

//������������ݹ�
void inorder(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;
    //��->��->��	
    inorder(rootNode->m_pLeft);
    std::cout << rootNode->m_nValue << " ";
    inorder(rootNode->m_pRight);
}

//������� --ջ
template<typename T>
void inorder2(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* tempNode = rootNode;

    while (!nodeStack.empty() || tempNode)
    {
        if (tempNode) {
            nodeStack.push(tempNode);
            tempNode = tempNode->m_pLeft;//��
        }
        else {
            tempNode = nodeStack.top();
            nodeStack.pop();
            std::cout << tempNode->m_nValue << " ";
            tempNode = tempNode->m_pRight;//��->��
        }
    }
}

//������������ݹ�
void postorder(BinaryTreeNode* rootNode)
{
    if (!rootNode)
        return;
    //��->��->��	
    postorder(rootNode->m_pLeft);
    postorder(rootNode->m_pRight);
    std::cout << rootNode->m_nValue << " ";
}

//�����������ջ
void postorder2(BinaryTreeNode* rootNode)
{
    std::stack<BinaryTreeNode*> nodeStack;
    BinaryTreeNode* curNode = rootNode; //��ǰ�ڵ�
    BinaryTreeNode* preNode = nullptr; //֮ǰ���ʹ��Ľڵ㣬������

    //��cur�ƶ������������±�
    while (curNode)
    {
        nodeStack.push(curNode);
        curNode = curNode->m_pLeft;
    }

    while (!nodeStack.empty())
    {
        //�ߵ����cur�գ����Ѿ��������������׶�
        curNode = nodeStack.top();
        nodeStack.pop();

        //���һ����ѷ��ʲŷ��ʸ��ڵ�
        if (!curNode->m_pRight || curNode->m_pRight == preNode)
        {
            std::cout << curNode->m_nValue << " ";
            preNode = curNode;
        }
        //������δ����
        else {
            //���ڵ��ٴ���ջ
            nodeStack.push(curNode);
            //����������
            curNode = curNode->m_pRight;
            //��cur�ƶ��������������������±�
            while (curNode)
            {
                nodeStack.push(curNode);
                curNode = curNode->m_pLeft;
            }
        }
    }
}
//��������������������������������
//��Ȩ����������ΪCSDN����������������ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/gongjianbo1992/article/details/88378805
#endif


//������ʵ�ֶ������Ĺ�����ȱ���(�������)
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


//***ע***
//����Ĺ淶�ԣ���д������������������������
//����������ԣ����ܲ��ԡ��߽���ԡ�������
//�����³���ԣ���ȡ�����Ա�̴�����Ч������


//������16����ֵ�������η�
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
//覴ã�û�п���ָ���Ǹ��������
//ָ���������Ǹ���
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

//������n�η���Ч�ʸ��ߵĽⷨ��
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

    //nΪż��ʱ��a��n�η�����a��n/2�η�����a��n/2�η�
    //nΪ����ʱ��a��n�η�����a��n/2�η�����a��n/2�η�����a
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result *= result;

    if ((exponent & 0x1) == 1)
        result *= base;

    return result;
}
//�Ż������ϸ�ڣ�
//1.ʹ���˹�ʽ��a��n�η����Ƚ���ѭ����Ҫ��2��ʱ��
//2.����λ�������˳�����
//3.��λ��������������������ж�������ż��
#endif


//������17����ӡ��1������nλ��
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

//û�п��Ǵ�������
//���������n�ܴ��ʱ������������nλ��ʱ��
//������(int)���߳�����(long long)�������
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

//�ⷨ1��
//�����ַ�����ģ��ӷ�
#if 0
void Paint_1_to_n(long  long n)
{
    if (n < 1)
        throw new exception("Invaild data !");

    //����number�ַ��������洢�����ַ�   

    //***ע***
    //����д���Ὣ��һ��Ԫ������Ϊ�ַ�0��������Ԫ������ΪASCIIֵ0������Ӧ�ַ�'\0'
    //char* number = new char[n + 1]{'0'};

    char* number = new char[n + 1];
    fill(number, number + n + 1,'0');

    //for (int i = 0; i < n; i++)
    //    cout << number[i];

    //���ֵ����λ�ĺ�һλ��Ԫ������Ϊ0
    //�Ϳ���������strlen()�����ַ�������
    number[n] = '\0';

    while (!Increment(number))
    {
        PrintNumber(number);
    }

    delete[]number;
}

bool Increment(char* number)
{
    //�������λ��־
    bool isOverflow = false;

    //���λֵ
    int nTake = 0;

    int Length = strlen(number);

    //�����ַ������������λ��ʼ�����λ�ƶ�
    for (int i = Length - 1; i >= 0; i--)
    {
        //��������Sum���λ��ǰ��ֵ
        int Sum = number[i] - '0' + nTake;

        //������ָ�����ֵ����λ
        if (i == Length - 1)
            Sum++;

        //����λ�ϵ�ֵ����1�󣬵�10����Ҫ���д���
        if (Sum >= 10)
        {
            //����λ�����λ
			//***ע***
		    //�����жϷ���ʱ��Ч�ʺã�ΪO(1)
            //����strcmp()�жϣ�ʱ��Ч��ΪO(n)
            if (i == 0)
                isOverflow = true;
            else
            {
                //Sum��10ʱ����λҪ��Ϊ0
                Sum -= 10;
                //��ǰ��1λ
                nTake = 1;
                //���ø�λ�ϵ�ֵ
                number[i] = Sum + '0';
            }
        }
        else
        {
            number[i] = Sum + '0';
            //�˳�ѭ��
            break;
        }
    }

    return isOverflow;
}
void PrintNumber(char* number)
{
    int Length = strlen(number);

    //���ֿ�ͷ��0�ı��
    bool flag=false;

    //���������ַ�����
    for (int i = 0; i < Length; i++)
    {
        //***ע***
        //��д��������
        //  if (number[i] == '0' && !flag)
        //��������Ϊ010�����ӡ����10         
        
        //���ֽ����㿪ͷ������һ���Ƿ�0ʱ���Ŵ�ӡ
        if (number[i] != '0' && !flag)
            flag = true;

        if (flag)
            printf("%c",number[i]);
    }

    printf("\t");
}
#endif

//�ⷨ2��
//������ת�������ֵ�ȫ���У����õݹ�ʵ��ȫ����
#if 1
void Paint_1_to_n(long  long n)
{
    if (n < 1)
        throw new exception("Invaild data !");

    //����number�ַ��������洢�����ַ�   
    char* number = new char[n + 1];

    //fill(number, number + n + 1, '0');

    //���ֵ����λ�ĺ�һλ��Ԫ������Ϊ0
    //�Ϳ���������strlen()�����ַ�������
    number[n] = '\0';

    for (int i = 0; i < 10; ++i)
    {
        //�������λ��0��9����
        number[0] = i + '0';
                                //���ֳ��ȣ�����ֵ
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

    //���ֳ����λ֮���λ����0��ʼ������9
    for (int i = 0; i < 10; ++i)
    {
        number[index + 1] = i + '0';

        Recursively(number,length,index+1);
    }
}

void PrintNumber(char* number)
{
    int Length = strlen(number);

    //���ֿ�ͷ��0�ı��
    bool flag = false;

    //���������ַ�����
    for (int i = 0; i < Length; i++)
    {
        //***ע***
        //��д��������
        //  if (number[i] == '0' && !flag)
        //��������Ϊ010�����ӡ����10         

        //���ֽ����㿪ͷ������һ���Ƿ�0ʱ���Ŵ�ӡ
        if (number[i] != '0' && !flag)
            flag = true;

        if (flag)
            printf("%c", number[i]);
    }

    printf("\t");
}
#endif
#endif


//������18��ɾ������Ľڵ�
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

//***ע***
//Ѱ�������з���Ҫ��Ľڵ㣬ʱ��Ч��O(n)�����ǲ����
//����Ҫ�Ż������Ѿ��ҵ��÷���Ҫ��Ľڵ�ĵ�ַ��Ҫ��O(1)�ڽ���ɾ������
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if (pListHead == nullptr || pToBeDeleted == nullptr)
        throw new exception("Error !");

    //��������Ľڵ㲻��ǰһ���ڵ��ָ�룬����
    //����ķ�����˳�����ÿ���ڵ㣬�ҵ�Ҫɾ���Ľڵ��
    //�ȶ���ǰһ���ڵ��m_pNextָ���������
    //��ʱ�临�Ӷ�ΪO(n)����ΪҪ������Ҫɾ���Ľڵ��ǰһ���ڵ�

    //���Բ����������ǽ�Ҫɾ���Ľڵ����һ���ڵ�����ݶ�
    //��ֵ��Ҫɾ���Ľڵ㡣�൱��ɾ���˸ýڵ㡣
    //���ַ��������ͷ�Ҫɾ���Ľڵ���ڴ�ռ�

    //��Ҫɾ���Ľڵ���    �ǽ�һ���ڵ������Ҳ    �������β�ڵ�
    if (pToBeDeleted->m_pNext != nullptr)
    {
        //tmpָ��Ҫɾ���Ľڵ����һ���ڵ�
        ListNode* tmp = pToBeDeleted->m_pNext;

        //��һ���ڵ�����ݸ���Ҫɾ���Ľڵ�
        pToBeDeleted->m_nValue = tmp->m_nValue;
        //��һ���ڵ��ָ��������һ���ڵ��ָ���ֵ����Ҫɾ���Ľڵ��m_pNext��Ա
        pToBeDeleted->m_pNext = tmp->m_pNext;

        //ɾ��Ҫɾ���Ľڵ����һ���ڵ�
        delete tmp;

        //***ע***
        //Ҫ������һ�仰
        //��Ϊ��һ��ֻ���ͷ���tmpָ����ָ����ڴ�ռ䣬��
        //tmp�ͻ��ΪҰָ��
        //��Ұָ�롱���� NULL ָ�룬��ָ���������ڴ��ָ�롣
        tmp = nullptr;
    }
    else if (pToBeDeleted->m_pNext==nullptr)//��Ҫɾ�����ǽ�һ���ڵ������
    {
        delete pToBeDeleted;

        pToBeDeleted = nullptr;

        *pListHead = nullptr;
    }
    else//��Ҫɾ������β�ڵ�
    {
        //ֻ���ñ����ķ���
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


//ɾ���������ظ��Ľڵ�
#if 0
#include <iostream>
#include <exception>

using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

//***ע***
//���������Ҫ�����ɾ�������ͷ�ڵ㡣
//ͷ�ڵ���������Ľڵ��ظ���Ҳ����˵ͷ�ڵ�Ҳ���ܱ�ɾ����
//���ɾ������Ӧ������Ϊvoid deleteDuplication(ListNode * *pHead), 
//������void deleteDuplication(ListNode* pHead)��
void DeleteDuplication(ListNode** pHead)
{
    //��ָ��ͷָ���ָ������Ϊnullptr��ͷָ������Ϊnullptr(û�нڵ�)
    if (pHead == nullptr || *pHead == nullptr)
        return;

    //����һ��ָ��ǰ�ڵ��ǰһ���ڵ��ָ��
    ListNode* pPreNode = nullptr;
    //����һ��ָ��ǰ�ڵ��ָ��
    ListNode* pNode = *pHead;

    while (pNode != nullptr)
    {
        //����һ��ָ��ǰ�ڵ�ĺ�һ���ڵ��ָ��
        ListNode* pNextNode = pNode->m_pNext;

        //����һ����ǣ������ڵ��Ƿ��ɾ��
        bool needDelete = false;

        //����ǰ�ڵ��к�һ���ڵ������һ���ڵ�������뵱ǰ�ڵ�������ͬ
        if (pNextNode != nullptr && pNextNode->m_nValue == pNode->m_nValue)
            needDelete = true;//��Ǵ˽ڵ��ɾ��

        //����ǰ�ڵ�ĺ�һ���ڵ������뵱ǰ�ڵ�����ݲ�ͬ
        if (!needDelete)
        {
            //��ǰ�ڵ��ǰһ���ڵ��ָ������Ϊ��ǰ�ڵ�ĵ�ַ
            pPreNode = pNode;
            pNode = pNode->m_pNext;//��ǰ�ڵ��ָ������ƶ�һ���ڵ��λ��
        }
        else//����ǰ�ڵ��к�һ���ڵ������һ���ڵ�������뵱ǰ�ڵ�������ͬ
        {
            int value = pNode->m_nValue;

            //����һ��ָ��Ӧ��ɾ���Ľڵ��ָ��pToBeDeleted���䱻��ʼ��Ϊ��ǰ�ڵ�ĵ�ַ
            ListNode* pToBeDeleted = pNode;

            //��pToBeDeleted��Ϊ��Ч������pToBeDeletedָ��Ľڵ������
            //�뵱ǰָ��ָ��Ľڵ��������ͬ
            while (pToBeDeleted != nullptr && pToBeDeleted->m_nValue == value)
            {
                //pNextNodeָ��ǰ�ڵ�ĺ�һ���ڵ�
                pNextNode = pToBeDeleted->m_pNext;

                //�ͷŵ�ǰ�ڵ���ָ����ڴ�ռ�
                delete pToBeDeleted;
                pToBeDeleted = nullptr;

                //pToBeDeleted�浱ǰ�ڵ�ĺ�һ���ڵ㣬�����Ļ�����ǰ�ڵ�ĺ�һ���ڵ�
                //Ҳ�ᱻɾ��
                pToBeDeleted = pNextNode;
            }

            //����Ҫ����ɾ���Ľڵ��ǰһ���ڵ��m_pNext���ݳ�Ա��ʹ����ڵ�
            //���մ�pNextNodeָ��Ľڵ�ĵ�ַ��������������

            //���ӵ�һ���ڵ㿪ʼ��Ҫɾ�����ɸ��ڵ�
            if (pPreNode == nullptr)
                *pHead = pNextNode;
            else//�����Ǵӵ�һ���ڵ㿪ʼɾ��
                pPreNode->m_pNext = pNextNode;

            //��ǰ�ڵ�ָ���������ظ��������ڵ���һ���ڵ�
            pNode = pNextNode;
        }
    }
}
#endif


//������19��������ʽƥ��
#if 0
#include <iostream>

using namespace std;

                //�ַ���         ģʽ����������ʽ
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

//�����ַ���Ϊaaa
bool matchCore(char* str, char* pattern)
{
    //���ַ�����������ʽ�������������
    if (*str == '\0' && *pattern == '\0')
        return true;

    //��������ʽ�ȱ����������
    if (*str != '\0' && *pattern == '\0')
        return false;

    //�����Ϊ������ʽpatternָ��ָ���λ�ú�ĵ�1���ַ���'*'�Ͳ���'*'
    if (pattern[1] == '*')
    {        
		//if (str[0] == pattern[0] || (pattern[0] == '.' && str[0] != '\0'))

        //����ǰ��ָ��ָ����ַ���ͬ  ��  ������ʽ�ַ�Ϊ'.'���ַ���δ������ĩβ
        if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        {
            //�����ַ�����λ�ú�ĵ�1���ַ���������ʽ��λ�ú�ĵ�2���ַ�
            return matchCore(str + 1, pattern + 2) ||
                //�����ַ�����λ�ú�ĵ�1���ַ���������ʽ��λ�õ��ַ�
                matchCore(str + 1, pattern) ||//��Ϊ������ʽ������a*
                //�����ַ�����λ�õ��ַ���������ʽ��λ�ú�ĵ�2���ַ�
                matchCore(str, pattern + 2)//��Ϊ������ʽ������a*a*
                ;
        }
        else
            //�����ַ�����λ�õ��ַ���������ʽ��λ�ú�ĵ�2���ַ�
            return matchCore(str,pattern+2);//��Ϊ������ʽ������b*a*
    }

    //������ʽpatternָ��ָ���λ�ú�ĵ�1���ַ�����'*'
    if (*str == *pattern || (*pattern == '.' && *str != '\0'))
        return matchCore(str+1,pattern+1);
}
#endif


//������20����ʾ��ֵ���ַ���
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

//������������η��ࣿ
//��������ܶ࣬���Բ���ֱ����һ��ѭ���������ݲ��ж�
//Ҫ�ҵ����ɣ�
//С�������e��Eǰ������ֿ����ñ���ɨ������
//С�����Ļ���e��E������ֲ���ҲҪ�ñ���ɨ��Ļ���
//�ǿ��Խ�����ɨ����Ƴ�һ��ģ��
bool isNum(const char* str)
{
    if (str == nullptr)
        return false;

    //���ֵĿ�ͷ�п��ܳ��������ţ����Ҫ���д���
    //���������ţ���Ҫ��ָ������ƶ�һλ�ľ��룬
    //�����ж��޷��ŵĲ���
    bool flag = scanInteger(&str);

    //�������ϵĴ���Σ�strָ���Ѿ�ָ����С�����e��E
    //������������.123����ǰ������flag=false;
    if (*str == '.')
    {
        ++str;

        //Ҫ�չ˵��������������
        //  .123     123. 
        flag = scanInteger(&str) || flag;

    }

    if (*str == 'e' || *str == 'E')
    {
        ++str;

        //***ע***
        //�˴����룬��Ϊ���ܽ���   .e1   
        flag = scanInteger(&str) && flag;
    }

    //���ܽ���10e+5.4
    return flag && *str == '\0';
}

bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-')
        ++(*str);//***ע***
    //�˴�str����Ϊconst�������ܸı�strָ������ݣ���strָ���ǿ��Ըı��
    //�����ܳ���**str = 0x00;��ָ�������ַ�����ָ�����洢��λ�ò��ܱ�
    //��ָ�������ַ�����ָ��洢�����ݿ��Ա䡣    
    //��ָ�����ָ����һ���ַ�

    return scanUnsignedInteger(str);
}

//�ú�������ɨ���ַ�����0~9����λ
bool scanUnsignedInteger(const char** str)
{
    //����beforeָ��ָ��ɨ��ʱһ��ʼ���ַ�
    const char* before = *str;

    while (**str != '\0' && **str >= '0' && **str <= '9')
    {
        ++(*str);
    }

    //��ָ���ַ�����ָ������ˣ���ô�ַ�����ȷʵ����0~9���ַ���
    //���Լ�������������ж�
    return *str > before;
}
#endif


//������21����������˳��ʹ����λ��ż��ǰ��
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

    //***ע***
    //����д����
    //cin.get()��ȡ�����ַ�������
    //������֮������ڷָ�Ŀո�Ҳ��Ϊ������
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

    //����1��2��3��4��5
    while (p1 < p2)
    {
        //��p1ָ���������
        if (pData[p1] & 0x01)
            ++p1;
        else if (!(pData[p1] & 0x01) && pData[p2] & 0x01)//һż��һ��
        {
            Swap(&pData[p1], &pData[p2]);
            ++p1, --p2;
        }
        else//һż��һż
            --p2;

        //һ�棬һ��
        //���ϵ����һ

        //һ�棬һż
        //���ϵ����һ
    }
}

void Swap(int* a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}
#endif

//������
#if 0
void Reorder(int* pData, int length)
{
	if (pData == nullptr || length == 0)
		return;

	int* pBegin = pData;
	int* pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		// ����ƶ�pBegin��ֱ����ָ��ż��
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)
			pBegin++;

		// ��ǰ�ƶ�pEnd��ֱ����ָ������
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

//***ע***
//����һ�������н�����ú�����ְ����з��롣
//������ߴ���������ԣ����ڹ��ܵ���չ
void Reorder(int* pData, int length, bool (*pfun)(int n))
{
    if (pData == nullptr || length == 0)
        return;

    int* pBegin = pData;
    int* pEnd = pData + length - 1;

    while (pBegin < pEnd)
    {
        // ����ƶ�pBegin��ֱ����ָ��ż��
        while (pBegin < pEnd && (*pfun)(*pBegin))
            pBegin++;

        // ��ǰ�ƶ�pEnd��ֱ����ָ������
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


//***ע***
//��ߴ����³���Ե���Ч;���ǽ��з����Ա��
//�����Ա����һ�ֱ��ϰ�ߣ���ָԤ����ʲô�ط����ܻ�������⣬
//��Ϊ��Щ���ܳ��ֵ������ƶ�����ʽ��


//������22�������е�����k���ڵ�
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

//һ�����뵽���Ǳ����������Σ�һ�α����õ������ܽڵ���n
//һ�α����õ���ͷ��ʼ�ĵ�n-k+1���ڵ�(�൱���ǵ�����k���ڵ�)

//�뵽ÿ�α���ʱǰ��һ���ڵ㶼��ָ��ȥָ��
//������Ҳ����ǰ��Ҫ����һ�����ڴ�ռ�ȥ��ָ���

//�ܲ���������ָ��ȥ�������£�
//��Ϊ��������Ҫ����������һ���ڵ��
//�����һ���ڵ������Ϊ��ʼ�����Ľڵ㣬�Ǿ���ָ��1ȥָ��
//��ָ��2ʼ�ս���ָ��1���k-1���ڵ�ľ���(ע��������ڴ���ڴ�ռ䲻����������)

//�൱������ָ���γ�һ�ι̶����������    (��ȡ��)
//ָ��1��ͷ��㿪ʼ�ߣ���k-1���ڵ�ľ����ָ��2��ʼ��ָ��1һ����
//ֱ��ָ��1����β�ڵ㣬��ָ��2ָ��Ľ�����Ҫ��ĵ�����k���ڵ�
ListNode* FindNode(ListNode** pListHead, int k)
{
    if (pListHead == nullptr || k <= 0||*pListHead==nullptr)
        throw new exception("Invaild data !");

    ListNode* p1 = *pListHead;
    ListNode* p2 = *pListHead;

    //p1����k-1���ڵ�
    for (int i = 1; i < k; ++i)  //***ע***
    {                                      //�з������޷�����������������ʱ����ʽת�����޷�������
        p1 = p1->m_pNext;   //���Ҳ�ǽ��ͳ��޷�������

        if(p1==nullptr)
            throw new exception("Invaild data !");//ע������³����
    }

    while (p1->m_pNext != nullptr)
    {
        p2 = p2->m_pNext;
        p1 = p1->m_pNext;
    }

    return p2;
}
#endif


//��������м�ڵ�
//�ⷨ��
//��������ָ�룬һ��ָ��һ����һ������һ��ָ��һ����������
//���ߵÿ��ָ���ߵ������ĩβʱ���ߵ�����ָ��������������м䡣


//������23�������л�����ڽڵ�
//***ע***
//��Ҫ��������
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

//���ҵ����е�����һ���ڵ�
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

//�ҵ����е�����һ���ڵ�󣬵ó����нڵ����Ŀ
//�����ҵ�������ڽڵ�
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* meetingNode = MeetingNode(pHead);

    if (meetingNode == nullptr)
        return nullptr;

    int cnt = 1;
    ListNode* tmp = meetingNode->m_pNext;

    //��������нڵ�ĸ���
    while (tmp != meetingNode)
    {
        ++cnt;
        tmp = tmp->m_pNext;
    }

    //***ע***
    //���ҵ�������ڽڵ�
    //������
    //��������ָ�룬һ��ָ�����ƶ����нڵ����Ŀ���ڵ㣬
    //Ȼ����һ��ָ����ͬ��һ��ָ��һ���ƶ�
    //����������Ľڵ���ǻ�����ڽڵ�

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


//������24����ת����
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
//***ע***
//˼��
//�����нڵ� i ->  j -> k
//���������  i <- j <- k
//���ڲ����ڵ� i �� j ʱ��Ҫ����ʱָ��ȥ����ԭ��jָ�����һ���ڵ�k�ĵ�ַ
ListNode* ReverseList(ListNode* pHead)
{
    if (pHead == nullptr)
        return nullptr;

    ListNode* i = pHead;
    ListNode* j = i->m_pNext;

    //�����������1���ڵ�
    if (j == nullptr)
        return pHead;
        
    ListNode* tmp = j->m_pNext;
    //�����������2���ڵ�
    if (tmp == nullptr)
    {
        j->m_pNext = i;
        i->m_pNext = nullptr;

        return j;
    }

    //����������3�������ϸ��ڵ�
    //�����
    //i <- j <- k -> L
    //i <- j <- k <- L

    ListNode* tmp1;

    while (tmp != nullptr)
    {
        //��ָ��û��ʱ��ָ�����һ���ڵ�洢��λ��
        tmp1=tmp->m_pNext;
        //Ȼ���ٸı�ָ��
        tmp->m_pNext = j;

        j->m_pNext = i;

        if (i == pHead)
        {
            i->m_pNext = nullptr;
            i = j;//  i ǰ��
        }
        else
            i = j;

        j = tmp;//  j ǰ��

        tmp = tmp1;//tmpǰ��
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

        //����������ĩβ�Ľڵ�
        if (pNext == nullptr)
            pReversedHead = pNode;

        //ָ��ָ��ı�
        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }

}
#endif
#endif


//������֮������ж����
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

    //***ע****
    //����д����
    if (i == j)
    {

    }

    //����ԭ��
    //�����������ܶ�����������Ϊ������ȣ�
    //���������Ϊ����ԭ�򣬿��ܻ�����������ֲ����
    //���磺
    // a = 1.1     b = 1.1
    //���������ʵ�ʶ����Ʊ�ʾ�Ŀ�����1.09999999��1.1000000001


    //��ȷ����1��
    if(abs(i - j) < 0.000001)

    //��ȷ����2����Ϊ������
    //����ǰ�ֽ��������ֽ�������
    //������ʱ�Ž������С

    return 0;
}
#endif


//������25���ϲ��������������
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

//�ⷨһ��
//�ϲ�ʱ��������һ������Ϊ���������кϲ�
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
            //������������
            //������һΪ 1 2 5 7
            //   �����Ϊ 3 4 6 8
            while (pNode1->m_pNext!=nullptr&&pNode1->m_pNext-> m_nValue <= pNode2->m_nValue)
            {
                pNode1 = pNode1->m_pNext;
            }

            //����ͷ������ĸ������ͷ���
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
            //������������
            //������һΪ 3 4 6 8
            //   �����Ϊ 1 2 5 7
            while (pNode2->m_pNext!=nullptr&&pNode2->m_pNext->m_nValue <= pNode1->m_nValue)
            {
                pNode2 = pNode2->m_pNext;
            }

            //����ͷ������ĸ������ͷ���
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

//�ⷨ����
//���õݹ飬��������һ���ϲ��������
//�ô���
//���Ա���ڵ�֮������������ϵĸ���ָ���������
//���ؿ�����������
//������һΪ 3 4 6 8
//   �����Ϊ 1 2 5 7
//�Ż���ʱ�临�Ӷ�
#if 1
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
    //***ע***
    //�������������Ȳ�һ�µ�����
    if (pHead1 == nullptr)
        return pHead2;

    if (pHead2 == nullptr)
        return pHead1;

    //����һ���ڵ㣬����pMergedHeadָ��ָ��
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


//������26�������ӽṹ
//˼·��
//��Ҫ��һ�������б���
//��Ҫ����A���ҵ�����B�ĸ��ڵ�ֵһ���Ľڵ�󣬼����ж����ߵ������ṹ�������Ƿ����
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
    //�õݹ�ķ�ʽȥ������
    bool res = false;

    if (pRoot1 != nullptr && pRoot2 != nullptr)
    {
        //***ע***
        //����д����
        //if(pRoot1->m_dbValue==pRoot2->m_dbValue)
        //����ԭ��
        //�������ʾС������������ֱ���õȺ�ȥ�ж�����С���Ƿ����

        //��ȷд����
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

//�ڸ��ڵ�ȷ��ֵ��ͬ��ǰ���£�����
//�ݹ��ж����������ṹ������Ԫ���Ƿ���ͬ
bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
    //��2�Ѿ���������
    if (pRoot2==nullptr)
        return true;

    //��1�Ѿ���������
    if (pRoot1 == nullptr)
        return false;

    //����д����
    //if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
    //    return true;
    //else
    //    return false;

    //��ȷд����
    if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
        return false;

    //ԭ����д�ɴ���д������ôֻҪ�������ڵ���ͬ����ֱ�ӷ���true��
    //�����ٽ��к������ж�

    bool flag = false;

    flag = DoesTree1HaveTree2(pRoot1->m_pLeft,pRoot2->m_pLeft);
    if(flag)
	flag = DoesTree1HaveTree2(pRoot1->m_pRight, pRoot1->m_pRight);

    return flag;
}
#endif


//������27���������ľ���
//�ѵ㣺
//���������ƺ�����ͨ������������нڵ��ֵ֮��Ľ�����
//˼·�����ˡ�
//ֵ�Ľ������Բ����õ�����ֵ�ķ�ʽ�������������ý������������ķ�ʽ
//ʵ��ֵ�Ľ���
//������ʽ������ǰ�����
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

    //��ɨ�赽Ҷ�ӽڵ㣬�������������ӽڵ㽻��
    if (rootNode->m_pLeft == nullptr && rootNode->m_pRight == nullptr)
        return;

    //������ǰ�ڵ��µ����ҽڵ�
    BinaryTreeNode* tmp = rootNode->m_pLeft;

    rootNode->m_pLeft = rootNode->m_pRight;
    rootNode->m_pRight = tmp;

    Mirror(rootNode->m_pLeft);
    Mirror(rootNode->m_pRight);
}
#endif

//��ѭ����ʵ��
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

            //��ɨ�赽Ҷ�ӽڵ㣬�������������ӽڵ㽻��
            if (tempNode->m_pLeft != nullptr || tempNode->m_pRight != nullptr)
            {
                //������ǰ�ڵ��µ����ҽڵ�
                BinaryTreeNode* tmp = tempNode->m_pLeft;

                tempNode->m_pLeft = tempNode->m_pRight;
                tempNode->m_pRight = tmp;
            }

            nodeStack.push(tempNode);

            tempNode = tempNode->m_pLeft;//��->��
        }
        else
        {
            //���Ѿ�ɨ�����ĳ�����������ӽڵ�Ľڵ㱣��󵯳�
            tempNode = nodeStack.top();
            nodeStack.pop();

            tempNode = tempNode->m_pRight;//��
        }
    }
}
#endif
#endif


//������28���ԳƵĶ�����
//�ԳƵ�ǰ���ǽṹ���ҶԳƺͽڵ��ֵ���ҶԳ�
//�ö������ľ������жϣ�ֻ���жϽṹ�ϵĶԳƣ���Ҫ�жϽڵ��ֵ�Ƿ�Գ�
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
//������
//ͨ���Ƚ϶������ĺ�nullptr�����ݵ�ǰ������ͺ�nullptr���ݵĶԳ�ǰ�����������
//���ж϶������Ƿ�Գ�
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

    //***ע***
    //����ǰ������Ǹ����ң����Գ�ǰ������Ǹ�����

    return isSymmetricCore(rootNode1->m_pLeft, rootNode2->m_pRight) &&
        isSymmetricCore(rootNode1->m_pRight,rootNode2->m_pLeft);
}
bool Equal(double a, double b)
{
    return abs(a - b) < 0.0000001;
}
#endif


//������29��˳ʱ���ӡ����
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

	//����ÿһȦ����ֹλ�õ�����ֵ����䣬����Ҫ�ҵ�
    //ÿһȦ��ֹ��ӡ�������������Ѷ�
    //������һ��ѭ���������޷���ɴ�ӡ�����
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

    //���������кŵı���start
    //����һ��
    //���к���Ϊ��ʼ��ӡ����ʼλ�ã����������Ϊ0���п�ʼ��ӡ��������Ϊ1���п�ʼ��ӡ
    //���ö���
    //����Ҫ��ӡ��ÿһȦ�����Ͻǵ�Ԫ�ص����궼��������ͬ��ֵ����(0��0)��(1��1)��
    //����startҲ����������Ϊ��ӡ��ʼ������
    //��������
    //��ӡ������������Ҫ�۲���ҹ��ɺ�ó�
    //����5*5��6*6�ľ�����˵����Ȼ���һȦ��ֻ��һ�����ֻ�����ĸ����֣�
    //�������һȦ���Ͻǵ��������ڵ�����һ������
    //row>start*2  &&  col>start*2
    //����startҲ����������Ϊ��ӡ����������

    int start = 0;

    while (row > start * 2 && col > start * 2)
    {
        PrintMatrixInCircle(matrix,row,col,start);

        ++start;
    }
}

//��Ȧ��ӡ
void PrintMatrixInCircle(int** matrix, int row, int col, int start)
{
    //��ӡ�Ϸ���
    for (int c = start; c < col - start; ++c)
    {
        cout << matrix[start][c] << ' ';
    }

    //��ӡ�Ҳ����
    for (int r = start+1; r < row - start; ++r)
    {
        cout << matrix[r][col-start-1] << ' ';
    }

    //��ӡ�·���
    for (int c = col-start-1-1; c >= start; --c)
    {
        cout << matrix[row-start-1][c] << ' ';
    }

    //��ӡ������
    for (int r = row - start - 1 - 1; r > start; --r)
    {
        cout << matrix[r][start] << ' ';
    }
}
#endif


//������30������min������ջ
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
    MyStack<T> m_data;//����ջ
    MyStack<T> m_min;//����ջ

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

//���԰�ÿ�ε���СԪ��(֮ǰ����СԪ�غ���ѹ��ջ��Ԫ�����ߵĽ�Сֵ)
//���������ŵ�����ջMyStack������
template<typename T>
bool StackWithMin<T>::push(const T& item)
{
    m_data.push(item);

    //***ע***
    //m_min�����޷�����m_top���˽�����ݳ�Ա,
    //��m_top����ΪprotectedҲ����
    //ԭ��
    // ˽�м̳����ṩ������ȷʵ�Ȱ����ࡣ
    // ���磬���������������Ա �����������ݳ�Ա��Ҳ�����ǳ�Ա��������
    // �������ĳ�Ա�����������ǿ��õģ����ڼ̳в�νṹ���ǲ����õġ�
    // ���ʹ����Ͻ����������������һ�����У�����߽����������࣬
    // ����λ�ڼ̳в�νṹ֮�⣬��˲��ܷ��ʱ�����Ա����
    // ͨ���̳еõ��Ľ��������࣬������ܹ����ʱ�����Ա��
    // ����ֻ����size()����
    if ( m_min.size() == 0 || m_data.top() < m_min.top())
    {
        m_min.push(item);
    }
    else
        m_min.push(m_min.top());

    //***ע***
    //����ջÿ��ѹ��Ķ���ջ��Ԫ�غ͵�ǰ��ѹ��Ԫ�صĽ�СԪ��

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
//������assert()�����н׶ζԶ��Խ��м�飬���Ϊ true��
//��ʾһ����Ϣ��������� abort()


//������31��ջ��ѹ�롢��������
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

//�Լ�д�Ľⷨ��
#if 0
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    if (pPush == nullptr || pPop == nullptr || nLength <= 0)
        return false;

    stack<int> stk;

    int i = 0;

    //����pPush����
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

//���ϵĽⷨ��
#if 1
bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    if (pPush == nullptr || pPop == nullptr || nLength <= 0)
        return false;

    stack<int>stk;

    //ֱ����ָ����Ϊ�ж�ѭ����ֹ������
    /*const int* pNextPush = pPush;
    const int* pNextPop = pPop;

    while (pNextPop - pPop < nLength)
    {

    }*/

    bool flag = false;

    int i = 0;

    //����
    //��������Ϊ�ж�ѭ����ֹ��������
    //��������pPop����
    for (int index = 0; index < nLength; ++index)
    {
        //������ջΪ�գ�����ջ��ջ��Ԫ�ز�����pPop[index]
        while (stk.empty() || stk.top() != pPop[index])
        {
            if (i == nLength)
                break;

            stk.push(pPush[i]);
            ++i;
        }

        //������ջ�Ѿ�װ����pPush���У��Ժ�pPop[index]�����
        if (stk.top() != pPop[index])
            break;

        //������ջ��ջ��Ԫ����pPop[index]���
        stk.pop();
    }

    if (stk.empty())
        flag = true;

    return flag;
}
#endif

#endif


//������32�����ϵ��´�ӡ������
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

//���Ͻⷨ��
void PrintFromToptoBottom(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    std::queue<BinaryTreeNode*> nodeQueue;
    BinaryTreeNode* tempNode = nullptr;

    nodeQueue.push(pTreeRoot);

    while (!nodeQueue.empty())
    {
        //����Ԫ��
        tempNode = nodeQueue.front();

        std::cout << tempNode->m_dbValue << " ";

        //�󵯳�
        nodeQueue.pop();

        if (tempNode->m_pLeft)
            nodeQueue.push(tempNode->m_pLeft);
        if (tempNode->m_pRight)
            nodeQueue.push(tempNode->m_pRight);
    }
}
#endif


//���д��ϵ��´�ӡ������
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

//��ΰ����ӡ��
//��������������x���洢ÿ��ȴ���ӡ�Ľڵ�����
//�ѵ㣺һ�����ĸ��ڵ㣬����ô�죿
//������xֵ��Ϊ0�󣬴�ӡ���з�

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
        //����Ԫ��
        tempNode = nodeQueue.front();
        //�󵯳�
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


//֮���δ�ӡ������
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

    //��¼���
    int odd_even = 1;

    //��¼ĳ��Ӧ�ô�ӡ�Ľڵ�����
    int num_of_this_level = 0;

    //��¼ĳ�㻹�ж��ٽڵ�����û�б���ӡ
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

        //����㣺
        //��������ֵΪ3�Ľڵ�ʱ��Ҫ�����ѹ��ڵ㣬����ͻ���ɶ����и��ڵ��ֵ
        //Ϊ5  6  4

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

//�Լ��Ľⷨ��
//�ڲ��ı�������ӽڵ��ٱ������ӽڵ��˳���£�
//����һ������ջ������Ԫ��˳��
#if 0
void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;

    queue<BinaryTreeNode*> nodeQueue;
    stack<BinaryTreeNode*> nodeStack;
    stack<BinaryTreeNode*> aux_Stack;

    //��¼���
    int odd_even = 1;

    //��¼ĳ��Ӧ�ô�ӡ�Ľڵ�����
    int num_of_this_level = 0;

    //��¼ĳ�㻹�ж��ٽڵ�����û�б���ӡ
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

            //***ע***
            //����ջ�����ߵ�Ԫ��˳��
            //��ӡ�Դ�ӡ����nodeStack�е�Ԫ��
            aux_Stack.push(nodeStack.top());

            nodeStack.pop();
        }

        cout << p_tmpNode->m_dbValue << " ";

        cnt--;

        //���ݲ�ŵ���ż��������ͬ�Ĳ���
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
            if (!cnt)//�����Ϊż�����Ҹò�ڵ㶼����ӡ���ˣ��ǾͿ��������ѹ��ڵ��ֵ��
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

//�ⷨ����
//�ı����˳�򣬵�����������ʱ��ѹ��ջ��˳��Ϊ�ȱ������ӽڵ��ٱ������ӽڵ�
//������ż����ʱ��ѹ��ջ��˳��Ϊ�ȱ������ӽڵ��ٱ������ӽڵ�
//���Ҳ��ö��У������ܹ�ʹ������ջ
#if 0
void Print_in_zigzag_pattern(BinaryTreeNode* pTreeRoot)
{
    if (!pTreeRoot)
        return;
    
    stack<BinaryTreeNode*> nodeStack[2];

    //��ʾ��ǰ��ʹ�õ�ջ
    int current = 0;
    //next��������ָ����ʹ���ĸ�ջ����Ԫ��
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

        //��������num_of_this_level������cnt���������û��з�

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


//������33�������������ĺ����������
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

//��������������Ԫ�����еĹ淶Ϊ
//ĳ���ڵ�������������нڵ��ֵ����С�������������нڵ��ֵ�����

//�������ĺ���������ص��ǣ�
//���е����һ��Ԫ�ؾ��Ǹ��ڵ��ֵ�����г�ĩβ��ֵ��������ֵ��С�ڸ��ڵ��ֵ
//��Ϊ���ڵ������������֮����Ϊ������
//�����������У��Դ��ڴ˹���

//�Լ��Ľⷨ��
#if 0
bool VerifySquenceOfBST(int* sequence, int length)
{
    if (sequence==nullptr||length<=0)
        return false;

    //���������洢��ǰ���ĸ��ڵ��ֵ
    int root = sequence[length-1];

    //ȷ���������������е����ݳ���
    int i;
    for (i = 0; ; ++i)
    {
        if (sequence[i] >= root)//***ע***   �˴�Ҫд�ɴ��ڵ��ڣ�����������ѭ��
            break;
    }

    int j = i;
    for (   ; j<length-1 ; ++j)
    {
        if (sequence[j] < root)
            return false;
    }

    bool flag = true;
    //��ĳ�ڵ����������
    if(i>=1&&sequence[i]!=root)
		flag = VerifySquenceOfBST(sequence, i);

    //��ĳ�ڵ����������
    if (flag&&j != i)
        flag = VerifySquenceOfBST(sequence+i,   j-i);

    return flag;
}
#endif

//�ⷨ����
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


//������34���������к�Ϊĳһֵ��·��
//˼·��
//����ǰ������ķ�ʽ���ʵ�ĳһ�ڵ�ʱ�����ǰѸýڵ���ӵ�·���ϣ�
//���ۼӸýڵ��ֵ������ýڵ�ΪҶ�ڵ㣬����·���нڵ�ֵ�ĺ͸պõ��������������
//��ǰ·������Ҫ�����ǰ�����ӡ�����������ǰ�ڵ㲻��Ҷ�ڵ㣬��
//�������������ӽڵ㡣��ǰ�ڵ���ʽ����󣬵ݹ麯�����Զ��ص����ĸ�
//�ڵ㡣��ˣ������ں����˳�֮ǰҪ��·����ɾ����ǰ�ڵ㲢��ȥ��ǰ��
//���ֵ����ȷ�����ظ��ڵ�ʱ·���պ��ǴӸ��ڵ㵽���ڵ㡣���ǲ��ѿ�
//������·�������ݽṹʵ������һ��ջ����Ϊ·��Ҫ��ݹ����״̬һ
//�£����ݹ���õı��ʾ���һ��ѹջ�ͳ�ջ�Ĺ��̡�
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

    //����ǰ�ܺ͵����������ܺͣ���pRootָ��������Ҷ�ӽ��
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

    vec.pop_back();//��vector������ʵ��ջ
}
#endif


//���η������ֽ��ø�������򵥻�
//������35����������ĸ���
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

//��һ��
//����ԭ�ڵ���µĿ����Ľڵ���һһ��Ӧ��ϵ�����Կ����ù�ϣ���ڱ���
//ԭ�ڵ��ͬʱ�����������ϣ�����ԭ�ڵ���´����Ľڵ�
#if 0
ComplexListNode* Clone(ComplexListNode* pHead)
{
    ComplexListNode* cur = pHead;

    //������ϣ��
    unordered_map<ComplexListNode*, ComplexListNode*> hash;

    //����ԭ�ڵ�Ϳ����Ľ��
    //(ԭ�ڵ�������Ϊ��)
    while (cur)
    {
        ComplexListNode* tmp=new ComplexListNode;
        tmp->m_nValue = cur->m_nValue;

        hash.insert(make_pair(cur,tmp));//make_pair()���غ���ָ��ֵ�� std::pair ����

        cur = cur->m_pNext;
    }

    cur = pHead;
    //�޸Ŀ����Ľڵ��ָ���Աָ����ڴ�ռ�
    while (cur)
    {
        //***ע***
        //�����������ʾ��(������������)�����ʴ洢��ֵ
        //���ʿ����Ľڵ��m_pNextָ��
        //(�����Ľڵ��m_pNextָ��ԭ�������ԭ����ı������Ľڵ����һ���ڵ�ĵ�ַ)
        //m_pNext�濽������һ���ڵ�ĵ�ַ
        hash[cur]->m_pNext = hash[cur->m_pNext];

        //ͬ���޸ı������ڵ��m_pSiblingָ��ָ����ڴ�ռ�
        hash[cur]->m_pSibling = hash[cur->m_pSibling];

        cur = cur->m_pNext;
    }

    return (*(hash.begin())).first;

    //return hash[pHead];
}
#endif

//������
//��ʹ�ø����ռ�������ʵ��O(n)��ʱ�临�Ӷ�
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

//�������ĸ����ڵ�������г���
//覴ã�����ԭ�������
#if 0
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    /*
    cout << "����" << endl;
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
    cout << "����"<<endl;
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

//��һ���������Ϊ��������
#if 1
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    //pNode���ڱ���ԭ����
    ComplexListNode* pNode = pHead;
    //pClonedHeadָ���¡�����ͷ��
    ComplexListNode* pClonedHead = nullptr;
    //pClonedNode���ڱ�����¡����
    ComplexListNode* pClonedNode = nullptr;

    if (pNode != nullptr)
    {
        //��pClonedHead��pClonedNode��ָ��pNode����һ���ڵ㣬����¡����ĵ�һ���ڵ�
        // ����Ϊ��¡����ĵ�һ���ڵ���ԭ����ĵڶ����ڵ㣩
        pClonedHead = pClonedNode = pNode->m_pNext;
        //����pNode��m_pNextָ�룬����ָ����һ���ڵ㣨ԭ�����е����¸��ڵ㣩
        pNode->m_pNext = pClonedNode->m_pNext;
        //pNodeָ������ĵ�3���ڵ�
        pNode = pNode->m_pNext;
    }

    //                  pClonedHead
    //                  pClonedNode      pNode
    //       1                  1'                    2                     2'

    while (pNode != nullptr)
    {
        //��pClonedNode��m_pNextָ��ָ��pNode����һ���ڵ㣬
        //�Ӷ�����¡�������һ���ڵ����ӵ���һ������¡�ڵ㡣
        pClonedNode->m_pNext = pNode->m_pNext;

        //����pClonedNode��pNode��ʹ���Ƿֱ�ָ���¡�����ԭ�����е���һ���ڵ㡣
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


//������36��������������˫������
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

    //������������ת����˫������
    //��ô����ĳ���ڵ�����ӽڵ㽫λ�ڸýڵ�֮ǰ����
    //�ýڵ��ָ�����ӽڵ��ָ�����Ϊָ��˫������ǰһ���ڵ��ָ��
    //�ýڵ��ָ���ҽڵ��ָ��Ҳͬ����Ҫ����
     
    //���ڵ��Ҷ�ӽ�������ָ�롾���ܡ���Ҫ���⴦��

    BinaryTreeNode* List=Convert(pNodeA1);

    //***ע***
    //����д������䣬��Ϊ�������ṹ�����˫������ṹ��
    //����ֵΪ10�Ľڵ㿪ʼ���������ͷŽڵ㵽ֵΪ4�Ľڵ��
    //���ٴα�����ֵΪ6�Ľڵ㣬����ͼ���ж����ͷ��ڴ�ռ䣬��ᵼ�´���
    //DestroyTree(pNodeA1);

    return 0;
}

BinaryTreeNode* Convert(BinaryTreeNode* pNode)
{
    if (!pNode)
        throw new exception("Error!");

    BinaryTreeNode* pLastNodeInList = nullptr;
    ConvertNode(pNode,&pLastNodeInList);

    //����pHeadNodeInListָ��ָ��������׸��ڵ�
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

    //�Եݹ�ķ�ʽ�����������
    if (cur->m_pLeft != nullptr)
        ConvertNode(cur->m_pLeft,pLastNodeInList);

    //***�ѵ�***
    //��������������е���Ԫ��ʱ��Ӧ�����δ���

    //˫��������׽ڵ��ָ��ǰһ���ڵ��ָ�븳Ϊnullptr
    //���׽ڵ��ָ��ǰһ���ڵ��ָ�븳Ϊǰһ���ڵ�ĵ�ַ
    //����������з��ദ������һ�����Ϳ������
    cur->m_pLeft = *pLastNodeInList;

    //��pLastNodeInListָ����׽ڵ㣬�����øýڵ��ָ���һ���ڵ��ָ��
    //ָ��ǰcurָ���λ��
    if (*pLastNodeInList != nullptr)
        (*pLastNodeInList)->m_pRight = cur;

    //*pLastNodeInListǰ��һ���ڵ�ľ���
    *pLastNodeInList = cur;

    //С�᣺
    //curָ�봦��ָ��Ľڵ��ָ��ǰһ���ڵ��ָ��
    //*pLastNodeInListָ�봦��ָ��Ľڵ��ָ���һ���ڵ��ָ��
    //����ָ��һǰһ��������ƶ�

    if (cur->m_pRight != nullptr)
        ConvertNode(cur->m_pRight,pLastNodeInList);
}
#endif


//������37�����л�������
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

//***ע***
//istream���ostream��ĸ��ƹ��캯����������Ϊprotected��
//�����ⲿ�޷�������Щ������ֻ��д�����õ���ʽ��
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

//���ļ��������н��ַ������ȡ
bool ReadStream(std::istream& stream, int* number)
{
	if (stream.eof())
		return false;

    char buffer[32] = {'\0'};

    //����ch�������ݴ��ַ�
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
        //����Ԫ��
        tempNode = nodeQueue.front();
        //�󵯳�
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


//������38���ַ���������
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

//pStrʼ��ָ���ַ�������Ԫ��
//pBeginָ�����ڿ������е��ַ����еĵ�ǰλ�õ�ָ��
//pBeginָ���Ԫ�ز��ϵ�����ָ���Ԫ�صĺ����ÿһ��Ԫ�ؽ��н���
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

            //***ע1***
            //���ַ���������ԭʼλ�ã���ȷ��ѭ������һ�ε���ʹ��ԭʼ�ַ���
            tmp = *pCh;
            *pCh = *pBegin;
            *pBegin = tmp;
        }
    }
}
//�����ע1        ��           ���ע1�������������        
//abc                                         abc                                    abcd
//acb                                         acb                                    abdc
//cab                                         bac                                    acbd
//cba                                         bca                                    acdb
//abc                                         cba                                    adcb
//acb                                         cab                                    adbc
#endif


//�ַ������������
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

//����n���ַ��ĳ���Ϊm(1��m��n)����ϵ�ʱ�����ǰ���n���ַ��ֳ������֣�
//��һ���ַ�������������ַ���
//�������������һ���ַ�������һ����ʣ����ַ���ѡȡm - 1���ַ���
//�������ﲻ������һ���ַ�������һ����ʣ���n - 1���ַ���ѡȡm���ַ���

//���԰���n���ַ���ɳ���Ϊm����ϵ�����ֽ�����������⣬
//�ֱ���n - 1���ַ��г���Ϊm-1����ϣ��Լ�
// ��n-1���ַ��г���Ϊm����ϡ������������ⶼ�����õݹ�ķ�ʽ�����
void Combination(char* string)
{
    assert(string != NULL);

    vector<char> result;

    int m, length = strlen(string);

    //�󳤶�Ϊlength���ַ��ĳ���Ϊi�����
    for (m = 1; m <= length; ++m)
        Combination(string, m, result);
}

void Combination(char* string, int number, vector<char>& result)
{
    assert(string != NULL);

    if (number == 0)
    {
        static int num = 1;
        printf("��%d�����\t", num++);

        vector<char>::iterator iter = result.begin();
        for (; iter != result.end(); ++iter)
            printf("%c", *iter);
        printf("\n");

        return;
    }

    if (*string == '\0')
        return;

    result.push_back(*string);

    //���������һ���ַ�������һ����ʣ����ַ�����ѡȡnumber-1���ַ�
    Combination(string + 1, number - 1, result);  

    result.pop_back();  //��ȥ��һ���ַ�

    //�����������һ���ַ�������һ����ʣ����ַ�����ѡȡnumber���ַ�  
    Combination(string + 1, number, result); 
}
#endif


//�˻ʺ�����
#if 0
#include <iostream>
#include<cmath>
using namespace std;

//c[x]=y����ʾ�ʺ���ڵ�x�У���y��
//����8x8��nΪ8
//����cnt��¼���ϵ��������
int c[20], n = 8, cnt = 0;

void search(int r);
void print(void);

int main()
{
    //�ӵ�1�п�ʼ����ģ��
    search(0);
    cout << cnt << endl;
    return 0;
}

//���ݷ�����
//�ݹ����search()
void search(int r) 
{
    //���Ѿ�ģ�⵽��9��(r��������1)
    if (r == n) 
    {
        print();
        ++cnt;
        return;
    }

    for (int i = 0; i < n; ++i) 
    {
        //��r+1�е�i+1�з��ûʺ�
        c[r] = i;

        int ok = 1;

        //��r+1��֮ǰ���н��б���
        for (int row = 0; row < r; ++row)
        {
            //������ͬ�����߻�Ϊ�Խ���
            if (c[r] == c[row] || abs(r - row) == abs(c[r] - c[row]))
            {
                //���зŵĲ��ԣ�Ҫ���·�
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


//������39�������г��ִ�������һ�������
#if 0
#include <iostream>
//#include <vector>
#include <unordered_map>
using namespace std;

//�Լ��Ľⷨ���ù�ϣ��
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
        //��ϣ��Ĳ�ѯʱ����O(1)
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

//�ⷨ��������Partition()��ʱ�临�Ӷ�ΪO(n)���㷨
#if 0
int RandomInRange(int a, int b)
{
    srand((unsigned int)time(0));
    // ���� [0, max]
    //int x = rand() % (max + 1);

    // ���� [1, max]
    //int x = 1 + rand() % (max);

    // ���� [min, max] ��Χ�������
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

//***begin��end��ָ��������ֵ***
int Partition(int data[], int length, int begin, int end)
{
    if (data == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //����һ����ָ����Χ�ڵ������
    int index = RandomInRange(begin, end);
    //���������Ϊ����ֵ��Ӧ������������ĩβ�����ֽ���
    //��ô����ĩβ�����־����������ֵ��Ӧ������
    Swap(&data[index], &data[end]);

    //��������small�洢����ֵ�����ʼֵ��beginС1���磺beginΪ0����smallΪ-1
    int small = begin - 1;

    //����ֵ��ͷ��ʼ��������
    for (index = begin; index < end; ++index)
    {
        //����ǰ����ֵָ������ֱ��������ֵָ�������С
        if (data[index] <= data[end])//ע����С�ڵ���
        {
            //����small��ֵ
            ++small;

            //��small��Ϊ��ǰ������ֵ
            if (small != index)
                Swap(&data[index], &data[small]);//����Ԫ�أ�Ŀ����
            //������ֵsmall����ֵ��С�ڸ�����ֵ����Ӧ��ֵ
        }
    }
    //��small������1
    ++small;
    //���������ֵָ��������ƶ���smallָ���λ����
    Swap(&data[small], &data[end]);

    //������������λ��
    return small;
}

int MoreThanHalfNum(int* number, int length)
{
    if (number == nullptr || length <= 0)
        return 0;

    //�洢����õ��������λ����Ӧ���ڵ�����ֵ
    int middle = length / 2;

    int start = 0;
    int end = length - 1;

    int index = Partition(number,length,start,end);

    //�����᲻Ϊmiddle
    while (index != middle)
    {
        //***ע***��������Ѷȣ�
        //����ǰѡ��� pivot����ŦԪ�أ�λ����λ����������middle�����Ҳ�
        //��ʾ���������벿���д�����λ��Ԫ�صĺ�ѡ��
        //��Ϊ�����������У���λ��Ԫ�ؽ�λ���������벿�֣�����С�� middle ��λ�ã�
        //������Ҫ����벿�ּ���������
        
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

//�ⷨ�������������ص㣬�ҵ�������ֵĹ���
//������������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬
//Ҳ����˵�����ֵĴ����������������ֳ��ִ����ĺͻ�Ҫ��
//���Ǳ�������һ�����ֵ�ʱ��
//�����һ�����ֺ�����֮ǰ�����������ͬ���������1�������һ������
//������֮ǰ��������ֲ�ͬ���������1���������Ϊ�㣬��ô������Ҫ��
//����һ�����֣����Ѵ�����Ϊ1����������Ҫ�ҵ����ֳ��ֵĴ�����������
//�����ֳ��ֵĴ���֮�ͻ�Ҫ�࣬��ôҪ�ҵ����ֿ϶������һ�ΰѴ�����
//Ϊ1ʱ��Ӧ�����֡�
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


//������40����С��k����
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

//�ⷨһ��ʹ��Partition����
int Partition(int* number, int length, int begin, int end)
{
    if (number == nullptr || length <= 0 || begin < 0 || end >= length)
    {
        //throw new exception("Invaild Parameters");
    }

    //1.ȡһ�����������ֵ
    srand(time(0));
    int rd_index = begin + rand()%(end - begin + 1);

    //2.���������ֵ��Ӧ��ֵ�Ƶ�����ĩβ����Ϊ�Ƚϱ��
    Swap(&number[rd_index], &number[end]);

    //3.��������small������ֵ
    int small = begin - 1;

    //4.��������
    //***ע***�ӵ�һ��Ԫ�ر����������ڶ���Ԫ��
    for (int index = begin; index < end; ++index)
    {
        if (number[index] <= number[end])
        {
            ++small;

            Swap(&number[index],&number[small]);
        }
    }

    //5.��Ŧֵ�ټ�1
    ++small;

    //6.ԭ�����������ֵ��Ӧ������  �ص�  ������Ŧֵ�����λ��
    Swap(&number[small],&number[end]);

    //������ȷ��������������ֵ����ŦֵС�ĸ���λ�õ�ֵ������Ŧֵ��Ӧ��ֵҪС������ڣ�
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
            //***��д�������***
            start = index + 1;

            index=Partition(number,length,start,end);
        }
        else
        {
            //***��д�������***
            end = index - 1;

            index = Partition(number, length, start, end);
        }
    }

    for (int i = 0; i <= index; ++i)
        cout << number[i] << " ";
}

//�ⷨ����ά��һ����������������Ҫ����O(1)ʱ���ڲ��ҵ������е����ֵ��
//����ҪO(logk)ʱ�����ɾ���Ͳ��������
//����һ����СΪk�������������洢��С��k�����֣�������ÿ��
//�������n�������ж���һ������������������е���������k����
//��ֱ�Ӱ���ζ����������������֮�У��������������k�������ˣ�
//Ҳ����������������ʱ���ǲ����ٲ����µ����ֶ�ֻ���滻���е����֡�
// �ҳ������е�k�����е����ֵ��Ȼ������δ���������������ֵ���б�
//�ϡ�����������ֵ�ȵ�ǰ���е����ֵС������������滻��ǰ���е�
//���ֵ������������ֵ�ȵ�ǰ���е����ֵ��Ҫ����ô�������������
//��С��k������֮һ���������ǿ����������������
//�˷����������ڴ���������

//�û��ں������multisetʵ��
#if 1
void GetLeastNumbers(const vector<int>& data, int k)
{
    if (data.empty() || k <= 0)
        return;

    //***ע***
    //set������Ԫ��Ĭ�ϴ�С�����ţ��ָ�Ϊ�ɴ�С���
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

        //д��1��
		//intSet.erase(--(intSet.rbegin().base()));
        //д��2��
		intSet.erase(next(intSet.rbegin()).base());
	}
}
//***ע***
//begin()��cbegin()������
//begin ������ iterator �� const_iterator ������ȡ���ڵ������Ķ���� const �޶���
//cbegin ������������ const_iterator

//�����erase()������ʹ�÷����������ɾ��Ԫ�أ�
//intSet.erase(intSet.rbegin());   //����
//���������
//��ҪӦ��ƫ����base()  ����  next()
#endif

//�û��ڶ���ѵ����ȶ���ʵ��
#if 0
void GetLeastNumbers(const vector<int>& data, int k)
{
    if (data.empty() || k <= 0)
        return;

    //***ע***
    //priority_queue������Ԫ��Ĭ�ϴӴ�С���

    //***�����Ǹ�Ϊ��С������***
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


//������41���������е���λ��
//������������Ͽ��������㷨
//���������������
//�����ö����������������Ż���AVL����������������������������ݶ����������У�
//����AVL��ʵ���ѣ����ǣ�
//����ܹ���֤����������ߵ����ݶ�С���ұߵ����ݣ���ô��ʹ��������
//�ڲ�������û������Ҳ���Ը���
//������������������ұ���С�������õ���λ����
//��ˣ�Ҫʵ��һ�����Ѻ���С��
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
    //����ǰ���Ѻ���С�ѵ�Ԫ�ظ���֮��Ϊż����ע��0Ҳ��ż������
    //�������ݲ��뵽��С��
    if (((max.size() + min.size()) & 0x1) == 0)
    {
        //�������ݱ������е�����ҪС
        if (max.size() > 0 && num < max[0])
        {
            //�����Ȱ�����µ����ݲ������ѣ����Ű����������������ó���
            //������С�ѡ����ڡ����ղ�����С�ѵ�������ԭ�������������֡�������
            //�ͱ�֤����С�����������ֶ����������е�����

            max.push_back(num);

            //������ [first, last) ��Χ�ڵĵ�����ָ�������н�����������
            //���γɰ� operator< ������¶ѡ� [first, last - 1) ��Χ�ڵĵ�����
            //����ָ��һ�����жѣ�Ҳ�� operator< ����
            //��ˣ� first != last ����Ϊ true������ *(last - 1) ��Ҫ��ӵ������룩�ѵ�Ԫ�ء�
            //���е��������������ô˺������бȽ�
            push_heap(max.begin(),max.end(),less<T>());

            num = max[0];

            //������λ�� first ��ֵ����λ�� last-1 ��ֵ�������ӷ�Χ [first, last-1) ��Ϊ�ѡ�
            //��ӵ�дӷ�Χ [first, last) ������Ķ��Ƴ��׸�Ԫ�ص�Ч����
            pop_heap(max.begin(),max.end(),less<T>());
            //�������е����ֵɾȥ
            max.pop_back();
        }

        min.push_back(num);
        push_heap(min.begin(),min.end(),greater<T>());
    }
    else//���򣬲��뵽����
    {
        //�������ݱ���С���е�����Ҫ��
        if (min.size() > 0 && num > min[0])
        {
            //�����Ȱ�����µ����ݲ�����С�ѣ����Ű���С������С�������ó���
            //�������ѡ��������ղ������ѵ�������ԭ��С������С�����֣�����
            //�ͱ�֤���������������ֶ�С����С���е�����

            min.push_back(num);

            push_heap(min.begin(), min.end(), greater<T>());

            num = min[0];

            //������λ�� first ��ֵ����λ�� last-1 ��ֵ�������ӷ�Χ [first, last-1) ��Ϊ�ѡ�
            //��ӵ�дӷ�Χ [first, last) ������Ķ��Ƴ��׸�Ԫ�ص�Ч����
            pop_heap(min.begin(), min.end(), greater<T>());
            //����С���е���Сֵɾȥ
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
        res = min[0];//��Ϊ���Ѻ���С��Ԫ���ܺ�Ϊż��ʱ�����������ݲ��뵽��С��
    else                  //����Ԫ������Ϊ����ʱ����λ������С�ѵ���Ԫ��
        res = (max[0] + min[0]) / 2;//***ע***double���͵Ļ���û������λ��������
                                                    //����/2����ͨ����
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


//������42�����������������
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

//�ѵ㣺��֪��Ӧ�ô�����ĵڼ���Ԫ�ؿ�ʼ��ȡ�����ĸ�Ԫ�ؾͽ���
//����������ʱֻ����ʱ�Ļ���sumֵ��С�����ø��������Ԫ�ؿ��ܻ���sum��һ�����
//�����ȡ�᣿Ҳ������˫ָ��˼����

//��̬�滮˼�룺
//״̬���̣�max( dp[ i ] ) = getMax(    max( dp[ i -1 ] ) + arr[ i ] ,    arr[ i ] )
//����ʽ�ӵ������ǣ����Ǵ�ͷ��ʼ�������飬����������Ԫ�� arr[i] ʱ��
//���������ĺͿ���Ϊ max(dp[i - 1]) + arr[i] ��Ҳ����Ϊ arr[i] ��
//���Ƚϼ��ɵó��ĸ�����ȡ���ֵ��ʱ�临�Ӷ�Ϊ n��

    int sum = pData[0];
    int Max = pData[0];

    for (int i = 1; i < length; ++i)
    {
        //***ע***
        //�������ʹsum���ݴ���õĺ͵�ͬʱȷ���˴�����ĵڼ���Ԫ�ؿ�ʼ���
        sum = max(sum+pData[i],pData[i]);

        Max = (sum >= Max) ? sum : Max;
    }
 
    return Max;
}
#endif


//������43��1~n������1���ֵĴ���
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

    //�Ƚ���������ת�����ַ��洢
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

    //�洢���λ������ֵ���������ֵķָ����
    //����nΪ21345��ô��Ӧ��Ϊ1~1345��1346~11345��11346~21345
    //***ע***
    //�ڶ����ֺ͵������֣�1�ļ�����������Ѷȣ�
    //�������У�����λ����1�Ĵ���Ӧ��Ϊ2*( C4 1 )*10^3=8000
    //��Ϊ������Կ���һ���������⣺
    //��λ�����г���1�����С�Ȼ������ظ������֣�����1101��
    //��Ӧ��ȥ��ֻ����1�Σ�����������������ǳ���1�Ĵ�����1101����3�Σ�
    //��������ǧ���١���λ����һ�������õġ���������ת��Ϊ����λ�ֱ���1ʱ��
    //����λ������У���һ�Ρ�

    int first = *strN - '0';

    int length = strlen(strN);

    if (length == 1 && first == 0)
        return 0;

    if (length == 1 && first > 0)
        return 1;

    // ����strN��"21345"
    // numFirstDigit������10000-19999�ĵ�һ��λ��1����Ŀ
    int numFirstDigit = 0;
    if (first > 1)
        numFirstDigit = PowerBase10(length - 1);
    else if (first == 1)
        numFirstDigit = atoi(strN + 1) + 1;

    // numOtherDigits��01346-21345���˵�һλ֮�����λ��1����Ŀ
    int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
    // numRecursive��1-1345��1����Ŀ
    int numRecursive = Numberof1Core(strN + 1);

    return numFirstDigit + numOtherDigits + numRecursive;
}
#endif


//������44������������ĳһλ������
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

    //��һ����
    //�ҵ���nλ����Ӧ���ڼ�λ��֮��
    //ͬʱ�ҵ��Ǹ�λ���������������µĶ���λ
    Data data = FindWeiShu(n);

    //�ڶ�����
    //����ĳ�������ֵ���ʼ����
    int begin;
    if (data.weishu == 1)
        begin = 0;
    else
        begin= pow(10, data.weishu - 1);

    //��������
    //ĳ�����µ����ֵĵ�x������
    int x_num = data.yvxia / data.weishu;
    //��x�����ֵĵڼ�λ
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

    //***ע***0~9��10������
	n -= weishu * (pow(10, right) - pow(10, left)+1);

    while (n>=0)
    {
        ++right, ++left,++weishu;

		//                  λ��*��λ�����м�������
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
    data.yvxia = abs(n);//��abs��Ϊ�˵�n����5ʱ��yvxia��Ա�õ���ֵΪ5������-5

    return data;
}
#endif


//������45���������ų���С����
//�ⷨ��
//Ҫȷ��һ�������ж�m��n�ĸ�Ӧ������ǰ�棬
//�����ǽ����Ƚ����������ֵ�ֵ�ĸ�����
//������
//��������m��n��ƴ�ӳ�����mn��nm�����mn<nm,
//��ô����Ӧ�ô�ӡ��mn, Ҳ����mӦ������n��ǰ�棬���Ƕ����ʱmС��n; 
//��֮�����nm < mn, �����Ƕ���nС��m; ���mn = nm, ��m����n
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

    //***ע***
    //Ϊ����������⣬��Ҫ��ÿ���������ַ�����ʽ��ʾ
    //����ָ���ַ������ָ��
    //����д����
    //char** strNumbers = new char[MaxLengthOfNum][length];
    //��ȷд����
    char** strNumbers = new char* [length];

    for (int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[MaxLengthOfNum];

        sprintf(strNumbers[i], "%d", numbers[i]);
    }

    //Ȼ��ʹ�ö��ַ������������Ը��ַ���������
    //***ע***
    //qsort()�������ܶ�strNumbers��ָ�����������������
    //�����Զ���ıȽϷ���������
    qsort(strNumbers,length,sizeof(char*),mycompare);

    char Print[MaxLengthOfNum];
    strncpy(Print,strNumbers[0],MaxLengthOfNum-1);
    Print[MaxLengthOfNum-1] = '\0';

    //***ע***
    //strncat������ src ��ָ����ַ���������� count ���ַ���
    //�� dest ��ָ��Ŀ���ֹ�ֽ��ַ�����ĩβ�����ҵ����ַ���ֹͣ
    //ʼ�պ���ֹ���ַ���ĩβ���ʺ�����д�������ֽ����� count+1 ����
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

    //***ע***
    //���������ͷŶ�̬������ڴ�
    //�ͷ��ַ�����
    for (int i = 0; i < length; ++i)
    {
        delete [] strNumbers[i];
    }

    //�ͷ��ַ�����ָ����ɵ�����
    delete[] strNumbers;
}

int mycompare(const void* a, const void* b)
{
    //***ע***
    //����д����
    //const char* arg1 = (const char*)a;
    //const char* arg2 = (const char*)b; 

    //***��ȷд��***
    //��⣺qsort()������ʵ����Ҫ����ָ������������Ԫ�ص�ָ��
    //�����е�Ԫ���Ѿ���ָ�룬���a��b����ָ���ָ��
    const char* arg1 = *(const char**)a;//��ǿ������ת��Ϊָ���ָ�룬������������Ϊ
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

    // return (arg1 > arg2) - (arg1 < arg2); // ���еļ�д
    // return arg1 - arg2; // ����ļ�д�������� INT_MIN ���ʧ�ܣ�
}
#endif


//������46�������ַ�����ַ���
//˼·��
//���ģ������жϰ�쳲��������У�������̨���⣩��
//�ѷ���1�����ֺͷ���2�����ֿ�����1�׺���2�ף�
//ֻ�е�����ƥ�� >= 10�� <= 25ʱ����2�ף�dp[n] = dp[n - 1] + dp[n - 2] 
//�������ֻ����1�ף������ǰһ�������ͬ��dp[n] = dp[n - 1]
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

    //***ע***
    //��to_string()�������ٽ�����ֵת��Ϊ�ַ��洢
    string str = to_string(num);
      
    int Length = str.size();
    
    //***
    unique_ptr<int[]> dp(new int[Length+1]);

    //��������12������������12��ƥ����ĸ�����dp[2]=dp[1]+dp[0]
    //����Ϊ����Ϊһλ��ʱdp[1]=1������Ƴ�dp[0]=1
    dp[0] = 1;
    dp[1] = 1;

    if (Length == 1)
        return 1;

    //dp������ֵ����ڼ������֣��ӵڶ������ֿ�ʼ������dp[2]��ʼ
    //��ôstrӦ��ȡ��1������2������
    for (int i = 2; i <= Length; ++i)
    {
        string tmp = str.substr(i-2,2);//***ע***i-2�൱���ǵ�i-1�����ֿ�ʼ�����ȡ��λ

        if (tmp.compare("10") >= 0 && tmp.compare("25") <= 0)
            dp[i] = dp[i - 1] + dp[i - 2];
        else
            dp[i] = dp[i-1];
    }

    return dp[Length];
}
#endif


//������47�����������ֵ
//����01�������⣬���ֲ���
//�����ö�̬�滮����
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
    //��Ϊ�Ǵ����Ͻǵ����½ǣ�����ֻ�������һ������£�
    // ���Կ��ԶԳ������Ͻǵ�Ԫ��֮���Ԫ��
    //���ж�̬�滮
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

//�ⷨ����ֻ��һά������Ϊ�����ռ䣨�ռ����Ż���
//�ڲݸ�ֽ��дд�������������
#if 0
int maxValue(vector<vector<int>>& grid) 
{
    int m = grid.size(), n = grid[0].size();

    vector<int> dp(n, 0);

    for (int i = 0; i < m; i++) 
    {
        //***ע***dp[0]����ǵ�grid[i][0]���ܻ�õ�����ֵ
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


//������48��������ظ��ַ������ַ���
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

    //����curLength�����浱ǰģ������µķ���Ҫ��ĳ���
    //����maxLength������������Ҫ��ĳ���
    int curLength = 0, maxLength=0;

    //�������飬��ÿ���ַ����ֵ�λ��
    unique_ptr<int[]>position(new int[26]);

    fill(position.get(), position.get() + 26, -1);

    for (int i = 0; i < str.length(); ++i)
    {
        //����PreIndex��ʾĳ����ĸ��һ�γ��ֵ�λ��
        //(��һ�γ���ʱ��PrevIndexֵΪ-1)
        int PrevIndex = position[str[i]-'a'];

        //��ĳ����ĸ�ǵ�һ�γ��ֻ���
        //��ĳ��ĸ��λ����ĳ��ĸ��һ�γ��ֵ�λ�õľ���
        // ���ڵ�ǰ��¼��������ظ��ַ����ַ����ĳ��ȡ�
        if (PrevIndex<0 || i - PrevIndex>curLength)
            ++curLength;
        else
        {
            //�洢һ�·�����������󳤶�
            if (curLength > maxLength)
                maxLength = curLength;

            //***ע***
            //��curLength��ֵ�ض�Ϊ������ͬ���ַ��ľ���֮��
            curLength = i - PrevIndex;
        }

        //ĳ�ַ���һ�γ��ֵ�λ���õ�ǰ���ֵ�λ�ô���
        position[str[i]-'a'] = i;
    }

	//�洢һ�·�����������󳤶�
    if (curLength > maxLength)
        maxLength = curLength;

    return maxLength;
}
#endif


//������49������
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
    //***����д��***
    //if (num % 2 != 0)
    //    return false;
    //if (num % 3 != 0)
    //    return false;
    //if (num % 5 != 0)
    //    return false;

    //����ֻ�ܱ�2��3��5����
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

    //***ע***
    //����ʹ��vector������ָ�����Զ������ڴ沢����Ǳ�ڵ��ڴ�й©
    vector<int> pUglyNumbers(WhichOne);

	pUglyNumbers[0] = 1;
	int nextUglyIndex = 1;

	//int* pMultiply2 = pUglyNumbers;
	//int* pMultiply3 = pUglyNumbers;
	//int* pMultiply5 = pUglyNumbers;

    //��������ָ�룬��Щָ������
    //ͨ�������ú󽫵�ǰ�����ֱ���� 2��3 �� 5 ��������һ����ѡ����
    vector<int> ::iterator pMultiply2;
    pMultiply2 = pUglyNumbers.begin();
    auto pMultiply3 = pUglyNumbers.begin();
    auto pMultiply5 = pUglyNumbers.begin();

	while (nextUglyIndex < WhichOne)
	{
		//int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
		//pUglyNumbers[nextUglyIndex] = min;

        //***�ѵ�***
        //���������Ϊ�˽���������С�����˳�����ɲ��洢
        //��Ҫ����������while�������
		int Min = min(min(*pMultiply2 * 2, *pMultiply3 * 3), *pMultiply5 * 5);

		pUglyNumbers[nextUglyIndex] = Min;

        //ͨ���� *pMultiply2 ��ָ���������2������Ƿ�С�ڵ���
        //��ǰ�����ɵĳ��������е����һ������
        //����ǣ���ʾ��ǰ *pMultiply2 ��ָ���������2�󲻴��ڵ�ǰ�����ɵ���������
        //�����Ҫ�� *pMultiply2 ָ������ƶ�һλ���Ա���һ�μ���
        
        //Ŀ����ȷ�����ɵĳ��������ǰ����������еġ�
        //ͨ�����ϵظ���������ָ�룬���Ա�֤����һ�������ǵ�ǰ������
        //���������е�ĳ��������2��3��5�õ�����Сֵ��
		while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
			++pMultiply2;
		while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
			++pMultiply3;
		while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
			++pMultiply5;

        //��ָ���ƶ���ָ����һ������Ӧ�����λ��
		++nextUglyIndex;
	}

	int ugly = pUglyNumbers[nextUglyIndex - 1];

	return ugly;
}
#endif


//������50����һ��ֻ����һ�ε��ַ�
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
        //ʱ�临�Ӷȣ�O(1)
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

//������ά��һ����������ļ��׹�ϣ��
#if 1
void AppearOnlyOnce(const string& str)
{
    if (str == "")
        return;

    //���㹻��������ASCII�ַ���Ӧ��ֵ
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


//�鲢����
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

//                                                      front ,end ��Ϊ����ֵ
void MergeSort(vector<int>& Array, int front, int end)
{
    //��ǰ���������������һ��Ԫ�أ��������Ѿ�����
    if (front >= end)
        return;

    int mid = front + (end - front) / 2;

    //MergeSort()�ݹ�ؽ����黮��Ϊ��С�������飬ֱ�����Ǳ�����
    MergeSort(Array, front, mid);
    MergeSort(Array, mid + 1, end);
    //Ȼ��ʹ�� Merge ���������Ǻϲ���һ��
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

    //�ںϲ�֮ǰ�� numeric_limits<int>::max() ���ӵ� Left �� Right �������ĩβ��
    //numeric_limits<int>::max() �������е����ֵ��
    //�ںϲ����������䵱��һ���������ʾ������Ľ�����
    //����ȷ���ںϲ������У���Ԫ�ؽ��бȽϺͺϲ�ʱ���㷨����Ҫ������Ƿ�
    //�ѵ����κ��������ĩβ�� max() �ڱ�ֵ�䵱�ϲ������е���Ȼֹͣ�㣬
    //��ֹ����Խ����󲢼򻯺ϲ��߼�
    LeftSubArray.insert(LeftSubArray.end(), numeric_limits<int>::max());
    RightSubArray.insert(RightSubArray.end(), numeric_limits<int>::max());

    //���������Ե�һ�β�ֵ���������Ϊ������ʵҲ���ǹ鲢�����һ����
    //��һ�β��֮����������о���[3 5 1]��[2 8 5]�ˣ�
    //���Ǵ��Ҫע�⣬�����ڶ����������н��й鲢ʱ������Ӧ��������ź����ˣ�
    //��Ϊ�ǵݹ��֣������һ�β�ֵ�ʱ�����ж��ǵ�����Ԫ�أ����Ե��鲢�����һ��ʱ��
    //Ҳ������ߵ�����Ӧ����[1 3 5]���ұߵ�����Ӧ����[2 5 8]
    // Pick min of LeftSubArray[idxLeft] and RightSubArray[idxRight], and put into Array[i]
    //ȡLeftSubArray[idxLeft]��RightSubArray[idxRight]�е�min������С�ߣ�����Array[i]��
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
        //***ע***
        //�ڱ�ֵ��2147483647�䵱�ϲ������е���Ȼֹͣ�㣬
        //��ֹvector������Խ����󲢼򻯺ϲ��߼�
    }

#endif

#if 1
    //��ʹ���ڱ�ֵ�ĺϲ�����
    int n1 = mid - front + 1;  //n1ֵΪǰ��ε�Ԫ�ظ���
    int n2 = end - mid;          //n2Ϊ���ε�Ԫ�ظ���

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

    // ��ʣ��Ԫ�ظ��ƻ�����
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


//������51�������е������
//��ĳ�������ó����ͺ����ÿ��������Ƚϣ�ʱ�临�Ӷ���O(n^2)
//˼·��
//��һ����������ָ��������飬ͳ�Ƴ��������ڲ�������������
//�ڶ�����ͳ����������������֮�����������������Ҫ��������
//������Ϊ���鲢����
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

    //����������ָ������copy���飬����������ı������ݣ�������
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

    //length�����õ������鳤�ȵ�һ��
    int length = (endindex - startindex) / 2;

    //������ָ�������������
    int left = InversePairsCore(copy,data,startindex,startindex+length);
    //�����������飬���е�  int end = ...  ʱ
    //����startIndexΪ0��endIndexΪ1��lengthΪ0
    //���Ѿ��ָ����˽�Ϊ����Ԫ�ص�������
    int right = InversePairsCore(copy,data,startindex+length+1,endindex);
    //�������������Ԫ��ʱ��ִ�������InversePairsCore()�󣬻������һ��if
    //�����е�return��Ȼ�����أ������InversePairsCore()������������
    //��������Ҳ��ָ�������������

    //����i��ʾ��ǰ��Ρ����һ��Ԫ�ص�����λ��
    int i = startindex + length;
    //����j��ʾ�����Ρ����һ��Ԫ�ص�����λ��
    int j = endindex;

    int indexCopy = endindex;

    int cnt = 0;

    while (i >= startindex && j >= startindex + length + 1)
    {
        //����һ���������е����ִ��ڵڶ����������е����֣���
        //�����������ԣ��������������ڵڶ�����������ʣ�����ֵĸ���
        if (data[i] > data[j])
        {
            cnt += j - startindex - length;

            //���ϴ�����ִӺ���ǰ���Ƶ���������
            copy[indexCopy] = data[i];

            --indexCopy, --i;
        }
        else
        {
            copy[indexCopy] = data[j];

            --indexCopy, --j;
        }
    }

    // ��ʣ��Ԫ�ظ��ƻ�����
    for (;i >= startindex; --i)
        copy[indexCopy--] = data[i];

    for (;j >= startindex+length+1; --j)
        copy[indexCopy--] = data[j];

     //���������������������ڲ�����������������������������֮�������������
    return cnt+left + right ;
}
#endif


//������52����������ĵ�һ�������ڵ�
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

// ��һ����������������м�
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

//��ͨ������
//��һ������˳�����ÿ���ڵ㣬ÿ������һ���ڵ㣬���ڵڶ���������˳�����ÿ���ڵ㡣
//����ڵڶ�����������һ���ڵ�͵�һ�������ϵĽڵ�һ����
//��˵����������������ڵ����غϡ�ʱ�临�Ӷ�O(mn)
//�Ż��ⷨ��
//�۲�ϲ���ͺϲ�ǰ���������״̬���õ�
//�ϲ���������������нڵ㶼���غϵģ���ôֻҪ����ĩβ��ʼ��
//��ǰ�Ƚϣ����һ����ͬ�Ľڵ���ǵ�һ�������ڵ�
//��δ�ĩβ��ʼ�Ƚϣ�
//�������ݽṹ����>ջ        ʱ�临�Ӷ�O(m+n)
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

//�ⷨ����
//�ٴι۲���������ĳһ�ڵ㼰��֮��ʼ�ϲ�������
//���˿��ԴӺ���ǰ�������ҵ����һ�������Ľڵ㣬������ѡ��
//�Դ�ǰ���������ڽϳ����������ȱ��������ڵ㣬Ȼ�������ڵ�һͬ������
//�ҵ���һ����ͬ�Ľڵ㣬�÷�������ջ�ķ���ʱ�临�Ӷ���ͬ
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


//������53�������������в������ֳ��ֵĴ���
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

//һ��Ľⷨ��ʱ�临�Ӷ�ΪO(n)
//�и���Ľⷨ�����á�����Ķ��ַ���ȷ����һ��k��λ�ú����һ��k��λ��
//������ʱ�临�Ӷȿ��Խ���O(logn)
int AppearTimes(int* data, int length, int k)
{
    if (data == nullptr || length <= 0)
        throw exception("Error input!\n");

    int First = GetFirstK(data, length, k, 0, length - 1);
    int Last = GetLastK(data, length, k, 0, length - 1);

    //***ע***
    //ע�����ġ������ԡ�
    //��Ҫ����������û��Ҫ���ҵ����ֵ����
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

    //***ע***
    //ʹ�ñ���Ķ��ַ���ȷ��k��һ�γ��ֵ�����ֵ
    
    //���м�����־�����Ҫ������ִ���������
    //����м����ֵ���k��?������Ҫ�ж����k�ǲ������һ��k, 
    //Ҳ�����м����ֵ���һ�������ǲ���Ҳ����k�������һ�����ֲ���k, 
    //���м����־������һ��k��������һ�����ǻ���Ҫ������ĺ�����ȥ���ҡ�
    if (middledata == k)
    {
        //�жϸ������ǲ��ǵ�һ�����֣��жϸ��м����ֵ�ǰһ�������ǲ��ǻ���k
        if (middleidx == 0 || data[middleidx - 1] != k)
            return middleidx;
        else
            endidx = middleidx - 1;
    }
    else if (middledata > k)
        endidx = middleidx - 1;
    else
        begidx = middleidx + 1;

    //�ݹ�Ѱ��
    return GetFirstK(data,length,k,begidx,endidx);

    //***ע***
    //������������return
}
int GetLastK(int*data, int length, int k, int begidx, int endidx)
{
    if (begidx > endidx)
        return -1;

    int middleidx = begidx+(endidx - begidx) / 2;
    int middledata = data[middleidx];

    //***ע***
    //ʹ�ñ���Ķ��ַ���ȷ��k���һ�γ��ֵ�����ֵ

    //���м�����־�����Ҫ������ִ���������
    if (middledata == k)
    {
        //�жϸ������ǲ������һ�����֣��жϸ��м����ֵĺ�һ�������ǲ��ǻ���k
        if (middleidx == endidx || data[middleidx + 1] != k)
            return middleidx;
        else
            begidx = middleidx + 1;
    }
    else if (middledata > k)
        endidx = middleidx - 1;
    else
        begidx = middleidx + 1;

    //�ݹ�Ѱ��
    return GetLastK(data, length, k, begidx, endidx);
}
#endif


//0~n-1��ȱʧ������
//һ������Ϊn-1�ĵ������������е��������ֶ���Ψһ�ģ�
//����ÿ�����ֶ��ڷ�Χ0��n - 1֮�ڣ�
//�ڷ�Χ0��n-1�ڵ�n������������ֻ��һ�����ֲ��ڸ������С�
// ���ͣ�
//���������ڷ�Χ0��n-1�ڵ�n�����֣�
//�����ڡ��ڷ�Χ0~n�ڵ�n�����֣������Եó�������ֻ��һ�����ֲ��ڸ������С�
//�൱��˵ÿ������ԭ��Ӧ����������ֵ��һһ��Ӧ��
//�����ö��ֲ��ҷ�����������ֵ����Ӧ������
#if 0
#include <iostream>

using namespace std;

int FindTheNumber(int* ,int length);

int main()
{
    //����Ϊn-1=12   n=13
    //ÿ��������0~12֮��
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
        else//data[mididx]==mididx �����
        {
            begidx = mididx + 1;
        }

        mididx = begidx + (endidx - begidx) / 2;
    }

    return -1;
}
#endif
//***ע***
//���ַ������ɵݹ����ѭ������ʾ


//��������ֵ���±���ȵ�Ԫ��
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
//***ע***
//�ܽ᣺���������򵥵��ݼ������飬�����ض����ݿ����ö��ַ��������ַ�����Сʱ�临�Ӷ�


//������54�������������ĵ�k��ڵ㣨***��Ŀ��˼��Ѱ�ҵ�kС�Ľڵ�***��
//˼·����������������������ң�
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

//***ע***   ʹ�õ���k�����ã�����˵��������ԭ����k
BinaryTreeNode* FindTheKLargestNodeCore(BinaryTreeNode* pBTNode, int& k)
{
    //�Լ���Ľⷨ��
    //��������������������������ָ����ڵ��ָ��͸ýڵ��ֵ����map����
    //�ٸ���Ҫ�󷵻ص�k��Ľڵ�

    //���Ͻⷨ��
    //Ѱ�ҵ�kС�Ľڵ㣬

    BinaryTreeNode* target = nullptr;

    if (pBTNode->m_pLeft != nullptr)
        target = FindTheKLargestNodeCore(pBTNode->m_pLeft,k);

    //����������������ߵĽڵ�ʱ
    if (target == nullptr)
    {
        if (k == 1)
            target = pBTNode;

        --k;
    }
    //***ע***
    //ͨ���ݼ�k��ֵ���õ���kС�Ľڵ��ָ��

    //����û�ҵ���������������
    if (target == nullptr && pBTNode->m_pRight != nullptr)
        target = FindTheKLargestNodeCore(pBTNode->m_pRight,k);

    return target;
}
//***ע***
//���㷨ֻ�ܵõ���kС�����ܸĽ��Եõ���k��Ľڵ�
#endif


//������55�������������
//deep = log2(num) + 1;//***ע***n���ڵ�����ȹ�ʽ 
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

//�ⷨһ��
//����ڵ�������ټ������
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
    //***ע***
    //Ҫ���䣺
    if (!pNode)
        return 0;
    return CalNodes(pNode->m_pLeft) + CalNodes(pNode->m_pRight) + 1;

    //���Զ���������13
}
#endif

//�ⷨ����
//������һ���Ƕ������������ȡ����һ����ֻ��һ���ڵ㣬��ô�������Ϊ1��
//������ڵ�ֻ����������û������������ô�������Ӧ����������������ȼ�1; 
//ͬ����������ڵ�ֻ����������û������������ô�������Ӧ����������������ȼ�1��
//���������������������������ô��������Ⱦ���������������ȵĽϴ�ֵ�ټ�1��
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


//�ж��Ƿ�Ϊƽ�������
//���ĳ������������ڵ���������������������1, ��ô������һ��ƽ���������
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
    //�Ѿ�������Ҷ�ӽ��
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
//���������������
//�ᵼ��һ���ڵ㱻������Σ�ʱ��Ч�ʲ���

//���õĽⷨ��
//ʹ�á����������
//�ڱ�����һ���ڵ�֮ǰ���Ǿ��Ѿ���������������������ֻҪ�ڱ���ÿ���ڵ��ʱ��
//��¼�������(ĳһ�ڵ����ȵ�������Ҷ�ڵ��·���ĳ���), ���ǾͿ���һ�߱���
//һ���ж�ÿ���ڵ��ǲ���ƽ��ġ�
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

    //�ڵݹ�ؽ��к������ʱ��ͬʱ�õ�ĳһ�ڵ����ȣ�Ҳ���ж���һ�����ǲ���ƽ�������
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


//������56�����������ֳ��ֵĴ���
//һ���������������������֮�⣬�������ֶ����������Ρ���д����
//�ҳ�������ֻ����һ�ε����֡�Ҫ��ʱ�临�Ӷ���O(n), �ռ临�Ӷ���O(1)��

//˼·��
//����ĳ������ֻ��һ�����ֳ�����һ�Σ����������ֶ����������Ρ�
//��ô�ҳ�������ֿ������������
//���ڵ�����ת��Ϊ��ν�����������ֳ����������飬
//���������������ֻ��һ�����ֳ�����һ�Σ����������ֶ����������Ρ�
//�����ճ���ͷ��β��ÿ�����ֽ���������㣬���յõ��Ľ��Ϊ
//����������һ�ε����ֵ����ֵ
//��ô����Ѱ�Ҹ�ֵ�ĵ�һ��Ϊ1��λ�ã���ÿ�����ֵĸ�λ�������ж�
//��Ϊ������ͬ�����ֵ�����һλ������ͬ�ģ����ǲ����ܰ�������ͬ�����ַ��䵽������������ȥ
//���Եõ�����������
//ÿ�����������һ�����ֳ���һ�Σ����������ֶ����������Ρ�
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

    //����д����
    //int basis_of_determination = 0x80000000;
    //while (wei--)
    //    basis_of_determination >>= 1;
    //������������ʱ�����λ����1

    int basis_of_determination = 0x40000000;
    while (wei!=1)
    {
        basis_of_determination >>= 1;
        --wei;
    }

    int num1 = 0;//��0���ֵ���䣬���Գ�ֵ����Ϊ0
    int num2 = 0;
    for (int i = 0; i < length; ++i)
    {
        if (data[i] & basis_of_determination)//***ע***
            num1 ^= data[i];                      //����ֻ����һ�ε����֣���������һ������ͬ
        else                                               //����һ����������һ��ĳλΪ1����һ��ĳλΪ0
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
    //INT_MAXΪ2147483647����01111111111111111111111111111111
    // 
    //***ע***
    //�ο�������15
    int flag = 0x40000000;      //��01000000000000000000000000000000

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
//***ע***
//Ҳ���Ը�ΪѰ�Ҷ������������һ��Ϊ1��λ��λ��
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


//������Ψһֻ����һ�ε�����
//��һ�������г�һ������ֻ����һ��֮�⣬�������ֶ����������Ρ�
//���ҳ��Ǹ�ֻ����һ�ε����֡�

//˼·��
//λ�����Դ���������ε����֣������ܴ���������ε����֡�
//������λ������뷨��
//���һ�����ֳ������Σ���ô���Ķ����Ʊ�ʾ��ÿһλ(0����1)
//Ҳ�������Ρ���������г������ε����ֵĶ����Ʊ�ʾ��ÿһλ���ֱ�
//����������ôÿһλ�ĺͶ��ܱ�3������
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

    //���������е����֣������ֵĶ����Ʊ�ʾ��ÿһλ���ֱ������
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
        if(bitArray[j]%3!=0)//������һ�ε����֣���3ȡ��һ����Ϊ0
        {
            int tmp = 1;
            tmp <<= 31 - j;

            res |= tmp;//***ע***ͨ��  ������  ����  �������  ���õ����ϵ�����
        }
    }

//�õ��������ַ�����
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


//������57����Ϊs������
//����һ����������������һ������s���������в�����������
//ʹ�����ǵĺ�������s������ж�����ֵĺ͵���s, ���������һ�Լ��ɡ�
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

    //***˼·***
    //�����Ѿ����������������һ����
    //��˫ָ��˼�룬��϶��ַ��Ľ�ȡ���ݶε������ж�����

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


//����һ������s����ӡ�����к�Ϊs��������������(���ٺ���������)��
//���磬����15, ����1 + 2 + 3 + 4 + 5 = 4 + 5 + 6 = 7 + 8 = 15, 
//���Դ�ӡ��3����������1��5��4~6��7~8��
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

    //***˼·***
    //������������������������һ����
    //��˫ָ��˼�룬��϶��ַ��Ľ�ȡ���ݶε������ж�����

    int begnum, endnum;
    begnum = 1, endnum = 2;
    int tmp,flag=false;

    while (begnum < endnum)//***ע***   ����д<=
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
//***ע***
//���ǵ�ÿ�β���֮������кͲ���֮ǰ��������ȴ󲿷����ֶ���һ���ģ�
//ֻ�����ӻ��߼�����һ�����֣�������ǿ�����ǰһ�����еĺ͵Ļ�����
//�����֮������еĺ͡��������Լ��ٺܶ಻��Ҫ�����㣬�Ӷ���ߴ����Ч�ʡ�
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


//������58����ת�ַ���
//��ת����˳��
//����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣
//Ϊ������������ź���ͨ��ĸһ���������������ַ���"I am a
//student.",�����"student.a am I"��
#if 0
#include <iostream>
#include <algorithm>
using namespace std;

char* reverse_word_order(char* target);
char* reverse_all(char* begidx,char* endidx);

int main()
{
    //***ע***
    //��������޸��ַ������Ͳ�Ҫ��ָ��ָ���ַ�����������
    //const char* data="I am a student.";

    //��ʼ���ַ��������洢�ַ���
    char data[] = "I am a student.";

    cout << reverse_word_order(data);

    return 0;
}

char* reverse_word_order(char* target)
{
    if (target == nullptr)
        return const_cast<char*>("Error input!");

    //�����ַ������ȣ�����ĩβ���ַ���
    char* tmp = target;
    int length = 0;

    //����д����
    //while (tmp)

    while(*tmp!='\0')
    {
        ++length;
        ++tmp;
    }

    //�ȷ�ת�����ַ�
    reverse_all(target,target+length);

    //�ٶ�ÿһ�����ʵ��ַ����з�ת
    char* begidx, *endidx;
    begidx = endidx = target;

    //д��һ��
#if 0
    while(*endidx!='\0')
    {
        //***ע***
        //�����ж��Ƿ��ַ���ĩβ�����ж��Ƿ�Ϊ�ո��ַ�
        while (*endidx != '\0' &&*endidx != ' ')
            ++endidx;

        reverse_all(begidx,endidx);

        //Խ���ո��ַ�
        if(*endidx != '\0')
			++endidx;

        begidx = endidx;
    }
#endif

    //д������
#if 1
    // ��ת�����е�ÿ������
    char* pBegin, * pEnd;
    pBegin = pEnd = target;
    while (*pBegin != '\0')
    {
        //��һ�������Ѿ���ɷ�ת����
        if (*pBegin == ' ')
        {
            pBegin++;
            pEnd++;
        }//��pEndָ��ﵽһ�����ʵ�ĩβ
        else if (*pEnd == ' ' || *pEnd == '\0')
        {
            reverse_all(pBegin, pEnd);
            pBegin = pEnd;
        }
        else//pEndָ��δ�ﵽһ�����ʵ�ĩβ
            pEnd++;
    }
#endif

    return target;
}

char* reverse_all(char* begidx, char* endidx)
{
    //endidxԭ��ָ��ĩβ�Ŀ��ַ���ָ��ո��ַ���
    //���Ҫ����ǰ�ƶ�һ���ַ���λ
    --endidx;

    while (begidx<endidx)
    {
        char tmp = *begidx;
        *begidx = *endidx;
        *endidx = tmp;

        ++begidx;
        --endidx;
    }

    //��������ɣ�
    //.tneduts a ma I

    return const_cast<char*>("OK");
}
#endif


//����ת�ַ�����
//�ַ���������ת�����ǰ��ַ���ǰ������ɸ��ַ�ת�Ƶ��ַ�����β����
//�붨��һ������ʵ���ַ�������ת�����Ĺ��ܡ����磬�����ַ���
//"abcdefg"������2, �ú�������������ת��λ�õ��Ľ��"cdefgab"��
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

//�Լ��Ľⷨ��
//Ҫ����deque����������Ҫ�������θ�ֵ����
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
    }//��������strlen()������

    if (n > length)
        return const_cast < char*> ("Error !\n");

    //����һ��˫�˶��У����ڴ洢����ĩβ���ַ����ַ�������
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

//��Ҫһ�����ɵĽⷨ��
//abcdefg ���
//cdefgab
//�����ַ�����ת�õ�bagfedc
//�۲�õ����൱�ڶ�ԭ�ַ����� ab �� cdefg �ֱ���з�ת�������������з�ת����
//���ֻ��Ҫ����3��ǰ���Reverse�����Ϳ���ʵ���ַ���������ת���ܡ�
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


//������59�����е����ֵ
//�������ڵ����ֵ
//����һ������ͻ������ڵĴ�С�����ҳ����л�������������ֵ��
//���磬�����������{ 2,3,4,2,6,2,5,1 }���������ڵĴ�С3,
//��ôһ������6���������ڣ����ǵ����ֵ�ֱ�Ϊ{ 4,4,6,6,6,5 }
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

//�ⷨһ��
//ʹ��priority_queue����
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
        pq.;//���ȶ����޷�������������е�Ԫ�ص�����
        //һ������û�иù��ܵķ�������һ�����������Ѿ��ź�����
        pq.push(data[i++]);

        cout << pq.top() << ", ";
    }
    */

    //���ѵ�Ľ��������
    //ת��˼·��û�б�Ҫ��λ��������������Ԫ��λ�ò�����Ԫ��
    //��ÿ�δ��ڻ���ʱɾȥ��
    //����Ӱ������������ȶ��еĶ���Ԫ�أ����������ڻ���ʱ��
    //Ҫ�ж϶���Ԫ�ص���ԭ�����е�����ֵ�Ƿ��ڴ����⣬����ǣ�
    //��ɾȥ�������Ԫ�ؼ��ɡ�
    //��ˣ����ȶ��е�ÿ��Ԫ���Ǹ��ṹ�壨��pair���󣩣�
    //����Ԫ��ֵ�͸�Ԫ�ص�����ֵ

    priority_queue<pair<int,int>> pq;

    int i;
    for ( i = 0; i < WindowLength; ++i)
        pq.emplace(data[i],i);

    //***ע***
    //push() ���ѹ������ĸ�����Ϊ������ӵ������У������ö���Ԫ�����͵Ķ���
    //emplace() �ڶ���ĩβ�͵ع���һ���¶����������е�Ԫ�����͹��캯�������õĲ�����Ϊ������

    cout << pq.top().first<<", ";

    while(i != dataLength)
    {
        pq.emplace(data[i], i);

        //***ע***
        //�жϵ�ǰ�����е����ֵ��Ӧ������ֵ�Ƿ�
        //λ�ڴ������������
        //ע���õ���whileѭ��
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

//�ⷨ����
//ʹ��deque����
//˳�ŷ���һ��˼·���������Ż���
//����������Ҫ������ǻ������ڵ����ֵ��
// �����ǰ�Ļ����������������±� i �� j������ i �� j ����࣬
// ���� i ��Ӧ��Ԫ�ز����� j ��Ӧ��Ԫ�أ���ô�ᷢ��ʲô�أ�
//���������������ƶ�ʱ��ֻҪ nums[i] ���ڴ����У���ô nums[j] һ��Ҳ���ڴ����У�
//���� nums[i] �� nums[j] ���������֤�ġ�
//��ˣ����� nums[j] �Ĵ��ڣ�nums[i] һ�������ǻ��������е����ֵ�ˣ�
//���ǿ��Խ� nums[i] ���õ��Ƴ�
//�������ܱ�֤˫�˶��е���Ԫ��һֱ�ǵ�ǰ����״̬�µ����ֵ���Ͳ���Ҫ���ȶ�����
void TheMaxNumInSlidingWindow(int* data, int dataLength, int WindowLength)
{
    if (data == nullptr || WindowLength > dataLength || WindowLength <= 0)
        throw exception("Error input!");

    deque <int> index;

    for (int i = 0; i < WindowLength; ++i)
    {
        //��index�������ݣ��ҵ�ǰҪ�����Ԫ��ֵ���ڵ�����һ��Ԫ�ص�ֵ
        while (!index.empty() && data[i] >= data[index.back()])
            index.pop_back();//index�д��ĳβԪ�ص����������������ֵ�������Ǹ�ֵ

        index.push_back(i);
    }
    //�ڴ������ɺ�index�д���Ǹô��ڷ�Χ�ڵ����ֵ��Ӧ������ֵ

    //���ڿ�ʼ����
    for (int i = WindowLength; i < dataLength; ++i)
    {
        cout << data[index.front()] << ", ";

        //��index�������ݣ��ҵ�ǰҪ�����Ԫ��ֵ���ڵ�����һ��Ԫ�ص�ֵ
        while (!index.empty() && data[i] >= data[index.back()])
            index.pop_back();//index�д��ĳβԪ�ص����������������ֵ�������Ǹ�ֵ
                
        //��index�������ݣ��ж����ֵ��Ӧ������ֵ�Ƿ��ڴ��ڷ�Χ��
        if (!index.empty() && index.front() <= i - WindowLength)
            index.pop_front();

        //����index���Ƿ������ݣ���ǰҪ�����Ԫ��ֵС����һ��Ԫ�ص�ֵ
        index.push_back(i);
    }

    cout << data[index.front()];

    return;
}
#endif


//���е����ֵ
//�붨��һ�����в�ʵ�ֺ���max�õ�����������ֵ��Ҫ����max��
//push_back��pop_front��ʱ�临�Ӷȶ���O(1)��
//�൱��Ҫ��dequeʵ��priority_queue
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

    //***ע1***
    //����Ϊ����д��
    //using std::deque;
    //using namespace std;
    //һ������ʹ��using����Ϊ���������಻����(������)�����ͬ������

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
    //��MaxIsTheTopElement�������ݣ��ҵ�ǰҪ�����Ԫ��ֵ���ڵ�����һ��Ԫ�ص�ֵ
    while (!MaxIsTheTopElement.empty() && num >= MaxIsTheTopElement.back().number )
        MaxIsTheTopElement.pop_back();//MaxIsTheTopElement���ĩβԪ�ص�����
    //�����������ֵ�������Ǹ�ֵ

    //***ע2***
    //����д��
    //MaxIsTheTopElement.emplace(num,CurrentIndex);
    //ԭ��emplace()������Ҫ�õ�ĳԪ�����͵Ĺ��캯�������ṹ��û�й��캯������

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

    //MaxIsTheTopElement������Ԫ�ص�����������һ��ĺͻ������ڵ����߽�Ƚ�
    //�ڴ˴�������һ��data���������ֻҪ�жϵ������Ƿ��Ǻ�data����������Ԫ����ͬ����
    if (MaxIsTheTopElement.front().index == data.front().index)
        MaxIsTheTopElement.pop_front();

    data.pop_front();

    //***ע3***
    //�˴�CurrentIndexֵ���õݼ�
    //��Ϊ�ñ����������ж�data����Ҫ������Ԫ�غ�MaxIsTheTopElement����Ҫ������Ԫ��
    //�Ƿ�����ͬ��CurrentIndexֵ��Ϊ�жϵ�����Ԫ���Ƿ���ͬ����CurrentIndex�ݼ���
    //�����MaxIsTheTopElement�е�ֵ���󵯳������
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


//������60��n�����ӵĵ���
//��n���������ڵ��ϣ��������ӳ���һ��ĵ���֮��Ϊs��
//����n, ��ӡ��s�����п��ܵ�ֵ���ֵĸ��ʡ�
#if 0
#include <iostream>
#include <memory>
#include <iomanip>
#include <algorithm>
using namespace std;

//�涨һ�������ܵõ������ֵ
const int g_maxValue = 6;

void PrintProbability(int number);
void Probability(int num, unique_ptr< int[] >&);
void Probability(int original, int current, int sum, unique_ptr< int[] >& pProbabilities);

void PrintProbability_Solution2(int number);
void PrintProbability_Solution3(int number);

int main()
{
    //n�����ӣ����ܵõ������п��ܵ�ֵ�ĸ���
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

    //����maxSum��Ͷ�� number �����ӿ��ܻ�õ�����ܺ�
    int maxSum = number * g_maxValue;

    //������ָ�����̬������ڴ棬
    //�洢���ܳ��ֵĲ�ͬ�ܺ͵ļ�����
    unique_ptr< int[] > pProbabilities(new int [maxSum - number + 1] {0});
    //����nΪ2����ô��ֵ��ΧΪ2~12����Ҫ11���洢λ��

    //***ע***
    //ʹ����C++11��һ���Գ�ʼ��(Uniform Initialization)

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
    //��n�����ӷ�Ϊ���ѣ���һ��ֻ��һ������һ����n-1��
    //���ڵ�һ�ѣ�
    //����ÿ�����ܵ��������ֵ���� 1 �� g_maxValue��
    for (int i = 1; i <= g_maxValue; ++i)
        Probability(num, num, i, pPro);
}

//����ʣ�µ���һ�Ѽ�n-1������
//��Ȼ�ֳ����ѣ���һ��ֻ��һ�����ڶ�����n-2�������ǰ���һ���Ǹ��������ӵ�
//��������һ�ֵ������ӵĵ�����ӣ��ٺ�ʣ�µ�n - 2����������������͡�
void Probability(int original, int current, int sum, unique_ptr< int[] >& pProbabilities)
{
    //***���***
    // original ��ʾ�����Ͷ��������current ��ʾ��ǰʣ���Ͷ��������sum ��ʾ��ǰ�ۻ����ܺ͡�
    // �����ǰʣ���Ͷ������ current ���� 1���򽫵�ǰ�ۻ����ܺ� sum - original ��Ϊ������
    // �� pProbabilities ��������Ӧλ�õĴ����� 1��
	// �����ǰ��Ͷ������ current ���� 1����ʹ��ѭ���ݹ��������
    // ÿ�εݹ齫��ǰ��Ͷ�������� 1���ۻ����ܺ����ӵ�ǰ�������ֵ i
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

//������
#if 1
void PrintProbability_Solution2(int number)
{
    if (number < 1)
        return;

    //ʹ��һ����ά���� pProbabilities ,
    //���е�һά����洢����Ͷ����ÿ����ֵ���ֵĴ���
    //��һ��һά�������ڸ����洢ֵ
    //��������һά���齻���Ϊ��������
    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];

    for (int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }

    //ʹ�� flag �������н���ı�ǣ����ڱ�ʶ��ǰ���ڸ��µ������С�
    //һ��ʼ��pProbabilities[0]����������������
    int flag = 0;
    for (int i = 1; i <= g_maxValue; ++i)
        pProbabilities[flag][i] = 1;

    //ʹ�ö�̬�滮��˼�룬ͨ��ѭ������ÿ��Ͷ�������¸�����ֵ���ֵĴ�����
    //���ѭ�� k ��ʾ��ǰͶ���Ĵ������ڲ�ѭ�����ڼ�����ֵĴ�����
    for (int k = 2; k <= number; ++k)
    {
        //�ڼ��㵱ǰͶ�������¸�����ֵ���ֵĴ���ʱ��
        //���Ƚ��µ���������С�ڴ��� k ��λ�õĴ�����Ϊ 0��
        //��Щλ�õ�Ԫ��Ҫ���и���
        for (int i = 0; i < k; ++i)
            pProbabilities[1 - flag][i] = 0;
        //***ע***
        //1-flag���ڽ��潫ĳ��һά����������Ϊ0

        // ÿ��Ͷ�����������ֵ���� 1 �� g_maxValue ֮�䣬
        // ���� i ��ʾ���ܵ��ܺ�ֵ�ķ�Χ�Ǵ� k����С���ܵĺ�ֵ����ÿ�ζ�Ͷ���� 1 ������µĺ�ֵ��
        // �� g_maxValue * k��ÿ�ζ�Ͷ���� g_maxValue ������µ�����ֵ����
        
        // �ڷ�ΧΪ k �� g_maxValue * k ֮���λ���ϣ�
        // ����ÿ����ֵ���ֵĴ�����
        // ����ͨ������ǰһ���������еĺ�ֵ��
        // �ڵ�ǰ��ֵ��λ�����ۼӿ��ܵ��������ֵ���õ��Ĵ�����ʵ�ֵ�
        for (int i = k; i <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;

            // �µ���������
            // j ��ʾ��ǰͶ�������ӵĵ�����
            // �� 1 ��ʼ������ֱ����ǰ��ֵ i �����ӵ����� g_maxValue ��С���Ǹ�ֵ��
            // ������Ϊ��Ͷ�����������ֵ���ڵ�ǰ�ĺ�ֵ i ���߳��������ӵ����� g_maxValue ʱ��
            // �Ͳ���Ҫ�������ֵ����Ϊ������Ե�ǰ��ֵ����Ӱ�졣
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

//������
//�ο�https://cloud.tencent.com/developer/article/1947235
void PrintProbability_Solution3(int number)
{
    //��Ϊ���Ľ��ֻ��ǰһ����̬ת�������йأ���������ֻ��Ҫ����һ��һά�Ķ�̬ת������
    //ԭ��dp[i][j]��ʾ����ǰi�����ӵĵ���֮��Ϊj�ĸ��ʣ�����ֻ��Ҫ����״̬�����飬
    //���Ծ�ֻ��һ��һά����dp[j]��ʾn��������ÿ������ĸ��ʡ�
    
    //��ʼ��1����������µĵ���֮���������ֻ��6�������������dp�ĳ�ʼ����size��6��
    double* dp = new double[6];

    //ֻ��һ������
    fill(dp, dp + 6,1/6.0);

    int length = 6;

    //�ӵ�2�����ӿ�ʼ������number��ʾnumber�����ӣ�
    //�ȴӵڶ������������Ȼ��������3����4��������n�������
    // i ��ʾ���ܹ�i������ʱ�Ľ��
    for (int i = 2; i <= number; i++) 
    {
        //ÿ�εĵ���֮�ͷ�Χ���е�仯������֮�͵�ֵ�����i*6����С��i*1��i֮ǰ�Ľ��ֵ�ǲ�����ֵģ�
        //����i=3������ʱ����С����3�ˣ���������2��1�������ֵ��18����Ҫ�Ĵ洢�ռ���18-3+1=16
        //���Ե���֮�͵�ֵ�ĸ�����6*i-(i-1)������5*i+1
        //����i������ʱ�ĵ���֮�͵�ֵ�����ȼٶ���temp
        double* temp = new double[5 * i + 1] {0};
        //***ע***
        //iΪ2ʱ��temp[0]�����ֵΪ2�ĸ��ʣ�iΪ3ʱ��temp[0]�����ֵΪ3�ĸ���

        //��i-1�����ӵĵ���֮�͵�ֵ�������֣�����i�����ӵĵ���֮�������ֵ
        //***ע***
        //i-1�����ӵĵ���֮�͵ĸ�����ֵ�ĸ��ʼ�dp����ĵ�j��ֵ��
        //����Ӱ�����i������ʱ��temp[j+k]��ֵ

        //***ע***
        //����д����
        //for (int j = 0; j < sizeof(dp)/sizeof(dp[0]); j++)
        //������ֻ����̬����ĳ��ȣ���������̬����ĳ��ȡ�

        for (int j = 0; j < length; j++)
        {
            //����ֻ��1������ʱ��dp[1]�Ǵ������ӵ���֮��Ϊ2ʱ�ĸ��ʣ�
            //����Ե���2������ʱ�ĵ���֮��Ϊ3��4��5��6��7��8����Ӱ�죬
            //��Ϊ����һ�����ӵ�ֵΪ2ʱ����һ�����ӵ�ֵ����Ϊ1~6��
            //�����ĵ���֮����Ӧ�ľ���3~8��
            //��dp[2]�������֮��Ϊ3ʱ�ĸ��ʣ�
            //�������2������ʱ�ĵ���֮��Ϊ4��5��6��7��8��9����Ӱ�죻
            //����k��������Ƕ�Ӧ�ŵ�i�����ӳ���ʱ���ܳ����������     
            for (int k = 0; k < 6; k++) 
            {
                //����ǵ��Ǽ���dp����ֵ��1/6�ĳ˻���1/6�ǵ�i������Ͷ��ĳ��ֵ�ĸ���
                temp[j + k] += dp[j] * (1.0 / 6.0);
            }
        }

        //i�����ӵĵ���֮��ȫ���������Ҫ��temp�����ƽ���dp���飬
        // dp����ͻ����i������ʱ�Ŀ��ܳ��ֵĵ���֮�͵ĸ��ʣ�
        // ���ڼ���i+1������ʱ�ĵ���֮�͵ĸ���

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


//������61���˿����е�˳��
//����˼·��
//���Ȱ������������ͳ��������0�ĸ���(����С������)
//���ͳ������֮�����������������֮��Ŀ�ȱ�����������ȱ������
//С�ڻ��ߵ���0�ĸ�������ô���������������ģ���֮��������
//����
//���Ȱ������������ͳ��������0�ĸ���(����С������)
//Ȼ��������ָ�����Ƚ��������ֵĲ�ֵ��
//�Բ�ֵ��������з��ദ��
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
    //������ָ��ֱ�Ӷ�λ�ڷǴ�С������С���������ִ�
    int* theBeg = numbers+CntZero;
    int* theEnd = numbers + CntZero + 1;
    int difference_value = *theEnd - *theBeg;

	while (theEnd!=numbers+length)
	{
        //������0��ֱ����false
        //������1���ͼ����ƶ�����ָ��
        //������2��CntZero������ڵ���1
        //������3��CntZero������ڵ���2
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
        //��Ϊ���´���飬��֧�ֶ����С�������
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
//***ע***
//Ҫ��һ�������ٶȣ����Բ���sort()�������ó���Ϊ14�Ĺ�ϣ��������O(n)
//��ʱ���ڿ��������
#endif


//������62��ԲȦ�����ʣ�µ�����
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

    //ԲȦ�н�һ������
    if (n == 1)
        return 0;

    list<int> circle;

    for (int i = 0; i < n; ++i)
    {
        circle.push_back(i);
    }

    //����gostep����ָ���ƶ��Ĵ���
    int gostep;
    //����ָ��ָ��Ҫɾ����Ԫ�����ڵ�λ��
    // ***(��mΪ1���ƶ�)***
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
		//***����д��***
		//list�ĵ���������������ʵ�����
		//auto next_pos = erase_pos+1;

        //����дΪauto next_pos = ++erase_pos ;    --erase_pos ;     ...     erase_pos=next_pos;

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


//������63����Ʊ���������
//˼·����ɨ�赽��i��Ԫ��ֵʱ���ܹ���ס֮ǰ��i-1�������е���Сֵ
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

    //�ӵ�����Ԫ�ؿ�ʼ����
    for (int i = 2; i < length; ++i)
    {
        TmpMinValue = TmpMinValue < stk[i] ? TmpMinValue : stk[i];
        TmpMaxValue = TmpMaxValue > stk[i] ? TmpMaxValue : stk[i];
    }

    return TmpMaxValue - TmpMinValue;
}
#endif


//������64����1+2+3+...+n
#if 0
#include <iostream>

using namespace std;

//�ⷨһ�����ù��캯����static��Ա��������ֱ��ʹ��ѭ��
class Tmp
{
private:
    //***ע***
    //�����˾�̬��Ա�������ڳ�ʼ��ʱִ��һ�γ�ʼ����䣬֮�󲻻����ظ�ִ��
    //���ص㣬����¼ÿ��Ҫ�ۼӵ�ֵN�����ܺ�Sum
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

//***ע***
//��������������Ϊstatic�����ã�
//����ʵ��������Ϳ��Ե��ã�
//��ͨ�ĳ�Ա������Ҫͨ�����ʵ����������ܵ��ã�
//����̬��Ա��������ֱ��ͨ�����������ã����贴����Ķ���ʵ����

//��������������Ϊstatic�����ã�
//��ִ��ʱ���������κ��ض��Ķ���
//��˶���ȫ�ֲ����ǳ����á�

int Sum_solution_1(int n)
{
    //����һ��Tmp�����飬����n��Tmp�����
    //��ô��Щ����󶼻��ɹ��캯��������
    //���캯�������n��
    unique_ptr<Tmp[]> t(new Tmp[n]{});
    
    //***ע***
    //����д����
    //return t->GetSum();

    //��⣺
    //t ��һ��ָ�� Tmp ��������� unique_ptr �������������������ڴ�
    //�������������� Tmp ��Ķ��󡿣���˲���ֱ�ӷ������еķ�����
    //Ҫ������ķ���������Ҫͨ�� unique_ptr ���е�ָ���ӵط�������Ԫ�أ�
    //���ڸ�Ԫ���ϵ�����Ӧ�ķ���
    return t[0].GetSum();
}

//�ⷨ���������麯������ֱ��ʹ�õݹ飨���еݹ���һ�������õ�if�ĵط����жϺ�ʱ�ݹ���ֹ��
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
        //����ȡ������
        //nΪ100  !nΪ0  !!nΪ1
        //nΪ0      !nΪ1  !!nΪ0
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

//�ⷨ����ʹ�ú���ָ��������ֱ��ʹ�õݹ�
typedef int (*pFun)(int);

int Sum_solution_3_terminate(int n)
{
    return 0;
}

int Sum_solution_3(int n)
{
    pFun funArray[2] = { Sum_solution_3_terminate ,Sum_solution_3 };

    //����д����
    //return funArray[!!n](--n) + n;
    return funArray[!!n](n-1) + n;
}

//�ⷨ�ģ�ģ��Ԫ��̣��ڱ�����ȷ��ֵ
template<int n>
class Sum_solution_4
{
public:
    enum Value {N=Sum_solution_4<n-1>::N+n};

    Sum_solution_4()
    {}

};

//ģ����廯
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

    //����д����
    //Sum_solution_4<n> s4;    //ԭ�򣺷�ģ�����Ͳ�������Ϊ����ֵ
    Sum_solution_4<100> s4;    
    cout<< s4.N <<endl;

    return 0;
}
#endif


//������65�����üӼ��˳����ӷ�
//˼·���������ߡ����ڶ�����Ҳ����
//��һ������λ��ӵ������н�λ
//�ڶ��������½�λ��
//����������ǰ����������Ľ�����
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
//��һ��ѭ����
//XOR_res                  =0001 0100
//OperationAfterAnd =0000 0010
//�ڶ���ѭ����
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
//��һ��ѭ����
//XOR_res                  =1111 1111 1111 1111 1111 1111 1111 1101 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 0100
//�ڶ���ѭ����
//XOR_res                  =1111 1111 1111 1111 1111 1111 1111 1001 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 1000
//ֱ��ĳ��ѭ��
//XOR_res                  =0000 0000 0000 0000 0000 0000 0000 0001 
//OperationAfterAnd =0000 0000 0000 0000 0000 0000 0000 0000

//���������ķ�����(���ܽ����ӵ������и��������)
#if 0
int Add(int num1, int num2)
{
    int XOR_res = num1 ^ num2;

    //���½�λ��λ�ò�������λ
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
        //��һ��Ҳ�ǵ�����
        //�洢�ǽ�λ��
        XOR_res = num1 ^ num2;
        //�ڶ���
        //������������ĳλҪ��λ�Ĵ���
        OperationAfterAnd = (num1 & num2) << 1;

        num1 = XOR_res;
        num2 = OperationAfterAnd;
    }  

    return num1;
}
#endif
#endif


//������66�������˻�����
//����һ������A[0,1,��n-1],�빹��һ������B[0,1,��n-1],����B�е�Ԫ��
//B[i] =  A[0]��A[1]������A[ i - 1]��A[i + 1]������A[n - 1]������ʹ�ó�����
//�ⷨ��
//B[i] = A[0]��A[1]������A[i-1]��A[i+1]������A[n-1]
//����A[0]��A[1]������A[i - 1] �� A[i + 1]������A[n - 2]��A[n - 1]�����ֵĳ˻���
//�������ֱַ�������C������D��ʾ
//��������C[i]�ļ������϶���
//��������D[i]�ļ������¶���
//������B������һ��������������
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

        //����д����
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
        //������C[i]����ã�����������C������ֱ�����������B�ϲ���
        output[0] = 1;
        for (int i = 1; i < length1; ++i)
        {
            output[i] = output[i - 1] * input[i - 1];
        }

        for (auto x : output)
            cout << x << " ";
        cout << endl;

        //������D[i]����ã����������Ĳ����Ǵ�B[4]��ʼ����B[0]����
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


//������67���Լ�дһ��atoi()���ܵĺ���
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
    //Ҫ���ǵ��Ļ���������������
    //nullptr   �� ""  �� +  �� -  �����
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
    //***ע***
    //����Ϊlong long���ж϶���int�����Ƿ����
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

        //***ע***
        //�ڶ��ִ�������
        //���Բ���дRunOnlyOnce�����ǽ�����Ĵ�����ѭ����ժ����Ȼ��
        //ѭ���Լ�����Ĵ�����Ƶ� int StrToIntCore(const char* str, bool Positive)��

        //Ϊ"-123junk-  123"  �����������ԵĲ���
        if (!isdigit(*traverse) && !isspace(*traverse))
            break;

        if (isdigit(*traverse))
        {
            res = res * 10 + (*traverse) - '0';
        }

        ++traverse;
    }

    //***ע***
    //numeric_limits<int>::min()ʽ�ӱ�����Ϊ constexpr �����ʽ�˶��ڱ����ڡ�
    if(res<numeric_limits<int>::min()||res>numeric_limits<int>::max())
    {
        flag= USER_OVERFLOW;

        return 0;
    }

    return Positive ? res : -res;
}
#endif


//������68�����������ڵ����͹�������
//ע�ⲻ�Ƕ�����
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

// ��״��ͨ����
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

//�õݹ��ҳ���ĳ�ڵ��Ψһ·��
bool GetNodePath(const TreeNode* pRoot, const TreeNode* pNode, 
    list<const TreeNode*>& path)
{
    if (pRoot == pNode)
        return true;

    path.push_back(pRoot);

    bool found = false;

    //���Ƕ������Ĵ�����
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

    //***ע***
    //����ͷ��ʼ�ҵ�����
    //��һ��iterator1��iterator2��ͬʱ������һ�ξ������һ�������ڵ�
    //��������52�Ա�
    while (iterator1 != path1.end() && iterator2 != path2.end())
    {
        if (*iterator1 == *iterator2)
            pLast = *iterator1;

        iterator1++;
        iterator2++;
    }

    return pLast;
}

// �������ڵ�
TreeNode* CreateTreeNode(int value) 
{
    TreeNode* pNode = new TreeNode();
    pNode->m_nValue = value;
    return pNode;
}

// �������ڵ㣬�� pChild ���Ϊ pParent ���ӽڵ�
void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild) 
{
    if (pParent != nullptr) 
    {
        pParent->m_vChildren.push_back(pChild);
    }
}

// ��ӡ�����ڵ�
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

// ��ӡ������
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

// ����������
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

//����ָOffer ���ݽṹ���㷨��


//������3��ǰn�����ֶ�������ʽ��1�ĸ���
#if 1
#include <iostream>
#include <vector>
using namespace std;

void CountBits(int num,vector<int>& );

int main()
{
    unsigned int num;
    cin >> num;

    //����0������num
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
//�ⷨһ��
//����i&(i-1)+1 
//��i�Ķ�������ʽ�����ұߵ�1���0��Ҳ����˵��
//����i�Ķ�������ʽ��1�ĸ����ȡ�i & ��i - 1�����Ķ�������ʽ��1�ĸ�����1
//��O(1)��ʱ����������i�Ķ������ж���λ��ֵΪ1
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

    //������⣺
    //vec[i] = vec[i & (i - 1)] + 1;�ȼ���vec[i] = vec[i - 1] + 1;
    //������
    //iΪ4ʱ��i & (i - 1)Ϊ0

    return;
}
#endif

//�ⷨ����
//���������i��һ��ż������ôi�൱�ڽ���i / 2������һλ�Ľ�������ż��i�͡�i / 2��
//�Ķ�������ʽ��1�ĸ�������ͬ�ġ����i����������ôi�൱�ڽ���i / 2������һλ֮��
//�ٽ����ұ�һλ��Ϊ1�Ľ�����������i�Ķ�������ʽ��1�ĸ����ȡ�i / 2����1�ĸ�����1��
#if 1
void CountBits(int num, vector<int>& vec)
{
    if (num < 0)
        throw exception("Invalid number");

    vec[0] = 0;

    for (int i = 1; i <= num; ++i)
    {
        vec[i] = vec[ i >>1 ] + (i&1);//***ע***С���ű����
    }

    return;
}
#endif
#endif