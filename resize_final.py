from PIL import Image
import os
import os.path
import cv2
import glob
import numpy as np


def iter_frames(im):
    try:
        i = 0
        while 1:
            im.seek(i)
            imframe = im.copy()
            if i == 0:
                palette = imframe.getpalette()
            else:
                imframe.putpalette(palette)
            yield imframe
            i += 1
    except EOFError:
        pass

def convertjpg( jpgfile, width=64, height=48):
    src = cv2.imread(jpgfile)


    dst = cv2.resize(src,(width,height),interpolation=cv2.INTER_CUBIC)

    tmp=np.zeros(dst.shape[1]*dst.shape[0])
    i=0
    while i < dst.shape[0]*dst.shape[1]:
        tmp[i]=dst[i//width,i%height,0]
        i+=1
    tmp = tmp/255
    return tmp

#convert gif to jpg so that we can use opencv to read the image
def resize(root_dir,out_dir,width=64,height=48):
    for parent, dirnames, filenames in os.walk(root_dir):  # 遍历每一张图片
        for filename in filenames:
            currentPath = os.path.join(parent, filename)
            im = Image.open(currentPath)  # 打开gif格式的图片
            for i, frame in enumerate(iter_frames(im)):
                frame.save(out_dir + filename + '.jpg', **frame.info)
    num_pictures=0
    result = np.zeros((165, width * height))
    for jpgfile in glob.glob(out_dir+'*.jpg'):
        dst = convertjpg(jpgfile, width, height)
        result[num_pictures, :] = dst
        num_pictures += 1
    np.set_printoptions(edgeitems=5)
    print(num_pictures)
    print(result.shape)

def final_matrix(out_dir, width = 64, height = 48):
    result = np.zeros((165, width * height))
    num_pictures=0
    for jpgfile in glob.glob(out_dir+'*.jpg'):
        dst = convertjpg(jpgfile, width, height)
        result[num_pictures, :] = dst
        num_pictures += 1
    #print(num_pictures)
    #print(result.shape)
    return result

# resize('C:/Users/kicka/Documents/Github/hungary/yaleface_raw_images/','C:/Users/kicka/Documents/Github/hungary/yaleface_adjusted/',64,48)

if __name__ == "__main__":
    dir_path = dirname = os.path.dirname(__file__)
    filename = dir_path + "/yaleface_adjusted/"
    A = final_matrix(filename,64,48)
    print(A.shape)