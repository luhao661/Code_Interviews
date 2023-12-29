//����ָOffer ���ݽṹ���㷨��


//������3��ǰn�����ֶ�������ʽ��1�ĸ���
#if 0
#include <iostream>
#include <vector>
using namespace std;

void CountBits(int num, vector<int>&);

int main()
{
    unsigned int num;
    cin >> num;

    //����0������num
    vector<int> vec(num + 1);

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
        vec[i] = vec[i >> 1] + (i & 1);//***ע***С���ű����
    }

    return;
}
#endif
#endif


//������5�����ʳ��ȵ����˻�
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    vector<string> vec_str;

    string tmp;
    while (cin >> tmp)
    {
        vec_str.push_back(tmp);
    }

    //����һ������Ϊ26��������ģ���ϣ��
    int hash[26] = {};

    //ĳ��������û����ͬ����ĸ
    bool flag = 0;

    int MaxMultiply = 0;

    for (auto it_1 = vec_str.begin(); it_1 != vec_str.end(); ++it_1)
    {
        int len_1 = (*it_1).length();
        for (int i = 0; i < len_1; ++i)
        {
            ++hash[(*it_1)[i] - 'a'];
        }

        for (auto it = it_1 + 1; it != vec_str.end(); ++it)
        {
            int len = (*it).length();
            for (int i = 0; i < len; ++i)
            {
                if (hash[(*it)[i] - 'a'] != 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                int Max = len_1 * len;

                //MaxMultiply = Max > MaxMultiply ? Max : MaxMultiply;
                MaxMultiply = max(MaxMultiply, Max);
            }
            else
            {
                flag = 0;
                continue;
            }
        }

        fill(hash, hash + 26, 0);
    }

    cout << MaxMultiply;

    return 0;
}
//���ԣ�
#if 0
abcw
foo
bar
fxyz
abcdef
#endif
#endif
//***ע***
//���ж��������ʵĸ�����ĸʱ����ʹ��ĸ�Ĳ���ʱ�临�ӶȽ���O(1)
//���Ƚ��������ʵ���ĸ����Ҫ���Ը��Ӷ�
//�����������Ķ�������λ��¼�ַ����г��ֵ��ַ������ö�������λ��ģ���ϣ��
//�����ж����������Ƿ�����ͬ��ĸ���Ϳ�����flags[i]&flags[j]==0���ж�
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    vector<string> vec_str;

    string tmp;
    while (cin >> tmp)
    {
        vec_str.push_back(tmp);
    }

    //ĳ��������û����ͬ����ĸ
    bool flag = 0;

    int MaxMultiply = 0;

    int TheNumberOfWords = vec_str.size();
    //***ע***
    //��shared_ptr����̬����������д��
    shared_ptr<int> flags(new int[TheNumberOfWords] {}, default_delete<int[]>());

    for (int i = 0; i < TheNumberOfWords; ++i)
        for (int j = 0; j < vec_str[i].length(); ++j)
            flags.get()[i] |= 1 << (vec_str[i][j] - 'a');//***ע*** ��get()����

    for (int i = 0; i < TheNumberOfWords; ++i)
    {
        for (int j = i + 1; j < TheNumberOfWords; ++j)
            if ((flags.get()[i] & flags.get()[j]) == 0)
            {
                int strLenMultiply = vec_str[i].length() * vec_str[j].length();
                MaxMultiply = max(MaxMultiply, strLenMultiply);
            }
    }

    cout << MaxMultiply;

    return 0;
}
#endif


//������6�����������е���������֮��
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void FindPairOfNumbers(const vector<int>& vec, int k);

