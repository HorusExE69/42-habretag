class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self.height = height
        self._age = age

    def show(self):
        print(
            (
                f"{self.name.capitalize()}"
                f": "
                f"{self.height:.1f}"
                f"cm, "
                f"{self._age}"
                f" days old"
            )
        )

    def grow(self, size):
        self.height += size

    def age(self, days):
        self._age += days
        return self._age


if __name__ == "__main__":
    start_size = 25
    rose = Plant("Rose", 25, 30)
    print("=== Garden Plant Growth ===")
    rose.show()
    for i in range(1, 8):
        rose.grow(0.8)
        rose.age(1)
        print(f"=== Day {i} ===")
        rose.show()
    print(f"Growth this week: {rose.height - start_size:.1f}cm")
