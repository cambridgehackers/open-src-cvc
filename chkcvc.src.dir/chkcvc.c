
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int check_cvc_linking(void);
static int assemble_file(int);
static void print_error(char *);

/*
 * test a user configuration to ensure correct CVC compilation/running
 */
int main(int argc, char **argv)
{
 int rval;

 rval = check_cvc_linking();
 if (rval == 0)
  {
   fprintf(stdout, "System configuration is fine for CVC compilation.\n");
  }
 else 
  {
   fprintf(stdout, "System configuration must be changed for CVC compilation.\n");
   fprintf(stdout, "Please contact Pragmatic C Software with the output created from this run\n");
  }
 unlink("/tmp/t1.o");
 unlink("/tmp/t2.o");
 return(rval);
}
   
/*
 * assemble an object file in tmp
 */
static int assemble_file(int fnum)
{
 FILE *pp, *fp;
 char as_cmd[1024], fname[1024];

 /* make sure tmp is readable */
 sprintf(fname, "/tmp/t%d.s", fnum);
 if ((fp = fopen(fname, "w")) == NULL)
  {
   print_error("Unable to open /tmp/ file for read/write");
   print_error("/tmp/ directory must be able to read/write");
   return(1);
  } 
 fclose(fp);

#ifdef __X86_64__
 sprintf(as_cmd, "as --32 -o /tmp/t%d.o", fnum);
#else
 sprintf(as_cmd, "as -o /tmp/t%d.o", fnum);
#endif
 if ((pp = popen(as_cmd, "w")) == NULL)
  {
   print_error("Unable to locate GNU assembler");
   return(1);
  } 
  
 /* pipe some generic assebmly */
 fprintf(pp, ".globl ST_ENT.0_%d\n\t.type  ST_ENT.0_%d, @function\nST_ENT.0_%d:\n\t movl	$0x1, N_0_%d\n\t movl	$0, N_0_%d + 4\n\t ret\n\t", fnum,
 fnum, fnum, fnum, fnum);
 fprintf(pp, "\n\t.section\t.rodata\n\t .comm	N_0_%d, 8, 4\n", fnum);
 pclose(pp);
 return(0);
}

/*
 * create two object file in /tmp/, link to *.so dynamic library and load lib
 * return 0 if success
 */
static int check_cvc_linking(void)
{
 FILE *pp;
 void *solib, *symadr;
 char cmd[1024], soname[1024], s1[1024];

 /* create two object files in tmp */
 if (assemble_file(1)) return(1);
 if (assemble_file(2)) return(1);

 /* AIV 07/09/07 - removed -lm linking of math library isn't needed */
 /* and was causing problems for 64 bit linking of our 32-bit assembly */
#ifdef __X86_64__
 /* linker flags */
 strcpy(s1, "-G -shared -export-dynamic -melf_i386 -L/usr/lib/");
#else
 strcpy(s1, "-G -shared -export-dynamic");
#endif

 /* create *.so file */
 strcpy(soname, "/tmp/cvc.so");
 sprintf(cmd, "ld %s -o %s /tmp/t1.o /tmp/t2.o", s1, soname);
 if ((pp = popen(cmd, "w")) == NULL)
  {
   print_error("Unable to locate GNU linker (ld)");
   return(1);
  }
 pclose(pp);

 /* load .so file */
 if ((solib = dlopen(soname, RTLD_LAZY | RTLD_GLOBAL)) == NULL)
  {
   sprintf(s1, "Unable to open dynamic library from /tmp/ because: %s",
     dlerror());
   print_error(s1);
   return(1);
  }

 /* attempt to link an symbol from the loaded library */
 if ((symadr = dlsym(solib, "N_0_1")) == NULL)
  {
   sprintf(s1, "Unable to link dlsym because: %s\n", dlerror());
   print_error(s1);
   return(1);
  }
 return(0);
}

/*
 * print error message
 */
static void print_error(char *msg)
{
 fprintf(stderr, "%s\n", msg);
}
