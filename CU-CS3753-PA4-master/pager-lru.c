/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for an LRU pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp;
    int pagetmp;
    int proc;
    int pc;
    int page;
    int oldpage;
    int min;
    int minPage;
    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
		timestamps[proctmp][pagetmp] = 0; 
	    }
	}
	initialized = 1;
    }
    
    /* TODO: Implement LRU Paging */
    //fprintf(stderr, "pager-lru not yet implemented. Exiting...\n");
    //exit(EXIT_FAILURE);
    for(proc=0; proc<MAXPROCESSES; proc++) { 
    /* Is process active? */
    if(q[proc].active) {
        /* Dedicate all work to first active process*/ 
        pc = q[proc].pc;                // program counter for process
        page = pc/PAGESIZE;         // page the program counter needs
        timestamps[proc][page]=tick;
        /* Is page swaped-out? */
        if(!q[proc].pages[page]) {
        /* Try to swap in */
        if(!pagein(proc,page)) {
            min=tick+1;
            /* If swapping fails, swap out another page */
            for(oldpage=0; oldpage < q[proc].npages; oldpage++) {
            /* Make sure page isn't one I want */
                if(q[proc].pages[oldpage]==1 && q[proc].pages[oldpage]!=0){
                    if(timestamps[proc][oldpage]<min){
                        min=timestamps[proc][oldpage];
                        minPage=oldpage;
                    }
                    if(min<=1){
                        break;
                    }
                    if(pageout(proc,minPage)) {
                    /* Break loop once swap-out starts*/
                        break;
                    } 
                }
                
            }
        }
        }
        /* Break loop after finding first active process */
        //break;
    }
    } 

    /* advance time for next pageit iteration */
    tick++;
} 
