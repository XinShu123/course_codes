class ListStack:
    def __init__(self):
        self.__data = list()
    def __len__(self):
        return len(self.__data)
    def is_empty(self):
        return len(self.__data) == 0
    def push(self,e):
        self.__data.append(e)
    def top(self):
        if self.is_empty():
            print('The stack is empty.')
        else:
            return self.__data[self.__len__()-1]
    def pop(self):
        if self.is_empty():
            print('The stack is empty.')
        else:
            return self.__data.pop()
        

count = 0
def HanoiTower(n):
    global count
    stack = ListStack()
    stack.push([n, "A", "B", "C"])
    while not stack.is_empty():
        curr = stack.pop()
        
        if curr[0] < 1:
            pass
        elif curr[0] == 1:
            print("%s --> %s"%(curr[1], curr[3]))
            count+=1
        else:
            stack.push([curr[0]-1, curr[2], curr[1], curr[3]])
            stack.push([1, curr[1], curr[2], curr[3]])
            stack.push([curr[0]-1, curr[1], curr[3], curr[2]])
            

n = int(input('enter the number of disks:'))
HanoiTower(n)
print('The least steps of solution is:',count)
