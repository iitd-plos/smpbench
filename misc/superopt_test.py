import multiprocessing
import sys
import os
import time
from subprocess import check_call, STDOUT

execfile("../smpbench-build/config.py")
superopt_dir = os.path.abspath(srcdir + "/../superopt")
lli = "lli-3.4"
llvm2tfg_build_dir = os.path.abspath(srcdir + "/../llvm-build")

color_red="`tput bold; tput setaf 1`"
color_green="`tput bold; tput setaf 2`"
color_reset="`tput sgr0`"
#opts = ["O0", "O3"]
#compilers = ["gcc", "clang", "llc", "icc"]
opts = ["O3"]
compilers = ["llc"]

#num_cpus = multiprocessing.cpu_count()
cint_progs = []
cint_profile_commands = {}

for arg in sys.argv:
  cint_progs.append(arg)
cint_progs.pop(0)

#print("num_cpus = ", num_cpus)
for cp in cint_progs:
  name = os.path.basename(cp)
  if name == "ctests":
    continue
  cint_prog = os.path.abspath(build + "/" + cp)
  #print(cint_prog)
  cmd = "/bin/true && (/bin/true"
  for opt in opts:
    cmd = cmd + " && ("
    cmd = cmd + llvm2tfg_build_dir + "/bin/llvm2tfg " + cint_prog + ".bc." + opt + " -o " + cint_prog + ".bc." + opt + ".etfg";
    cmd = cmd + " && " + "rm -f " + cint_prog + ".bc." + opt + ".i386";
    cmd = cmd + " && " + superopt_dir + "/build/etfg_i386/codegen " + cint_prog + ".bc." + opt + ".etfg -o " + cint_prog + ".bc." + opt + ".i386" + " -l " + cint_prog + ".bc." + opt + ".rewrite.log";
    cmd = cmd + ")"
  cmd = cmd + ")"
  cmd = cmd + " && " + "(perl " + srcdir + "/misc/compare_commands.pl " + name
  ccmd = ""
  cint_profile_commands[cp] = []
  for c in compilers:
    for opt in opts:
      ccmdo = "\"" + cint_prog + "." + c + "." + opt + ".i386\""
      ccmd = ccmd + " " + ccmdo
      cint_profile_commands[cp].append((c,opt,ccmdo))
  for opt in opts:
    ccmdo = "\"" + cint_prog + ".bc." + opt + ".i386\""
    ccmd = ccmd + " " + ccmdo
    cint_profile_commands[cp].append(("scg",opt,ccmdo))
  ccmd = ccmd + " \"\""
  cmd = cmd + ccmd + " && echo \"" + cint_prog  + " " + color_green + "passed" + color_reset + "\") || echo \"" + cint_prog + " " + color_red + "FAILED" + color_reset + "\""
  print cmd + "\n"

#DEVNULL = open(os.devnull, 'wb', 0)
profile_cmds = open("profile_cmds", 'w+')
for cp,commands in cint_profile_commands.items():
  profile_cmds.write(cp + "\n")
  for c,opt,command in commands:
    profile_cmds.write("  " + c + " : " + opt + " : " + command + "\n")
  #start = time.time()
  #check_call([command], stdout=DEVNULL, stderr=STDOUT)
  #print(command + ": ")
  #print("{:.3f} seconds".format(time.time() - start))
profile_cmds.close()
