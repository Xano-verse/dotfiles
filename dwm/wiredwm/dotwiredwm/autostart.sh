#!/bin/sh
feh --bg-scale ~/Pictures/Wall\ of\ papers/Horizontal/Themed/Lain/lain_world.jpg
setxkbmap -layout pt
#picom &
picom --animations -b
export PATH=/home/xanodeb/wiredwm/dwmblocks/statusbar_scripts:$PATH
wiredwmblocks &
