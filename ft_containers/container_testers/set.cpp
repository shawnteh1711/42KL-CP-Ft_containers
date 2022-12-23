/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:48:37 by schuah            #+#    #+#             */
/*   Updated: 2022/12/23 22:23:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/set.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <set>
#include <chrono>

template <class T>
void	ft_set_print(ft::set<T> const &s)
{
	std::cout << "Size: " << s.size() << std::endl;
	std::cout << "Content: " << s.size() << std::endl;
	for (typename ft::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
}

template <class T>
void	std_set_print(std::set<T> const &s)
{
	std::cout << "Size: " << s.size() << std::endl;
	std::cout << "Content: " << s.size() << std::endl;
	for (typename std::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;
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
void	set_check(ft::set<Key, T> const &ft_s, std::set<Key, T> const &std_s)
{
	ft_set_print(ft_s);
	typename ft::set<Key, T>::const_iterator	ft_it = ft_s.begin();
	typename std::set<Key, T>::const_iterator	std_it = std_s.begin();
	for (; std_it != std_s.end(); std_it++, ft_it++)
	{
		assert(*ft_it == *std_it);
		assert(ft_s.count(*ft_it) == std_s.count(*std_it));
		assert(ft_s.empty() == std_s.empty());
		assert(ft_s.get_allocator() == std_s.get_allocator());
		assert(ft_s.max_size() == std_s.max_size());
		assert(ft_s.size() == std_s.size());
	}
}

int	main(void)
{
	{
		print_break("Constructors");
		ft::set<int>												ft_s1;
		std::set<int>												std_s1;
		for (int i = 0; i < 5; i++)
		{
			ft_s1.insert(i);
			std_s1.insert(i);
		}

		ft::set<int>												ft_s2;
		ft::set<int>												ft_s3(ft_s1);
		ft::set<int>												ft_s4(ft_s1.begin(), ft_s1.end());
		ft::set<int>												ft_s5(ft_s1.key_comp());
		ft::set<int>												ft_s6(ft_s1.key_comp(), ft_s1.get_allocator());
		ft::set<int>												ft_temp = ft_s1;
		ft::set<int>												ft_clear;

		std::set<int>												std_s2;
		std::set<int>												std_s3(std_s1);
		std::set<int>												std_s4(std_s1.begin(), std_s1.end());
		std::set<int>												std_s5(std_s1.key_comp());
		std::set<int>												std_s6(std_s1.key_comp(), std_s1.get_allocator());
		std::set<int>												std_temp = std_s1;
		std::set<int>												std_clear;

		ft::set<int>::const_iterator								it;
		ft::set<int>::const_iterator								eit;
		ft::set<int>::const_reverse_iterator						rit;
		ft::set<int>::const_reverse_iterator						erit;

		std::allocator<std::pair<int, char> >						a1;
		std::allocator<int>											a2;

		ft::set<int, std::greater<int> >							ft_comp;
		ft::set<int, std::greater<int> >::key_compare				ft_key_comp1;
		ft::set<int>::key_compare									ft_key_comp2;
		ft::set<int, std::greater<int> >::value_compare				ft_value_comp1 = ft_comp.value_comp();
		ft::set<int>::value_compare									ft_value_comp2 = ft_s1.value_comp();
		ft::pair<ft::set<int>::iterator, ft::set<int>::iterator>	range;

		std::set<int, std::greater<int> >							std_comp;
		std::set<int, std::greater<int> >::key_compare				std_key_comp1;
		std::set<int>::key_compare									std_key_comp2;
		std::set<int, std::greater<int> >::value_compare			std_value_comp1 = std_comp.value_comp();
		std::set<int>::value_compare								std_value_comp2 = std_s1.value_comp();

		set_check(ft_s1, std_s1);
		set_check(ft_s2, std_s2);
		set_check(ft_s3, std_s3);
		set_check(ft_s4, std_s4);
		set_check(ft_temp, std_temp);

		ft_set_print(ft_s1);
		std_set_print(std_s1);

		print_break("Get_allocator");
		a1 = ft_temp.get_allocator();
		ft_set_print(ft_s1);
		assert(a1 == ft_s1.get_allocator());

		ft_s1.insert(42);
		ft_set_print(ft_s1);
		assert(a1 == ft_s1.get_allocator());

		ft_s1.erase(42);
		ft_set_print(ft_s1);
		assert(a1 == ft_s1.get_allocator());

		std::set<int>	ft_alloc(a2);
		ft_set_print(ft_s1);
		assert(ft_s1.get_allocator() == ft_alloc.get_allocator());

		print_break("Begin and End");
		ft_set_print(ft_s1);
		it = ft_s1.begin();
		eit = ft_s1.end();

		assert(*(ft_s1.begin()) == 0);
		assert(*(--ft_s1.end()) == 4);
		assert(it == ft_s1.begin());
		assert(eit == ft_s1.end());

		ft_s1.insert(5);
		ft_set_print(ft_s1);
		assert(*(ft_s1.begin()) == 0);
		assert(*(--ft_s1.end()) == 5);
		assert(it == ft_s1.begin());
		assert(eit == ft_s1.end());

		ft_s1.erase(5);
		ft_set_print(ft_s1);
		assert(*(ft_s1.begin()) == 0);
		assert(*(--ft_s1.end()) == 4);
		assert(it == ft_s1.begin());
		assert(eit == ft_s1.end());

		ft_s1.insert(ft_s1.begin(), -1);
		ft_set_print(ft_s1);
		assert(*(ft_s1.begin()) == -1);
		assert(*(--ft_s1.end()) == 4);
		assert(it == ++ft_s1.begin());
		assert(eit == ft_s1.end());

		ft_s1.erase(-1);
		ft_set_print(ft_s1);
		assert(*(ft_s1.begin()) == 0);
		assert(*(--ft_s1.end()) == 4);
		assert(it == ft_s1.begin());
		assert(eit == ft_s1.end());

		ft_set_print(ft_s2);
		assert(ft_s2.begin() == ft_s2.end());

		print_break("Rbegin and Rend");
		ft_set_print(ft_s1);
		rit = ft_s1.rbegin();
		erit = ft_s1.rend();
		assert(*(ft_s1.rbegin()) == 4);
		assert(*(--ft_s1.rend()) == 0);
		assert(rit == ft_s1.rbegin());
		assert(erit == ft_s1.rend());

		ft_s1.insert(5);
		ft_set_print(ft_s1);
		assert(*(ft_s1.rbegin()) == 5);
		assert(*(--ft_s1.rend()) == 0);
		assert(rit == ft_s1.rbegin());
		assert(erit == ft_s1.rend());

		ft_s1.erase(5);
		ft_set_print(ft_s1);
		assert(*(ft_s1.rbegin()) == 4);
		assert(*(--ft_s1.rend()) == 0);
		assert(rit == ft_s1.rbegin());
		assert(erit == ft_s1.rend());

		ft_s1.insert(ft_s1.begin(), -1);
		ft_set_print(ft_s1);
		assert(*(ft_s1.rbegin()) == 4);
		assert(*(--ft_s1.rend()) == -1);
		assert(rit == ft_s1.rbegin());
		assert(erit == --ft_s1.rend());

		ft_s1.erase(-1);
		ft_set_print(ft_s1);
		assert(*(ft_s1.rbegin()) == 4);
		assert(*(--ft_s1.rend()) == 0);
		assert(rit == ft_s1.rbegin());
		assert(erit == ft_s1.rend());

		ft_set_print(ft_s2);
		assert(ft_s2.rbegin() == ft_s2.rend());

		print_break("Empty");
		ft_set_print(ft_s2);
		assert(ft_s2.empty() == true);

		ft_set_print(ft_s1);
		assert(ft_s1.empty() == false);

		ft_s2.insert(1);
		ft_set_print(ft_s2);
		assert(ft_s2.empty() == false);

		ft_s2.erase(1);
		ft_set_print(ft_s2);
		assert(ft_s2.empty() == true);

		print_break("Size");
		ft_set_print(ft_s2);
		assert(ft_s2.size() == 0);

		ft_set_print(ft_s1);
		assert(ft_s1.size() == 5);

		ft_s1.insert(6);
		ft_set_print(ft_s1);
		assert(ft_s1.size() == 6);

		ft_s1.erase(6);
		ft_set_print(ft_s1);
		assert(ft_s1.size() == 5);

		print_break("Max_size");
		ft_set_print(ft_temp);
		assert(ft_temp.max_size() > 0);
		assert(ft_temp.max_size() == std_temp.max_size());
		assert(ft_s1.max_size() == std_s1.max_size());

		ft_s1.insert(5);
		ft_set_print(ft_s1);
		assert(ft_s1.max_size() == std_s1.max_size());

		ft_s1.erase(5);
		ft_set_print(ft_s1);
		assert(ft_s1.max_size() == std_s1.max_size());

		print_break("Clear");
		ft_s2.clear();
		std_s2.clear();
		set_check(ft_s2, std_s2);
		
		ft_s2 = ft_s3;
		std_s2 = std_s3;
		it = ft_s2.begin();
		ft_s2.clear();
		std_s2.clear();
		set_check(ft_s2, std_s2);
		assert(it != ft_s2.begin());

		ft_clear.clear();
		std_clear.clear();
		set_check(ft_clear, std_clear);

		print_break("Insert");
		ft_s2.insert(10);
		std_s2.insert(10);
		set_check(ft_s2, std_s2);

		ft_s2.insert(ft_s2.begin(), 42);
		std_s2.insert(std_s2.begin(), 42);
		set_check(ft_s2, std_s2);

		ft_s2.insert(ft_s2.begin(), 99);
		std_s2.insert(std_s2.begin(), 99);
		set_check(ft_s2, std_s2);

		ft_s2.insert(--ft_s2.end(), 200);
		std_s2.insert(--std_s2.end(), 200);
		set_check(ft_s2, std_s2);

		ft_s2.insert(ft_s3.begin(), ft_s3.end());
		std_s2.insert(std_s3.begin(), std_s3.end());
		set_check(ft_s2, std_s2);

		ft_s2.insert(ft_s2.begin(), ft_s2.end());
		std_s2.insert(std_s2.begin(), std_s2.end());
		set_check(ft_s2, std_s2);

		print_break("Erase");
		ft_s2.erase(99);
		std_s2.erase(99);
		set_check(ft_s2, std_s2);

		ft_s2.erase(++ft_s2.begin());
		std_s2.erase(++std_s2.begin());
		set_check(ft_s2, std_s2);

		ft_s2.erase(--ft_s2.end());
		std_s2.erase(--std_s2.end());
		set_check(ft_s2, std_s2);

		ft_s2.erase(--ft_s2.end(), ft_s2.end());
		std_s2.erase(--std_s2.end(), std_s2.end());
		set_check(ft_s2, std_s2);

		ft_s2.erase(ft_s2.begin(), ++ft_s2.begin());
		std_s2.erase(std_s2.begin(), ++std_s2.begin());
		set_check(ft_s2, std_s2);

		ft_s2.erase(ft_s2.begin(), ft_s2.end());
		std_s2.erase(std_s2.begin(), std_s2.end());
		set_check(ft_s2, std_s2);

		print_break("Swap");
		ft_set_print(ft_s3);
		ft_set_print(ft_s2);
		
		ft_s2.swap(ft_s3);
		std_s2.swap(std_s3);
		set_check(ft_s2, std_s2);
		set_check(ft_s3, std_s3);

		ft_s2.swap(ft_s4);
		std_s2.swap(std_s4);
		set_check(ft_s2, std_s2);
		set_check(ft_s4, std_s4);

		ft_s3.swap(ft_s4);
		std_s3.swap(std_s4);
		set_check(ft_s3, std_s3);
		set_check(ft_s4, std_s4);

		print_break("Count");
		ft_set_print(ft_s2);
		assert(ft_s1.count(4) == 1);
		assert(ft_s1.count(-1) == 0);
		assert(ft_s1.count(0) == 1);
		assert(ft_s1.count(100) == 0);

		ft_s1.insert(4);
		ft_set_print(ft_s1);
		assert(ft_s1.count(4) == 1);
		
		ft_set_print(ft_s4);
		assert(ft_s4.count(0) == 0);
		assert(ft_s4.count(1) == 0);

		print_break("Find");
		ft_set_print(ft_s1);
		it = ft_s1.find(4);
		assert(it != ft_s1.end());
		assert(*it == 4);

		it = ft_s1.find(100);
		assert(it == ft_s1.end());

		ft_s1.insert(100);
		ft_set_print(ft_s1);
		it = ft_s1.find(100);
		assert(it != ft_s1.end());
		assert(*it == 100);

		print_break("Equal_range");
		ft_s1.insert(11);
		ft_s1.insert(42);
		ft_set_print(ft_s1);
		range = ft_s1.equal_range(0);
		assert(range.first != ft_s1.end());
		assert(*range.first == 0);
		assert(range.second != ft_s1.end());
		assert(*range.second == 1);
		assert(range.second == std::next(range.first));

		range = ft_s1.equal_range(3);
		assert(range.first != ft_s1.end());
		assert(*range.first == 3);
		assert(range.second != ft_s1.end());
		assert(*range.second == 4);
		assert(range.second == std::next(range.first));

		range = ft_s1.equal_range(12);
		assert(range.first != ft_s1.end());
		assert(*range.first == 42);
		assert(range.second != ft_s1.end());
		assert(*range.second == 42);
		assert(range.second == range.first);

		range = ft_s1.equal_range(100);
		assert(range.first != ft_s1.end());
		assert(*range.first == 100);
		assert(range.second == ft_s1.end());

		range = ft_s1.equal_range(101);
		assert(range.first == ft_s1.end());
		assert(range.second == ft_s1.end());
		assert(range.second == range.first);

		ft_set_print(ft_s4);
		range = ft_s4.equal_range(10);
		assert(range.first == ft_s4.end());
		assert(range.second == ft_s4.end());
		assert(range.second == range.first);

		print_break("Lower_bound");
		ft_set_print(ft_s1);
		it = ft_s1.lower_bound(3);
		assert(it != ft_s1.end());
		assert(*it == 3);

		it = ft_s1.lower_bound(6);
		assert(it != ft_s1.end());
		assert(*it == 11);

		it = ft_s1.lower_bound(41);
		assert(it != ft_s1.end());
		assert(*it == 42);

		it = ft_s1.lower_bound(43);
		assert(it != ft_s1.end());
		assert(*it == 100);

		it = ft_s1.lower_bound(101);
		assert(it == ft_s1.end());

		ft_set_print(ft_s4);
		it = ft_s4.lower_bound(0);
		assert(it == ft_s4.end());

		print_break("Upper_bound");
		ft_set_print(ft_s1);
		it = ft_s1.upper_bound(3);
		assert(it != ft_s1.end());
		assert(*it == 4);

		it = ft_s1.upper_bound(6);
		assert(it != ft_s1.end());
		assert(*it == 11);

		it = ft_s1.lower_bound(41);
		assert(it != ft_s1.end());
		assert(*it == 42);

		it = ft_s1.lower_bound(43);
		assert(it != ft_s1.end());
		assert(*it == 100);

		it = ft_s1.upper_bound(101);
		assert(it == ft_s1.end());

		ft_set_print(ft_s4);
		it = ft_s4.upper_bound(0);
		assert(it == ft_s4.end());

		print_break("Key_comp");
		ft_key_comp1 = ft_comp.key_comp();
		std_key_comp1 = std_comp.key_comp();
		assert(ft_key_comp1(1, 0) == std_key_comp1(1, 0));
		assert(ft_key_comp1(0, 1) == std_key_comp1(0, 1));
		
		ft_set_print(ft_s1);
		ft_key_comp2 = ft_s1.key_comp();
		std_key_comp2 = std_s1.key_comp();
		assert(ft_key_comp1(1, 0) == std_key_comp1(1, 0));
		assert(ft_key_comp1(0, 1) == std_key_comp1(0, 1));

		print_break("Value_comp");
		assert(ft_value_comp1(0, 1) == std_value_comp1(0, 1));
		assert(ft_value_comp1(1, 0) == std_value_comp1(1, 0));
		
		ft_set_print(ft_s1);
		assert(ft_value_comp2(0, 1) == std_value_comp2(0, 1));
		assert(ft_value_comp2(1, 0) == std_value_comp2(1, 0));

		print_break("Operators");
		ft_s1.clear();
		ft_s1.insert(ft_s3.begin(), --ft_s3.end());
		ft_s1.erase(--ft_s1.end());
		ft_s2 = ft_s1;
		ft_s4 = ft_s3;
		ft_s3.erase(2);
		ft_s3.erase(3);
		ft_s3.erase(4);

		ft_set_print(ft_s1);
		ft_set_print(ft_s2);
		ft_set_print(ft_s3);
		ft_set_print(ft_s4);

		assert(ft_s1 == ft_s1);
		assert(ft_s1 == ft_s2);
		assert(!(ft_s1 == ft_s3));
		assert(!(ft_s1 == ft_s4));

		assert(!(ft_s1 != ft_s1));
		assert(!(ft_s1 != ft_s2));
		assert(ft_s1 != ft_s3);
		assert(ft_s1 != ft_s4);

		assert(!(ft_s1 < ft_s1));
		assert(!(ft_s1 < ft_s2));
		assert(!(ft_s1 < ft_s3));
		assert(ft_s1 < ft_s4);

		assert(ft_s1 <= ft_s1);
		assert(ft_s1 <= ft_s2);
		assert(!(ft_s1 <= ft_s3));
		assert(ft_s1 <= ft_s4);

		assert(!(ft_s1 > ft_s1));
		assert(!(ft_s1 > ft_s2));
		assert(ft_s1 > ft_s3);
		assert(!(ft_s1 > ft_s4));

		assert(ft_s1 >= ft_s1);
		assert(ft_s1 >= ft_s2);
		assert(ft_s1 >= ft_s3);
		assert(!(ft_s1 >= ft_s4));

		print_break("Std::swap");
		ft_s1 = ft_s4;
		ft::swap(ft_s1, ft_s5);
		std::swap(std_s1, std_s5);
		set_check(ft_s1, std_s1);
		set_check(ft_s5, std_s5);

		ft::swap(ft_s1, ft_s5);
		std::swap(std_s1, std_s5);
		set_check(ft_s1, std_s1);
		set_check(ft_s5, std_s5);
	}
	{
		clock_t start_time;
		clock_t	end_time;
		double	ft_elapsed_time, std_elapsed_time;
		int	i;
		print_break("Performance");
		start_time = clock();

		ft::set<int>														ft_s1;
		for (int i = 0; i < 5; i++)
			ft_s1.insert(i);
		ft::set<int>														ft_s2;
		ft::set<int>														ft_s3(ft_s1);
		ft::set<int>														ft_s4(ft_s1.begin(), ft_s1.end());
		ft::set<int>														ft_s5(ft_s1.key_comp());
		ft::set<int>														ft_s6(ft_s1.key_comp(), ft_s1.get_allocator());
		ft::set<int>														ft_temp = ft_s1;
		ft::set<int>														ft_clear;

		ft_s1.get_allocator();
		ft_s1.begin();
		ft_s1.end();
		ft_s1.rbegin();
		ft_s1.rend();
		ft_s1.empty();
		ft_s1.size();
		ft_s1.max_size();
		ft_s1.clear();
		ft_s1.insert(42);
		ft_s1.insert(ft_s1.begin(), 42);
		ft_s1.insert(ft_s3.begin(), ft_s3.end());
		ft_s1.erase(42);
		ft_s1.erase(ft_s1.begin());
		ft_s1.erase(ft_s1.begin(), ft_s1.end());
		ft_s1.swap(ft_s3);
		ft_s1.count(0);
		ft_s1.find(0);
		ft_s1.equal_range(0);
		ft_s1.lower_bound(0);
		ft_s1.upper_bound(0);
		ft_s1.key_comp();
		ft_s1.value_comp();
		i = (ft_s1 == ft_s1);
		i = (ft_s1 != ft_s1);
		i = (ft_s1 < ft_s1);
		i = (ft_s1 <= ft_s1);
		i = (ft_s1 > ft_s1);
		i = (ft_s1 >= ft_s1);
		std::swap(ft_s1, ft_s3);

		end_time = clock();
		ft_elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		std::cout << "ft elapsed time: " << std::fixed << std::setprecision(6) << ft_elapsed_time << " seconds" << std::endl;
		start_time = clock();

		std::set<int>														std_s1;
		for (int i = 0; i < 5; i++)
			std_s1.insert(i);
		std::set<int>														std_s2;
		std::set<int>														std_s3(std_s1);
		std::set<int>														std_s4(std_s1.begin(), std_s1.end());
		std::set<int>														std_s5(std_s1.key_comp());
		std::set<int>														std_s6(std_s1.key_comp(), std_s1.get_allocator());
		std::set<int>														std_temp = std_s1;
		std::set<int>														std_clear;

		std_s1.get_allocator();
		std_s1.begin();
		std_s1.end();
		std_s1.rbegin();
		std_s1.rend();
		std_s1.empty();
		std_s1.size();
		std_s1.max_size();
		std_s1.clear();
		std_s1.insert(42);
		std_s1.insert(std_s1.begin(), 42);
		std_s1.insert(std_s3.begin(), std_s3.end());
		std_s1.erase(42);
		std_s1.erase(std_s1.begin());
		std_s1.erase(std_s1.begin(), std_s1.end());
		std_s1.swap(std_s3);
		std_s1.count(0);
		std_s1.find(0);
		std_s1.equal_range(0);
		std_s1.lower_bound(0);
		std_s1.upper_bound(0);
		std_s1.key_comp();
		std_s1.value_comp();
		i = (std_s1 == std_s1);
		i = (std_s1 != std_s1);
		i = (std_s1 < std_s1);
		i = (std_s1 <= std_s1);
		i = (std_s1 > std_s1);
		i = (std_s1 >= std_s1);
		std::swap(std_s1, std_s3);

		end_time = clock();
		std_elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		std::cout << "std elapsed time: " << std::fixed << std::setprecision(6) << std_elapsed_time << " seconds" << std::endl;
		std::cout << "Slower by: " << ft_elapsed_time / std_elapsed_time << "x times\n" << std::endl;
		print_break("All test finished: Set OK");
	}
	return (0);
}
