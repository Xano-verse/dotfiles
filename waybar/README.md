# Waybar config

located in `~/.config/waybar`
(there are other valid locations, see the waybar github wiki)

config.jsonc has the "technical" side of the configuration (like which modules appear where) and the style.css has the styling (colors and shapes)

in the style.css we can import other .css files, so for example if we want to use pywal to generate a colorscheme based on the wallpaper, we can import the colorscheme from ~/.cache/wal/colors-waybar.css (pywal generates a file already meant for waybar) and then use the colors with @color1

