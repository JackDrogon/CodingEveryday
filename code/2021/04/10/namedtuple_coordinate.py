#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import namedtuple

Coordinate = namedtuple('Coordinate', 'lat long')

print(issubclass(Coordinate, tuple))

moscow = Coordinate(55.756, 37.617)
print(moscow)

print(moscow == Coordinate(lat=55.756, long=37.617))
