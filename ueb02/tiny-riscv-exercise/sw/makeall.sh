#!/bin/bash

for d in */ ; do
    make -C $d
done

