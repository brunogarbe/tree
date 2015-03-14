/**
 * @file table.hpp
 * @brief An STL-like C++ tree class.
 * @author  Bruno Garbe Jr. (meia) <brunogarbe@gmail.com>
 * @version 0.1a
 * @date Mar 2015
 * @bug No known bugs.
 *
 * @section LICENSE
 *
 * Copyright (c) 2014, Bruno Garbe Jr.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL BRUNO GARBE JUNIOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @section DESCRIPTION
 *
 * The time class represents a moment of time.
 */

#ifndef EXT_TREE_HPP
#define EXT_TREE_HPP

#define EXT_TREE_MAJOR_VERSION 1
#define EXT_TREE_MAJOR_VERSION_STR "1"

#define EXT_TREE_MINOR_VERSION 1
#define EXT_TREE_MINOR_VERSION_STR "1"

#define EXT_TREE_BUILD_NUMBER 53
#define EXT_TREE_BUILD_NUMBER_STR "53"

#define EXT_TREE_VERSION_STR EXT_TREE_MAJOR_VERSION_STR "." \
	EXT_TREE_MINOR_VERSION_STR "." EXT_TREE_BUILD_NUMBER_STR

// for assert
#include <cassert>

#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <iterator>
using namespace std;

namespace ext
{
// Forward declaration of the classes
template<typename t_type, class t_allocator> class tree_node;
template<typename t_type, class t_allocator> class tree;
template<typename t_type, class t_allocator> class tree_iterator;
template<typename t_type, class t_allocator> class preorder_iterator;


// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
// Tree node

/*! \brief A test class.
    A more detailed class description.
*/

template <class t_type, class t_allocator = std::allocator<t_type> >
class tree_node
{
public:
	typedef t_type 									value_type;
    typedef t_type* 								pointer;
    typedef t_type& 								reference;
	typedef const t_type* 							const_pointer;
    typedef const t_type& 							const_reference;
	typedef t_allocator 							allocator_type;    
    typedef tree_node<value_type, allocator_type> 	node_type;
    typedef tree_node<value_type, allocator_type>* 	node_pointer;

public:
    pointer mv_data;

public:
    node_pointer parent;
    node_pointer first_child;
    node_pointer last_child;
    node_pointer prev_sibling;
    node_pointer next_sibling;

    /// Allocator.
    allocator_type mv_allocator;

public:
    // 	Constructors:
    explicit tree_node(const t_type& val = t_type())
        :	parent(nullptr),
            first_child(nullptr),
            last_child(nullptr),
            prev_sibling(nullptr),
            next_sibling(nullptr)
    {
        mv_data = mv_allocator.allocate(1);
        mv_allocator.construct(mv_data, val);
    }

    // Destructor
    ~tree_node()
    {
        mv_allocator.destroy(mv_data);
        mv_allocator.deallocate(mv_data, 1);
    }

public:
    pointer operator->()
    {
        return mv_data;
    }

    const_pointer operator->() const
    {
        return mv_data;
    }

    reference operator*()
    {
        assert (mv_data != nullptr);
        return *mv_data;
    }

    const_reference operator*() const
    {
        assert (mv_data != nullptr);
        return *mv_data;
    }

}; // end of class tree_node



// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
// Tree node

/*! \brief A test class.
    A more detailed class description.
*/

template <class t_type, class t_allocator = std::allocator<t_type> >
class tree_iterator
{
public:
    // Member typedefs
	typedef t_type 									value_type;
    typedef t_type* 								pointer;
    typedef t_type& 								reference;
	typedef const t_type* 							const_pointer;
    typedef const t_type& 							const_reference;
	typedef t_allocator 							allocator_type;    
    typedef std::size_t 							size_type;
    typedef std::ptrdiff_t 							difference_type;
	typedef std::bidirectional_iterator_tag 		iterator_category;

private:
	tree_node<t_type, t_allocator>* mp_node;
	
public:

