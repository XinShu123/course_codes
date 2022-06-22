class Node:
    def __init__(self,element,pointer):
        self.element = element
        self.pointer = pointer
        
class LinkedQueue:
    
    def __init__(self):
        self.head=None
        self.tail=None
        self.size=0

    def __len__(self):
        return self.size

    def is_empty(self):
        return self.size==0

    def first(self):
        if self.is_empty():
            print('Queue is empty.')
        else:
            return self.head.element

    def end(self):
        if self.is_empty():
            print('Queue is empty.')
        else:
            node=self.head
            while node != None:
                end=node.element
                node=node.pointer
            return end

    def dequeue(self):
        if self.is_empty():
            print('Queue is empty.')
        else:
            answer=self.head.element
            self.head=self.head.pointer
            self.size-=1
            if self.is_empty():
                self.tail=None
            return answer

    def enqueue(self,e):
        newest=Node(e,None)
        if self.is_empty():
            self.head=newest
        else:
            self.tail.pointer=newest
        self.tail=newest
        self.size+=1

    def __str__(self):
        queue=[]
        node=self.head
        while node != None:
            queue.append(str(node.element))
            node=node.pointer
        return str(queue)
def myQuickSort(head):
    if head == None or head.pointer == None:
        return head
    pivot = head.element
    i = head
    leftHead = head
    leftHeadNumber = 0
    while i.pointer!=None:
        if i.pointer.element<pivot:
            temp = i.pointer
            i.pointer = i.pointer.pointer
            temp.pointer = leftHead
            leftHead = temp
            leftHeadNumber+=1
        else:
            i = i.pointer
            
    rightHead = leftHead
    count = 0
    while count<=leftHeadNumber:
        rightHead = rightHead.pointer
        count+=1
        
    leftTail = leftHead
    number = 0
    while number<leftHeadNumber:
        leftTail = leftTail.pointer
        number+=1
    leftTail.pointer = None
    
    smallest = myQuickSort(leftHead)
    j = smallest
    while j.pointer!=None:
        j = j.pointer
    j.pointer = head
    head.pointer = myQuickSort(rightHead)
##    rightTail = rightHead
##    while rightTail.pointer!=None:
##        rightTail = rightTail.pointer
##    rightTail.pointer = None    
    return smallest
def main():
    while True:
        try:
            head = eval(input('enter the reference of first node(like LQ.head):'))
            smallest = myQuickSort(head)
            print(smallest)
            break
        except:
            print('Invalid input.')
LQ = LinkedQueue()
for i in [2,7,5,3,4,12,9]:
    LQ.enqueue(i)
main()
i = myQuickSort(LQ.head)
print(LQ)

    

            
    
