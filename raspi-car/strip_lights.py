import time
import random
from rpi_ws281x import PixelStrip, Color

LED_COUNT = 14        # LED灯的个数
LED_PIN = 18          # DI端接GPIO18

# 以下可以不用改
LED_FREQ_HZ = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA = 10          # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 100  # Set to 0 for darkest and 255 for brightest
LED_INVERT = False    # True to invert the signal (when using NPN transistor level shift)
LED_CHANNEL = 0       # set to '1' for GPIOs 13, 19, 41, 45 or 53

# Create NeoPixel object with appropriate configuration.
#创建对象
strip = PixelStrip(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)

# Intialize the library (must be called once before other functions).
#初始化
strip.begin()

#Toggle all LED light colors
#改变所以灯颜色
def change_color(color, wait_ms=20):
    for i in range(strip.numPixels()):
        strip.setPixelColor(i, color)
        strip.show()
        time.sleep(wait_ms / 1000.0)

#随机点亮一个灯
def random_lights():
    for i in range(10):
        #-1是因为randint(n,m)获取到的值会包含n和m，而led在程序中第一个位置是0，5个LED灯就是0到4
        num = random.randint(0,strip.numPixels()-1)
        r = random.randint(0,255)
        g = random.randint(0,255)
        b = random.randint(0,255)
        strip.setPixelColor(num, Color(r,g,b))
        strip.show()       
        time.sleep(0.5)
        change_color(Color(0,0,0))

#流水灯
def water_lights(color):
    count = 0
    while True:
        for i in range(strip.numPixels()):
            strip.setPixelColor(i, color)
            strip.show()       
            time.sleep(0.1)
        change_color(Color(0,0,0))
        time.sleep(0.5)
        count = count + 1
        if count >= 5:
            change_color(Color(0,0,0))
            break
            
# 呼吸灯
#利用setBrightness()设置灯的亮度 值在0到255之间 包括 0和255
def breathing(color):
    strip.setBrightness(0)
    change_color(color)
    strip.show()
    brightness = 0
    increment = 1
    count = 0
    while True:
        brightness = brightness + increment
        strip.setBrightness(brightness)
        strip.show()
        time.sleep(0.01)
        if brightness <= 0 or brightness >= 255:
            increment = -increment
            count = count + 1
        if count == 7:
            change_color(Color(0,0,0))
            break
        
        

try:
    random_lights()
    water_lights(Color(0,255,0))    
    breathing(Color(0,255,255))
except:
    pass