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

#include <string>
#include <iostream>
#include <vector>

class Character
{
public:
	Character(std::pair<int, int> xy, int lives);
	Character(std::pair<int, int> xy);
	Character(int lives);
	Character();
	Character(Character const & src);
	virtual ~Character() =0;
	Character &			operator=(Character const & src);
	std::pair<int, int>	getXY() const;
	void				setXY(const std::pair<int, int> xy);
	int					getSpeed() const;
	void				setSpeed(const int newSpeed);
	int					getHealth() const;
	void				setHealth(const int newHealth);
	int					getLives() const;
	void				setLives(const int newLives);
	virtual std::string	getFileLocation() const = 0;
	virtual void		setFileLocation(const std::string newLocation) = 0;
	virtual std::string	getName() const = 0;
	virtual void		setName(const std::string newName) = 0;
	virtual int			getLevel() const = 0;
	virtual void		setLevel(const int newLevel) = 0;
	virtual int			getExperience() const = 0;
	virtual void		setExperience(const int newExp) = 0;

private:
	std::pair<int, int>	_xy;
	int					_speed;
	int					_health;
	int					_lives;
	
};

#endif