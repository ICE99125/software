import os
import re
'''
The function of this program
1.Function menu
2.Add data
3.Modify data
4.Check data
5.CheckDataByID
6.Remove data
'''


def ChineseNum(n):
    # 判断中文字符数
    return len(re.findall('([\u4e00-\u9fa5])', n))


class NkAddressBookManagement():
    Name = '南开大学学生管理系统'
    QuitTip = '输入 [q] 离开'
    DataTitle = '详细数据'
    # TableTab = ['No.', 'ID', 'Name', 'QQ', 'Tel', 'Email']
    TableTab = ['序号', '学号', '姓名', 'QQ', '电话', '邮箱']
    addData = '添加信息\t[a]'
    Modifydata = '更新数据\t[m]'
    checkData = '检查数据\t[c]'
    removeData = '移除数据\t[r]'

    def DisplayMenu(self):
        clearTerminal()
        tl = 40  # 总宽度
        # 中文字符在控制台占据两个英文字符的文字
        # 因此将总宽度减去中文字符数
        nl = tl - ChineseNum(self.Name)
        ql = tl - ChineseNum(self.QuitTip)
        al = tl - ChineseNum(self.addData)
        ml = tl - ChineseNum(self.Modifydata)
        cl = tl - ChineseNum(self.checkData)
        rl = tl - ChineseNum(self.Modifydata)
        MenuFormat = '{0:{0}^%s}\n{2:{1}^%s}\n\n{3:{1}^%s}\n{4:{1}^%s}\n{5:{1}^%s}\n{6:{1}^%s}\n\n{7:{1}>%s}\n{0:{0}^%s}' % (
            tl, nl, al, ml, cl, rl, ql, tl)
        print(
            MenuFormat.format('#', ' ', self.Name, self.addData,
                              self.Modifydata, self.checkData, self.removeData,
                              self.QuitTip))

    def AddData(self, StudentList):
        while True:
            try:
                clearTerminal()
                StudentItem = dict()
                # obetain student Info by user input
                for index, item in enumerate(self.TableTab):
                    if item == '学号':
                        ID = int(input('%d.学号:' % index))
                        if ID in StudentList.keys():
                            raise Exception('学号已存在,输入 [q] -> [m] 来更新')
                        else:
                            StudentItem[item] = ID
                    elif item == 'QQ':
                        while True:
                            e = input('%d.%s:' % (index, item))
                            if checkQQnum(e):
                                StudentItem[item] = e
                                break
                            else:
                                print('QQ格式错误!')
                    elif item == '电话':
                        while True:
                            e = input('%d.%s:' % (index, item))
                            if checkTelnum(e):
                                StudentItem[item] = e
                                break
                            else:
                                print('电话错误!')
                    elif item == '邮箱':
                        while True:
                            e = input('%d.%s:' % (index, item))
                            if checkEmail(e):
                                StudentItem[item] = e
                                break
                            else:
                                print('邮箱错误!')
                    elif index != 0:
                        StudentItem[item] = input('%d.%s:' % (index, item))
                StudentList.update({StudentItem['学号']: StudentItem})
                print('😛 添加成功!\n')
                self.DisplayTable({StudentItem['学号']: StudentItem})
            except ValueError:
                print('😥 学号必须是数字类型!!')
            except Exception as ex:
                print(ex)

            YourInput = input('输入 [q] 返回菜单/输入任意字符继续:')
            if YourInput == 'q':
                self.DisplayMenu()
                break

    def ModifyData(self, StudentList):
        clearTerminal()
        while True:
            Key = int(input('输入想要更改信息的学生学号:'))

            # try other method to judge Key not found
            if StudentList.get(Key) is not None:
                print('你可以更新以下信息:', end='')
                for index, item in enumerate(self.TableTab):
                    if index != 0 and index != 1:
                        print('[%s]' % item, end=' ')
                print("(使用 ',' 分割)")
                ModifiedKey = input('输入想要更新的信息:')

                for item in ModifiedKey.split(','):
                    if item not in self.TableTab:
                        print('😥 输入错误,请确保输入正确!\n')
                    elif item == '邮箱':
                        while True:
                            ModifyData = input('%s改成:' % item)
                            if checkEmail(ModifyData):
                                StudentList[Key][item] = ModifyData
                                break
                            elif ModifyData == '':
                                break
                            else:
                                print('%s格式错误' % item)
                    elif item == '电话':
                        while True:
                            ModifyData = input('%s改成:' % item)
                            if checkTelnum(ModifyData):
                                StudentList[Key][item] = ModifyData
                                break
                            elif ModifyData == '':
                                break
                            else:
                                print('%s格式错误' % item)
                    elif item == 'QQ':
                        while True:
                            ModifyData = input('%s改成:' % item)
                            if checkQQnum(ModifyData):
                                StudentList[Key][item] = ModifyData
                                break
                            elif ModifyData == '':
                                break
                            else:
                                print('%s格式错误' % item)
                    else:
                        ModifyData = input('%s改成:' % item)
                        if ModifyData != '':
                            StudentList[Key][item] = ModifyData
                print('😛 更新结束!\n')
            else:
                print('😨 学号不存在\n')

            YourInput = input('输入 [q] 返回菜单/输入任意键继续:')
            if YourInput == 'q':
                self.DisplayMenu()
                break

    def CheckData(self, StudentList):
        while True:
            try:
                clearTerminal()
                key = input('输入 [all] 查看全部学生信息/也可以输入学号:')

                if key == '':
                    continue
                elif key == 'all':
                    self.DisplayTable(StudentList)
                else:
                    key = int(key)
                    self.DisplayTable({key: StudentList[key]})
            except KeyError:
                print('😨 学号不存在\n')
            except ValueError:
                print('😥 学号必须是数字类型!!')
            except Exception as ex:
                print(ex)

            YourInput = input('输入 [q] 返回菜单/输入任意键继续:')
            if YourInput == 'q':
                self.DisplayMenu()
                break

    def DisplayTable(self, list):
        # The gap of the value of table
        GAP = 17

        length = len(self.TableTab)
        # Some formatting for table
        InfoFormat1 = ''
        for item in self.TableTab:
            ll = GAP - ChineseNum(item)
            InfoFormat1 = InfoFormat1 + '|{:^%d}' % ll
        InfoFormat1 = InfoFormat1 + '|'

        InfoFormat2 = ('+{0:{0}^%d}' % GAP) * length + '+'  # +---+---+

        TitleFormat = '|{:^%d}|' % (length * GAP + length - 1 - ChineseNum(
            self.DataTitle))  # |    xxx    |

        print('-' * (length * GAP + length + 1))
        print(TitleFormat.format(self.DataTitle))
        print(InfoFormat2.format('-'))
        print(InfoFormat1.format(*self.TableTab))
        print(InfoFormat2.format('-'))

        for index, item in enumerate(list.values()):
            a = []
            InfoFormat3 = '|{:^%d}' % GAP
            for i in item.values():
                a.append(i)
                if isinstance(i, str):
                    info_l = GAP - ChineseNum(i)
                    InfoFormat3 = InfoFormat3 + '|{:^%d}' % info_l
                else:
                    InfoFormat3 = InfoFormat3 + '|{:^%d}' % GAP
            InfoFormat3 = InfoFormat3 + '|'
            print(InfoFormat3.format(index + 1, *a))
            print(InfoFormat2.format('-'))

        print()

    def RemoveData(self, StudentList):
        while True:
            clearTerminal()
            try:
                Key = int(input('输入想要删除学生的学号:'))
                StudentList.pop(Key)
                print('😛 删除成功!\n')
            except KeyError:
                print('😨 学号不存在\n')
            except ValueError:
                print('😥 学号必须是数值类型!!\n')

            YourInput = input('输入 [q] 返回菜单/输入任意键继续:')
            if YourInput == 'q':
                self.DisplayMenu()
                break


