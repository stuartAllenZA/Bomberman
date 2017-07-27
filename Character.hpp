/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 13:23:17 by tmaske            #+#    #+#             */
/*   Updated: 2017/07/27 13:23:27 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>

class Character
{
public:
	Character();
	Character(Character const & src);
	~Character();
	Character & 			operator=(Character const & src);
	std::string				getDirection() const;
	void					setDirection(std::string name);

private:
	std::string				direction;
	int						speed;
	int						x;
	int						y;
};

#endif