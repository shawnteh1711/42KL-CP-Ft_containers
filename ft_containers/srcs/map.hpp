/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:49 by schuah            #+#    #+#             */
/*   Updated: 2022/12/21 14:33:51 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "iterator.hpp"
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
				if (this == &other)
					return (*this);
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

			/* Constructs an empty container with a comparator and allocator */
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
				if (this == &other)
					return (*this);
				this->_rbtree = other._rbtree;
				return (*this);
			};

			/* Returns the associated allocator */
			allocator_type	get_allocator() const
			{
				return (this->_rbtree.get_allocator());
			}

			/* Element access: Access specified element with bounds checking */
			T&	at(const key_type& key)
			{
				iterator	it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("Out of range");
				return (it->second);
			}

			const T&	at(const key_type& key) const
			{
				const_iterator	it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("Out of range");
				return (it->second);
			}

			/* Element access: access or insert specified element */
			T&	operator[](const Key& key)
			{
				return (insert(ft::make_pair(key, T())).first->second);
			}

			/* Iterators: Returns an iterator to the beginning */
			iterator	begin()
			{
				return (this->_rbtree.begin());
			}

			const_iterator	begin() const
			{
				return (this->_rbtree.begin());
			}

			/* Iterators: Returns an iterator to the end */
			iterator	end()
			{
				return (this->_rbtree.end());
			}

			const_iterator	end() const
			{
				return (this->_rbtree.end());
			}

			/* Iterators: Returns a reverse iterator to the beginning */
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			/* Iterators: Returns a reverse iterator to the end */
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

			/* Capacity: Checks whether the container is empty */
			bool	empty() const
			{
				return (this->_rbtree.empty());
			}

			/* Capacity: Returns the number of elements */
			size_type	size() const
			{
				return (this->_rbtree.size());
			}

			/* Capacity: Returns the maximum possible number of elements */
			size_type	max_size() const
			{
				return (this->_rbtree.max_size());
			}

			/* Modifiers: Clears the contents */
			void	clear()
			{
				this->_rbtree.clear();
			}

			/* Modifiers: Inserts value */
			pair<iterator, bool>	insert(const value_type& value)
			{
				return (this->_rbtree.insert(value));
			}

			/* Modifiers: Inserts value in the position as close as possible to the position just prior to pos */
			iterator	insert(iterator pos, const value_type& value)
			{
				return (this->_rbtree.insert(pos, value));
			}

			/* Modifiers: Inserts elements from range [first, last) */
			template <class InputIt>
			void	insert(InputIt first, InputIt last)
			{
				this->_rbtree.insert(first, last);
			}

			/* Modifiers: Removes the element at pos */
			void	erase(iterator pos)
			{
				this->_rbtree.erase(const_iterator(pos));
			}

			/* Modifiers: Removes the elements in the range [first, last), which must be valid range in *this */
			void	erase(iterator first, iterator last)
			{
				this->_rbtree.erase(first, last);
			}

			/* Modifiers: Removes the element (if one exists) with the key */
			size_type	erase(const key_type& key)
			{
				return (this->_rbtree.erase(key));
			}

			/* Modifiers: Swaps the contents */
			void	swap(map& other)
			{
				this->_rbtree.swap(other._rbtree);
			}

			/* Lookup: Returns the number of elements matching specific key */
			size_type	count(const key_type& key) const
			{
				return (this->_rbtree.count(key));
			}

			/* Lookup: Finds element with specific key */
			iterator	find(const key_type& key)
			{
				return (this->_rbtree.find(key));
			}

			const_iterator	find(const key_type& key) const
			{
				return (this->_rbtree.find(key));
			}

			/* Lookup: Returns range of elements matching a specific key */
			pair<iterator, iterator>	equal_range(const key_type& key)
			{
				return (this->_rbtree.equal_range(key));
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
			{
				return (this->_rbtree.equal_range(key));
			}

			/* Lookup: Returns an iterator to the first element not less than the given key */
			iterator	lower_bound(const key_type& key)
			{
				return (this->_rbtree.lower_bound(key));
			}

			const_iterator	lower_bound(const key_type& key) const
			{
				return (this->_rbtree.lower_bound(key));
			}

			/* Lookup: Returns an iterator pointing to the first element that is greater than key */
			iterator	upper_bound(const key_type& key)
			{
				return (this->_rbtree.upper_bound(key));
			}

			const_iterator	upper_bound(const key_type& key) const
			{
				return (this->_rbtree.upper_bound(key));
			}

			/* Observers: Returns the function that compares keys */
			key_compare	key_comp() const
			{
				return (this->_rbtree.value_comp().key_comp());
			}

			/* Observers: Returns the function that compares keys in objects of type value_type */
			value_compare	value_comp() const
			{
				return (value_compare(this->_rbtree.value_comp().key_comp()));
			}

		private:
			/* Private member variables */
			base	_rbtree;
	};

	/* Lexicographically compares the values in the map */
	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> lhs, const map<Key, T, Compare, Alloc> rhs)
	{
		return (!(lhs < rhs));
	}

	/* Swaps the contents of lhs and rhs */
	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
