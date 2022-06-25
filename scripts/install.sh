#!/bin/bash

PYTHON=`which python`

$PYTHON -m pip install --upgrade pip

$PYTHON -m pip install build

$PYTHON -m build -w

$PYTHON -m pip install $(ls -t dist/*.whl | head -n 1)