if [ ! -d "$HOME/.brew" ]; then
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)"
	osascript -e 'tell application "iTerm2"
		quit
	    make new terminal
	    tell the current terminal
	        activate current session
	        launch session "Default Session"
	        tell the last session
	            write text "cd ~/Bomberman; sh .cRun.sh;"
	        end tell
	    end tell
	end tell'
fi
sh .cRun.sh