from math import sin
from math import cos
from math import tan


func = input('please specify a trigonometric function(sin,cos,tan):')
if func == 'sin':
    func = sin
if func == 'cos':
    func = cos
if func == 'tan':
    func = tan
try:    
 lowerLimit = eval(input('please enter the lower limit:'))
 upperLimit = eval(input('please enter the upper limit:'))
 interval = upperLimit-lowerLimit
 if interval > 0:
  n = float(input('please enter the number of the sub-intervals:'))
  m = 1
  sumup = 0
  if n % 1 == 0 and n >= 1:
    while m <= n:
        sumup = sumup + interval/n*func(lowerLimit+interval/n*(m-1/2))
        m = m+1
    print(sumup)
  else:
    print('Invalid input:you should input an integer and it should be no smaller than one.')
 else:
     print('Invalid input:upper limit should be larger than lower limit.')
except:
    print('Invalid input.you should input numbers rather than a string.')
    
        
    
    
    
    
