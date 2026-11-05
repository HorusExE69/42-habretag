class Plant:
    def __init__(self, name, height, age) -> None:
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
        self._stat = self.Stat(self)

    def show(self):
        self._stat._tot_show += 1
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

    def get_stat(self):
        return self._stat

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
        self._stat._tot_growth += 1
        if not isinstance(size, (int, float)):
            print("Error, size must be a number")
        elif size < 0:
            print("Error, size can't be negative")
        else:
            self._height += size

    def age(self, days):
        self._stat._tot_age += 1
        self._age += days
        return self._age

    @staticmethod
    def is_more_than_a_year(days):
        if days > 365:
            return True
        else:
            return False

    @classmethod
    def anonymous(cls, height=0, age=0):
        return cls("Unknown", height, age)

    class Stat:
        def __init__(self, plant) :
            self._tot_growth = 0
            self._tot_age = 0
            self._tot_show = 0
            self.plant = plant

        def show_totals(self):
            print(
                (
                    f"Stats: "
                    f"{self._tot_growth} grow, "
                    f"{self._tot_age} age, "
                    f"{self._tot_show} show"
                )
            )


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
        self._stat._tot_shade += 1
        print(f"Tree {self._name.capitalize()} now produces a shade of {self._height:.1f}cm long and {self.trunk_diameter:.1f}cm wide")

    class Stat(Plant.Stat):
        def __init__(self, tree):
            super().__init__(tree)
            self._tot_shade = 0

        def show_totals(self):
            super().show_totals()
            print(f" {self._tot_shade} shade")


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


class Seed(Flower):
    def __init__(self, name, height, age, color, nb_seeds):
        super().__init__(name, height, age, color)
        self.nb_seeds = nb_seeds

    def show(self):
        super().show()
        print(f" Seeds: {self.nb_seeds}")

    def bloom(self, seeds):
        super().bloom()
        self.nb_seeds += seeds


if __name__ == "__main__":
    print("=== Garden statistics ===")
    print("=== Check year-old")
    print(f"Is 30 days more than a year? -> {Plant.is_more_than_a_year(30)}")
    print(f"Is 400 days more than a year? -> {Plant.is_more_than_a_year(400)}")
    print("\n=== Flower")
    rose = Flower("rose", 15, 10, "red")
    rose.show()
    print("[statistics for Rose]")
    rose.get_stat().show_totals()
    print("[asking the rose to grow and bloom]")
    rose.grow(8)
    rose.bloom()
    rose.show()
    print("[statistics for Rose]")
    rose.get_stat().show_totals()
    print("")
    print("=== Tree")
    oak = Tree("oak", 200, 365, 5)
    oak.show()
    print("[statistics for Oak]")
    oak.get_stat().show_totals()
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    print("[statistics for Oak]")
    oak.get_stat().show_totals()

    print("\n=== Seed")
    sunflower = Seed("sunflower", 80, 45, "yellow", 0)
    sunflower.show()
    print("[make sunflower grow, age and bloom]")
    sunflower.grow(30)
    sunflower.age(20)
    sunflower.bloom(42)
    sunflower.show()
    print("[statistics for Sunflower]")
    sunflower.get_stat().show_totals()