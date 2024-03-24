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
//可以用【整数的二进制数位】记录字符串中出现的字符，（用【二进制数位来模拟哈希表】）
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
#if 0
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

    //原问题理解为
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
        //以下步骤是向容器安插前缀和数据，这些数据充当
        //下一次循环时的PreSumArray[i]
        //若当前遍历到的 j 的前缀和在无序关联容器中已经存在
        if (um.find(PreSumArray[j]) != um.end())
            ++um[PreSumArray[j]];
        else//若当前遍历到的 j 的前缀和在无序关联容器中不存在
            um[PreSumArray[j]] = 1;

        //若找到前缀和为PreSumArray[j] - k的PreSumArray[i]
        //即数组[ i ... j-1]的和为k
        if (um.find(PreSumArray[j] - k) != um.end())
        {
            res += um[PreSumArray[j] - k];
        }
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


//面试题11：0和1个数相同的子数组
#if 0
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int FindTheLengthOfCorrespondingSubArray(const vector<int>&vec);

int main()
{
    vector<int> vec1{0,1,0};

    vector<int>vec2{0,0,0,0,1,1,1,0};

    cout << FindTheLengthOfCorrespondingSubArray(vec1)<<endl;
    cout << FindTheLengthOfCorrespondingSubArray(vec2)<<endl;

    return 0;
}
int FindTheLengthOfCorrespondingSubArray(const vector<int>& vec)
{
    int vecLen = vec.size();

    if (vecLen == 0)
        return 0;

    //可以发现如下性质：如果答案非 0，那么子数组长度必然为偶数，且长度至少为 2。
    //具体的，我们在预处理前缀和时，将 nums[i]为 0 的值当做 −1 处理。
    //从而将问题转化为：如何求得最长一段区间和为 0 的子数组。

    //创建前缀和数组               ***注***第一个元素为0
    vector<int> PreSumArray(vecLen + 1, 0);

    for (int i = 0; i < vecLen; ++i)
    {
        //PreSumArray的索引最大为vec.size()
        PreSumArray[i + 1] = (vec[i] == 0 ? -1 : vec[i]) + PreSumArray[i];
    }

    copy(PreSumArray.begin(), PreSumArray.end(), ostream_iterator<int>(cout," "));
    cout << endl;
    //例：
    //输入数组为   0, 1, 0   相当于输入 -1  1  -1
    //前缀和数组为0 -1 0 -1
    //输入数组为   0,  0, 0,  0,  1,  1, 1, 0
    //前缀和数组为0 -1 -2 -3 -4 -3 -2 -1 -2

    unordered_map<int, int>um;

    int MaxLen = 0;

    for (int index = 0; index <= vecLen; ++index)
    {
        //哈希表中没有该键，那么存该键和键对应的值
        //键为前缀和数组的某元素值，值为前缀和数组的某元素值的索引值
        if (um.find(PreSumArray[index]) == um.end())
            um[PreSumArray[index]] = index;
        else
            MaxLen = max(MaxLen,index-um[PreSumArray[index]]);
        //***理解***
        //若index为5，代表【当前】遍历到前缀和数组的索引值为5处
        //PreSumArray[index]表示vec数组从索引0到索引4对应的值之和
        //和为-3，之前遍历时出现过-3，【之前】那次的-3有记录索引值为3
        //那么【之前】的PreSumArray[index]表示vec数组从索引0到索引2
        //对应的值之和为-3
        //因此索引值3、4对应的子数组的0、1个数一定相同
        //长度正好为当前index减去之前的index
    }

    return MaxLen;
}
#endif


//面试题12：左右两边子数组的和相等
#if 0
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int CorrespondingIndex(const vector<int>& vec);

