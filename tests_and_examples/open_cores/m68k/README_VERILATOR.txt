This example was used to generate

http://www.veripool.com/verilog_sim_benchmarks.html

The code herein was from http://www.opencores.org

To run the benchmarks

cd sim
make (simulator-name)

You'll need to do several runs to avoid startup effects, and run another
test with 0 simulation cycles so you can subtract off initialization
effects.