int main()
{
    vector<int> vec;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));

    int k = 8;

    FindPairOfNumbers(vec, k);

    return 0;
}
#if 1
void FindPairOfNumbers(const vector<int>& vec, int k)
{
    //copy(vec.begin(),vec.end(),ostream_iterator<int>(cout));

    if (vec.size() <= 1)
        return;

    vector<int>::const_iterator ptr1, ptr2;//***ע***�˴�����д�� vector<int>:: iterator
#if 0
    ptr1 = vec.begin();
    ptr2 = vec.begin() + 1;

    while (*ptr1 + *ptr2 != k && ptr2 != vec.end())
    {
        if (*ptr1 + *ptr2 < k)
            ++ptr2;
        else
        {
            --ptr2;
            ++ptr1;
        }
    }
#endif
    //����
#if 1
    ptr1 = vec.begin();
    ptr2 = vec.end() - 1;

    while (*ptr1 + *ptr2 != k && ptr1 < ptr2)
    {
        if (*ptr1 + *ptr2 < k)
            ++ptr1;
        else
            --ptr2;
    }
#endif

    cout << distance(vec.begin(), ptr1) << " " << distance(vec.begin(), ptr2) << endl;
}
#endif
#if 0
#include <unordered_set>
//���������ù�ϣ��Ĳ���ʱ��ΪO(1)
void FindPairOfNumbers(const vector<int>& vec, int k)
{
    if (vec.size() <= 1)
        return;

    unordered_multiset<int> ums(vec.cbegin(), vec.cend());

    vector<int>::const_iterator i;

#if 0
    //����
    //������1 2 4 6 10 ������ ���Ϊ1 3   2 2   3 1 �����
    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        if (ums.find(k - *it) != ums.end())
        {
            i = find(vec.begin(), vec.end(), k - *it);

            cout << distance(vec.begin(), it) << " " << distance(vec.begin(), i) << endl;
        }
    }
#endif

    int tmp1 = -1, tmp2 = -1;
    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        if (ums.find(k - *it) != ums.end())
        {
            i = find(vec.begin(), vec.end(), k - *it);

            if (i != it && *it != tmp2 && *i != tmp1)
            {
                tmp1 = *it, tmp2 = *i;
                cout << distance(vec.begin(), it) << " " << distance(vec.begin(), i) << endl;
            }
        }
    }
}
#endif
#endif


//������7�������к�Ϊ0��3������
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void FindThreeNumbers(vector<int>&, int fixedNum, vector<int>::iterator);

int main()
{
    vector<int> vec;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));

    sort(vec.begin(), vec.end());

    for (auto it = vec.begin(); it != vec.end() - 2; ++it)
    {
        FindThreeNumbers(vec, *it, it);
    }

    return 0;
}
void FindThreeNumbers(vector<int>& vec, int fixedNum, vector<int>::iterator theIterator)
{
    if (vec.size() < 3)
        return;

    int SumOfPairOfTargetNums = -fixedNum;

    auto ptr1 = theIterator + 1;
    auto ptr2 = vec.end() - 1;

    while (ptr1 < ptr2 && *ptr1 + *ptr2 != SumOfPairOfTargetNums)
    {
        if (*ptr1 + *ptr2 > SumOfPairOfTargetNums)
            --ptr2;
        else
            ++ptr1;
    }

    if (*ptr1 + *ptr2 == SumOfPairOfTargetNums && ptr1 < ptr2)
        cout << fixedNum << " " << *ptr1 << " " << *ptr2 << " " << endl;
}
#if 0
- 1 0 1 2 - 1 - 4
#endif
#endif
//����û����ȥ��
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> FindThreeNumbers(vector<int>& nums);

int main()
{
    vector<int> vec;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(vec));

    sort(vec.begin(), vec.end());

    vector<vector<int>>res = FindThreeNumbers(vec);


    return 0;
}

vector<vector<int>> FindThreeNumbers(vector<int>& nums)
{
    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());

    int n = nums.size();

    for (int i = 0; i < n - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue; //��ǰ���ֺ�ǰһ��������ȣ�����

        int j = i + 1, k = n - 1;

        while (j < k)
        {
            int sum = nums[j] + nums[k];

            if (sum == -nums[i])
            {
                ans.push_back({ nums[i], nums[j], nums[k] });
                while (j < k && nums[j] == nums[j + 1])
                    j++;//��ָ���������Ҳ�������ȵ���

                j++;

                while (j < k && nums[k] == nums[k - 1])
                    k--;//��ָ�����������������ȵ���

                k--;
            }
            else if (sum > -nums[i])
                k--;
            else
                j++;
        }
    }
    return ans;
}
#endif


//������8���ʹ��ڻ����k�����������
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int FindTheShortestSubArray(const vector<int>& vec, int k);

