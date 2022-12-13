/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:05:32 by schuah            #+#    #+#             */
/*   Updated: 2022/12/13 22:16:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "utility.hpp"

/**
 * https://youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin
 * 
 * Rules:
 * 	1. Every node is either red or black
 * 	2. The root of the tree is black
 * 	3. Every leaf (end of the tree branch or NULL) is black
 * 	4. If a node is red, then both of its children must be black
 * 	5. All paths from a node to descendants leaves contain the same number of black nodes
 */
namespace ft
{
	/* Definitions */
	template <class T> class	rbt_leaf_node;
	template <class T> class	rbt_node;

	/* Helper struct to define aliases */
	template <class T>
	struct	rbt_node_types
	{
		typedef	rbt_leaf_node<T>		leaf_node_type;
		typedef	leaf_node_type*		leaf_node_pointer;
		typedef	rbt_node<T>			node_type;
		typedef	node_type*			node_pointer;
	};

	/* End node class of RBTree */
	template <class T>
	class	rbt_leaf_node
	{
		public:
			/* Member types */
			typedef typename rbt_node_types<T>::node_pointer	node_pointer;

            /* Public member objects */
			node_pointer	_left;

			/* Orthodox canonical form */
			rbt_leaf_node() : _left(NULL) {};
			rbt_leaf_node(const rbt_leaf_node& other) : _left(other._left) {};
			~rbt_leaf_node() {};
			rbt_leaf_node&	operator=(const rbt_leaf_node& other)
			{
				if (this == &other)
					return (*this);
				this->_left = other._left;
				return (*this);
			}
	};

	/* Node class of RBTree */
	template <class T>
	class	rbt_node : public rbt_node_types<T>::leaf_node_type
	{
		public:
			/* Member types */
			typedef typename rbt_node_types<T>::leaf_node_pointer		leaf_node_pointer;
			typedef typename rbt_node_types<T>::node_pointer			node_pointer;


            /* Public member objects */
			node_pointer		_right;
			leaf_node_pointer	_parent;
			bool				_black;
			T					_value;

			/* Orthodox canonical form */
			rbt_node() : _right(NULL), _parent(NULL), _black(false), _value(NULL) {};
			rbt_node(const rbt_node& other) : _right(other._right), _parent(other._parent), _black(other._black), _value(other._value) {};
			~rbt_node() {};
			rbt_node&	operator=(const rbt_node& other)
			{
				if (this == &other)
					return (*this);
				this->_right = other._right;
				this->_parent = other._parent;
				this->_black = other._black;
				this->_value = other._value;
			}

			/* Getter and setter function for parent of node */
			node_pointer	get_parent_ptr() const { return (static_cast<node_pointer>(this->_parent)); }
			void	set_parent_ptr(node_pointer parent) { this->_parent = static_cast<leaf_node_pointer>(parent); }
	};

	/* Boolean to check if the node is a left child */
	template <class Node>
	bool is_left_child(Node node)
	{
		return (node == node->_parent->_left);
	}

	/* Returns the most right node of the branch (Highest value) */
	template <class Node>
	Node	most_right_node(Node node)
	{
		while (node->_right != NULL)
			node = node->_right;
		return (node);
	}

	/* Returns the most left node of the branch (Lowest value) */
	template <class Node>
	Node	most_left_node(Node node)
	{
		while (node->_left != NULL)
			node = node->_left;
		return (node);
	}

	/* Iterates to the next node */
	template <class It, class Node>
	It	iter_to_next(Node node)
	{
		if (node->_right != NULL)
			return (most_left_node(node->_right));
		while (is_left_child(node) == 0)
			node = node->get_parent_ptr();
		return (node->_parent);
	}

	/* Iterates to the previous node */
	template <class Node, class It>
	It	iter_to_prev(It iter)
	{
		if (iter->_left != NULL)
			return (most_right_node(iter->_left));
		Node	node = static_cast<Node>(iter);
		while (is_left_child(node))
			node = node->get_parent_ptr();
		return (node->_parent);
	}

	/* Rotates a node to the left */
	template <class Node>
	void	node_rotate_left(Node node)
	{
		Node	rightchild = node->_right;
		node->_right = rightchild->_left;
		if (rightchild->_left != NULL)
			rightchild->_left->set_parent_ptr(node);
		rightchild->_parent = node->_parent;
		if (is_left_child(node))
			node->_parent->_left = rightchild;
		else
			node->get_parent_ptr()->_right = rightchild;
		rightchild->_left = node;
		node->set_parent_ptr(rightchild);
	}

	/* Rotates a node to the right */
	template <class Node>
	void	node_rotate_right(Node node)
	{
		Node	leftchild = node->_left;
		node->_left = leftchild->_right;
		if (leftchild->_right != NULL)
			leftchild->_right->set_parent_ptr(node);
		leftchild->_parent = node->_parent;
		if (is_left_child(node))
			node->_parent->_left = leftchild;
		else
			node->get_parent_ptr()->_right = leftchild;
		leftchild->_right = node;
		node->set_parent_ptr(leftchild);
	}

	template <class Node>
	void	branch_rotate_left(Node& root, Node node)
	{
		if (node == root)
			root = node->_right;
		node_rotate_left(node);
	}

	template <class Node>
	void	branch_rotate_right(Node& root, Node node)
	{
		if (node == root)
			root = node->_left;
		node_rotate_right(node);
	}

	template <class Node>
	bool	node_is_black(Node node)
	{
		return (node == NULL || node->_black);
	}
}

#endif
