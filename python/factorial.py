# 阶乘
def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)


print('10 的阶乘：%d' % factorial(10))