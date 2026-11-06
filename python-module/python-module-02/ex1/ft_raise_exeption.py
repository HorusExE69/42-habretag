def input_temperature(temp_str) :
    tmp = int(temp_str);
    if 0 <= tmp <= 40 :
        return tmp;
    if (tmp > 40) :
        raise ValueError(f"{tmp}°C is too hot for plants (max 40°C)")
    if (tmp < 0) :
        raise ValueError(f"{tmp}°C is too cold for plants (min 0°C)")

def test_temperature() :
    print("=== Garden Temperature Checker ===\n")
    print("Input data is '25'")
    try:
        input_temperature("25");
        print("Temperature is now 25°C")
    except ValueError as error:
        print(f"Caught input_temperature error: {error}")
    print("")
    print("Input data is 'abc'")
    try:
        input_temperature("abc");
        print("Temperature is now abc°C")
    except ValueError as error:
        print(f"Caught input_temperature error: {error}")
    print("")
    print("Input data is '100'")
    try:
        input_temperature("100");
        print("Temperature is now 100°C")
    except ValueError as error:
        print(f"Caught input_temperature error: {error}")
    print("")
    print("Input data is '-50'")
    try:
        input_temperature("-50");
        print("Temperature is now -50°C")
    except ValueError as error:
        print(f"Caught input_temperature error: {error}")
    print("")
    print("All tests completed - program didn't crash")

if __name__ == "__main__":
    test_temperature()