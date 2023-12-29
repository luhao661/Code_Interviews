//《剑指Offer 数据结构与算法》


//面试题3：前n个数字二进制形式中1的个数
#if 0
#include <iostream>
#include <vector>
using namespace std;

void CountBits(int num, vector<int>&);

int main()
{
    unsigned int num;
    cin >> num;

    //数字0到数字num
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
        vec[i] = vec[i >> 1] + (i & 1);//***注***小括号必须加
    }

    return;
}
#endif
#endif


//面试题5：单词长度的最大乘积
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

    //创建一个长度为26的数组来模拟哈希表
    int hash[26] = {};

    //某两个单词没有相同的字母
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
//测试：
#if 0
abcw
foo
bar
fxyz
abcdef
#endif
#endif
//***注***
//在判断两个单词的各个字母时，纵使字母的查找时间复杂度降到O(1)
//但比较整个单词的字母还需要线性复杂度
//可以用整数的二进制数位记录字符串中出现的字符，（用二进制数位来模拟哈希表）
//这样判断两个单词是否有相同字母，就可以用flags[i]&flags[j]==0来判断
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

    //某两个单词没有相同的字母
    bool flag = 0;

    int MaxMultiply = 0;

    int TheNumberOfWords = vec_str.size();
    //***注***
    //用shared_ptr管理动态分配的数组的写法
    shared_ptr<int> flags(new int[TheNumberOfWords] {}, default_delete<int[]>());

    for (int i = 0; i < TheNumberOfWords; ++i)
        for (int j = 0; j < vec_str[i].length(); ++j)
            flags.get()[i] |= 1 << (vec_str[i][j] - 'a');//***注*** 用get()方法

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


//面试题6：排序数组中的两个数字之和
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

    vector<int>::const_iterator ptr1, ptr2;//***注***此处不能写成 vector<int>:: iterator
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
    //或者
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
//还可以利用哈希表的查找时间为O(1)
void FindPairOfNumbers(const vector<int>& vec, int k)
{
    if (vec.size() <= 1)
        return;

    unordered_multiset<int> ums(vec.cbegin(), vec.cend());

    vector<int>::const_iterator i;

#if 0
    //错误
    //若输入1 2 4 6 10 则会出现 输出为1 3   2 2   3 1 的情况
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


//面试题7：数组中和为0的3个数字
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
//错误：没考虑去重
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
            continue; //当前数字和前一个数字相等，跳过

        int j = i + 1, k = n - 1;

        while (j < k)
        {
            int sum = nums[j] + nums[k];

            if (sum == -nums[i])
            {
                ans.push_back({ nums[i], nums[j], nums[k] });
                while (j < k && nums[j] == nums[j + 1])
                    j++;//左指针跳过其右侧所有相等的数

                j++;

                while (j < k && nums[k] == nums[k - 1])
                    k--;//右指针跳过其左侧所有相等的数

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


//面试题8：和大于或等于k的最短子数组
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
//滑动窗口
int FindTheShortestSubArray(const vector<int>& vec, int k)
{
    //设置初始最小值
    int MinLen = numeric_limits<int>::max();
    //初始化数组和
    int sum = 0;
    //定义两个变量i、j(类似于滑动窗口的感觉)
    for (int i = 0, j = 0; j < vec.size(); j++)
    {
        //扩大窗口
        sum += vec[j];

        while (i <= j && sum >= k)
        {
            //更新最小值
            MinLen = min(MinLen, j - i + 1);
            //缩小窗口
            sum -= vec[i++];
        }
    }

    //若所有子数组和都小于k,则返回0，否则返回更新值
    return MinLen == numeric_limits<int>::max() ? 0 : MinLen;
}
//***注***
//该解法的时间复杂度仍然是O(n)。这是因为在这两个循环中，
// 变量j和i都是只增加不减少，变量j从0增加到n - 1，变量i从0最多增加到n - 1，
// 因此总的执行次数是O(n)
#endif
#endif


//面试题9：乘积小于k的子数组
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

        //错误写法：
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
    //***注***
    //结果为
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

            //为了得到以ptr2为起点的比要求的子数组长度长1的子数组
            if (MultiplyRes >= k || ptr1 == vec.size() - 1)
            {
                //ptr1回退1步得到以当前ptr2为起点的最长满足要求的子数组
                if (MultiplyRes >= k)
                {
                    MultiplyRes /= vec[ptr1];
                    --ptr1;
                }

                while (MultiplyRes < k)
                {
                    //存【长度逐渐减少到1】的子数组
                    res.emplace_back(vec.begin() + ptr2, vec.begin() + ptr1 + 1);

                    //ptr2 < ptr1则缩小滑动窗口
                    if (ptr2 < ptr1)
                    {
                        MultiplyRes /= vec[ptr2];
                        //将滑动窗口【最左侧的值】存入
                        res.emplace_back(vec.begin() + ptr2, vec.begin() + ptr2 + 1);
                        //ptr2向右推进以缩小窗口
                        ++ptr2;
                    }
                    else//若ptr2 == ptr1
                        break;
                }
                //退出while循环后，MultiplyRes的值为当前滑动窗口最右侧的值
            }
        }
#endif
    return res;
}
#endif
//乘积小于k的子数组(不要求打印所有子数组)
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
    int curProduct = 1; //存储nums[l]~nums[r]的累积
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

    //***注***
#if 0
    res += r - l + 1; 是怎么得来的？
        对于有n个元素的集合：
        包含 1 个元素的子集有 n 个
        包含 2 个连续元素的子集有 n - 1 个
        ...
        包含 n 个连续元素的子集有 1 个
        总共有 1 + 2 + 3 + ... + n = （n + 1） * n / 2个连续元素的子集(数学归纳法)

        那么对于n - 1个元素的集合：共有(n) * (n - 1) / 2个连续元素的子集。

        (n + 1)n / 2 - n(n - 1) / 2 = n / 2 * (2) = n 对于n - 1个元素的集合，增加第n个元素，则增加的连续元素子集数为n个。

        对于a[l] ... a[r - 1] 的集合，增加第r个元素a[r]，则增加的连续元素子集数为 a[l] ... a[r] 范围内的元素总数即 r - l + 1个。
#endif
        return res;
}
#endif
//***注***
//使用【双指针】（类似于【滑动窗口】）解决子数组之和的面试题有一个前提条件——
//数组中的所有数字都是正数。如果数组中的数字有正数、负数和零，
//那么双指针的思路并不适用，这是因为当数组中有负数时在子数组中
//添加数字不一定能增加子数组之和，从子数组中删除数字也
//不一定能减少子数组之和。


