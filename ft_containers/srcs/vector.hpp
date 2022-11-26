/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:58 by schuah            #+#    #+#             */
/*   Updated: 2022/11/26 19:07:51 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "vector_iterator.hpp"

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
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef vector_iterator<pointer, vector>			iterator;
			typedef vector_iterator<const_pointer, vector>		const_iterator;
			typedef	ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			
			/* Default constructor */
			vector()
			{
				this->_alloc = allocator_type();
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
			}

			/* Constructs an empty container with the given allocator */
			explicit vector(const allocator_type& alloc)
			{
				this->_alloc = alloc;
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
			}
			
			/* Constructs the container with count copies of elements with value */
			explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			{
				if (count <= 0 || check_max_size(count))
					return ;
				this->_alloc = alloc;
				this->_start = this->_alloc.allocate(count);
				this->_capacity = this->_start + count;
				this->_end = _capacity;
				construct_with_val(this->_start, this->_end, value);
			}

			/* Constructs the container with the contents of the range */
			template <class InputIt>
			vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last, const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
				range_init(first, last, typename iterator_traits<InputIt>::iterator_category());
			}

			/* Copy constructor */
			vector (const vector& other)
			{
				size_type	src_cap = other.capacity();
				this->_alloc = other._alloc;
				if (src_cap <= 0)
					return ;
				this->_start = this->_alloc.allocate(src_cap);
				this->_capacity = this->_start + src_cap;
				this->_end = construct_from_start(this->_start, other._start, other._end);
			}

			/* Deconstructor */
			~vector()
			{
				if (this->_start != NULL)
				{
					destroy_from_start(this->_start);
					this->_alloc.deallocate(this->_start, capacity());
				}
			}

			/* Copy assignation operator */
			vector&	operator=(const vector& other)
			{
				if (&other == this)
					return (*this);
				assign(other.begin(), other.end());
				return (*this);
			}

			/* Replaces the contents with count copies of value */
			void	assign(size_type count, const T& value)
			{
				if (count > capacity())
				{
					vector	temp(count, value);
					temp.swap(*this);
				}
				else if (count > size())
				{
					const size_type	available = count - size();
					std::fill(begin(), end(), value);
					this->_end = construct_with_val(this->_end, this->_end + available, value);
				}
				else
				{
					pointer	it = std::fill_n(this->_start, count, value);
					destroy_from_start(it);
				}
			}

			/* Replaces the contents with copies of those in range [first, last] */
			template <class InputIt>
			void	assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				range_assign(first, last, typename iterator_traits<InputIt>::iterator_category());
			}

			/* Returns the allocator associated with the container */
			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}

			/**
			 * ELEMENT ACCESS
			 * 	at
			 * 	operator[]
			 * 	front
			 * 	back
			 * 	data 
			 */

			/* Iterators: Returns an iterator to the first element of the vector */
			iterator	begin()
			{
				return (iterator(this->_start));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_start));
			}
			
			/* Iterators: Returns an iterator to the element following the last element of the vector */
			iterator	end()
			{
				return (iterator(this->_end));
			}

			const_iterator	end() const
			{
				return (const_iterator(this->_end));
			}

			/**
			 * 	rbegin
			 * 	rend 
			 */

			/**
			 * CAPACITY
			 * 	empty
			 */

			/* Capacity: Returns the number of elements in the container */
			size_type	size() const
			{
				return (std::distance(this->begin(), this->end()));
			}

			/* Capacity: Returns the maximum number of elements the container is able to hold due to system or library implementation limitations */
			size_type	max_size() const
			{
				return (std::min(this->_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max())));
			}

			/**
			 * 	reserve
			 */

			/* Capacity: Returns the number of elements that the container has currently allocated space for */
			size_type	capacity () const
			{
				return (static_cast<size_type>(this->_end - this->_start));
			}

			/* Modifiers: Erases all elements from the container */
			void	clear()
			{
				destroy_from_start(this->_start);
			}

			/* Modifiers: Insert value before pos */
			iterator	insert(iterator pos, const value_type& value)
			{
				const size_type	index = pos - begin();
				insert(pos, 1, value);
				return (iterator(this->_start + index));
			}

			/* Modifiers: Inserts count copies of the value before pos */
			void	insert(iterator pos, size_type count, const value_type& value)
			{
				if (count == 0)
					return ;
				const size_type	available = this->_capacity - this->_end;
				if (available >= count)
				{
					const size_type	post = end() - pos;
					pointer			temp = this->_end;
					if (post > count)
					{
						this->_end = construct_from_start(this->_end, this->_end - count, this->_end);
						std::copy_backward(pos.base(), this->_end - count, this->_end);
						std::fill_n(pos, count, value);
					}
					else
					{
						this->_end = construct_with_val(this->_end, this->_end + count - post, value);
						this->_end = construct_with_val(this->_end, pos.base(), temp);
						std::fill(pos.base(), temp, value);
					}
				}
				else
				{
					const size_type	size = get_expansion(count);
					pointer			start = this->_alloc.allocate(size);
					pointer			end;
					end = construct_from_start(start, this->_start, pos.base());
					end = construct_from_start(end, end + count, value);
					end = construct_from_start(end, pos.base(), this->_end);
					deallocate_vector();
					this->_start = start;
					this->_end = end;
					this->_capacity = start + size;
				}
			}

			/* Modifiers: Insert elements from range [first, last] before pos */
			template <class InputIt>
			void	insert(iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
			{
				range_insert(pos, first, last, typename iterator_traits<InputIt>::iterator_category());
			}

			/**
			 *	erase
			 */

			/* Modifiers: Appends the given element value to the end of the container */
			void	push_back(const value_type& value)
			{
				if (this->_end != this->_capacity)
				{
					this->_alloc.construct(this->_end, value);
					this->_end++;
				}
				else
					insert(end(), value);
			}

			/**
			 *	pop_back
			 *	resize
			 */

			/* Exchanges the contents of the container with those of other */
			void	swap(vector& other)
			{
				std::swap(this->_start, other._start);
				std::swap(this->_end, other._end);
				std::swap(this->_capacity, other._capacity);
			}
		
		private:
			/* Helper function: Checks whether size is larger than max size */
			int	check_max_size(size_type size)
			{
				if (size > max_size())
					throw std::length_error("Length error");
				return (0);
			}
			
			/* Helper function: Range constructor (Using src as value) */
			template <class Iterator>
			pointer	construct_from_start(pointer dst, Iterator start, Iterator end)
			{
				for (; start != end; start++, dst++)
					this->_alloc.construct(dst, *start);
				return (dst);
			}

			/* Helper function: Range constructor (Using val as value) */
			pointer	construct_with_val(pointer dst, const_pointer end, const_reference val)
			{
				for (; dst != end; dst++)
					this->_alloc.construct(dst, val);
				return (dst);
			}

			/* Helper function: Clears and deallocates this vector */
			void	deallocate_vector()
			{
				if (this->_start != NULL)
				{
					clear();
					this->_alloc.deallocate(this->_start, capacity());
				}
			}

			/* Helper function: Destroys allocated memory from the start */
			void	destroy_from_start(pointer start)
			{
				for (pointer cur = start; cur != this->_end; cur++)
					this->_alloc.destroy(cur);
				this->_end = start;
			}

			/* Helper function: Returns the size after count expansions */
			size_type	get_expansion(size_type count) const
			{
				check_max_size(count);
				const size_type	max = max_size();
				const size_type	cap = capacity();
				if (cap >= max / 2)
					return (max);
				return (std::max(size() + count, cap * 2));
			}

			/* Helper function: Inserts from range [first, last] into pos without constructing */
			template <class InputIt>
			void	range_insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
			{
				if (pos == end())
				{
					for (; first != last; ++first)
						push_back(*first);
				}
				else if (first != last)
				{
					vector	temp(first, last);
					insert(pos, temp.begin(), temp.end());
				}
			}

			/* Helper function: Inserts from range [first, last] into pos by constructing*/
			template <class ForwardIt>
			void	range_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
			{
				if (first == last)
					return ;
				check_max_size(count);
				const size_type	count = std::distance(first, last);
				const size_type	available = this->_capacity - this->_end;
				if (available >= count)
				{
					const size_type post = end() - pos;
					pointer			temp = this->_end;
					if (post > count)
					{
						this->_end = construct_from_start(this->_end, this->_end - count, this->_end);
						std::copy_backward(pos.base(), temp - count, temp);
						std::copy(first, last, pos);
					}
					else
					{
						ForwardIt mid = first;
						std::advance(mid, post);
						this->_end = construct_from_start(this->_end, mid, last);
						this->_end = construct_from_start(this->_end, pos.base(), temp);
						std::copy(first, mid, pos);
					}
				}
				else
				{
					const size_type	size = get_expansion(count);
					pointer			start = this->_alloc.allocate(size);
					pointer			end = start;
					end = construct_from_start(start, this->_start, pos.base());
					end = construct_from_start(end, first, last);
					end = construct_from_start(end, pos.base(), this->_end);
					deallocate_vector();
					this->_start = start;
					this->_end = end;
					this->_capacity = start + size;
				}
			}

			/* Helper function: Assigns range [first, last] by pushing back */
			template <class InputIt>
			void	range_assign(InputIt first, InputIt last, std::input_iterator_tag)
			{
				clear();
				for (; first != last; first++)
					push_back(*first);
			}

			/* Helper function: Assigns range [first, last] by copying */
			template <class ForwardIt>
			void	range_assign(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
			{
				const size_type	n = std::distance(first, last);
				if (n < size())
				{
					iterator	it = std::copy(first, last, begin());
					destroy_from_start(it.base());
				}
				else
				{
					ForwardIt	it = first;
					std::advance(it, size());
					std::copy(first, it, begin());
					insert(end(), it, last);
				}
			}

			/* Helper function: Range initialising by pushing back */
			template <class InputIt>
			void	range_init(InputIt first, InputIt last, std::input_iterator_tag)
			{
				for (; first != last; first++)
					push_back(*first);
			}

			/* Helper function: Range initialising by creating a new container */
			template <class ForwardIt>
			void	range_init(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
			{
				const size_type count = std::distance(first, last);
				if (count == 0 || check_max_size(count))
					return ;
				this->_start = this->_alloc.allocate(count);
				this->_capacity = this->_start + count;
				this->_end = construct_from_start(this->_start, first, last);
			}

			/* Private member variables */
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;
	};

	/**
	 * NON-MEMBER FUNCTIONS
	 * 	opeartor==
	 * 	opeartor!=
	 * 	opeartor<
	 * 	opeartor<=
	 * 	opeartor>
	 * 	opeartor>=
	 * 
	 * 	std::swap
	 */
}

#endif
