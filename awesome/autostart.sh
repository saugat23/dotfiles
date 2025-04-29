#!/bin/bash

sleep 1 && feh --randomize --bg-scale ~/Pictures/wallpapers/* &

# Launch Network Applet
if ! pgrep -x nm-applet > /dev/null; then
    nm-applet &
fi &

numlockx on

# Avoid starting multiple instances
if ! pgrep -x picom > /dev/null; then
    picom --config ~/.config/picom/picom.conf &
fi
