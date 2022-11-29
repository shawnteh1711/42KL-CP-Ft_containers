/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:33:47 by schuah            #+#    #+#             */
/*   Updated: 2022/11/29 09:10:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

/**
 * https://en.cppreference.com/w/cpp/utility/pair
 */
namespace ft
{
	template <class T1, class T2>
	struct	pair
	{
		typedef	T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		/* Default constructor */
		pair()
		{
			first = first_type();
			second = second_type();
		}

		/* Constructs with x and y */
		pair(const first_type& x, const second_type& y)
		{
			first = x;
			second = y;
		}

		/* Copy constructor */
		template <class U1, class U2>
		pair(const pair<U1, U2>& p)
		{
			first = p.first;
			second = p.second;
		} 

		/* Copy assignation operator */
		pair&	operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return (*this);
		}
	};

	/* Creates a pair object, deducing the target type from the types of arguments */
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}

	/* Lexicographically compares the values in the pair */
	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.first == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs != rhs);
	}
	
	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (rhs.first >= lhs.first && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs <= rhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs > rhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs >= rhs);
	}
}

#endif
