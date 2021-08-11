数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组[1,2,3,2,2,2,5,4,2]。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。你可以假设数组是非空的，并且给定的数组总是存在多数元素。1<=数组长度<=50000，0<=数组元素<=10000

方法一:
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

方法二:

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        
        sort(numbers.begin(),numbers.end());
        //所求的元素一定在数组的中间
        int mid=numbers[numbers.size()/2];
        return mid;
    }
};

方法三:

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