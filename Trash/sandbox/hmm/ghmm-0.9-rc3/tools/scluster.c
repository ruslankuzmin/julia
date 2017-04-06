/*******************************************************************************
  author       : Bernhard Knab
  filename     : ghmm/tools/scluster.c
  created      : 2001-04-20 by Achim Gaedke from hmm/src/scluster.c
  $Id: scluster.c 2267 2009-04-24 15:01:58Z grunau $

Copyright (C) 1998-2005 Alexander Schliep
Copyright (C) 1998-2001 ZAIK/ZPR, Universitaet zu Koeln
Copyright (C) 2002-2005 Max-Planck-Institut fuer Molekulare Genetik, Berlin

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA




*******************************************************************************
Parts of the library are Copyright of Sun Microsystems, Inc.
and re distributed under following license

 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================


*******************************************************************************/

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#include <stdio.h>
#include <ghmm/mes.h>
#include <ghmm/rng.h>
#include <ghmm/scluster.h>

int main(int argc, char* argv[]) {
#define CUR_PROC "scluster_main"

#ifdef GHMM_OBSOLETE
  int exitcode = -1;

  ghmm_rng_init();

  if (argc == 5 || argc == 6) {
    if (argc == 6)
      GHMM_RNG_SET(RNG,atoi(argv[5]));
    else {
      /* random init */
      ghmm_rng_timeseed(RNG);
    }

    printf("Clustering Sequences with start partition\n");
    switch(atoi(argv[4])) {
    case 0: printf("SP_BEST (best model)\n"); break;
    case 1: printf("NO_SP (no start partition)\n"); break;
    case 2: printf("SP_KM (partition from k-means)\n"); break;
    case 3: printf("SP_ZUF (random start partition)\n"); break;
    default: printf("argv[4] %d not valid. must be in [0, 3]\n", atoi(argv[4]));
      return exitcode;
    }
    exitcode = ghmm_scluster_hmm(argv);
  }
  else {
    GHMM_LOG(LCONVERTED, "Insufficient arguments. \
       Usage: scluster [sequence file][model file][outfile][labels]<seed>\n"); 
  }
  /*------------------------------------------------------------------------*/
  ighmm_mes(MES_WIN, "\n(%2.2T): Program finished with exitcode %d.\n", exitcode );
  ighmm_mes_exit();
  return(exitcode);

#else  /* GHMM_OBSOLETE */
  fprintf (stderr, "cluster is obsolete. If you need it rebuild the GHMM with \"GHMM_OBSOLETE\".\n");
  return 0;
#endif /* GHMM_OBSOLETE */

# undef CUR_PROC
} /* main */