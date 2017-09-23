#ifndef INCLUDE_BREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_BREAKABLE_BOX_CLASS_HPP_

#include <Box.hpp>
#include <Drop.hpp>

class BreakableBox : public Box {
public:
	BreakableBox();
	BreakableBox(Drop *drop);
	BreakableBox(std::pair<float, float> xy);
	BreakableBox(std::pair<float, float> xy, Drop *drop);
	~BreakableBox();
	BreakableBox(BreakableBox const &src);
	BreakableBox		&operator=(BreakableBox const &src);
};

#endif

