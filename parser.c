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
            if (matrix[i][ii] == 'R')
                fprintf(problem, "\t\t(is_red l%d c%d)\n", i, ii/2);
            else if (matrix[i][ii] == 'B')
                fprintf(problem, "\t\t(is_blue l%d c%d)\n", i, ii/2);
            else if (matrix[i][ii] == 'G')
                fprintf(problem, "\t\t(is_green l%d c%d)\n", i, ii/2);
            else 
                fprintf(problem, "\t\t(is_off l%d c%d)\n", i, ii/2);

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
	fprintf(problem, "\t)\n\t(:goal (and \n ");
	for (int i = 0; i < p; i++)
		for (int ii = 1; matrix[i][ii] != '\0'; ii += 2)
        	fprintf(problem, "\t\t(is_off l%d c%d)\n", i, ii/2);
	fprintf(problem, ")))\n");
	//fprintf(domain, "(define (domain lightsout_rgb) (:types line column - object) (:predicates(is_off ?l - line ?c - column)(is_red ?l - line ?c - column)(is_blue ?l - line ?c - column)(is_green ?l - line ?c - column)(is_default ?l - line ?c - column)(is_edge ?l - line ?c - column)(is_edgebroken ?l - line ?c - column)(is_hbroken ?l - line ?c - column)(is_vbroken ?l - line ?c - column)(next_h ?l1 ?l2 - line)(next_v ?c1 ?c2 - column))(:action click_default:parameters(?l - line ?c - column):precondition(and(is_default ?l ?c)):effect(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))(forall(?h - column)(when(and(not(is_hbroken ?l ?h))(not(is_edgebroken ?l ?h)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))))(forall(?v - line)(when(and(not(is_vbroken ?v ?c))(not(is_edgebroken ?v ?c)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c))))))(:action click_edge:parameters(?l - line ?c - column):precondition(and(is_edge ?l ?c)):effect(and(forall(?h - column)(when(and(not(is_hbroken ?l ?h))(not(is_edgebroken ?l ?h)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c)))))(forall(?v - line)(when(and(not(is_vbroken ?v ?c))(not(is_edgebroken ?v ?c)))(and(when(is_off ?l ?c)(and(not(is_off ?l ?c))(is_red ?l ?c)))(when(is_red ?l ?c)(and(not(is_red ?l ?c))(is_green ?l ?c)))(when(is_green ?l ?c)(and(not(is_green ?l ?c))(is_blue ?l ?c)))(when(is_blue ?l ?c)(and(not(is_blue ?l ?c))(is_off ?l ?c))))))))))");
	fclose(domain), fclose(problem);
	//printf("MADAGASCAR...\n");
    //system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl > madagascar.plan");
	//printf("DOWNWARD...\n");
    //system("/home/software/planners/downward/fast-downward.py --alias lama domain.pddl problem.pddl");
	return 0;
}
