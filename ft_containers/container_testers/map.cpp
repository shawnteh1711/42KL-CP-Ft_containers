/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:16:42 by schuah            #+#    #+#             */
/*   Updated: 2022/12/23 18:48:08 by schuah           ###   ########.fr       */
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

	ft::map<int, char>														ft_m2;
	ft::map<int, char>														ft_m3(ft_m1);
	ft::map<int, char>														ft_m4(ft_m1.begin(), ft_m1.end());
	ft::map<int, char>														ft_m5(ft_m1.key_comp());
	ft::map<int, char>														ft_m6(ft_m1.key_comp(), ft_m1.get_allocator());
	ft::map<int, char>														ft_temp = ft_m1;
	ft::map<int, char>														ft_clear;

	std::map<int, char>														std_m2;
	std::map<int, char>														std_m3(std_m1);
	std::map<int, char>														std_m4(std_m1.begin(), std_m1.end());
	std::map<int, char>														std_m5(std_m1.key_comp());
	std::map<int, char>														std_m6(std_m1.key_comp(), std_m1.get_allocator());
	std::map<int, char>														std_temp = std_m1;
	std::map<int, char>														std_clear;

	ft::map<int, char>::const_iterator										it;
	ft::map<int, char>::const_iterator										eit;
	ft::map<int, char>::const_reverse_iterator								rit;
	ft::map<int, char>::const_reverse_iterator								erit;

	std::allocator<std::pair<int, char> >									a1;
	std::allocator<int>														a2;

	ft::map<int, char, std::greater<int> >									ft_comp;
	ft::map<int, char, std::greater<int> >::key_compare						ft_key_comp1;
	ft::map<int, char>::key_compare											ft_key_comp2;
	ft::map<int, char, std::greater<int> >::value_compare					ft_value_comp1 = ft_comp.value_comp();
	ft::map<int, char>::value_compare										ft_value_comp2 = ft_m1.value_comp();
	ft::pair<ft::map<int, char>::iterator, ft::map<int, char>::iterator>	range;

	std::map<int, char, std::greater<int> >									std_comp;
	std::map<int, char, std::greater<int> >::key_compare					std_key_comp1;
	std::map<int, char>::key_compare										std_key_comp2;
	std::map<int, char, std::greater<int> >::value_compare					std_value_comp1 = std_comp.value_comp();
	std::map<int, char>::value_compare										std_value_comp2 = std_m1.value_comp();
	

	map_check(ft_m1, std_m1);
	map_check(ft_m2, std_m2);
	map_check(ft_m3, std_m3);
	map_check(ft_m4, std_m4);
	map_check(ft_temp, std_temp);

	print_break("Get_allocator");
	a1 = ft_temp.get_allocator();
	ft_map_print(ft_m1);
	assert(a1 == ft_m1.get_allocator());

	ft_m1[42] = 'Z';
	ft_map_print(ft_m1);
	assert(a1 == ft_m1.get_allocator());

	ft_m1.erase(42);
	ft_map_print(ft_m1);
	assert(a1 == ft_m1.get_allocator());

	std::map<int, char>						ft_alloc(a2);
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
	ft_map_print(ft_m2);
	assert(ft_m2.empty() == true);

	ft_map_print(ft_m1);
	assert(ft_m1.empty() == false);

	ft_m2[1] = 'A';
	ft_map_print(ft_m2);
	assert(ft_m2.empty() == false);

	ft_m2[1] = '\0';
	ft_map_print(ft_m2);
	assert(ft_m2.empty() == false);

	ft_m2.erase(1);
	ft_map_print(ft_m2);
	assert(ft_m2.empty() == true);

	print_break("Size");
	ft_map_print(ft_m2);
	assert(ft_m2.size() == 0);

	ft_map_print(ft_m1);
	assert(ft_m1.size() == 8);

	ft_m1[66] = 'X';
	ft_map_print(ft_m1);
	assert(ft_m1.size() == 9);

	ft_m1[66] = 'D';
	ft_map_print(ft_m1);
	assert(ft_m1.size() == 9);

	ft_m1.erase(66);
	ft_map_print(ft_m1);
	assert(ft_m1.size() == 8);

	print_break("Max_size");
	ft_map_print(ft_temp);
	assert(ft_temp.max_size() > 0);
	assert(ft_temp.max_size() == std_temp.max_size());
	assert(ft_m1.max_size() == std_m1.max_size());

	ft_m1[5] = 'F';
	ft_map_print(ft_m1);
	assert(ft_m1.max_size() == std_m1.max_size());

	ft_m1[5] = 'V';
	ft_map_print(ft_m1);
	assert(ft_m1.max_size() == std_m1.max_size());

	ft_m1.erase(55);
	ft_map_print(ft_m1);
	assert(ft_m1.max_size() == std_m1.max_size());

	print_break("Clear");
	ft_m2.clear();
	std_m2.clear();
	map_check(ft_m2, std_m2);
	
	ft_m2 = ft_m3;
	std_m2 = std_m3;
	it = ft_m2.begin();
	ft_m2.clear();
	std_m2.clear();
	map_check(ft_m2, std_m2);
	assert(it != ft_m2.begin());

	ft_clear.clear();
	std_clear.clear();
	map_check(ft_clear, std_clear);

	print_break("Insert");
	ft_m2.insert(ft::pair<int, char>(10, 'O'));
	std_m2.insert(std::pair<int, char>(10, 'O'));
	map_check(ft_m2, std_m2);

	ft_m2.insert(ft_m1.begin(), ft::pair<int, char>(42, 'I'));
	std_m2.insert(std_m1.begin(), std::pair<int, char>(42, 'I'));
	map_check(ft_m2, std_m2);

	ft_m2.insert(ft_m1.begin(), ft::pair<int, char>(99, 'X'));
	std_m2.insert(std_m1.begin(), std::pair<int, char>(99, 'X'));
	map_check(ft_m2, std_m2);

	ft_m2.insert(--ft_m1.end(), ft::pair<int, char>(200, 'Q'));
	std_m2.insert(--std_m1.end(), std::pair<int, char>(200, 'Q'));
	map_check(ft_m2, std_m2);

	ft_m2.insert(ft_m3.begin(), ft_m3.end());
	std_m2.insert(std_m3.begin(), std_m3.end());
	map_check(ft_m2, std_m2);

	ft_m2.insert(ft_m2.begin(), ft_m2.end());
	std_m2.insert(std_m2.begin(), std_m2.end());
	map_check(ft_m2, std_m2);

	print_break("Erase");
	ft_m2.erase(99);
	std_m2.erase(99);
	map_check(ft_m2, std_m2);

	ft_m2.erase(++ft_m2.begin());
	std_m2.erase(++std_m2.begin());
	map_check(ft_m2, std_m2);

	ft_m2.erase(--ft_m2.end());
	std_m2.erase(--std_m2.end());
	map_check(ft_m2, std_m2);

	ft_m2.erase(--ft_m2.end(), ft_m2.end());
	std_m2.erase(--std_m2.end(), std_m2.end());
	map_check(ft_m2, std_m2);

	ft_m2.erase(ft_m2.begin(), ++ft_m2.begin());
	std_m2.erase(std_m2.begin(), ++std_m2.begin());
	map_check(ft_m2, std_m2);

	ft_m2.erase(ft_m2.begin(), ft_m2.end());
	std_m2.erase(std_m2.begin(), std_m2.end());
	map_check(ft_m2, std_m2);

	print_break("Swap");
	ft_m2.swap(ft_m3);
	std_m2.swap(std_m3);
	map_check(ft_m2, std_m2);
	map_check(ft_m3, std_m3);

	ft_m2.swap(ft_m4);
	std_m2.swap(std_m4);
	map_check(ft_m2, std_m2);
	map_check(ft_m4, std_m4);

	ft_m3.swap(ft_m4);
	std_m3.swap(std_m4);
	map_check(ft_m3, std_m3);
	map_check(ft_m4, std_m4);

	print_break("Count");
	ft_map_print(ft_m1);
	assert(ft_m1.count(5) == 1);
	assert(ft_m1.count(-1) == 0);
	assert(ft_m1.count(42) == 1);
	assert(ft_m1.count(100) == 0);

	ft_m1[5] = 'P';
	ft_map_print(ft_m1);
	assert(ft_m1.count(5) == 1);
	
	ft_map_print(ft_m4);
	assert(ft_m4.count(0) == 0);
	assert(ft_m4.count(1) == 0);

	print_break("Find");
	ft_map_print(ft_m1);
	it = ft_m1.find(5);
	assert(it != ft_m1.end());
	assert(it->first == 5);
	assert(it->second == 'P');

	it = ft_m1.find(100);
	assert(it == ft_m1.end());
	ft_m1[100] = 'N';

	ft_map_print(ft_m1);
	it = ft_m1.find(100);
	assert(it != ft_m1.end());
	assert(it->first == 100);
	assert(it->second == 'N');

	print_break("Equal_range");
	ft_map_print(ft_m1);
	range = ft_m1.equal_range(0);
	assert(range.first != ft_m1.end());
	assert(range.first->first == 0);
	assert(range.first->second == 'A');
	assert(range.second != ft_m1.end());
	assert(range.second->first == 1);
	assert(range.second->second == 'B');
	assert(range.second == std::next(range.first));

	range = ft_m1.equal_range(3);
	assert(range.first != ft_m1.end());
	assert(range.first->first == 3);
	assert(range.first->second == 'D');
	assert(range.second != ft_m1.end());
	assert(range.second->first == 4);
	assert(range.second->second == 'E');
	assert(range.second == std::next(range.first));

	range = ft_m1.equal_range(12);
	assert(range.first != ft_m1.end());
	assert(range.first->first == 42);
	assert(range.first->second == 'F');
	assert(range.second != ft_m1.end());
	assert(range.second->first == 42);
	assert(range.second->second == 'F');
	assert(range.second == range.first);

	range = ft_m1.equal_range(100);
	assert(range.first != ft_m1.end());
	assert(range.first->first == 100);
	assert(range.first->second == 'N');
	assert(range.second == ft_m1.end());

	range = ft_m1.equal_range(101);
	assert(range.first == ft_m1.end());
	assert(range.second == ft_m1.end());
	assert(range.second == range.first);

	ft_map_print(ft_m4);
	range = ft_m4.equal_range(10);
	assert(range.first == ft_m4.end());
	assert(range.second == ft_m4.end());
	assert(range.second == range.first);

	print_break("Lower_bound");
	ft_map_print(ft_m1);
	it = ft_m1.lower_bound(3);
	assert(it != ft_m1.end());
	assert(it->first == 3);
	assert(it->second == 'D');

	it = ft_m1.lower_bound(6);
	assert(it != ft_m1.end());
	assert(it->first == 11);
	assert(it->second == 'L');

	it = ft_m1.lower_bound(41);
	assert(it != ft_m1.end());
	assert(it->first == 42);
	assert(it->second == 'F');

	it = ft_m1.lower_bound(43);
	assert(it != ft_m1.end());
	assert(it->first == 100);
	assert(it->second == 'N');

	it = ft_m1.lower_bound(101);
	assert(it == ft_m1.end());

	ft_map_print(ft_m4);
	it = ft_m4.lower_bound(0);
	assert(it == ft_m4.end());

	print_break("Upper_bound");
	ft_map_print(ft_m1);
	it = ft_m1.upper_bound(3);
	assert(it != ft_m1.end());
	assert(it->first == 4);
	assert(it->second == 'E');

	it = ft_m1.upper_bound(6);
	assert(it != ft_m1.end());
	assert(it->first == 11);
	assert(it->second == 'L');

	it = ft_m1.lower_bound(41);
	assert(it != ft_m1.end());
	assert(it->first == 42);
	assert(it->second == 'F');

	it = ft_m1.lower_bound(43);
	assert(it != ft_m1.end());
	assert(it->first == 100);
	assert(it->second == 'N');

	it = ft_m1.upper_bound(101);
	assert(it == ft_m1.end());

	ft_map_print(ft_m4);
	it = ft_m4.upper_bound(0);
	assert(it == ft_m4.end());
	
	print_break("Key_comp");
	ft_key_comp1 = ft_comp.key_comp();
	std_key_comp1 = std_comp.key_comp();
	assert(ft_key_comp1(1, 0) == std_key_comp1(1, 0));
	assert(ft_key_comp1(0, 1) == std_key_comp1(0, 1));
	
	ft_map_print(ft_m1);
	ft_key_comp2 = ft_m1.key_comp();
	std_key_comp2 = std_m1.key_comp();
	assert(ft_key_comp1(1, 0) == std_key_comp1(1, 0));
	assert(ft_key_comp1(0, 1) == std_key_comp1(0, 1));

	print_break("Value_comp");
	assert(ft_value_comp1(ft::pair<int, char>(0, 'A'), ft::pair<int, char>(1, 'B')) == std_value_comp1(std::pair<int, char>(0, 'A'), std::pair<int, char>(1, 'B')));
	assert(ft_value_comp1(ft::pair<int, char>(0, 'B'), ft::pair<int, char>(1, 'A')) == std_value_comp1(std::pair<int, char>(0, 'B'), std::pair<int, char>(1, 'A')));
	assert(ft_value_comp1(ft::pair<int, char>(1, 'A'), ft::pair<int, char>(0, 'B')) == std_value_comp1(std::pair<int, char>(1, 'A'), std::pair<int, char>(0, 'B')));
	assert(ft_value_comp1(ft::pair<int, char>(1, 'B'), ft::pair<int, char>(0, 'A')) == std_value_comp1(std::pair<int, char>(1, 'B'), std::pair<int, char>(0, 'A')));
	
	ft_map_print(ft_m1);
	assert(ft_value_comp2(ft::pair<int, char>(0, 'A'), ft::pair<int, char>(1, 'B')) == std_value_comp2(std::pair<int, char>(0, 'A'), std::pair<int, char>(1, 'B')));
	assert(ft_value_comp2(ft::pair<int, char>(0, 'B'), ft::pair<int, char>(1, 'A')) == std_value_comp2(std::pair<int, char>(0, 'B'), std::pair<int, char>(1, 'A')));
	assert(ft_value_comp2(ft::pair<int, char>(1, 'A'), ft::pair<int, char>(0, 'B')) == std_value_comp2(std::pair<int, char>(1, 'A'), std::pair<int, char>(0, 'B')));
	assert(ft_value_comp2(ft::pair<int, char>(1, 'B'), ft::pair<int, char>(0, 'A')) == std_value_comp2(std::pair<int, char>(1, 'B'), std::pair<int, char>(0, 'A')));

	print_break("Operators");
	ft_m1.clear();
	ft_m1.insert(ft_m3.begin(), --ft_m3.end());
	ft_m1.erase(--ft_m1.end());
	ft_m2 = ft_m1;
	ft_m4 = ft_m3;
	ft_m3.erase(2);
	ft_m3.erase(3);
	ft_m3.erase(4);

	ft_map_print(ft_m1);
	ft_map_print(ft_m2);
	ft_map_print(ft_m3);
	ft_map_print(ft_m4);

	assert(ft_m1 == ft_m1);
	assert(ft_m1 == ft_m2);
	assert(!(ft_m1 == ft_m3));
	assert(!(ft_m1 == ft_m4));

	assert(!(ft_m1 != ft_m1));
	assert(!(ft_m1 != ft_m2));
	assert(ft_m1 != ft_m3);
	assert(ft_m1 != ft_m4);

	assert(!(ft_m1 < ft_m1));
	assert(!(ft_m1 < ft_m2));
	assert(!(ft_m1 < ft_m3));
	assert(ft_m1 < ft_m4);

	assert(ft_m1 <= ft_m1);
	assert(ft_m1 <= ft_m2);
	assert(!(ft_m1 <= ft_m3));
	assert(ft_m1 <= ft_m4);

	assert(!(ft_m1 > ft_m1));
	assert(!(ft_m1 > ft_m2));
	assert(ft_m1 > ft_m3);
	assert(!(ft_m1 > ft_m4));

	assert(ft_m1 >= ft_m1);
	assert(ft_m1 >= ft_m2);
	assert(ft_m1 >= ft_m3);
	assert(!(ft_m1 >= ft_m4));

	print_break("Std::swap");
	ft_m1 = ft_m4;
	ft::swap(ft_m1, ft_m5);
	std::swap(std_m1, std_m5);
	map_check(ft_m1, std_m1);
	map_check(ft_m5, std_m5);

	ft::swap(ft_m1, ft_m5);
	std::swap(std_m1, std_m5);
	map_check(ft_m1, std_m1);
	map_check(ft_m5, std_m5);
	return (0);
}