int main()
{
    vector<int> vec1{1,7,3,6,2,9};
    vector<int> vec2{1,7,3,5,2,9};
    vector<int> vec3{1,7,3,5,3,9};

    cout << CorrespondingIndex(vec1)<<endl;
    cout << CorrespondingIndex(vec2)<<endl;
    cout << CorrespondingIndex(vec3)<<endl;

    return 0;
}
int CorrespondingIndex(const vector<int>& vec)
{
    if (vec.size() <= 2)
        return -1;

    //创建前缀和数组
    int vecLen = vec.size();
    vector<int> PreSumArray(vecLen + 1);//默认元素值为0

    for (int i = 0; i < vecLen; ++i)
        PreSumArray[i + 1] = PreSumArray[i] + vec[i];

    int Sum = accumulate(vec.begin(),vec.end(),0);

    //若输入为0  1  0
    //前缀和为0  0  1  1
    
    //遍历的是PreSumArray数组的索引值，对应的是vec数组
    //首元素到索引值index-1对应的元素的值之和
    
    //从vec数组的索引值为1开始做为左右分割点
    //到vec数组的索引值为vecLen-2结束
    //那么就对应
    //PreSumArray数组索引值为2开始
    //到PreSumArray数组的索引值为vecLen-1结束
    for (int index = 2; index <= vecLen-1; ++index)
    {
        //比较的是分割点之前的元素值之和，所以为index-1
        //与分割点之后的元素值之和
        if (PreSumArray[index-1] == Sum - PreSumArray[index-1]-vec[index-1])
            return index-1;
    }

    return -1;
}
//完全可以不使用前缀和数组
#if 0
int sum = 0; 
for (int i = 0; i < nums, length; ++i)
{
    sum += nums[i];
    if (sum - nums[i] == total - sum)
        return i;
}
#endif
#endif


//面试题13：二维子矩阵的数字之和
//思路：
//左上角坐标为（r1，c1）、右下角坐标为（r2，c2）的子矩阵。
//该子矩阵的数字之和等于左上角坐标为（0，0）、右下角坐标为（r2，
//c2）的子矩阵的数字之和减去左上角坐标为（0，0）、右下角坐标为
//（r1 - 1，c2）的子矩阵的数字之和，再减去左上角坐标为（0，0）、右
//下角坐标为（r2，c1 - 1）的子矩阵的数字之和，最后加上左上角坐标为
//（0，0）、右下角坐标为（r1 - 1，c1 - 1）的子矩阵的数字之和
//而这三个子数组的共同点是都从左上角开始计算
//那么若要通过不重复地计算得到这三个子数组的数字之和
//就需要借助【前缀和二维数组】
#if 0
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int SumOfTwoDemensionSubArray(const vector<vector<int>>&vec,
    int subRow1, int subCol1, int subRow2, int subCol2);

int main()
{
    int row, col;
    row = col = 5;
    //vector<vector<int>>vec(row, vector<int>(col));

    vector<vector<int>>vec{
        {3,0,1,4,2},
        {5,6,3,2,1},
        {1,2,0,1,5},
        {4,1,0,1,7},
        {1,0,3,0,5}
    };


    int subRow1, subCol1,subRow2,subCol2;
    subRow1 = 2, subCol1 = 1;
    subRow2 = 4, subCol2 = 3;

    cout << SumOfTwoDemensionSubArray(vec, 
        subRow1, subCol1, subRow2, subCol2);

    return 0;
}
int SumOfTwoDemensionSubArray(const vector<vector<int>>& vec,
    int subRow1, int subCol1, int subRow2, int subCol2)
{
    if (vec.size() == 0 || vec[0].size() == 0)
        return numeric_limits<int>::min();

    int vecRowLen = vec.size();
    int vecColLen = vec[0].size();

    vector<vector<int>>PreSum(vecRowLen + 1, vector<int>(vecColLen+1));

    for(int i=0;i<vecRowLen;++i)
    {
        int rowSum = 0;

        for (int j = 0; j < vecColLen; ++j)
        {
            rowSum += vec[i][j];

            PreSum[i + 1][j + 1] = PreSum[i][j + 1] + rowSum;
            //***理解***
            //某行某列的二维前缀和等于上一行某列的值加上当前行
            //遍历到某列的和
        }
    }

    for (auto x : PreSum)
    {
        for (auto y : x)
            cout << left<<setw(5)<<y;

        cout << endl;
    }

    return PreSum[subRow2+1][subCol2+1]
        -PreSum[subRow1][subCol2+1]-PreSum[subRow2+1][subCol1]
        +PreSum[subRow1][subCol1];
}
#endif


