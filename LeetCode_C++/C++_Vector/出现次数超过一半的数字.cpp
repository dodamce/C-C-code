��������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ�������֡���������һ������Ϊ9������[1,2,3,2,2,2,5,4,2]����������2�������г�����5�Σ��������鳤�ȵ�һ�룬������2������Լ��������Ƿǿյģ����Ҹ������������Ǵ��ڶ���Ԫ�ء�1<=���鳤��<=50000��0<=����Ԫ��<=10000

����һ:
int SortInt(const void*a,const void*b)
{
    return *(int*)a-*(int*)b;
}

int MoreThanHalfNum_Solution(int* numbers, int numbersLen ) {
    // write code here
    int arr[50000]={0};
    for(int i=0;i<numbersLen;i++)
    {
        arr[numbers[i]]++;
    }
    int max=0;
    int j=0;
    for(j=1;j<50000;j++)
    {
        if(arr[j]>arr[max])
        {
            max=j;
        }
    }
    return max;
}

������:

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        
        sort(numbers.begin(),numbers.end());
        //�����Ԫ��һ����������м�
        int mid=numbers[numbers.size()/2];
        return mid;
    }
};

������:

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int count=0;
        int val=0;
        for(int i=0;i<numbers.size();i++)
        {
            if(count==0)
            {
                val=numbers[i];
                count++;
            }
            else
            {
                if(numbers[i]==val)
                {
                    ++count;
                }
                else
                {
                    --count;
                }
            }
        }
        return val;
    }
};