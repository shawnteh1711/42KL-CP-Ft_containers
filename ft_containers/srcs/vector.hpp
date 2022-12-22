/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:58 by schuah            #+#    #+#             */
/*   Updated: 2022/12/22 14:47:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <algorithm>
# include "vector_iterator.hpp"
# include "algorithm.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/vector
 */
namespace ft
{
	/* Vector class */
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			/* Member types */
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef vector_iterator<pointer, vector>		iterator;
			typedef vector_iterator<const_pointer, vector>	const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			/* Default constructor */
			vector() : _alloc(allocator_type()), _start(NULL), _end(NULL), _cap(NULL) {};

			/* Constructs an empty container with the given allocator */
			explicit	vector(const allocator_type& alloc) : _alloc(alloc), _start(NULL), _end(NULL), _cap(NULL) {};
			
			/* Constructs the container with count copies of elements with value */
			explicit	vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			{
				if (count <= 0 || this->check_max_size(count))
					return ;
				this->_alloc = alloc;
				this->_start = this->_alloc.allocate(count);
				this->_cap = this->_start + count;
				this->_end = _cap;
				this->construct_with_val(this->_start, this->_end, value);
			};

			/* Constructs the container with the contents of the range */
			template <class InputIt>
			vector(InputIt first, typename std::enable_if<!std::is_integral<InputIt>::value, InputIt>::type last, const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(NULL),  _end(NULL), _cap(NULL)
			{
				this->range_init(first, last);
			};

			/* Copy constructor */
			vector(const vector& other) : _alloc(other._alloc), _start(NULL), _end(NULL), _cap(NULL)
			{
				size_type	src_cap = other.capacity();
				if (src_cap <= 0)
					return ;
				this->_start = this->_alloc.allocate(src_cap);
				this->_cap = this->_start + src_cap;
				this->_end = this->construct_from_start(this->_start, other._start, other._end);
			};

			/* Deconstructor */
			~vector()
			{
				if (this->_start != NULL)
				{
					this->destroy_from_start(this->_start);
					this->_alloc.deallocate(this->_start, capacity());
				}
			};

			/* Copy assignation operator */
			vector&	operator=(const vector& other)
			{
				if (this == &other)
					return (*this);
				this->assign(other.begin(), other.end());
				return (*this);
			};

			/* Replaces the contents with count copies of value */
			void	assign(size_type count, const T& value)
			{
				if (count > this->capacity())
				{
					vector	temp(count, value);
					temp.swap(*this);
				}
				else if (count > this->size())
				{
					const size_type	available = count - this->size();
					std::fill(this->begin(), this->end(), value);
					this->_end = this->construct_with_val(this->_end, this->_end + available, value);
				}
				else
				{
					printf("Here\n");
					pointer	ptr = std::fill_n(this->_start, count, value);
					this->destroy_from_start(ptr);
				}
			};

			/* Replaces the contents with copies of those in range [first, last) */
			template <class InputIt>
			void	assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				this->range_assign(first, last);
			};