int main()
{
    //vector<int> vec(istream_iterator<int>(cin),istream_iterator<int>());

    vector<int>vec1({ 5,1,4,3 });
    vector<int>vec2({ 5,1,4,2 });
    vector<int>vec3({ 1,1,1,1 });
    vector<int>vec4({ 1 });
    vector<int>vec5({});
    int k = 7;

    cout << FindTheShortestSubArray(vec1, k) << endl;
    cout << FindTheShortestSubArray(vec2, k) << endl;
    cout << FindTheShortestSubArray(vec3, k) << endl;
    cout << FindTheShortestSubArray(vec4, k) << endl;
    cout << FindTheShortestSubArray(vec5, k) << endl;

    return 0;
}
#if 0
int FindTheShortestSubArray(const vector<int>& vec, int k)
{
    if (vec.size() == 0)
        return 0;

    if (vec.size() == 1)
        return *vec.begin() >= k;

    auto ptr1 = vec.begin();
    vector<int>::const_iterator ptr2;

    int Sum = 0;
    int MinLen = numeric_limits<int>::max();

    for (; ptr1 != vec.end(); ++ptr1)
    {
        Sum = *ptr1;

        if (Sum >= k)
            return 1;

        for (ptr2 = ptr1 + 1; ptr2 != vec.end(); ++ptr2)
        {
            Sum += *ptr2;

            if (Sum >= k)
            {
                MinLen = min(MinLen, (int)distance(ptr1, ptr2) + 1);
                break;
            }
        }
    }

    return MinLen < numeric_limits<int>::max() ? MinLen : 0;
}
#endif
#if 1
//��������
int FindTheShortestSubArray(const vector<int>& vec, int k)
{
    //���ó�ʼ��Сֵ
    int MinLen = numeric_limits<int>::max();
    //��ʼ�������
    int sum = 0;
    //������������i��j(�����ڻ������ڵĸо�)
    for (int i = 0, j = 0; j < vec.size(); j++)
    {
        //���󴰿�
        sum += vec[j];

        while (i <= j && sum >= k)
        {
            //������Сֵ
            MinLen = min(MinLen, j - i + 1);
            //��С����
            sum -= vec[i++];
        }
    }

    //������������Ͷ�С��k,�򷵻�0�����򷵻ظ���ֵ
    return MinLen == numeric_limits<int>::max() ? 0 : MinLen;
}
//***ע***
//�ýⷨ��ʱ�临�Ӷ���Ȼ��O(n)��������Ϊ��������ѭ���У�
// ����j��i����ֻ���Ӳ����٣�����j��0���ӵ�n - 1������i��0������ӵ�n - 1��
// ����ܵ�ִ�д�����O(n)
#endif
#endif


//������9���˻�С��k��������
#if 0
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> FindSubArray(const vector<int>& vec, int k);

int main()
{
    int k = 100;
    vector<int> vec({ 10,5,2,6 });

    vector<vector<int>>res = FindSubArray(vec, k);
    //try
    //{
    //}
    //catch (exception& e)
    //{
    //    cout<<e.what();
    //}

    for (auto i = res.begin(); i != res.end(); ++i)
    {
        for (const auto& x : *i)
            cout << x << " ";

        cout << endl;
    }

    return 0;
}
vector<vector<int>> FindSubArray(const vector<int>& vec, int k)
{
    if (vec.size() == 0)
        throw exception("Error!");

    vector<vector<int>>res;

    int ptr1, ptr2, MultiplyRes = 1;

#if 0
    for (ptr2 = ptr1 = 0; ptr1 < vec.size(); ++ptr1)
    {
        MultiplyRes *= vec[ptr1];

        //����д����
        /*
        while (MultiplyRes < k)
        {
            res.emplace_back(vec.begin()+ptr2, vec.begin() + ptr1);

            if (ptr2 < ptr1)
                MultiplyRes /= ptr2++;
            else
                break;
        }
        */

        if (MultiplyRes >= k || ptr1 == vec.size() - 1)
        {
            if (MultiplyRes >= k)
            {
                MultiplyRes /= vec[ptr1];
                --ptr1;
            }

            while (MultiplyRes < k)
            {
                res.emplace_back(vec.begin() + ptr2, vec.begin() + ptr1 + 1);

                if (ptr2 < ptr1)
                {
                    MultiplyRes /= vec[ptr2];
                    ++ptr2;
                }
                else
                    break;
            }
        }
    }
    //***ע***
    //���Ϊ
#if 0
    10 5
        5
        5 2 6
        2 6
        6
#endif
#endif

#if 1
        for (ptr2 = ptr1 = 0; ptr1 < vec.size(); ++ptr1)
        {
            MultiplyRes *= vec[ptr1];

            //Ϊ�˵õ���ptr2Ϊ���ı�Ҫ��������鳤�ȳ�1��������
            if (MultiplyRes >= k || ptr1 == vec.size() - 1)
            {
                //ptr1����1���õ��Ե�ǰptr2Ϊ���������Ҫ���������
                if (MultiplyRes >= k)
                {
                    MultiplyRes /= vec[ptr1];
                    --ptr1;
                }

                while (MultiplyRes < k)
                {
                    //�桾�����𽥼��ٵ�1����������
                    res.emplace_back(vec.begin() + ptr2, vec.begin() + ptr1 + 1);

                    //ptr2 < ptr1����С��������
                    if (ptr2 < ptr1)
                    {
                        MultiplyRes /= vec[ptr2];
                        //���������ڡ�������ֵ������
                        res.emplace_back(vec.begin() + ptr2, vec.begin() + ptr2 + 1);
                        //ptr2�����ƽ�����С����
                        ++ptr2;
                    }
                    else//��ptr2 == ptr1
                        break;
                }
                //�˳�whileѭ����MultiplyRes��ֵΪ��ǰ�����������Ҳ��ֵ
            }
        }
#endif
    return res;
}
#endif
//�˻�С��k��������(��Ҫ���ӡ����������)
#if 0
#include <iostream>
#include <vector>
using namespace std;

