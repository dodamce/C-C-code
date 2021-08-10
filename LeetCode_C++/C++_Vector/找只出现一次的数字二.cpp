给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 

找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。

class Solution {
public:
    int singleNumber(vector<int>& nums) 
    {
    sort(nums.begin(), nums.end());
	int size = nums.size();
	for (int i = 0; i < size; i+=3)
	{
		int j = i;
		if (j + 1 == nums.size())
		{
			return nums[j];
		}
		if (nums[j + 1] != nums[i])
			return nums[i];
	}
    return NULL;
    }
};