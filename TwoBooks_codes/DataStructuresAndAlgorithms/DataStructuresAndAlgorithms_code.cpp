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
//经验：
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
//经验：
//使用【双指针】（类似于【滑动窗口】）解决子数组之和的面试题有一个前提条件——
//数组中的所有数字都是正数。如果数组中的数字有正数、负数和零，
//那么双指针的思路并不适用，这是因为当数组中有负数时在子数组中
//添加数字不一定能增加子数组之和，从子数组中删除数字也
//不一定能减少子数组之和。


//经验：
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
//面试题10：和为k的子数组
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

    unordered_map<int, int>PreSum_Index_Pair;

    int MaxLen = 0;

    for (int index = 0; index <= vecLen; ++index)
    {
        //哈希表中没有该键，那么存该键和键对应的值
        //键为前缀和数组的某元素值，值为前缀和数组的某元素值的索引值
        if (PreSum_Index_Pair.find(PreSumArray[index]) == PreSum_Index_Pair.end())
            PreSum_Index_Pair[PreSumArray[index]] = index;
        else
            MaxLen = max(MaxLen,index- PreSum_Index_Pair[PreSumArray[index]]);
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

    //经验：
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
//经验：
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


//面试题24：反转链表
#if 1
//见//面试题24：反转链表
#endif


//面试题25：链表中的数字相加
#if 0
#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int m_nValue;
    ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pHead);
ListNode* ListNumber(ListNode* pHead1, ListNode* pHead2);
vector<ListNode*>vec_pListNode;

int main()
{
    ListNode* a1 = new ListNode;
    a1->m_nValue = 9;

    ListNode* a2 = new ListNode;
    a2->m_nValue = 9;

    ListNode* a3 = new ListNode;
    a3->m_nValue = 9;

    a1->m_pNext = a2;
    a2->m_pNext = a3;
    a3->m_pNext = nullptr;

    cout << a1->m_nValue << " " << a1->m_pNext->m_nValue
        << " " << a1->m_pNext->m_pNext->m_nValue << endl;

    ListNode* b1 = new ListNode;
    b1->m_nValue = 1;

    ListNode* b2 = new ListNode;
    b2->m_nValue = 0;

    //ListNode* b3 = new ListNode;
    //b3->m_nValue = 9;

    b1->m_pNext = b2;
    //b2->m_pNext = b3;

    //b3->m_pNext = nullptr;
    b2->m_pNext = nullptr;

    //cout << b1->m_nValue << " " << b1->m_pNext->m_nValue
    //    << " " << b1->m_pNext->m_pNext->m_nValue << endl;
    //错误思路：
    //根据两个链表求出两个整数，然后进行相加，最后结果由链表表示
    //没有考虑大数问题

    //正确思路：
    //将整数链表反转，然后原链表的头可以作为尾，存的是数字最高位
    //原链表的尾可以作为头，存的是数字最低位，
    //从最低位开始相加，处理到最高位结束
	ListNode* res = ListNumber(a1, b1);

    while (res)
    {
        cout << res->m_nValue;

        if (res->m_pNext)
        {
            cout << "->";
            res = res->m_pNext;
        }
        else
            break;
    }

    return 0;
}

ListNode* ListNumber(ListNode* pHead1, ListNode* pHead2)
{
    if (pHead1 == nullptr || pHead2 == nullptr)
        return nullptr;

    ListNode* rList1 = ReverseList(pHead1);
    ListNode* rList2 = ReverseList(pHead2);

    //创建链表
    //ListNode* res = new ListNode{0,nullptr};

    //vector<ListNode*>vec_pListNode;

    //存进位值
    int nTake = 0;

    while (rList1 != nullptr || rList2 != nullptr)
    {
        int tmpSum;

        //要考虑到两个数字位数不同的情况
        if(rList1 != nullptr && rList2 != nullptr)
            tmpSum = rList1->m_nValue + rList2->m_nValue + nTake;
        else if(rList1)
            tmpSum = rList1->m_nValue + nTake;
        else
            tmpSum = rList2->m_nValue + nTake;

        if (tmpSum > 9)
        {
            tmpSum -= 10;
            nTake = 1;
        }
        else
            nTake = 0;

        vec_pListNode.push_back(new ListNode{tmpSum,nullptr});

        if(rList1)
            rList1 = rList1->m_pNext;
        if(rList2)
            rList2 = rList2->m_pNext;
    }

    //考虑到最高位是进位的数字的情况
    if(nTake)
        vec_pListNode.push_back(new ListNode{ 1,nullptr });

    //倒着存运算的值，正着串链表
    for (auto it = vec_pListNode.rbegin(); it != vec_pListNode.rend() - 1; ++it)
        (*it)->m_pNext = *(next(it));

    return *(vec_pListNode.rbegin());
}

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

    return pReversedHead;
}
#endif


//面试题26：重排链表
#if 0
#include <iostream>
#include "List.h"
using namespace std;

ListNode* Rearrangement(ListNode* pNode);
ListNode* ReverseList(ListNode* pHead);
ListNode* MergeTwoLists(ListNode* p1, ListNode* p2);

int main()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);
    //ListNode* pNode6 = CreateListNode(6);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
   // ConnectListNodes(pNode5, pNode6);

    PrintList(pNode1);

    PrintList(Rearrangement(pNode1));

    return 0;
}
ListNode* Rearrangement(ListNode* pNode)
{
    if (pNode == nullptr)
        return nullptr;

    //将原链表分成两段
    //长度为偶数，分得前半段和后半段长度一样   (情况1)
    //长度为奇数，分得前半段比后半段长度多1     (情况2)
    ListNode* pFast, *pSlow;

    for (pFast = pSlow = pNode; pFast != nullptr; )
    {
        pFast = pFast->m_pNext;

        if (pFast != nullptr)
        {
            pFast = pFast->m_pNext;

            if (pFast == nullptr)
                break;

            pSlow = pSlow->m_pNext;
        }
        else
            break;
    }

    ListNode L1{0};//哨兵
    ListNode* pL1 = &L1;
    ListNode* traverse = pNode;
    do
    {
        pL1->m_pNext = new ListNode{traverse->m_nValue,traverse->m_pNext};
        pL1 = pL1->m_pNext;

        traverse = traverse->m_pNext;

    } while (traverse != pSlow->m_pNext);

    //前半段尾部节点的m_pNext成员设为nullptr，截取前半段
    pL1->m_pNext = nullptr;


    //截取后半段
    ListNode L2{ 0 };//哨兵
    ListNode* pL2 = &L2;
    do
    {
        pL2->m_pNext = new ListNode{ traverse->m_nValue,traverse->m_pNext };
        pL2 = pL2->m_pNext;

        traverse = traverse->m_pNext;

    } while (traverse != nullptr);

    //PrintList(L2.m_pNext);

    //后半段链表反转
    ListNode* prL2 = ReverseList(L2.m_pNext);

    //合并两个链表
    return MergeTwoLists(L1.m_pNext,prL2);
}

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

    return pReversedHead;
}

ListNode* MergeTwoLists(ListNode* p1, ListNode* p2)
{
    PrintList(p1);
    PrintList(p2);

    //哨兵
    ListNode resGuard{0};   
    ListNode* pGuard = &resGuard;

    //错误写法：
    //原因：
    //pGuard->m_pNext = p1;
    //pGuard->m_pNext->m_pNext = p2;
    //相当于与语句：p1->m_pNext = p2;
    //后面会把p1 = p1->m_pNext; 相当于p1存的地址和p2一样了
    //所以不能在两个原链表上进行操作
#if 0
	while (1)
	{
		pGuard->m_pNext = p1;

        if (p2 != nullptr)
        {
            pGuard->m_pNext->m_pNext = p2;
            pGuard = p2;
        }
        else//仅p2为nullptr   那就是(情况2)
        {
            pGuard = p1;
            pGuard->m_pNext = nullptr;
            break;
        }

		p1 = p1->m_pNext;
		p2 = p2->m_pNext;

        //p1、p2都为nullptr    (情况1)
        if (p1 == nullptr && p2 == nullptr)
            break;
	}
#endif
    //修改：
    //可以创建变量暂存p1->m_pNext的值
    //后再赋给p1

    //或者改为：
    while (1)
    {
        pGuard->m_pNext = new ListNode{ p1->m_nValue,nullptr };

        if (p2 != nullptr)
        {
            pGuard->m_pNext->m_pNext = new ListNode{ p2->m_nValue,nullptr };
            pGuard = pGuard->m_pNext->m_pNext;
        }
        else//仅p2为nullptr   那就是(情况2)
        {
            pGuard = pGuard->m_pNext;
            pGuard->m_pNext = nullptr;
            break;
        }

        p1 = p1->m_pNext;
        p2 = p2->m_pNext;

        //p1、p2都为nullptr    (情况1)
        if (p1 == nullptr && p2 == nullptr)
            break;
    }

    return resGuard.m_pNext;
}
#endif


//面试题27：回文链表
//要求时间复杂度O(1), 空间复杂度O(1)
//***注***
//与字符串的回文判断方法做区分，字符串判断回文只需双指针
#if 0
#include<iostream>
#include "List.h"

using namespace std;

bool JudgePalindrome(ListNode* pNode);
ListNode* ReverseList(ListNode* pHead);

int main()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(3);
    ListNode* pNode5 = CreateListNode(2);
    ListNode* pNode6 = CreateListNode(1);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode6);

    PrintList(pNode1);

    cout<<JudgePalindrome(pNode1)<<endl;

    ListNode* b1 = CreateListNode(1);
    ListNode* b2 = CreateListNode(2);
    ListNode* b3 = CreateListNode(3);
    ListNode* b4 = CreateListNode(2);
    ListNode* b5 = CreateListNode(1);

    ConnectListNodes(b1, b2);
    ConnectListNodes(b2, b3);
    ConnectListNodes(b3, b4);
    ConnectListNodes(b4, b5);

    PrintList(b1);

    cout << JudgePalindrome(b1)<<endl;

    return 0;
}
bool JudgePalindrome(ListNode* pNode)
{
    if (pNode == nullptr)
        return false;

    //将原链表分成两段
    //长度为偶数，分得前半段和后半段长度一样   (情况1)
    //长度为奇数，分得前半段比后半段长度多1     (情况2)
    ListNode* pFast, * pSlow;
    int Len = 1;

    for (pFast = pSlow = pNode; pFast != nullptr; )
    {
        pFast = pFast->m_pNext;

        if (pFast != nullptr)
        {
            ++Len;

            pFast = pFast->m_pNext;

            if (pFast == nullptr)
                break;

            ++Len;

            pSlow = pSlow->m_pNext;
        }
        else
            break;
    }

    ListNode* rpNode = nullptr;

    //若长度为奇数，那就比较奇数长度的两段，中间的节点被两段公用
    if (Len % 2)
    {
        rpNode = ReverseList(pSlow);//***注***ReverseList()后 pSlow->m_pNext=nullptr
    }
    else//若长度为偶数，那就比较偶数长度的两段
    {
        rpNode = ReverseList(pSlow->m_pNext);
        //***注***
        pSlow->m_pNext = nullptr;
    }

    do
    {
        if (pNode->m_nValue == rpNode->m_nValue)
        {
            pNode = pNode->m_pNext;
            rpNode = rpNode->m_pNext;
        }
        else
            return false;

    } while (pNode != nullptr);

    return true;
}
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

    return pReversedHead;
}
#endif


//面试题28：展平多级双向链表
//回溯法:遇到有子节点的就暂存到栈里,等遍历完子节点在从栈中取出回溯
#if 0
#include <iostream>
#include <stack>
using namespace std;

class Node 
{
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

int main()
{


    return 0;
}

Node* flatten(Node* head)
{
    Node* pnode = head;
    Node* prev = nullptr;
    stack<Node*> stk;

    while (pnode != nullptr || !stk.empty()) 
    {
        if (pnode == nullptr)
        {
            pnode = stk.top(),stk.pop();
            pnode->prev= prev;
            prev->next = pnode;
        }

        if (pnode->child != nullptr)
        {
            //遇到有子节点的就暂存到栈里,等遍历完子节点，
            // 再从栈中取出回溯
            if (pnode->next != nullptr)
                stk.push(pnode->next);
                
            pnode->child->prev = pnode;
            pnode->next = pnode->child;
            pnode->child = nullptr;
        }

        prev = pnode;
        pnode = pnode->next;
    }

    return head;
}
}
#endif


//面试题29：排序的循环链表
#if 0
#include <iostream>
#include "list.h"

ListNode* insertNode(ListNode* pHead,int insertValue);
void insertNodeCore(ListNode* pHead, int Value);

using namespace std;

int main()
{
    ListNode Guide{0,nullptr};
    ListNode* pGuide = &Guide;

    for (int i = 1; i <= 7; ++i)
    {
        //错误写法：
        //insertNode(pGuide->m_pNext, i);
        //***注***
        //每一次的循环结束pGuide->m_pNext的值都是nullptr
        //理解：
        //正常情况下是传某个节点的地址给形参pHead
        //然后insertNode()函数内对pHead的值进行修改
        //是不可以影响pGuide->m_pNext的值的
        //因为pHead是和pGuide->m_pNext一样都指向同一个节点的
        //insertNode()函数内对pHead的值进行修改
        //相当于pHead指针指向了别的节点  
        //不影响pGuide->m_pNext，pGuide->m_pNext会仍存nullptr
        //现在传nullptr给形参pHead的情况也可以按照上述来理解

        //当然也可以理解为函数的形参的值是个原来值的副本来理解。


        //可以修改为
        pGuide->m_pNext = insertNode(pGuide->m_pNext, i);
        //或者函数改为
        // ListNode* insertNode(ListNode* &pHead, int insertValue)
        //这样就直接操作的是pGuide->m_pNext指针了
        //然后在此处写：insertNode(pGuide->m_pNext, i);
    }

    ListNode* pNode = Guide.m_pNext;
    int cnt = 1;
    while (1)
    {
        printf("%d\t", pNode->m_nValue);
        pNode = pNode->m_pNext;

        if (cnt == 7)
            break;

        ++cnt;
    }

    return 0;
}
ListNode* insertNode(ListNode* pHead, int insertValue)
{
    //若循环链表中本来没有节点
    if (pHead == nullptr)
    {
        pHead = new ListNode;
        pHead->m_nValue = insertValue;
        pHead->m_pNext = pHead;
    }
    else if (pHead->m_pNext == pHead)
    {
        /*if (pHead->m_nValue < insertValue)
        {
            pHead->m_pNext = new ListNode{insertValue,pHead};
        }
        else
        {

        }*/
        pHead->m_pNext = new ListNode{ insertValue,pHead };
    }
    else
        insertNodeCore(pHead, insertValue);

    return pHead;
}
void insertNodeCore(ListNode* pHead, int Val)
{
    ListNode* pNode, * pNext;

    pNode = pHead;
    pNext = pHead->m_pNext;

    while (1)
    {
        if (pNode->m_nValue<Val && pNext->m_nValue>Val)
        {
            pNode->m_pNext = new ListNode{ Val,pNext };
            break;
        }
        else if (pNode->m_nValue<Val && pNext->m_nValue<Val)
        {
            if(pNext->m_nValue < pNode->m_nValue) 
            {
                pNode->m_pNext = new ListNode{ Val,pNext };
                break;
            }
        }
        else if (pNode->m_nValue > Val && pNext->m_nValue > Val)
        {
            if (pNext->m_nValue < pNode->m_nValue)
            {
                pNode->m_pNext = new ListNode{ Val,pNext };
                break;
            }
        }

		pNode = pNext;
        pNext = pNext->m_pNext;
    }
}
#endif


