#python -m uvicorn robotarm:app --reload
from fastapi import Body, FastAPI
import fastapi
from pydantic import BaseModel
from typing import Union
import serial
import time
app = FastAPI()

ser = serial.Serial('COM5', 9600, timeout=2)
cpos = 0

#format for recieve bytes:
#{(servo number 1-4), (move speed 1-9), (pos argument), (pos argument (optional)), (pos argument (optional))}
#post status change of port (status=open or status=close)

class Port(BaseModel):
	status: str

#class MoveParam(BaseModel):
#	servo: int
#	speed: int
#	position: int

@app.get("/port_status")
def status():
	return {ser.isOpen()}

@app.get("/current_position")
def current_position():
	return {cpos}

@app.post("/port_status")
def port_port(port: Port) -> bool:
	if port.status == "open":
		ser.open()
	elif port.status == "close":
		ser.close()
	else:
		raise valueError("its either open, or closed. Why have you passed in something else. What do you want, you goddam fucker. Why do I exist solely to explain how stupid you are for not simply entering open or closed")
	return ser.isOpen()

@app.post("/get_rotated")
def pass_serial_command(servo: int, speed: int, position: int):
	if servo > 4 or servo < 1:
		raise valueError("thats not a servo you fucknut")
	if speed > 9 or speed < 1:
		raise valueError("too fast or too slow nutts-for-brains")
	if position < 0 or position > 180:
		raise valueError("servos dont move that way ya cocknuckle")

	str_params = str(servo) + str(speed) + str(position)
	params = bytes(str_params, 'UTF-8')
	ser.write(params)

@app.post("/swivel_base")
def swivel_base():
	for x in range(0, 2):
		pass_serial_command(1, 5, 180)
		print(180)
		time.sleep(1)
		pass_serial_command(1, 5, 0)
		print(0)
		time.sleep(1)
