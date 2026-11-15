from abc import ABC, abstractmethod


class BattleStrategy(ABC):

    @abstractmethod
    def is_valid(self, creature):
        pass

    @abstractmethod
    def act(self, creature):
        pass