//面试题30：插入、删除和随机访问都是O(1)的容器
//思路：就是实现一个自定义的哈希表
//插入、删除前需要在O(1)时间内查找到该元素 -> 无序关联容器
//随机访问性能为O(1)  -> vector容器

//哈希表key存放元素值 ， value存放元素值在数组中的下标
//等概率的返回某个元素→vector容器
//随机生成数组下标范围内一个随机下标值，返回该数组内的数值即可
#if 0
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet 
{
private:
    //哈希表key存放值，value存放下标
    unordered_map<int, int>IndexOfNum;
    //数组
    vector<int>nums;
public:
    /** Initialize your data structure here. */
    RandomizedSet() 
    {}

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        //如果在哈希表中存在该元素，返回false
        if (IndexOfNum.find(val) != IndexOfNum.end())
        {
            return false;
        }

        //将该数值添加到数组尾部并将该数值和下标映射存入哈希表

        //哈希表中加入pair数据，内容为加入的值和该值对应的下标，
        // 因为数组中插入是在最后一个下标的下一个下标，
        // 所以对应的下标为nums.size()
        IndexOfNum[val] = nums.size();

        //数组末尾加val
        nums.push_back(val);

        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) 
    {
        //如果哈希表中不存在该元素，则返回false
        if (IndexOfNum.find(val) == IndexOfNum.end())
        {
            return false;
        }

        //如果在数组中直接删除，为了保证数组内存连续性
        // 需要将该数值后面的数组均前移一位，
        // 时间复杂度为O(n)，不符题意。

        //数组删除时的处理方法：
        //用数组的最后一个数值去填充将删除的数值的内存，
        // 并更新哈希表中的下标，其他数值在位置保持不变，
        // 删除数组最后一个数值，时间复杂度为O(1)

        //在哈希表中根据待删除元素找到待删除元素在数组中的下标
        int index = IndexOfNum[val];

        //在哈希表中修改记录
        //把数组中最后一个元素的下标记录为index
        IndexOfNum[nums.back()] = index;
        //在哈希表中删除val
        IndexOfNum.erase(val);

        //在数组中待删除元素用数组中最后一个元素替换
        nums[index] = nums.back();
        //删除最后一个元素
        nums.pop_back();

        return true;
    }

    /** Get a random element from the set. */
    int getRandom() 
    {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main()
{
    RandomizedSet RS;

    RS.insert(0);

    for (int i = 1; i <= 9; ++i)
        RS.insert(i);

    for (int i = 1; i <= 9; ++i)
        cout << RS.getRandom()<<' ';
    cout << endl;

    RS.remove(8);

    for (int i = 1; i <= 9; ++i)
        cout << RS.getRandom() << ' ';

    return 0;
}
#endif


//面试题31：最近最少使用缓存 (Least Recently Used, LRU)
//要求如下两个操作的时间复杂度都是O(1)：
// get（key）：如果缓存中存在键key，则返回它对应的值；否则返回 - 1。
// put（key，value）：如果缓存中之前包含键key，则它的值设为value；
// 否则添加键key及对应的值value。在添加一个键时，如果缓存容量已经满了，
// 则在添加新键之前删除最近最少使用的键（缓存中最长时间没有被使用过的元素）。

//分析：
//需要能随机访问
//需要把该数据插入到头部或者尾部

//哈希表能在O(1)内找到键，如果键和值的pair存了键在链表中的位置的值，
//那么就可以在O(1)时间内访问链表
//由于链表记录了数据输入的时间顺序，链表中的元素必须储存键，这样才能通过键
//找到哈希表项目，实现删除要求
#if 0
#include <unordered_map>

using namespace std;

struct DLinkedNode
{
    int m_key;
    int m_value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : m_key(0), m_value(0), prev(nullptr), next(nullptr) 
    {}
    DLinkedNode(int key, int value) : m_key(key), m_value(value), prev(nullptr), next(nullptr)
    {}
};

class LRUCache 
{
private:
    unordered_map<int, DLinkedNode*> m_key2Node;
    int m_capacity;
    DLinkedNode* head;
    DLinkedNode* tail;

public:
    LRUCache(int capacity)
    {
        // 初始化的时候, 让系统分配头尾两个节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
        // 控制缓存的容量
        m_capacity = capacity;
    }

    int get(int key)
    {
        // 如果容器里有这个key，就直接返回，并把这个移动到链表的头部
        if (m_key2Node.find(key) != m_key2Node.end()) 
        {
            removeNode(m_key2Node[key]);
            addNode2Head(m_key2Node[key]);
            return m_key2Node[key]->m_value;
        }
        else 
        { 
            // 如果没有这个节点，就返回-1
            return -1;
        }
    }

    void put(int key, int value) 
    {
        // 如果有这个节点，就覆盖这个key对应的值，并把这个节点放在链表的头部
        if (m_key2Node.find(key) != m_key2Node.end())
        {
            m_key2Node[key]->m_value = value;
            removeNode(m_key2Node[key]);
            addNode2Head(m_key2Node[key]);
        }
        else
        { 
            // 如果没有这个节点，就添加这个节点，并把这个节点放在链表头部，
            // 如果节点数量超过容器大小，就删除尾部节点的元素
            DLinkedNode* node = new DLinkedNode(key, value);
            m_key2Node[key] = node;
            addNode2Head(node);
            while (m_key2Node.size() > m_capacity) 
            {
                removeTail();
            }
        }
    }

    // 移动一个节点到链表的头部，是要先删除节点，再在链表的头部添加这个节点
    // 删除一个节点的函数
    void removeNode(DLinkedNode* node) 
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 添加一个节点到链表的头部的函数
    void addNode2Head(DLinkedNode* node)
    {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

    // 从尾部移除一个节点的函数
    void removeTail()
    {
        m_key2Node.erase(tail->prev->m_key);

        DLinkedNode* node = tail->prev;

        tail->prev->prev->next = tail;
        tail->prev = tail->prev->prev;

        // 防止内存泄漏
        delete node;
    }
    //使用双向链表而不是单向链表的原因是：
    // 在缓存满了需要删除的时候，双向链表可以通过tail快速找到最后一个节点。
    // 如果使用单向链表想要找到最后一个节点，需要从头节点遍历过去
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
#endif


 //面试题32：有效的变位词
#if 0
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool WhetherAAnagram(const string &s,const string &t);

int main()
{
    string s("anagram");
    string t("nagaram");

    cout << WhetherAAnagram(s,t);

    return 0;
}
bool WhetherAAnagram(const string& s, const string& t)
{
    if (s.empty() || t.empty())
        return false;

    shared_ptr<int> hash(new int[26] {},default_delete<int[]>());

    if (s.size() != t.size())
        return false;

    for (int i = 0; i < s.size(); ++i)
        hash.get()[s[i] - 'a']++;

    for (int i = 0; i < t.size(); ++i)
        hash.get()[s[i] - 'a']--;

    if (all_of(hash.get(), hash.get() + 26, [](int num) {return num == 0; }))
        return true;

    return false;
}
#endif


//面试题33：变位词组
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

map<string,vector<string>> Classification(const string& str);

int main()
{
    string inputStr ("eat tea tan ate nat bat");

    Classification(inputStr);

    return 0;
}
map<string, vector<string>> Classification(const string& str)
{
    if (str.empty())
        exit(-1);

    map<string, vector<string>> str_vector_pairs;

    istringstream is(str);

    string word;

    is >> word;
    while (is)
    {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());

        if (str_vector_pairs.find(sortedWord) == str_vector_pairs.end())
        {
            vector<string> tmp;
            tmp.push_back(word);
            str_vector_pairs[sortedWord] = move(tmp);
        }
        else
        {
            str_vector_pairs[sortedWord].push_back(word);
        }

        is >> word;
    }

    for (auto Pair : str_vector_pairs)
    {
        for (auto elem : Pair.second)
            cout << elem << ' ';

        cout << endl;
    }

    //法二：
    //is_permutation()

    return str_vector_pairs;
}
#endif


//面试题34：外星语言是否排序
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool WhetherIsOrderedCore(
    const string& s1, const string& s2,
    const vector<int>& order_hash);
bool WhetherIsOrdered(const vector<string> &str_vec,const string& order);

int main()
{
    vector<string> str_vec{ "offer","is","coming"};
    string order("zyxwvutsrqponmlkjihgfedcba");

    cout << WhetherIsOrdered(str_vec,order);

    return 0;
}
bool WhetherIsOrdered(const vector<string>& str_vec, const string& order)
{
    if (str_vec.size() == 0)
        return false;

    vector<int>order_hash(order.size());
    int order_value=1;
    for (int i = 0; i < order.size(); ++i)
    {
        //索引代表第几个字母，值代表字母的顺序值
        order_hash[order[i] - 'a'] = order_value++;
    }

    for (int idx = 0; idx < str_vec.size()-1; ++idx)
    {
        if (WhetherIsOrderedCore(str_vec[idx], str_vec[idx + 1], order_hash))
            continue;
        else
            return false;
    }

    return true;
}

bool WhetherIsOrderedCore(
    const string& s1, const string& s2,
    const vector<int>& order_hash)
{
    int idx = 0;

    while (idx < s1.size() && idx < s2.size())
    {
        if (order_hash[s1[idx] - 'a'] == order_hash[s2[idx] - 'a'])
        {
            ++idx;
            continue;
        }
        else if (order_hash[s1[idx] - 'a'] < order_hash[s2[idx] - 'a'])
        {
            return true;
        }
        else
            return false;
    }

    return true;
}
#endif


//面试题35：最小时间差
#if 0
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    int getMinutes(string& t) {
        return (int(t[0] - '0') * 10 + int(t[1] - '0')) * 60 + int(t[3] - '0') * 10 + int(t[4] - '0');
    }

public:
    int findMinDifference(vector<string>& timePoints) 
    {
        int n = timePoints.size();
        if (n > 1440)
        {
            return 0;
        }
        sort(timePoints.begin(), timePoints.end());

        int ans = INT_MAX;
        int t0Minutes = getMinutes(timePoints[0]);
        int preMinutes = t0Minutes;

        for (int i = 1; i < n; ++i) 
        {
            int minutes = getMinutes(timePoints[i]);
            ans = min(ans, minutes - preMinutes); // 相邻时间的时间差

            preMinutes = minutes;
        }

        ans = min(ans, t0Minutes + 1440 - preMinutes); // 首尾时间的时间差
        //因为是经过sort的，所以假如首时间为00：00，而尾时间为23：59，那么如果不加1440，
        // 则（t0Minutes - preMinutes）= 0 -1439 = -1439，
        // 那么和经过min(ans, t0Minutes + 1440 - preMinutes) 之后答案肯定是-1439，
        // 那不是离谱的嘛对吧，而真实情况就是首尾时间相差1，那么加上1440之后，
        // （ t0Minutes + 1440 - preMinutes）就是0+1440-1439 = 1，这就对了哈。
        return ans;
    }
};
//作者：力扣官方题解
#endif
//补充：
//还可以进行优化：
//开一个1440长度的数组，将每个时间处理为分钟数，每个时间在数组上对应位置值为true
//这样时间输入完后就自动排好了序。
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int CalMin(const vector<string> &str_vec);
int CalMinCore(shared_ptr<bool> &hash);

int main()
{
    vector<string> str_vec{"23:50","23:59","00:00"};

    cout << CalMin(str_vec);

    return 0;
}

int CalMin(const vector<string>& str_vec)
{
    if (str_vec.empty())
        return -1;

    shared_ptr<bool> hash(new bool [1440] {false}, default_delete<bool[]>());

    string strhours, strminutes;
    for (int i = 0; i < str_vec.size(); ++i)
    {
        strhours = str_vec[i].substr(0,2);
        strminutes = str_vec[i].substr(3, 2);

        int idx = stoi(strhours) * 60 + stoi(strminutes);

        if (hash.get()[idx])
            return 0;
        else
            hash.get()[idx] = true;
    }

    return CalMinCore(hash);
}
int CalMinCore(shared_ptr<bool>& hash)
{
    int nowIdx, preIdx;
    nowIdx = preIdx = -1;

    int MinValue = numeric_limits<int>::max();
    int theFirstTime;

    for (int i = 0; i < 1440; ++i)
    {
        if (hash.get()[i])
        {
            if (preIdx == -1)
            {
                theFirstTime=preIdx = i;
                continue;
            }

            nowIdx = i;

            MinValue = min(MinValue,nowIdx-preIdx);

            preIdx = nowIdx;
        }
    }

    return min(MinValue, theFirstTime + 1440 - nowIdx);
}
#endif


//面试题36：后缀表达式
//经验：
//使用栈
#if 0
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int Calculate(const string &input);
int CalculateCore(stack<int> &stk,string op);

int main()
{
    string inputStr{"2,1,3,*,+"};

    cout << Calculate(inputStr)<<endl;

    cout << Calculate(string("200,1,3,*,+")) << endl;

    return 0;
}
int Calculate(const string& input)
{
    if (input.empty())
        return 0;

    stack<int>stk;

    istringstream is(input);

    //错误写法：
    //进行计算的数字只支持一位数字
#if 0
    char ch;
    while (is)
    {
        is >> ch;

        if (isdigit(ch))
            stk.push(ch);
        else
            CalculateCore(stk,ch);

        is.ignore();//跳过一个字符
    }
#endif

    string str="";

    while (is)
    {
        //***注***
        //Input string stream的截止判断条件不再是通常cin情况输入下的EOF
        //而是string::npos
        while(is.peek()!=','&& is.peek() != string::npos)
        {
            str+=is.get();
        }

        if (all_of(str.begin(), str.end(), [](char ch) {return isdigit(ch);}))
            stk.push(stoi(str));
        else
            CalculateCore(stk, str);

        if (is.peek() != string::npos)
            is.ignore();//跳过一个字符
        else
            break;

        str.clear();
    }

    return stk.top();
}
int CalculateCore(stack<int>& stk, string str)
{
    if (stk.size() < 2)
        exit(-1);

    int a, b;
    char op = str[0];

    b = stk.top();
    stk.pop();
    a = stk.top();
    stk.pop();

    switch (op)
    {
    case '+':
    {
        stk.push(a+b);
    }
    break;
    case '-':
    {
        stk.push(a - b);
    }
    break;
    case '*':
    {
        stk.push(a * b);
    }
    break;
    case '/':
    {
        stk.push(a / b);
    }
    break;
    default:
        cout << "Error!\n";
    }

    return stk.top();
}
#endif


//面试题37：小行星碰撞
#if 0
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> WhatRemain(const vector<int>& input);
//int WhatRemainCore(stack<pair<int, int>>& Rstk,  stack<pair<int, int>>& Lstk);

int main()
{
    vector<int>DataInput{ 4, 5, -6, 4, 8, -5 };

    vector<int> res = WhatRemain(DataInput);

    for (auto x : res)
        cout << x << ' ';

    return 0;
}
#if 0
vector<int> WhatRemain(const vector<int>& input)
{
    if (input.empty())
        exit(-1);

    stack<pair<int, int>> GoRight_stack_elem_idx_pairs;
    stack<pair<int, int>> GoLeft_stack_elem_idx_pairs;

    for (int index = 0; index < input.size(); ++index)
    {
        int elem = input[index];

        //若向右飞行
        if (elem > 0)
            GoRight_stack_elem_idx_pairs.emplace(elem, index);
        else//若向左飞行
            GoLeft_stack_elem_idx_pairs.emplace(elem,index);
    }

    WhatRemainCore(GoRight_stack_elem_idx_pairs, GoLeft_stack_elem_idx_pairs);


}
int WhatRemainCore(stack<pair<int, int>>& Rstk, stack<pair<int, int>>& Lstk)
{
    return 1;
}
//错误处理：
//根据数据的正负，放入两个stack中，这样增加处理数据的难度
#endif

#if 0
vector<int> WhatRemain(const vector<int>& input)
{
    if (input.empty())
        exit(-1);

    vector<int> res;

    for (int i = 0; i < input.size(); ++i)
    {
        int elem = input[i];

        if (res.empty())
            res.push_back(elem);
        else
        {
            //情况1：同向       
            int PreValue = input[i - 1];
            bool PreRightOrLeft = PreValue > 0 ? true : false;
            bool RightOrLeft = elem > 0 ? true : false;

            if (PreRightOrLeft == RightOrLeft)
                res.push_back(elem);
            else//情况2：反向       
            {
                //特殊情况：反向但不相撞
                if (PreRightOrLeft == false && RightOrLeft==true)
                {
                    res.push_back(elem);
                    continue;
                }

                //情况2.1：res中的末尾的值的绝对值等于现在处理的元素值
                if (abs(res.back()) == abs(elem))
                    res.pop_back();
                //情况2.2：res中的末尾的值的绝对值大于现在处理的元素值
                else if (abs(res.back()) > abs(elem))
                    continue;
                //情况2.3：res中的末尾的值的绝对值小于现在处理的元素值
				else
                {
                    //先把末尾的元素弹出
                    res.pop_back();
                    //因为现在处理的元素又会遭遇之前压入的元素，又会遭遇上述情况
                    //所以此处处理为
                    if (res.empty())
                        res.push_back(elem);
                    else
						--i;//***理解***
                }
            }
        }
    }

    return res;
}
#endif

//更简洁的代码
#if 1
vector<int> WhatRemain(const vector<int>& asteroids)
{
	vector<int> st;

	for (auto aster : asteroids)
    {
		bool alive = true;

        //分析得到两个小行星要相撞，必须st容器末尾元素代表的
        // 小行星向右飞行，当前遍历到的小行星向左飞行
        
        //aster仍存在且向左飞行且st容器非空且st容器末尾元素代表的小行星向右飞行
		while (alive && aster < 0 && !st.empty() && st.back() > 0) 
        {
            //两个小行星相撞，会只剩一个或者啥也不剩

			alive = st.back() < -aster; // aster 是否存在
            //情况1：alive为true：相撞但st容器末尾元素代表的小行星体积更小
            //情况2：alive为false：相撞但st容器末尾元素代表的小行星体积更大或体积相等

            //会造成st容器的末尾元素弹出的情况：
            //相撞但st容器末尾元素代表的小行星体积更小或体积相等
			if (st.back() <= -aster)
            {  
                // 栈顶行星爆炸
				st.pop_back();
			}
		}

		if (alive)
        {
			st.push_back(aster);
		}
	}
	return st;
}
/*
当行星 aster 存在且 aster<0, 栈顶元素非空且大于 0 时，
说明两个行星相互向对方移动：如果栈顶元素大于等于 −aster，则行星 aster 发生爆炸，
将 alive 置为 false；如果栈顶元素小于等于 −aster，则栈顶元素表示的行星发生爆炸，
执行出栈操作。
重复以上判断直到不满足条件，如果最后 alive 为真，说明行星 aster 不会爆炸，
则将 aster 入栈。
链接：https://leetcode.cn/problems/asteroid-collision/solutions/1663442/xing-xing-peng-zhuang-by-leetcode-soluti-u3k0/
*/
#endif
#endif


//面试题38：每日温度
#if 0
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> WaitDays(const vector<int>& input);

int main()
{
    vector<int> temper_vec{35,31,33,36,34};

    vector<int>res = WaitDays(temper_vec);

    for (auto x : res)
        cout << x << ' ';

    return 0;
}
vector<int> WaitDays(const vector<int>& input)
{
    if (input.empty())
        throw exception("Error data");

    //创建栈来存储元素的索引值
    stack<int> stk;
    //***理解***
    //栈中存的是待比较的温度对应的天数(从第0天开始)

    //创建vector容器来存储结果值
    vector<int>ans(input.size(), 0);
    //***注***
    //0代表后面无更高的温度

    for (int i = 0; i < input.size(); ++i) 
    {
        if (stk.empty())
        {
            stk.push(i);
        }
        else 
        {
            //若栈非空，且栈顶索引值对应的元素值小于当前遍历的元素值
            //即后面出现了更高的温度
            while ( !stk.empty()&& input[stk.top()] < input[i])
            {
                //***理解***
                //ans中栈顶索引值对应的元素值设置为当前轮到的索引值减去栈顶索引值
                ans[stk.top()] = i - stk.top();

                //和当前轮到的索引值代表的天数【最接近的天数】(即栈顶值对应的天数)
                //在ans中对应的值已经计算完毕，该天数从栈中弹出
                stk.pop();
            }

            stk.push(i);
        }
    }
    return ans;
}
#endif


//
#if 1

#endif


//面试题41：滑动窗口的平均值
#if 0
#include <iostream>
#include <deque>
using namespace std;

class MovingAverage
{
private:
    double sum = 0;
    deque<int> deq;
    int eleCnt = 0;
    int m_size;

public:
    MovingAverage(int size);
    double next(int val);
};

MovingAverage::MovingAverage(int size)
{
    m_size = size;
    //deq.resize(size);
    //fill(deq.begin(),deq.end(),0);
}

double MovingAverage::next(int val)
{
    if (deq.size() == m_size)
    {
        sum -= deq.front();
        deq.pop_front();
    }

    sum += val;
    deq.push_back(val);

    return sum / deq.size();
}

int main()
{
    MovingAverage MA(3);

    cout<<MA.next(1)<<endl;
    cout<<MA.next(2) << endl;
    cout<<MA.next(3) << endl;
    cout << MA.next(4) << endl;
    cout << MA.next(5) << endl;

    return 0;
}
#endif


//
#if 1

#endif


//面试题59：数据流的第k大的数字
//分析：
//如果数据存储在排序的数组中，那么只需要O(1)的时间就能找出第k大的数字。
// 但这个直观的方法有两个缺点。首先，需要把从数据流中读取的所有数据
// 都存到排序数组中，如果从数据流中读出n个数字，那么动态数组的大小为O(n)。
// 随着不断地从数据流中读出新的数据，O(n)的空间复杂度可能会耗尽所有的内存。
// 其次，在排序数组中添加新的数字的时间复杂度也是O(n)
#if 0
//思路：
//1.为了保证数据流的所有数据都能得到处理，但没有这么多空间来存放这些数据，
//考虑用合适的容器，【只存储最大的k个数字】，在每次从数据流中读取到数据后，
//都判断并进行可能的容器内元素的更改
//2.要减少添加新的数字的时间复杂度，同时要处理可能发生的元素变动
//可以使用优先队列(priority_queue)模拟一个最小堆
//【 存的是数据流中第一个元素到当前遍历的元素中最大的元素到第k大的元素】
//空间复杂度O(k)，插入与弹出的复杂度O(logk)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class KthLargest
{
private:
    //***注***
    //写法：int,vector<int>,greater<int>
    priority_queue<int,vector<int>,greater<int>> prq;//模拟最小堆
    size_t m_size = 0;

public:
    KthLargest(int k, const vector<int>& vec)
    {
        m_size = k;

        for (auto x : vec)
        {
            if (prq.size() < m_size)
            {
                prq.push(x);
            }
            else
            {                
                prq.push(x);
                prq.pop();
            }
        }
    }

    int add(int num)
    {
        if (prq.size() < m_size)
        {
            prq.push(num);
        }
        else
        {            
#if 1
            if (prq.top() > num)
            {}//因为最小堆中的最小元素比num大，代表最小堆中其他元素也比num大，
              //不用再推入队列进行处理
            else
            {
                prq.push(num);
                prq.pop();
            }

#endif

#if 0
            //如下写法不可行：
            if(prq.top()<num)
            { }
            else
            {
                prq.push(num);
                prq.pop();
            }
			//***注***
            //不用该if (prq.top() < num)判断式   
            //因为最小堆中的最小元素比num小，代表num可能为第x个大的数字，prq.top()会改变
            //因此还是要将num压入队列，进行处理。
#endif
        }

        //prq.top()就是k个元素中最小的元素，就是第k大的数字
        return (prq.size() < m_size) ? (numeric_limits<int>::min()) : (prq.top());
    }
};

int main()
{
    vector<int> vec{4,5,8,2};

    //第k大的数字，数组
    KthLargest KL(3, vec);

    cout << KL.add(3) << endl;
    cout << KL.add(5) << endl;

    //***注***
    //可以假设k为2来加强理解：
    //k为2，那就是寻找数据流中第2大的元素的值
    //那么由优先队列模拟的最小堆始终元素个数为2
    //比top()小的，直接不做处理，比top()大的再推入队列进行处理
    //处理后top()返回的值就是第2大的元素的值

    //扩展：
    //求第k小的数字，可以用最大堆

    return 0;
}
#endif


//面试题60：出现频率最高的k个数字
#if 0
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<int> FindNumbers(const vector<int>& input,int k);

int main()
{
    vector<int>input{1,2,2,1,3,1};

    int k = 2;

    vector<int>res=FindNumbers(input,k);

    for (auto x : res)
        cout << x << ' ';

    return 0;
}

#if 0
class SortCriterion
{
public:
    //bool operator()(const pair<int, int>&pa1, const pair<int, int>&pa2) const
    //{
    //    return pa1.second >= pa2.second;
    //} 

    //错误：
    //map的键值对只能根据键来排序

    bool operator()(int a, int b) const
    {
        return a>b;
    }
};

vector<int> FindNumbers(const vector<int>& input, int k)
{
    if (input.empty())
        throw exception("Error!");

    vector<int> ans;

    //用unordered_map的话，每个数字对应出现的数字的次数的查询速度是O(1)
    //但出现的次数的一系列值仍然是乱序

    //***注***
    //错误思路：
    //因此要实现【键值对按值来排序】【按从大到小的顺序】

    SortCriterion SC;

    map<int, int,SortCriterion> Num_Appear_pair(SC);

    for (int i = 0; i < input.size(); ++i)
    {
        if (Num_Appear_pair.find(input[i]) == Num_Appear_pair.end())
        {
            Num_Appear_pair.emplace(input[i], 1);
        }
        else
            Num_Appear_pair[input[i]]++;
    }

    int cnt = 1;
    for (auto it=Num_Appear_pair.begin();it!=Num_Appear_pair.end()&&cnt<=k;++it)
    {
        ans.push_back((*it).first);
        cnt++;
    }

    return ans;
}
#endif

//思路：
//既然map容器不能根据值来排序，那就利用最小堆
//最小堆的元素是键值对，根据值的大小来决定是否压入队列进行处理

//创建SortCriterion类作为【函数对象】，来作为最小堆比较元素的规则
class SortCriterion
{
public:
    //***注***最后一个const必须加，否则出现错误C3848
    bool operator()(const pair<int, int>&New_pa, const pair<int, int>&Old_pa) const
    {
        return New_pa.second >= Old_pa.second;//***理解***
    } //想象一个从左侧安插元素从右侧弹出元素的队列，若bool值为真，则新值排在旧值之左侧
};     //队列中元素呈现递减排列，那么弹出的值也就由小到大了。

class MinHeap
{
private:
    priority_queue<pair<int, int>, vector<pair<int, int>>, SortCriterion> Num_Appear_pair_pq;
    int m_k = 0;

public:
    MinHeap(int k)
    {        
        m_k = k;
    }

    void Add(pair<int, int>pa)
    {
        if (Num_Appear_pair_pq.size() < m_k)
        {
            Num_Appear_pair_pq.push(pa);
        }
        else if (pa.second > Num_Appear_pair_pq.top().second)
        {
            Num_Appear_pair_pq.push(pa);
            Num_Appear_pair_pq.pop();
        }
    }

    int Get_num_oneByone()
    {
        int num=Num_Appear_pair_pq.top().first;
        Num_Appear_pair_pq.pop();

        return num;
    }
};

vector<int> FindNumbers(const vector<int>& input, int k)
{
    if (input.empty())
        throw exception("Error!");

    vector<int> ans;

    MinHeap minheap(k);
    unordered_map<int, int>Num_Appear_pair;

    //1.将每个数字出现的次数和该数字绑定，生成pair对，用unordered_map管理
    for (int i = 0; i < input.size(); ++i)
    {
        if (Num_Appear_pair.find(input[i]) == Num_Appear_pair.end())
        {
            Num_Appear_pair.emplace(input[i], 1);
        }
        else
            Num_Appear_pair[input[i]]++;
    }

    //2.将每个pair对使用最小堆进行数据处理，堆中保留出现次数最多的k个数字对应的数字-次数pair对
    for (auto it = Num_Appear_pair.begin(); it != Num_Appear_pair.end(); ++it)
    {
        minheap.Add(*it);
    }

    //3.将结果保存到vector中
    for (int i = 0; i < k; ++i)
        ans.push_back(minheap.Get_num_oneByone());

    return ans;
}
#endif


//面试题61：和最小的k个数对
#if 0
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> FindKSmallestNumPairs(vector<int>& nums1, vector<int>& nums2, int k);

int main()
{
    vector<int>nums1{1,5,13,21};
    vector<int>nums2{2,4,9,15};

    int k = 3;
    vector<vector<int>> res = FindKSmallestNumPairs(nums1,nums2,k);
        
    for (auto x : res)
    {
        for (auto y : x)
            cout << y << ' ';

        cout << endl;
    }

    return 0;
}

class SortCriterion
{
public:
    bool operator()(const pair<int, int>& np, const pair<int, int>& op)const
    {
        return np.first + np.second < op.first + op.second;//生成最大堆
    }
};

vector<vector<int>> FindKSmallestNumPairs(vector<int>& nums1, vector<int>& nums2, int k)
{
    if (nums1.empty() || nums2.empty())
        throw exception("Invalid data");

    priority_queue<pair<int, int>, vector<pair<int, int>>, SortCriterion> pq;

    for(int i=0;i<nums1.size();++i)
        for (int j = 0; j < nums2.size(); ++j)
        {
            if (pq.size() < k)
            {
                pq.emplace(nums1[i],nums2[j]);
            }
            else
            {
                if (nums1[i] + nums2[j] < pq.top().first + pq.top().second)
                {
                    pq.emplace(nums1[i], nums2[j]);
                    pq.pop();
                }
            }
        }

    vector<vector<int>>res;

    while (pq.size())
    {
        res.push_back(vector<int>{pq.top().first,pq.top().second});
        pq.pop();
    }

    return res;
}
#endif


//小结(经验)：
//在最大堆中最大值总是位于堆顶，在最小堆中最小值总是位于堆顶。
// 因此，在堆中只需要O(1)的时间就能得到堆中的最大值或最小值。

//堆经常用来解决在数据集合中找出k个最大值或最小值相关的问题。
// 通常用最大堆找出数据集合中的k个最小值，用最小堆找出数据集合中的k个最大值。


//面试题62：实现前缀树
#if 0
//实现原理：
//一个单词的每个字母都由一个指向PreTree的指针去表示，而指针所在的指针数组的索引值
//就代表了这是哪个字母
#include <string>

using namespace std;

class PreTree
{
private:
    //标记是否为一个单词
    //***注***必须类内初始化为false，
    // 否则以后动态分配的PreTree对象的isWord值为true
    bool isWord=false;
    //创建next数组，有26个元素，每个元素都是指向PreTree的指针，初始化为nullptr
    PreTree* next[26]{nullptr};

public:
    PreTree()
    {}      

    void insert(string& str)
    {        
        //在前缀树中添加单词时，首先到达前缀树的根节点        
        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            //一个字母一个字母地提取
            char ch = str[i];

            // 确定根节点是否有一个子节点和单词的第1个字符对应。
            // 如果该子节点不存在，则创建一个与第1个字符对应的子节点，然后前往该子节点
            if (pNode->next[ch - 'a'] == nullptr)
                pNode->next[ch - 'a'] = new PreTree();

            //如果已经有对应的子节点，则前往该子节点。
            pNode = pNode->next[ch-'a'];

            // 接着判断该子节点中是否存在与单词的第2个字符相对应的子节点，并以此类推，
            // 将单词其他的字符添加到前缀树中
        }

		//当单词的所有字符都添加到前缀树中之后，所在的节点对应单词的最后一个字符。
        // 为了标识路径到达该节点时已经对应一个完整的单词，
        // 需要将该节点的isWord设为true
        pNode->isWord = true;
    }

    bool search(string str)
    {
        //从前缀树的根节点开始查找
        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            char ch = str[i];

            //如果根节点没有一个子节点和字符串的第1个节点相对应，
            // 那么前缀树中自然不存在查找的单词，直接返回false。
            if (pNode->next[ch - 'a'] == nullptr)
                return false;

            pNode = pNode->next[ch - 'a'];
        }

        //直到到达和字符串最后一个字符对应的节点。
        // 如果该节点的isWord的值为true，
        // 那么路径到达该节点时正好对应输入的单词，
        // 因此前缀树中存在该输入的单词，可以返回true；否则返回false。
        return pNode->isWord;
        //***理解***search()方法讲究的是【完全匹配】
    }

    bool starsWith(string str)
    {
        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            char ch = str[i];

            //如果根节点没有一个子节点和字符串的第1个节点相对应，
            // 那么前缀树中自然不存在查找的单词，直接返回false。
            if (pNode->next[ch - 'a'] == nullptr)
                return false;

            pNode = pNode->next[ch - 'a'];
        }

        // 如果一直到前缀的最后一个字符在前缀树中都有节点与之对应，
        // 那么说明前缀树中一定存在以该前缀开头的单词。
        // 此时无论当前节点的isWord的值是什么，都应该返回true。
        return true;
        //***理解***startsWith()方法相当于标准库中的search()，讲究的是【是否包含】
    }
};
#endif


