class User:
    def __init__(self, name, pwd):
        self.name = name
        self.pwd = pwd


class Account:
    def __init__(self):
        self.user_list = []

    def login(self, name, pwd):
        """
        用户登录
        """
        for i in self.user_list:
            if i.name == name and i.pwd == pwd:
                return True
        return False

    def register(self, name, pwd):
        """
        用户注册
        """
        for i in self.user_list:
            if name == i.name:
                return False

        self.user_list.append(User(name, pwd))
        return True

    def run(self):
        """
        主程序
        """
        count = 0
        while count < 2:
            name = input("用户名:")
            pwd = input("密码:")
            isRegister = self.register(name, pwd)
            if isRegister:
                count += 1
            else:
                print("用户名重复！")

        count = 3
        print("登录")
        while count > 0:
            name = input("用户名:")
            pwd = input("密码:")
            islogin = self.login(name, pwd)
            if islogin:
                print("登录成功!")
                break
            else:
                count -= 1
                print(f"密码错误！还剩{count}次机会")


if __name__ == "__main__":
    obj = Account()
    obj.run()
