import fseg

def test_version():
    assert fseg._fseg.__version__ == "0.1.0"

def test_add_1args():
    assert fseg.add(1) == 2

def test_add_2args():
    assert fseg.add(1, 2) == 3

def test_substract():
    assert fseg.substract(1, 2) == -1

def test_attr():
    assert fseg._fseg.the_answer == 42
    assert fseg._fseg.what == "World"