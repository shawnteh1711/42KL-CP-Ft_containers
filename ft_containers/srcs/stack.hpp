/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:37:43 by schuah            #+#    #+#             */
/*   Updated: 2022/12/20 15:05:36 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

/**
 * https://en.cppreference.com/w/cpp/container/stack
 */
namespace ft
{
	/* Stack class */
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			/* Member types */
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;	
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			/* Copy-constructs the underlying container c with the contents of cont */
			explicit	stack(const container_type& cont = container_type()) : c(cont) {};

			/* Copy constructor */
			stack(const stack& other) : c(other.c) {};

			/* Destructor */
			~stack() {};

			/* Copy assignation operator */
			stack& operator=(const stack& other)
			{
				this->c = other.c;
				return (*this);
			};

			/* Element access: Returns reference to the top element in the stack */
			reference	top()
			{
				return (this->c.back());
			};

			const_reference	top() const
			{
				return (this->c.back());
			};

			/* Capacity: Checks if the underlying container has no elements */
			bool	empty() const
			{
				return (this->c.empty());
			};

			/* Capacity: Returns the number of elements in the underlying container */
			size_type	size() const
			{
				return (this->c.size());
			};

			/* Modifiers: Pushes the given element value to the top of the stack */
			void	push(const value_type& value)
			{
				this->c.push_back(value);
			};

			/* Modifiers: Removes the top element from the stack */
			void	pop()
			{
				this->c.pop_back();
			};

			/* Friend is used here to access the the private member object (c) for comparison */
			template <class Type, class C>
			friend bool	operator==(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

			template <class Type, class C>
			friend bool	operator<(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		private:
			/* Member objects */
			container_type	c;
	};

	/* Lexicographically compares the values in the stack */
	template <class T, class Container>
	bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