//经验：
//前缀树主要用来解决与字符串查找相关的问题。
//如果字符串的长度为k，由于在前缀树中查找一个字符串
// 相当于顺着前缀树的路径查找字符串的每个字符，因此时间复杂度是O(k)

//比较哈希表与前缀树对于查找字符串的使用上的区别
//在哈希表中，只有输入完整的字符串才能进行查找操作，
// 在前缀树中就没有这个限制。例如，可以只输入字符串的前面若干字符，
// 即前缀，查找以这个前缀开头的所有字符串。
// 如果要求根据字符串的前缀进行查找，那么合理应用前缀树可能是解决这个问题的关键。


//面试题63：替换单词
#if 0
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class PreTree
{
private:
    bool isWord=false;
    PreTree* next[26]{ nullptr };

public:
    PreTree()
    {}

    void insert(string& str)
    {
        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            char ch = str[i];

            if (pNode->next[ch - 'a'] == nullptr)
                pNode->next[ch - 'a'] = new PreTree();

            pNode = pNode->next[ch - 'a'];
        }

        pNode->isWord = true;
    }

    bool starsWith(string str)
    {
        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            char ch = str[i];

            //***
            //树中为cat    输入的str为cattle       
            if (pNode->next[ch - 'a'] == nullptr)
                return false;
            else
                pNode = pNode->next[ch - 'a'];
             
            if (pNode->isWord)
                return true;
        }
    }

    string GetWordRoot(string str)
    {
        string WordRoot;

        PreTree* pNode = this;

        for (int i = 0; i < str.size(); ++i)
        {
            char ch = str[i];
            pNode = pNode->next[ch - 'a'];

            WordRoot += ch;

			if (pNode->isWord)
                return WordRoot;                
        }
    }
};