    tree_iterator(void)
		: mp_node(nullptr)
	{}
	
    ~tree_iterator(void)
	{}
	
    // Type conversion methods allow const_iterator and iterator to be converted
    //const_iterator constify(void) const;
    //iterator deconstify(void) const;
    //bool operator == (const this_iterator& r) const;
    //bool operator != (const this_iterator& r) const;
    //bool operator < (const this_iterator& r) const;

    reference operator*(void) const
	//	throw(null_dereference,end_dereference)
	{
		//this->assert_valid();
		return *(mp_node->mv_data);
	}

    //pointer operator->(void) const
    //throw(null_dereference,end_dereference);

    friend class tree<t_type, t_allocator>;
	friend class preorder_iterator<t_type, t_allocator>;
	/*
    friend class tree_prefix_iterator<T,TRef,TPtr>;
    friend class tree_postfix_iterator<T,TRef,TPtr>;
*/
public:
    // Note: I had to make this public to get round a problem implementing persistence - it should be private
    // you cannot create a valid iterator except by calling an tree method that returns one
    // constructor used by tree to create a non-null iterator
    explicit tree_iterator(tree_node<t_type, t_allocator>* node)
		: mp_node(node)
	{}
	
    // constructor used by tree to create an end iterator
    //explicit tree_iterator(const tree<T>* owner);
    
	// used to create an alias of an iterator
    //explicit tree_iterator(const safe_iterator<tree<T>, tree_node<T> >& iterator);
};


// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
// Tree node

/*! \brief A test class.
    A more detailed class description.
*/

/*
Member Functions:

	Constructors
	Destructor
	operator=

	Capacity:
		size
		empty

	Modifiers:
		insert
		erase
		swap
		clear
		emplace ?
		
	Allocator
		get_allocator

Non-member function overloads

		relational operators
		swap

*/


// Declare a custom container
template<typename t_type, class t_allocator = std::allocator<t_type> >
class tree
{
public:
    // Member typedefs
	typedef t_type 									value_type;
    typedef t_type* 								pointer;
    typedef t_type& 								reference;
	typedef const t_type* 							const_pointer;
    typedef const t_type& 							const_reference;
	typedef t_allocator 							allocator_type;    
    typedef std::size_t 							size_type;
    typedef tree_node<value_type, allocator_type> 	node_type;
    typedef tree_node<value_type, allocator_type>* 	node_pointer;

public:
    node_pointer mv_root;

public:
    tree()
        : mv_root(nullptr)
    {}

    ~tree()
    {}

    size_type size() const
    {
		assert (0 == 1);
        return 0;
    }

    size_type max_size() const
    {
		assert (0 == 1);
        return 16;
    }

    bool empty() const
    {
        assert (0 == 1);
        return (1 > 0 ? false : true);
    }
	
	tree_iterator<value_type, allocator_type> set_root(value_type x)
    {
        if(mv_root != nullptr)
        {
            ;//TODO implement if root already defined
            cout << "error" << endl;
        }

        mv_root = new node_type(x);

        return tree_iterator<value_type, allocator_type>(mv_root);
    }

	
	template<typename t_iterator>
	t_iterator add_node(const t_iterator& n_parent, value_type x)
    {

        node_pointer n = new node_type(x);
        n->parent = n_parent.mp_node;

        if(n_parent.mp_node->first_child == nullptr)
        {
            n_parent.mp_node->first_child = n;
        }
        else
        {
            node_pointer temp = n_parent.mp_node->first_child;
            while(temp->next_sibling != nullptr)
            {
                temp = temp->next_sibling;
            }
            temp->next_sibling = n;
        }

        //return n;
		return tree_iterator<value_type, allocator_type>(n);
    }

}; // end of class tree


// Declare a custom bidirectional iterator
template<typename t_type, class t_allocator = std::allocator<t_type> >
class preorder_iterator
{
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef t_type                                           value_type;
    typedef value_type &                     reference;
    typedef value_type   *                          pointer;
    typedef int                                           difference_type;

