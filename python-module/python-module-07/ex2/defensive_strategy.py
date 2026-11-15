from .battle_strategy import BattleStrategy
from ex1.heal_capability import HealCapability
from .exceptions import InvalidStrategyException


class DefensiveStrategy(BattleStrategy):

    def is_valid(self, creature):
        return isinstance(creature, HealCapability)

    def act(self, creature):
        if not self.is_valid(creature):
            raise InvalidStrategyException(
                f"Invalid Creature '{creature.name}' "
                "for this defensive strategy"
            )

        attack_result = creature.attack()
        heal_result = creature.heal()
        return attack_result, heal_result
