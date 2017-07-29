#ifndef INCLUDE_SAVE_CLASS_HPP_
#define INCLUDE_SAVE_CLASS_HPP_

#include <string>
#include <vector>
#include <GameClass.hpp>

class Save {
  public:
	  void					  saveGame(std::string playerSaveFileName, Game &game);

  private:
	  std::string			  _saveFileName;
	  std::vetor<std::string> _saveFileContents;
};


#endif