string ReplaceCertainWords(vector<string> &WordRoot,string sentence);

int main()
{
    vector<string> WordRoot{ {"cat","bat","rat"}};

    string sentence{"the cattle was rattled by the battery"};

    string res = ReplaceCertainWords(WordRoot, sentence);

    cout << res;

    return 0;
}
string ReplaceCertainWords(vector<string>& WordRoot, string sentence)
{
    if (WordRoot.empty() || sentence.empty())
        throw exception("Error!");

    //将词根都存入前缀树
    PreTree PT;

    for (auto x : WordRoot)
        PT.insert(x);

    //解析格式化的输入
    istringstream is(sentence);

    string handleStr,res;

    //错误：
    //这样会忽略掉空白字符
    //is >> handleStr;

    string kongbai(" \t,.;");

    while (is)
    {
        //如果待输入的单个字符不是空白字符
        while (find(kongbai.begin(), kongbai.end(), is.peek()) == kongbai.end())
        {
            //***必写***
            if (is.peek() == string::npos)
                break;

            handleStr += is.get();
        }

        //这个待处理的单词包含前缀树中的词根
        if (PT.starsWith(handleStr))
            res += PT.GetWordRoot(handleStr);//返回这个待处理的单词的词根
        else
            res += handleStr;

        //如果待输入的单个字符是空白字符
        while (find(kongbai.begin(), kongbai.end(), is.peek()) != kongbai.end())
        {
            if (is.peek() == string::npos)
                break;

            res += is.get();
        }

        handleStr.clear();

        if (is.peek() == string::npos)
            break;   
    }

    return res;
}
//string类的find_first_of()才有从指定位置开始搜索的功能，
// 标准库提供的find_first_of()没有该功能
#endif


//
#if 1

#endif


//面试题67:最大的异或
#if 0
//一般方法：
//找出数组中所有的两个数字组成的数对，计算异或值后比较得到最大异或值
//时间复杂度O(n的平方)

//利用前缀树的方法：
//首先思考：异或是同为0，异为1
//如果想找到某个整数k和其他整数的最大异或值，
// 那么尽量找和k的数位不同的整数

//这个问题可以转化为查找的问题，而且还是按照整数的二进制数位进行查找的问题。
// 需要将整数的每个数位都保存下来。前缀树可以实现这种思路，
// 前缀树的每个节点对应整数的一个数位，路径对应一个整数

//数字以从高位到低位的顺序存储在前缀树中
//前缀树用于快速查找和某个数位相异的数位

//前缀树类的next数组怎么定义？
//定义为next[2]

#include <iostream>
#include <vector>

using namespace std;

class PreTree
{
private:
    PreTree* next[2]{nullptr};

    //由于整数都是32位，它们在前缀树中对应的路径的长度都是一样的，
    // 因此没有必要用一个布尔值字段标记最后一个数位

public:
    PreTree()
    {}

    void BuildPreTree(const vector<int>& input)
    {
        for (int i = 0; i < input.size(); ++i)
        {
            PreTree* pNode = this;
            int mask = 1;

            for (int idx = 31; idx >= 0; --idx)
            {
                //错误写法：
                //int tmp = input[i] & (mask << idx);
                //正确写法1：
                int tmp = (input[i] & (mask << idx)) ? 1 : 0;
                //写法2：
                //int tmp = (input[i] & (mask << idx))>>idx;

                //从某个数字的高位开始构造某个数字前缀树表示
                if (pNode->next[tmp] == nullptr)
                {
                    pNode->next[tmp] = new PreTree();
                }

                pNode = pNode->next[tmp];
            }
        }
    }
    //问题：
    //当几个数字都输入进了前缀数，那就分不清前缀树的哪条支路是对应某个数字了
    //到某个支路点后有两个分支点，一个是1，一个是0
    //那一定对应两个数字，遍历到该支路点前的支路都是两个数字具有的相同的位的值
    //后面选择一条支路，也就选择走某个数对应的数位
    //那后面如果再出现分支，就可能出现走到别的数字对应的数位了
    //就是说可能混合走了2个或3个数字的支路。

    //理解：
    //“那后面如果再出现分支，就可能出现走到别的数字对应的数位了”
    //但那个“别的数字”对应的数位，你之前走的路都属于该数字所构造的支路
    //所以从始至终还是”别的数字“这一个数字

    int findMaxXOR(const vector<int>& input) 
    {
        int maxXOR = 0;

        for (int i = 0; i < input.size(); ++i)
        {
            PreTree* pNode = this;
            int currXOR = 0;

            for (int idx = 31; idx >= 0; --idx)
            {
                int bit = (input[i] >> idx) & 1;

                //为了找和当前数位的值相反的位值
                int opposite_bit = 1 - bit;

                if (pNode->next[opposite_bit] != nullptr)
                {
                    //记录计算到当前数位的异或值，即该位为1
                    currXOR |= (1 << idx);

                    pNode = pNode->next[opposite_bit];
                }
                else
                {
                    pNode = pNode->next[bit];
                }
            }

            maxXOR = max(maxXOR, currXOR);
        }

        return maxXOR;
    }

};

//int FindMaxXor(const vector<int>& input);

int main()
{
    vector<int> dataInput{1,3,4,7};

    //int res = FindMaxXor(dataInput);
    PreTree PT;
    PT.BuildPreTree(dataInput);
    cout << PT.findMaxXOR(dataInput);

    return 0;
}
/*
int FindMaxXor(const vector<int>& input)
{
    if (input.empty())
        return 0;

    PreTree PT;

    PT.BuildPreTree(input);

    int maxXor = 0;
}
*/
#endif


//二分查找法
//***注***
//一般的循环入口条件：
//当left等于right时，查找范围是长度为1的子数组。
// 长度为1的子数组仍然是一个有效的查找范围，但当left大于right时
// 这两个下标就不能形成一个有效的查找返回，
// 因此while循环的条件是left小于或等于right。

//经验：
//如果问题是关于在【排序数组】中的查找操作，
//那么可以考虑采用二分查找算法。
//扩展：
//在【分段排序的数组】中也可以尝试二分查找法


//面试题68：查找插入位置
#if 0
#include <iostream>
#include <vector>
using namespace std;

int FindInsertIndex(const vector<int>& input,int t);

int main()
{
    vector<int> input{1,3,6,8};

    int t;

    t = 3;
    cout << FindInsertIndex(input,t)<<endl;

    t = 5;
    cout << FindInsertIndex(input, t)<<endl;

    t = 0;
    cout << FindInsertIndex(input, t)<<endl;

    t = 10;
    cout << FindInsertIndex(input, t)<<endl;

    return 0;
}
int FindInsertIndex(const vector<int>& input, int t)
{
    if (input.empty())
        throw exception("Error!");

    int begidx, endidx,mididx;
    begidx = 0, endidx = input.size() - 1;

    while (begidx <= endidx)
    {
        //注意运算符优先级
        mididx = begidx+((endidx - begidx) >> 1);

        if (input[mididx] == t)
            return mididx;
        else if (input[mididx] < t)
        {
            begidx = mididx + 1;

            //考虑边界情况2：mididx为数组索引最大值，begidx为数组索引最大值+1
            if (begidx > endidx || input[begidx] > t)//注意两个关系表达式先后次序
                return begidx;
        }
        else
        {
            endidx = mididx - 1;

            //考虑边界情况1：mididx为0，endidx为-1
            if (endidx<0 || input[endidx] < t)
                return mididx;
        }
    }

    return -1;
}
#endif


//面试题69：山峰数组的顶部
#if 0
#include <iostream>
#include <vector>
using namespace std;

pair<int, int> FindClimax(const vector<int>& vec);

int main()
{
    vector<int> DataInput{1,3,5,4,2};

    pair<int, int>res = FindClimax(DataInput);
    cout << res.first << ' ' << res.second<<endl;

    DataInput = vector<int>{1,5,4,3,2};
    res = FindClimax(DataInput);
    cout << res.first << ' ' << res.second<<endl;

    DataInput = vector<int>{ 5,4,3,2,1 };
    res = FindClimax(DataInput);
    cout << res.first << ' ' << res.second;

    return 0;
}
pair<int, int> FindClimax(const vector<int>& vec)
{
    if (vec.empty()||vec.size()<3)
        throw exception("Error input!");

    int begidx, endidx, mididx;

    begidx = 0, endidx = vec.size() - 1;

#if 0
    while (begidx <= endidx)
    {
        mididx = begidx + ((endidx - begidx) >> 1);

        if (mididx == begidx || mididx == endidx)
            return make_pair(vec[mididx], mididx);
        else if (vec[mididx] > vec[mididx - 1] && vec[mididx] > vec[mididx + 1])
            return make_pair(vec[mididx], mididx);
        else if (vec[mididx] < vec[mididx - 1])
            endidx = mididx;
        else if (vec[mididx] < vec[mididx + 1])
            begidx = mididx;
    }
#endif
    //mididx到两个顶点，直接返回，这样的操作的前提是
    //endidx = mididx;而不是endidx = mididx-1;   begidx同理

    //换一种：
    while (begidx <= endidx)
    {
        mididx = begidx + ((endidx - begidx) >> 1);
    
        //先考虑顶点情况，再考虑中部的情况

        if (mididx == begidx && vec[mididx] < vec[mididx + 1])
            begidx = mididx + 1;
        else if (mididx == endidx && vec[mididx] < vec[mididx - 1])
            endidx = mididx - 1;
        else if ((mididx == begidx && vec[mididx] > vec[mididx + 1]) || (mididx == endidx && vec[mididx] > vec[mididx - 1]))
            return make_pair(vec[mididx], mididx);
        else if (vec[mididx] > vec[mididx - 1] && vec[mididx] > vec[mididx + 1])
            return make_pair(vec[mididx], mididx);
        else if (vec[mididx] < vec[mididx - 1])
            endidx = mididx-1;
        else if (vec[mididx] < vec[mididx + 1])
            begidx = mididx+1;
    }
}
#endif


