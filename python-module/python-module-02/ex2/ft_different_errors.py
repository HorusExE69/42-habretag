def garden_operation(operation_number) :
    if operation_number == 0:
        raise ValueError("Caught ValueError: invalid literals for int() with base 10: 'abc'")
    elif operation_number == 1:
        raise ZeroDivisionError("Caught ZeroDivisionError: division by zero")
    elif operation_number == 2:
        raise FileNotFoundError("Caught FileNotFoundError: [Errno 2] No such file or directory: '/non/existent/file'")
    elif operation_number == 3:
        raise TypeError("Caught TypeError: can't only concatenate str (not \"int\") to str")
    else :
        return

def test_error_types(op_nb):
    try:
        match op_nb:
            case 0:
                print("Testing operation 0...")
                garden_operation(0)
            case 1:
                print("Testing operation 1...")
                garden_operation(1)
            case 2:
                print("Testing operation 2...")
                garden_operation(2)
            case 3:
                print("Testing operation 3...")
                garden_operation(3)
            case 4:
                print("Testing operation 4...")
                garden_operation(4)
    except ValueError as error:
        print(error)
    except ZeroDivisionError as error:
        print(error)
    except FileNotFoundError as error:
        print(error)
    except TypeError as error:
        print(error)
    else:
        print("Operation completed successfully\n")

if __name__ == "__main__":
    print("=== Garden Error Demo ===")
    test_error_types(0)
    test_error_types(1)
    test_error_types(2)
    test_error_types(3)
    test_error_types(4)
    print("All error types tested successfully")