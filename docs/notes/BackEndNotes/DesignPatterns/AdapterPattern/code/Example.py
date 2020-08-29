# -*- coding: utf-8 -*-


class AStaff:
    name = ""
    id = ""
    phone = ""

    def __init__(self, id):
        self.id = id
    
    def getName(self):
        print "A protocol getName method...id:%s"%self.id
        return self.name
    
    def setName(self, name):
        print "A protocol setName method...id:%s"%self.id
        self.name = name

    def getPhone(self):
        print "A protocol getPhone method...id:%s"%self.id
        return self.phone

    def setPhone(self, phone):
        print "A protocol setPhone method...id:%s"%self.id
        self.phone=phone


class BStaff:
    name = ""
    id = ""
    telephone = ""

    def __init__(self, id):
        self.id=id

    def get_name(self):
        print "B protocol get_name method...id:%s"%self.id

        return self.name
    def set_name(self, name):
        print "B protocol set_name method...id:%s"%self.id
        self.name = name

    def get_telephone(self):
        print "B protocol get_telephone method...id:%s"%self.id
        return self.telephone

    def set_telephone(self, telephone):
        print "B protocol get_name method...id:%s"%self.id
        self.telephone = telephone


# 适配器
class StaffAdapter:
    adapter = ""

    def __init__(self, id):
        self.adapter = BStaff(id)

    def getName(self):
        return self.adapter.get_name()

    def getPhone(self):
        return self.adapter.get_telephone()

    def setName(self, name):
        self.adapter.set_name(name)
    
    def setPhone(self, phone):
        self.adapter.set_telephone(phone)


if __name__ == "__main__":
    a_staff= AStaff("123")
    a_staff.setName("AAA")
    a_staff.setPhone("0731-36262324")
    print("A Staff Name: ", a_staff.getName())
    print("A Staff Phone: ", a_staff.getPhone())
    print("\n")

    b_staff = StaffAdapter("456")
    b_staff.setName("BBB")
    b_staff.setPhone("023-54323425")
    print("B Staff Name: ", b_staff.getName())
    print("B Staff Phone: ", b_staff.getPhone())
    print("\n")