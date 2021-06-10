#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
#---------------------------------------------------------------------------------------------------

import sys, os, subprocess

#---------------------------------------------------------------------------------------------------

def RED () :
  return '\033[91m'

#---------------------------------------------------------------------------------------------------

def ENDC () :
  return '\033[0m'

#---------------------------------------------------------------------------------------------------

def BOLD () :
  return '\033[1m'

#---------------------------------------------------------------------------------------------------

#--- Get script absolute path
scriptDir = os.path.dirname (os.path.abspath (sys.argv [0]))
os.chdir (scriptDir)
#---
toolDir = os.path.expanduser ("~/Library/Arduino15/packages/rp2040/tools/pqt-pioasm")
found = False
for aDir in sorted (os.listdir (toolDir)) :
  pioasmTool = (toolDir + "/" + aDir + "/pioasm")
  if os.path.exists (pioasmTool) :
    found = True
    #--- charlieplexing5
    returncode = subprocess.call ([pioasmTool, "charlieplexing5.pioasm", "pio-charlieplexing5.h"])
    if returncode != 0 :
      sys.exit (returncode)
    #--- charlieplexing6
    returncode = subprocess.call ([pioasmTool, "charlieplexing6.pioasm", "pio-charlieplexing6.h"])
    if returncode != 0 :
      sys.exit (returncode)
if not found :
  print (RED () + BOLD () + "Cannot find pioasm" + ENDC ())

#---------------------------------------------------------------------------------------------------
