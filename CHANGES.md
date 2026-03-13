# Changes made in this fork of CVC
## 15/03/2026
- update install receipe, don't install 64b version to `cvc` but to `cvc64`, this better lines up with cocotb makefile expectations

## 13/03/2026
- refactored the `makefile.cvc64` file 
	- used patterns rules to remove the need for manual receipe definitions
	- added automatic receipe dependancy determination using gcc `-MMD` 
	- moved build artifacts to the `build64` directory
- renamed `makedile.cvc64` to `Makefile` assuming most future users will run 64 bit systems by default
- fix compilation on modern gcc versions ( assessed to be broken based of gcc `15.2.1` behavior )
	- explicitly specify `c99` behavior, modern system default used a C version >= `c23` where K&R function pointer style is no longer supported
- fix syscall definition on modern systems
	- `clone` in particular now seem to be defined only behind `__USE_GNU` though `<sched.h>`
- added missing external defintion of `__add_dmpv_chglst_el_sel` in `cvmacros.h`
- update README to markdown, keeping license terms as per license aggreement
- adding install receipe
