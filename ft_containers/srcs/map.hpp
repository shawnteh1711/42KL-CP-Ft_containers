/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:49 by schuah            #+#    #+#             */
/*   Updated: 2022/12/20 15:13:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "iterator.hpp"
# include "utility.hpp"
# include "rbtree.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/map
 * https://en.cppreference.com/w/cpp/utility/functional/binary_function
 */
namespace ft
{
	/* Value type comparison class */
	template <class Key, class T, class Compare>
	class vt_compare : public std::binary_function<Key, Key, bool>
	{
		public:
			/* Public member variables */
			bool	result_type;
			Key		first_argument_type;
			Key		second_argument_type;
			
			/* Default constructor */
			vt_compare() {};

			/* Copy constructor */
			vt_compare(const Compare& c) : _comp(c) {};

			/* Destructor */
			~vt_compare() {};

			/* Copy assignation operator */
			vt_compare	&operator=(const vt_compare& other)
			{
				this->_comp = other._comp;
				return (*this);
			};

			/* Function object */
			const	Compare& key_comp() const
			{
				return (this->_comp);
			};

			/* Comparisons using key_comp */
			bool	operator()(const T& x, const T& y) const
			{
				return (key_comp()(x.first, y.first));
			};

			bool	operator()(const Key& x, const T& y) const
			{
				return (key_comp()(x, y.first));
			};
			
			bool	operator()(const T& x, const Key& y) const
			{
				return (key_comp()(x.first, y));
			};

			/* Swaps the value of _comp */
			void	swap(vt_compare& other)
			{
				std::swap(this->_comp, other._comp);
			};

		private:
			/* Private member variables */
			Compare	_comp;
	};

	/* Swaps the x and y */
	template <class Key, class T, class Compare>
	void	swap(vt_compare<Key, T, Compare>& x, vt_compare<Key, T, Compare>& y)
	{
		x.swap(y);
	}
	
	/* Map class */
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			/* Member types */
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef pair<const Key, T>								value_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

		private:
			/* Helper types */
			typedef vt_compare<key_type, value_type, key_compare>	vt_compare;
			typedef rbtree<value_type, vt_compare, allocator_type>	base;

		public:
			/* Member types */
			typedef typename base::iterator							iterator;
			typedef typename base::const_iterator					const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/* Value_compare subclass */
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				/* Have access to private members of Map class */
				friend class map;
				
				public:
					/* Member types */
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					/* Compares two values of type value_type */
					bool	operator()(const value_type& x, const value_type& y) const
					{
						return (this->comp(x.first, y.first));
					};

				protected:
					/* Protected member objects */
					key_compare	comp;
					
					/* Initializes the internal instance of the comparator to c */
					value_compare(const key_compare& c) : comp(c) {};
			};

			/* Default constructor */
			map() : _rbtree(vt_compare()) {};

			/* Constructs an empty container with a comparator */
			explicit	map(const key_compare& comp, const allocator_type& alloc = allocator_type()) : _rbtree(vt_compare(comp), alloc) {};

			/* Constructs the container with the contents of range [first, last) */
			template <class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbtree(vt_compare(comp), alloc)
			{
				insert(first, last);
			};

			/* Copy constructor */
			map(const map& other) : _rbtree(other._rbtree) {};

			/* Destructor */
			~map() {};

			/* Copy assignation operator */
			map& operator=(const map& other)
			{
				if (*this == other)
					return (*this);
				this->_rbtree = other._rbtree;
				return (*this);
			};

			/* Returns the associated allocator */
			allocator_type	get_allocator() const
			{
				return (this->_rbtree.get_allocator());
			}

		private:
			base	_rbtree;
	};
}

#endif
