#!/usr/bin/env python
import os
import time
from subprocess import check_call, STDOUT

def compute_avg(ls):
  sum = 0
  n = 0
  for e in ls:
    sum = sum + e
    n = n + 1
  if n == 0:
    return 0
  else:
    return sum / n

NUM_ITER=10
cint_profile_commands = {}
cur_cp = ""
profile_cmds = open('profile_cmds', 'r')
for line in profile_cmds:
  if line[:2] == "  ":
    ls = line.split(':')
    c = ls[0].strip()
    opt = ls[1].strip()
    cmd = ls[2].strip()
    cint_profile_commands[cur_cp].append((c, opt, cmd))
  else:
    cur_cp = line.strip()
    cint_profile_commands[cur_cp] = []
profile_cmds.close()

DEVNULL = open(os.devnull, 'wb', 0)

for cp,commands in cint_profile_commands.items():
  for c,opt,command in commands:
    cmd = command[1:len(command)-1]
    #print "running " + cmd
    elapsed = []
    for i in range(NUM_ITER):
      start = time.time()
      try:
        check_call([cmd], stdout=DEVNULL, stderr=STDOUT)
      except:
        print "Call to " + cmd + " failed. ignoring"
      end = time.time()
      elapsed.append(end - start)
    avg = compute_avg(elapsed)
    minimum = min(elapsed)
    maximum = max(elapsed)
    if len(c) == 3:
      c = c + "  "
    print(cp + " : " + c + " : " + opt + " : " + "{:.3f} avg {:.3f} max {:.3f} min".format(avg, maximum, minimum))


