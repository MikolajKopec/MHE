import math


class Puzzle():
    size = None
    board = None
    rating = 0
    def __init__(self,size,board):
        self.size = size
        self.board = board

    def __str__(self) -> str:
        for i, field in enumerate(self.board):
            if i%self.size == 0:
                print("")
            if field == -2:
                print("*",end =" "),
            elif field == -3:
                print("#",end =" "),
            elif field == -4:
                print("o",end =" "),
            else:
                print(field,end =" "),
        print("")
        return ""
    
    def get_row(self,row_number):
        start_index = row_number*self.size
        end_index = start_index + self.size
        return [self.board[i] for i in range(start_index,end_index)]

    def get_column(self,column_number):
        start_index = column_number
        end_index = self.size*self.size-(self.size-column_number)
        result = [self.board[i] for i in range(start_index,end_index+1,self.size)]
        return result


    def check_bulb_is_alone(self,array):
        is_bulb = False
        for i,field in enumerate(array):
            if is_bulb and field == -4:
                self.rating = self.rating + 1
            if(field == -4):
                is_bulb = True
            if(field>=0):
                is_bulb = False

    def evaluate_bulbs(self):
        for i in range(self.size):
            self.check_bulb_is_alone(self.get_column(i))
            # print(self.rating)
            self.check_bulb_is_alone(self.get_row(i))
            # print(self.rating)

    def turn_off_lights(self):
        for i,each in enumerate(self.board):
            if each == -2:
                self.board[i] = -3

    def get_row_by_element_index(self,i):
        return math.trunc(i/self.size)

    def get_column_by_element_index(self,i):
        return i%self.size

    def light_row(self,bulb_index):
        row = self.get_row_by_element_index(bulb_index)
        end_index1 = self.size*(row+1)
        end_index2 = self.size*row
        for i in range(bulb_index,end_index1):
            if(self.board[i] == -3):
                self.board[i] = -2
            if(self.board[i]>=0):
                break
        for i in range(bulb_index,end_index2-1,-1):
            if(self.board[i] == -3):
                self.board[i] = -2
            if(self.board[i]>=0):
                break
    def light_column(self,bulb_index):
        column = self.get_column_by_element_index(bulb_index)
        for i in range(bulb_index,len(self.board),self.size):
            if(self.board[i] == -3):
                self.board[i] = -2
            if(self.board[i]>=0):
                break
        for i in range(bulb_index,column-1,-self.size):
            if(self.board[i] == -3):
                self.board[i] = -2
            if(self.board[i]>=0):
                break

    def turn_on_lights(self):
        for i,field in enumerate(self.board):
            if(field==-4):
                self.light_column(i)
                self.light_row(i)
    
    def check_if_all_fields_are_light_up(self):
        for each in self.board:
            if each == -3:
                self.rating = self.rating+1

    def check_if_bulbs_are_next_to_square(self):
        for i,each in enumerate(self.board):
            number_of_neighors = 0
            if each in [5, -4,-2]:
                continue
            elif each >=0:
                number_of_neighors = each
            if i > self.size and self.board[i - self.size] == -4:
                number_of_neighors -= 1
            if (
                i + self.size < self.size * self.size
                and self.board[i + self.size] == -4
            ):
                number_of_neighors -=1
            if i % self.size != 0 and self.board[i - 1] == -4:
                number_of_neighors-=1
            if i % self.size != self.size - 1 and self.board[i + 1] == -4:
                number_of_neighors -=1
            if number_of_neighors != 0:
                self.rating = self.rating + abs(number_of_neighors)


    def evaluate(self,board_to_solve):
        # print(self)
        
        for i,each in enumerate(board_to_solve.board):
            if each>=0:
                self.board[i] = each
        # print(self)
        self.turn_off_lights()
        self.turn_on_lights()
        self.evaluate_bulbs()
        self.check_if_all_fields_are_light_up()
        self.check_if_bulbs_are_next_to_square()