/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:16:42 by schuah            #+#    #+#             */
/*   Updated: 2022/12/23 15:33:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/map.hpp"
#include <iostream>
#include <map>
#include <cassert>
#include <iomanip>

template <class Key, class T>
void	ft_map_print(ft::map<Key, T> const &m)
{
	std::cout << "Size: " << m.size() << std::endl;
	std::cout << "Content: " << std::endl;
	for (typename ft::map<Key, T>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << std::left << std::setw(3) << it->first << ":\t" << it->second << std::endl;
	std::cout << std::endl;
}

template <class Key, class T>
void	std_map_print(std::map<Key, T> const &m)
{
	std::cout << "Size: " << m.size() << std::endl;
	std::cout << "Content: " << std::endl;
	for (typename std::map<Key, T>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << std::left << std::setw(3) << it->first << ":\t" << it->second << std::endl;
	std::cout << std::endl;
}

void	print_break(std::string text)
{
	int	count = (75 - text.length()) / 2;
	for (int i = 0; i < count; i++)
		std::cout << "-";
	std::cout << " " << text << " ";
	for (int i = 0; i < count; i++)
		std::cout << "-";
	std::cout << "\n" << std::endl;
}

template <class Key, class T>
void	map_check(ft::map<Key, T> const &ft_m, std::map<Key, T> const &std_m)
{
	ft_map_print(ft_m);
	typename ft::map<Key, T>::const_iterator	ft_it = ft_m.begin();
	typename std::map<Key, T>::const_iterator	std_it = std_m.begin();
	for (; std_it != std_m.end(); std_it++, ft_it++)
	{
		assert(ft_it->first == std_it->first);
		assert(ft_it->second == std_it->second);
		assert(ft_m.at(ft_it->first) == std_m.at(std_it->first));
		assert(ft_m.count(ft_it->first) == std_m.count(std_it->first));
		assert(ft_m.empty() == std_m.empty());
		assert(ft_m.get_allocator() == std_m.get_allocator());
		assert(ft_m.max_size() == std_m.max_size());
		assert(ft_m.size() == std_m.size());
	}
}

int	main(void)
{
	print_break("Constructors");
	ft::map<int, char>						ft_m1;
	std::map<int, char>						std_m1;
	for (int i = 0; i < 5; i++)
	{
		ft_m1[i] = 'A' + i;
		std_m1[i] = 'A' + i;
	}

	ft::map<int, char>							ft_m2;
	ft::map<int, char>							ft_m3(ft_m1);
	ft::map<int, char>							ft_m4(ft_m1.begin(), ft_m1.end());
	ft::map<int, char>							ft_m5(ft_m1.key_comp());
	ft::map<int, char>							ft_m6(ft_m1.key_comp(), ft_m1.get_allocator());
	ft::map<int, char>							ft_temp = ft_m1;

	std::map<int, char>							std_m2;
	std::map<int, char>							std_m3(std_m1);
	std::map<int, char>							std_m4(std_m1.begin(), std_m1.end());
	ft::map<int, char>							std_m5(std_m1.key_comp());
	ft::map<int, char>							std_m6(std_m1.key_comp(), std_m1.get_allocator());
	std::map<int, char>							std_temp = std_m1;

	ft::map<int, char>::const_iterator			it;
	ft::map<int, char>::const_iterator			eit;
	ft::map<int, char>::const_reverse_iterator	rit;
	ft::map<int, char>::const_reverse_iterator	erit;

	map_check(ft_m1, std_m1);
	map_check(ft_m2, std_m2);
	map_check(ft_m3, std_m3);
	map_check(ft_m4, std_m4);
	map_check(ft_temp, std_temp);

	print_break("Get_allocator");
	std::allocator<int>	a = ft_temp.get_allocator();
	ft_map_print(ft_m1);
	assert(a == ft_m1.get_allocator());

	ft_m1[42] = 'Z';
	ft_map_print(ft_m1);
	assert(a == ft_m1.get_allocator());

	ft_m1.erase(42);
	ft_map_print(ft_m1);
	assert(a == ft_m1.get_allocator());

	std::allocator<std::pair<int, char> >	b;
	std::map<int, char>	ft_alloc(b);
	ft_map_print(ft_m1);
	assert(ft_m1.get_allocator() == ft_alloc.get_allocator());

	print_break("At");
	try
	{
		ft_m1.at(42);
		assert(false);
	}
	catch(const std::exception& e) { std::cerr << e.what() << "\n\n"; }

	ft_m1[42] = 'F';
	ft_map_print(ft_m1);
	assert(ft_m1.at(42) == 'F');
	
	ft_m1[11] = 'G';
	ft_map_print(ft_m1);
	assert(ft_m1.at(11) == 'G');

	ft_m1[11] = 'L';
	ft_map_print(ft_m1);
	assert(ft_m1.at(11) == 'L');

	try
	{
		ft_m1.at(111);
		assert(false);
	}
	catch(const std::exception& e) { std::cerr << e.what() << "\n\n"; }

	print_break("Operator[]");
	ft_m1[55] = 'H';
	ft_map_print(ft_m1);
	assert(ft_m1[55] = 'H');

	ft_m1[55] = 'I';
	ft_map_print(ft_m1);
	assert(ft_m1[55] = 'I');

	char&	character = ft_m1[55];
	character = 'D';
	ft_map_print(ft_m1);
	assert(ft_m1[55] = 'D');

	print_break("Begin and End");
	ft_map_print(ft_m1);
	it = ft_m1.begin();
	eit = ft_m1.end();

	assert(ft_m1.begin()->first == 0);
	assert(ft_m1.begin()->second == 'A');
	assert((--ft_m1.end())->first == 55);
	assert((--ft_m1.end())->second == 'D');
	assert(it == ft_m1.begin());
	assert(eit == ft_m1.end());

	ft_m1[66] = 'P';
	ft_map_print(ft_m1);
	assert(ft_m1.begin()->first == 0);
	assert(ft_m1.begin()->second == 'A');
	assert((--ft_m1.end())->first == 66);
	assert((--ft_m1.end())->second == 'P');
	assert(it == ft_m1.begin());
	assert(eit == ft_m1.end());

	ft_m1.erase(66);
	ft_map_print(ft_m1);
	assert(ft_m1.begin()->first == 0);
	assert(ft_m1.begin()->second == 'A');
	assert((--ft_m1.end())->first == 55);
	assert((--ft_m1.end())->second == 'D');
	assert(it == ft_m1.begin());
	assert(eit == ft_m1.end());

	ft_m1[-1] = 'N';
	ft_map_print(ft_m1);
	assert(ft_m1.begin()->first == -1);
	assert(ft_m1.begin()->second == 'N');
	assert((--ft_m1.end())->first == 55);
	assert((--ft_m1.end())->second == 'D');
	assert(it == ++ft_m1.begin());
	assert(eit == ft_m1.end());

	ft_m1.erase(-1);
	ft_map_print(ft_m1);
	assert(ft_m1.begin()->first == 0);
	assert(ft_m1.begin()->second == 'A');
	assert((--ft_m1.end())->first == 55);
	assert((--ft_m1.end())->second == 'D');
	assert(it == ft_m1.begin());
	assert(eit == ft_m1.end());

	ft_map_print(ft_m2);
	assert(ft_m2.begin() == ft_m2.end());

	print_break("Rbegin and Rend");
	ft_map_print(ft_m1);
	rit = ft_m1.rbegin();
	erit = ft_m1.rend();
	assert(ft_m1.rbegin()->first == 55);
	assert(ft_m1.rbegin()->second == 'D');
	assert((--ft_m1.rend())->first == 0);
	assert((--ft_m1.rend())->second == 'A');
	assert(rit == ft_m1.rbegin());
	assert(erit == ft_m1.rend());

	ft_m1[66] = 'P';
	ft_map_print(ft_m1);
	assert(ft_m1.rbegin()->first == 66);
	assert(ft_m1.rbegin()->second == 'P');
	assert((--ft_m1.rend())->first == 0);
	assert((--ft_m1.rend())->second == 'A');
	assert(rit == ft_m1.rbegin());
	assert(erit == ft_m1.rend());

	ft_m1.erase(66);
	ft_map_print(ft_m1);
	assert(ft_m1.rbegin()->first == 55);
	assert(ft_m1.rbegin()->second == 'D');
	assert((--ft_m1.rend())->first == 0);
	assert((--ft_m1.rend())->second == 'A');
	assert(rit == ft_m1.rbegin());
	assert(erit == ft_m1.rend());

	ft_m1[-1] = 'N';
	ft_map_print(ft_m1);
	assert(ft_m1.rbegin()->first == 55);
	assert(ft_m1.rbegin()->second == 'D');
	assert((--ft_m1.rend())->first == -1);
	assert((--ft_m1.rend())->second == 'N');
	assert(rit == ft_m1.rbegin());
	assert(erit == --ft_m1.rend());

	ft_m1.erase(-1);
	ft_map_print(ft_m1);
	assert(ft_m1.rbegin()->first == 55);
	assert(ft_m1.rbegin()->second == 'D');
	assert((--ft_m1.rend())->first == 0);
	assert((--ft_m1.rend())->second == 'A');
	assert(rit == ft_m1.rbegin());
	assert(erit == ft_m1.rend());

	ft_map_print(ft_m2);
	assert(ft_m2.rbegin() == ft_m2.rend());

	print_break("Empty");
	return (0);
}
