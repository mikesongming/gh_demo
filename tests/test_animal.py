import pytest

from fseg import animal

@pytest.mark.xfail(reason="Animal is an interface class")
def test_animal():
    animal.Animal().go(1)

def test_dog():
    assert animal.Dog().go(1) == "woof! "