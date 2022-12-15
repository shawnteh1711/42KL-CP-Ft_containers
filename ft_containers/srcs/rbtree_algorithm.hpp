/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_algorithm.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:24:10 by schuah            #+#    #+#             */
/*   Updated: 2022/12/15 14:55:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ALGORITHM_HPP
# define RBTREE_ALGORITHM_HPP

# include "rbtree_types.hpp"

/**
 * https://youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin
 * https://youtu.be/CTvfzU_uNKE
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
	bool	node_is_left_child(Node node)
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
		while (node_is_left_child(node) == false)
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
		while (node_is_left_child(node))
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
		if (node_is_left_child(node))
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
		if (node_is_left_child(node))
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
	 * Insertion startegy:
	 * 	1. Insert Z and color it red
	 * 	2. Recolor and rotate nodes to fix violation to rbtree rules
	 *  
	 * Post-insertion cases:
	 * 	1. Z is root
	 * 		- Color Z to be black
	 * 	2. Z's uncle is red
	 * 		- Color Z's parent and uncle to black
	 * 		- COlor Z's grandparent to red
	 * 
	 *              BG                  RG
	 *             /  \                /  \
	 *           RP    RU     ->     BP    BU
	 *             \                   \
	 *              RZ                  RZ
	 * 
	 * 	3. Z's uncle is black (Triangle)
	 * 		- Z, Z's parent and grandparent form a triangle
	 * 		- Z is a left child, and Z's parent is a right child
	 * 		- Rotate Z's parent in the opposite direction of Z, so Z takes the place of its parent
	 * 
	 * 			    BG      \		          BG
	 * 			   /  \      \	             /  \
	 *           BU    RP     \     ->     BU    RZ
	 * 			      /	      /	       	           \
	 * 			    RZ       /	       	            RP
	 * 
	 * 	4. Z's uncle is black (Line)
	 * 		- Z, Z's parent and grandparent form a line
	 * 		- Z and Z's parent are right childs
	 * 		- Rotate Z's grandparent in the opposite direction of Z, so A takes the place of B
	 * 		- Color Z's parent to black
	 * 		- Color Z's grandparent to red
	 * 
	 *              BG       \                      RP                    BP
	 *             /  \       \                    /  \                  /  \
	 *           BU    RP      \       ->        BG    RZ     ->       RG    RZ
	 *                   \      \               /                     /
	 *                    RZ     \            BU                    BU
	 * 
	 *  Notes: 
	 * 		1. Example terms used:
	 * 			- The first letter determines the color of the node: B for black, R for Red
	 * 			- The second letter determines the relationship between the node and Z: G for grandparent, P for parent, U for uncle 
	 * 		2. Same instructions are applied to the mirrored cases of 3 and 4
	 * 		3. Examples used are branches of a RBTree
	 * 		4. All cases apply when the condition is mirrored
	 */
	template <class Node>
	void	btree_insert(Node root, Node z)
	{
		/* Case 1 */
		z->_black = (z == root);
		while (z != root && z->get_parent_ptr()->_black == false)
		{
			if (node_is_left_child(z->get_parent_ptr()))
			{
				Node	uncle = z->get_parent_ptr()->get_parent_ptr()->_right;
				
				/* Case 2 */
				if (node_is_black(uncle) == false)
				{
					uncle->_black = true;
					z = z->get_parent_ptr();
					z->_black = true;
					z = z->get_parent_ptr();
					z->_black = (z == root);
				}
				else
				{
					/* Case 3 */
					if (node_is_left_child(z) == false)
					{
						z = z->get_parent_ptr();
						node_rotate_left(z);
					}

					/* Case 4 */
					z = z->get_parent_ptr();
					z->_black = true;
					z = z->get_parent_ptr();
					z->_black = false;
					node_rotate_right(z);
					return ;
				}
			}
			else
			{
				Node	uncle = z->get_parent_ptr()->get_parent_ptr()->_left;

				/* Case 2 */
				if (node_is_black(uncle) == false)
				{
					uncle->_black = true;
					z = z->get_parent_ptr();
					z->_black = true;
					z = z->get_parent_ptr();
					z->_black = (z == root);
				}
				else
				{
					/* Case 3 */
					if (node_is_left_child(z))
					{
						z = z->get_parent_ptr();
						node_rotate_right(z);
					}

					/* Case 4 */
					z = z->get_parent_ptr();
					z->_black = true;
					z = z->get_parent_ptr();
					z->_black = false;
					node_rotate_left(z);
					return ;
				}
			}
		}
	}
	
	/**
	 * Deletion strategy:
	 *	1. Find the node to be deleted using binary search tree traversal
	 *	2. If node to be deleted has 2 non-null children, replace it with its inorder successor, then delete inorder successor
	 *	3. If node to be deleted is red then just delete it
	 * 	4. If node to be deleted is black but has one red child, replace it with that child and change color of child to black
	 * 	5. Otherwise, refer to the 6 cases below
	 * 
	 * Deletion cases:
	 * 	1. Double-black node is root (Terminal case)
	 * 		- (Optional) Color Z to be black
	 * 	2. Double-black node has a black parent, red sibling with two black child
	 * 		- Left rotation on double-black node's parent
	 * 		- Color double-black node's parent to red
	 * 		- Color double-black node's sibling to black
	 * 
	 *              BP                        BS
	 *             /  \                      /  \
	 *           DB    RS        ->        RP    BR
	 *                /  \                /  \ 
	 *              BL    BR            DB    BL
	 * 
	 * 	3. Double-black node has a black parent, black sibling with two black child
	 * 		- Color double-black node's sibling to red
	 * 		- Double-black node's parent becomes double-black
	 * 		- Refer to all cases again
	 * 
	 *              BP                     DBP
	 *             /  \                   /  \
	 *           DB    BS        ->      B    RS
	 *                /  \                   /  \
	 *              BL    BR               BL    BR
	 * 
	 * 	4. Double-black node has a red parent, black sibling with two black child (Terminal case)
	 * 		- Recolor parent and sibling
	 * 
	 *              RP	                   BP
	 *             /  \                   /  \
	 *           DB    BS        ->      B    RS
	 *                /  \                   /  \
	 *              BL    BR               BL    BR
	 * 
	 * 	5. Double-black node has a black parent, a black sibling with a red left child and black right child
	 * 		- Right rotation on double-black node's sibling
	 * 		- Color double-black node's sibling's left child to black
	 * 		- Color double-black node's sibling to red
	 * 
	 *              BP                     BP
	 *             /  \                   /  \
	 *           DB    BS        ->     DB    BL
	 *                /  \                      \
	 *              RL    BR                     RS
	 *                                             \
	 *                                              BR
	 * 
	 * 	6. Double-black node has a black sibling with a red right child (Terminal case)
	 * 		- Left rotation on double-black node's parent
	 * 		- Color double-black node's sibling with their parent's color
	 * 		- Color double-black node's parent and its black sibling's right child to black
	 * 
	 *              RBP                      RBS
	 *             /  \                      /  \
	 *           DB    BS        ->        BP    BR
	 *                /  \                /  \
	 *              RBL   RR             B   RBL
	 * 
	 *  Notes: 
	 * 		1. Example terms used:
	 * 			- The first letter (or two) determines the color of the node: B for black, R for red, DB for double-black, RB for either red or black
	 * 			- The last letter determines the relationship between the node and double-black: P for parent, S for sibling, L for left child, R for right child
	 * 		2. Case 1, 4 and 6 are terminal cases, means the tree is back to be RBTree after performing the changes
	 * 		3. Double-black node exists when the deleted node has two black child, this is to maintain the temporary balance of the RBTree until further adjustments are made
	 * 		4. Examples used are branches of a RBTree
	 * 		5. All cases apply when the condition is mirrored
	 */
	template <class Node>
	void	btree_delete_fixup(Node root, Node rchild_parent)
	{
		Node	dbnode = NULL;
		Node	sibling;

		while (root != dbnode && node_is_black(dbnode))
		{
			if (dbnode == rchild_parent->_left)
			{
				sibling = rchild_parent->_right;

				/* Case 2 */
				if (sibling->_black == false)
				{
					rchild_parent->_black = false;
					sibling->_black = true;
					branch_rotate_left(root, rchild_parent);
					sibling = rchild_parent->_right;
				}

				/* Case 3 and Case 4 */
				if (node_is_black(sibling->_left) && node_is_black(sibling->_right))
				{
					sibling->_black = false;
					dbnode = rchild_parent;
					rchild_parent = dbnode->get_parent_ptr();
				}
				else
				{
					/* Case 5 */
					if (node_is_black(sibling->_right))
					{
						sibling->_black = false;
						branch_rotate_right(root, sibling);
						sibling = rchild_parent->_right;
						sibling->_black = true;
					}

					/* Case 6 */
					sibling->_black = rchild_parent->_black;
					rchild_parent->_black = true;
					sibling->_right->_black = true;
					branch_rotate_left(root, rchild_parent);
					dbnode = root;
					break ;
				}
			}
			else
			{
				sibling = rchild_parent->_left;
				
				/* Case 2 */
				if (sibling->_black == false)
				{
					rchild_parent->_black = false;
					sibling->_black = true;
					branch_rotate_right(root, rchild_parent);
					sibling = rchild_parent->_left;
				}

				/* Case 3 and Case 4 */
				if (node_is_black(sibling->_right) && node_is_black(sibling->_left))
				{
					sibling->_black = false;
					dbnode = rchild_parent;
					rchild_parent = dbnode->get_parent_ptr();
				}
				else
				{
					/* Case 5 */
					if (node_is_black(sibling->_left))
					{
						sibling->_black = false;
						branch_rotate_left(root, sibling);
						sibling = rchild_parent->_left;
						sibling->_black = true;
					}

					/* Case 6 */
					sibling->_black = rchild_parent->_black;
					rchild_parent->_black = true;
					sibling->_left->_black = true;
					branch_rotate_right(root, rchild_parent);
					dbnode = root;
					break ;
				}
			}
		}

		/* Case 1 and Case 3 if parent is red */
		if (dbnode)
			dbnode->_black = true;
	}


	template <class Node>
	void	btree_delete(Node root, Node remove)
	{
		Node	lchild = remove;
		Node	rchild_parent;
		Node	rchild;
		bool	removed;

		/* If remove has 2 non-null children, replace it with its inorder successor */
		if (lchild->_left != NULL && lchild->_right != NULL)
			lchild = most_left_node(remove->_right);
		rchild_parent = lchild->get_parent_ptr();
		rchild = lchild->_right;
		if (lchild->_left != NULL)
			rchild = lchild->_left;
		if (rchild != NULL)
			rchild->_parent = lchild->_parent;
		if (node_is_left_child(lchild))
		{
			lchild->_parent->_left = rchild;
			if (lchild == root)
				root = rchild;
		}
		else
		{
			if (remove->_right == lchild)
				rchild_parent = lchild;
			lchild->get_parent_ptr()->_right = rchild;
		}
		removed = lchild->_black;

		/* If lchild is remove's in order successor, transplant lchild into target's place */
		if (lchild != remove)
		{
			lchild->_black = remove->_black;
			lchild->_parent = remove->_parent;
			if (node_is_left_child(remove))
				lchild->_parent->_left = lchild;
			else
				lchild->get_parent_ptr()->_right = lchild;
			lchild->_left = remove->_left;
			lchild->_left->set_parent_ptr(lchild);
			lchild->_right = remove->_right;
			if (lchild->_right)
				lchild->_right->set_parent_ptr(lchild);
			if (remove == root)
				root = lchild;
		}

		/* Check if a black node was removed */
		if (removed)
		{
			if (root == NULL)
				return ;
			if (rchild != NULL)
			{
				rchild->_black = true;
				return ;
			}
			btree_delete_fixup(root, rchild_parent);
		}
	}
}

#endif
