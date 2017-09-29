if isAppRunning("iTerm") then
	tell application "iTerm"
		set myterm to (make new terminal)
		tell myterm
			set mysession to (make new session at the end of sessions)
			tell mysession
				exec command "sh .cRun.sh"
			end tell
		end tell
		activate
	end tell
else
	activate application "iTerm"
end if