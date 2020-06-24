# Python 3.6
# Tamir Cohen 17/03/2020
import argparse

# Examples:
# grids = [
#     [" XX "],
#
#     ["    ",
#      "  X ",
#      "  X ",
#      "    "],
#
#     ["           ",
#      "X---------X",
#      "           ",
#      "           "],
#     ["     ",
#      "  X  ",
#      "  |  ",
#      "  |  ",
#      "  X  "],
#     # Note: this grid is only valid when starting on the right-hand X, but still considered valid
#     ["                      ",
#      "   +-------+          ",
#      "   |     +-++---+     ",
#      "X--+     +--+   X     "],
#
#     [" X  ",
#      " |  ",
#      " +  ",
#      " X  "],
#
#     ["              ",
#      "   +------    ",
#      "   |          ",
#      "X--+      X   ",
#      "              "],
#
#     ["      +------+",
#      "      |      |",
#      "X-----+------+",
#      "      |       ",
#      "      X       "],
#     ["+-----+",
#      "|+---+|",
#      "||+-+||",
#      "|||X+||",
#      "X|+--+|",
#      " +----+"],
#
#     ["X-----+",
#      "|     |",
#      "|     |",
#      "|     |",
#      "+-----W"]
# ]

grids = [
    [
        "X+++",
        "+++X"]
]


def get_possible_move(row, column, row_max, column_max):
    """
    ret returns the positions available around given char
    :param row: char row index
    :param column: char column index
    :param row_max: char row index max
    :param column_max: char column index max
    :return: [(row, column), (row, column)...]
    """
    # all slots to check around the char
    position_available = [(row - 1, column), (row + 1, column), (row, column + 1), (row, column - 1)]

    # filter positions out of index
    position_valid = list(filter(lambda pos: -1 < pos[0] < row_max and -1 < pos[1] < column_max, position_available))


def check_symbols_valid(lines):
    """
    this function checks if there any floating pieces of road or invalid symbols
    :param lines: list of string in const size
    :return: (bool) true if there is a floating piece
    """
    number_of_x = 0

    for row in range(len(lines)):
        for column in range(len(lines[row])):
            current_char = lines[row][column]

            if current_char == " ":
                continue

            # num of X in map
            if current_char == "X":
                number_of_x += 1

                if number_of_x > 2:
                    print("Too many X in map!")
                    return False

            # invalid char
            if current_char not in [" ", "X", "|", "-", "+"]:
                print("Invalid Char '{}' in map!".format(current_char))
                return False

            # checking floating symbols
            position_valid = return_valid_pos(row, column, len(lines), len(lines[row]))

            # locking for non-empty cells
            if len(list(filter(lambda pos: lines[pos[0]][pos[1]] != " ", position_valid))) == 0:
                print("Floating char '{}' in map!".format(current_char))
                return False

    return True


def check_turn_valid(turns_pos, grid):
    """
    function check that all turn pieces are used properly,
    :param turns_pos: list of string in const size
    :param grid: map grid
    :return: True if all ok, False otherwise
    """
    for turn_pos in turns_pos:

        position_valid = return_valid_pos(turn_pos[0], turn_pos[1], len(grid), len(grid[turn_pos[0]]))
        turn_inputs = 0
        # going over all valid positions around the turn
        for pos in position_valid:
            found_route = False
            char = grid[pos[0]][pos[1]]
            # after turn we need to go row up or down, only interested if char is facing me
            if char in ["-", "X", "+"] and pos[0] == turn_pos[0]:
                turn_inputs += 1
                possible_turns = [(turn_pos[0] + 1, turn_pos[1]), (turn_pos[0] - 1, turn_pos[1])]

                for option in possible_turns:
                    # if it is in the index range
                    if option in position_valid:
                        # found valid out from turn
                        if grid[option[0]][option[1]] in ["|", "+", "X"]:
                            found_route = True

                if not found_route:
                    print("1: Turn err -, could not calc row {} column {}".format(turn_pos[0], turn_pos[1]))
                    return False

            # after turn we need to go column up or down, only interested if char is facing me
            if char in ["|", "X", "+"] and pos[1] == turn_pos[1]:
                turn_inputs += 1
                possible_turns = [(turn_pos[0], turn_pos[1] + 1), (turn_pos[0], turn_pos[1] - 1)]

                for option in possible_turns:
                    # if it is in the index range
                    if option in position_valid:
                        # found valid out from turn
                        if grid[option[0]][option[1]] in ["-", "+", "X"]:
                            found_route = True

                if not found_route:
                    print("2: Turn err |, could not calc row {} column {}".format(turn_pos[0], turn_pos[1]))
                    return False

        if turn_inputs < 2:
            print("3: Turn err, not enough inputs to turn at row {} column {}".format(turn_pos[0], turn_pos[1]))
            return False

    return True


