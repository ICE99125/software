import time

print('闭包实现简单的进度条')


def outer():
    step = 0

    def inner():
        nonlocal step
        step = step + 1
        return step

    return inner


a = outer()
for _ in range(100):
    time.sleep(0.01)  # 防止一下子就到 100%
    print("\r%s%%" % a(), end="")

print()

print('装饰器实现进度条')


def outer(func):
    def inner(n):
        time.sleep(0.01)
        func(n)

    return inner


@outer
def processor(n):
    print("\r%s%%" % n, end="")


for i in range(101):
    processor(i)

print()
print('闭包修改数组')


def outer():
    list = []

    def inner(n):
        list.append(n)
        return list

    return inner


a = outer()
print(a('美羊羊'))
print(a('喜羊羊'))
print(a('懒洋洋'))