///在数值范围内的二分查找(二分答案)
//经验：
//如果一开始不知道问题的解是什么，但是知道解的范围是多少，
// 则可以尝试在这个范围内应用二分查找
//假设解的范围的最小值是min，最大值是max，先尝试范围内的中间值mid。
// 如果mid正好是问题的解，那么固然好。当mid不是问题的解时，
// 如果能够判断接下来应该在从min到mid - 1或从mid + 1到max的范围内查找，
// 那么就可以继续重复二分查找的过程，直到找到解为止。
//应用这种思路的关键在于两点：
// 一是确定解的范围，即解的可能的最小值和最大值。
// 二是在发现中间值不是解之后如何判断接下来应该在解的范围的
// 前半部分还是后半部分查找。只有每次将查找范围减少一半时才能应用二分查找算法


//面试题72：求平方根
#if 0
#include <iostream>
#include <cmath>
using namespace std;

long CalSquareRoot(long num);

int main()
{
    int num = 0;
    cout << CalSquareRoot(num) << endl;

    num = 1;
    cout << CalSquareRoot(num) << endl;

    num = 2;
    cout << CalSquareRoot(num) << endl;

    num = 4;
    cout << CalSquareRoot(num) << endl;

    num = 18;
    cout << CalSquareRoot(num) << endl;

    return 0;
}

#if 0
long CalSquareRoot(long num)
{
    if (num < 0)
        return -1;

    int bidx, eidx, midx;
    bidx = 0, eidx = numeric_limits<int>::max();
    long midxMultiplymidx;

    while (bidx <= eidx)
    {
        //midx = bidx + ((eidx - bidx) >> 1);
        midx = bidx + eidx >> 1;

		midxMultiplymidx = midx * midx;

        //如果发生溢出
        if(midxMultiplymidx<0)
        {
            eidx = midx - 1;
            continue;
        }

        if (midxMultiplymidx == num)
            return midx;
        else if (midxMultiplymidx > num)
            eidx = midx - 1;
        else if (midxMultiplymidx < num)
        {
            if (pow(midx + 1, 2) > num)
                return midx;
            else
                bidx = midx + 1;
        }
    }

    return -2;
}
#endif
//可优化：
//1.整数num的平方根一定小于等于num
//所以eidx最大可以缩小范围至num
//2.上述处理溢出的方法不太好
//将midx * midx == num优化为
//midx == num/midx  这两个式子在数学上等价，
// 但后者可以防止计算溢出

long CalSquareRoot(long num)
{
    if (num < 0)
        return -1;

    int bidx, eidx, midx;
    bidx = 0, eidx = num;
    int tmp;

    if (num == 0)
        return 0;
    else if (num == 1)
        return 1;

    while (bidx <= eidx)
    {
        //midx = bidx + ((eidx - bidx) >> 1);
        midx = bidx + eidx >> 1;

        tmp = num/midx;

        if (midx == tmp)
            return midx;
        else if (midx > tmp)
            eidx = midx - 1;
        else if (midx < tmp)
        {
            if (pow(midx + 1, 2) > tmp)
                return midx;
            else
                bidx = midx + 1;
        }
    }

    return -2;
}
#endif


//面试题73：狒狒吃香蕉
// 狒狒很喜欢吃香蕉。一天它发现了n堆香蕉，第i堆有piles[i]根香蕉。
// 门卫刚好走开，H小时后才会回来。狒狒吃香蕉喜欢细嚼慢咽，
// 但又想在门卫回来之前吃完所有的香蕉。
// 请问狒狒每小时至少吃多少根香蕉？
// 如果狒狒决定每小时吃k根香蕉，而它在吃的某一堆剩余的香蕉的数目少于k，
// 那么它只会将这一堆的香蕉吃完，下一个小时才会开始吃另一堆的香蕉。
// 该题目较为抽象
//用具体的数字做特例化解释
//有4堆香蕉，第i堆有piles[i]根香蕉，piles[4]={1,3,5,7}。门卫6小时后回来
//若每小时至少吃4根香蕉，能在6小时吃完香蕉
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int CalNumsToEat(vector<int>& piles,int H);
int CalCostTime(vector<int>& data, int speed);

int main()
{
    vector<int> piles{1,3,5,7};
    int k,H=6;

    k = CalNumsToEat(piles,H);
    cout << k << endl;

    piles = { 1,3,5,7 }, H = 4;
    k = CalNumsToEat(piles, H);
    cout << k << endl;

    piles = {1,1,1,1},H=4;
    k = CalNumsToEat(piles, H);
    cout << k << endl;

    piles = { 2,1,1,1 }, H = 4;
    k = CalNumsToEat(piles, H);
    cout << k << endl;

    piles = { 3,2,2,2 }, H = 10;
    k = CalNumsToEat(piles, H);
    cout << k << endl;

    return 0;
}
int CalNumsToEat(vector<int>& piles, int H)
{
    //如果香蕉的堆数大于H小时数，
    //那么无论每小时吃多少香蕉，都不可能在H小时吃完
    if (piles.empty() || H <= 0 ||piles.size()>H)
        return -1;

    int Bnum, Enum, Mnum;

    Bnum = 1;
    //Enum = accumulate(piles.cbegin(),piles.cend(),0,plus<int>());

    //最少都需要piles.size()的时间吃完，
    //所以最多数量香蕉的堆的香蕉数可以定为吃的最大速度
    //往后吃的速度可以减少，到指定的H小时内吃完
    Enum = *(max_element(piles.cbegin(),piles.cend()));//*是解引用

    while (Bnum <= Enum)
    {
        Mnum = Bnum + Enum >> 1;

		int CostTime= CalCostTime(piles,Mnum);

        if (CostTime == H)
            return Mnum;
        else if (CostTime > H)//如果花费时间大于规定的H
        {
            Bnum = Mnum + 1;//速度要加快
        }
        else//如果花费时间小于规定的H
        {
            //***注意最小速度是1***
            if (Mnum==1||CalCostTime(piles, Mnum - 1) > H)
                return Mnum;
            else
                Enum = Mnum - 1;
        }
    }

    return -2;
}

int CalCostTime(vector<int>&data,int speed)
{
    int CostTime = 0;

    for (int i = 0; i < data.size(); ++i)
    {
        if (data[i] <= speed)
            CostTime += 1;
        else//***注***
            CostTime += data[i] / speed + ((data[i] % speed) ? 1 : 0);
    }

    return CostTime;
}
#endif


//排序算法
//经验：

//面试题76：数组中第k大的数字
// (比较//面试题59：数据流的第k大的数字，时间复杂度为O(nlogk))
//本题不一样，数据都保存在一个数组中，所有操作都在内存中完成。
//经验：有更快找出第k大的数字的算法，可以利用快速排序算法中的partition()
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int FindKthLargest_Fun1(vector<int> data,int k);
int FindKthLargest_Fun2(vector<int> data, int k);

int main()
{
    vector<int> dataInput{2,3,7,5,9,11,11,12};
    int k = 5;

    cout << FindKthLargest_Fun1(dataInput,k)<<endl;

    k = 6;
    cout << FindKthLargest_Fun2(dataInput, k);

    return 0;
}

void Swap(int* a, int* b)
{
    int tmp = *b;

    *b = *a;
    *a = tmp;
}
//思路：
//***在长度为n的排序数组中，第k大的数字的下标是n-k。***
//用快速排序的函数partition对数组分区，如果函数partition选取的中间值
// 在分区之后的下标正好是n - k，分区后左边的值都比中间值小，
// 右边的值都比中间值大，即使整个数组不是排序的，中间值也肯定是第k大的数字。
int FindKthLargest_Fun1(vector<int> data, int k)
{
    if (data.empty() || k == 0 || k > data.size())
        throw exception("Error input!");

    int bidx = 0;
    int eidx = data.size()-1;

    //C++ STL中的partition()实参需要起始迭代器、终止迭代器、一元谓词函数做单参判断式
    //返回的是第二组元素首元素的迭代器
    //不能满足左边的分区都比中间值小，右边的分区都比中间值大

    //在长度为Len的排序数组中，第k大的数字的下标是Len - k。
    //vector<int>:: iterator targetIter=next(data.begin(), eidx+1-k);
    int targetIdx = data.size() - k;

    default_random_engine rd_engine;

    //错误写法1：
    //uniform_int_distribution<int> rd_num(bidx,eidx);
    //data[rd_num];

    //错误写法2：
    //uniform_int_distribution<int> rd_num(bidx,eidx);
    //int rd_idx=rd_num;

    //正确写法：
    uniform_int_distribution<int> rd_num(bidx, eidx);
    int rd_idx = rd_num(rd_engine);

    //1.将随机索引值对应的值移到数组末尾，做为比较标尺
    Swap(&data[rd_idx],&data[eidx]);

    //2.使用 STL 的 partition 函数进行分区
    auto it = partition(data.begin(), data.end(),
        [&](int x) {return x <= data[eidx]; });

    // 枢轴值的位置
    int it_idx = it - data.begin();

    // 将枢轴值放到正确的位置上
    Swap(&data[it_idx], &data[eidx]);

    while (it_idx != targetIdx)
    {
        if (it_idx > targetIdx)
            eidx = it_idx - 1;
        else
            bidx = it_idx + 1;

        uniform_int_distribution<int> rd_num(bidx, eidx);
        rd_idx = rd_num(rd_engine);

        Swap(&data[rd_idx], &data[eidx]);

        it = partition(data.begin()+ bidx, data.begin()+ eidx,
            [&](int x) {return x <= data[eidx]; });
        it_idx = it - data.begin();

        Swap(&data[it_idx], &data[eidx]);
    }

    return data[targetIdx];
}

//由此可见，不封装partition()及其依赖代码块，代码篇幅较大
//可对重复调用部分进行封装

int MyPartition(vector<int>& data, int bidx, int eidx)
{
    //1.取一个随机的索引值
    default_random_engine rd_engine;
    uniform_int_distribution<int> rd_num(bidx, eidx);
    int rd_idx = rd_num(rd_engine);

    //2.将随机索引值对应的值移到数组末尾，做为比较标尺
    Swap(&data[rd_idx],&data[eidx]);

    //3.使用 partition 函数进行分区，返回一个枢轴位置(迭代器的形式)
    auto it = partition(data.begin()+bidx,data.begin()+eidx,
        [&](int x) {return x <= data[eidx]; });//***注***是小于等于

    //现在第一组元素的值都小于等于第二组元素的值，
    //而it指向第二组的首元素

    int idx = distance(data.begin(), it);

    //4.原来随机的索引值对应的数字  回到  现在枢纽值代表的位置
    Swap(&data[idx], &data[eidx]);

    //现在第一组元素仍都小于第二组元素
    //返回第二组首元素索引值
    return idx;
}

int FindKthLargest_Fun2(vector<int> data, int k)
{
    if (data.empty() || k == 0 || k > data.size())
        throw exception("Error input!");

    int bidx = 0;
    int eidx = data.size() - 1;

    int targetIdx = data.size() - k;

    int idx = MyPartition(data,bidx,eidx);

    while (idx != targetIdx)
    {
        if (idx > targetIdx)
            eidx = idx - 1;
        else
            bidx = idx + 1;

        idx = MyPartition(data, bidx, eidx);
    }

    return data[targetIdx];
}
#endif


//回溯算法
//经验：
// 回溯算法本质上是纯暴力搜索，但有些问题用多层的for循环都很难解答
// 回溯法能解答已经是算可以的了。
// 如果解决一个问题需要若干步骤，每一步都面临若干选项，
// 并且题目要求列出问题所有的解，那么可以尝试用回溯法解决这个问题。
// 回溯法通常可以用递归的代码实现
//回溯法可以解决的问题类型：
//组合问题
//切割问题
//子集问题
//排列问题
//棋盘问题

//回溯算法很抽象，理解时最好把回溯法抽象成一个图形结构
//脑内模拟回溯十分困难
//所有的回溯法都可以抽象为一个【树形结构】
/*

    -------- for ----------------->
  |                             ○
  |  递                      /  \
  |  归                    ○      ○ 
  |                      /  |  \    /\
  |                    ○   ○  ○  ○ ○
 ∨

*/

//       void  backtracking(参数)
//       {
//              if(终止节点)
//              {
//                收集结果
//                return;
//              }
//             for(集合的元素集)
//             {
//               处理节点; 
//               递归函数;
//               回溯操作(撤销操作)
//             }
//            return;
//       }


//引入：
//面试题：LeetCode 77 组合
#if 0
/*
有数字集合 1 2 3 4 5 6 7 8，求所有可能的3个数字的组合

用for循环：
for(int i=0;i<size;++i)
    for(int j=i+1;j<size;++j)
        for(int k=j+1;k<size;++k)
        {  }

时间效率不达标
*/

//回溯算法如何解决该问题？
//回溯算法也是模拟这种嵌套for的过程，用
//【递归来控制有多少层for循环】，有多少次递归就有多少个嵌套for循环

//对于该题，画树形结构：
/*
                      1              2      3       4 
                     /               /         \        \
                    1              2           3       4        取用
                 2 3 4         3  4         4       无       余下
                /   |   \         |    \         |
            1 2  1 3  1 4   2 3  2 4   3 4

细节1：对于     2 
                       /  
                      2   
                    3  4   为什么 1 2 不写了呢
           若写为    2 
                        /  
                       2   
                   1 2  3  4    那么就会变成    2 
                                                           /  
                                                          2   
                                                    1  2    3    4 
                                                   /    |      \    \
                                                2 1   2 2  2 3  2 4 其中的2 1和前面的1 2情况重复，2 2不符合题意

         所以取用什么数字，余下的就是该数字后面的若干数字


写代码——【回溯三部曲】：
1.递归函数的参数和返回值
2.确定终止条件
3.单层搜索逻辑 (集合元素集(有时可剪枝)，处理节点，递归函数，回溯操作)

*/

#include <iostream>
#include <vector>

using namespace std;

//startindex 确定每次搜索余下若干数字的起始位置
void backtracking(vector<vector<int>> &res, vector<int> &path,int n,int k,int startindex)
{
    //终止节点：
    //如果树形结构到达了叶子结点，即path的大小等于k值，就证明找到了组合
    if (path.size() == k)
    {
        //收集结果
        res.push_back(path);
        return;
    }

    //单层搜索逻辑：
    //集合的元素集
    for (int i = startindex; i <= n; ++i)//范围[1, n]  所以是小于等于
    {
        //处理节点：取哪个数字   比如取1
        path.push_back(i);
		//递归函数                        比如取1，那剩下2 3 4 只能从2开始搜索
        backtracking(res, path, n, k, i + 1);
        //回溯操作(撤销操作)
        //理解：得到结果1 2，把2弹出后，才能在后续得到1 3
        //【反应在树形结构上就是回到上一个节点】
        path.pop_back();
    }

    return;
}

