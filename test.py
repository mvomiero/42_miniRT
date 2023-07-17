#!/usr/bin/env python3

import subprocess
import pyautogui
import time

RESET = '\033[0m'
BOLD = '\033[1m'
ITAL = '\033[3m'
GREEN = '\033[32m'

TIME = 3
TIME_PAUSE = 1

# printing formatted
def print_text(text, *formatting):
	formatted_text = ''.join(formatting) + text + RESET
	print(formatted_text)

def substitute_last_line(file_path, new_line):
	with open(file_path, 'r+') as file:
		lines = file.readlines()
		if lines:
			lines[-1] = new_line + '\n'
			file.seek(0)
			file.writelines(lines)
			file.truncate()

# Usage example
file_path = 'scenes/simple_scenes/camera_test.rt'



print_text("\n\tMINIRT TESTS\n", BOLD, GREEN)

""" SPHERE """

print_text("\nSphere:\n", ITAL, GREEN)

# Execute the command
subprocess.Popen(["./miniRT", "scenes/simple_scenes/sphere.rt"])

# Wait for x seconds
time.sleep(TIME)

# Simulate pressing the Esc key
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" PLANE """

print_text("\nPlane:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/plane.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" PLANE """

print_text("\nCylinder:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/cylinder.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA """
#substitute_last_line(file_path, new_line)

print_text("\nCamera:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA Z front"""
substitute_last_line(file_path, "C 0,0,0 0,0,1 55")

print_text("\nCamera z front:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA Z back"""
substitute_last_line(file_path, "C 0,0,0 0,0,-1 55")

print_text("\nCamera z back:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA X front"""
substitute_last_line(file_path, "C 0,0,0 1,0,0 55")

print_text("\nCamera x front:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA X back"""
substitute_last_line(file_path, "C 0,0,0 -1,0,0 55")

print_text("\nCamera x back:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA Y up"""
substitute_last_line(file_path, "C 0,0,0 1,0,0 55")

print_text("\nCamera y up:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

""" CAMERA Y down"""
substitute_last_line(file_path, "C 0,0,0 -1,0,0 55")

print_text("\nCamera y down:\n", ITAL, GREEN)

subprocess.Popen(["./miniRT", "scenes/simple_scenes/camera_test.rt"])
time.sleep(TIME)
pyautogui.press('esc')
time.sleep(TIME_PAUSE)

#reset file to initial status
substitute_last_line(file_path, "C 4,10,-70 -0.2,0,0.7 90")

print_text("\n\t🌞DONE!!!🌞\n", ITAL, GREEN)

# general overview
#C 4,10,-70 -0.2,0,0.7 90

# z front
#C 0,0,0 0,0,1 55
# z back
#C 0,0,0 0,0,-1 55

# x front
#C 0,0,0 1,0,0 55

# x back
#C 0,0,0 -1,0,0 55

# y up
#C 0,0,0 0,1,0 55
# y down
#C 0,0,0 0,-1,0 55

# camera for testing
