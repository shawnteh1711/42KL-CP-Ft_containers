/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:49 by schuah            #+#    #+#             */
/*   Updated: 2022/12/12 18:02:51 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

/**
 * https://en.cppreference.com/w/cpp/container/map
 * https://en.cppreference.com/w/cpp/utility/functional/binary_function
 * https://youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin
 */
namespace ft
{
	/* Value type comparison class */
	template <class Key, class T, class Compare>
	class vt_compare : public std::binary_function<Key, Key, bool>
	{
		public:
			bool	result_type;
			Key		first_argument_type;
			Key		second_argument_type;
			
			/* Default constructor */
			vt_compare()
			{
			}

			/* Copy constructor */
			vt_compare(const Compare& c) : _comp(c)
			{
			}

			/* Destructor */
			~vt_compare()
			{
			}

			/* Copy assignation operator */
			vt_compare	&operator=(const vt_compare& other)
			{
				this->_comp = other._comp;
				return (*this);
			}

			/* Function object */
			const	Compare& key_comp() const
			{
				return (this->_comp);
			}

			/* Comparisons using key_comp */
			bool	operator()(const T& x, const T& y) const
			{
				return (key_comp()(x.first, y.first));
			}

			bool	operator()(const Key& x, const T& y) const
			{
				return (key_comp()(x, y.first));
			}
			
			bool	operator()(const T& x, const Key& y) const
			{
				return (key_comp()(x.first, y));
			}

			/* Swaps the value of _comp */
			void	swap(vt_compare& other)
			{
				std::swap(this->_comp, other._comp);
			}

		private:
			/* Private member variables */
			Compare	_comp;
	};

	template <class Key, class T, class Compare>
	void	swap(vt_compare<Key, T, Compare>& x, vt_compare<Key, T, Compare>& y)
	{
		x.swap(y);
	}
	
}

#endif
