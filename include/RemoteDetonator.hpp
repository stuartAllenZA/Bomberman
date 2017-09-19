#ifndef REMOTEDETONATOR_HPP
#define REMOTEDETONATOR_HPP

#include <Drop.hpp>

class RemoteDetonator : public Drop {
	public:
		RemoteDetonator(std::pair<int, int> xy);
		~RemoteDetonator();
		RemoteDetonator(RemoteDetonator const & src);
		RemoteDetonator	&operator=(RemoteDetonator const &src);
	private:
};

#endif

