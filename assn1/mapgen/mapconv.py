from PIL import Image

filename = "map.png"
im = Image.open(filename)
pix = im.load()
size = im.size

print(size)

f = open("map.txt","w")

for i in range(size[0]):
    for j in range(size[1]):
        if(pix[j,i][0] == 0):
        	f.write("0")
        else:
        	f.write("1")
    f.write("\n")