//面试题14：字符串中的变位词（组成各个单词的字母
//及每个字母出现的次数完全相同，只是字母排列的顺序可能不同）
#if 0
#include <iostream>
#include <string>
using namespace std;

bool Judge(shared_ptr<int>& sp);

int main()
{
    string str1("acf");
    string str2("dgcaf");

#if 0
    //维护一个数位形式的哈希表
    int flag = 0;

    //在哈希表中标记变位词的字母
    //for (auto i = str1.begin(); i != str1.end(); ++i)
    //{
    //    //++hash[*i - 'a'];
    //    ++(hash.get()[*i - 'a']);
    //}

    for (auto i = str1.begin(); i != str1.end(); ++i)
    {
        flag |= 1 << (*i - 'a');
    }

    //要实现仅遍历一次str2就能判断str2是否包含str1的某个变位词
    //就需要实现在str2中框出str1长度范围内的子字符串，判断这些子字符串
    //是否满足变位词
    //框出的范围每移动一个单位，就伴随增加一个字符和减少一个字符
    //框出的字符也要体现在哈希表中
    //所以可以用【双指针】来实现
    int left, right;
    left = right = 0;

    //右指针先走
    while (right != str1.size())
    {
        //--hash.get()[str2[right]-'a'];

        flag &= 0 << str2[right] - 'a';
        ++right;
    }

    right = str1.size() - 1;

    //为什么要创建数位形式的哈希表？
    //因为便于用flag值直接判断是否找到了变位词
    while (flag/***注**/ && right != str2.size())
    {                                              //数位形式缺点：
        flag |= 1 << str2[left] - 'a';//某一位没法设置为-1
        flag &= 0 << str2[right] - 'a';

        ++left, ++right;
    }
    //***注***
    //遍历完成后再判断flag也可以
    //那么即使是数组形式的哈希表，若遍历完成后
    //再判断数组中各元素的值，时间复杂度也可以接受

    if (flag)
        cout << false;
    else
        cout<<true;
#endif

    //维护一个哈希表
    shared_ptr<int>hash(new int[26] {}, default_delete<int[]>());

    //在哈希表中标记变位词的字母
	for (auto i = str1.begin(); i != str1.end(); ++i)
	{
		//++hash[*i - 'a'];//没有operator[]方法
		++(hash.get()[*i - 'a']);
	}

    int left, right;
    left = right = 0;

    //右指针先走 str1.size()-1的长度
    while (right != str1.size())
    {
        --hash.get()[str2[right]-'a'];
        ++right;
    }

    right = str1.size() - 1;

    if (Judge(hash))
    {
        cout << "true";
        return 0;
    }

    do
    {                      
        //类似滑动窗口
        //元素加入则对应的hash表位置处的值-1，退出则+1
        ++right;
        --hash.get()[str2[right] - 'a'];

        ++hash.get()[str2[left] - 'a'];
        ++left;

        if(Judge(hash))
        {
            cout << "true";
            return 0;
        }

    } while (right != str2.size()-1);

    cout << "false";

    return 0;
}
bool Judge(shared_ptr<int>& sp)
{
    for (int i = 0; i < 26; ++i)
    {
        if (sp.get()[i] != 0)
            return false;
    }

    return true;
}
#endif


//面试题15：字符串中的所有变位词
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Judge(shared_ptr<int>& sp);
vector<int> res;

