/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 13:23:09 by tmaske            #+#    #+#             */
/*   Updated: 2017/07/27 13:23:10 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() {

}

Character::Character(Character const & src) {
	*this = src;
}

Character::~Character() {
}

Character &		Character::operator=(Character const & src) {
	return (*this);
}

std::string Character::getDirection() const {
	return (this->name);
}

void		Character::setDirection(std::string direction) {
	this->direction = direction;
}