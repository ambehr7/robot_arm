from fastapi import FastAPI
from pydantic import BaseModel
import serial
import time
app = FastAPI()

ser = serial.Serial('COM4', 9600, timeout=2)
cpos = 0

@app.get("/port_status")
def status():
	return {ser.isOpen()}

@app.get("/current_position")
def current_position():
	return {cpos}

@app.post("/close_port")
def close_port():
	ser.close()
	return ser.isOpen()

@app.post("/open_port")
def open_port():
	ser.open()
	return ser.isOpen()

@app.post("/rotate")
def move_servo(pos: int):
	if pos >= 0 and pos <= 180 and ser.isOpen():
		ser.write(bytes(str(pos), 'utf-8'))
		cpos = pos
		print("complete")

