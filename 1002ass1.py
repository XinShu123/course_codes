import numpy as nm
import random


def generate_numbers(dimension):

    num_of_numbers = dimension*dimension-1
    list = []
    for number in range(num_of_numbers):
        list.append(number+1)
    nums = random.sample(list, len(list))
    return nums

def calc_inversions(some_list):
    num_of_inversion = 0
    current_index = 0
    while(current_index < len(some_list)-1):

        comparison_index=current_index+1
        while (comparison_index <= len(some_list)-1):
            if some_list[comparison_index]<some_list[current_index]:
                num_of_inversion+=1
            comparison_index+=1
        current_index+=1
    return num_of_inversion
# print(calc_inversions([13,2,10,3,1,12,8,4,5,9,6,15,14,11,7]))

def check_solvable(dimension):
    pos_blank = random.sample(range(1,dimension*dimension+1),1)
    pos_blank=pos_blank[0]
    x_coordinate= (pos_blank-1)//dimension+1
    solvable = False
    result = []
    while not solvable:
        list = generate_numbers(dimension)
        num_inversions=calc_inversions(list)
        if dimension % 2 != 0:
            if num_inversions % 2 == 0:
                solvable = True
        else:
            if (dimension-x_coordinate+1) % 2 != 0 and num_inversions % 2 == 0:
                solvable = True
            elif (dimension-x_coordinate+1) % 2 == 0 and num_inversions % 2 != 0:
                solvable = True
        result=list
    return result, pos_blank

def check_direction(result,dimension):
    pos_blank=result.index(" ")
    x_coordinate=pos_blank // dimension + 1
    y_coordinate=pos_blank % dimension + 1
    valid_directions = []
    if x_coordinate == 1:
        valid_directions.append("up")
    elif x_coordinate == dimension:
        valid_directions.append("down")
    else:
        valid_directions.append("up")
        valid_directions.append("down")
    if y_coordinate == 1:
        valid_directions.append("left")
    elif y_coordinate == dimension:
        valid_directions.append("right")
    else:
        valid_directions.append("left")
        valid_directions.append("right")
    return valid_directions

def left_move(result):
    index=result.index(' ')
    index+=1
    temp=result[index]
    result[index]=" "
    result[index-1]=temp
    #return result

def right_move(result):
    index=result.index(' ')
    index-=1
    temp=result[index]
    result[index]=" "
    result[index+1]=temp
    #return result

def up_move(result,dimension):
    index=result.index(' ')
    index+=dimension
    temp=result[index]
    result[index]=" "
    result[index-dimension]=temp

def down_move(result,dimension):
    index=result.index(' ')
    index-=dimension
    temp=result[index]
    result[index]=" "
    result[index+dimension]=temp

def show(result,dimension):
    i=0
    while i<len(result):
        print(str(result[i]).ljust(2)+" ",end='')
        if(i+1)%dimension==0:
            print()
        i+=1

def check_solved(list):
    solved=True
    if list[len(list)-1]!=" ":
        solved=False
    i=0
    while i<len(list)-2 and solved==True:
        if list[i]>list[i+1]:
            solved=False
        i+=1
    return solved

def validate_yesno(prompt):
    if prompt != 'n' and prompt != 'q':
        raise Exception

def validate_dimension(dimension):
    if dimension <3 or dimension >10:
        raise Exception

def validate_direction(direction,dir_dist,valid_directions):
    if dir_dist.__contains__(direction):
        if dir_dist[direction] not in valid_directions:
            return False
        return True
    return False

def execute():
    try:
        dimension=int(input("Input the desired dimension of the game (>3):"))
        validate_dimension(dimension)

        left, right, up, down = input("enter the four letters for left, right, up, down operations"
        " (with blank between each direction):").split()
        dir_dist = {left: "left", right: "right", up: "up", down: "down"}
        new_dict = {v: k for k, v in dir_dist.items()}
        list, pos_blank = check_solvable(dimension)
        list.insert(pos_blank - 1, " ")
        show(list, dimension)
        solved = False
        number = 0
        while not solved:

            valid_directions = check_direction(list, dimension)
            str = "("
            for i, dir in enumerate(valid_directions):
                str = str + dir+ "-" + new_dict[dir]
                if i != len(valid_directions) - 1:
                    str += ","
            str += ")"
            direction=input("Enter your move " + str + ">")

            number += 1
            if direction == left:
                left_move(list)
            elif direction == right:
                right_move(list)
            elif direction == up:
                up_move(list, dimension)
            elif direction == down:
                down_move(list, dimension)

            show(list, dimension)
            solved = check_solved(list)
        print("Congratulations! You solved the puzzle in %d moves" % number)



    except ValueError:
        print("dimension must be an integer!")
    except Exception:
        print("dimension out of range!")




def main():
    print("Welcome to 118020362's puzzle game: you can choose from 3*3 to 10*10 dimension")
    print("The board has an empty space where an adjacent tile can be slid to.")
    print("The objective of the game is to rearrange the tiles"
    " into a sequential order by their number"
    " by repeatedly making sliding moves.")
    execute()
    while True:

        prompt=input("Enter 'n' to start a new game"
                         "or enter 'q' to quit the game:")
        if (prompt == 'n'):
            execute()
            continue
        elif prompt=='q':
            print("You quit the game!")
            break
        else:
            print("invalid input!")
            continue

if __name__=="__main__":
    main()





















