# try:
#     list_1 = [1, 2, 3, 4]
#     print(list_1[20])
# except IndexError:
#     print("index out of bound！")

# def fun():
#     try:
#         print('try--start')
#         a = 1 / 0
#         print(a)
#     except ValueError as ret:
#         print(ret)
#     except Exception as e:
#         print(e)
#     finally:
#         return 'finally'

# print(fun())

# def func():
#     try:
#         print("23")
#         return 123
#     finally:
#         print("123")
#         return 321

# print(func())

# try:
#     x = 0
#     print(x)
# except (NameError):
#     print('x未定义')
# except (Exception):
#     print('其他异常')
# else:
#     print('无异常')
# finally:
#     print('无论如何都会执行')

# def func():
#     try:
#         return 123
#     finally:
#         return 321

# print(func())

# def func():
#     a = 1
#     try:
#         a = a + 10
#     except:
#         a = a + 10
#     else:
#         a = a + 10
#     finally:
#         a = a + 10
#     return a

# print(func())


def func():
    try:
        return 123
    except Exception:
        return 111
    else:
        print(222)
    finally:
        print(321)


print(func())
