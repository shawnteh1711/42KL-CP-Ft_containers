/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:58 by schuah            #+#    #+#             */
/*   Updated: 2022/11/25 15:51:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"

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
			explicit vector (size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			{
				if (count <= 0)
					return ;
				else if (count > std::min(this->_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max())))
					throw std::length_error("Length error");
				this->_alloc = alloc;
				this->_start = this->_alloc.allocate(count);
				this->_capacity = this->_start + count;
				this->_end = _capacity;
				construct_with_val(this->_start, this->_end, value);
			}

			/* Constructs the container with the contents of the range */
			template <class InputIt>
			vector (InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last, const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
				(void)first;
				(void)last;
			}

			/* Copy constructor */
			vector (const vector& other)
			{
				this->_alloc = other._alloc;
				size_type	src_cap = other.capacity();
				if (src_cap <= 0)
					return ;
				this->_start = this->_alloc.allocate(src_cap);
				this->_capacity = this->_start + src_cap;
				this->_end = contruct_from_start(this->_start, other._start, other._end);
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

			/**
			 * MEMBER FUNCTION
			 * 	assign
			 * 	get_allocator
			 */

			/**
			 * ELEMENT ACCESS
			 * 	at
			 * 	operator[]
			 * 	front
			 * 	back
			 * 	data 
			 */

			/**
			 * ITERATORS
			 * 	begin
			 * 	end
			 * 	rbegin
			 * 	rend 
			 */

			/**
			 * CAPACITY
			 * 	empty
			 * 	size
			 * 	max_size
			 * 	reserve
			 */

			/*
			 * Capacity member function. Returns the number of elements that can
			 * be held in currently allocated storage
			 */
			size_type	capacity () const
			{
				return (static_cast<size_type>(this->_end - this->_start));
			}

			/**
			 * MODIFIERS
			 * 	clear
			 *	insert
			 *	erase
			 *	push_back
			 *	pop_back
			 *	resize
			 *	swap 
			 */
		
		private:
			/* Helper function: Range constructor (Using src as value) */
			template <typename Iterator>
			pointer	contruct_from_start(pointer dst, Iterator start, Iterator end)
			{
				while (start != end)
				{
					this->_alloc.construct(dst, *start);
					dst++;
					start++;
				}
				return (dst);
			}

			/* Helper function: Range constructor (Using val as value) */
			pointer	construct_with_val(pointer dst, const_pointer end, const_reference val)
			{
				while (dst != end)
				{
					this->_alloc.construct(dst, val);
					dst++;
				}
				return (dst);
			}

			/* Helper function: Destroys allocated memory from the start */
			void	destroy_from_start(pointer start)
			{
				for (pointer cur = start; cur != this->_end; cur++)
					this->_alloc.destroy(cur);
				this->_end = start;
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
