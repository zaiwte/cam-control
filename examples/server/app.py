import asyncio
import io
from starlette.applications import Starlette
import urllib.request #para abrir y leer URL
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, StreamingResponse, Response
from fastapi.templating import Jinja2Templates
import uvicorn
import cv2
import numpy as np

ip = "192.168.1.2"
camera = f"http://{ip}/cam.jpg"
flash_on = f"http://{ip}/cam.on.flash"
flash_off = f"http://{ip}/cam.off.flash"

templates = Jinja2Templates(directory="templates")

app = FastAPI(title="cam-control")

#cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
face_detector = cv2.CascadeClassifier(cv2.data.haarcascades +
"haarcascade_frontalface_default.xml")

async def webcam():
    while True:
        #ret, frame = cap.read()
        #----------------------------------------------------------------------------------
        img_resp = urllib.request.urlopen(camera)
        imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(imgnp, -1)
        img_rotate = cv2.rotate(frame, cv2.ROTATE_180)

        #----------------------------------------------------------------------------------
        #if ret:
        gray = cv2.cvtColor(img_rotate, cv2.COLOR_BGR2GRAY)
        faces = face_detector.detectMultiScale(gray, 1.3, 5)
        for (x,y,w,h) in faces:
            cv2.rectangle(img_rotate, (x,y), (x+w,y+h), (0,255,0),2)
        (flag,encodedImg) = cv2.imencode(".jpg", img_rotate)
        if not flag:
            continue
        #como pasar los bytes a el cliente
        yield b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n'+bytearray(encodedImg)+b'\r\n'

@app.get("/", response_class=HTMLResponse)
async def read_item(request: Request):
    return templates.TemplateResponse("index.html", {'request': request})


@app.get("/streaming")
async def video_stream():
    return StreamingResponse(webcam(), media_type="multipart/x-mixed-replace;boundary=frame")

if __name__ == "__main__":

    uvi = uvicorn.run(app,
                host="0.0.0.0",
                port=5000,
                server_header=False)
