from ex0.creature import Creature
from .transform_capability import TransformCapability


class Shiftling(Creature, TransformCapability):
    def __init__(self):
        super().__init__("Shiftling", "Normal")
        TransformCapability.__init__(self)

    def attack(self):
        if self.is_trans:
            return "Shiftling performs a boosted strike!"
        return "Shiftling attacks normally"

    def transform(self):
        self.is_trans = True
        return "Shiftling shifts into a sharper form!"

    def revert(self):
        self.is_trans = False
        return "Shiftling returns to normal."


class Morphagon(Creature, TransformCapability):
    def __init__(self):
        super().__init__("Morphagon", "Normal/Dragon")
        TransformCapability.__init__(self)

    def attack(self):
        if self.is_trans:
            return "Morphagon unleashes a devastating morph strike!"
        return "Morphagon attacks normally."

    def transform(self):
        self.is_trans = True
        return "Morphagon morphs into a dragonic battle form!"

    def revert(self):
        self.is_trans = False
        return "Morphagon stabilizes its form."
