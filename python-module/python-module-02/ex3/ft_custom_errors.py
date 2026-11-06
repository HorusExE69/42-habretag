class GardenError(Exception):
    def __init__(self, message):
        super().__init__(f"Caught GardenError: {message}")


class PlantError(Exception):
    def __init__(self, message):
        super().__init__(f"Caught PlantError: {message}")


class WaterError(Exception):
    def __init__(self, message):
        super().__init__(f"Caught WaterError: {message}")


if __name__ == "__main__":
    print("=== Custom Garden Errors Demo ===\n")
    print("Testing PlantError...")
    try:
        raise PlantError("The tomato plant is wilting!")
    except PlantError as e:
        print(e)
    print("\nTesting WaterError...")
    try:
        raise WaterError("Not enough water in the tank!")
    except WaterError as e:
        print(e)
    print("\nTesting catching all garden errors...")
    try:
        raise GardenError("The tomato plant is wilting!")
    except GardenError as e:
        print(e)
    try:
        raise GardenError("Not enough water in the tank!")
    except GardenError as e:
        print(e)
    print("\nAll custom error types work correctly!")

