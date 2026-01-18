#!/bin/bash

if [[ $1 =~ .+@.+\..+ ]] ; then
    echo "$1 is an email address"
else
    echo "$1 is not an email address"
fi
