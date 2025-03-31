import cv2
import numpy as np
# import time
from PIL import Image

turbo_c_color_codes = [
    0,  # 黑色
    1,  # 蓝色
    2,  # 绿色
    3,  # 青色
    4,  # 红色
    5,  # 品红色
    6,  # 棕色
    7,  # 浅灰色
    8,  # 深灰色
    9,  # 浅蓝色
    10,  # 浅绿色
    11,  # 浅青色
    12,  # 浅红色
    13,  # 浅品红色
    14,  # 黄色
    15  # 白色
]

# Turbo C 16 种颜色对应的 RGB 值
turbo_c_colors = [
    (0, 0, 0),  # 黑色
    (0, 0, 128),  # 蓝色
    (0, 128, 0),  # 绿色
    (0, 128, 128),  # 青色
    (128, 0, 0),  # 红色
    (128, 0, 128),  # 品红色
    (128, 128, 0),  # 棕色
    (192, 192, 192),  # 浅灰色
    (128, 128, 128),  # 深灰色
    (0, 0, 255),  # 浅蓝色
    (0, 255, 0),  # 浅绿色
    (0, 255, 255),  # 浅青色
    (255, 0, 0),  # 浅红色
    (255, 0, 255),  # 浅品红色
    (255, 255, 0),  # 黄色
    (255, 255, 255)  # 白色
]


def find_closest_color(bgr):

    min_distance = float('inf')
    closest_index = 0
    for i, color in enumerate(turbo_c_colors):
        r, g, b = color
        distance = np.sqrt((b - bgr[0]) ** 2 + (g - bgr[1]) ** 2 + (r - bgr[2]) ** 2)
        if distance < min_distance:
            min_distance = distance
            closest_index = i
    return closest_index


def convert_image_to_binary(image_path, output_binary_path):

    image = cv2.imread(image_path)
    if image is None:
        print(f"无法读取图片: {image_path}")
        return
    height, width, _ = image.shape
    with open(output_binary_path, 'wb') as file:
        file.write(width.to_bytes(4, byteorder='big'))
        file.write(height.to_bytes(4, byteorder='big'))
        for y in range(height):
            for x in range(width):
                bgr = image[y, x]
                color_index = find_closest_color(bgr)
                # 直接使用颜色编号
                color_code = turbo_c_color_codes[color_index]
                file.write(color_code.to_bytes(1, byteorder='big'))
    print(f"二进制像素颜色信息已保存到 {output_binary_path}")


def convert_image_to_text(image_path, output_text_path):

    image = cv2.imread(image_path)
    if image is None:
        print(f"无法读取图片: {image_path}")
        return
    height, width, _ = image.shape
    with open(output_text_path, 'w') as file:
        file.write(f"{width} {height}\n")
        for y in range(height):
            for x in range(width):
                bgr = image[y, x]
                color_index = find_closest_color(bgr)
                # 直接使用颜色编号
                color_code = turbo_c_color_codes[color_index]
                file.write(f"{color_code}\n")
    print(f"文本像素颜色信息已保存到 {output_text_path}")


def display_simulated_image(binary_path):

    with open(binary_path, 'rb') as file:
        width = int.from_bytes(file.read(4), byteorder='big')
        height = int.from_bytes(file.read(4), byteorder='big')
        image = Image.new('RGB', (width, height))
        pixels = image.load()
        for y in range(height):
            for x in range(width):
                color_code = int.from_bytes(file.read(1), byteorder='big')
                r, g, b = turbo_c_colors[color_code]
                pixels[x, y] = (r, g, b)
    image.show()
    return image


if __name__ == "__main__":
    image_path = "./image/source.jpg"  # 替换为实际图片路径
    output_text_path = "tag.txt"
    output_binary_path = "tag.bin"

    convert_image_to_text(image_path, output_text_path)
    convert_image_to_binary(image_path, output_binary_path)
    display_simulated_image(output_binary_path)
    # time.sleep(5000)
