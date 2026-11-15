
from ex1 import HealingCreatureFactory, TransformCreatureFactory


def test_healing_factory(factory):
    print("Testing Creature with healing capability")

    base_creature = factory.create_base()
    evolved_creature = factory.create_evolved()

    print(" base:")
    print(base_creature.describe())
    print(base_creature.attack())
    print(base_creature.heal())

    print(" evolved:")
    print(evolved_creature.describe())
    print(evolved_creature.attack())
    print(evolved_creature.heal())


def test_transform_factory(factory):
    print("Testing Creature with transform capability")

    base_creature = factory.create_base()
    evolved_creature = factory.create_evolved()

    print(" base:")
    print(base_creature.describe())
    print(base_creature.attack())
    print(base_creature.transform())
    print(base_creature.attack())
    print(base_creature.revert())

    print(" evolved:")
    print(evolved_creature.describe())
    print(evolved_creature.attack())
    print(evolved_creature.transform())
    print(evolved_creature.attack())
    print(evolved_creature.revert())


def main():
    healing_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    test_healing_factory(healing_factory)
    print()
    test_transform_factory(transform_factory)


if __name__ == "__main__":
    main()