	typedef tree<t_type, t_allocator> tree_type;

public:
	tree_type* mv_tree;
    typename tree_type::node_pointer mv_position;

	stack<typename tree_type::node_pointer> mv_stack;

public:
    preorder_iterator()
		: mv_tree(nullptr), mv_position(nullptr)
    {}

	preorder_iterator(tree_type* n_tree)
        : mv_tree(n_tree), mv_position(nullptr)
    {}
	
	// Copy Constructor
	
/*
    preorder_iterator(_Ty *l_Ptr)
    {
        // copy constructor
        m_Ptr = l_Ptr;
    }
*/
    reference operator*() const
    {
        // return designated object
        return **mv_position;
    }

	void mv_incrementIterator()
    {
        if(!mv_stack.empty())
        {
            this->mv_position = mv_stack.top();
            mv_stack.pop();
            // right
            if (this->mv_position->next_sibling != nullptr)
                mv_stack.push(this->mv_position->next_sibling);

            // left
            if (this->mv_position->first_child != nullptr)
                mv_stack.push(this->mv_position->first_child);
        }
        else
        {
			this->mv_position = nullptr;
        }
    }

    preorder_iterator& operator++()
    {
        mv_incrementIterator();
        return (*this);
    }

    preorder_iterator& operator--()
    {
        mv_incrementIterator();
        return (*this);
    }
/*
    custom_iterator operator++(int)
    {
        // postincrement
        custom_iterator _Tmp = *this;
        ++*this;
        return (_Tmp);
    }

    custom_iterator operator--(int)

    {
        // postdecrement
        custom_iterator _Tmp = *this;
        --*this;
        return (_Tmp);
    }
*/
    bool operator==(const tree_iterator<t_type, t_allocator>& _Right) const
    {
        return (this->mv_position == _Right.mp_node);
    }
	
	bool operator==(const preorder_iterator<t_type, t_allocator>& _Right) const
    {
        return (this->mv_position == _Right.mv_position);
    }

    bool operator!=(const tree_iterator<t_type, t_allocator>& _Right) const
    {
        // test for iterator inequality
        return (!(this->mv_position == _Right.mp_node));
    }
	
	bool operator!=(const preorder_iterator<t_type, t_allocator>& _Right) const
    {
        // test for iterator inequality
        return (!(this->mv_position == _Right.mv_position));
    }

	//void operator=(const typename tree_type::node_pointer n_address )
	void operator=(const tree_iterator<t_type, t_allocator>& n_node )
    {
        this->mv_position = n_node.mp_node;

        // A common idiom for clearing standard containers is swapping with an empty
        // version of the container:
        std::stack<typename tree_type::node_pointer>().swap(mv_stack);
        mv_stack.push(this->mv_position);

        mv_incrementIterator();
    }
	
	void operator=(const typename tree<t_type, t_allocator>::node_pointer& n_node )
    {
        this->mv_position = n_node;

        // A common idiom for clearing standard containers is swapping with an empty
        // version of the container:
        std::stack<typename tree_type::node_pointer>().swap(mv_stack);
        mv_stack.push(this->mv_position);

        mv_incrementIterator();
    }
};


} // end of namespace ext

// start the namespace std for the overload of std::begin and std::end
namespace std
{

template<typename t_type, class t_allocator>
ext::preorder_iterator<t_type, t_allocator> begin(ext::tree<t_type, t_allocator>& np_tree)
{
	ext::preorder_iterator<t_type, t_allocator> it(&np_tree);
	it = np_tree.mv_root;
    return it;
}

template<typename t_type, class t_allocator>
ext::preorder_iterator<t_type, t_allocator> end(ext::tree<t_type, t_allocator>& np_tree)
{
	ext::preorder_iterator<t_type, t_allocator> it(&np_tree);
	//it = nullptr;
	it.mv_position = nullptr;
    return it;
}


} // end of namespace std
#endif
