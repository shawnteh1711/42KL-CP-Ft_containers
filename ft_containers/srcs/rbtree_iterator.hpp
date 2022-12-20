/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:06:52 by schuah            #+#    #+#             */
/*   Updated: 2022/12/20 14:43:59 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include "rbtree_algorithm.hpp"
# include "rbtree_types.hpp"

namespace ft
{
	/* Const tree iterator definition */
	template <class Key, class T>
	class const_tree_iterator;
	
	/* Tree iterator class */
	template <class Key, class T>
	class tree_iterator
	{
		public:
			/* Member types */
			typedef std::bidirectional_iterator_tag					iterator_category;
			typedef Key												value_type;
			typedef Key&											reference;
			typedef Key*											pointer;
			typedef T												difference_type;
			typedef const_tree_iterator<Key, T>						const_iterator;
		
		private:
			/* Helper types */
			typedef typename rbt_node_types<Key>::leaf_node_pointer	leaf_node_pointer;
			typedef typename rbt_node_types<Key>::node_pointer		node_pointer;

		public:
			/* Orthodox canonical form */
			tree_iterator() : ptr(NULL) {};
			tree_iterator(const tree_iterator &other) : ptr(other.ptr) {};
			~tree_iterator() {};
			tree_iterator	&operator=(const tree_iterator& other)
			{
				if (this == &other)
					return (*this);
				this->ptr = other.ptr;
				return (*this);
			};

			/* Constructor with node_pointer */
			tree_iterator(node_pointer pointer) : ptr(static_cast<leaf_node_pointer>(pointer)) {};

			/* Constructor with leaf_node_pointer */
			tree_iterator(leaf_node_pointer pointer) : ptr(pointer) {};

			/* Base member function. Accesses the underlying pointer */
			leaf_node_pointer&	base()
			{
				return (this->ptr);
			};

			const leaf_node_pointer&	base() const
			{
				return (this->ptr);
			};

			/* Returns leaf_node_pointer in node_pointer type */
			node_pointer	node_ptr() const
			{
				return (static_cast<node_pointer>(this->ptr));
			};

			/* Accesses the pointed-to element */
			reference	operator*() const
			{
				return (static_cast<node_pointer>(this->ptr)->_value);
			};

			pointer	operator->() const
			{
				return (&(operator*()));
			};

			/* Advances of decrements the iterator */
			tree_iterator&	operator++()
			{
				ptr = iter_to_next<leaf_node_pointer>(static_cast<node_pointer>(this->ptr));
				return (*this);
			};

			tree_iterator	operator++(int)
			{
				tree_iterator	it = *this;
				++(*this);
				return (it);
			};

			tree_iterator&	operator--()
			{
				ptr = iter_to_prev<node_pointer>(this->ptr);
				return (*this);
			};

			tree_iterator	operator--(int)
			{
				tree_iterator it = *this;
				--(*this);
				return (it);
			};

			/* Compares the underlying pointer */
			bool	operator==(const tree_iterator& other) const
			{
				return (this->ptr == other.ptr);
			};

			bool	operator==(const const_iterator& other) const
			{
				return (this->ptr == other.base());
			};

			bool	operator!=(const tree_iterator& other) const
			{
				return (!(*this == other));
			};

			bool	operator!=(const const_iterator& other) const
			{
				return (!(*this == other));
			};

		private:
			/* Member object */
			leaf_node_pointer	ptr;
	};

	template <class Key, class T>
	class	const_tree_iterator
	{
		public:
			/* Member types */
			typedef std::bidirectional_iterator_tag					iterator_category;
			typedef Key												value_type;
			typedef const Key&										reference;
			typedef const Key*										pointer;
			typedef T												difference_type;
			typedef tree_iterator<Key, T>							iterator;
			typedef typename rbt_node_types<Key>::leaf_node_pointer	leaf_node_pointer;
			typedef typename rbt_node_types<Key>::node_pointer		node_pointer;

			/* Orthodox canonical form */
			const_tree_iterator() : ptr(NULL) {};
			const_tree_iterator(const const_tree_iterator &other) : ptr(other.ptr) {};
			~const_tree_iterator() {};
			const_tree_iterator	&operator=(const const_tree_iterator& other)
			{
				if (this == &other)
					return (*this);
				this->ptr = other.ptr;
				return (*this);
			};

			/* Constructor with node_pointer */
			const_tree_iterator(node_pointer pointer) : ptr(static_cast<leaf_node_pointer>(pointer)) {};

			/* Constructor with iterator */
			const_tree_iterator(iterator it) : ptr(it.base()) {};

			/* Base member function. Accesses the underlying pointer */
			leaf_node_pointer&	base()
			{
				return (this->ptr);
			};

			const leaf_node_pointer&	base() const
			{
				return (this->ptr);
			};

			/* Returns leaf_node_pointer in node_pointer type */
			node_pointer node_ptr() const
			{
				return (static_cast<node_pointer>(this->ptr));
			};

			/* Accesses the pointed-to element */
			reference	operator*() const
			{
				return (static_cast<node_pointer>(this->ptr)->_value);
			};

			pointer	operator->() const
			{
				return (&(operator*()));
			};

			/* Advances of decrements the iterator */
			const_tree_iterator&	operator++()
			{
				ptr = iter_to_next<leaf_node_pointer>(static_cast<node_pointer>(this->ptr));
				return (*this);
			};

			const_tree_iterator	operator++(int)
			{
				const_tree_iterator	it = *this;
				++(*this);
				return (it);
			};

			const_tree_iterator&	operator--()
			{
				ptr = iter_to_prev<node_pointer>(ptr);
				return (*this);
			};

			const_tree_iterator	operator--(int)
			{
				const_tree_iterator	it = *this;
				--(*this);
				return (it);
			};

			/* Compares the underlying pointer */
			bool	operator==(const const_tree_iterator& other) const
			{
				return (ptr == other.ptr);
			};

			bool	operator==(const iterator& other) const
			{
				return (ptr == other.base());
			};

			bool	operator!=(const const_tree_iterator& other) const
			{
				return (!(*this == other));
			};

			bool	operator!=(const iterator& other) const
			{
				return (!(*this == other));
			};

		private:
			/* Member object */
			leaf_node_pointer	ptr;
	};
}

#endif
