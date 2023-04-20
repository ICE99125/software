# 总部
class Headquarters:
    def __init__(self):
        self.school_list = []  # 分校列表

    # 查询分校总余额
    def statistic_balance(self):
        balance = 0
        for i in self.school_list:
            balance += i.balance
        return balance

    # 统计员工人数
    def statistic_staff_num(self):
        num = 0
        for i in self.school_list:
            num += i.staff_num
        return num

    # 统计学员人数
    def statistic_student_num(self):
        num = 0
        for i in self.school_list:
            num += i.student_num
        return num

    # 新开一个校区
    def add_school(self, school):
        self.school_list.append(school)

    # 将学生转到另一个校区
    def transfer(self, student, school):
        # 调用 self.leave_school(student) 先让学生退学
        # 再调用 school.add_student(student) 添加至另一个校区
        pass

    # 学生退学
    def leave_school(self, student):
        # 从 school_list 中找到包含该学生的学校
        # 调用 delete_student(student) 删除
        pass


# 学生类
class Student:
    class_list = []

    def add_class(self, class_):
        self.class_list.append(class_)  # 加入新班级

    def leave_class(self):
        self.class_list.clear()  # 退学/转学


# 学校类
class School:
    def __init__(self, location, name):
        self.location = location  # 校区地址
        self.name = name  # 校区名
        self.staff_list = []  # 职员列表
        self.student_list = []  # 学生列表
        self.balance = 0  # 学校账户余额
        self.class_list = []  # 学校开设课程

    # 员工人数
    @property
    def staff_num(self):
        return len(self.staff_list)

    # 学生人数
    @property
    def student_num(self):
        return len(self.student_list)

    # 移除学生
    # 移除的时候随便调用 student.leave_class() 清空该学生的班级列表
    def delete_student(self, student):
        pass

    # 添加学生
    def add_student(self, student, class_index):
        self.student_list.append(student)  # 学生入学
        student.add_class(self.class_list[class_index])  # 学生入班
        # 遍历学生的班级列表获取总学费
        for i in student.class_list:
            self.balance += i.price

    # 添加员工/老师
    def add_staff(self, staff):
        pass

    # 员工/老师辞职
    def delete_staff(self, staff):
        pass

    # 新开课程
    def create_class(self, class_):
        self.class_list.append(class_)


# 员工类
class Staff:
    pass


# 老师类
class Teacher(Staff):
    pass


# 班级类
class Class:
    def __init__(self, course_list):
        self.course_list = course_list  # 班级课程列表

    # 加入班级的费用
    # 遍历班级课程列表获取总费用
    @property
    def price(self):
        total_price = 0
        for i in self.course_list:
            total_price += i.price

        return total_price


# 课程类
class Course:
    def __init__(self, type, price):
        self.type = type  # 课程名
        self.price = price  # 课程定价


def main():
    h = Headquarters()  # 培训机构总部
    s = School("北京", "xx培训机构")  # 开始一家培训机构
    h.add_school(s)  # 并入总部
    c = Class([Course("前端", 10000), Course("后端", 10000)])  # 开设一个班
    student1 = Student()  # 学生 1 号
    s.create_class(c)  # 班级加入学校
    s.add_student(student1, 0)  # 学生入学并加入 0 号班级


if __name__ == '__main__':
    main()
