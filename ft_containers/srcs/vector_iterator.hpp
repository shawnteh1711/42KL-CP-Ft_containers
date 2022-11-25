/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:55:59 by schuah            #+#    #+#             */
/*   Updated: 2022/11/25 18:38:20 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <typename Iter, typename Container>
	class vector_iterator
	{
		public:
    		typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::reference			reference;
			typedef typename iterator_traits<Iter>::pointer				pointer;

			/* Default constructor */
			vector_iterator()
			{
				this->_iter = iterator_type();
			}

			/* Constructs with the given iterator type */
			explicit vector_iterator(const iterator_type& iter)
			{
				this->_iter = iter;
			}
			
			/* Copy constructor */
			template <class It>
			vector_iterator(const vector_iterator<It,
				typename enable_if<is_same<It,
				typename Container::pointer>::value, Container>::type>& iter)
			{
				this->_iter = iter.base();
			}

			/* Destructor */
			~vector_iterator()
			{
			}

			/* Copy assignation operator */
			vector_iterator&	operator=(const vector_iterator& other)
			{
				this->_iter = other._iter;
				return (*this);
			}

			/* Base member function. Accesses the underlying iterator */
			const iterator_type&	base() const
			{
				return (this->_iter);
			}

			/* Accesses the pointed-to element */
			reference	operator*() const
			{
				return (*this->_iter);
			}

			pointer	operator->() const
			{
				return (this->_iter);
			}

			/* Accesses an element by index */
			reference	operator[](difference_type n)
			{
				return (*(this->_iter + n));
			}

			/* Advances or decrements the iterator */
			vector_iterator&	operator++()
			{
				this->_iter++;
				return (*this);
			}

			vector_iterator&	operator--()
			{
				this->_iter--;
				return (*this);
			}

			vector_iterator	operator++(int)
			{
				return (vector_iterator(_iter++));
			}

			vector_iterator	operator--(int)
			{
				return (vector_iterator(_iter--));
			}

			vector_iterator	operator+(difference_type n) const
			{
				return (vector_iterator(_iter + n));
			}

			vector_iterator	operator-(difference_type n) const
			{
				return (vector_iterator(_iter - n));
			}

			vector_iterator&	operator+=(difference_type n)
			{
				this->_iter += n;
				return (*this);
			}

			vector_iterator&	operator-=(difference_type n)
			{
				this->_iter -= n;
				return (*this);
			}

		protected:
			Iter	_iter;
	};
}

#endif
