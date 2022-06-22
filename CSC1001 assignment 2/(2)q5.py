
def Student(lis,n):#find one student's activity
    
    
    number = int(n)
    index = -1
    lis1 = []
    while index<=99-number:
        index = index+number
        lis1.append(index)
      
    
        
    
    for i in lis1:#a list of state
        if lis[i] == False:#a list of index
           lis[i] = True

        else:
            lis[i] = False
            
    return lis
def main():
    n = 100
    a = 1
    print('After 100 th student\'s coming,')
    lis = [False for i in range(0,100)]
    
    while a <= n:
        lis = Student(lis,a)
        a+=1
    print(lis)
    count = 0
    index = 0
    for i in lis:
        index+=1
        if i:
            count+=1
            print('The %d th locker is open.'%(index))
    print('%d lockers are open.'%count)
main()    

    

    
    
    
    
