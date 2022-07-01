import PySimpleGUI as sg
import cv2
from opencvcam import imgFromEsp32Cam
class CameraGui:
    def __init__(self):
        self.var = 1

    def home(self):
        HOME = [[sg.Image(imgFromEsp32Cam(),
                          key='-IMAGE-',
                          size=(800,600))]]

        return {
                'F':sg.Frame('', HOME, k='-F-'),
                'E': [{'k': '-F-', 'ex': True, 'ey': True}]
                }

    def show(self):
        layout = [[self.home()['F']]]

        window = sg.Window('camera',
                           layout,
                           finalize = True)

        while True:
            event,values = window.read(timeout=100)

            if event in (sg.WIN_CLOSED, 'Exit'):
                break

            for i in [self.home()['E']]:
                for j in i:
                    window[j['k']].expand(expand_x = j['ex'] ,expand_y = j['ey'] ,expand_row = False)

        window.close()


if __name__ == '__main__':
    sg.theme('LightGray2')
    CameraGui().show()