int main()
{
    int n, k;

    cin >> n >> k;

    vector<int> path;
    vector<vector<int>>res;    
    backtracking(res,path,n,k,1);//返回范围[1, n] 中所有可能的 k 个数的组合，所以startindex为1

    for (const auto& x : res)
    {
        cout << '[';
        for (auto it = x.cbegin(); it != x.cend(); ++it)
        {
            cout << *it;

            if (it == x.cend() - 1)
                cout << "],\n";
            else
                cout << ',';
        }
    }
}
#endif
//组合问题的剪枝操作  【针对单层搜索逻辑】
#if 0
//对于LeetCode 77 组合，如果n为4，k为4
//那么对于树形结构
/*
                      1              2      3       4 
                     /               /         \        \
                    1              2           3       4        取用
                 2 3 4         3  4         4       无       余下
                /   |   \         |    \         |
            1 2  1 3  1 4   2 3  2 4   3 4

    仅可以保留取用1，余下2 3 4 的情况，其他情况都可以剪除
    当剪除了有深度的分支，对于降低时间复杂度是有效果的

                1   
                /    
               1     
            2 3 4    
            /   |   \ 
        1 2  1 3  1 4 
        3 4    4     无               可以剪除  3 4    
                                                           |   \ 
                                                          1 3  1 4 
                                                            4     无

       变成：             1   
                              /    
                             1     
                          2     
                          /      
                      1 2  
                      3 4  
                      /   \
                  1 2 3  1 2 4
                     4       无               可以剪除     1 2
                                                                   3 4
                                                                        \
                                                                         1 2 4
                                                                            无

          最后变成：   1
                             /
                            1
                         2
                         /
                     1 2
                     3 4
                     /   
                 1 2 3  
                    4       
                    /
             1 2 3 4

             剪枝，剪的是节点的子孩子，如何体现在单层搜索逻辑上？
             单层搜索逻辑：
             for (int i = startindex; i <= n; ++i)
             应该缩小 i 的取值范围，来达到剪枝的目的

             k：要选的数字的个数
             path.size()：已经选了的数字的个数
             k-path.size()：还需要选的数字的个数
             n：范围[1,n]

             n-(k-path.size())+1：【至多】是从该值开始搜索
             4-(4-0)+1=1 达到了最大从1开始搜索
*/

#include <iostream>
#include <vector>

using namespace std;

//startindex 确定每次搜索余下若干数字的起始位置
void backtracking(vector<vector<int>>& res, vector<int>& path, int n, int k, int startindex)
{
    //终止节点：
    //如果树形结构到达了叶子结点，即path的大小等于k值，就证明找到了组合
    if (path.size() == k)
    {
        //收集结果
        res.push_back(path);
        return;
    }

    //单层搜索逻辑：
    //集合的元素集
    for (int i = startindex; i <= n - (k - path.size()) + 1; ++i)
    {
        //处理节点：取哪个数字   比如取1
        path.push_back(i);
        //递归函数                        比如取1，那剩下2 3 4 只能从2开始搜索
        backtracking(res, path, n, k, i + 1);
        //回溯操作(撤销操作)
        //理解：得到结果1 2，把2弹出后，才能在后续得到1 3
        //【反应在树形结构上就是回到上一个节点】
        path.pop_back();
    }

    return;
}

int main()
{
    int n, k;

    cin >> n >> k;

    vector<int> path;
    vector<vector<int>>res;
    backtracking(res, path, n, k, 1);//返回范围[1, n] 中所有可能的 k 个数的组合，所以startindex为1

    for (const auto& x : res)
    {
        cout << '[';
        for (auto it = x.cbegin(); it != x.cend(); ++it)
        {
            cout << *it;

            if (it == x.cend() - 1)
                cout << "],\n";
            else
                cout << ',';
        }
    }
}
#endif


//面试题：组合总和
#if 0
//分析：
/*
                            1           2           3           4          5
                        /
                      1
                2 3 4 5
               /
           1 2 
         3 4 5
       可剪枝

*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> FindCombinations(int n,int k);
void FindCombinationsCore
(vector<vector<int>>&res, vector<int>&path,int n,int k,int start);

int main()
{
    int n, k;  //  范围[1,n]        要求组合的数字和为n，组合包含数字个数k  

    n = 5, k = 3;

    vector<vector<int>> res = FindCombinations(n,k);

    if (!res.empty())
        for (const auto& x : res)
        {
            for (auto y : x)
                cout << y << " ";

            cout << endl;
        }
    else
        cout << "No result!\n";

    n = 9, k = 3;
    res = FindCombinations(n, k);

    if (!res.empty())
        for (const auto& x : res)
        {
            for (auto y : x)
                cout << y << " ";

            cout << endl;
        }
    else
        cout << "No result!\n";

    return 0;
}

vector<vector<int>> FindCombinations(int n, int k)
{
    if (n < 1 || k < 1)
        throw exception("Error data");

    vector<vector<int>>res;
    vector<int> path;

    FindCombinationsCore(res,path,n,k,1);

    return res;
}

void FindCombinationsCore
(vector<vector<int>>& res, vector<int>& path, int n, int k, int start)
{
    //优化1：
    if (path.size() > k)
    {
        return;
    }

    if (n == 0 && path.size() == k)
    {
        res.push_back(path);

        return;
    }

    for (int i = start; i <= n; ++i)
    {
        path.push_back(i);

        //                                         优化2：n-i
        FindCombinationsCore(res,path,n-i,k,i+1);

        path.pop_back();
    }

    return;
}
#endif
//代码随想录官方版本：
#if 0
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> FindCombinations(int n, int k);
void FindCombinationsCore
(vector<vector<int>>& res, vector<int>& path,
    int targetSum, int currentSum, int k, int start);

int main()
{
    int n, k;  //  范围[1,n]        要求组合的数字和为n，组合包含数字个数k  

    n = 5, k = 3;

    vector<vector<int>> res = FindCombinations(n, k);

    if (!res.empty())
        for (const auto& x : res)
        {
            for (auto y : x)
                cout << y << " ";

            cout << endl;
        }
    else
        cout << "No result!\n";

    n = 9, k = 3;
    res = FindCombinations(n, k);

    if (!res.empty())
        for (const auto& x : res)
        {
            for (auto y : x)
                cout << y << " ";

            cout << endl;
        }
    else
        cout << "No result!\n";

    return 0;
}

vector<vector<int>> FindCombinations(int n, int k)
{
    if (n < 1 || k < 1)
        throw exception("Error data");

    vector<vector<int>>res;
    vector<int> path;

    FindCombinationsCore(res, path, n, 0, k, 1);

    return res;
}

void FindCombinationsCore
(vector<vector<int>>& res, vector<int>& path,
    int targetSum, int currentSum, int k, int start)
{
    //剪枝1：
    if (currentSum > targetSum)
        return;

    if (path.size() == k && currentSum == targetSum)
    {
        res.push_back(path);
        return;
    }

    //剪枝2：
    //若n=9，k=2，那么i从数字9开始取数字就没有意义
    //n-(k-path.size())+1  【至多】是从该值开始搜索

    //for (int i = start; i <= targetSum; ++i)
    for (int i = start; i <= targetSum - (k - path.size()) + 1; ++i)
    {
        currentSum += i;
        path.push_back(i);

        FindCombinationsCore(res, path, targetSum, currentSum, k, i + 1);

        currentSum -= i;
        path.pop_back();
    }
}
#endif


//面试题81：允许重复选择元素的组合
//给定一个没有重复数字的正整数集合，请列举出所有元素之和
// 等于某个给定值的所有组合。同一个数字可以在组合中出现任意次。
//回溯法解决
//回溯法可以用递归的代码实现
#if 0
//能够用回溯法解决的问题都能够分成若干步来解决，每一步都面临若干选择。

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>>FindCombinations(vector<int>& input, int k);
void FindCombinationsCore(vector<int>& input,int k,vector<int>& current,
    vector<vector<int>>& res,int start);

int main()
{
    vector<int> dataInput{2,3,5};
    int k = 8;

    vector<vector<int>>res=FindCombinations(dataInput, k);

    for (auto x : res)
    {
        for (auto y : x)
            cout << y << ' ';

        cout << endl;
    }

    return 0;
}

vector<vector<int>>FindCombinations(vector<int>& input, int k)
{
    if (input.empty() || k <= 0)
        throw exception("Error!");

    //创建存储其中一组数字的容器
    vector<int> current;
    //创建存储满足要求的所有组合的容器
    vector<vector<int>> res;

    FindCombinationsCore(input,k,current,res,0);

    return res;
}
// 对于从集合中选取数字组成组合的问题而言，集合中有多少个数字，
// 解决这个问题就需要多少步。每一步都从集合中取出一个下标为i的数字，
// 此时面临两个选择：
// 一个选择是跳过这个数字不将该数字添加到组合中，
// 那么这一步实际上什么都不做，接下来处理下标为i + 1的数字。
// 另一个选择是将数字添加到组合中，由于一个数字可以重复在组合中出现，
// 也就是说，下一步可能再次选择同一个数字，因此下一步仍然处理下标为i的数字
#if 0
void FindCombinationsCore(vector<int>& input, int k, vector<int>& current,
    vector<vector<int>>& res)
{
    //回溯的终止条件
    //k是组合中元素之和的目标值。每当在组合中添加一个数字时，
    // 就从target中减去这个数字。当k等于0时，组合中的所有元素之和正好等于k，
    // 因此也就找到了一个符合条件的组合
    if (k == 0)
    {
        res.push_back(current);
        return;
    }
    else if (k < 0)
        return;

    for (int i = 0; i < input.size(); ++i)
    {
        current.push_back(input[i]);

        FindCombinationsCore(input, k - input[i], current, res);

        current.pop_back();
    }

    return;
}
#endif
//结果：
/*
2 2 2 2
2 3 3
3 2 3
3 3 2
3 5
5 3
*/
//结果分析：出现重复的组合，原因是在循环中每次调用FindCombinationsCore
//for循环的起始值都是0

//解决：
//在每次进入回溯后，用变量标记当前遍历到了input数组的哪个元素处
//这样在每次进入循环时，只会从当前遍历到的元素处开始向后尝试，避免了元素的重复
void FindCombinationsCore(vector<int>& input, int k, vector<int>& current,
    vector<vector<int>>& res, int start)
{
    if (k == 0)
    {
        res.push_back(current);
        return;
    }
    else if (k < 0)
        return;

    for (int i = start; i < input.size(); ++i)
    {
        current.push_back(input[i]);

        FindCombinationsCore(input, k - input[i], current, res,i);

        current.pop_back();
    }

    return;
}
#endif
//补充：
//要判断两个数组是否是重复数组，
// 即数组元素的顺序可以不同，但元素的出现次数需要一致
#if 0
#include <iostream>
#include <unordered_map>
#include <vector>

bool isDuplicateArray(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    if (arr1.size() != arr2.size())
    {
        return false;
    }

    std::unordered_map<int, int> frequencyMap;//数值-出现次数pair

    for (int num : arr1)
    {
        frequencyMap[num]++;
    }

    for (int num : arr2)
    {
        if (frequencyMap.find(num) == frequencyMap.end() || frequencyMap[num] == 0)
        {
            return false;
        }

        frequencyMap[num]--;
    }

    return true;
}

int main() 
{
    std::vector<int> arr1 = { 2, 3, 3 };
    std::vector<int> arr2 = { 3, 2, 3 };

    if (isDuplicateArray(arr1, arr2)) 
    {
        std::cout << "Arrays are duplicate arrays." << std::endl;
    }
    else 
    {
        std::cout << "Arrays are not duplicate arrays." << std::endl;
    }

    return 0;
}
#endif


//面试题85：生成匹配的括号
//分析：
// 如果输入n，那么生成的括号组合包含n个左括号和n个右括号。
// 因此生成这样的组合需要2n步，每一步生成一个括号。
// 每一步都面临两个选项，既可能生成左括号也可能生成右括号。
// 由此来看，这个问题很适合采用回溯法解决
#if 0
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> GenerateMatching(int n);
void GenerateMatchingCore
(vector<string>&res, int left, int right, string current);

int main()
{
    int n = 0;

    n = 2;//2个左括号，2个右括号
    vector<string> res = GenerateMatching(n);

    for (auto x : res)
    {
        cout << x<<endl;
    }

    return 0;
}

//错误的写法逻辑：
#if 0
vector<string> GenerateMatching(int n)
{
    if (n < 0)
        throw exception("Error input!");

    vector<string> res;

    return GenerateMatchingCore(res, n, n, "");
}

vector<string> GenerateMatchingCore
(vector<string>res, int left, int right, string current)
{
    if (left == 0 && right == 0)
    {
        res.push_back(current);
    }

    if (left > 0)
        GenerateMatchingCore(res,left-1,right,current+"(");

    if (right > 0)//会出现”())(“”)(()“等情况
        GenerateMatchingCore(res, left, right-1, current + ")");

    return res;
}
#endif
//错误原因：
//GenerateMatchingCore()反复递归调用后，最终返回的仍会是第一次调用该函数时
//其内部(局部)变量res的状态，即res中内容仍为空
//修改：
//递归函数的返回值设为void，真正的结果数据用一个容器的引用来存放
#if 1
vector<string> GenerateMatching(int n)
{
    if (n < 0)
        throw exception("Error input!");

    vector<string> res;
    GenerateMatchingCore(res, n, n, "");

    return res;
}

void GenerateMatchingCore
(vector<string>&res, int left, int right, string current)
{
    if (left == 0 && right == 0)
    {
        res.push_back(current);
    }

    if (left > 0)
        GenerateMatchingCore(res, left - 1, right, current + "(");

    //if (right > 0)//会出现”())(“”)(()“等情况
    //    GenerateMatchingCore(res, left, right - 1, current + ")");

	if (right > left)
		GenerateMatchingCore(res, left, right - 1, current + ")");

    /*
在生成括号组合时需要注意每一步都要满足限制条件。
第1个限制条件是左括号或右括号的数目不能超过n个。
第2个限制条件是括号的匹配原则，
即在任意步骤中已经生成的右括号的数目不能超过左括号的数目。
例如，如果在已经生成"()"之后再生成第3个括号，此时第3个括号只能是左括号不能是右括号。
如果第3个是右括号，那么组合变成"()）"，由于右括号的数目超过左括号的数目，
之后不管怎么生成后面的括号，这个组合的左括号和右括号都不能匹配

//第2个限制条件可以用right > left解决
    */

    return;
}
#endif
#endif


//面试题86：分割回文字符串
#if 0
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> SegmentStr(const string& data);
void SegmentStrCore
(vector<vector<string>>&res, const string& data, int start, vector<string> &current);

int main()
{
    string data{"google"};

    vector<vector<string>> res = SegmentStr(data);

    for (auto x : res)
    {
        for (auto y : x)
            cout << "\"" << y << "\"  ";

        cout << endl;
    }

    return 0;
}

