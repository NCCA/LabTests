#!/usr/bin/env python

def testImport(module,message) :
try:
    import PyOpenColorIO as test
except ImportError:
    raise ImportError()
