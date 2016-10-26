#!/bin/bash 
# install test procedures

args=$#

if test $args = "0"; then
  if which cvc >& /dev/null; then
    CVC="cvc +interp -q"
  elif test -f /tmp/cvc; then
    CVC="/tmp/cvc +interp -q"
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
    CVC="cvc64 +interp -q"
  elif test -f /tmp/cvc64; then
    CVC="/tmp/cvc64 +interp -q"
  else
   echo "ERROR - there is no cvc on PATH or in /tmp"
   exit 1
  fi
  fi
fi

# removeme

$CVC instid.v >/dev/null
./rmlic.pl
if test $args != "0"; then
  diff verilog.log instid.plg64
 else
  diff verilog.log instid.plg
fi

$CVC +suppress_warns+602+ instpnd3.v >/dev/null
./rmlic.pl
diff verilog.log instpnd3.plg

$CVC aspike1.v >/dev/null
./rmlic.pl
diff verilog.log aspike1.plg

$CVC +warn_canceled_e aspike1.v >/dev/null
./rmlic.pl
diff verilog.log aspike1a.plg

$CVC +show_canceled_e aspike1.v >/dev/null
./rmlic.pl
diff verilog.log aspike1b.plg

$CVC +show_canceled_e +pulse_e_style_ondetect aspike1.v >/dev/null
./rmlic.pl
diff verilog.log aspike1c.plg

## -et (event tracing) does not print very much output when cvc used
## $CVC aspike1.v -et >/dev/null
$CVC aspike1.v >/dev/null
./rmlic.pl
diff verilog.log aspike1d.plg

$CVC +warn_canceled_e -v JK_Q.v -v JK_QBAR.v udpjkff.v >/dev/null
./rmlic.pl
diff verilog.log udpjkff.plg

$CVC xx2bdel.v >/dev/null
./rmlic.pl
diff verilog.log xx2bdel.plg

$CVC xx2bpth.v >/dev/null
./rmlic.pl
diff verilog.log xx2bpth.plg

$CVC xx2bpth2.v >/dev/null
./rmlic.pl
diff verilog.log xx2bpth2.plg

$CVC c880.v >/dev/null
./rmlic.pl
diff verilog.log c880.plg

## compiler does not have interactive mode or support -i
$CVC -i force01.inp force01.v >/dev/null
./rmlic.pl
diff verilog.log force01.plg

$CVC smrd04.v -f smrd04.vc >/dev/null
./rmlic.pl
diff verilog.log smrd04.plg

$CVC gatenots.v >/dev/null
./rmlic.pl
diff verilog.log gatenots.plg

$CVC arms_sim.v armscnt.v >/dev/null
./rmlic.pl
diff verilog.log arms.plg

$CVC -f dfpsetd.vc >/dev/null
./rmlic.pl
diff verilog.log dfpsetd.plg

$CVC -f mipdnot1.vc >/dev/null
./rmlic.pl
diff verilog.log mipdnot1.plg

$CVC +change_port_type -f sdfia04.vc >/dev/null
./rmlic.pl
diff verilog.log sdfia04.plg

$CVC dffn.v >/dev/null
./rmlic.pl
diff verilog.log dffn.plg

$CVC xplipnd.v >/dev/null
./rmlic.pl
if test $args != "0"; then
  diff verilog.log xplipnd.plg64
 else
  diff verilog.log xplipnd.plg
fi

$CVC defsplt1.v >/dev/null
./rmlic.pl
diff verilog.log defsplt1.plg

## longer tests - remove to speed up installation test 

## next 3 tests are self comparing - they print messages only on errors 
$CVC +suppress_warns+530+ 2901sim.v block.v >/dev/null
./rmlic.pl
diff verilog.log 2901block.plg

$CVC 2901sim.v alg.v >/dev/null
./rmlic.pl
diff verilog.log 2901alg.plg

$CVC gcdsim.v gcd.v >/dev/null
./rmlic.pl
diff verilog.log gcd.plg

$CVC cpurtl2.v >/dev/null
./rmlic.pl
diff verilog.log cpurtl2.plg

echo ">>>> Install +interp test completed (this should be only message printed)."
echo " "
