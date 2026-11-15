from ex0.creature import Creature
from .heal_capability import HealCapability


class Sproutling(Creature, HealCapability):
    def __init__(self):
        super().__init__("Sproutling", "Grass")

    def heal(self):
        return "Sproutling heals itself for a small amount"

    def attack(self):
        return "Sproutling uses Vine Whip!"


class Bloomelle(Creature, HealCapability):
    def __init__(self):
        super().__init__("Bloomelle", "Grass/Fairy")

    def heal(self):
        return "Bloomelle heals itself and others for a large amount"

    def attack(self):
        return "Bloomelle uses Petal Dance!"
