def verify(arr, checkRow):
    row2 = checkRow
    for row1 in range(1,checkRow):
        if arr[row1] == arr[row2]:
            return False
    for row1 in range(1, checkRow):
        if row1 + arr[row1] == row2 + arr[row2]:
            return False
    for row1 in range(1, checkRow):
        if row1 - arr[row1] == row2 - arr[row2]:
            return False       
    return True
def solve():
    rowOne = rowTwo = rowThree = rowFour = rowFive = rowSix = rowSeven = rowEight = 1
    for rowOne in range(1, 9):
        if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 1) == False:
            continue
        for rowTwo in range(1, 9):
            if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 2) == False:
                continue
            for rowThree in range(1, 9):
                if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 3) == False:
                    continue
                for rowFour in range(1, 9):
                    if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 4) == False:
                        continue
                    for rowFive in range(1, 9):
                        if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 5) == False:
                            continue
                        for rowSix in range(1, 9):
                            if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 6) == False:
                                continue
                            for rowSeven in range(1, 9):
                                if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 7) == False:
                                    continue
                                for rowEight in range(1, 9):
                                    if verify([0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight], 8):
                                        return [0, rowOne, rowTwo, rowThree, rowFour, rowFive, rowSix, rowSeven, rowEight]
def display():
        rowLis = solve()
        for row in range(1,9):
            for column in range(1,9):
                if rowLis[row] == column:
                    print('|Q| ',end = '')
                else:
                    print('| ',end = '')
            print()    
               
display()    
        
    
