#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <iterator>
using namespace std;

#include "../src/tree.hpp"

// functor to print the output of the int
struct print
{
    void operator ()(int x)
    {
        cout << x << endl;
    }
};



// std::for_each
/*
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
    for (; first != last; ++first) {
        f(*first);
    }
    return f;
}

The behavior of this template function is equivalent to:

template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  return fn;      // or, since C++11: return move(fn);
}

*/

using namespace ext;

// main entry point to program
int main()
{
	// Constructors
	/*
	typedef std::vector<std::string> str_vec_t;
str_vec_t v1;                       // create an empty vector
str_vec_t v2(10);                   // 10 copies of empty strings
str_vec_t v3(10, "hello");          // 10 copies of the string
                                    // "hello"
str_vec_t v4(v3);                   // copy ctor
 
    std::list<std::string> sl;      // create a list of strings
                                    // and populate it
    sl.push_back("cat");
    sl.push_back("dog");
    sl.push_back("mouse");
 
str_vec_t v5(sl.begin(), sl.end()); // a copy of the range in
                                    // another container
                                    // (here, a list)
 
v1 = v5;                            // will copy all elements
                                    // from v5 to v1
	*/
	
	
	// Predefined iterators
	/*
	std::vector<int> v;
v.push_back(999);
std::vector<int>::reverse_iterator r = v.rbegin();
std::vector<int>::iterator i = r.base(); // will point to the last
                                         // element in the sequence
	*/
	
	// Comparison operations
	/*
	std::vector<int> v1, v2;
//...
if(v1 == v2) ...
	*/
	
	// Swapping contents
	/*
	std::vector<int> v;
//...
v.clear();
v.swap(std::vector<int>(v));
	*/
	
	tree<int> ts;
	tree_iterator<int> root = ts.set_root(0);
	
	/*
	cout << *root << endl;
	tree_iterator<int> n1 = ts.add_node(root, 1);
	tree_iterator<int> n2 = ts.add_node(root, 2);
	auto n3 = ts.add_node(root, 3);
	
	cout << *n1 << endl;
	cout << *n2 << endl;
	cout << *n3 << endl;
	

	preorder_iterator<int> it1(&ts);
	it1 = root;	
	cout << *it1 << endl;
	
	preorder_iterator<int> itb = std::begin(ts);
	auto ite = std::end(ts);

	cout << *itb << endl;
	//cout << *ite << endl;
	
	
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

	preorder_iterator<int> cResult;
    cout << "find 40 through custom<int>: ";
    cResult = find(std::begin(ts), std::end(ts), 2);
    cout << *cResult << endl;
    cout << endl;

	 cout << "max_element through custom<int>: ";
    cResult = max_element(std::begin(ts), std::end(ts));
    cout << *cResult << endl;
    cout << endl;
	
*/
    return 0;
}
