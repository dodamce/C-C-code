����һ���������� nums ������ ԭ�� ɾ���ظ����ֵ�Ԫ�أ�ʹÿ��Ԫ�� ֻ����һ�� ������ɾ����������³��ȡ�

��Ҫʹ�ö��������ռ䣬������� ԭ�� �޸��������� ����ʹ�� O(1) ����ռ����������ɡ�

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

������:
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