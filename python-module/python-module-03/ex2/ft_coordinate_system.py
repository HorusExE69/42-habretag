import math


class InvalidParam(Exception):
    def __init__(self, lst_message):
        str_message = ""
        for i in range(0, len(lst_message)):
            if i != len(lst_message) - 1:
                str_message += f"{lst_message[i]}\n"
            else:
                str_message += f"{lst_message[i]}"
        super().__init__(str_message)


def get_player_pos():
    err = []
    while True:
        try:
            input_str = input(
                "Enter new coordinates as floats in format 'x,y,z': ")
            if input_str.count(",") == 2 :
                input_str = input_str.replace(" ", "")
                (x,y,z) = input_str.split(",")
            elif input_str.count(",") < 2 :
                raise Exception("Not enough arguments")
            else :
                raise Exception("Too much arguments")
            if not x.isdigit():
                err.append(f"Error on parameter '{x}': could not convert string to float: '{x}'")
            if not y.isdigit():
                err.append(f"Error on parameter '{y}': could not convert string to float: '{y}'")
            if not z.isdigit():
                err.append(f"Error on parameter '{z}': could not convert string to float: '{z}'")
            if err:
                raise InvalidParam(err)
        except InvalidParam as e:
            print(e)
        except Exception as e:
            print(e)
        else:
            break
    return (float(x), float(y), float(z))


if __name__ == "__main__":
    print("=== Game Coordinate System ===\n")
    print("Get a first set of coordinates")
    player_pos = get_player_pos()
    print("Got a first tuple: ", player_pos)
    print(
        f"It includes: X={player_pos[0]}, Y={player_pos[1]}, Z={player_pos[2]}")
    print("Distance to center:", math.sqrt(
        player_pos[0]**2 + player_pos[1]**2 + player_pos[2]**2))
    print("")
    print("Get a second set of coordinates")
    player_pos2 = get_player_pos()
    print("Distance between the 2 sets of coordinates:", math.sqrt(
        (player_pos2[0] - player_pos[0])**2 + (player_pos2[1] - player_pos[1])**2 + (player_pos2[2] - player_pos[2])**2))
