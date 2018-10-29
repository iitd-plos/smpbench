import multiprocessing
import sys
import os

execfile("../smpbench-build/config.py")
superopt_dir = os.path.abspath(srcdir + "/../superopt")
lli = "lli-3.4"
llvm2tfg_build_dir = os.path.abspath(srcdir + "/../llvm2tfg-build")

color_red="`tput bold; tput setaf 1`"
color_green="`tput bold; tput setaf 2`"
color_reset="`tput sgr0`"
opts = ["O0", "O2", "O3"]
#opts = ["O0"]

#num_cpus = multiprocessing.cpu_count()
cint_progs = []

for arg in sys.argv:
  cint_progs.append(arg)
cint_progs.pop(0)

#print("num_cpus = ", num_cpus)
for cp in cint_progs:
  name = os.path.basename(cp)
  cint_prog = os.path.abspath(build + "/" + cp)
  #print(cint_prog)
  cmd = "/bin/true && (/bin/true"
  for opt in opts:
    cmd = cmd + " && ("
    cmd = cmd + llvm2tfg_build_dir + "/bin/llvm2tfg " + cint_prog + ".bc." + opt + " -o " + cint_prog + ".bc." + opt + ".etfg";
    cmd = cmd + " && " + "rm -f " + cint_prog + ".bc." + opt + ".i386";
    cmd = cmd + " && " + superopt_dir + "/build/etfg_i386/codegen " + cint_prog + ".bc." + opt + ".etfg -o " + cint_prog + ".bc." + opt + ".i386";
    cmd = cmd + ")"
  cmd = cmd + ")"
  #cmd = cmd + " && " + "(perl " + srcdir + "/misc/compare_commands.pl " + name + " \"" + lli + " " + cint_prog + ".bc.O0\" \"" + cint_prog + ".gcc48.O3.i386\" \"" + cint_prog + ".bc.O0.i386\" \"\" && echo \"" + cint_prog  + " " + color_green + "passed" + color_reset + "\") || echo \"" + cint_prog + " " + color_red + "FAILED" + color_reset + "\""
  cmd = cmd + " && " + "(perl " + srcdir + "/misc/compare_commands.pl " + name
  for opt in opts:
    cmd = cmd + " \"" + cint_prog + ".gcc48." + opt + ".i386\""
  for opt in opts:
    cmd = cmd + " \"" + cint_prog + ".bc." + opt + ".i386\""
  cmd = cmd + " \"\" && echo \"" + cint_prog  + " " + color_green + "passed" + color_reset + "\") || echo \"" + cint_prog + " " + color_red + "FAILED" + color_reset + "\""
  print cmd + "\n"
