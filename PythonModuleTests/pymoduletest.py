#!/usr/bin/env python
import unittest

def testImport(module) :
    try:
        importlib.import_module(modu
        return True
    except ImportError:
        return False


class MyTest(unittest.TestCase):
    def testOpenColorIO(self):
        self.assertTrue(testImport('PyOpenColorIO'))


if __name__ == '__main__':
    unittest.main()