local awful = require("awful")
local gears = require("gears")
local wibox = require("wibox")

-- Notes widget
local notes_widget = wibox.widget {
    text   = "",
    widget = wibox.widget.textbox,
}

-- Function to read notes from file
local function update_notes()
    awful.spawn.easy_async_with_shell("head -n 1 ~/.config/awesome/widgets/notes.txt", function(stdout)
        notes_widget.text = "🗒️ " .. stdout:gsub("\n", "")
    end)
end

-- Update on startup
update_notes()

-- Optional: refresh every 60 seconds
gears.timer {
    timeout   = 60,
    autostart = true,
    callback  = update_notes
}

return notes_widget

