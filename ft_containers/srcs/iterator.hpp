/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:38:42 by schuah            #+#    #+#             */
/*   Updated: 2022/11/21 21:50:50 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "type_traits.hpp"

/**
 * https://en.cppreference.com/w/cpp/iterator/iterator
 * https://en.cppreference.com/w/cpp/iterator/iterator_traits
 */
namespace ft
{
	template <typename Iter> struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <typename Iter> struct iterator_traits<Iter*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef typename std::remove_cv<Iter>::type	value_type;
		typedef Iter*								pointer;
		typedef Iter&								reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};
}

#endif