int FindSubArray(const vector<int>& vec, int k);

int main()
{
    int k = 100;
    vector<int> vec({ 10,5,2,6 });

    int res = FindSubArray(vec, k);

    cout << res;

    return 0;
}
int FindSubArray(const vector<int>& vec, int k)
{
    if (k == 0 || k == 1)
        return 0;

    int l = 0;
    int curProduct = 1; //�洢nums[l]~nums[r]���ۻ�
    int res = 0;

    for (int r = 0; r < vec.size(); r++)
    {
        curProduct *= vec[r];

        while (curProduct >= k)
        {
            curProduct /= vec[l++];
        }

        res += r - l + 1;
    }

    //***ע***
#if 0
    res += r - l + 1; ����ô�����ģ�
        ������n��Ԫ�صļ��ϣ�
        ���� 1 ��Ԫ�ص��Ӽ��� n ��
        ���� 2 ������Ԫ�ص��Ӽ��� n - 1 ��
        ...
        ���� n ������Ԫ�ص��Ӽ��� 1 ��
        �ܹ��� 1 + 2 + 3 + ... + n = ��n + 1�� * n / 2������Ԫ�ص��Ӽ�(��ѧ���ɷ�)

        ��ô����n - 1��Ԫ�صļ��ϣ�����(n) * (n - 1) / 2������Ԫ�ص��Ӽ���

        (n + 1)n / 2 - n(n - 1) / 2 = n / 2 * (2) = n ����n - 1��Ԫ�صļ��ϣ����ӵ�n��Ԫ�أ������ӵ�����Ԫ���Ӽ���Ϊn����

        ����a[l] ... a[r - 1] �ļ��ϣ����ӵ�r��Ԫ��a[r]�������ӵ�����Ԫ���Ӽ���Ϊ a[l] ... a[r] ��Χ�ڵ�Ԫ�������� r - l + 1����
#endif
        return res;
}
#endif
//***ע***
//ʹ�á�˫ָ�롿�������ڡ��������ڡ������������֮�͵���������һ��ǰ����������
//�����е��������ֶ�����������������е��������������������㣬
//��ô˫ָ���˼·�������ã�������Ϊ���������и���ʱ����������
//������ֲ�һ��������������֮�ͣ�����������ɾ������Ҳ
//��һ���ܼ���������֮�͡�


