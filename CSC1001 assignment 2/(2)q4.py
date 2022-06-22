def isAnagram(s1,s2):
    lis1 = []
    for i in s1:
        lis1.append(i)
    lis1.sort()
    lis2 = []
    for j in s2:
        lis2.append(j)
    lis2.sort()
    if lis1 == lis2:
        return True
    else:
        return False
def main():
    s1 = input('Enter one string:')
    s2 = input('Enter another string:')
    if isAnagram(s1,s2):
        print('is an anagram')
    else:
        print('is not an anagram')
main()
