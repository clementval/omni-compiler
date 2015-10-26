static char rcsid[] = "";
/* 
 * $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
 * $TSUKUBA_Copyright:
 *  Copyright (C) 2010-2014 University of Tsukuba, 
 *  	      2012-2014  University of Tsukuba and Riken AICS
 *  
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 published by the Free Software Foundation.
 *  
 *  Please check the Copyright and License information in the files named
 *  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
 *  Software release kit.
 *  
 *  * The specification of XcalableMP has been designed by the XcalableMP
 *    Specification Working Group (http://www.xcalablemp.org/).
 *  
 *  * The development of this software was partially supported by "Seamless and
 *    Highly-productive Parallel Programming Environment for
 *    High-performance computing" project funded by Ministry of Education,
 *    Culture, Sports, Science and Technology, Japan.
 *  $
 */
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "omni.h"


extern char	*optarg;
extern int	optind;


#if defined(__OMNI_SCASH__) || defined(__OMNI_SHMEM__)
#pragma omp threadprivate(optind,optarg)
#endif


usage (name)
     char *name;
{
  char *cmd;

  cmd = strrchr (name, '/');
  if (cmd == NULL) {
    cmd = name;
  } else {
    cmd += 1;
  }

  printf ("%s : [options]\n", cmd);
  printf ("--------------\n");
  printf ("-i : set thread number, exit function called by this thread.\n");
  printf ("-c : set exit code\n");
  printf ("-h : this message.\n");

  exit (0);
}


int
main (argc, argv)
     int	argc;
     char	*argv[];
{

  int	eid = 0;
  int	ec  = 0;
  int	c;

  while ((c = getopt (argc, argv, "i:c:h")) != EOF) {
    switch (c) {
    case 'i':
      eid = atoi(optarg);
      break;
    case 'c':
      ec = atoi(optarg);
      break;
    case 'h':
    default:
      usage(argv[0]);
      break;
    }
  }

  #pragma omp parallel 
  {
    if (omp_get_thread_num () == eid) {
      exit (ec);
    }
  }

  return 0;
}
