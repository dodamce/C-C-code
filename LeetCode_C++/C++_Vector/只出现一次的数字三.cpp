给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 

找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> ret;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();)
        {
            int j=i;
            if(j+1>=nums.size())
            {
                ret.push_back(nums[j]);
                return ret;
            }
            if(nums[i]!=nums[j+1])
            {
                ret.push_back(nums[i]);
                i++;
            }
            else
            {
                i+=2;
            }
        }
        return ret;
    }
};

方法二:按照位的不同分成两组
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int sum=0;
        for(int i=0;i<nums.size();i++)
        {
            sum=sum^nums[i];
        }
        int tmp=1;
        int n1=0;int n2=0;
        //找到这两个数字不相同的一位
        while((sum&tmp)==0)
        {
            tmp=tmp<<1;
        }
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]&tmp)
            {
                n1=n1^nums[i];
            }
            else
            {
                n2=n2^nums[i];
            }
        }
        vector<int>ret;
        ret.push_back(n1);
        ret.push_back(n2);
        return ret;
    }
};