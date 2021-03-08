def reverse(number):
    lis = []
    while number > 0:
        lis.append(number%10)
        number = number//10
    string = ''
    for i in lis:
        string+=str(i)
    return int(string)    


def isNonPalindrome(number):
    if number == reverse(number):
        return False
    elif number!=reverse(number):
        return True
from math import sqrt
def isPrime(number):
    divisor = 2
    while divisor <= sqrt(number):
        if number%divisor == 0:
            return False
        else:
            divisor+=1
            continue
    return True    
        
def reversalIsPrime(number):
    if isPrime(reverse(number)):
        return True
    else:
        return False
def main():
    number = 2
    count = 0
    print('The first 100 emirp numbers are:')
    while count <= 99:
     if isNonPalindrome(number) and isPrime(number) and reversalIsPrime(number):
         print('%8d'%number,end = '')
         count+=1
         number+=1
         if count%10==0:
             print()
     else:
         number+=1
main()        
    
    
    
        
        
