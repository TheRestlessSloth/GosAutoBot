#!/bin/bash

xrandr --output HDMI-1 --rotate left --mode 1920x1080
xrandr --output HDMI-2 --rotate normal --mode 1920x1080
xinput map-to-output 6 HDMI-1&

