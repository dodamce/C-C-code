#include<iostream>
#include<vector>

using namespace std; 

void TestVector1()
{
  vector<int>v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  for(size_t i=0;i<v.size();i++)
  {
    cout<<v[i]<<" ";
  }
  cout <<endl;
  vector<int>::iterator it=v.begin();
  while(it!=v.end())
  {
    cout<<*it<<" ";
    it++;
  }
  cout<<endl;
  for(auto e:v)
  {
    cout<<e<<endl;
  }
}

int main()
{
  TestVector1();
  return 0;
}
