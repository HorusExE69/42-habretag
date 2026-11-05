class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self.age = age
        print(
            f"Created: {self.name.capitalize()}: {self.height}cm, {self.age} days old")

    def grow(self, size):
        self.height += size

    def age(self, days):
        self._age += days
        return self._age

if __name__ == "__main__":
    print("=== Plant Factory Output ===")
    rose = Plant("Rose", 25.0, 30)
    oak = Plant("Oak", 200.0, 365)
    cactus = Plant("Cactus", 5.0, 90)
    sunflower = Plant("Sunflower", 80.0, 45)
    fern = Plant("Fern", 15.0, 120)
