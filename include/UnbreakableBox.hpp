#ifndef INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_

#include <Box.hpp>
#include <Drop.hpp>

class UnbreakableBox : public Box {
public:
	UnbreakableBox();
	UnbreakableBox(Drop *drop);
	UnbreakableBox(std::pair<float, float> xy);
	UnbreakableBox(std::pair<float, float> xy, Drop *drop);
	~UnbreakableBox();
	UnbreakableBox(UnbreakableBox const &src);
	UnbreakableBox		&operator=(UnbreakableBox const &src);
};

#endif

