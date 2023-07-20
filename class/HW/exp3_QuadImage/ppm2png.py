from PIL import Image
import sys

def ppm2png(ppm_path, png_path):
    img = Image.open(ppm_path)
    img.save(png_path)
    # img.show()

if __name__ == '__main__':
    filename = sys.argv[1]
    ppm2png(filename, filename.replace('.ppm', '.png'))