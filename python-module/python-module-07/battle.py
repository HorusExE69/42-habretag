
from ex0 import FlameFactory, AquaFactory


def test_factory(factory):
    print("Testing factory")

    base_creature = factory.create_base()
    evolved_creature = factory.create_evolved()

    print(base_creature.describe())
    print(base_creature.attack())

    print(evolved_creature.describe())
    print(evolved_creature.attack())


def battle(factory1, factory2):
    print("Testing battle")

    creature1 = factory1.create_base()
    creature2 = factory2.create_base()

    print(creature1.describe())
    print(" vs.")
    print(creature2.describe())
    print(" fight!")

    print(creature1.attack())
    print(creature2.attack())


def main():
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()
    test_factory(flame_factory)
    print()
    test_factory(aqua_factory)
    print()
    battle(flame_factory, aqua_factory)


if __name__ == "__main__":
    main()
