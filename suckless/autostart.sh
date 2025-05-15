# Setup Feh
feh --bg-fill --randomize ~/Pictures/wallpapers/*

#Setup Picom
picom --config ~/.config/picom/picom.conf &
redshift -O 4800 &

#Exec slstatus
exec slstatus &
nm-applet &
blueman-applet &
xfce4-clipman &
volumeicon &
xfce4-notee &