			/* Returns the allocator associated with the container */
			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			};

			/* Element access: Returns a reference to the element at specifies location pos, with bounds checking */
			reference	at(size_type pos)
			{
				this->check_range(pos);
				return ((*this)[pos]);
			};

			const_reference	at(size_type pos) const
			{
				this->check_range(pos);
				return ((*this)[pos]);
			};

			/* Element access: Returns a reference to the element at specified location pos. No bounds checking is performed */
			reference	operator[](size_type pos)
			{
				return (*(this->_start + pos));
			};

			const_reference	operator[](size_type pos) const
			{
				return (*(this->_start + pos));
			};

			/* Element access: Returns a reference to the first element in the container */
			reference	front()
			{
				return (*this->begin());
			};

			const_reference	front() const
			{
				return (*this->begin());
			};

			/* Element access: Returns a reference to the last element in the container */
			reference	back()
			{
				return (*(this->end() - 1));
			};

			const_reference	back() const
			{
				return (*(this->end() - 1));
			};

			/* Element access: Returns pointer to the underlying array serving as element storage */
			pointer	data()
			{
				return (this->_start);
			};

			const_pointer	data() const
			{
				return (this->_start);
			};

			/* Iterators: Returns an iterator to the first element of the vector */
			iterator	begin()
			{
				return (iterator(this->_start));
			};

			const_iterator	begin() const
			{
				return (const_iterator(this->_start));
			};
			
			/* Iterators: Returns an iterator to the element following the last element of the vector */
			iterator	end()
			{
				return (iterator(this->_end));
			};

			const_iterator	end() const
			{
				return (const_iterator(this->_end));
			};

			/* Iterators: Returns a reverse iterator to the first element of the reversed vector */
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->end()));
			};

			const_reverse_iterator	rbegin() const
			{
				return (reverse_iterator(this->end()));
			};

			/* Iterators: Returns a reverse iterator to the element following the last element of the reversed vector */
			reverse_iterator	rend()
			{
				return (reverse_iterator(this->begin()));
			};

			const_reverse_iterator	rend() const
			{
				return (reverse_iterator(this->begin()));
			};

			/* Capacity: Checks if the container has no elements */
			bool	empty() const
			{
				return (this->begin() == this->end());
			};

			/* Capacity: Returns the number of elements in the container */
			size_type	size() const
			{
				return (std::distance(this->begin(), this->end()));
			};

			/* Capacity: Returns the maximum number of elements the container is able to hold due to system or library implementation limitations */
			size_type	max_size() const
			{
				return (std::min(this->_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max())));
			};

			/* Capacity: Increase the capacity of the vector (Allocation might be needed) to a value that's greator or equal to new_cap */
			void	reserve(size_type new_cap)
			{
				if (new_cap < this->capacity())
					return ;
				this->check_max_size(new_cap);
				pointer	start = this->_alloc.allocate(new_cap);
				pointer	end;
				end = this->construct_from_start(start, this->_start, this->_end);
				this->deallocate_vector();
				this->_start = start;
				this->_end = end;
				this->_cap = this->_start + new_cap;
			};

			/* Capacity: Returns the number of elements that the container has currently allocated space for */
			size_type	capacity () const
			{
				return (static_cast<size_type>(this->_cap - this->_start));
			};

			/* Modifiers: Erases all elements from the container */
			void	clear()
			{
				this->destroy_from_start(this->_start);
			};

			/* Modifiers: Insert value before pos */
			iterator	insert(iterator pos, const value_type& value)
			{
				const size_type	index = pos - this->begin();
				this->insert(pos, 1, value);
				return (iterator(this->_start + index));
			};

			/* Modifiers: Inserts count copies of the value before pos */
			void	insert(iterator pos, size_type count, const value_type& value)
			{
				if (count == 0)
					return ;
				const size_type	available = this->_cap - this->_end;
				if (available >= count)
				{
					const size_type	post = this->end() - pos;
					pointer			temp = this->_end;
					if (post > count)
					{
						this->_end = this->construct_from_start(this->_end, this->_end - count, this->_end);
						std::copy_backward(pos.base(), this->_end - count, this->_end);
						std::fill_n(pos, count, value);
					}
					else
					{
						this->_end = this->construct_with_val(this->_end, this->_end + count - post, value);
						this->_end = this->construct_from_start(this->_end, pos.base(), temp);
						std::fill(pos.base(), temp, value);
					}
				}
				else
				{
					const size_type	size = this->get_expansion(count);
					pointer			start = this->_alloc.allocate(size);
					pointer			end;
					end = this->construct_from_start(start, this->_start, pos.base());
					end = this->construct_with_val(end, end + count, value);
					end = this->construct_from_start(end, pos.base(), this->_end);
					this->deallocate_vector();
					this->_start = start;
					this->_end = end;
					this->_cap = start + size;
				}
			};

			/* Modifiers: Insert elements from range [first, last) before pos */
			template <class InputIt>
			void	insert(iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				this->range_insert(pos, first, last);
			};

			/* Modifiers: Removes the element at pos */
			iterator	erase(iterator pos)
			{
				if (pos + 1 != this->end())
					std::copy(pos + 1, this->end(), pos);
				this->_end--;
				this->_alloc.destroy(this->_end);
				return (pos);
			};

			/* Modifiers: Removes the elements in the range [first, last) */
			iterator	erase(iterator first, iterator last)
			{
				if (first == last)
					return (first);
				if (last != this->end())
					std::copy(last, this->end(), first);
				pointer	end = first.base() + (this->end() - last);
				this->destroy_from_start(end);
				return (first);
			};

			/* Modifiers: Appends the given element value to the end of the container */
			void	push_back(const value_type& value)
			{
				if (this->_end != this->_cap)
				{
					this->_alloc.construct(this->_end, value);
					this->_end++;
				}
				else
					this->insert(this->end(), value);
			};

			/* Modifiers: Removes the last element of the element */
			void	pop_back()
			{
				this->_end--;
				this->_alloc.destroy(this->_end);
			};

			/* Modifiers: Resizes the container to contain count element */
			void	resize(size_type count, value_type value = value_type())
			{
				const size_type	len = this->size();
				if (count > len)
					this->insert(this->end(), count - len, value);
				else if (count < len)
					this->destroy_from_start(this->_start + count);
			};

			/* Modifiers: Exchanges the contents of the container with those of other */
			void	swap(vector& other)
			{
				std::swap(this->_start, other._start);
				std::swap(this->_end, other._end);
				std::swap(this->_cap, other._cap);
			};
		
		private:
			/* Helper function: If size is larger than max size, throw std::length_error exception */
			int	check_max_size(size_type size)
			{
				if (size > this->max_size())
					throw std::length_error("Length error");
				return (0);
			};

			/* Helper function: If n is larger than size, throw std::out_of_range exception */
			int	check_range(size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("Out of range");
				return (0);
			};
			
			/* Helper function: Range constructor (Using src as value) */
			template <class Iterator>
			pointer	construct_from_start(pointer dst, Iterator start, Iterator end)
			{
				for (; start != end; start++, dst++)
					this->_alloc.construct(dst, *start);
				return (dst);
			};

			/* Helper function: Range constructor (Using val as value) */
			pointer	construct_with_val(pointer dst, const_pointer end, const_reference val)
			{
				for (; dst != end; dst++)
					this->_alloc.construct(dst, val);
				return (dst);
			};

			/* Helper function: Clears and deallocates this vector */
			void	deallocate_vector()
			{
				if (this->_start != NULL)
				{
					this->clear();
					this->_alloc.deallocate(this->_start, this->capacity());
				}
			};

			/* Helper function: Destroys allocated memory from the start */
			void	destroy_from_start(pointer start)
			{
				for (pointer cur = start; cur != this->_end; cur++)
					this->_alloc.destroy(cur);
				this->_end = start;
			};

			/* Helper function: Returns the size after count expansions */
			size_type	get_expansion(size_type count) const
			{
				const size_type	max = this->max_size();
				const size_type	cap = this->capacity();
				if (max - cap < count)
					throw std::length_error("Length error");
				if (cap >= max / 2)
					return (max);
				return (std::max(size() + count, cap * 2));
			};

			/* Helper function: Assigns range [first, last) by copying */
			template <class ForwardIt>
			void	range_assign(ForwardIt first, ForwardIt last)
			{
				const size_type	n = std::distance(first, last);
				if (n < this->size())
				{
					iterator	it = std::copy(first, last, this->begin());
					this->destroy_from_start(it.base());
				}
				else
				{
					ForwardIt	it = first;
					std::advance(it, this->size());
					std::copy(first, it, this->begin());
					this->insert(this->end(), it, last);
				}
			};

			/* Helper function: Range initialising by creating a new container */
			template <class ForwardIt>
			void	range_init(ForwardIt first, ForwardIt last)
			{
				const size_type count = std::distance(first, last);
				if (count == 0 || this->check_max_size(count))
					return ;
				this->_start = this->_alloc.allocate(count);
				this->_cap = this->_start + count;
				this->_end = this->construct_from_start(this->_start, first, last);
			};

			/* Helper function: Inserts from range [first, last) into pos by constructing*/
			template <class ForwardIt>
			void	range_insert(iterator pos, ForwardIt first, ForwardIt last)
			{
				if (first == last)
					return ;
				const size_type	count = std::distance(first, last);
				const size_type	available = this->_cap - this->_end;
				this->check_max_size(count);
				if (available >= count)
				{
					const size_type post = this->end() - pos;
					pointer			temp = this->_end;
					if (post > count)
					{
						this->_end = this->construct_from_start(this->_end, this->_end - count, this->_end);
						std::copy_backward(pos.base(), temp - count, temp);
						std::copy(first, last, pos);
					}
					else
					{
						ForwardIt mid = first;
						std::advance(mid, post);
						this->_end = this->construct_from_start(this->_end, mid, last);
						this->_end = this->construct_from_start(this->_end, pos.base(), temp);
						std::copy(first, mid, pos);
					}
				}
				else
				{
					const size_type	size = this->get_expansion(count);
					pointer			start = this->_alloc.allocate(size);
					pointer			end = start;
					end = this->construct_from_start(start, this->_start, pos.base());
					end = this->construct_from_start(end, first, last);
					end = this->construct_from_start(end, pos.base(), this->_end);
					this->deallocate_vector();
					this->_start = start;
					this->_end = end;
					this->_cap = start + size;
				}
			};

			/* Private member variables */
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_cap;
	};

	/* Lexicographically compares the values in the vector */
	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	/* Swaps the contents of lhs and rhs */
	template <class T, class Alloc>
	void	swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
