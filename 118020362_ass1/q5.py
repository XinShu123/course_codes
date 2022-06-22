try:
    N = eval(input('Enter an integer larger than 2:'))
    if N > 2:
        count = 0
        for i in range(2,N):
            if i == 2:
                print('The prime numbers smaller than %d include:'%N)
                print('%-8d'%i,end = '')
                count+=1
            else:
                for j in range(2,i):
                    if i % j == 0:
                        break
                    elif j == i-1:
                        print('%-8d'%i,end = '')
                        count+=1
                        if count % 8 == 0:
                            print()
    else:
        print('Invalid input:you should input an integer larger than 2.')
except:
    print('Invalid input:you should enter an integer rather than a string.')
