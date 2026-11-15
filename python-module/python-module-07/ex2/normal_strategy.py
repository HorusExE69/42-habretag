from .battle_strategy import BattleStrategy


class NormalStrategy(BattleStrategy) :

    def is_valid(self, creature):
        return True

    def act(self,creature) :
        return  creature.attack() 
