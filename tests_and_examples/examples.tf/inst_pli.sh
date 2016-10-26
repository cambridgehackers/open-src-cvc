#!/bin/sh 
# install test procedures

# pass name for your OS as argument to shell script

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

make -f makefile.$OS probe.so
$CVC +acc+2 -q +loadpli1=./probe:pli1_compat_bootstrap probe.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test1" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log probe.plg
rm probe.so probe.o

make -f makefile.$OS tfclk.so
$CVC +acc+1 -q tfclk.v +loadpli1=./tfclk:pli1_compat_bootstrap >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test2" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log tfclk.plg
rm tfclk.so tfclk.o

make -f makefile.$OS plimfil.so
$CVC +acc+1 +memfile+testmem.dat -q +loadpli1=./plimfil:pli1_compat_bootstrap plimfil.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test3" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log plimfil.plg
rm plimfil.so plimfil.o

make -f makefile.$OS plimfil2.so
$CVC +acc+1 +memfile+testmem2.dat -q +loadpli1=./plimfil2:pli1_compat_bootstrap plimfil2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test4" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >&/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log plimfil2.plg
rm plimfil2.so plimfil2.o

echo ">>>> PLI 1.0 test finished - no diff differences should be printed."
echo " "