//面试题10：和为k的子数组
//题目中没说数组是由正整数构成的
//换一种思路求子数组之和。【累加数组数字求子数组之和】
// 假设整个数组的长度为n，它的某
//个子数组的第1个数字的下标是i，最后一个数字的下标是j。为了计算
//子数组之和，需要先做预处理，计算从数组下标为0的数字开始到以每
//个数字为结尾的子数组之和。预处理只需要从头到尾扫描一次，就能
//求出从下标0开始到下标0结束的子数组之和S0，从下标0开始到下标1结
//束的子数组之和S(1)，以此类推，直到求出从下标0开始到最后一个数字
//的子数组之和S(n - 1)。因此，
//从下标为i开始到下标为j结束的子数组的和就是S(j) - S(i - 1)
//该方法也称为【前缀和】
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

    //创建前缀和数组               ***注***第一个元素为0
    vector<int> PreSumArray(vecLen + 1, 0);

    for (int i = 0; i < vecLen; ++i)
    {
        //PreSumArray的索引最大为vec.size()
        PreSumArray[i + 1] = vec[i] + PreSumArray[i];
    }

    //例：
    //输入数组         [1, 1, 1]
    //PreSumArray=[0, 1, 2, 3]
    //***理解***
    //PreSumArray[2] - PreSumArray[0] 
    //索引值为2的前缀和减去索引值为0的前缀和
    //为索引值为0到索引值为1的子数组元素之和

    //原问题转化为
    //[i...j-1] 这个子数组和为 k 这个条件我们可以转为 
    // PreSumArray[j] - PreSumArray[i] = k，
    //简单移项可得符合条件的下标 j 需要满足 PreSumArray[i] == PreSumArray[j] - k 。
    //所以我们考虑以 j-1 结尾的和为 k 的连续子数组个数时只要统计
    //有多少个前缀和为 PreSumArray[ j ] - k 的 PreSumArray[i] 即可。

    //要找出所有符合条件的 PreSumArray[i]，需要遍历索引值 j-1 前的所有 i
    //会增加时间复杂度

    //因此，可以用哈希表，以前缀和PreSumArray[j]为键，以出现次数为值
    //从左往右          边更新哈希表，边计算
    //以索引值 j-1 为结尾的 um[ PreSumArray[j]-k ] 的值可以在O(1)时间内得到
    //从左往右更新哈希表时，i 一直处于 0 到 j-1 之间，所以不会出现重复

    unordered_map<int, int>um;
    int res = 0;
    for (int j = 0; j <= vecLen; ++j)//***注***这里是小于等于
    {
        //若找到前缀和为PreSumArray[j] - k的PreSumArray[i]
        //即数组[ i ... j-1]的和为k
        if (um.find(PreSumArray[j] - k) != um.end())
        {
            res += um[PreSumArray[j] - k];
        }

        //以下步骤是向容器安插前缀和数据，这些数据充当
        //下一次循环时的PreSumArray[i]
        //若当前遍历到的 j 的前缀和在无序关联容器中已经存在
        if (um.find(PreSumArray[j]) != um.end())
            ++um[PreSumArray[j]];
        else//若当前遍历到的 j 的前缀和在无序关联容器中不存在
            um[PreSumArray[j]] = 1;
    }

    return res;
}
//下面是暴力方法：
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
//作者：力扣官方题解
//链接：https ://leetcode.cn/problems/subarray-sum-equals-k/solutions/238572/he-wei-kde-zi-shu-zu-by-leetcode-solution/
#endif
#endif