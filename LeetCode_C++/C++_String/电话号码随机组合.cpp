����һ������������?2-9?���ַ����������������ܱ�ʾ����ĸ��ϡ��𰸿��԰� ����˳�� ���ء�

�������ֵ���ĸ��ӳ�����£���绰������ͬ����ע�� 1 ����Ӧ�κ���ĸ��

 

string num_str[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

class Solution {
public:
    void _letterCombinations(string &digits,int i,string s,vector<string>&ret)
    {
        if(i==digits.size())
        {
            ret.push_back(s);
            return ;
        }
        int num=digits[i]-'0';
        string& tmp=num_str[num];
        for(int j=0;j<tmp.size();j++)
        {
            _letterCombinations(digits,i+1,s+tmp[j],ret);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if(digits.empty())
        {
            return ret;
        }
        string s;//��ŵݹ����ַ���
        int i=0;//��¼�ݹ�Ĳ���
        _letterCombinations(digits,i,s,ret);
        return ret;
    }
};
