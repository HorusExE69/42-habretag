class PlantError(Exception):
    def __init__(self, message):
        super().__init__(f"Caught PlantError: {message}")

def water_plant(plant_name) :
    if plant_name != plant_name.capitalize():
        raise PlantError(f"Invalid plant name to water: {plant_name}")
    else:
        print(f"Watering {plant_name}: [OK]")

def test_watering_system(tab_plants):
    print("Opening watering system")
    try:
        for plant in tab_plants:
            water_plant(plant)
    except PlantError as e:
        print(e)
        print("...ending tests and returning to main")
    finally:
        print("Closing watering system")

if __name__ == "__main__":
    print("=== Garden Watering System ===\n")
    print("Testing valid plants...")
    plants = ["Tomato", "Lettuce", "Carrots"]
    test_watering_system(plants)
    print("\nTesting invalid plants...")
    plants = ["Tomato", "lettuce", "Carrots"]
    test_watering_system(plants)
    print("\nCleanup always happens, even with errors!")