int main()
{
    string str1("abc");
    string str2("cbadabacg");

    //维护一个哈希表
    shared_ptr<int>hash(new int[26] {}, default_delete<int[]>());

    //在哈希表中标记变位词的字母
    for (auto i = str1.begin(); i != str1.end(); ++i)
    {
        //++hash[*i - 'a'];//没有operator[]方法
        ++(hash.get()[*i - 'a']);
    }

    int left, right;
    left = right = 0;

    //右指针先走 str1.size()-1的长度
    while (right != str1.size())
    {
        --hash.get()[str2[right] - 'a'];
        ++right;
    }

    right = str1.size() - 1;

    if (Judge(hash))
    {
        res.push_back(0);
    }

    do
    {
        //类似滑动窗口
        //元素加入则对应的hash表位置处的值-1，退出则+1
        ++right;
        --hash.get()[str2[right] - 'a'];

        ++hash.get()[str2[left] - 'a'];
        ++left;

        if (Judge(hash))
        {
            res.push_back(left);
        }

    } while (right != str2.size() - 1);

    for (auto x : res)
        cout << x << endl;

    return 0;
}
bool Judge(shared_ptr<int>& sp)//若含有其他字符则可以考虑使用unordered_map
{
    for (int i = 0; i < 26; ++i)
    {
        if (sp.get()[i] != 0)
            return false;
    }

    return true;
}
#endif


//面试题16：不含重复字符的最长子字符串
//（对照//面试题48：最长不含重复字符的子字符串）
//此处用双指针来解
#if 0
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

int LongestSubString(const string& str);
bool Judge(const unordered_map<char, int>& hash);

int main()
{
    string str1{"babcca"};
    string str2{"ccccccccccca"};
    string str3{"ccccccabbccccc"};

    cout << LongestSubString(str1)<<endl;
    cout << LongestSubString(str2)<<endl;
    cout << LongestSubString(str3)<<endl;

    return 0;
}
#if 0
int LongestSubString(const string& str)
{
    if (str.empty())
        return 0;

    unordered_map<char, int> hash;

    int left, right;
    left = right = 0;

    int MaxLen = 0;

    for (  ; right < str.size(); ++right)
    {
        if (hash.find(str[right]) == hash.end())
            hash[str[right]] = 1;
        else
            ++hash[str[right]];

        if (Judge(hash))
            MaxLen = max(MaxLen,right-left+1);
        else
        {
            --hash[str[left]];
            ++left;
        }//找到 不含重复字符的最长子字符串的 长度之后，窗口长度不会再变小，只可能变大
    }

    return MaxLen;
}
#endif

#if 1
int LongestSubString(const string& str)
{
    if (str.empty())
        return 0;

    int cnt[256] = {};

    int left, right;
    left = right = 1;
    int MaxLen = 0;

    auto fun = [](int* pcnt) {
        for (int index = 0; index < 256; ++index)
        {
            if (pcnt[index] > 1)
                return true;
        }

        return false;
        };

//此方法还是要多次重复扫描数组cnt
#if 0
    for (; right < str.size(); ++right)
    {
        ++cnt[str[right] - 'a'];

        while (fun(cnt))
        {
            --cnt[str[left]-'a'];
            ++left;
        }

        MaxLen = max(MaxLen,right-left+1);
    }
#endif
    
#if 1
    int duplication = 0;

    for (; right < str.size(); ++right)
    {
        ++cnt[str[right] - 'a'];

        if (cnt[str[right] - 'a'] == 2)
            ++duplication;

        while (duplication>0)
        {
            --cnt[str[left] - 'a'];

            if (cnt[str[left] - 'a'] == 1)
                duplication--;

            ++left;
        }

        MaxLen = max(MaxLen, right - left + 1);
    }
#endif

    return MaxLen;
}
#endif

bool Judge(const unordered_map<char, int>& hash)
{
    for (auto x : hash)
    {
        if (x.second > 1)
            return false;
    }

    return true;
}
#endif


//面试题17：包含所有字符的最短字符串
//***注***
//要和变位词做区分
#if 0
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

string FindShortestSubString(const string& source,const string& target);

int main()
{
    string s("ADDBANCADAAAAAABC");
    string t("ABC");

    cout << FindShortestSubString(s,t);

    return 0;
}

bool Judge(unordered_map<char, int> unmap)
{
    for (auto x : unmap)
        if (x.second >= 1)
            return false;

    return true;
}

