from example_package import add_one, time_two

def test_add_one():
    assert add_one(3) == 4

def test_time_two():
    assert time_two(3) == 6
