#include <Enemy.hpp>

Enemy::Enemy(std::pair<float, float> xy, int speed, int health, int lives) : Character(xy, speed, health, lives) {
	std::cout << "Enemy with XY, Speed, Health & Lives Constructed\n";
}

Enemy::Enemy(std::pair<float, float> xy, int speed, int health) : Character(xy, speed, health) {
	std::cout << "Enemy with XY, Speed & Health Constructed\n";
}

Enemy::Enemy(std::pair<float, float> xy, int lives) : Character(xy, lives) {
	std::cout << "Enemy with XY & Lives Constructed\n";
}

Enemy::Enemy(std::pair<float, float> xy) : Character(xy) {
	std::cout << "Enemy with XY Constructed\n";
}

Enemy::Enemy(int lives) : Character(lives) {
	std::cout << "Enemy with Lives Constructed\n";
}

Enemy::Enemy() : Character() {
	std::cout << "Enemy Default Constructed\n";
}

Enemy::Enemy(Enemy const & src) {
	//std::cout << "Enemy Copy-Constructed\n";
	*this = src;
}

Enemy::~Enemy() {
	//std::cout << "Enemy De-Constructed\n";
}

Enemy &	Enemy::operator=(Enemy const & src) {
	Character::operator=(src);
	return (*this);
}

std::pair<float, float>	Enemy::getNewCoOrd() const {
	return (this->_newCoOrd);
}

void					Enemy::setNewCoOrd(const std::pair<float, float> newCoOrd) {
	this->_newCoOrd = newCoOrd;
}

void					Enemy::determineNewCoOrds(std::vector<char> able) {
	static unsigned long int		cnt = 0;
	int 							randomOri;
	char							oldOri;
	//Set to current XY
	_newCoOrd = this->_xy;
	oldOri = _ori;
	//Determine correct ori
	if (cnt % 120 == 0) {
		randomOri = rand() % able.size();
		_ori = able[randomOri];
	}
	cnt++;
	//Determine new co-ords
	if (_ori == 'E')
		_newCoOrd.first = static_cast<int>(_newCoOrd.first + (_speed * (0.5 * _size)));
	else if (_ori == 'W')
		_newCoOrd.first = static_cast<int>(_newCoOrd.first - (_speed * (0.5 * _size)));
	else if (_ori == 'N')
		_newCoOrd.second = static_cast<int>(_newCoOrd.second + (_speed * (0.5 * _size)));
	else if (_ori == 'S')
		_newCoOrd.second = static_cast<int>(_newCoOrd.second - (_speed * (0.5 * _size)));
	//if (_newCoOrd == playerPos)
		//_newCoOrd = _xy;
}

float					Enemy::getPenetration(std::pair<float, float> playerPos) {
	float	penetration = 0.0;
	if (_ori == 'E' && _xy.first + _attackSize >= playerPos.first)
		penetration = playerPos.first - (_xy.first + _attackSize);
	else if (_ori == 'W' && _xy.first - _attackSize <= playerPos.first)
		penetration = (_xy.first - _attackSize) - playerPos.first;
	else if (_ori == 'N' && _xy.second + _attackSize >= playerPos.second)
		penetration = playerPos.second - (_xy.second + _attackSize);
	else if (_ori == 'S' && _xy.second - _attackSize <= playerPos.second)
		penetration = (_xy.second - _attackSize) - playerPos.second;
	return (penetration);
}

std::ostream & 			operator<<(std::ostream & o, Enemy const & rhs) {
	std::pair<float, float>	xy = rhs.getXY();
	o << "Dumping Enemy State\nX: " << xy.first <<"\tY: " << xy.second <<
	"\nSpeed: " << rhs.getSpeed() <<
	"\nHealth: " << rhs.getHealth() <<
	"\nLives: " << rhs.getLives() << std::endl;
	return o;
}