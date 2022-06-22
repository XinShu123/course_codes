try:
 N = eval(input('Enter a nonnegative integer:'))
 if N > 0 and N % 1 == 0:

     m = 1
     while m <= N:
            print('%-8d%-8d%-8d'%(m,m+1,m**(m+1)))
            m = m+1
 elif N <= 0:
     print('Invalid input.You wrongly input a nonpositive number.You should input a nonnegative integer.')
 elif N % 1!=0:
     print('Invalid input.You wrongly input a float number.You should input a nonnegative integer .')
except:
    print('Invalid input: You wrongly input a string.You should input a nonnegative integer.')
    


