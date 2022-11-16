/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:36:16 by schuah            #+#    #+#             */
/*   Updated: 2022/11/16 21:18:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"

int	main(void)
{
	// ft::vector<int>	vct1;
	ft::vector<int> vct2(10);
	ft::vector<int>	vct3(10, 10);
	// ft::vector<int> vct4{10, 20, 30};

	int arr[] = { 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
  
    ft::vector<int> vct5(arr, arr + n);
	// ft::vector<int> vct6(vct4.begin(), vct4.end());
	ft::vector<int> vct7(vct3);

	
	return (0);
}
