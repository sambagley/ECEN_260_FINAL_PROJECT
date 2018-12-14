#converts an 800 by 800 jpg to an array that uses one 8bit color for each of the 50 pixels
# in the LED string. First 25 elements go from center to outside and the next 25 elements 
# go to the other side of the wheel also from the center outwards. 
# resolution is set to 180 ticks per 360 degrees. 

#needs very high quality jpeg or tiff format to produce good results. 
#best results come from recoloring images in photo editing software to 
#be simpler and removing small unimportant details. 

from PIL import Image
import math

class ImageDecode():
    def __init__(self):
        
        # Set how many degrees between each tick and how many LEDS are in the string
        self.degrees_resolution = 2
        #self.num_leds = 26
        
        # Set picture filename and filename of file to write array to.
        # use jpg for jpeg and tif for tiff formats
        self.picture_name = "pika4.tif"
        self.filename = "pika4.txt"
        
        self.img = Image.open(r'''C:\Users\natha\python_files\image_processing\{}'''.format(self.picture_name)).transpose(Image.FLIP_LEFT_RIGHT).transpose(Image.ROTATE_180)
        self.radius = 400
        self.spacing = 13.68
        self.data = open("{}".format(self.filename), "w")
        self.data.write("char quadrants[180][50] = {")
        
    def get_data(self):
        """
        Returns data
        """
        # Set degrees to zero to begin getting data
        degrees = 0
        while degrees < 360:
            
            # get data for first half of LEDS
            radius = 58
            data = []
            while radius < self.radius:
                byte = self.get_byte(radius, degrees)
                self.write_data(byte)
                radius += self.spacing
                
            # get data for second half of LEDS
            radius = 58
            while radius < self.radius:
                byte = self.get_byte(radius,(degrees + 180))
                self.write_data(byte)
                radius += self.spacing
                
            degrees += self.degrees_resolution

    def get_coordinates(self, r, theta):
        
    ##    convert theta to degrees
        theta = math.radians(theta)
    ##    find x and y values of pixel
        x,y = int(r*math.cos(theta)), int(r*math.sin(theta))
        return x,y

    def get_rgb(self, x, y):
        pix = self.img.load()
        
        # Add an f parameter for tif files
        r, g, b, f = pix[x,y]
        return r, g, b
    
    def get_byte(self, radius, degrees):
            x, y = self.get_coordinates(radius, degrees)    
            x += 400
            y += 400
            r, g, b = self.get_rgb(x, y)
            r, g, b = int(r/32), int(g/32), int(b/64)
            r = '{:03b}'.format(r)
            g = '{:03b}'.format(g)
            b = '{:02b}'.format(b)
            byte = r+g+b
            byte = int(byte, 2)
            byte = hex(byte)
            byte.replace("'","")
            return byte
        
    def close_file(self):
        self.data.write("}")
        
    def write_data(self, byte):
        self.data.write(byte+",")
        
    def print_data(self):
        print(self.data)
        
def main():  
    data = ImageDecode()
    data.get_data()
    
    data.print_data()
main()