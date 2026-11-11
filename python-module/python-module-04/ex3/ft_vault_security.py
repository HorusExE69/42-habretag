def secure_archive(file_name, str="r", content=None):
    try :
        if str == "r":
            with open(file_name, "r", encoding="utf-8") as f:
                res = f.read()
            return (True, res)
        elif str == "w":
            with open(file_name, "w", encoding="utf-8") as f:
                f.write(content)
            return (True, f"Content successfully written to '{file_name}'")
        else :
            return (False, f"Invalid mode '{str}'. Use 'r' for read or 'w' for write.")
    except PermissionError:
        return (False, f"[Errno 13] Permission denied: '{file_name}'")
    except FileNotFoundError:
        return (False, f"[Errno 2] No such file or directory: '{file_name}'")
    except IsADirectoryError:
        return (False, f"[Errno 21] Is a directory: '{file_name}'")

if __name__ == "__main__":
    print("=== Cyber Archives Security ===\n")
    print("Using 'secure_archive' to read from a nonexistent file:\n", secure_archive("nonexistent_file.txt", "r"))
    print("")
    print("Using 'secure_archive' to read from an inaccessible file:\n", secure_archive("/sgoinfre/habretag", "r"))
    print("")
    content = secure_archive("ft_vault_security.py", "r")
    print("Using 'secure_archive' to read from a regular file:\n", secure_archive("ft_vault_security.py", "r"))
    print("")
    print("Using 'secure_archive' to write previous content to a new file:\n", secure_archive("test.txt", "w", content[1]))