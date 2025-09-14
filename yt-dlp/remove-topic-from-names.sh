#!/bin/bash

# Use after downloading music albums from youtube with the music-youtube-config.txt.
# Some artists don't have channels so they're named "Artist - Topic". This is to remove every " - Topic" from the filenames.

cd "$1"

# Will include both files and directories
for file in *; do

	#	  ${array[@]: offset:length}
	if [[ ${file[@]: -12:8} = " - Topic" ]]; then

		new_name=${file:0:-12}		# filename up until " - Topic", excludes the extension
		ext=${file[@]: -4:4} 		# already includes the .

		mv "$file" "$new_name$ext"
		echo "[32m>> renamed $file to $new_name$ext[37m"

	fi

done
