def input_temperature(temp_str) :
    tmp = int(temp_str);
    return tmp;

def test_temperature() :
    print("=== Garden Temperature ===\n")
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
    print("All tests completed - program didn't crash")

if __name__ == "__main__":
    test_temperature()