def start():
    M = NkAddressBookManagement()
    StudentList = dict()
    M.DisplayMenu()
    while True:
        try:
            SelectMenu = input('😋 请输入你的选项:')
            if SelectMenu == 'a':
                M.AddData(StudentList)
            elif SelectMenu == 'm':
                M.ModifyData(StudentList)
            elif SelectMenu == 'c':
                M.CheckData(StudentList)
            elif SelectMenu == 'r':
                M.RemoveData(StudentList)
            elif SelectMenu == 'q':
                clearTerminal()
                break
            else:
                raise Exception('😥 输入错误!')
        except Exception as ex:
            print(ex)


# 检测 QQ 号
def checkQQnum(n):
    rex = '[1-9]([0-9]{4,10})'
    r = re.findall(rex, n)
    if len(r) == 1:
        return True
    else:
        return False


# 检测电话号码
def checkTelnum(n):
    rex = '0?(13|14|15|18|17)[0-9]{9}'
    r = re.findall(rex, n)
    if len(r) == 1:
        return True
    else:
        return False


# 检测邮箱
def checkEmail(n):
    rex = r'\w[-\w.+]*@([A-Za-z0-9][-A-Za-z0-9]+\.)+[A-Za-z]{2,14}'
    r = re.findall(rex, n)
    if len(r) == 1:
        return True
    else:
        return False


# 根据平台清空控制台
def clearTerminal():
    platform = os.name
    if platform == 'nt':
        os.system('cls')
    elif platform == 'posix':
        os.system('clear')


if __name__ == '__main__':
    start()
