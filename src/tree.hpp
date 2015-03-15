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
 * Copyright (c) 2015, Bruno Garbe Jr.
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

#define EXT_TREE_MAJOR_VERSION 0
#define EXT_TREE_MAJOR_VERSION_STR "0"

#define EXT_TREE_MINOR_VERSION 1
#define EXT_TREE_MINOR_VERSION_STR "1"

#define EXT_TREE_BUILD_NUMBER 10
#define EXT_TREE_BUILD_NUMBER_STR "10"

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

// Forward declaration of the classes
namespace ext
{
template<typename t_type, class t_allocator> class tree;

namespace detail
{
template<typename t_type, class t_allocator> class tree_node;
template<typename t_type, class t_allocator> class tree_iterator;
template<typename t_type, class t_allocator> class preorder_tree_iterator;
template<typename t_type, class t_allocator> class postorder_tree_iterator;
template<typename t_type, class t_allocator> class levelorder_tree_iterator;
} // end of namespace detail

template<typename t_type, class t_allocator>
ext::detail::postorder_tree_iterator<t_type, t_allocator> begin_post(ext::tree<t_type, t_allocator>& np_tree);

template<typename t_type, class t_allocator>
ext::detail::postorder_tree_iterator<t_type, t_allocator> end_post(ext::tree<t_type, t_allocator>& np_tree);

template<typename t_type, class t_allocator>
ext::detail::levelorder_tree_iterator<t_type, t_allocator> begin_level(ext::tree<t_type, t_allocator>& np_tree);

template<typename t_type, class t_allocator>
ext::detail::levelorder_tree_iterator<t_type, t_allocator> end_level(ext::tree<t_type, t_allocator>& np_tree);

} // end of namespace ext

namespace std
{
template<typename t_type, class t_allocator>
ext::detail::preorder_tree_iterator<t_type, t_allocator> begin(ext::tree<t_type, t_allocator>& np_tree);

template<typename t_type, class t_allocator>
ext::detail::preorder_tree_iterator<t_type, t_allocator> end(ext::tree<t_type, t_allocator>& np_tree);

} // end of namespace std



namespace ext
{

namespace detail
{

// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template <class t_type, class t_allocator = std::allocator<t_type> >
class tree_node
{
public:
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;

	typedef 	tree_node<value_type, allocator_type> 	node_type;

	friend class tree<value_type, allocator_type>;
	friend class detail::tree_iterator<value_type, allocator_type>;
	friend class detail::preorder_tree_iterator<value_type, allocator_type>;
	friend class detail::postorder_tree_iterator<value_type, allocator_type>;
	friend class detail::levelorder_tree_iterator<value_type, allocator_type>;


private:
	node_type* 			parent;
	node_type* 			first_child;
	node_type* 			last_child;
	node_type* 			prev_sibling;
	node_type* 			next_sibling;
	pointer 			mv_data;
	allocator_type 		mv_allocator;

private:
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

	tree_node(const tree_node& n_copy) = delete;

	tree_node& operator= (const tree_node& n_other) = delete;

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

} // end of namespace detail


// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template<typename t_type, class t_allocator = std::allocator<t_type> >
class tree
{
public:
	// Member typedefs
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;
	typedef 		std::size_t 	size_type;

	typedef 	tree<value_type, allocator_type> 								tree_type;
	typedef 	detail::tree_node<value_type, allocator_type> 					node_type;
	typedef 	detail::tree_node<value_type, allocator_type>* 					node_pointer;
	typedef 	detail::tree_iterator<value_type, allocator_type> 				iterator;
	typedef 	detail::preorder_tree_iterator<value_type, allocator_type> 		preorder_iterator;
	typedef 	detail::postorder_tree_iterator<value_type, allocator_type> 	postorder_iterator;
	typedef 	detail::levelorder_tree_iterator<value_type, allocator_type> 	levelorder_iterator;


public:
	node_pointer mv_root;

public:
	// Constructors, destructors and operator=
	explicit tree()
		: mv_root(nullptr)
	{}

	explicit tree(const t_type& val)
		: mv_root(val)
	{}

	explicit tree(const tree_type& copy_from_me)
		: mv_root(nullptr)
	{}

	explicit tree(tree&& other)
		: tree() // initialize via default constructor, C++11 only
	{
		swap(*this, other);
	}

