# -*- coding: utf-8 -*-

from copy import copy, deepcopy

class SimpleLayer:
    background = [0, 0, 0, 0]
    content = "blank"

    def get_content(self):
        return self.content

    def get_background(self):
        return self.background

    def paint(self, painting):
        self.content = painting

    def set_background(self, background):
        self.background[3] = background

    def fill_background(self, background):
        self.background = background

    def clone(self):
        return copy(self)

    def deep_clone(self):
        return deepcopy(self)


if __name__ == "__main__":
    # 一般深拷贝比浅拷贝复制得更加完全，但也更占资源（包括时间和空间资源）
    # 浅拷贝：会拷贝对象内容及其内容的引用或者子对象的引用，但不会拷贝引用的内容和子对象本身
    dog_layer = SimpleLayer()
    dog_layer.paint("Dog")
    dog_layer.fill_background([0, 0, 255, 0])
    print("Original background: ", dog_layer.get_background())
    print("Original Painting: ", dog_layer.get_content())
    print("\n")

    copy_dog_layer = dog_layer.clone()
    copy_dog_layer.paint("Puppy")
    copy_dog_layer.set_background(128)
    print("Original background: ", dog_layer.get_background())
    print("Original Painting: ", dog_layer.get_content())
    print("Copy background: ", copy_dog_layer.get_background())
    print("Copy Painting: ", copy_dog_layer.get_content())
    print("\n")


    # 深拷贝：不仅拷贝了对象和内容的引用，也会拷贝引用的内容
    dog_layer = SimpleLayer()
    dog_layer.paint("Dog")
    dog_layer.fill_background([0, 0, 255, 0])
    print("Original background: ", dog_layer.get_background())
    print("Original Painting: ", dog_layer.get_content())
    print("\n")
    
    deep_copy_dog_layer = dog_layer.deep_clone()
    deep_copy_dog_layer.paint("Puppy")
    deep_copy_dog_layer.set_background(128)
    print("Original background: ", dog_layer.get_background())
    print("Original Painting: ", dog_layer.get_content())
    print("DeepCopy background: ", deep_copy_dog_layer.get_background())
    print("DeepCopy Painting: ", deep_copy_dog_layer.get_content())