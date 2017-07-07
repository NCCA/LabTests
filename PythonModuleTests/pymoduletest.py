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
    def testOIIO(self) :
	self.assertTrue(testImport('OpenImageIO'))

    def testOpenEXR(self) :
	self.assertTrue(testImport('OpenEXR'))
	self.assertTrue(testImport('Imath'))

    def testAlembic(self) :
	self.assertTrue(testImport('alembic'))
    
    def testPyQt(self) :
	self.assertTrue(testImport('PyQt5'))
if __name__ == '__main__':
    unittest.main()
