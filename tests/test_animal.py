import pytest

from fseg import animal

@pytest.mark.xfail(reason="Animal is an interface class")
def test_animal():
    animal.go("CAT", 1)

def test_dog():
    assert animal.go("DOG", 1) == "woof! "