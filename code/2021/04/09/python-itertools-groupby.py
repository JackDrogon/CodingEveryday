#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools


def sortBy(score):
    if score > 80:
        return "A"
    elif score >= 60:
        return "B"
    else:
        return "C"


scores = [81, 82, 84, 76, 64, 78, 59, 44, 55, 89]
for m, n in itertools.groupby(scores, key=sortBy):
    print(m, list(n))
