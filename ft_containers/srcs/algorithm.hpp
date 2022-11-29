/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:05:28 by schuah            #+#    #+#             */
/*   Updated: 2022/11/29 10:08:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

/**
 * https://en.cppreference.com/w/cpp/algorithm/equal
 * https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
 */
namespace ft
{
	/* Checks if the range [first1, last1] is equal to the range [first2, first2 + (last1 - first1)] */
	template <class InputIt1, class InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; first1++, first2++)
			if (*first1 != *first2)
				return (false);
		return (true);
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; first1++, first2++)
			if (p(*first1, *first2) == false)
				return (false);
		return (true);
	}

	/* Elements are compared using operator< */
	template <class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 && first2 != last2; first1++, first2++)
		{
			if (*first1 < *first2)
				return (true);
			if (*first1 > *first2)
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	/* Elements are compared using the given binary comparison function comp */
	template <class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; first1++, first2++)
		{
			if (comp(*first1, *first2))
				return (false);
			if (comp(*first1, *first2) == false)
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}
}

# endif
