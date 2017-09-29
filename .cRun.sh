if [ ! -d "$HOME/.brew" ]; then
	echo "Please install brew"
elif [ ! -d "$HOME/.brew/Cellar/cmake" ]; then
	brew install cmake
fi
sh .clean.sh
cmake .
make -j4
./Bomberman