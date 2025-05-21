#!/usr/bin/env python3

import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk
import subprocess
import sys

class LogoutOverlay(Gtk.Window):
    def __init__(self):
        super().__init__()

        self.set_decorated(False)
        self.fullscreen()
        self.set_app_paintable(True)
        self.override_background_color(Gtk.StateFlags.NORMAL, Gdk.RGBA(0, 0, 0, 0.2))
        self.connect("key-press-event", self.on_key_press)
        self.connect("destroy", Gtk.main_quit)

        label = Gtk.Label(label="Logout Menu\n[k] Lock • [l] Logout • [s] Shutdown • [r] Reboot • [Esc] Cancel")
        label.modify_fg(Gtk.StateFlags.NORMAL, Gdk.color_parse("white"))
        label.set_justify(Gtk.Justification.CENTER)
        label.set_margin_top(300)
        label.set_margin_bottom(300)
        label.set_name("main-label")

        css = b"""
        #main-label {
            font: 32px 'JetBrainsMono Nerd Font';
        }
        """
        style_provider = Gtk.CssProvider()
        style_provider.load_from_data(css)
        Gtk.StyleContext.add_provider_for_screen(
            Gdk.Screen.get_default(),
            style_provider,
            Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
        )

        self.add(label)
        self.show_all()

    def on_key_press(self, widget, event):
        key = Gdk.keyval_name(event.keyval)
        if key == "k":
            subprocess.run(["i3lock-fancy"])
        elif key == "l":
            subprocess.run(["pkill", "-KILL", "-u", subprocess.getoutput("whoami")])
        elif key == "s":
            subprocess.run(["systemctl", "poweroff"])
        elif key == "r":
            subprocess.run(["systemctl", "reboot"])
        elif key == "Escape":
            Gtk.main_quit()

        # After any action (except cancel), quit overlay
        if key in ["k", "l", "s", "r"]:
            Gtk.main_quit()

if __name__ == "__main__":
    app = LogoutOverlay()
    Gtk.main()

