#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char matrix[64][64];
int main(void) {
	int p = 0;
	while (scanf(" %s", matrix[p++]) == 1);
	FILE *problem = fopen("problem.pddl", "w");//, *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout_rgb)\n\t(:objects");
    //for (int i = 0; i < p-1; i++){
	//	fprintf(problem, " l%d", i);
	//}
	//fprintf(problem, " - line");
	
	int max_column_size = 0;
    for (int i = 0; i < p || matrix[i][0] != 0; i++){
		int isize = strlen(matrix[i])/2;
		if(isize > max_column_size) max_column_size = isize;
	}
	//for(int i = 0 ; i < max_column_size; i++) fprintf(problem, " cl%d", i);
	//fprintf(problem, " - column");

    for (int i = 0; i < p || matrix[i][0] != 0; i++)
		for(int j = 0, m = 0; matrix[i][j] != '\0' ; j+=2)
			fprintf(problem, " c%d-%d", i, m++);
	fprintf(problem, " - cell)\n\t(:init\n");	
	for (int i = 0; i < p; i++)
		for(int ii  = 1, m = 0; matrix[i][ii] != '\0' ; ii+=2, m++){
            if (matrix[i][ii] == 'R')
                fprintf(problem, "\t\t(is_red c%d-%d)\n", i, m);
            else if (matrix[i][ii] == 'B')
                fprintf(problem, "\t\t(is_blue c%d-%d)\n", i, m);
            else if (matrix[i][ii] == 'G')
                fprintf(problem, "\t\t(is_green c%d-%d)\n", i, m);
            else 
                fprintf(problem, "\t\t(is_off c%d-%d)\n", i, m);

            if(matrix[i][ii-1] == '-')
                fprintf(problem, "\t\t(is_default c%d-%d)\n", i, m);
            else if(matrix[i][ii-1] == '*')
                fprintf(problem, "\t\t(is_edge c%d-%d)\n", i, m);
            else if(matrix[i][ii-1] == '_')
                fprintf(problem, "\t\t(is_vbroken c%d-%d)\n", i, m);
            else if(matrix[i][ii-1] == '|')
                fprintf(problem, "\t\t(is_hbroken c%d-%d)\n", i, m);
            else 
                fprintf(problem, "\t\t(is_edgebroken c%d-%d)\n", i, m);

			// same line
			for(int j  = 1, n = 0; matrix[i][j] != '\0' ; j+=2, n++)
		        fprintf(problem, "\t\t(same_line c%d-%d c%d-%d)\n", i, m, i, n);
			for(int j = 0 ; j < max_column_size; j++)
				if(matrix[j][m] != 0)
	        		fprintf(problem, "\t\t(same_column c%d-%d c%d-%d)\n", i, m, j, m);
        	fprintf(problem, "\n");
		} 
	fprintf(problem, "\t)\n\t(:goal (and \n ");
	for (int i = 0; i < p; i++)
		for(int j = 0, m = 0; matrix[i][j] != '\0' ; j+=2)
        	fprintf(problem, "\t\t(is_off c%d-%d)\n", i, m++);
	fprintf(problem, ")))\n");
	//fprintf(domain, "(define (domain lightsout_rgb) (:types line column - object) (:predicates(is_off ?l - line ?c - column)(is_red ?l - line ?c - column)(is_blue ?l - line ?c - column)(is_green ?l - line ?c - column)(is_default ?l - line ?c - column)(is_edge ?l - line ?c - column)(is_edgebroken ?l - line ?c - column)(is_hbroken ?l - line ?c - column)(is_vbroken ?l - line ?c - column)(next_h ?l1 ?l2 - line)(next_v ?c1 ?c2 - column))(:action click_default:parameters(?l - line ?c - column):precondition(and(is_default ?l ?c)):effect(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))(forall(?h - column)(when(and(not(is_hbroken ?l ?h))(not(is_edgebroken ?l ?h)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))))(forall(?v - line)(when(and(not(is_vbroken ?v ?c))(not(is_edgebroken ?v ?c)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c))))))(:action click_edge:parameters(?l - line ?c - column):precondition(and(is_edge ?l ?c)):effect(and(forall(?h - column)(when(and(not(is_hbroken ?l ?h))(not(is_edgebroken ?l ?h)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))))(forall(?v - line)(when(and(not(is_vbroken ?v ?c))(not(is_edgebroken ?v ?c)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c))))))))))");
	//fclose(domain), 
	fclose(problem);
	//printf("MADAGASCAR...\n");
    //system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl > madagascar.plan");
	//printf("DOWNWARD...\n");
    //system("/home/software/planners/downward/fast-downward.py --alias lama domain.pddl problem.pddl");
	return 0;
}
