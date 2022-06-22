class SLList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def __len__(self):
        return self.size

    def is_empty(self):
        return self.size == 0

    def insert_head(self,e):
        newest = Node(e,None)
        newest.pointer = self.head
        self.head = newest
        if self.is_empty():
            self.tail = newest
        self.size += 1
        return newest

    def insert_tail(self,e):
        newest = Node(e,None)
        if self.is_empty():
            self.head = newest
        else:
            self.tail.pointer = newest
        self.tail = newest
        self.size += 1
        return newest

    def delete_head(self):
        if self.head == None:
            print('The list is empty.')
        else:
            element = self.head.element
            self.head = self.head.pointer
            self.size -= 1
            return element

    def iterate(self):
        pointer = self.head
        print('The element in the list: ')
        while pointer != None:
            print(pointer.element)
            pointer = pointer.pointer
        
class Node:
    def __init__(self,element = None,pointer = None):
        self.element = element
        self.pointer = pointer
def count(head):
    if head == None:
        return 0
    else:
        return count(head.pointer)+1
lis = SLList()
lis1 = [1,2,3,4,5,6]
for i in lis1:
    lis.insert_tail(i)
lis.insert_head(1)
lis.delete_head()
lis.insert_tail(3)
    
def main():
    while True:
        try:
            n = eval(input('enter a reference for lis(like lis.head):'))
            print('the number of the nodes in lis is:',count(n))
            break
        except:
            print('Invalid input')
main()
i = lis.head
while i!=None:
    print(i.element)
    i = i.pointer

    
        
    
    
    
    
    
    
    
