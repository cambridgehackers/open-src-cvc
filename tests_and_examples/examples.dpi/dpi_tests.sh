#!/bin/sh 
# install test procedures

args=$#

if test $args = "0"; then
  OS="lnx32"
  if which cvc >& /dev/null; then
    CVC="cvc -q"
  elif test -f /tmp/cvc; then
    CVC="/tmp/cvc -q"
  else
   echo "ERROR - there is no cvc on PATH or in /tmp"
   exit 1
  fi
else 
 if test $1 != "cvc64"; then 
   echo "ERROR - only option is 'cvc64' to run 64-bit otherwise leave empty for 32-bit CVC"
   exit 2
  else
  OS="lnx64"
  if which cvc64 >& /dev/null; then
    CVC="cvc64 -q"
  elif test -f /tmp/cvc64; then
    CVC="/tmp/cvc64 -q"
  else
   echo "ERROR - there is no cvc on PATH or in /tmp"
   exit 1
  fi
  fi
fi

make -f makefile.$OS twostate_tasks.so
$CVC -q -sv_lib twostate_tasks.so twostate_tasks.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test1" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log twostate_tasks.plg
rm twostate_tasks.so twostate_tasks.o

make -f makefile.$OS twostate_functions.so
$CVC -q -sv_lib twostate_functions.so twostate_functions.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test2" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log twostate_functions.plg
rm twostate_functions.so twostate_functions.o

make -f makefile.$OS fourstate.so
$CVC -q -sv_lib fourstate.so fourstate.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test3" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log fourstate.plg
rm fourstate.so fourstate.o

make -f makefile.$OS export.so
$CVC -q -sv_lib export.so export.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test4" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log export.plg
rm export.so export.o

make -f makefile.$OS fourstate_array.so
$CVC -q -sv_lib fourstate_array.so fourstate_array.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test5" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log fourstate_array.plg
rm fourstate_array.so fourstate_array.o

make -f makefile.$OS twostate_array.so
$CVC -q -sv_lib twostate_array.so twostate_array.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test6" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log twostate_array.plg
rm twostate_array.so twostate_array.o

make -f makefile.$OS reals.so
$CVC -q -sv_lib reals.so reals.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test7" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log reals.plg
rm reals.so reals.o

make -f makefile.$OS selects.so
$CVC -q -sv_lib selects.so selects.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test8" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log selects.plg
rm selects.so selects.o

make -f makefile.$OS chandle.so
$CVC -q -sv_lib chandle.so chandle.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test8" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log chandle.plg
rm chandle.so chandle.o

make -f makefile.$OS diffname.so
$CVC -q -sv_lib diffname.so diffname.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test8" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log diffname.plg
rm diffname.so diffname.o
