#!/bin/bash 
# install test procedures

args=$#

if test $args = "0"; then
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

$CVC instid.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test1 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log instid.plg

$CVC instpnd3.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test2 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log instpnd3.plg

$CVC aspike1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test3 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log aspike1.plg
$CVC +warn_canceled_e aspike1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test4 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log aspike1a.plg
$CVC +show_canceled_e aspike1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test5 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log aspike1b.plg
$CVC +show_canceled_e +pulse_e_style_ondetect aspike1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test6 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log aspike1c.plg
## -et (event tracing) does not print very much output when cvc used
## $CVC aspike1.v -et >/dev/null
$CVC aspike1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test7 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log aspike1d.plg

$CVC +warn_canceled_e -v JK_Q.v -v JK_QBAR.v udpjkff.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test8 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log udpjkff.plg

$CVC xx2bdel.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test9 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xx2bdel.plg
$CVC xx2bpth.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test10 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xx2bpth.plg
$CVC xx2bpth2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test11 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xx2bpth2.plg

$CVC c880.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test12 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log c880.plg

## compiler does not have interactive mode or support -i
## $CVC -i force01.inp force01.v >/dev/null
## ./rmlic.pl
## diff verilog.log force01.plg

$CVC smrd04.v -f smrd04.vc >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test13 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log smrd04.plg

$CVC gatenots.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test14 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log gatenots.plg

$CVC arms_sim.v armscnt.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test15 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log arms.plg

$CVC -f dfpsetd.vc >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test16 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log dfpsetd.plg

$CVC -f mipdnot1.vc >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test17 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log mipdnot1.plg

$CVC -f sdfia04.vc >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test18 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log sdfia04.plg

$CVC dffn.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test19 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log dffn.plg

$CVC xplipnd.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test20 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log xplipnd.plg

$CVC defsplt1.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test21 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log defsplt1.plg

## longer tests - remove to speed up installation test 

## next 3 tests are self comparing - they print messages only on errors 
$CVC 2901sim.v block.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test22 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log 2901block.plg

$CVC 2901sim.v alg.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test23 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log 2901alg.plg

$CVC gcdsim.v gcd.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test24 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log gcd.plg

$CVC cpurtl2.v >/dev/null
if test ! -f cvcsim
then
 echo "ERROR - compiling test25 -" 
 echo "Run 'checkcvc' from bin to check configuration"
 exit;
fi
./cvcsim >/dev/null
rm cvcsim
./rmlic.pl
diff verilog.log cpurtl2.plg

echo ">>>> Install test completed (this should be only message printed)."
echo " "
