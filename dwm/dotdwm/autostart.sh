#!/bin/sh
feh --bg-scale ~/Pictures/Wall\ of\ papers/Horizontal/Not\ Themed/minimalist\ town.png
setxkbmap -layout pt
picom &
export PATH=/home/xanodeb/dwm/dwmblocks/statusbar_scripts:$PATH
dwmblocks &