//首先扫描字符串t，每扫描到一个字符，就把该字符
//在哈希表中对应的值加1。然后扫描字符串s，每扫描一个字符，
//就检查哈希表中是否包含该字符。如果哈希表中没有该字符，则说明
//该字符不是字符串t中的字符，可以忽略不计。如果哈希表中存在该字符，
//则把该字符在哈希表中的对应值减1。如果字符串s中包含字符串t的
//所有字符，那么哈希表中最终所有的值都应该小于或等于0。
string FindShortestSubString(const string& source, const string& target)
{
    if (source.empty() || target.empty())
        return "";

    //用哈希表统计每个字符出现的次数，配合双指针
    //避免暴力枚举s中的子字符串

    unordered_map<char, int> unmap;

    for (int i = 0; i < target.size(); ++i)
        unmap[target[i]]=1;

    int left, right /*ShortestLen=numeric_limits<int>::max()*/;
    left = right = 0;

    string ShortestStr(source.size()+1,' ');

    for (; right < source.size(); ++right)
    {
        if (unmap.find(source[right]) != unmap.end())
        {
            --unmap[source[right]];

            while (Judge(unmap))
            {
                if (ShortestStr.size() > right - left + 1)
                {
                    ShortestStr.clear();
                    ShortestStr.append(source.begin()+left, source.begin()+right+1);
                }

                if (unmap.find(source[left]) != unmap.end())
                    ++unmap[source[left]];

                ++left;
            }
        }
    }

    return ShortestStr.size()== source.size() + 1?"": ShortestStr;
}
#endif


//面试题18：有效的回文
//双指针思想
#if 0
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool JudgePalindrome(const string& str);

int main()
{
    string str1("Was it a cat I saw?");
    string str2("Was it a cau I saw?");
    string str3("??????????????????");

    //cout << JudgePalindrome(str1)<<endl;
    //cout << JudgePalindrome(str2) << endl;
    cout << JudgePalindrome(str3)<<endl;

    return 0;
}
bool JudgePalindrome(const string& str)
{
    if (str.empty())
        return false;

    string StrBackup = str;

    //***注***
    //错误写法：
#if 0
    for (int i = 0; i < StrBackup.size(); ++i)
    {
        if (isalpha(StrBackup[i]) || isdigit(StrBackup[i]))
            continue;
        else
            StrBackup.erase(i,1);
    }
#endif
    //错误原因：
    //若是要进行erase()操作，那么StrBackup.size()的值会改变，
    //导致遍历不到字符串末尾

    //正确写法：
    for (auto it = StrBackup.begin(); it != StrBackup.end(); )
    {
        if (isalpha(*it) || isdigit(*it))
            ++it;
        else
            //StrBackup.erase(distance(StrBackup.begin(),it),1);
            it=StrBackup.erase(it,it+1);
    }

    //copy(StrBackup.begin(), StrBackup.end(), ostream_iterator<char>(cout));
    //cout << endl;

    transform(StrBackup.begin(),StrBackup.end(),StrBackup.begin(),
        [](char ch)
        {
            if (isalpha(ch) && isupper(ch))
                return (char)tolower(ch);
            else
                return ch;
        });

    //copy(StrBackup.begin(),StrBackup.end(),ostream_iterator<char>(cout));

    if (StrBackup =="")
        return false;

    int left , right;
    left = 0; right = StrBackup.size() - 1;

    while (left < right)
    {
        if (StrBackup[left] == StrBackup[right])
        {
            ++left, --right;
        }
        else
            return false;
    }

    return true;
}
#endif


//面试题19：最多删除一个字符得到回文
#if 0
#include <iostream>
#include <string>

using namespace std;

bool MaybeDeleteOneChar(const string& str);

