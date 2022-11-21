/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:58 by schuah            #+#    #+#             */
/*   Updated: 2022/11/21 19:02:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "type_traits.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/vector
 * https://cplusplus.com/reference/vector/vector/vector/
 */
namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T                                        value_type;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef value_type&                              reference;
			typedef const value_type&                        const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			
			/* Default constructor */
			explicit vector(const allocator_type &alloc)
			{
				this->_alloc = alloc;
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
			}
			
			/* Fill constructor */
			explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				if (n <= 0)
					return;
				else if (n > std::min(this->_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max())))
					throw std::length_error("Length error");
				this->_alloc = alloc;
				this->_start = this->_alloc.allocate(n);
				this->_capacity = this->_start + n;
				this->_end = _capacity;
				construct_with_val(this->_start, this->_end, val);
			}

			/* Range constructor */
			template <class InputIterator>
			vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type &alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_start = NULL;
				this->_end = NULL;
				this->_capacity = NULL;
				(void)first;
				(void)last;
			}

			/* Copy constructor */
			vector (const vector &src)
			{
				this->_alloc = src._alloc;
				size_type	src_cap = src.capacity();
				if (src_cap <= 0)
					return ;
				
				this->_start = this->_alloc.allocate(src_cap);
				this->_capacity = this->_start + src_cap;
				this->_end = contruct_from_start(this->_start, src._start, src._end);
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

			/* Capacity member function */
			size_type	capacity () const
			{
				return (static_cast<size_type>(this->_end - this->_start));
			}

			/* Range constructor helper function (Using src as value)*/
			template <typename Iterator>
			pointer contruct_from_start(pointer dst, Iterator start, Iterator end)
			{
				while (start != end)
				{
					this->_alloc.construct(dst, *start);
					dst++;
					start++;
				}
				return (dst);
			}

			/* Range constructor helper function (Using val as value)*/
			pointer construct_with_val(pointer dst, const_pointer end, const_reference val)
			{
				while (dst != end)
				{
					this->_alloc.construct(dst, val);
					dst++;
				}
				return (dst);
			}
		
		private:
			void	destroy_from_start(pointer start)
			{
				for (pointer cur = start; cur != this->_end; cur++)
					this->_alloc.destroy(cur);
				this->_end = start;
			}

			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;
	};
}

#endif
