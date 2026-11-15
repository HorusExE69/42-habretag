from ex0.creature_factory import CreatureFactory
from .transform_creatures import Shiftling, Morphagon


class TransformCreatureFactory(CreatureFactory):
    def __init__(self):
        pass

    def create_base(self):
        return Shiftling()

    def create_evolved(self):
        return Morphagon()
