/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:08:49 by schuah            #+#    #+#             */
/*   Updated: 2022/12/23 18:49:18 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/stack.hpp"
#include <iostream>
#include <stack>
#include <cassert>

template <class T>
void	ft_stack_print(ft::stack<T> const &s)
{
	std::cout << "Size: " << s.size() << std::endl;
	std::cout << "Content: " << std::endl;
	for (ft::stack<T> temp = s; temp.empty() == false; temp.pop())
		std::cout << temp.top() << " ";
	std::cout << "\n" << std::endl;
}

template <class T>
void	std_stack_print(std::stack<T> const &s)
{
	std::cout << "Size: " << s.size() << std::endl;
	std::cout << "Content: " << std::endl;
	for (std::stack<T> temp = s; temp.empty() == false; temp.pop())
		std::cout << temp.top() << " ";
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

template <class T>
void	stack_check(ft::stack<T> const &ft_s, std::stack<T> const &std_s)
{
	ft::stack<T>	ft_temp = ft_s;
	std::stack<T>	std_temp = std_s;
	ft_stack_print(ft_s);
	assert(ft_s.empty() == std_s.empty());
	assert(ft_s.size() == std_s.size());
	for (; std_temp.empty() == false; std_temp.pop(), ft_temp.pop())
	{
		assert(ft_temp.empty() == std_temp.empty());
		assert(ft_temp.size() == std_temp.size());
		assert(ft_temp.top() == std_temp.top());
	}
}

ft::stack<int> init_stack(int a, int b, int c)
{
	ft::stack<int>	out;

	out.push(a);
	out.push(b);
	out.push(c);
	return (out);
}	

int	main(void)
{
	print_break("Constructors");
	ft::stack<int>									ft_s1;
	ft::stack<int>									ft_s2;
	ft::stack<int, ft::vector<int> >				ft_uc;
	ft::stack<int>									ft_temp;
	ft::stack<int>									ft_s3 = ft_s1;
	ft::stack<int>									ft_s4(ft_s3);

	std::stack<int>									std_s1;
	std::stack<int>									std_s2;
	std::stack<int, ft::vector<int> >				std_uc;
	std::stack<int>									std_temp;
	std::stack<int>									std_s3 = std_s1;
	std::stack<int>									std_s4(std_s3);

	stack_check(ft_s1, std_s1);
	stack_check(ft_s2, std_s2);
	stack_check(ft_temp, std_temp);
	stack_check(ft_s3, std_s3);
	stack_check(ft_s4, std_s4);

	for (int i = 0; i < 5; i++)
	{
		ft_s1.push(i);
		std_s1.push(i);
	}
	ft_temp = ft_s1;
	std_temp = std_s1;

	stack_check(ft_s1, std_s1);
	stack_check(ft_s2, std_s2);
	stack_check(ft_temp, std_temp);
	stack_check(ft_s3, std_s3);
	stack_check(ft_s4, std_s4);

	print_break("Top");
	ft_s2.push(42);
	std_s2.push(42);
	stack_check(ft_s2, std_s2);

	ft_s2.push(24);
	std_s2.push(24);
	stack_check(ft_s2, std_s2);

	print_break("Empty");
	ft_s3.push(42);
	std_s3.push(42);
	stack_check(ft_s3, std_s3);

	ft_s3.pop();
	std_s3.pop();
	stack_check(ft_s3, std_s3);

	print_break("Size");
	ft_s3.push(42);
	std_s3.push(42);
	stack_check(ft_s3, std_s3);

	ft_s3.pop();
	std_s3.pop();
	stack_check(ft_s3, std_s3);

	print_break("Push");
	ft_s2.push(42);
	std_s2.push(42);
	stack_check(ft_s2, std_s2);

	ft_s2.push(24);
	std_s2.push(24);
	stack_check(ft_s2, std_s2);

	print_break("Pop");
	ft_s2.pop();
	std_s2.pop();
	stack_check(ft_s2, std_s2);

	ft_s2.pop();
	std_s2.pop();
	stack_check(ft_s2, std_s2);

	ft_s2.pop();
	std_s2.pop();
	stack_check(ft_s2, std_s2);

	ft_s2.pop();
	std_s2.pop();
	stack_check(ft_s2, std_s2);

	print_break("Operators");
	ft::stack<int>	s1 = init_stack(1, 2, 4);
	ft::stack<int>	s2 = init_stack(1, 2, 4);
	ft::stack<int>	s3 = init_stack(1, 2, 3);
	ft::stack<int>	s4 = init_stack(1, 3, 2);

	ft_stack_print(s1);
	ft_stack_print(s2);
	ft_stack_print(s3);
	ft_stack_print(s4);

	assert(s1 == s1);
	assert(s1 == s2);
	assert(!(s1 == s3));
	assert(!(s1 == s4));

	assert(!(s1 != s1));
	assert(!(s1 != s2));
	assert(s1 != s3);
	assert(s1 != s4);

	assert(!(s1 < s1));
	assert(!(s1 < s2));
	assert(!(s1 < s3));
	assert(s1 < s4);

	assert(s1 <= s1);
	assert(s1 <= s2);
	assert(!(s1 <= s3));
	assert(s1 <= s4);

	assert(!(s1 > s1));
	assert(!(s1 > s2));
	assert(s1 > s3);
	assert(!(s1 > s4));

	assert(s1 >= s1);
	assert(s1 >= s2);
	assert(s1 >= s3);
	assert(!(s1 >= s4));

	return (0);
}
