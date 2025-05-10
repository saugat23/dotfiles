# Setup Feh
feh --bg-fill --randomize ~/Pictures/wallpapers/*

#Setup Picom
"$HOME"/.config/picom/build/src/./picom -b --animations --animation-window-mass 0.5 --animation-for-open-window zoom --animation-stiffness 500 &

#Exec slstatus
exec slstatus &
nm-applet &
blueman-applet &
xfce4-clipman &

