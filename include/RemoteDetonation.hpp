#ifndef INCLUDE_REMOTE_DETONATOR_CLASS_HPP_
#define INCLUDE_REMOTE_DETONATOR_CLASS_HPP_

#include "Drops.hpp"

class RemoteDetonator : public Drop {
	public:
		RemoteDetonator();
		~RemoteDetonator();
		RemoteDetonator(RemoteDetonator const & src);
		RemoteDetonator	&operator=(RemoteDetonator const &src);
	private:
};

#endif

