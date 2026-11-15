from .battle_strategy import BattleStrategy
from ex1.transform_capability import TransformCapability
from .exceptions import InvalidStrategyException


class AggressiveStrategy(BattleStrategy):

    def is_valid(self, creature):
        return isinstance(creature, TransformCapability)

    def act(self, creature):
        if not self.is_valid(creature):
            raise InvalidStrategyException(
                f"Invalid Creature '{creature.name}' "
                "for this aggressive strategy"
            )

        creature.transform()
        result = creature.attack()
        creature.revert()
        return result