	tree_type& operator= (tree_type s) // the pass-by-value parameter serves as a temporary
	{
		s.swap (*this); // Non-throwing swap
		return *this;
	}

	~tree()
	{}

public:
	// Allocator
	allocator_type get_allocator() const noexcept
	{
		//assert (0 == 1);
		return mv_root->mv_allocator;
	}

	// Capacity methods
	size_type size() const
	{
		//assert (0 == 1);
		return 0;
	}

	bool empty() const
	{
		//assert (0 == 1);
		return true;
	}

	//Modifiers:
	void clear()
	{
		assert (0 == 1);
	}

	void swap(tree_type& first)
	{
		assert (0 == 1);
	}

	iterator set_root(value_type x)
	{
		if(mv_root != nullptr)
		{
			;//TODO implement if root already defined
			cout << "error" << endl;
		}

		mv_root = new node_type(x);

		return iterator(mv_root, this);
	}

	iterator get_root()
	{
		return iterator(mv_root, this);
	}


	template<typename t_iterator>
	t_iterator insert_child(const t_iterator& n_parent, value_type x)
	{
		node_pointer n = new node_type(x);
		n->parent = n_parent.mv_position;

		if(n_parent.mv_position->first_child == nullptr)
		{
			n_parent.mv_position->first_child = n;
		}
		else
		{
			node_pointer temp = n_parent.mv_position->first_child;
			while(temp->next_sibling != nullptr)
			{
				temp = temp->next_sibling;
			}
			temp->next_sibling = n;
		}

		return detail::tree_iterator<value_type, allocator_type>(n, this);
	}

	template<typename t_iterator>
	t_iterator insert_sibling(const t_iterator& n_sibling, value_type x)
	{
		assert (0 == 1);

		node_pointer n = new node_type(x);
		return detail::tree_iterator<value_type, allocator_type>(n, this);
	}

	template<typename t_iterator>
	size_type depth(t_iterator it)
    {
        node_pointer node_tmp = it;
        int counter = 0;
        while(node_tmp->parent != nullptr)
        {
            node_tmp = node_tmp->parent;
            counter++;
        }
        return counter;
    }

	template<typename t_iterator>
	void erase(const t_iterator& n_sibling)
	{
		assert (0 == 1);
	}

	template<typename t_iterator>
	void swap(const t_iterator& n_iter1, const t_iterator& n_iter2)
	{
		assert (0 == 1);
	}

}; // end of class tree


namespace detail
{

// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template <class t_type, class t_allocator = std::allocator<t_type> >
class tree_iterator
{
public:
	// Member typedefs
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;
	typedef 		std::size_t 	size_type;
	typedef 		std::ptrdiff_t	difference_type;
	//typedef std::bidirectional_iterator_tag 		iterator_category;

	typedef tree<value_type, allocator_type> 			tree_type;
	typedef tree_node<value_type, allocator_type> 		node_type;
	typedef tree_iterator<value_type, allocator_type> 	iterator_type;
	typedef tree_node<value_type, allocator_type>* 		node_pointer;

	friend class tree<t_type, t_allocator>;
	friend class detail::preorder_tree_iterator<t_type, t_allocator>;

public:
	node_type* mv_position;
	tree_type* mv_tree;

	explicit tree_iterator()
		: mv_position(nullptr), mv_tree(nullptr)
	{}

private:
	explicit tree_iterator(node_type* n_node, tree_type* n_tree)
		: mv_position(n_node), mv_tree(n_tree)
	{}

public:
	tree_iterator(const tree_iterator& n_copy) = default;
	tree_iterator(tree_iterator&& n_copy) = default;
	tree_iterator& operator= (const tree_iterator& n_other) = default;
	tree_iterator& operator= (tree_iterator&& n_other) = default;

	~tree_iterator()
	{}

public:
	// Type conversion methods allow const_iterator and iterator to be converted
	//const_iterator constify(void) const;
	//iterator deconstify(void) const;

	bool operator==(const iterator_type& n_iterator) const
	{
		return ( (mv_position == n_iterator.mv_position) and (mv_tree == n_iterator.mv_tree) );
	}

	bool operator!=(const iterator_type& n_iterator) const
	{
		// test for iterator inequality
		return (!this->operator!=(n_iterator));
	}

	pointer operator->()
	{
		assert (mv_position != nullptr);
		return (mv_position->mv_data);
	}

