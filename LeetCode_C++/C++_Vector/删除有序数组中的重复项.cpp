给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int num=nums.size();
        int flag=0;
        for(int i=0;i<num;i++)
        {
            int j=i+1;
            while(j<nums.size()&&nums[i]==nums[j])
            {
                j++;
                num--;
                flag++;
            }
            int tmp=i+1;
            while(j<nums.size())
            {
                nums[tmp]=nums[j];
                tmp++;
                j++;
            }
            for(int k=0;k<flag;k++)
            {
                nums.pop_back();
            }
            flag=0;
        }
        return num;
    }
};

方法二:
int removeDuplicates(int* nums, int numsSize){
    int i=0;
    if(numsSize==0)
    {
        return 0;
    }
   for(int j=0;j<numsSize;j++)
   {
       if(nums[i]!=nums[j])
       {
           i++;
           nums[i]=nums[j];
       }
   }
   return i+1;
}