for i in range(1, 10):
    for j in range(i):
        print('%d×%d=%d' % (i, j + 1, i * (j + 1)), end='\t')
    print()
