'''
What is the Fibonacci sequence?
F(1)=1
F(2)=1
F(n)=F(n-1)+F(n-2)
'''


# 斐波那契数列-递归法
def fibonacci_1(n):
    n = int(n)
    if n == 1 or n == 2:
        return 1
    else:
        return fibonacci_1(n - 1) + fibonacci_1(n - 2)


f1 = fibonacci_1(10)
print('递归法：%d' % f1)


# 斐波那契数列-列表循环法
def fibonacci_2(n):
    n = int(n)
    i = 1
    fib = []
    while i <= n:
        if i < 3:
            fib.append(1)
        else:
            fib.append(fib[i - 3] + fib[i - 2])
        i = i + 1
    return fib


f2 = fibonacci_2(10)
print('列表循环法：%s' % f2)


# 斐波那契数列-循环法
def fibonacci_3(n):
    n = int(n)
    a, b = 1, 1
    i = 1
    while i < n:
        a, b = b, a + b
        i = i + 1
    return a


f3 = fibonacci_3(10)
print('循环法：%s' % f3)


# 斐波那契数列-生成器
def fibonacci_4(n):
    a, b = 1, 1
    for _ in range(n):
        yield a
        a, b = b, a + b


f4 = list(fibonacci_4(10))
print(f"生成器法：{f4}")
