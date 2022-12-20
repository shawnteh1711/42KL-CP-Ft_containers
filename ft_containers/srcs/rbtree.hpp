/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:56:56 by schuah            #+#    #+#             */
/*   Updated: 2022/12/20 17:46:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "rbtree_iterator.hpp"

namespace ft
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

		private:
			/* Helper types */
			typedef typename rbt_node_types<value_type>::node_type				node_type;
			typedef typename rbt_node_types<value_type>::leaf_node_type			leaf_node_type;
			typedef typename rbt_node_types<value_type>::node_pointer			node_pointer;
			typedef typename rbt_node_types<value_type>::leaf_node_pointer		leaf_node_pointer;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;

		public:
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

			/* Modifiers: Inserts value */
			pair<iterator, bool>	insert(const value_type& value)
			{
				leaf_node_pointer	parent;
				node_pointer&		child_ref = get_pos_key(parent, value);
				iterator			it(child_ref);
				bool				inserted = false;

				if (child_ref == NULL)
				{
					it = insert_pos(child_ref, parent, value);
					inserted = true;
				}
				return (ft::make_pair(it, inserted));
			}

			/* Modifiers: Inserts value in the position as close as possible to the possible to the position just prior to pos */
			iterator	insert(const_iterator pos, const value_type& value)
			{
				leaf_node_pointer	parent;
				node_pointer		temp;
				node_pointer&		child = get_pos_iterator(iterator(pos.base()), parent, value, temp);
				iterator			it(child);
			
				if (child == NULL)
					it = insert_pos(child, parent, value);
				return (it);
			}

			/* Modifiers: Inserts elements from rnage [first, last] */
			template <class InputIt>
			void	insert(InputIt first, InputIt last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			/* Modifiers: Removes the element at pos */
			iterator	erase(const_iterator pos)
			{
				const_iterator	next(pos);
				++next;

				if (this->_leaf_node_ptr == pos.base())
					this->_leaf_node_ptr = next.base();
				
				node_pointer	ptr = pos.node_ptr();
				btree_delete(end_node()->_left, ptr);
				this->_value_alloc.destroy(&ptr->_value);
				this->_node_alloc.deallocate(ptr, 1);
				this->_size--;
				return (iterator(next.base()));
			}

			/* Modifiers: Removes the elements in the range [first, last), which must be a valid range in *this */
			void	erase(const_iterator first, const_iterator last)
			{
				while (first != last)
					first = erase(first);
			}

			/* Modifiers: Removes the element (if one exists) with the key */
			template <class Key>
			size_type	erase(const Key& key)
			{
				const_iterator	it = this->find(key);

				if (it == this->end())
					return (0);
				erase(it);
				return (1);
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

			/* Lookup: Returns the number of elements matching specific key */
			template <class Key>
			size_type	count(const Key& key) const
			{
				return (this->get_node_pointer(key) == NULL) ? 0 : 1;
			}

			/* Lookup: Finds element with specific key */
			template <class Key>
			iterator	find(const Key& key)
			{
				leaf_node_pointer	ptr = this->get_node_pointer(key);
				return (ptr == NULL) ? iterator(end_node()) : iterator(ptr);
			}

			template <class Key>
			const_iterator	find(const Key& key) const
			{
				leaf_node_pointer	ptr = this->get_node_pointer(key);
				return (ptr == NULL) ? const_iterator(end_node()) : const_iterator(ptr);
			}

			/* Compares the keys to key */
			template <class Key>
			pair<iterator, iterator>	equal_range(const Key& key)
			{
				pair<leaf_node_pointer, leaf_node_pointer>	range = get_equal_range(key);
				return (ft::make_pair(iterator(range.first), iterator(range.second)));
			}

			template <class Key>
			pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				pair<leaf_node_pointer, leaf_node_pointer>	range = get_equal_range(key);
				return (ft::make_pair(const_iterator(range.first), const_iterator(range.second)));
			}

			/* Lookup: Returns an iterator pointing to the first element that is not less than (i.e. greator or equal to) key */
			template <class Key>
			iterator	lower_bound(const Key& key)
			{
				return (iterator(get_lower_bound(key)));
			}

			template <class Key>
			const_iterator	lower_bound(const Key& key) const
			{
				return (const_iterator(get_lower_bound(key)));
			}

			/* Lookup: Returns an iterator pointing to the first element that is greater than key */
			template <class Key>
			iterator	upper_bound(const Key& key)
			{
				return (iterator(get_upper_bound(key)));
			}

			template <class Key>
			const_iterator	upper_bound(const Key& key) const
			{
				return (iterator(get_upper_bound(key)));
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

			/* Helper function: Returns the end node */
			leaf_node_pointer	end_node()
			{
				return (static_cast<leaf_node_pointer>(&this->_leaf_node));
			}

			leaf_node_pointer	end_node() const
			{
				return (const_cast<leaf_node_pointer>(&this->_leaf_node));
			}

			/* Helper function: Get equal range */
			template <class Key>
			pair<leaf_node_pointer, leaf_node_pointer>	get_equal_range(const Key& key) const
			{
				node_pointer		ptr = this->root();
				leaf_node_pointer	ub = this->end_node();
				leaf_node_pointer	lb = this->end_node();

				while (ptr != NULL)
				{
					if (value_comp()(key, ptr->_value))
					{
						ub = static_cast<leaf_node_pointer>(ptr);
						lb = static_cast<leaf_node_pointer>(ptr);
						ptr = ptr->_left;
					}
					else if (value_comp()(ptr->_value, key))
						ptr = ptr->_right;
					else
					{
						lb = static_cast<leaf_node_pointer>(ptr);
						if (ptr->_right != NULL)
							ub = static_cast<leaf_node_pointer>(most_left_node(ptr->_right));
						break ;
					}
				}
				return (ft::make_pair(lb, ub));
			}

			/* Helper function: Get the lower bound node */
			template <class Key>
			leaf_node_pointer	get_lower_bound(const Key& key) const
			{
				leaf_node_pointer	pos = this->end_node();
				node_pointer		ptr = this->root();

				while (ptr != NULL)
				{
					if (value_comp()(ptr->_value, key))
						ptr = ptr->_right;
					else
					{
						pos = static_cast<leaf_node_pointer>(ptr);
						ptr = ptr->_left;
					}
				}
				return (pos);
			}

			/* Helper function: Get the node's pointer based on the key */
			template <class Key>
			leaf_node_pointer	get_node_pointer(const Key& key) const
			{
				node_pointer	ptr = this->root();
				while (ptr != NULL)
				{
					if (this->value_comp()(key, ptr->_value))
						ptr = ptr->_left;
					else if (value_comp()(ptr->_value, key))
						ptr = ptr->_right;
					else
						return (static_cast<leaf_node_pointer>(ptr));
				}
				return (NULL);
			}

			/* Helper function: Get the position of the node based on the key */
			template<class Key>
			node_pointer&	get_pos_key(leaf_node_pointer& parent, const Key& key) const
			{
				node_pointer	node = this->root();
				node_pointer	*node_ptr = &this->end_node()->_left;

				while (node != NULL)
				{
					if (value_comp()(key, node->_value))
					{
						if (node->_left != NULL)
						{
							node_ptr = &node->_left;
							node = node->_left;
						}
						else
						{
							parent = static_cast<leaf_node_pointer>(node);
							return (node->_left);
						}
					}
					else if (value_comp()(node->_value, key))
					{
						if (node->_right != NULL)
						{
							node_ptr = &node->_right;
							node = node->_right;
						}
						else
						{
							parent = static_cast<leaf_node_pointer>(node);
							return (node->_right);
						}
					}
					else
					{
						parent = static_cast<leaf_node_pointer>(node);
						return (*node_ptr);
					}
				}
				parent = static_cast<leaf_node_pointer>(end_node());
				return (parent->_left);
			}

			/* Helper function: Get the position of the node based on the iterator */
			template<class Key>
			node_pointer&	get_pos_iterator(iterator it, leaf_node_pointer& parent, const Key& key, node_pointer& temp) const
			{
				if (it == this->end() || value_comp()(key, *it))
				{
					const_iterator	prev = it;
					if (prev == begin() || value_comp()(*--prev, key))
					{
						if (it.base()->_left == NULL)
						{
							parent = it.base();
							return (parent->_left);
						}
						else
						{
							parent = prev.base();
							return (prev.node_ptr()->_right);
						}
					}
					return (get_pos_key(parent, key));
				}
				else if (value_comp()(*it, key))
				{
					const_iterator	next = it;
					++next;
					if (next == end() || value_comp()(key, *next))
					{
						if (it.node_ptr()->_right == NULL)
						{
							parent = it.base();
							return (it.node_ptr()->_right);
						}
						else
						{
							parent = next.base();
							return (parent->_left);
						}
					}
					return (get_pos_key(parent, key));
				}
				parent = it.base();
				temp = it.node_ptr();
				return (temp);
			}

			/* Helper function: Get the upper bound node */
			template <class Key>
			leaf_node_pointer	get_upper_bound(const Key& key) const
			{
				leaf_node_pointer	pos = this->end_node();
				node_pointer		ptr = this->root();

				while (ptr != NULL)
				{
					if (value_comp()(key, ptr->_value))
					{
						pos = static_cast<leaf_node_pointer>(ptr);
						ptr = ptr->_left;
					}
					else
						ptr = ptr->_right;
				}
				return (pos);
			}

			/* Helper function: Insert a new node into the pos */
			iterator	insert_pos(node_pointer& pos, leaf_node_pointer parent, const value_type& value)
			{
				pos = this->_node_alloc.allocate(1);
				pos->_left = NULL;
				pos->_right = NULL;
				pos->_parent = parent;
				this->_value_alloc.construct(&pos->_value, value);
				if (this->_leaf_node_ptr->_left != NULL)
					this->_leaf_node_ptr = this->_leaf_node_ptr->_left;
				this->_size++;
				node_pointer ptr = pos;
				btree_insert(this->end_node()->_left, ptr);
				return (iterator(ptr));
			}

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
