/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 13:01:20 by lchimes           #+#    #+#             */
/*   Updated: 2017/08/09 13:01:22 by lchimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>

class Menu
{
public:
	Menu();
	~Menu();
	Menu(Menu const & src)
	Menu &			operator=(Menu const & src);
	int				getCurrentSelection() const;
	void			setCurrentSelection(const int newSelection);
private:
	int				currentSelection;
};

#endif
