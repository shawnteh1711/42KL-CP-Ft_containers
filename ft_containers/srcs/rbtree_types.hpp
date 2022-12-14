/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_types.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:05:32 by schuah            #+#    #+#             */
/*   Updated: 2022/12/14 13:28:36 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_TYPES_HPP
# define RBTREE_TYPES_HPP

#include "utility.hpp"

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
}

#endif
