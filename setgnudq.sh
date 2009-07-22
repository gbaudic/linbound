#!/bin/sh

echo "LB 0.1 setup system for devel purposes\n"
aclocal
autoconf
automake -a

#It might be a great idea to let the user choose to produce the tarball or not
make distcheck
