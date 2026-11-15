from ex0 import FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import (
    NormalStrategy,
    AggressiveStrategy,
    DefensiveStrategy,
    InvalidStrategyException
)


def battle(opponent1, opponent2):
    factory1, strategy1 = opponent1
    factory2, strategy2 = opponent2

    creature1 = factory1.create_base()
    creature2 = factory2.create_base()

    print("\n* Battle *")
    print(creature1.describe())
    print("vs.")
    print(creature2.describe())
    print("now fight!")

    for creature, strategy in (
        (creature1, strategy1),
        (creature2, strategy2)
    ):
        if not strategy.is_valid(creature):
            strategy_name = strategy.__class__.__name__
            strategy_name = strategy_name.replace("Strategy", "").lower()
            raise InvalidStrategyException(
                f"Invalid Creature '{creature.name}' "
                f"for this {strategy_name} strategy"
            )

        result = strategy.act(creature)

        if isinstance(result, tuple):
            for action in result:
                print(action)
        else:
            print(result)


def tournament(opponents):
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")
    
    try:
        for i in range(len(opponents)):
            for j in range(i + 1, len(opponents)):
                battle(opponents[i], opponents[j])
    except InvalidStrategyException as error:
        print(f"Battle error, aborting tournament: {error}")


def main():
    flame_factory = FlameFactory()
    aqua_factory = AquaFactory()
    healing_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    normal = NormalStrategy()
    aggressive = AggressiveStrategy()
    defensive = DefensiveStrategy()

    print("Tournament 0 (basic)")
    print("[ (Flameling+Normal), (Healing+Defensive) ]")
    tournament([
        (flame_factory, normal),
        (healing_factory, defensive)
    ])

    print("\nTournament 1 (error)")
    print("[ (Flameling+Aggressive), (Healing+Defensive) ]")
    tournament([
        (flame_factory, aggressive),
        (healing_factory, defensive)
    ])

    print("\nTournament 2 (multiple)")
    print("[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]")
    tournament([
        (aqua_factory, normal),
        (healing_factory, defensive),
        (transform_factory, aggressive)
    ])


if __name__ == "__main__":
    main()
