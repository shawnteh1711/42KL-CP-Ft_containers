/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_algorithm.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:24:10 by schuah            #+#    #+#             */
/*   Updated: 2022/12/14 14:21:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ALGORITHM_HPP
# define RBTREE_ALGORITHM_HPP

# include "rbtree_types.hpp"

/**
 * https://youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin
 * 
 * Rules:
 * 	1. Every node is either red or black
 * 	2. The root of the tree is black
 * 	3. Every leaf (end of the tree branch or NULL) is black
 * 	4. If a node is red, then both of its children must be black
 * 	5. All paths from a node to descendants leaves contain the same number of black nodes
 */
namespace ft
{
	/* Boolean to check if the node is a left child */
	template <class Node>
	bool is_left_child(Node node)
	{
		return (node == node->_parent->_left);
	}

	/* Boolean to check if the node is black*/
	template <class Node>
	bool	node_is_black(Node node)
	{
		return (node == NULL || node->_black);
	}

	/* Returns the most right node of the branch (Highest value) */
	template <class Node>
	Node	most_right_node(Node node)
	{
		while (node->_right != NULL)
			node = node->_right;
		return (node);
	}

	/* Returns the most left node of the branch (Lowest value) */
	template <class Node>
	Node	most_left_node(Node node)
	{
		while (node->_left != NULL)
			node = node->_left;
		return (node);
	}

	/* Iterates to the next node */
	template <class It, class Node>
	It	iter_to_next(Node node)
	{
		if (node->_right != NULL)
			return (most_left_node(node->_right));
		while (is_left_child(node) == 0)
			node = node->get_parent_ptr();
		return (node->_parent);
	}

	/* Iterates to the previous node */
	template <class Node, class It>
	It	iter_to_prev(It iter)
	{
		if (iter->_left != NULL)
			return (most_right_node(iter->_left));
		Node	node = static_cast<Node>(iter);
		while (is_left_child(node))
			node = node->get_parent_ptr();
		return (node->_parent);
	}

	/* Rotates a node to the left */
	template <class Node>
	void	node_rotate_left(Node node)
	{
		Node	rightchild = node->_right;
		node->_right = rightchild->_left;
		if (rightchild->_left != NULL)
			rightchild->_left->set_parent_ptr(node);
		rightchild->_parent = node->_parent;
		if (is_left_child(node))
			node->_parent->_left = rightchild;
		else
			node->get_parent_ptr()->_right = rightchild;
		rightchild->_left = node;
		node->set_parent_ptr(rightchild);
	}

	/* Rotates a node to the right */
	template <class Node>
	void	node_rotate_right(Node node)
	{
		Node	leftchild = node->_left;
		node->_left = leftchild->_right;
		if (leftchild->_right != NULL)
			leftchild->_right->set_parent_ptr(node);
		leftchild->_parent = node->_parent;
		if (is_left_child(node))
			node->_parent->_left = leftchild;
		else
			node->get_parent_ptr()->_right = leftchild;
		leftchild->_right = node;
		node->set_parent_ptr(leftchild);
	}

	/* Rotates a node branch to the left */
	template <class Node>
	void	branch_rotate_left(Node& root, Node node)
	{
		if (node == root)
			root = node->_right;
		node_rotate_left(node);
	}

	/* Rotates a node branch to the right */
	template <class Node>
	void	branch_rotate_right(Node& root, Node node)
	{
		if (node == root)
			root = node->_left;
		node_rotate_right(node);
	}

	/**
	 * Startegy:
	 * 	1. Insert Z and color it red
	 * 	2. Recolor and rotate nodes to fix violation to rbtree rules
	 *  
	 * Insertion cases:
	 * 	1. Z is root
	 * 		- Color Z to be black
	 * 	2. Z's uncle is red
	 * 		- Recolor Z's parent, grandparent and uncle
	 * 	3. Z's uncle is black (Triangle)
	 * 		- Z, Z's parent A and grandparent B form a triangle
	 * 		- Z is a left child, and Z's parent A is a right child
	 * 		- Rotate Z's parent in the opposite direction of Z, so Z takes the place of A
	 * 
	 * 			     BB     \					       BB
	 * 			    /  \     \			   	   	      /  \
	 * 	  Uncle -> BC  RA     \	     =>     Uncle -> BC  RZ <- Z
	 * 			      /	      /						       \
	 * 			Z -> RZ      /						       RA
	 * 
	 * 	4. Z's uncle is black (Line)
	 * 		- Z, Z's parent and grandparent form a line
	 * 		- Z and Z's parent are right childs
	 * 		- Rotate Z's grandparent in the opposite direction of Z, so A takes the place of B
	 * 		- Recolor the original parent and grandparent after the rotation
	 * 
	 *               BB     \                             RA                       BA
	 *              /  \     \                           /  \                     /  \
	 *    Uncle -> BC  RA     \       =>                BB  RZ <- Z     =>       RB   RZ
	 *                   \     \                       /                        /
	 *              Z -> RZ     \            Uncle -> BC                       BC
	 * 
	 * 
	 *  Notes: 
	 * 		1. Same instructions are applied to the mirrored cases of 3 and 4
	 * 		2. Examples used are branches of a RBTree
	 */
}

#endif
