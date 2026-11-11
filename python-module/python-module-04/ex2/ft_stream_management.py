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
            content = fd.read()
            print(content)
            print("\n---")
        print(f"File '{file_name}' closed.")
        print("")
        print("Transform data:")
        content = content.replace("\n", "#\n")
        content += "#"
        print("---\n")
        print(content)
        print("\n---")
        print("Enter new file name (or empty): ", end="", flush=True)
        n_file = sys.stdin.readline().strip()
        if n_file:
            print(f"Saving data to '{n_file}'")
            try:
                with open(n_file, "w", encoding="utf-8") as n_fd:
                    n_fd.write(content)
                print(f"Data saved in file '{n_file}'")
            except PermissionError:
                print(
                    f"[STDERR] Error opening file '{n_file}': [Errno 13] Permission denied: '{n_file}'", file=sys.stderr)
                print("Data not saved")
                sys.exit(1)
            except FileNotFoundError:
                print(
                    f"[STDERR] Error opening file '{n_file}': [Errno 2] No such file or directory: '{n_file}'", file=sys.stderr
                )
            except IsADirectoryError:
                print(
                    f"[STDERR] Error opening file '{n_file}': [Errno 21] Is a directory: '{n_file}'", file=sys.stderr
                )
        else:
            print("No saving data")
    except PermissionError:
        print(
            f"[STDERR] Error opening file '{file_name}': [Errno 13] Permission denied: '{file_name}'", file=sys.stderr)
        sys.exit(1)
    except FileNotFoundError:
        print(
            f"[STDERR] Error opening file '{file_name}': [Errno 2] No such file or directory: '{file_name}'", file=sys.stderr)
        sys.exit(1)
