/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:47 by schuah            #+#    #+#             */
/*   Updated: 2022/12/21 14:38:38 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "iterator.hpp"
# include "rbtree.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/set
 */
namespace ft
{
	/* Set class 	*/
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		public:
			/* Member types */
			typedef Key												key_type;
			typedef Key												value_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Compare											value_compare;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

		private:
			/* Helper types */
			typedef rbtree<value_type, value_compare, Allocator>	base;

		public:
			/* Member types */
			typedef typename base::const_iterator					iterator;
			typedef typename base::const_iterator					const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/* Default constructor */
			set() : _rbtree(value_compare()) {};

			/* Constructs an empty container with a comparator and allocator */
			explicit	set(const key_compare& comp, const allocator_type& alloc = allocator_type()) : _rbtree(comp, alloc) {};

			/* Constructs the container with the contents of range [first, last) */
			template <class InputIt>
			set(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _rbtree(comp, alloc)
			{
				this->insert(first, last);
			}

			/* Copy constructor */
			set(const set& other) : _rbtree(other._rbtree) {};
		
			/* Destructor */
			~set() {};

			/* Copy assignation operator */
			set&	operator=(const set& other)
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
			};

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
				return (reverse_iterator(this->end()));
			}

			/* Iterators: Returns a reverse iterator to the end */
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->begin()));
			}
			
			const_reverse_iterator	rend() const
			{
				return (reverse_iterator(this->begin()));
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
				this->_rbtree.erase(pos);
			}

			/* Modifiers: Removes the elements in the range [first, last), which must be a valid range in *this */
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
			void	swap(set& other)
			{
				this->_rbtree.swap(other._rbtree);
			}

			/* Lookup: Returns the number of elements matching specific key */
			size_type	count(const key_type& key) const
			{
				return (this->_rbtree.count(key));
			}

			/* Lookup: Finds elements with specific key */
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

			/* Lookup: Returns an iterator to the first element greater than the given key */
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
				return (this->_rbtree.value_comp());
			}

			/* Observers: Returns the function that compares keys in objects of type value_type */
			key_compare	value_comp() const
			{
				return (this->_rbtree.value_comp());
			}

		private:
			base	_rbtree;
	};
}

#endif