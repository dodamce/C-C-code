����һ���������� nums������ǡ��������Ԫ��ֻ����һ�Σ���������Ԫ�ؾ��������Ρ� 

�ҳ�ֻ����һ�ε�������Ԫ�ء�����԰� ����˳�� ���ش𰸡�

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

������:����λ�Ĳ�ͬ�ֳ�����
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
        //�ҵ����������ֲ���ͬ��һλ
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