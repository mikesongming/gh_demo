import fseg
from fseg import _fseg as m


def test_main():
    assert m.__version__ == "0.1.0"
    assert fseg.add(1, 2) == 3
    assert fseg.substract(1, 2) == -1
