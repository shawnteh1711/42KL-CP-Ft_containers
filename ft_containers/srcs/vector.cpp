/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:20:25 by schuah            #+#    #+#             */
/*   Updated: 2022/12/21 16:19:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <vector>
#include <cassert>

template <class T>
void	vector_check(ft::vector<T> const &v, std::vector<T> const &std_v)
{
	assert(v.size() == std_v.size());
	assert(v.capacity() == std_v.capacity());
	assert(v.max_size() == std_v.max_size());
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << "max_size: " << v.max_size() << std::endl;
	
	for (size_t i = 0; i < std_v.size(); i++)
		assert(v[i] == std_v[i]);
	typename ft::vector<T>::const_iterator	b = v.begin();
	typename ft::vector<T>::const_iterator	e = v.end();
	std::cout << "Content: " << std::endl;
	for (; b != e; ++b)
		std::cout << *b << " ";
	std::cout << std::endl;
}

template <class T>
void	std_vector_print(std::vector<T> const &v)
{
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
	std::cout << "max_size: " << v.max_size() << std::endl;
	
	typename std::vector<T>::const_iterator	b = v.begin();
	typename std::vector<T>::const_iterator	e = v.end();
	std::cout << "Content: " << std::endl;
	for (; b != e; ++b)
		std::cout << *b << " ";
	std::cout << "\n" << std::endl;
}

void	print_break(std::string text)
{
	int	count = (100 - text.length()) / 2;
	std::cout << std::endl;
	for (int i = 0; i < count; i++)
		std::cout << "-";
	std::cout << " " << text << " ";
	for (int i = 0; i < count; i++)
		std::cout << "-";
	std::cout << "\n" << std::endl;
}

int	main(void)
{
	print_break("Initializing test");
	ft::vector<int> ft_v1;
	ft::vector<int> ft_v2(10);
	ft::vector<int> ft_v3(10, 42);
	ft::vector<int> ft_v4 = ft_v3;
	ft::vector<int> ft_v5(ft_v4.begin(), ft_v4.end());
	ft::vector<int> ft_v6(ft_v5);

	std::vector<int> std_v1;
	std::vector<int> std_v2(10);
	std::vector<int> std_v3(10, 42);
	std::vector<int> std_v4 = std_v3;
	std::vector<int> std_v5(std_v4.begin(), std_v4.end());
	std::vector<int> std_v6(std_v5);

	vector_check(ft_v1, std_v1);
	vector_check(ft_v2, std_v2);
	vector_check(ft_v3, std_v3);
	vector_check(ft_v4, std_v4);
	vector_check(ft_v5, std_v5);
	vector_check(ft_v6, std_v6);

	print_break("Assign test");
	std::vector<int> a(5);
	for (int i = 0; i < 5; i++)
		a[i] = i;

	ft_v1.assign(a.begin(), a.end());
	std_v1.assign(a.begin(), a.end());
	vector_check(ft_v1, std_v1);

	ft_v1.assign(10, 42);
	std_v1.assign(10, 42);
	vector_check(ft_v1, std_v1);

	ft_v1.assign(20, 42);
	std_v1.assign(20, 42);
	vector_check(ft_v1, std_v1);

	return (0);
}