def try_route(start_row, start_column, lines):
    """

    :param start_row:
    :param start_column:
    :param lines:
    :return:
    """
    current_pos = (start_row, start_column)
    last_pos = (None, None)

    while True:
        valid_move = False
        current_char = lines[current_pos[0]][current_pos[1]]

        # checking finish
        if current_char == "X" and last_pos != (None, None):
            return True

        position_valid = return_valid_pos(current_pos[0], current_pos[1], len(lines), len(lines[start_row]))
        non_empty_chars = list(filter(lambda pos: lines[pos[0]][pos[1]] != " ", position_valid))

        # checking start
        if current_char == "X":
            possible_start = (None, None)
            for pos in non_empty_chars:
                possible_char = lines[pos[0]][pos[1]]

                # same row as me
                if possible_char in ["-", "X", "+"] and pos[0] == current_pos[0]:
                    # if not null means i already found someone...
                    if possible_start[0] is not None:
                        print("Err1: X can only have one output")
                        print(non_empty_chars, possible_char, last_pos, pos)
                        return False
                    else:
                        possible_start = pos

                # same column as me
                if possible_char in ["|", "X", "+"] and pos[1] == current_pos[1]:
                    # if not null means i already found someone...
                    if possible_start[0] is not None:
                        print("Err2: X can only have one output")
                        return False
                    else:
                        possible_start = pos

            last_pos = current_pos
            current_pos = possible_start
            continue

        # checking row
        if current_char == "-":
            for pos in non_empty_chars:
                # finding next step, same row but different column, not the last position
                if pos[0] == current_pos[0] and pos[1] != current_pos[1] and pos[1] != last_pos[1] and lines[pos[0]][
                    pos[1]] in ["-", "+", "X"]:
                    last_pos = current_pos
                    current_pos = pos
                    valid_move = True
                    break

            if not valid_move:
                print("Couldn't move after char '-' in {}".format(current_pos))
                return False

        # checking column
        if current_char == "|":
            for pos in non_empty_chars:
                # finding next step, same column but different row, not the last position
                if pos[1] == current_pos[1] and pos[0] != current_pos[0] and pos[0] != last_pos[0] and lines[pos[0]][
                    pos[1]] in ["|", "+", "X"]:
                    last_pos = current_pos
                    current_pos = pos
                    valid_move = True
                    break

            if not valid_move:
                print("Couldn't move after char '|' in {}".format(current_pos))
                return False

        # checking intersection
        if current_char == "+":
            # same row, so we need to change row
            if last_pos[0] == current_pos[0]:
                num_of_options = 0
                for pos in non_empty_chars:
                    # finding next step, same column but different row, not the last position
                    if pos[1] == current_pos[1] and pos[0] != current_pos[0] and pos[0] != last_pos[0] and \
                            lines[pos[0]][pos[1]] in ["|", "+", "X"]:
                        last_pos = current_pos
                        current_pos = pos
                        valid_move = True
                        num_of_options += 1

                if not valid_move:
                    print("Couldn't move after char '-+' in {}".format(current_pos))
                    return False
                elif num_of_options > 1:
                    print("too much options after turn '+' in {}".format(current_pos))
                    return False

            # same column, so we need to change column
            elif last_pos[1] == current_pos[1]:
                num_of_options = 0
                for pos in non_empty_chars:
                    # finding next step, same row but different column, not the last position
                    if pos[0] == current_pos[0] and pos[1] != current_pos[1] and pos[1] != last_pos[1] and \
                            lines[pos[0]][
                                pos[1]] in ["-", "+"]:
                        last_pos = current_pos
                        current_pos = pos
                        valid_move = True
                        num_of_options += 1

                if not valid_move:
                    print("Couldn't move after char '+|' in {}".format(current_pos))
                    return False
                elif num_of_options > 1:
                    print("too much options after turn '+' in {}".format(current_pos))
                    return False


def line_valid(lines):
    turns = []
    first_x_pos = (None, None)
    second_x_pos = (None, None)

    for row in range(len(lines)):
        for column in range(len(lines[row])):
            current_char = lines[row][column]

            if current_char == "X":
                print("$> Found X at row {} column {}".format(row, column))

                if first_x_pos[0] is None:
                    first_x_pos = (row, column)
                else:
                    second_x_pos = (row, column)

            if current_char == "+":
                turns.append((row, column))

    if not check_symbols_valid(lines):
        print("!> Floating road was found, invalid map")
        return False

    if not check_turn_valid(turns, lines):
        print("!> Invalid turn usage, invalid map")
        return False

    if first_x_pos[0] is None:
        print("&> No Start point found")
        return False

    if try_route(first_x_pos[0], first_x_pos[1], lines) or try_route(second_x_pos[0], second_x_pos[1], lines):
        print("@> Route is valid")
        return True

    else:
        print("!> Could not resolve route")
        return False

def make_next_step(current_pos, grid):
    current_symbol = grid[current_pos[0]][current_pos[1]]

    # in-index positions around me
    valid_positions = get_valid_pos(current_pos[0], current_pos[1], len(grid), len(grid[current_pos[0]]))



if __name__ == '__main__':
    if __name__ == '__main__':
        results = []
        for grid in grids:
            print("#########################")
            results.append(line_valid(grid))
            print("#########################\n")

        for i in results:
            print(i)
