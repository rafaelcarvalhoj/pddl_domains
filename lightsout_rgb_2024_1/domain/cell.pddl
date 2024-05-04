(define (domain lightsout_rgb)
;	(:requirements :equality :disjunctive-preconditions)
    (:types line column cell - object)
    (:predicates
        ; ========CORES========
        (is_off ?c - cell)
        (is_red ?c - cell)
        (is_blue ?c - cell)
        (is_green ?c - cell)

        ; ======TIPOS DE BOTÃO======
        (is_default ?c - cell)
        (is_edge ?c - cell)
        (is_edgebroken ?c - cell)
        (is_hbroken ?c - cell)
        (is_vbroken ?c - cell)

		; =======CONEXOES=======
		(same_column ?c ?cc - cell)
		(same_line ?c ?cc - cell)
    )
    (:action click
        :parameters (?c - cell)
        :precondition (and )
        :effect (and
                    ; COLOR
					(when (not (is_edge ?c))
						(and(when (is_off ?c) (and (not (is_off ?c)) (is_red ?c)))
						(when (is_red ?c) (and (not (is_red ?c)) (is_green ?c)))
						(when (is_green ?c) (and (not (is_green ?c)) (is_blue ?c)))
						(when (is_blue ?c) (and (not (is_blue ?c)) (is_off ?c)))))
                    ; VERTICAL
                    (forall (?cc - cell) 
							(when
								; PRE
								(and (not(= ?c ?cc)) (same_column ?c ?cc) (not (is_vbroken ?cc)) (not (is_edgebroken ?cc)))
								; EFFECT
								(and 
									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))
									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))
									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))
									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc))))))
                    ; HORIZONTAL
                    (forall (?cc - cell) 
							(when
                            	(and (not(= ?c ?cc)) (same_line ?c ?cc) (not (is_hbroken ?cc)) (not (is_edgebroken ?cc)))
                            	(and
									(when (is_off ?cc) (and (not (is_off ?cc)) (is_red ?cc)))
									(when (is_red ?cc) (and (not (is_red ?cc)) (is_green ?cc)))
									(when (is_green ?cc) (and (not (is_green ?cc)) (is_blue ?cc)))
									(when (is_blue ?cc) (and (not (is_blue ?cc)) (is_off ?cc)))))))
	) 
)
