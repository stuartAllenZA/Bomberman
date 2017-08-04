#ifndef INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_
#define INCLUDE_UNBREAKABLE_BOX_CLASS_HPP_

class UnbreakableBox {
	public:
		UnbreakableBox();
		~UnbreakableBox();
		UnbreakableBox(UnbreakableBox const &src);
		UnbreakableBox		&operator=(UnbreakableBox const &src);
	private:
};

#endif

