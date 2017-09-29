if [ ! -d "$HOME/.brew" ]; then
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
fi
osascript .restartTerm.scpt
if [ ! -d "$HOME/.brew/Cellar/cmake" ]; then
	brew install cmake
fi
sh .clean.sh
cmake .
make -j4
./Bomberman