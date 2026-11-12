import alchemy

print("=== Alembic 4 ===")
print("Accesing the alchemy module using 'import alchemy'")
print(f"Testing create_air: {alchemy.create_air()}")
print("Now show that not all functions can be reached")
print(f"This will raise an exception!")
print(f"{alchemy.create_earth()}")