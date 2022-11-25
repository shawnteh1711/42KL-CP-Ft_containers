/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:38:42 by schuah            #+#    #+#             */
/*   Updated: 2022/11/25 12:16:34 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "type_traits.hpp"

/**
 * https://en.cppreference.com/w/cpp/iterator/iterator
 * https://en.cppreference.com/w/cpp/iterator/iterator_traits
 * https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 * https://cplusplus.com/reference/iterator/reverse_iterator/
 */
namespace ft
{
	/* Base member types */
	template <class Iter> struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	/* T* specialization member types */
	template <class T> struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	/* Reverse_iterator class */
	template <class Iter>
	class reverse_iterator : public std::iterator<
		typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference>
	{
		public:
			typedef Iter											iterator_type;
			typedef typename iterator_traits<Iter>::value_type		value_type;
			typedef typename iterator_traits<Iter>::difference_type	difference_type;
			typedef typename iterator_traits<Iter>::pointer			pointer;
			typedef typename iterator_traits<Iter>::reference		reference;

			/* Default constructor */
			reverse_iterator()
			{
			}

			/* Initialization constructor */
			explicit reverse_iterator(iterator_type it)
			{
				this->current = it;
			}

			/* Copy constructor */
			template <class It> reverse_iterator(const reverse_iterator<It>& rev_it)
			{
				this->current = rev_it.base();
			}

			/* Copy assignation operator */
			reverse_iterator	&operator=(const reverse_iterator& other)
			{
				this->current = other.current;
				return (*this);
			}
			
			/* Base member function. Accesses the underlying iterator */
			iterator_type	base() const
			{
				return (current);
			}

			/* Accesses the pointed-to element */
			reference	operator*() const
			{
				return (*(current - 1));
			}

			pointer	operator->() const
			{
				return (&(operator*()));
			}
		
			/* Accesses an element by index */
			reference	operator[](difference_type n) const
			{
				return (*(*this + n));
			}

			/* Advances or decrements the iterator */
			reverse_iterator&	operator++()
			{
				--current;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				return (reverse_iterator(current--));
			}

			reverse_iterator&	operator--()
			{
				++current;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				return (reverse_iterator(current++));
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			reverse_iterator	operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}

		protected:
			Iter	current;
	};

	
}

#endif
