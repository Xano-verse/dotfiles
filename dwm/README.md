# dwm

dwm binary file goes in /usr/local/bin as well as dwmblocks binary.

To make the greeter detect dwm create a dwm.desktop file in /usr/share/xsessions with the following text (this may cause .xinitrc to not be executed but we can use the autostart.sh script in .dwm instead):

```
[Desktop Entry]
Encoding=UTF-8
Name=dwm
Comment=Dynamic window manager
Exec=dwm
Icon=dwm
Type=XSession
```


