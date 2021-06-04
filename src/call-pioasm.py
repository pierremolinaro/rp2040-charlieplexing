#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
#---------------------------------------------------------------------------------------------------

import sys, os, subprocess

#---------------------------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#---
pioasmTool = os.path.expanduser ("~/Library/Arduino15/packages/rp2040/tools/pqt-pioasm/1.1.0-a-81a1771/pioasm")
#--- charlieplexing5
returncode = subprocess.call ([pioasmTool, "charlieplexing5.pioasm", "pio-charlieplexing5.h"])
if returncode != 0 :
  sys.exit (returncode)
#--- charlieplexing6
returncode = subprocess.call ([pioasmTool, "charlieplexing6.pioasm", "pio-charlieplexing6.h"])
if returncode != 0 :
  sys.exit (returncode)

#---------------------------------------------------------------------------------------------------
