#include <stdio.h>
#include <stdlib.h>

char matrix[64][64];
int main(void) {
	int p = 0;
	while (scanf(" %s", matrix[p++]) == 1);
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout_rgb)\n\t(:objects");
	
    for (int i = 0; i < p-1; i++)
			fprintf(problem, " l%d", i);
	fprintf(problem, " - line ");	
	
    for (int i = 0; i < p-1; i++)
		fprintf(problem, " c%d",i);
	fprintf(problem, " - column)\n\t(:init\n");	
	for (int i = 0; i < p; i++)
		for (int ii = 1; matrix[i][ii] != '\0'; ii += 2){
            // colors
            if (matrix[i][ii] == 'R')
                fprintf(problem, "\t\t(is_red l%d c%d)\n", i, ii/2);
            else if (matrix[i][ii] == 'B')
                fprintf(problem, "\t\t(is_blue l%d c%d)\n", i, ii/2);
            else if (matrix[i][ii] == 'G')
                fprintf(problem, "\t\t(is_green l%d c%d)\n", i, ii/2);
            else 
                fprintf(problem, "\t\t(is_off l%d c%d)\n", i, ii/2);

            // button type
            if(matrix[i][ii-1] == '-')
                fprintf(problem, "\t\t(is_default l%d c%d)\n", i, ii/2);
            else if(matrix[i][ii-1] == '*')
                fprintf(problem, "\t\t(is_edge l%d c%d)\n", i, ii/2);
            else if(matrix[i][ii-1] == '_')
                fprintf(problem, "\t\t(is_hbroken l%d c%d)\n", i, ii/2);
            else if(matrix[i][ii-1] == '|')
                fprintf(problem, "\t\t(is_vbroken l%d c%d)\n", i, ii/2);
            else 
                fprintf(problem, "\t\t(is_edgebroken l%d c%d)\n", i, ii/2);
        }
/*	for (int i = 0; i < p; i++)
		for (int ii = 0; matrix[i][ii] != '\0'; ii++) {
			if (matrix[i][ii+1] != 0) fprintf(problem, "\t\t(adj c%d-%d c%d-%d)\n", i, ii, i, ii+1);
			if (matrix[i+1][ii] != 0) fprintf(problem, "\t\t(adj c%d-%d c%d-%d)\n", i, ii, i+1, ii);
		}*/
	fprintf(problem, "\t)\n\t(:goal "
                                "(forall (?l - line)\n"
                                    "\t\t(forall (?c - column) "
                                        "(is_off ?l ?c)))\n");
	//for (int i = 0; i < p; i++)
	//	for (int ii = 0; matrix[i][ii] != '\0'; ii+=2)
	//		fprintf(problem, " (is_off l%d c%d)", i, ii-1);
	fprintf(problem, ")\n");
	fprintf(domain, "(define (domain lightsout)\n"
					"	(:types cell)\n"
					"	(:predicates\n"
					"		(on ?c - cell)\n"
					"		(adj ?c0 ?c1 - cell))\n"
					"	(:action CLICK\n"
					"		:parameters (?c - cell)\n"
					"		:precondition (and)\n"
					"		:effect (and\n"
					"			(when (on ?c) (not (on ?c)))\n"
					"			(when (not (on ?c)) (on ?c))\n"
					"			(forall (?w - cell)\n"
					"				(when (or (adj ?c ?w) (adj ?w ?c))\n"
					"					(and (when (on ?w) (not (on ?w)))\n"
					"					(when (not (on ?w)) (on ?w))))))))");
	fclose(domain), fclose(problem);
    //system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl");
	return 0;
}
