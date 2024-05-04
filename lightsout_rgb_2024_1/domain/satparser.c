#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char matrix[64][64];
int main(void) {
	int p = 0;
	while (scanf(" %s", matrix[p++]) == 1);
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout_rgb)\n\t(:objects");
	int max_column_size = 0;
    for (int i = 0; i < p || matrix[i][0] != 0; i++){
		int isize = strlen(matrix[i])/2;
		if(isize > max_column_size) max_column_size = isize;
	}
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
	fprintf(domain, "(define (domain lightsout_rgb)\n");
    fprintf(domain, "    (:types line column cell - object)\n");
    fprintf(domain, "    (:predicates\n");
    fprintf(domain, "        (is_off ?c - cell)\n");
    fprintf(domain, "        (is_red ?c - cell)\n");
    fprintf(domain, "        (is_blue ?c - cell)\n");
    fprintf(domain, "        (is_green ?c - cell)\n");
    fprintf(domain, "        (is_default ?c - cell)\n");
    fprintf(domain, "        (is_edge ?c - cell)\n");
    fprintf(domain, "        (is_edgebroken ?c - cell)\n");
    fprintf(domain, "        (is_hbroken ?c - cell)\n");
    fprintf(domain, "        (is_vbroken ?c - cell)\n");
    fprintf(domain, "        (same_column ?c ?cc - cell)\n");
    fprintf(domain, "        (same_line ?c ?cc - cell))\n");
    fprintf(domain, "    (:action click\n");
    fprintf(domain, "        :parameters (?c - cell)\n");
    fprintf(domain, "        :precondition (and )\n");
    fprintf(domain, "        :effect (and\n");
    fprintf(domain, "                    ; COLOR\n");
    fprintf(domain, "					(when (not (is_edge ?c))\n");
    fprintf(domain, "                    (and(when (is_off ?c) (and (not (is_off ?c)) (is_red ?c)))\n");
    fprintf(domain, "                    (when (is_red ?c) (and (not (is_red ?c)) (is_green ?c)))\n");
    fprintf(domain, "                    (when (is_green ?c) (and (not (is_green ?c)) (is_blue ?c)))\n");
    fprintf(domain, "                    (when (is_blue ?c) (and (not (is_blue ?c)) (is_off ?c)))))\n");
    fprintf(domain, "                    ; VERTICAL\n");
    fprintf(domain, "                    (forall (?cc - cell)\n");
    fprintf(domain, "							(when\n");
    fprintf(domain, "								; PRE\n");
    fprintf(domain, "								(and (not(= ?c ?cc)) (same_column ?c ?cc) (not (is_vbroken ?cc)) (not (is_edgebroken ?cc)))\n");
    fprintf(domain, "								; EFFECT\n");
    fprintf(domain, "								(and\n");
    fprintf(domain, "									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))\n");
    fprintf(domain, "									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))\n");
    fprintf(domain, "									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))\n");
    fprintf(domain, "									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))\n");
    fprintf(domain, "                    ; HORIZONTAL\n");
    fprintf(domain, "                    (forall (?cc - cell)\n");
    fprintf(domain, "							(when\n");
    fprintf(domain, "                            	(and (not(= ?c ?cc)) (same_line ?c ?cc) (not (is_hbroken ?cc)) (not (is_edgebroken ?cc)))\n");
    fprintf(domain, "                            	(and\n");
    fprintf(domain, "									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))\n");
    fprintf(domain, "									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))\n");
    fprintf(domain, "									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))\n");
    fprintf(domain, "									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))))\n");
    fprintf(domain, ")");
	fclose(domain), 
	fclose(problem);
    
	system("/tmp/dir/software/planners/downward/fast-downward.py --alias seq-sat-lama-2011 domain.pddl problem.pddl > /dev/null");
    
    FILE *sas_plan;
	int i = 1;
	char filename[20];
	while(true){
		sprintf(filename, "sas_plan.%d", i);
		if ((sas_plan = fopen(filename, "r")) == NULL)
			break;
		fclose(sas_plan);
		i++;
	}
	sprintf(filename, "sas_plan.%d", i-1);
	if ((sas_plan = fopen(filename, "r")) != NULL) {
		char cmd[200];
		sprintf(cmd, "sed -E 's/^\\(click c([0-9]+)-([0-9]+).*$/\\(click \\1 \\2\\);/g' sas_plan.%d > out", i-1);
		system(cmd);
		FILE *file = fopen("out", "r");
		char line[100];
		while(fgets(line, sizeof(line), file)) {
			if (strstr(line, "; cost") == NULL) {
				printf("%s", line);
			}
		}
		fclose(file);
		fclose(sas_plan);
	} else {
		while(1){
			// sem wa dessa vez
		}
	}
	return 0;
}