	const_pointer operator->() const
	{
		assert (mv_position != nullptr);
		return (mv_position->mv_data);
	}

	reference operator*()
	{
		assert (mv_position != nullptr);
		assert (mv_position->mv_data != nullptr);
		return *(mv_position->mv_data);
	}

	const_reference operator*() const
	{
		assert (mv_position != nullptr);
		assert (mv_position->mv_data != nullptr);
		return *(mv_position->mv_data);
	}

}; // end of class tree_iterator

} // end of namespace detail


namespace detail
{

// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template<typename t_type, class t_allocator = std::allocator<t_type> >
class preorder_tree_iterator
{
public:
	// Member typedefs
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;
	typedef 		std::size_t 	size_type;
	typedef 		std::ptrdiff_t 	difference_type;

	typedef std::forward_iterator_tag 						iterator_category;
	typedef tree<value_type, allocator_type> 				tree_type;
	typedef tree_node<value_type, allocator_type> 			node_type;
	typedef tree_node<value_type, allocator_type>* 			node_pointer;
	typedef preorder_tree_iterator<t_type, t_allocator> 	iterator_type;

	friend iterator_type std::begin<value_type, allocator_type>(tree_type& np_tree);
	friend iterator_type std::end<value_type, allocator_type>(tree_type& np_tree);

public:
	tree_type* mv_tree;
	node_pointer mv_position;
	stack<node_pointer> mv_stack;

public:
	preorder_tree_iterator()
		: mv_tree(nullptr), mv_position(nullptr)
	{}

private:
	preorder_tree_iterator(tree_type* n_tree)
		: mv_tree(n_tree), mv_position(nullptr)
	{}

	preorder_tree_iterator(tree_type* n_tree, node_pointer n_position)
		: mv_tree(n_tree), mv_position(n_position)
	{
		mv_stack.push(this->mv_position);
		mv_incrementIterator();
	}

public:
	pointer operator->()
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	const_pointer operator->() const
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	reference operator*()
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	const_reference operator*() const
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	preorder_tree_iterator& operator++()
	{
		mv_incrementIterator();
		return (*this);
	}

	preorder_tree_iterator operator++(int)
	{
		// postincrement
		preorder_tree_iterator _Tmp = *this;
		++(*this);
		return (_Tmp);
	}


	template <class t_iterator>
	bool operator==(const t_iterator& n_iterator) const
	{
		return ( mv_position == n_iterator.mv_position );
	}

	template <class t_iterator>
	bool operator!=(const t_iterator& n_iterator) const
	{
		return (mv_position != n_iterator.mv_position);
	}

	template <class t_iterator>
	void operator=(const t_iterator& n_node )
	{
		mv_position = n_node.mv_position;

		// A common idiom for clearing standard containers is swapping with an empty
		// version of the container:
		std::stack<typename tree_type::node_pointer>().swap(mv_stack);
		mv_stack.push(this->mv_position);

		mv_incrementIterator();
	}

private:
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
}; // end of class preorder_iterator

// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template<typename t_type, class t_allocator = std::allocator<t_type> >
class postorder_tree_iterator
{
public:
	// Member typedefs
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;
	typedef 		std::size_t 	size_type;
	typedef 		std::ptrdiff_t 	difference_type;

	typedef std::forward_iterator_tag 						iterator_category;
	typedef tree<value_type, allocator_type> 				tree_type;
	typedef tree_node<value_type, allocator_type> 			node_type;
	typedef tree_node<value_type, allocator_type>* 			node_pointer;
	typedef postorder_tree_iterator<t_type, t_allocator> 	iterator_type;

	friend iterator_type ext::begin_post<value_type, allocator_type>(tree_type& np_tree);
	friend iterator_type ext::end_post<value_type, allocator_type>(tree_type& np_tree);

public:
	tree_type* mv_tree;
	node_pointer mv_position;
	node_pointer mv_current;
	stack<node_pointer> mv_stack;

public:
	postorder_tree_iterator()
		: mv_tree(nullptr), mv_position(nullptr), mv_current(nullptr)
	{}

private:
	postorder_tree_iterator(tree_type* n_tree)
		: mv_tree(n_tree), mv_position(nullptr), mv_current(nullptr)
	{}

