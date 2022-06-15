from ._fseg import Pet
from ._fseg import Animal, Dog

def go(kind: str, steps: int):
    if kind.lower() == 'dog':
        return Dog().go(steps)
    else:
        return Animal().go(steps)

def foo():
    return Pet('kettie', Pet.Cat)