from PIL import Image, ImageFilter
import glob
import shutil

QUEUE_LENGTH     = 16
DMA_CHUNK_LENGTH = 16
#iso/character/tim files

path = glob.glob('iso/characters/*/*.png')

#calculate if the image is a multiple of 16
def recalc(width, height, bpp):
    dawidth = 0
    if bpp == '8':
        dawidth = width / 2
    elif bpp == '4':
        dawidth = width / 4
    else:
        print("invalid bpp " + bpp + " "  + curpath + ".txt, aborting")
        exit()

    length = dawidth * height
    length = length / 2
    if ((length >= DMA_CHUNK_LENGTH) and (length % DMA_CHUNK_LENGTH)):
        return False
    else:
        return True

def writetex(path):
    print("fixed image " + curpath)
    new_image = Image.new('RGBA', (realwidth, realheight))
    new_image.paste(tex)
    new_image.save(path)

for curpath in path:
    tex = Image.open(curpath)

    bpp = 0
    with open(curpath + '.txt', 'r') as file:
        bpp = file.read()
        bpp.strip()
        bppstr = ''.join(bpp.split('\n'))
        bpp = bppstr
        bpp = bpp[-1] 

    realwidth = tex.size[0]
    realheight = tex.size[1]

    #check if the image needs fixing
    if recalc(realwidth, realheight, bpp) == True:
        print("no need to fix image " + curpath)
        continue
    print("fixing image " + curpath)

    while realheight % 2 != 0 and realheight < 256:
        realheight = realheight + 1

    if realheight % 2 != 0:
        print("failed to fix image " + curpath + " height isnt a multiple of 2")
        exit()
    #try mess with the width
    for i in range(256):
        if realwidth > 255:
            break;
        if recalc(realwidth+i, realheight, bpp) == True:
            realwidth = realwidth + i;
            break;
        
    # yay fix worked
    if recalc(realwidth, realheight, bpp) == True:
        writetex(curpath)
        continue

    #try mess with the height if fix didnt work
    for i in range(256):
        if realheight > 255:
            break;
        if recalc(realwidth, realheight+i, bpp) == True:
            realheight = realheight+i;
            break;
        
    # yay fix worked
    if recalc(realwidth, realheight, bpp) == True:
        writetex(curpath)
        continue

    print("failed to fix image " + curpath)
