#!/bin/bash
CURRENT_ENGINE=$(ibus engine)
if [ "$CURRENT_ENGINE" = "xkb:us::eng" ]; then
    ibus engine m17n:ne:rom-imp
else
    ibus engine xkb:us::eng
fi
