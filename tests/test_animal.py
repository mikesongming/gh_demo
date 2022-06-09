import pytest

from fseg import animal

def test_animal():
    with pytest.raises(RuntimeError):
        animal.Animal().go(1)

def test_dog():
    assert animal.Dog().go(2) == "woof! "