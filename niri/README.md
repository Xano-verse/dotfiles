# niri

niri config files are usually in ~/.config/niri/

base-config was the default config that came with it,
config.kdl is the config in use


niri is using waybar by running
`spawn-at-startup "waybar"`

the wallpaper is set with
`spawn-sh-at-startup "swaybg -i "Path/to/Wallpaper"`

pywal is launched to generate the colorscheme based on the wallpaper with
`spawn-sh-at-startup "wal -i "Path/to/Wallpaper"`


