#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char matrix[64][64];
int main(void) {
	int p = 0;
	while (scanf(" %s", matrix[p++]) == 1);
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
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
	fprintf(domain, "(define (domain lightsout_rgb) (:types line column cell - object) (:predicates (is_off ?c - cell) (is_red ?c - cell) (is_blue ?c - cell) (is_green ?c - cell) (is_default ?c - cell) (is_edge ?c - cell) (is_edgebroken ?c - cell) (is_hbroken ?c - cell) (is_vbroken ?c - cell) (same_column ?c ?cc - cell) (same_line ?c ?cc - cell)) (:action click :parameters (?c - cell) :precondition (and ) :effect (and ; COLOR (when (not (is_edge ?c)) (and (when (is_off ?c) (and (not (is_off ?c)) (is_red ?c))) (when (is_red ?c) (and (not (is_red ?c)) (is_green ?c))) (when (is_green ?c) (and (not (is_green ?c)) (is_blue ?c))) (when (is_blue ?c) (and (not (is_blue ?c)) (is_off ?c))))) ; VERTICAL (forall (?cc - cell) (when (and (not(= ?c ?cc)) (same_column ?c ?cc) (not (is_vbroken ?cc)) (not (is_edgebroken ?cc))) (and (when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc))) (when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc))) (when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc))) (when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc)))))) ; HORIZONTAL (forall (?cc - cell) (when (and (not(= ?c ?cc)) (same_line ?c ?cc) (not (is_hbroken ?cc)) (not (is_edgebroken ?cc))) (and (when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc))) (when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc))) (when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc))) (when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))))");
	fclose(domain), 
	fclose(problem);
	//printf("MADAGASCAR...\n");
    //system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl > madagascar.plan");
	//printf("DOWNWARD...\n");
    system("/home/software/planners/downward/fast-downward.py --alias lama-first domain.pddl problem.pddl");
	system("sed -E 's/^\\(click c([0-9]+)-([0-9]+).*$/\\(click \\1 \\2\\);/g' sas_plan > out");

	FILE *file = fopen("out", "r");
    char line[100];
	while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "; cost") == NULL) {
            printf("%s", line);
        }
    }
    fclose(file);
	return 0;
}
