#!/usr/bin/env python3

import subprocess
import pyautogui
import time

# Execute the command
subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera.rt"])

# Wait for 8 seconds
time.sleep(3)

# Simulate pressing the Esc key
pyautogui.press('esc')
