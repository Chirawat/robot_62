import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('cheese.jpg', 0)
ret, threshold1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

roi = threshold1[0:5, 0:5]  # y:y+h, x:x+w
print(roi)




# plt.subplot(221), plt.imshow(img, 'gray'), plt.title('original')
# plt.subplot(222), plt.imshow(threshold1,'gray'), plt.title('threshold')
# plt.show()

# cv2.waitKey()
# cv2.destroyAllWindows()
