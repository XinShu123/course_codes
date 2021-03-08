def getDigit(number):
    if number >=10:
        a,b = divmod(number,10)
        return a+b
    else:
        return number
def sumOfDoubleEvenPlace(number):
    number = str(number)
    index = len(number)-2
    sumup = 0
    while index >= 0:
        if 2*int(number[index]) >= 10:
            sumup+=getDigit(2*int(number[index]))
        else:    
            sumup+= 2*int(number[index])                
        index=index-2
    return sumup
def sumOfOddPlace(number):
    number = str(number)
    index = len(number)-1
    sumup = 0
    while index >= 0:
        sumup+=int(number[index])
        index = index-2
    return sumup
def isValid():
        number = input('Input an integer:')
        if number.startswith('4') or number.startswith('5') or number.startswith('37') or number.startswith('6'):
           if 13 <= len(number) <= 16:
               number = int(number)
               if (sumOfDoubleEvenPlace(number)+sumOfOddPlace(number)) % 10 == 0:
                   return 'Valid'
               else:
                return 'Invalid'
           else:
               return 'Invalid'
        else:
           return 'Invalid'
print(isValid())    

        
        
        
    
