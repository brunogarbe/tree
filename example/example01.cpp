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
#include "tree_util.hpp"

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


	// load the tree
    tree<string>* ts2 = load_tree_file<string>("../test/out.txt");

    // print the version
    cout << EXT_TREE_VERSION_STR << endl;


	// preorder iterator
    cout << "@ ";
	//preorder_iterator<string> it(ts);
    for(tree<string>::preorder_iterator itp = std::begin(*ts2); itp != std::end(*ts2); ++itp)
    {
        cout << "" << *itp << " ";
    }
	cout << "!" << endl;

/*
    // parent iterator
    cout << "& ";
	parent_iterator<string> it2(ts);
    for(it2 = ts->begin(); it2 != ts->end(); ++it2)
    {
        cout << "" << *it2 << " ";
    }
	cout << "!" << endl;


    // level iterator
    cout << "$ ";
	levelorder_iterator<string> it3(ts);
    for(it3 = ts->begin(); it3 != ts->end(); ++it3)
    {
        cout << "" << *it3 << " ";
    }
	cout << "!" << endl;


    // level iterator
    cout << "% ";
    postorder_iterator<string> it4(ts);
    for(it4 = ts->mv_root; it4 != ts->mv_dummy_end; ++it4)
    {
        cout << "" << *it4 << " ";
    }
	cout << "!" << endl;


	//cout << ts->depth(ts->preorder_last_node()) << endl;
*/
    save_tree_file<string>("teste.txt", ts2);

	return 0;
}
