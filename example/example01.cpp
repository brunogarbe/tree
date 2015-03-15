#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <iterator>
using namespace std;

#include "tree.hpp"

struct print
{
	void operator ()(int x)
	{
		cout << x << endl;
	}
};

using namespace ext;

int main()
{
	tree<int> ts;
	tree<int>::iterator root = ts.set_root(0);

	cout << *root << endl;
	tree<int>::iterator nx;	
	tree<int>::iterator n1 = ts.insert_child(root, 1);
	tree<int>::iterator n2 = ts.insert_child(root, 2);
	tree<int>::iterator n3 = ts.insert_child(root, 3);
	//auto n3 = ts.insert_child(root, 3);

	cout << "n1: " << *n1 << endl;
	cout << "n2: " << *n2 << endl;
	cout << "n3: " << *n3 << endl;
	//cout << "nx: " << *nx << endl;

	tree<int>::preorder_iterator itn;
	tree<int>::preorder_iterator itb = std::begin(ts);
	tree<int>::preorder_iterator ite = std::end(ts);
	//tree<int>::preorder_iterator it2 = n2;

	cout << *itb << endl;

	cout << "iterator for loop through custom<int>" << endl;
	for(auto j = std::begin(ts); j != std::end(ts); ++j)
		cout << *j << endl;
	cout << endl;

	// for_each loop through containers
	cout << "for_each loop through vector<int>" << endl;
	for_each(std::begin(ts), std::end(ts), print());
	cout << endl;

	// range loop
	for(auto e : ts)
	{
		cout << "x: " << e << endl;
	}

	tree<int>::preorder_iterator cResult;
	cout << "find 40 through custom<int>: ";
	cResult = find(std::begin(ts), std::end(ts), 2);
	cout << *cResult << endl;
	cout << endl;

	cout << "max_element through custom<int>: ";
	cResult = max_element(std::begin(ts), std::end(ts));
	cout << *cResult << endl;
	cout << endl;

	return 0;
}
