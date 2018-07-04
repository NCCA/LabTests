#!/usr/bin/env python
import unittest
import importlib

tests = [
        ['OpenColorIO import test','PyOpenColorIO'],
        ['Numpy import test','numpy'],
        ['SciPy import test','scipy'],
        ['SciPy lin algebra import test','scipy.misc'],
	['Alembic import test','alembic'],
        ['OpenEXR import test','OpenEXR'],    
        ['OpenImageIO import test','OpenImageIO'],
        ['PyQt5 import test','PyQt5'],
	['MaterialX import test','MaterialX'],
	['Python OpenGL import test','OpenGL.GL'],
	['OpenGL Glut import test','OpenGL.GLUT'],
	['OpenGL GLU import test','OpenGL.GLU'],
	['SDL2 import test','sdl2'],
	['GLFW3 import test','glfw'],
    

       
 ]

def testImport(module) :
    try:
        #import module as test
        importlib.import_module(module)
	return True
    except ImportError:
        return False


""" see discussion here for this idea of auto unit tests
https://stackoverflow.com/questions/32899/how-to-generate-dynamic-parametrized-unit-tests-in-python

"""

class TestSequence(unittest.TestCase):
    pass

def testGenerator(a):
    def test(self):
        self.assertTrue(testImport(a))
    return test

if __name__ == '__main__':
    for t in tests:
        testName = 'test_%s' % t[0]
        test = testGenerator(t[1])
        setattr(TestSequence, testName, test)
    unittest.main()

