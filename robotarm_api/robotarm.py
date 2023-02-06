#python -m uvicorn robotarm:app --reload
from fastapi import Body, FastAPI
import fastapi
from pydantic import BaseModel
from typing import Union
import pydantic
import serial
import time
import enum

#format for recieve bytes:
#{(servo number 1-4), (move speed 1-9), (pos argument), (pos argument (optional)), (pos argument (optional))}
#post status change of port (status=open or status=close)
app = FastAPI()
ser = serial.Serial('COM5', 9600, timeout=2)

class PortStatus(enum.Enum):
	OPEN = "open"
	CLOSE = "close"

class SerialCommand(BaseModel):
	servo: pydantic.conint(strict=True, ge=1, le=4)
	speed: pydantic.conint(strict=True, ge=1, le=9)
	position: pydantic.conint(strict=True, ge=0, le=180)

class Servo(BaseModel):
	servo_num: pydantic.conint(strict=True, ge=1, le=4)
	position: pydantic.conint(strict=True, ge=0, le=180)

#class MoveParam(BaseModel):
#	servo: int
#	speed: int
#	position: int

@app.get("/port_status")
def status():
	return {ser.isOpen()}


@app.post("/port_status")
def port_port(status: PortStatus) -> PortStatus:
	getattr(ser, status.value)()
	

@app.post("/rotate")
def pass_serial_command(command: SerialCommand):
	params = f"{command.servo}{command.speed}{command.position}".encode("utf-8")
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



