# Setup Feh
feh --bg-fill --randomize ~/Pictures/wallpapers/*

# Setup Picom
pgrep -x picom > /dev/null || picom --config ~/.config/picom/picom.conf &
pgrep -x redshift > /dev/null || redshift -O 5400 &

# Exec slstatus (should use just `slstatus &`, not `exec`, or DWM won't continue)
pgrep -x slstatus > /dev/null || slstatus &

pgrep -x nm-applet > /dev/null || nm-applet &
pgrep -x blueman-applet > /dev/null || blueman-applet &
pgrep -x xfce4-clipman > /dev/null || xfce4-clipman &
pgrep -x volumeicon > /dev/null || volumeicon &
pgrep -x xfce4-notes > /dev/null || xfce4-notes &
