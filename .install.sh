if [ ! -d "$HOME/.brew" ]; then
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
	osascript -e 'tell application "iTerm2
    create window with default profile command "sh ~/Bomberman/.cRun.sh -hold"
	end tell'
fi
sh .cRun.sh
