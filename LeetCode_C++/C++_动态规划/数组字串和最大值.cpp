����һ���������飬������������Ҳ�и����������е�һ������������������һ�������顣������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�Ϊ O(n).
ʾ��1
���룺
[1,-2,3,10,-4,7,2,-5]
����ֵ��
18
˵����
���������Ϊ{1,-2,3,10,��4,7,2,һ5}��������������Ϊ{3,10,һ4,7,2}��������Ϊ��������ĺ� 18�� 

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
       vector<int> ret;
        ret.resize(array.size()+1);
        for(int i=1;i<ret.size();i++)
        {
            ret[i]=max(ret[i-1]+array[i-1],array[i-1]);
        }
        int max=ret[1];
        for(int i=1;i<ret.size();i++)
        {
            if(ret[i]>max)
            {
                max=ret[i];
            }
        }
        return max;
    }
};