from .creature_factory import CreatureFactory
from .creature import Flameling, Pyrodon

class FlameFactory(CreatureFactory) :
    def __init__(self) :
        pass

    def create_base(self):
        return Flameling()

    def create_evolved(self):
        return Pyrodon()