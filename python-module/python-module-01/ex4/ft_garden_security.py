class Plant:
    def __init__(self, name, height, age):
        if type(name) is not str:
            print("Error, name must be a string")
        if not isinstance(height, (int, float)):
            print("Error, height must be a number")
        if height < 0:
            print("Error, height can't be negative")
        if type(age) is not int:
            print("Error, age must be an integer")
        if age < 0:
            print("Error, age can't be negative")
        self._name = name
        self._height = height
        self._age = age
        print(
            (
                f"Plant created: "
                f"{self._name.capitalize()}"
                f": "
                f"{self._height:.1f}"
                f"cm, "
                f"{self._age}"
                f" days old"
            )
        )

    def show(self):
        print(
            (
                f"Current state : "
                f"{self._name.capitalize()}"
                f": "
                f"{self._height:.1f}"
                f"cm, "
                f"{self._age}"
                f" days old"
            )
        )

    def get_name(self):
        return self._name

    def get_height(self):
        return self._height

    def get_age(self):
        return self._age

    def set_name(self, name):
        if type(name) is not str:
            print("Error, name must be a string")
        else:
            self._name = name
            print(f"Name updated: {self._name}")

    def set_height(self, height):
        if not isinstance(height, (int, float)):
            print("Error, height must be a number")
        elif height < 0:
            print("Error, height can't be negative")
        else:
            self._height = height
            print(f"Height updated: {self._height}cm")

    def set_age(self, age):
        if type(age) is not int:
            print("Error, age must be an integer")
        elif age < 0:
            print("Error, age can't be negative")
        else:
            self._age = age
            print(f"Age updated: {self._age} days")

    def grow(self, size):
        self.height += size

    def age(self, days):
        self._age += days
        return self._age


if __name__ == "__main__":
    print("=== Garden Security System ===")
    plant = Plant("rose", 15, 10)
    print("")
    plant.set_height(25)
    if plant.get_height() != 25:
        print("Height update rejected")
    plant.set_age(30)
    if plant.get_age() != 30:
        print("Age update rejected")
    print("")
    plant.set_height(-5)
    if plant.get_height() != -5:
        print("Height update rejected")
    plant.set_age(-15)
    if plant.get_age() != -15:
        print("Age update rejected")
    print("")
    plant.show()
