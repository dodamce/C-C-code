#include"My_priority _queue.h"

using namespace std;

int main()
{
	My::priority_queue<int>q;
	q.push(5);
	q.push(3);
	q.push(7);
	q.push(1);
	q.push(2);
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}
	return 0;
}