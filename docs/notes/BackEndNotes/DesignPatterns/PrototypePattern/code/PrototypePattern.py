# -*- coding: UTF-8 -*-

import copy


class SelfReferencingEntity:
    def __init__(self):
        self.parent = None

    def set_parent(self, parent):
        self.parent = parent


class SomeComponent:
    """
    """

    def __init__(self, some_int, some_list_of_objects, some_circular_ref):
        self.some_int = some_int
        self.some_list_of_objects = some_list_of_objects
        self.some_circular_ref = some_circular_ref

    def __copy__(self):
        """
        """
        # 创建嵌套对象的副本
        some_list_of_objects = copy.copy(self.some_list_of_objects)
        some_circular_ref = copy.copy(self.some_circular_ref)

        # 使用准备好的嵌套对象克隆来克隆对象本身
        new = self.__class__(
            self.some_int, some_list_of_objects, some_circular_ref
        )
        new.__dict__.update(self.__dict__)

        return new

    def __deepcopy__(self, memo={}):
        """
        """
        # 创建嵌套对象的副本
        some_list_of_objects = copy.deepcopy(self.some_list_of_objects, memo)
        some_circular_ref = copy.deepcopy(self.some_circular_ref, memo)

        # 使用准备好的嵌套对象克隆来克隆对象本身
        new = self.__class__(
            self.some_int, some_list_of_objects, some_circular_ref
        )
        new.__dict__ = copy.deepcopy(self.__dict__, memo)

        return new



if __name__ == "__main__":

    list_of_objects = [1, {1, 2, 3}, [1, 2, 3]]
    circular_ref = SelfReferencingEntity()
    component = SomeComponent(23, list_of_objects, circular_ref)
    circular_ref.set_parent(component)

    shallow_copied_component = copy.copy(component)

    # 更改列表，检查是否发生变化
    shallow_copied_component.some_list_of_objects.append("another object")
    if component.some_list_of_objects[-1] == "another object":
        print("已发生变化")
    else:
        print("未发生变化")

    # 在对象列表中更改设置
    component.some_list_of_objects[1].add(4)
    if 4 in shallow_copied_component.some_list_of_objects[1]:
        print("已发生变化")
    else:
        print("未发生变化")


    deep_copied_component = copy.deepcopy(component)

    deep_copied_component.some_list_of_objects.append("one more object")
    if component.some_list_of_objects[-1] == "one more object":
        print("已发生变化")
    else:
        print("未发生变化")


    component.some_list_of_objects[1].add(10)
    if 10 in deep_copied_component.some_list_of_objects[1]:
        print("已发生变化")
    else:
        print("未发生变化")

    print("id(deep_copied_component.some_circular_ref.parent): {0}".format(id(deep_copied_component.some_circular_ref.parent)))
    print("id(deep_copied_component.some_circular_ref.parent.some_circular_ref.parent): {0}".format(id(deep_copied_component.some_circular_ref.parent.some_circular_ref.parent)))