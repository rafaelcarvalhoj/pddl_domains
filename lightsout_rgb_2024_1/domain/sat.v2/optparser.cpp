#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <utility>

#define type(A) ((*A).first)
#define color(A) ((*A).second)

using namespace std;

int main(void) {
	int p = 0;
	string s;
	vector<vector<pair<char, char>>> matrix;
	while (cin >> s){
		vector<pair<char, char>> temp;
        for (string::iterator it = s.begin(); it != s.end(); it += 2) {
            temp.push_back(pair<char, char>{*it, *(it + 1)});
        }
        matrix.push_back(temp);
	}
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout_rgb)\n\t(:objects");
	int max_column_size = 0;
    for (auto it = matrix.begin(); it != matrix.end(); ++it){
		if((*it).size() > max_column_size) max_column_size = (*it).size();
	}
	int m = 0, n = 0;	
	for (auto i = matrix.begin(); i != matrix.end(); ++i, m++) {
        for (auto j = i->begin(); j != i->end(); ++j, n++) {
			fprintf(problem, " c%d-%d", m, n);
        }
		n = 0;
    }
	m = 0; n = 0;
	fprintf(problem, " - cell)\n\t(:init\n");	
	for (auto i = matrix.begin(); i != matrix.end(); ++i, m++){ 
        for (auto it = i->begin(); it != i->end(); ++it, n++) {
            if (color(it) == 'R')
                fprintf(problem, "\t\t(is_red c%d-%d)\n", m, n);
            else if (color(it) == 'B')
                fprintf(problem, "\t\t(is_blue c%d-%d)\n", m, n);
            else if (color(it) == 'G')
                fprintf(problem, "\t\t(is_green c%d-%d)\n", m, n);
            else 
                fprintf(problem, "\t\t(is_off c%d-%d)\n", m, n);

            if(type(it) == '-')
                fprintf(problem, "\t\t(is_default c%d-%d)\n", m, n);
            else if(type(it) == '*')
                fprintf(problem, "\t\t(is_edge c%d-%d)\n", m, n);
            else if(type(it) == '_')
                fprintf(problem, "\t\t(is_vbroken c%d-%d)\n", m, n);
            else if(type(it) == '|')
                fprintf(problem, "\t\t(is_hbroken c%d-%d)\n", m, n);
            else 
                fprintf(problem, "\t\t(is_edgebroken c%d-%d)\n", m, n);

			int bt = 0;
        	for (auto it2 = i->begin(); it2 != i->end(); ++it2, bt++)
			   	if(n != bt)
			        fprintf(problem, "\t\t(same_line c%d-%d c%d-%d)\n", m, n, m, bt);
			
			int column_max = matrix.size();
			for(int j = 0 ; j < column_max ; j++)
				if(matrix[j].size() > n && m != j)
	        		fprintf(problem, "\t\t(same_column c%d-%d c%d-%d)\n", m, n, j, n);
        	fprintf(problem, "\n");
		} 
		n = 0;
	}
	fprintf(problem, "\t)\n\t(:goal (and \n ");
	m = 0; n = 0;
	for (auto i = matrix.begin(); i != matrix.end(); ++i, m++) {
        for (auto j = i->begin(); j != i->end(); ++j, n++) {
        	fprintf(problem, "\t\t(is_off c%d-%d)\n", m, n);
        }
		n = 0;
    }
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
    fprintf(domain, "								(and (same_column ?c ?cc) (not (is_vbroken ?cc)) (not (is_edgebroken ?cc)))\n");
    fprintf(domain, "								; EFFECT\n");
    fprintf(domain, "								(and\n");
    fprintf(domain, "									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))\n");
    fprintf(domain, "									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))\n");
    fprintf(domain, "									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))\n");
    fprintf(domain, "									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))\n");
    fprintf(domain, "                    ; HORIZONTAL\n");
    fprintf(domain, "                    (forall (?cc - cell)\n");
    fprintf(domain, "							(when\n");
    fprintf(domain, "                            	(and (same_line ?c ?cc) (not (is_hbroken ?cc)) (not (is_edgebroken ?cc)))\n");
    fprintf(domain, "                            	(and\n");
    fprintf(domain, "									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))\n");
    fprintf(domain, "									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))\n");
    fprintf(domain, "									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))\n");
    fprintf(domain, "									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))))\n");
    fprintf(domain, ")");
	fclose(domain), fclose(problem);
    
	//system("/tmp/dir/software/planners/downward/fast-downward.py --alias seq-sat-fdss-2018 --overall-time-limit 179s domain.pddl problem.pddl > /dev/null");
	system("/home/software/planners/downward/fast-downward.py --alias seq-opt-merge-and-shrink --overall-time-limit 179s domain.pddl problem.pddl > /dev/null");

    FILE *sas_plan;
    if ((sas_plan = fopen("sas_plan", "r")) != NULL) {
        system("sed -E 's/^\\(click c([0-9]+)-([0-9]+).*$/\\(click \\1 \\2\\);/g' sas_plan > out");
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
		exit(200);
	}
	return 0;
}