int main()
{
    string str1("abc");
    string str2("abca");
    string str3("accb");
    string str4("abcbbcbba");
    string str5("abbcbbcba");

    cout<<MaybeDeleteOneChar(str1) << endl;
    cout<<MaybeDeleteOneChar(str2) << endl;
    cout<<MaybeDeleteOneChar(str3) << endl;
    cout<<MaybeDeleteOneChar(str4) << endl;
    cout<<MaybeDeleteOneChar(str5) << endl;

    return 0;
}
#if 0
bool MaybeDeleteOneChar(const string& str)
{
    if (str.empty())
        return false;

    string strBackup(str);

    int left, right;
    left = 0; right = strBackup.size()-1;

    bool onlyOnce = true;

    while (left < right)
    {
        if (strBackup[left] == strBackup[right])
        {
            ++left, --right;
            continue;
        }
        else if (onlyOnce && strBackup[left + 1] == strBackup[right])
        {
            ++left;
            onlyOnce = false;
        }
        else if (onlyOnce && strBackup[right - 1] == strBackup[left])
        {
            --right;
            onlyOnce = false;
        }
        else
            return false;
    }
    //***注***
    //str4进行测试时输出错误，原因是
    //两个else if 语句块的先后次序其实并不一定，要看字符串的情况才能确定
    //哪个块在前，哪个块在后
    //这样就需要改变编程形式

    return true;
}
#endif

#if 1
bool tryFun1(string& strBackup)
{
    int left, right;
    left = 0; right = strBackup.size() - 1;

    bool onlyOnce = true;

    while (left < right)
    {
        if (strBackup[left] == strBackup[right])
        {
            ++left, --right;
            continue;
        }
        else if (onlyOnce && strBackup[left + 1] == strBackup[right])
        {
            ++left;
            onlyOnce = false;
        }
        else
            return false;
    }
    return true;

}
bool tryFun2(string& strBackup)
{
    int left, right;
    left = 0; right = strBackup.size() - 1;

    bool onlyOnce = true;

    while (left < right)
    {
        if (strBackup[left] == strBackup[right])
        {
            ++left, --right;
            continue;
        }
        else if (onlyOnce && strBackup[right - 1] == strBackup[left])
        {
            --right;
            onlyOnce = false;
        }
        else
            return false;
    }
    return true;
}

bool MaybeDeleteOneChar(const string& str)
{
    if (str.empty())
        return false;

    string strBackup(str);

    return tryFun1(strBackup) || tryFun2(strBackup);
}
#endif
#endif


//面试题20：回文字符串的个数
//解法：
//双指针+中心扩展法
//枚举每一个可能的回文中心，然后用两个指针分别向左右两边拓展，
//当两个指针指向的元素相同的时候就拓展，否则停止拓展
#if 0
#include <iostream>
#include <string>

using namespace std;

int PalindromeCnt(const string& str);

int main()
{
    string str1("abc");
    string str2("abcba");
    string str3("abccba");
    string str4("aaa");

    cout << PalindromeCnt(str1) << endl;
    cout << PalindromeCnt(str2) << endl;
    cout << PalindromeCnt(str3) << endl;
    cout << PalindromeCnt(str4) << endl;

    return 0;
}
int PalindromeCnt(const string& str)
{
    if (str.empty())
        return 0;

    //保底有str长度个的回文字符串
    int n = str.length();

    int ans = n;

    for (int k = 0; k < n; k++) 
    {
		// 以str[k]为中心向两边扩
        int i = k - 1, j = k + 1;
        while (i >= 0 && j < n && str[i--] == str[j++])
        {
            ans++;
        }

        //***注***
        // 以str[k]右侧的空白位置(这是个假想位置)为中心向两边扩
        i = k;
        j = k + 1;
        while (i >= 0 && j < n && str[i--] == str[j++]) 
        {
            ans++;
        }
    }

    return ans;
}
#endif


//面试题21：删除倒数第k个节点
#if 1
//见//面试题22：链表中倒数第k个节点
#endif


//面试题22：链表中环的入口节点
#if 1
//见//面试题23：链表中环的入口节点
#endif


//面试题23：两个链表的第1个重合节点
#if 1
//见//面试题52：两个链表的第一个公共节点
#endif


