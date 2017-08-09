/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 13:07:48 by lchimes           #+#    #+#             */
/*   Updated: 2017/08/09 13:07:49 by lchimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



Menu::Menu() : currentSelection(0) {
	std::cout << "Menu Default Constructed\n";
}

Menu::Menu(Menu const & src) {
	std::cout << "Menu Copy-Constructed\n";
	*this = src;
}

Menu &  Character::operator=(Menu const & src) {
    std::cout << "Menu Constructed (OPERATOR OVERLOAD)"
	this->_currentSelection = src.getCurrentSelection();
	return (*this);
}

Menu::~Menu() {
	std::cout << "Menu Destructed\n";
}
