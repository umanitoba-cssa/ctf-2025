import numpy as np
from PIL import Image

num_shares = int(2)

def encrypt(input_image):
    image = np.asarray(input_image)
    (row, column) = image.shape
    shares = np.random.randint(0, 2, size=(row, column, num_shares))*255
    shares[:,:,-1] = image.copy()
    for i in range(num_shares-1):
        shares[:,:,-1] = shares[:,:,-1] ^ shares[:,:,i]

    return shares

def main():
    try:
        img_in = Image.open('in.jpg').convert('L')
    except FileNotFoundError:
        print("in.jpg not found")
        exit(0)

    shares = encrypt(img_in)

    for i in range(num_shares):
        img_out = Image.fromarray(shares[:,:,i].astype(np.uint8))
        img_out.save("out" + str(i) + ".jpg")

if __name__ == "__main__":
    main()
