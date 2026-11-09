import sys
import typing

if __name__ == "__main__":
    try:
        file_name = sys.argv[1]
    except IndexError:
        print("Usage: python3 ft_ancient_text.py <file>")
        sys.exit(1)

    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file '{file_name}'")
    try:
        with open(file_name, "r", encoding="utf-8") as fd:
            print("---\n")
            print(fd.read())
            print("\n---")
        print(f"File '{file_name}' closed.")
    except PermissionError:
        print(
            f"Error opening file '{file_name}': [Errno 13] Permission denied: '{file_name}'")
        sys.exit(1)
    except FileNotFoundError:
        print(
            f"Error opening file '{file_name}': [Errno 2] No such file or directory: '{file_name}'")
        sys.exit(1)
