from abc import ABC, abstractmethod


class TransformCapability(ABC):
    def __init__(self):
        self.is_trans = False

    @abstractmethod
    def transform(self):
        pass

    @abstractmethod
    def revert(self):
        pass
