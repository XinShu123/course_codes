def sqrt(n):
    lastGuess = 1
    while n>=0:
        nextGuess = (lastGuess + (n/lastGuess))/2
        if abs(nextGuess-lastGuess)>=0.0001:
            lastGuess = nextGuess
        elif abs(nextGuess-lastGuess)<0.0001:
            return nextGuess
def main():
    try:
        n = eval(input('enter a number:'))
        print('The approximated square root is',sqrt(n))
    except:
        print('Invalid input.you should input an integer.')
main()        
        
        
