#!/bin/bash

if ! command -v cpplint &> /dev/null
then
    echo "cpplint could not be found"
    echo "install cpplint"
    pip3 install cpplint
fi
