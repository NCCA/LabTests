#!/bin/bash
export RMANTREE=/opt/pixar/RenderManProServer-21.4/
export RMAN_SHADERPATH=$HOME/Shaders:$RMANTREE/lib/shaders
export PYTHONPATH=$PYTHONPATH:$RMANTREE/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/$RMANTREE/lib:
export PATH=$PATH:/$RMANTREE/bin
./rgb.py ; render rgb.rib ; 