	postorder_tree_iterator(tree_type* n_tree, node_pointer n_position)
		: mv_tree(n_tree), mv_position(n_position), mv_current(n_position)
	{
		//mv_stack.push(this->mv_position);
		//mv_incrementIterator();

		//mv_current = n_address;
        //mv_position = n_address;

        while (mv_current != nullptr)
        {
            mv_stack.push(mv_current);
            mv_current = mv_current->first_child;
        }

        if(!mv_stack.empty() && mv_current == nullptr)
        {
            mv_position = mv_stack.top();
            mv_stack.pop();
            mv_current = mv_position->next_sibling;
        }
	}

public:
	pointer operator->()
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	const_pointer operator->() const
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	reference operator*()
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	const_reference operator*() const
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	postorder_tree_iterator& operator++()
	{
		//mv_incrementIterator();
		while (mv_current != nullptr)
        {
            mv_stack.push(mv_current);
            mv_current = mv_current->first_child;
        }

        if(!mv_stack.empty() && mv_current == nullptr)
        {
            mv_position = mv_stack.top();
            mv_stack.pop();
            mv_current = mv_position->next_sibling;
        }
        else
        {
            mv_position = nullptr;
        }
		return (*this);
	}

	postorder_tree_iterator operator++(int)
	{
		// postincrement
		postorder_tree_iterator _Tmp = *this;
		++(*this);
		return (_Tmp);
	}


	template <class t_iterator>
	bool operator==(const t_iterator& n_iterator) const
	{
		return ( mv_position == n_iterator.mv_position );
	}

	template <class t_iterator>
	bool operator!=(const t_iterator& n_iterator) const
	{
		return (mv_position != n_iterator.mv_position);
	}

	template <class t_iterator>
	void operator=(const t_iterator& n_node )
	{
		/*
		mv_position = n_node.mv_position;

		// A common idiom for clearing standard containers is swapping with an empty
		// version of the container:
		std::stack<typename tree_type::node_pointer>().swap(mv_stack);
		mv_stack.push(this->mv_position);

		mv_incrementIterator();
		*/
		mv_current = n_node.mv_position;
        mv_position = n_node.mv_position;

        while (mv_current != nullptr)
        {
            mv_stack.push(mv_current);
            mv_current = mv_current->first_child;
        }

        if(!mv_stack.empty() && mv_current == nullptr)
        {
            mv_position = mv_stack.top();
            mv_stack.pop();
            mv_current = mv_position->next_sibling;
        }
	}

private:
	void mv_incrementIterator()
	{
/*
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
*/
	}
}; // end of class postorder_iterator


// ******1*********2*********3*********4*********5*********6*********7*********8*********9*********0*********
/*! \brief A test class.
    A more detailed class description.
*/
template<typename t_type, class t_allocator = std::allocator<t_type> >
class levelorder_tree_iterator
{
public:
	// Member typedefs
	typedef 		t_type 			value_type;
	typedef 		t_type* 		pointer;
	typedef 		t_type& 		reference;
	typedef const 	t_type* 		const_pointer;
	typedef const 	t_type& 		const_reference;
	typedef 		t_allocator 	allocator_type;
	typedef 		std::size_t 	size_type;
	typedef 		std::ptrdiff_t 	difference_type;

	typedef std::forward_iterator_tag 						iterator_category;
	typedef tree<value_type, allocator_type> 				tree_type;
	typedef tree_node<value_type, allocator_type> 			node_type;
	typedef tree_node<value_type, allocator_type>* 			node_pointer;
	typedef levelorder_tree_iterator<t_type, t_allocator> 	iterator_type;

	friend iterator_type ext::begin_level<value_type, allocator_type>(tree_type& np_tree);
	friend iterator_type ext::end_level<value_type, allocator_type>(tree_type& np_tree);

public:
	tree_type* mv_tree;
	node_pointer mv_position;
	//node_pointer mv_current;
	//stack<node_pointer> mv_stack;
	deque<typename tree_type::node_pointer> q;

public:
	levelorder_tree_iterator()
		: mv_tree(nullptr), mv_position(nullptr)
	{}

private:
	levelorder_tree_iterator(tree_type* n_tree)
		: mv_tree(n_tree), mv_position(nullptr)
	{}