vector<vector<string>> SegmentStr(const string& data)
{
    if (data.empty())
        throw exception("Error data!");

    vector<vector<string>> res;
    vector<string> current;

    //回溯法，如何确定每次进入递归函数时，实参应该是什么

    //思路：
    //输入字符串"google"，假设处理到第1个字符'g'。
    // 此时包括字符'g'在内后面一共有6个字符，
    // 所以此时面临6个选项，即可以分割出6个以字符'g'开头的子字符串，
    // 分别为"g"、"go"、"goo"、"goog"、"googl"和"google"，
    // 其中只有"g"和"goog"是回文子字符串。
    // 分割出"g"和"goog"这两个回文子字符串之后，
    // 再用同样的方法分割后面的字符串

    //每次进入递归函数的实参要体现的意思是
    //在该index位置之前的各个位置，已经分割好
    //现在处理并分割该位置之后的位置

    SegmentStrCore(res,data,0,current);

    return res;
}


bool isHuiWen(const string& str, int bidx, int eidx)
{
    bool flag = false;

    while (bidx<=eidx)
    {
        if(str[bidx] == str[eidx])
			flag = true;
        else
        {
            flag = false;
            break;
        }

        ++bidx, --eidx;
    }

    return flag;
}

void SegmentStrCore
(vector<vector<string>>&res, const string& str,int start, vector<string> &current)
{
    if (start == str.size())
    {
        res.push_back(current);
        return;
    }

    for (int i = start; i < str.size(); ++i)
    {
        if (isHuiWen(str, start, i))
        {
            current.push_back(str.substr(start, i - start + 1));

            for (auto x : current)
            {
                cout << x << " ";
            }
            cout << endl;

            SegmentStrCore(res,str,i+1,current);

            current.pop_back();
            for (auto x : current)
            {
                cout << x << " ";
            }
            cout << endl;
        }
    }

}

//编写难点：
//如何用回溯法实现所有情况的枚举尝试
//人的惯性想法：
//从首个字符进行枚举，会呈现：
//g go goo goog googl google
//明显这样枚举会漏掉很多种情况
//分析：
//在SegmentStrCore()中for()循环作用是确定当前是从start开始到str.size()结束
//有这些 若干种 子串结果进行回文判断的尝试
//先是截取一个字母的情况，有 g  o  o  g  l  e
//回溯，(回溯前进行current弹出操作，变成g  o  o  g  l，
// 然后进入上一级的for中，i值递增1后值为6，再次回溯，
// 进入上一级for中的current.pop_back()，变成g  o  o  g)
//尝试le不满足，
//回溯，(同上，current，变成g  o  o)
//尝试gl 尝试gle
//。。。
//回溯到current变成g
//尝试oo 可行  current变成g oo
//再次尝试g ,可行，curret变成g oo g l e，回溯，尝试gl  尝试gle
//以此类推


//回溯+记忆搜索
#if 1
class Solution
{
private:
    vector<vector<int>> f;
    vector<vector<string>> ret;
    vector<string> ans;
    int n;

public:
    void dfs(const string& s, int i) 
    {
        if (i == n) 
        {
            ret.push_back(ans);
            return;
        }
        for (int j = i; j < n; ++j)
        {
            if (isPalindrome(s, i, j) == 1)
            {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }

    // 记忆化搜索中，f[i][j] = 0 表示未搜索，1 表示是回文串，-1 表示不是回文串
    int isPalindrome(const string& s, int i, int j)
    {
        if (f[i][j]) 
        {
            return f[i][j];
        }
        if (i >= j)
        {
            return f[i][j] = 1;
        }
        return f[i][j] = (s[i] == s[j] ? isPalindrome(s, i + 1, j - 1) : -1);
    }

    vector<vector<string>> partition(string s)
    {
        n = s.size();
        f.assign(n, vector<int>(n));

        dfs(s, 0);
        return ret;
    }
};
#endif
#endif


//贪心算法
//经验：
//贪心算法的本质是找到每个阶段的局部最优从而得到全局最优
//贪心算法的两个极端：感觉题目极简单或者感觉极难
//贪心没有套路
//感觉这道题能用贪心试试，且找不到明显的反例去反驳这种
//局部最优推到全局最优的思路，就用贪心方法去做吧，
//不用硬要把这种想法用数学归纳法或者什么数学方法去证明，那样
//太耗费时间，得不偿失。
//面试题：LeetCode 455 分发饼干
#if 0
//小孩胃口：1   2  7  10
//饼干：       1  3  5  9

//思路：大饼干喂大胃口的小孩，不至于浪费大饼干

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> appetites{ 1,2,7,10 };
    vector<int> cookie{ 1,3,5,9 };

    sort(appetites.begin(),appetites.end());
    sort(cookie.begin(), cookie.end());

    int res = 0;
#if 0
    int index = cookie.size()-1;

    //遍历每个待投喂的小孩
    for (int i = appetites.size() - 1; i >= 0; --i)
    {
        //饼干量比小孩胃口大，就算可以喂饱，处理下一块饼干
        if (index >= 0 && cookie[index] >= appetites[i])
        {
            ++res;
            --index;
        }
    }

    cout << res;
    //细节：
    //可否遍历的是饼干，而内部遍历的是小孩胃口？
    //不可行
    //因为饼干只有在投喂成功一个小孩后才进行下标移动，
    // 硬要实现的话需要更多重复的下标移动操作
#endif

    //写法二：双指针法
    int ia, ic;
    ia = appetites.size() - 1, ic = cookie.size() - 1;

    while (ia >= 0 && ic >= 0)
    {
        if (appetites[ia] <= cookie[ic])
        {
            ++res;
            --ia, --ic;
        }
        else
            --ia;
    }

    cout << res;

    return 0;
}
#endif


//面试题： LeetCode 376 摆动序列
#if 0
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int CalTheLongestSubSequence(const vector<int>& vec)
    {
        if (vec.size() == 1)
            return 1;
        if (vec.size() == 2)
        {
            if (vec[0] != vec[1])
                return 2;
            else
                return 1;
        }

        return CalTheLongestSubSequenceCore(vec);
    }

    int CalTheLongestSubSequenceCore(const vector<int>& vec)
    {
        vector<int> CalTheDiffValue;

        for (auto it = vec.cbegin(); it != vec.cend() - 1; ++it)
        {
            int diff = *next(it) - *it;

            CalTheDiffValue.push_back(diff);
        }

        copy(CalTheDiffValue.begin(), CalTheDiffValue.end(), ostream_iterator<int>(cout, " "));
        //1,17,5,10,13,15,10,5,16,8
        //  16 -12 5 3 2 -5 -5 11 -8 
        //删掉单调的几个数字后得到1, 17, 10, 13, 10, 16, 8
        //                                           16, -7, 3, -3, 6, -8

        //把16 -12 5 3 2 -5 -5 11 -8 变成 16 -12 5 -5 11 -8  同样可以得到size为6
        //那就对CalTheDiffValue进行处理
#if 0
        //***至少三个元素，才可运行如下代码***
        int thefrontValue = CalTheDiffValue[0];
        for (auto it = CalTheDiffValue.begin() + 1; it != CalTheDiffValue.end();)
        {
            if ((thefrontValue >= 0 && *it <= 0) || ((thefrontValue < 0 && *it > 0)))
            {
                thefrontValue = *it;
                ++it;
            }
            else
            {
                it = CalTheDiffValue.erase(it);
            }
        }
        //没有考虑上下坡中有平坡的情况
        //DataInput = { 1,2,2,2,1 };
        //1 0 0 -1
#endif

#if 0
        int thefrontValue = CalTheDiffValue[0];
        for (auto it = CalTheDiffValue.begin() + 1; it != CalTheDiffValue.end();)
        {
            if ((thefrontValue > 0 && *it < 0) || ((thefrontValue < 0 && *it > 0)))
            {
                thefrontValue = *it;
                ++it;
            }
            else
            {
                it = CalTheDiffValue.erase(it);
            }
        }
        //没有考虑单调有平坡后单调的情况
        //DataInput = { 1,2,2,3 };
        //1 0 1
#endif

        //考虑完后代码仍为：
        int thefrontValue = CalTheDiffValue[0];
        for (auto it = CalTheDiffValue.begin() + 1; it != CalTheDiffValue.end();)
        {
            if ((thefrontValue > 0 && *it < 0) || ((thefrontValue < 0 && *it > 0)))
            {
                thefrontValue = *it;
                ++it;
            }
            else
            {
                it = CalTheDiffValue.erase(it);
            }
        }

        return CalTheDiffValue.size() + 1;
    }
    //细节：
    //若真的对数组中的某些数字进行删除操作，反而会使问题更复杂
};

int main()
{
    Solution S;

    vector<int> DataInput;

    DataInput = { 1,7,4,9,2,5 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,17,5,10,13,15,10,5,16,8 };
    cout<<S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,2,3,4,5,6,7,8,9 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,2,2,2,1 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,2,2,2 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,2,2,3 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 1,2 };
    cout << S.CalTheLongestSubSequence(DataInput)<<endl;

    DataInput = { 2,2 };
    cout << S.CalTheLongestSubSequence(DataInput) << endl;

    return 0;
}
#endif


//动态规划算法
//经验：
//动态规划算法可以解决的问题类型：
//基础类(斐波那契数列，爬楼梯)
//背包问题
//打家劫舍
//股票问题
//子序列问题

//误区：
//只关注递推公式，没真正理解解题步骤

//【动态规划五部曲】：
//1.动态规划dp数组以及下标的含义
//2.递推公式
//3.dp数组如何初始化
//4.遍历顺序
//5.打印dp数组可以作为调试分析结果


//经验：
// 运用动态规划解决问题的第1步是识别哪些问题适合运用动态规划。
// 和适合运用回溯法的问题类似，适用动态规划的问题都存在若干步骤，
// 并且每个步骤都面临若干选择。 
//【如果题目要求列举出所有的解，那么很有可能需要用回溯法解决】
//【如果题目是求一个问题的最优解（通常是求最大值或最小值）】
// 或者求问题的解的数目（或判断问题是否存在解），
// 那么这个题目有可能适合运用动态规划
 
 
//引入：
//面试题：LeetCode 509 斐波那契数
#if 0
/*
1.动态规划dp数组以及下标的含义
  dp[i]：第i个斐波那契数的值为dp[i]

2.递推公式
  dp[i]=dp[i-1]+dp[i-2]

3.dp数组如何初始化
  dp[0]=0  dp[1]=1

4.遍历顺序
由于dp[i]由dp[i-1]和dp[i-2]得到，所以应该从前向后遍历
这样保证dp[i]都是最新的值
*/

#include <iostream>
#include <vector>
using namespace std;

int Fib(int n)
{
    if (n <= 0)
        throw exception("Error input!\n");

    if (n == 1)
        return 1;

    vector<int> dp(n + 1, 0);

    dp[0] = 0, dp[1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main()
{
    int n;
    cin >> n;

    cout << Fib(n);

    return 0;
}
//补充：
//状态压缩优化：//面试题10：斐波那契数列
#endif 


//面试题：LeetCode 70 爬楼梯
//若用回溯法：(相当于排列问题，但会超时)
#if 0
/*
                        1              2
                         |
                       1 
                    1  2
                   /
                  1 
                1 2
*/

#include <iostream>
#include <vector>

using namespace std;

void HowManyWays
(vector<vector<int>>&res, vector<int>& currentWays,
    int targetLadder,int currentLadder,int start)
{
    if (currentLadder > targetLadder)
    {
        return;
    }

    if (currentLadder == targetLadder)
    {
        res.push_back(currentWays);
        return;
    }

    for (int i = start; i <= 2; ++i)
    {
        currentWays.push_back(i);
        currentLadder += i;

        HowManyWays(res,currentWays, targetLadder, currentLadder,1);

        currentLadder -= i;
        currentWays.pop_back();
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>>res;
    vector<int>current;
    HowManyWays(res,current,n,0,1);

    for (const auto& x : res)
    {
        for (auto y : x)
            cout << y << ' ';

        cout << endl;
    }

    cout << res.size()<<endl;
}
#endif
//使用动态规划
#if 0
//倒着想：
// 1阶   1种
// 2阶   2种
// 3阶：只能从第1阶或者第2阶上来，1阶的可以迈2阶，2阶的可以迈1阶
//          共3种
//同理4阶  5种
            
//1.dp数组以及下标的含义：达到第i阶有dp[i]种方法
//2.递推公式：dp[i]=dp[i-1]+dp[i-2]
//3.dp数组如何初始化
//dp[0]=?
//由于题目的n为正整数
//所以dp[0]没有意义，直接可从dp[1]初始化，dp[1]=1
//由于dp[2]=dp[1]+dp[0]=2
//所以dp[0]=1

//4.遍历顺序：从前往后
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int>dp(n+1);

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i-1] + dp[i-2];
    }

    for (const auto& x : dp)
    {
        cout << x<<' ';
    }
    cout << endl;

    cout << dp[n];
}
#endif


//爬楼梯花费体力版
//面试题：LeetCode 88 使用最小花费爬楼梯
/*
数组的每个下标作为一个阶梯，第i个阶梯对应着一个非负数的体力花费值cost[i](下标从0开始)
每当爬上一个阶梯都要花费对应的体力值，一旦支付了相应的体力值，
就可以选择向上爬一个阶梯或者爬两个阶梯。
请找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。
*/
#if 0
/*
1.dp[i]表示到第i个阶梯所花费的最小体力值为dp[i]
2.递推公式
假设现在在第0阶梯，那么最小花费是dp[0]=0
假设现在在第1阶梯，那么最小花费是dp[1]=0
假设现在在第2阶梯，那么最小花费是dp[2]=min(cost[1],cost[0])
                                                                 =min(dp[1]+cost[1],dp[0]+cost[0])
假设现在在第3阶梯，那么最小花费是dp[3]=min(dp[2]+cost[2],dp[1]+cost[1])
dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2])
3.初始化
dp[0]=0   dp[1]=0
4.遍历顺序  从左往右
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace  std;

int LowestCost(const vector<int>&vec);

int main()
{
    vector<int>cost;
    cost = { 10,15 };
    cout << LowestCost(cost) << endl;

    cost = { 10,15,20 };
    cout << LowestCost(cost) << endl;

    cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << LowestCost(cost) << endl;

    return 0;
}
int LowestCost(const vector<int>& vec_cost)
{
    int len = vec_cost.size();

    if (len <= 1)
        return 0;

    //错误理解：
    //假设vec_cost={10，15}  要上到第1阶梯输出应该为0而不是10
    //假设vec_cost={10，15，20}  要上到第2阶梯输出为15   ？？？

    //正确理解：
    //阶梯总数为vec_cost.size()，也就是说假设vec_cost={10，15}
    //要到顶为第2阶梯，输出为10
    //假设vec_cost={10，15，20}  要上到第3阶梯输出为15
    //                dp={0,      0,    10,   15}

    vector<int>dp(len+1,0);

    for (int i = 2; i <= len; ++i)
    {
        dp[i] = min(dp[i-1] + vec_cost[i-1], dp[i-2] + vec_cost[i-2]);
    }

    copy(dp.begin(), dp.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return dp[len];
}
#endif


//面试题：LeetCode 98 不同路径
#if 0
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？
*/

