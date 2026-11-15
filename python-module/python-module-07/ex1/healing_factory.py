from ex0.creature_factory import CreatureFactory
from .healing_creatures import Sproutling, Bloomelle


class HealingCreatureFactory(CreatureFactory):
    def __init__(self):
        pass

    def create_base(self):
        return Sproutling()

    def create_evolved(self):
        return Bloomelle()
