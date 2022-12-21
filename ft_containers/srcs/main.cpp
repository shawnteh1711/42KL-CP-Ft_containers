/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:36:16 by schuah            #+#    #+#             */
/*   Updated: 2022/12/21 14:59:54 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_containers.hpp"
#include <vector>

int	main(void)
{
	// ft::vector<int>	vct1;
	ft::vector<int> vct2(10);
	ft::vector<int>	vct3(10, 10);
	std::vector<std::string> words1;

	int arr[] = { 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
  
    ft::vector<int> vct4(arr, arr + n);
	ft::vector<int> vct6(vct3.begin(), vct3.end());
	for (int i = 0; i < (int)vct6.size(); i++)
	{
		printf("%d \n", vct6[i]);
	}
	ft::vector<int> vct7(vct3);

	char	*str = strdup("Hello World");
	std::cout << 3[str] << std::endl;
	std::cout << 4[str] << std::endl;

	ft::pair<int, int> t;

	ft::map<char, int> yes;
	
	return (0);
}
