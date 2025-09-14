#!/bin/bash

# Use after downloading music albums from youtube with the music-youtube-config.txt.
# This will remove the "Album - " part of the directories' names


for dir in */; do
	
	if [[ ${dir:0:8} = "Album - " ]]; then


		# "Album - " is 8 characters -> offset of 8
		new_name=${dir:8}

		mv "$dir" "$new_name"
		echo "[32m>> renamed $dir to $new_name[37m"

	fi

done
