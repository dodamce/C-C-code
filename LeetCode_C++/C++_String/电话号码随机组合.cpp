给定一个仅包含数字?2-9?的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

 

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
        string s;//存放递归后的字符串
        int i=0;//记录递归的层数
        _letterCombinations(digits,i,s,ret);
        return ret;
    }
};
