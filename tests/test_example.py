from example_package import add_one, time_two, half, square
import pytest

def test_add_one():
    assert add_one(3) == 4

def test_time_two():
    assert time_two(3) == 6

def test_half():
    assert half(2) == 1

def test_division_zero():
    with pytest.raises(ZeroDivisionError):
        1/0

def test_sqaure():
    assert square(3) == 9