	levelorder_tree_iterator(tree_type* n_tree, node_pointer n_position)
		: mv_tree(n_tree), mv_position(n_position)
	{
		if (mv_position != nullptr)
        {
            q.push_back(mv_position);
        }
        if(!q.empty())
        {

            mv_position = q.front();
            q.pop_front();

            if (mv_position->next_sibling != nullptr) q.push_front(mv_position->next_sibling);
            if (mv_position->first_child != nullptr) q.push_back(mv_position->first_child);
        }
        else
        {
            mv_position = nullptr;
        }
	}

public:
	pointer operator->()
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	const_pointer operator->() const
	{
		assert (mv_position != nullptr);
		return *mv_position;
	}

	reference operator*()
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	const_reference operator*() const
	{
		assert (mv_position != nullptr);		
		return **mv_position;
	}

	levelorder_tree_iterator& operator++()
	{
		if(!q.empty())
        {

            mv_position = q.front();
            q.pop_front();

            if (mv_position->next_sibling != nullptr)
            {
                q.push_front(mv_position->next_sibling);
            }

            if (mv_position->first_child != nullptr)
            {
                q.push_back(mv_position->first_child);
            }
        }
        else
        {
            mv_position = nullptr;
        }
		return (*this);
	}

	levelorder_tree_iterator operator++(int)
	{
		// postincrement
		levelorder_tree_iterator _Tmp = *this;
		++(*this);
		return (_Tmp);
	}


	template <class t_iterator>
	bool operator==(const t_iterator& n_iterator) const
	{
		return ( mv_position == n_iterator.mv_position );
	}

	template <class t_iterator>
	bool operator!=(const t_iterator& n_iterator) const
	{
		return (mv_position != n_iterator.mv_position);
	}

	template <class t_iterator>
	void operator=(const t_iterator& n_node )
	{
        mv_position = n_node.mv_position;

		if (mv_position != nullptr)
        {
            q.push_back(mv_position);
        }
        if(!q.empty())
        {

            mv_position = q.front();
            q.pop_front();

            if (mv_position->next_sibling != nullptr) q.push_front(mv_position->next_sibling);
            if (mv_position->first_child != nullptr) q.push_back(mv_position->first_child);
        }
        else
        {
            mv_position = nullptr;
        }
	}

private:
	void mv_incrementIterator()
	{
/*
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
*/
	}
}; // end of class postorder_iterator

} // end of namespace detail

} // end of namespace ext


// start the namespace std for the overload of std::begin and std::end
namespace std
{

template<typename t_type, class t_allocator>
ext::detail::preorder_tree_iterator<t_type, t_allocator> begin(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::preorder_tree_iterator<t_type, t_allocator>(&np_tree, np_tree.mv_root);
}

template<typename t_type, class t_allocator>
ext::detail::preorder_tree_iterator<t_type, t_allocator> end(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::preorder_tree_iterator<t_type, t_allocator>(&np_tree);
}

template<typename t_type, class t_allocator>
void swap(ext::tree<t_type, t_allocator>& a, ext::tree<t_type, t_allocator>& b)
{
	using std::swap; // bring in swap for built-in types

	assert (0 == 1);
	// TODO: implementation
	/*
	        swap(a.base1, b.base1);
	        swap(a.base2, b.base2);
	        // ...
	        swap(a.member1, b.member1);
	        swap(a.member2, b.member2);
	        // ...
	*/
}

} // end of namespace std

namespace ext
{
template<typename t_type, class t_allocator>
ext::detail::postorder_tree_iterator<t_type, t_allocator> begin_post(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::postorder_tree_iterator<t_type, t_allocator>(&np_tree, np_tree.mv_root);
}

template<typename t_type, class t_allocator>
ext::detail::postorder_tree_iterator<t_type, t_allocator> end_post(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::postorder_tree_iterator<t_type, t_allocator>(&np_tree);
}

template<typename t_type, class t_allocator>
ext::detail::levelorder_tree_iterator<t_type, t_allocator> begin_level(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::levelorder_tree_iterator<t_type, t_allocator>(&np_tree, np_tree.mv_root);
}

template<typename t_type, class t_allocator>
ext::detail::levelorder_tree_iterator<t_type, t_allocator> end_level(ext::tree<t_type, t_allocator>& np_tree)
{
	return ext::detail::levelorder_tree_iterator<t_type, t_allocator>(&np_tree);
}

} // end of namespace ext

#endif
