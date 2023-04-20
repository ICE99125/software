from time import time
import os
import re


class Student:
    '''
    学生类
    '''
    def __init__(self, name, studentID, tel) -> None:
        self.__name = name
        self.__studentID = studentID
        self.__tel = tel

    def getName(self):
        return self.__name

    def getStudentID(self):
        return self.__studentID

    def getTel(self):
        return self.__tel

    def changeName(self, name):
        self.__name = name

    def changeStudentID(self, studentID):
        self.__studentID = studentID

    def changeTel(self, tel):
        self.__tel = tel


class StudentList:
    '''
    通讯录
    '''
    studentlist = []

    # 菜单栏
    @classmethod
    def menu(cls):
        name = "南开大学学生管理系统"
        quit = "离开(q)"
        add = "添加信息(a)"
        modify = "更新数据(m)"
        display = "检查数据(c)"
        delete = "移除数据(d)"
        total = 40  # 总宽度
        nl = total - cls.ChineseNum(name)
        ql = total - cls.ChineseNum(quit)
        al = total - cls.ChineseNum(add)
        ml = total - cls.ChineseNum(modify)
        cl = total - cls.ChineseNum(display)
        dl = total - cls.ChineseNum(delete)

        cls.clearTerminal()  # 清空控制台
        print("#".center(total, "#"))
        print(f"{name:^{nl}}\n{add:^{al}}\n{modify:^{ml}}\n", end="")
        print(f"{display:^{cl}}\n{delete:^{dl}}\n{quit:>{ql}}")
        print("#".center(total, "#"))

    # 判断学生 ID 是否重复
    def checkIDexist(self, ID):
        a = list(filter(lambda x: x.getStudentID() == ID, self.studentlist))
        if len(a) == 0:
            return True
        else:
            return False

    # 添加学生信息
    def add(self):
        while True:
            self.clearTerminal()
            name = input("姓名:")
            while True:
                studentID = input("学号:")
                if self.checknum(studentID):
                    if self.checkIDexist(studentID):
                        break
                    else:
                        print("学号重复, 请尝试更新操作")
                else:
                    print("输入错误")
            while True:
                tel = input("电话号:")
                if self.checkTelnum(tel):
                    break
                else:
                    print("输入错误")

            # 将学生对象加入列表里
            self.studentlist.append(Student(name, studentID, tel))
            print('添加成功!')

            if input('退出(q)') == "q":
                self.menu()
                break

    # 删除学生信息
    def delete(self):
        while True:
            self.clearTerminal()
            studentID = input('输入想要删除学生的学号:')
            f = filter(lambda x: x.getStudentID() == studentID,
                       self.studentlist)
            stu = list(f)
            if len(stu) == 0:
                print("信息不存在")
            else:
                s = stu[0]
                print(f"将删除学生:{s.getName()}, 学号{s.getStudentID()}")
                self.studentlist.remove(s)
                print('删除成功')

            if input('退出(q):') == 'q':
                self.menu()
                break

    # 更新学生信息
    def modify(self):
        while True:
            self.clearTerminal()
            studentID = input('输入想要更新信息的学生学号:')
            f = filter(lambda x: x.getStudentID() == studentID,
                       self.studentlist)
            stu = list(f)
            if len(stu) == 0:
                print("信息不存在")
            else:
                student = stu[0]
                ModifiedKey = input('更新信息?name/ID/tel:')
                for item in ModifiedKey.split(','):
                    if item == "name":
                        name = input("姓名:")
                        student.changeName(name)
                    elif item == 'tel':
                        while True:
                            tel = input("电话:")
                            if self.checkTelnum(tel):
                                student.changeTel(tel)
                                break
                            else:
                                print("电话输入错误")
                    elif item == 'ID':
                        while True:
                            id = input("学号:")
                            if self.checknum(id):
                                if self.checkIDexist(id):
                                    student.changeStudentID(id)
                                    break
                                else:
                                    print("学号已存在")
                            else:
                                print("学号输入错误")
                    else:
                        print("输入错误")

            if input('退出(q)') == "q":
                self.menu()
                break

    # 展示学生信息
    def display(self):
        # 展示表格
        def table(list_):
            gap = 17  # 表格间隙
            num = 4  # 表项数目
            table_Length = gap * num  # 表格总长度
            title = "详细数据"

            print(f"+{'-':{'-'}^{table_Length - 1}}+")
            print(f"|{title:^{table_Length - self.ChineseNum(title) - 1}}|")

            # 分割线
            splitLine = f"{'+':{'-'}<{gap}}" * num + "+"
            print(splitLine)

            header = ""
            for i in ["序号", "姓名", "学号", "电话"]:
                n = gap - self.ChineseNum(i) - 1
                header += f"|{i:^{n}}"
            print(header + "|")
            print(splitLine)

            # 展示学生信息
            for index, item in enumerate(list_):
                name = item.getName()
                studentID = item.getStudentID()
                tel = item.getTel()
                nl = gap - self.ChineseNum(name) - 1
                sl = gap - self.ChineseNum(studentID) - 1
                tl = gap - self.ChineseNum(tel) - 1
                print(f"|{index + 1:^{gap - 1}}|{name:^{nl}}|", end="")
                print(f"{studentID:^{sl}}|{tel:^{tl}}|")
                print(splitLine)

        # 抽取满足条件的学生
        def filter_(arg):
            if "name" in arg:
                stuList = filter(lambda x: x.getName() == arg[1],
                                 self.studentlist)
                return list(stuList)
            elif "ID" in arg:
                stuList = filter(lambda x: x.getStudentID() == arg[1],
                                 self.studentlist)
                return list(stuList)
            elif "tel" in arg:
                stuList = filter(lambda x: x.getTel() == arg[1],
                                 self.studentlist)
                return list(stuList)

        while True:
            self.clearTerminal()
            userInput = input('输入查询信息(all/name/ID/tel):')

            start = time()
            if userInput == '':
                continue
            elif userInput == 'all':
                if len(self.studentlist) == 0:
                    print("学生列表为空")
                else:
                    table(self.studentlist)
            else:
                stuList = filter_(userInput.split(","))
                if stuList:
                    table(stuList)
                else:
                    print("相关信息不存在")
            end = time()
            print(f"本次查询耗时:{end - start}s")

            if input('退出(q):') == 'q':
                self.menu()
                break

    # 服务开启
    def start(self):
        self.menu()
        while True:
            try:
                mode = input('请输入你的选项:')
                if mode == 'a':
                    self.add()
                elif mode == 'm':
                    self.modify()
                elif mode == 'c':
                    self.display()
                elif mode == 'd':
                    self.delete()
                elif mode == 'q':
                    self.clearTerminal()
                    break
                else:
                    raise Exception('输入错误')
            except Exception as e:
                print(e)

    # 根据平台清空控制台
    @staticmethod
    def clearTerminal():
        platform = os.name
        if platform == 'nt':
            # windows
            os.system('cls')
        elif platform == 'posix':
            # linux
            os.system('clear')

    # 检测电话号码正确性
    @staticmethod
    def checkTelnum(n):
        rex = '0?(13|14|15|18|17)[0-9]{9}'
        r = re.findall(rex, n)
        if len(r) == 1:
            return True
        else:
            return False

    # 判断中文字符数
    @staticmethod
    def ChineseNum(n):
        return len(re.findall('([\u4e00-\u9fa5])', n))

    # 学号必须全是数字
    @staticmethod
    def checknum(n):
        rex = '^[0-9]*$'
        r = re.findall(rex, n)
        if len(r) == 1:
            return True
        else:
            return False


def main():
    slist = StudentList()
    slist.start()


if __name__ == "__main__":
    main()
