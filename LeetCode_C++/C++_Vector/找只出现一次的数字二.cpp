����һ���������� nums������ǡ��������Ԫ��ֻ����һ�Σ���������Ԫ�ؾ��������Ρ� 

�ҳ�ֻ����һ�ε�������Ԫ�ء�����԰� ����˳�� ���ش𰸡�

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