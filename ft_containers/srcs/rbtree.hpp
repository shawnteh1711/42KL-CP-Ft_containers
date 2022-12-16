/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:56:56 by schuah            #+#    #+#             */
/*   Updated: 2022/12/16 21:42:56 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "rbtree_algorithm.hpp"
# include "rbtree_iterator.hpp"

namespace fd
{
	/* Red-black tree class */
	template <class T, class Compare, class Allocator>
	class rbtree
	{
		public:
			/* Member types */
			typedef T															value_type;
			typedef Allocator													allocator_type;
			typedef Compare														value_compare;
			typedef typename allocator_type::difference_type					difference_type;
			typedef typename allocator_type::size_type							size_type;
			typedef const value_type&											const_reference;
			typedef value_type&													reference;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename allocator_type::pointer							pointer;
			typedef const_tree_iterator<value_type, difference_type>			const_iterator;
			typedef tree_iterator<value_type, difference_type>					iterator;
			typedef typename rbt_node_types<value_type>::node_type				node_type;
			typedef typename rbt_node_types<value_type>::leaf_node_type			leaf_node_type;
			typedef typename rbt_node_types<value_type>::node_pointer			node_pointer;
			typedef typename rbt_node_types<value_type>::leaf_node_pointer		leaf_node_pointer;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;

			/* Constructor with value_compare */
			rbtree(const value_compare& comp) : _node_alloc(node_allocator()), _value_alloc(allocator_type()), _comp(comp), _leaf_node(leaf_node_type()), _leaf_node_ptr(this->end_node()), _size(0) {};

			/* Constructor with value_compare and allocator_type */
			rbtree(const value_compare& comp, const allocator_type& alloc) : _node_alloc(node_allocator()), _value_alloc(alloc), _comp(comp), _leaf_node(leaf_node_type()), _leaf_node_ptr(this->end_node()), _size(0) {};

			/* Copy constructor */
			rbtree(const rbtree& other) : _node_alloc(other._node_alloc), _value_alloc(other._value_alloc), _comp(other._comp), _leaf_node(), _leaf_node_ptr(this->end_node()), _size(0)
			{
				insert(other.begin(), other.end());
			};

			/* Destructor */
			~rbtree()
			{
				this->destroy(this->root());
			}

			/* Copy assignation operator */
			rbtree	&operator=(const rbtree& other)
			{
				if (this == &other)
					return (*this);
				rbtree	copy(other);
				this->swap(copy);
				return (*this);
			}

			/* Returns the associated allocator */
			allocator_type	get_allocator() const
			{
				return (this->_value_alloc);
			}

			/* Iterators: Returns an iterator to the beginning */
			iterator	begin()
			{
				return (iterator(this->_leaf_node_ptr));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_leaf_node_ptr));
			}

			/* Iterators: Returns an iterator to the end */
			iterator	end()
			{
				return (iterator(this->end_node()));
			}

			const_iterator	end() const
			{
				return (const_iterator(this->end_node()));
			}

			/* Capacity: Checks whether the container is empty */
			bool	empty() const
			{
				return (this->size() == size_type(0));
			}

			/* Capacity: Returns the number of elements*/
			size_type	size() const
			{
				return (this->_size);
			}

			/* Capacity: Returns the maximum possible number of elements */
			size_type	max_size() const
			{
				return (std::min(this->_node_alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max())));
			}

			/* Modifiers: Clears the contents */
			void	clear()
			{
				this->destroy(this->root());
				this->_leaf_node._left = NULL;
				this->_leaf_node_ptr = this->end_node();
				this->_size = 0;
			}

			/* Modifiers: Swaps the contents */
			void	swap(rbtree& other)
			{
				std::swap(this->_leaf_node_ptr, other._leaf_node_ptr);
				std::swap(this->_leaf_node, other._leaf_node);
				std::swap(this->_size, other._size);
				std::swap(this->_comp, other._comp);
				if (this->size() == 0)
					this->_leaf_node_ptr = this->end_node();
				else
					this->end_node()->_left->_parent = this->end_node();
				if (other.size() == 0)
					other._leaf_node_ptr = other.end_node();
				else
					other.end_node()->_left->_parent = other.end_node();
			}

			/* Observers: Returns the function that compares keys in objects of type value_type */
			value_compare&	value_comp()
			{
				return (this->_comp);
			}

			const value_compare&	value_comp() const
			{
				return (this->_comp);
			}

		private:
			/* Helper function: Destroys a node */
			void	destroy(node_pointer node)
			{
				if (node == NULL)
					return ;
				this->destroy(node->_left);
				this->destroy(node->_right);
				_value_alloc.destroy(&node->_value);
				_node_alloc.deallocate(node, 1);
			}

			/* Helper function: Returns the leaf node in pointer type */
			leaf_node_pointer	end_node()
			{
				return (static_cast<leaf_node_pointer>(&this->_leaf_node));
			};

			leaf_node_pointer	end_node() const
			{
				return (static_cast<leaf_node_pointer>(&this->_leaf_node));
			};

			/* Helper function: Returns the root node */
			node_pointer	root() const
			{
				return (this->end_node()->_left);
			}

			/* Member object */
			node_allocator		_node_alloc;
			allocator_type		_value_alloc;
			value_compare		_comp;
			leaf_node_type		_leaf_node;
			leaf_node_pointer	_leaf_node_ptr;
			size_type			_size;
	};
}


#endif