//������10����Ϊk��������
//��Ŀ��û˵�����������������ɵ�
//��һ��˼·��������֮�͡����ۼ�����������������֮�͡�
// ������������ĳ���Ϊn������ĳ
//��������ĵ�1�����ֵ��±���i�����һ�����ֵ��±���j��Ϊ�˼���
//������֮�ͣ���Ҫ����Ԥ��������������±�Ϊ0�����ֿ�ʼ����ÿ
//������Ϊ��β��������֮�͡�Ԥ����ֻ��Ҫ��ͷ��βɨ��һ�Σ�����
//������±�0��ʼ���±�0������������֮��S0�����±�0��ʼ���±�1��
//����������֮��S(1)���Դ����ƣ�ֱ��������±�0��ʼ�����һ������
//��������֮��S(n - 1)����ˣ�
//���±�Ϊi��ʼ���±�Ϊj������������ĺ;���S(j) - S(i - 1)
//�÷���Ҳ��Ϊ��ǰ׺�͡�
#if 1
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int FindSubArray(const vector<int>& vec, int k);

int main()
{
    vector<int> vec = { 1,1,1 };
    int k = 2;

    cout << FindSubArray(vec, k);

    return 0;
}
int FindSubArray(const vector<int>& vec, int k)
{
    int vecLen = vec.size();

    if (vecLen == 0)
        return 0;

    //����ǰ׺������               ***ע***��һ��Ԫ��Ϊ0
    vector<int> PreSumArray(vecLen + 1, 0);

    for (int i = 0; i < vecLen; ++i)
    {
        //PreSumArray���������Ϊvec.size()
        PreSumArray[i + 1] = vec[i] + PreSumArray[i];
    }

    //����
    //��������         [1, 1, 1]
    //PreSumArray=[0, 1, 2, 3]
    //***���***
    //PreSumArray[2] - PreSumArray[0] 
    //����ֵΪ2��ǰ׺�ͼ�ȥ����ֵΪ0��ǰ׺��
    //Ϊ����ֵΪ0������ֵΪ1��������Ԫ��֮��

    //ԭ����ת��Ϊ
    //[i...j-1] ����������Ϊ k ����������ǿ���תΪ 
    // PreSumArray[j] - PreSumArray[i] = k��
    //������ɵ÷����������±� j ��Ҫ���� PreSumArray[i] == PreSumArray[j] - k ��
    //�������ǿ����� j-1 ��β�ĺ�Ϊ k ���������������ʱֻҪͳ��
    //�ж��ٸ�ǰ׺��Ϊ PreSumArray[ j ] - k �� PreSumArray[i] ���ɡ�

    //Ҫ�ҳ����з��������� PreSumArray[i]����Ҫ��������ֵ j-1 ǰ������ i
    //������ʱ�临�Ӷ�

    //��ˣ������ù�ϣ����ǰ׺��PreSumArray[j]Ϊ�����Գ��ִ���Ϊֵ
    //��������          �߸��¹�ϣ���߼���
    //������ֵ j-1 Ϊ��β�� um[ PreSumArray[j]-k ] ��ֵ������O(1)ʱ���ڵõ�
    //�������Ҹ��¹�ϣ��ʱ��i һֱ���� 0 �� j-1 ֮�䣬���Բ�������ظ�

    unordered_map<int, int>um;
    int res = 0;
    for (int j = 0; j <= vecLen; ++j)//***ע***������С�ڵ���
    {
        //���ҵ�ǰ׺��ΪPreSumArray[j] - k��PreSumArray[i]
        //������[ i ... j-1]�ĺ�Ϊk
        if (um.find(PreSumArray[j] - k) != um.end())
        {
            res += um[PreSumArray[j] - k];
        }

        //���²���������������ǰ׺�����ݣ���Щ���ݳ䵱
        //��һ��ѭ��ʱ��PreSumArray[i]
        //����ǰ�������� j ��ǰ׺������������������Ѿ�����
        if (um.find(PreSumArray[j]) != um.end())
            ++um[PreSumArray[j]];
        else//����ǰ�������� j ��ǰ׺����������������в�����
            um[PreSumArray[j]] = 1;
    }

    return res;
}
//�����Ǳ���������
#if 0
int subarraySum(vector<int>& nums, int k)
{
    int count = 0;
    for (int start = 0; start < nums.size(); ++start)
    {
        int sum = 0;
        for (int end = start; end >= 0; --end)
        {
            sum += nums[end];
            if (sum == k)
            {
                count++;
            }
        }
    }
    return count;
}
//���ߣ����۹ٷ����
//���ӣ�https ://leetcode.cn/problems/subarray-sum-equals-k/solutions/238572/he-wei-kde-zi-shu-zu-by-leetcode-solution/
#endif
#endif