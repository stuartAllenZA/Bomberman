#include <header.hpp>

int main(int argc, char **argv) {
	try {
	
	}

	catch (Exceptions::UndefinedObject const & exception) {
		std::cerr
			<< "undefined object exception: "
			<< exception.what()
			<< std::endl
			;
	}

	catch (Exceptions::UndefinedSymbol const & exception) {
		std::cerr
			<< "undefined symbol exception: "
			<< exception.what()
			<< std::endl
			;
	}

	catch (std::exception const & exception)
	{
		std::cerr
			<< "std::exception: "
			<< exception.what()
			<< std::endl
			;
	}

	catch (...)
	{
		std::cerr
			<< "unknown exception: "
			<< std::endl
			;
	}

	return 0;
}

