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

    def show(self):
        print(
            (
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
        if not isinstance(size, (int, float)):
            print("Error, size must be a number")
        elif size < 0:
            print("Error, size can't be negative")
        else:
            self._height += size

    def age(self, days):
        self._age += days
        return self._age


class Flower(Plant):
    def __init__(self, name, height, age, color):
        super().__init__(name, height, age)
        self._color = color
        self._isblooming = False

    def bloom(self):
        if self._isblooming:
            print(f"{self._name.capitalize()} has already bloom")
        else:
            self._isblooming = True

    def show(self):
        super().show()
        print(f" Color: {self._color}")
        if self._isblooming:
            print(f" {self._name.capitalize()} is blooming beautifully!")
        else:
            print(f" {self._name.capitalize()} has not bloomed yet")


class Tree(Plant):
    def __init__(self, name, height, age, trunk_diameter):
        super().__init__(name, height, age)
        self.trunk_diameter = trunk_diameter

    def show(self):
        super().show()
        print(f" Trunk diameter: {self.trunk_diameter:.1f}cm")

    def produce_shade(self):
        print(f"Tree {self._name.capitalize()} now produces a shade of {self._height:.1f}cm long and {self.trunk_diameter:.1f}cm wide")


class Vegetable(Plant):
    def __init__(self, name, height, age, harvest_season, nutritional_value):
        super().__init__(name, height, age)
        self.harvest_season = harvest_season
        self.nutritional_value = nutritional_value

    def show(self):
        super().show()
        print(f" Harvest season: {self.harvest_season.capitalize()}")
        print(f" Nutritional value: {self.nutritional_value}")

    def grow(self, size):
        super().grow(size)

    def age(self, days):
        new_age = super().age(days)
        self.nutritional_value += days
        return new_age


if __name__ == "__main__":
    print("=== Garden Plant Types ===")
    print("=== Flower")
    rose = Flower("rose", 15, 10, "red")
    rose.show()
    print("[asking the rose to bloom]")
    rose.bloom()
    rose.show()
    print("")
    print("=== Tree")
    oak = Tree("oak", 200, 365, 5)
    oak.show()
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    print("")
    print("=== Vegetable")
    tomato = Vegetable("tomato", 5, 10, "april", 0)
    tomato.show()
    print("[make tomato grow and age for 20 days]")
    tomato.grow(42)
    tomato.age(20)
    tomato.show()
