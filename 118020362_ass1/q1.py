finalAccountValue = eval(input('Enter the final account value:'))
annualInterestRate = eval(input('Enter the annual interest rate:'))
numberOfYears = eval(input('Enter the number of the years:'))
initialDepositAmount = finalAccountValue/(1+annualInterestRate/100)**numberOfYears
print('The initial value is:',initialDepositAmount)
