#!/usr/bin/env python
import unittest
import importlib

def testImport(module) :
    try:
        #import module as test
        importlib.import_module(module)
	return True
    except ImportError:
        return False


class MyTest(unittest.TestCase):
    def testOpenColorIO(self):
        self.assertTrue(testImport('PyOpenColorIO'))
    def testNumpy(self) :
	self.assertTrue(testImport('numpy'))
	self.assertTrue(testImport('scipy'))

if __name__ == '__main__':
    unittest.main()
