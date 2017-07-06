#!/usr/bin/env python
import unittest

def testImport(module) :
    try:
        import module as test
        return True
    except ImportError:
        return False


class MyTest(unittest.TestCase):
    def testOpenColorIO(self):
        self.assertTrue(testImport('PyOpenColorIO'))


if __name__ == '__main__':
    unittest.main()