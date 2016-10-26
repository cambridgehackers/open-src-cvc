/////////////////////////////////////////////////////////////////////
////                                                             ////
//// Copyright (C) 2004 to Wilson Snyder
////                       wsnyder@wsnyder.org
////                                                             ////
//// This source file may be used and distributed without        ////
//// restriction provided that this copyright statement is not   ////
//// removed from the file and that any derivative work contains ////
//// the original copyright notice and the associated disclaimer.////
////                                                             ////
////     THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY     ////
//// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   ////
//// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS   ////
//// FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR      ////
//// OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,         ////
//// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    ////
//// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE   ////
//// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR        ////
//// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  ////
//// LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT  ////
//// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  ////
//// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE         ////
//// POSSIBILITY OF SUCH DAMAGE.                                 ////
////                                                             ////
/////////////////////////////////////////////////////////////////////

#include <verilated.h>
#include <fstream>
#include <iomanip>
#include <sys/times.h>
using namespace std;

#include "m68.h"

m68 *top;

unsigned int main_time = 0;

double sc_time_stamp () {
    return main_time;
}

double cpuTime() {
    struct tms tm;
    times (&tm);
    return ((tm.tms_utime + tm.tms_stime + tm.tms_cutime + tm.tms_cstime + 1)
	/ 100.0);
}

int main(int argc, char **argv, char **env) {
    Verilated::debug(0);	// We compiled with it on for testing, turn it back off

    top = new m68;
    top->clk = 1;
    top->arbclk_i = 1;
    top->rst = 0;

    // Main loop
    int CYCLES = 10000000;
    double cpuStart = -1;
    if (argc>1) CYCLES = atoi(argv[1]);
    bool rstDone = false;
    while (main_time < 40+ (CYCLES * 10)) {
	if (main_time >= 40 && !rstDone) {
	    cpuStart = cpuTime();
	    rstDone = true;
	    top->rst = 1;
	}
	top->eval();
	main_time++;
	top->arbclk_i = !top->arbclk_i;
	if (main_time%5 == 0) top->clk = !top->clk;
    }

    double cpuEnd = cpuTime();
    cout<<"Test Complete, "<<fixed<<setprecision(2)
	<<(cpuEnd-cpuStart)<<" cpu sec, "
	<<fixed<<setprecision(0)
	<<(CYCLES/(cpuEnd-cpuStart))<<" cyc/sec\n";

    exit(0L);
}