//1.动态规划dp数组以及下标的含义
//dp[i][j]：机器人到达位置(i,j)有dp[i][j]种路径
//2.递推公式
/*
“机器人每次只能向下或者向右移动一步”

        i/j        0  1  2  3  4  5  6
                 
        0         1   1  1  1  1  1  1
        1         1   2  3  4  5  6  7 
        2         1   3  6  7
        3         1   4
        4         1
        5         1
        6         1

        错误：dp[i][j]=max(dp[i-1][j],dp[i][j-1])+1

       i/j        0  1  2  3  4  5  6

        0         1   1  1  1  1  1  1
        1         1   2  3  4  5  6  7
        2         1   3  6  10
        3         1   4
        4         1
        5         1
        6         1

        dp[i][j]=dp[i-1][j]+dp[i][j-1]

        出现错误的原因：
        纯粹地依靠画图填数字来推导规律，没有结合题目情景
        来考虑每一个位置对应dp[i][j]的意义
        正确的思考：
        dp[i][j]的路径个数=走到该位置上方的路径个数+走到该位置左方的路径个数  即：
        dp[i][j]的路径个数 = 走到dp[i-1][j]的路径个数+走到dp[i][j-1]的路径个数
        为什么不是
        dp[i][j]的路径个数 = 走到dp[i-1][j]的路径个数+走到dp[i][j-1]的路径个数+1   ？
        混淆了一点：dp[i-1][j]表示的是走到位置[i-1][j]有多少路径，而不是有多少步
        因此在位置[i-1][j]再向下走一步到终点，路径数还是dp[i-1][j]
*/

//3.dp数组如何初始化
//第一行第一列都初始化为1
//4.遍历顺序
//从上到下，从左到右

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int GetPaths(int rows, int cols)
{
    vector<vector<int>>dp(rows, vector<int>(cols, 0));

    fill((*dp.begin()).begin(), (*dp.begin()).end(), 1);

    for (auto it = dp.begin(); it != dp.end(); ++it)
    {
        (*(it))[0] = 1;
    }

    for(int i=1;i<=rows-1;++i)
        for (int j = 1; j <= cols-1; ++j)
        {
            //dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
            dp[i][j] = dp[i - 1][j]+ dp[i][j - 1];
        }

    for (auto const& x : dp)
    {
        for (auto y : x)
            cout << setw(3) << right << y;

        cout << endl;
    }

    return dp[rows-1][cols-1];
}

int main()
{
    int m, n;
    cin >> m >> n;

    cout << GetPaths(m,n)<<endl;

    return 0;
}
#endif


//面试题：LeetCode 63 不同路径2
#if 1
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
网格中的障碍物和空位置分别用 1 和 0 来表示。
*/

//1.动态规划dp数组以及下标的含义
//dp[i][j]：机器人到达位置(i, j)有dp[i][j]种路径
//2.递推公式
/*
对于网格：
01
00

       i/j       0  1  

       0        1  0  
       1        1  1  
 
对于网格：
000
010
000

       i/j       0  1  2  

       0        1  1  1
       1        1  0  1
       2        1  1  2

       有障碍物的位置，dp[i][j]设为0
       dp[i][j]=dp[i-1][j]+dp[i][j-1]
*/
//3.dp数组如何初始化
//第一行第一列都初始化为1
//4.遍历顺序
//从上到下，从左到右

#include <iostream>
#include <vector>

using namespace std;

#if 0
int CalThePaths(const vector<vector<int>>& grid)
{
    vector<vector<int>>dp(grid.size(), vector<int>(grid[0].size(), 0));

    for (int j = 0; j < dp[0].size(); ++j)
       if(grid[0][j]==0)//如果该位置不是障碍物
        dp[0][j] = 1;

    for (int i=0;i<dp.size();++i)
    {
        if (grid[i][0] == 0)//如果该位置不是障碍物
            dp[i][0] = 1;
    }

    for (int i = 1; i <= dp.size()-1; ++i)
        for (int j = 1; j <= dp[0].size()-1; ++j)
        {
            if (grid[i][j] == 0)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }

    return dp[dp.size()-1][dp[0].size()-1];
}
#endif
//错误，没有考虑以下情况：
//如果第一行或者第一列有障碍，不仅是该位置为0，【该位置及其后的位置也要为0】
//如果起始和终止位置为障碍，直接return 0
#if 1
int CalThePaths(const vector<vector<int>>& grid)
{
    if (grid[0][0] == 1 || grid[grid.size()-1][grid[0].size()-1] == 1)
        return 0;

    vector<vector<int>>dp(grid.size(), vector<int>(grid[0].size(), 0));

    for (int j = 0; j < dp[0].size(); ++j)
    {
        if (grid[0][j] == 0)//如果该位置不是障碍物
            dp[0][j] = 1;
        else
            break;
    }

    for (int i = 0; i < dp.size(); ++i)
    {
        if (grid[i][0] == 0)//如果该位置不是障碍物
            dp[i][0] = 1;
        else
            break;
    }

    for (int i = 1; i <= dp.size() - 1; ++i)
        for (int j = 1; j <= dp[0].size() - 1; ++j)
        {
            if (grid[i][j] == 0)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }

    return dp[dp.size() - 1][dp[0].size() - 1];
}
#endif

int main()
{
    vector<vector<int>> grid;

    grid = {
        {0,0,0},
        {0,1,0},
        {0,0,0} };

    cout << CalThePaths(grid)<<endl;

    return 0;
}
#endif


//面试题：LeetCode 343 整数拆分
#if 1
/*
给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。
返回你可以获得的最大乘积
*/


#endif


//爬楼梯进阶版
//每次你可以爬至多m (1 <= m < n)个台阶。有多少种不同的方法可以爬到n阶楼顶
//可以看成是完全背包问题
#if 0
//1.确定dp数组以及下标的含义
//dp[i]：爬到有i个台阶的楼顶，有dp[i]种方法。
//2.确定递推公式
//求装满背包有几种方法，递推公式一般都是dp[i] += dp[i - nums[j]];
//此题dp[i]有几种来源，dp[i - 1]，dp[i - 2]，dp[i - 3] 等等，即：dp[i - j]
//那么递推公式为：dp[i] += dp[i - j]
//3.dp数组如何初始化
//递归公式是 dp[i] += dp[i - j]，那么dp[0] 一定为1，dp[0]是递归中一切数值的基础所在，
// 如果dp[0]是0的话，其他数值都是0了。

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;

    vector<int>dp(n + 1);

    dp[0] = 1;

    //遍历背包
    for (int i = 1; i <= n; ++i)
    {
        //遍历物品
        for (int j = 1; j <= m; ++j)
        {
            if (i - j >= 0)
                dp[i] += dp[i - j];
        }
    }

    cout << dp[n];

    return 0;
}
#endif
 
 
//看//面试题81：允许重复选择元素的组合  适用回溯法
//题目改为：
//面试题：给定一个没有重复数字的正整数集合，
//请找出所有元素之和等于某个给定值的所有组合的数目
//(每个元素可以重复取用)
//就适用于动态规划
#if 0
//每一步都从集合中取出一个下标为i的数字，
// 此时面临两个选择：
// 一个选择是跳过这个数字不将该数字添加到组合中，
// 那么这一步实际上什么都不做，接下来处理下标为i + 1的数字。
// 另一个选择是将数字添加到组合中，由于一个数字可以重复在组合中出现，
// 也就是说，下一步可能再次选择同一个数字，因此下一步仍然处理下标为i的数字

//有数组2,3,5 
//定义：
//D[i][j]为数组前i个元素，和为j的组合数
//求D[3][8]=?

//***错误的分解想法****
//分解：
//情况1：选择当前数字
//D[i][j]=D[i-1][j]+array[i];

//情况2：不选择当前数字
//D[i][j]=D[i-1][j];
//***不妨填个表先看看，分析一下值出现的原理***

//设置值：
//D[0][0]=0   D[i][0]=0   D[0][j]=0

//画表：
/*

i/j          0  1  2  3  4  5  6  7  8        
           
0    0     0   0  0  0  0  0  0  0  0
1    2     0   0  1  0  1  0  1  0  1
2    3     0   0  1  1  1  1  2  1  2
3    5     0   0  1  1  1  2  2  2  3

//分解：
//情况1：当和值j小于当前数字array[i]
//D[i][j]=max(0,D[i-1][j])

//情况3：当和值j对当前数字array[i]取余后能得到0
//D[i][j]=D[i-1][j]+1;

//情况2：当和值j 减去若干个当前数字array[i]后得到的数字
   在前一个数字array[i-1]对应的状态中的值
//D[i][j]+=...;

情况1与2,3是else关系，情况2,3是并行关系
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int CalCombinations(vector<int> input,int k);

int main()
{
    vector<int> dataInput{2,3,5};
    int k = 8;

    cout << CalCombinations(dataInput,k);

    return 0;
}
int CalCombinations(vector<int> input, int k)
{
    if (input.empty() || k <= 0)
        return 0;

    //先进行排序
    sort(input.begin(), input.end());

    vector<vector<int>> dp(input.size()+1,vector<int>(k+1,0));

    for (int i = 1; i <= input.size(); ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            if (input[i - 1] > j)
            {
                dp[i][j] = dp[i - 1][j];
                continue;
            } 

            //继承上一个状态
            dp[i][j] = dp[i - 1][j];

            //这段代码块写错，不好写
            /*
            for (int k = 1; k * input[i - 1] <= j; ++k)
            {
                if (find(input.begin(), input.begin()+i-1, j - k * input[i - 1]) != input.end())
                {
                    dp[i][j] += dp[i - 1][j - k*input[i - 1]];
                    break;
                }
            }
            */
            //想复杂了
            //若和值为8，遍历到数字3，如何让dp[2][8]=2
            // 3，3，2的组合，应该找dp[1][2]

            for (int k = 1; k * input[i - 1] <= j; ++k)
            {
               if(dp[i-1][j-k*input[i-1]]!=0)
               {
                   dp[i][j] += dp[i - 1][j - k * input[i - 1]];
               }
            }

            if ( j % input[i - 1] == 0)
            {
                dp[i][j] += 1;
            }
        }
    }

    for (auto x : dp)
    {
        for (auto y : x)
        {
            cout << right << setw(3) << y;
        }

        cout << endl;
    }

    return dp[input.size()][k];
}
#endif
//改进的点：
//由于某个元素是可以重复取用的，所以应该可以优化为（对比一下完全背包）
//在【当前状态下】，取该元素，然后加上和值k减去该元素的值后对应的状态的值
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int CalCombinations(vector<int> input, int k);

int main()
{
    vector<int> dataInput{ 2, 3, 5 };
    int k = 8;

    cout << CalCombinations(dataInput, k);

    return 0;
}

int CalCombinations(vector<int> input, int k)
{
    if (input.empty() || k <= 0)
        return 0;

    sort(input.begin(), input.end());

    vector<vector<int>> dp(input.size() + 1, vector<int>(k + 1, 0));

    // Base case: there is exactly one way to make the sum 0, which is using no elements.
    for (int i = 0; i <= input.size(); ++i)
        dp[i][0] = 1;

    for (int i = 1; i <= input.size(); ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            dp[i][j] = dp[i - 1][j]; // Case 1: exclude current element

            if (j >= input[i - 1])
            {
                dp[i][j] += dp[i][j - input[i - 1]]; // Case 2: include current element
            }
        }
    }

    // Uncomment the following block to print the dp array for debugging
    
    for (auto x : dp)
    {
        for (auto y : x)
        {
            cout << right << setw(3) << y;
        }
        cout << endl;
    }
    

    return dp[input.size()][k];
}
#endif



//动态规划解决单序列问题
#if 1

#endif


//动态规划解决双序列问题
//面试题96：最长公共子序列(两个子序列在序列中可以不连续)
#if 0
//有S1：ABCBDAB   S2：BDCABC  
//定义：
//D[i][j] 为 S1的前i个字符与S2的前j个字符的最长公共子序列
//求的是D[7][6]=?

//动态规划就是考虑在当前状态下做什么决策

//分解：
//情况1：末尾字符相同  S1[i]==S2[j]
//比如说，在S1的第i个字符为x，在S2的第j个字符也为x，那么
//S1的前i个字符和S2的前j个字符【至少】找到了1个子序列
//那么得到S1的前i个字符，和S2的前j个字符的最长公共子序列可以写作
// D[i][j]=D[i-1][j-1]+1;//即前面的结果的基础上加1

//情况2：末尾字符不相同  S1[i]!=S2[j]
//比如说，在S1的第i个字符为x，在S2的第j个字符为y，那么
//可以不考虑S1的第i个字符，或可以不考虑S2的第j个字符
//那么得到S1的前i个字符，和S2的前j个字符的最长公共子序列可以写作
// D[i][j]=max(D[i-1][j], D[i][j-1]);

//可以又不考虑S1的第i个字符，也不考虑S2的第j个字符吗？
//这种行为完全可以替换为情况2的
// 先不考虑第(S1的)i或(S2的)j个字符再不考虑第(S2的)j或(S1的)i个字符
//所以以上两种情况已经囊括了所有情况

//设置值：
//D[0][0]=0   D[i][0]=0    D[0][j]=0   
//理解：
//前0个字符与前0/i/j个字符的最长公共子序列为0

//画表：
/*

i/j           0  1  2   3  4  5  6  
              0  B  D  C  A  B  C
0        0  0  0  0  0   0  0  0    D[0][j]=0
1        A  0
2        B  0
3        C  0
4        B  0
5        D  0
6        A  0
7        B  0
           D[i][0]=0


i/j           0  1  2   3  4  5  6
              0  B  D  C  A  B  C
0        0  0  0  0   0   0  0  0    
1        A  0  0  0   0   1  1  1
2        B  0  1  1   1   1  2  2
3        C  0  1  1   2   2  2  3
4        B  0  1  1   2   2  3  3 
5        D  0  1  2   2   2  3  3
6        A  0  1  2   2   3  3  3
7        B  0  1  2   2   3  4  4

最长公共子序列可能有多组：对于该例子，从D[7][5]的4开始回推
有子序列BDAB、BCAB
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int FindLCS(const string& S1,const string& S2);

int main()
{
    string S1{"ABCBDAB"};
    string S2{"BDCABC"};

    try
    {
        cout << FindLCS(S1,S2);
    }
    catch (exception& e)
    {
        e.what();
    }

    return 0;
}

int FindLCS(const string& S1, const string& S2)
{
    if (S1.empty() || S2.empty())
        throw exception("Invalid Data!");

    vector<vector<int>> dp(S1.size()+1, vector<int>(S2.size()+1, 0));
    //***理解***
    //+1是为了处理边界条件

    for (int i = 1; i <= S1.size(); ++i)
    {
        for (int j = 1; j <= S2.size(); ++j)
        {
            if (S1[i - 1] == S2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }

    return dp[S1.size()][S2.size()];
}
#endif
//扩展：
//求最长公共子串(两个子序列在序列中要连续
#if 1

#endif

