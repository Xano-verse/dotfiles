#!/bin/sh
feh --bg-scale ~/Pictures/Wall\ of\ papers/Horizontal/S\ tier/minimalist\ town.png
setxkbmap -layout pt
#picom &
picom --animations -b
export PATH=/home/xanodeb/dwm/dwmblocks/statusbar_scripts:$PATH
dwmblocks &
xrandr --output HDMI-A-0 --auto --left-of eDP
xrandr --output HDMI-A-0 --brightness 1

