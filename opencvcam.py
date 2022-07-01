import cv2
import urllib.request #para abrir y leer URL
import numpy as np
ip = "192.168.1.2"
camera = f"http://{ip}/cam.jpg"
flash_on = f"http://{ip}/cam.on.flash"
flash_off = f"http://{ip}/cam.off.flash"

winName = 'CAM'
cv2.namedWindow(winName, cv2.WINDOW_AUTOSIZE)
scale_percent = 80 # percent of original size

while(1):
    img_resp = urllib.request.urlopen(camera)
    imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
    frame = cv2.imdecode(imgnp, -1)
    img_rotate = cv2.rotate(frame, cv2.ROTATE_180)

    cv2.imshow(winName,img_rotate)
    key = cv2.waitKey(5)
    if key == ord('q'):
        break



cv2.destroyAllWindows()