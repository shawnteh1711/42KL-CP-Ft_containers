/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:49 by schuah            #+#    #+#             */
/*   Updated: 2022/12/12 17:27:55 by schuah           ###   ########.fr       */
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
	/* Map comparison function */
	template <class Key, class T, class Compare>
	class vt_compare : public std::binary_function<Key, Key, bool>
	{
		public:
			bool	result_type;
			Key		first_argument_type;
			Key		second_argument_type;
		private:
	}
}

#endif
