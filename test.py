#!/usr/bin/env python3

import subprocess
import pyautogui
import time
import shutil
import os

RESET = '\033[0m'
BOLD = '\033[1m'
ITAL = '\033[3m'
GREEN = '\033[32m'
BLUE = '\033[34m'
PURPLE = '\033[35m'
ORANGE = '\033[38;5;208m'

TIME = 3
TIME_PAUSE = 1
TIME_WR_INPUT = 2

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

file_path = 'scenes/simple_scenes/camera_test.rt'

print_text("\n\tMINIRT TESTS\n", BOLD, PURPLE)

# managing input:
user_input = input("Enter 'parsing' for parsing tests")

if user_input == 'parsing':

	""" WRONG INPUT """
	print_text("\nWrong input tests:\n", ITAL, BOLD, PURPLE)

	print_text("\nWrong text input: (blabla)", ITAL, ORANGE)
	subprocess.Popen(["./miniRT", "blabla"])
	time.sleep(TIME_WR_INPUT)

	print_text("\nNo input", ITAL, ORANGE)
	subprocess.Popen(["./miniRT", ""])
	time.sleep(TIME_WR_INPUT)

	print_text("\nNumeric input", ITAL, ORANGE)
	subprocess.Popen(["./miniRT", ""])
	time.sleep(TIME_WR_INPUT)

	print_text("\nNo arguments", ITAL, ORANGE)
	subprocess.Popen(["./miniRT"])
	time.sleep(TIME_WR_INPUT)

	print_text("\nToo many arguments", ITAL, ORANGE)
	subprocess.Popen(["./miniRT", "ciao", "bello"])
	time.sleep(TIME_WR_INPUT)

	print_text("\nWrong file no access", ITAL, ORANGE)
	# set permissions to 000
	os.chmod("scenes/simple_scenes/test_wrong_no_access.rt", 0o000)
	subprocess.Popen(["cat", "scenes/simple_scenes/test_wrong_no_access.rt"])
	time.sleep(TIME_PAUSE)
	subprocess.Popen(["./miniRT", "scenes/simple_scenes/test_wrong_no_access.rt"])
	time.sleep(TIME_WR_INPUT)
	os.chmod("scenes/simple_scenes/test_wrong_no_access.rt", 0o777)

	# handling a copy of the file
	shutil.copy("scenes/simple_scenes/test_wrong.rt", "scenes/simple_scenes/test_wrong_temp.rt")

	print_text("\nToo few elements", ITAL, ORANGE)
	subprocess.Popen(["./miniRT", "scenes/simple_scenes/test_wrong_temp.rt"])
	time.sleep(TIME_WR_INPUT)

	print_text("\nWrong file line", ITAL, ORANGE)
	substitute_last_line("scenes/simple_scenes/test_wrong_temp.rt", "L 6,20,-20 0.7 255,255,255\nblabla")
	subprocess.Popen(["./miniRT", "scenes/simple_scenes/test_wrong_temp.rt"])
	time.sleep(TIME_WR_INPUT)

	print_text("\nToo many elements", ITAL, ORANGE)
	substitute_last_line("scenes/simple_scenes/test_wrong_temp.rt", "L 6,20,-20 0.7 255,255,255")
	subprocess.Popen(["./miniRT", "scenes/simple_scenes/test_wrong_temp.rt"])
	time.sleep(TIME_WR_INPUT)
	# delete the copied file
	os.remove("scenes/simple_scenes/test_wrong_temp.rt")

else:

	""" RENDERING AND CAMERA """
	print_text("\nRendering and camera tests:\n", ITAL, BOLD, PURPLE)


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

	print_text("\n\t🌞 DONE!!! 🌞\n", ITAL, BOLD, PURPLE)

