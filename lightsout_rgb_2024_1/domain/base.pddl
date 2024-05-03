(define (domain lightsout_rgb)
    (:types line column - object)
    (:predicates
        ; ========CORES========
        (is_off ?l - line ?c - column)
        (is_red ?l - line ?c - column)
        (is_blue ?l - line ?c - column)
        (is_green ?l - line ?c - column)

        ; ======TIPOS DE BOTÃO======
        (is_default ?l - line ?c - column)
        (is_edge ?l - line ?c - column)
        (is_edgebroken ?l - line ?c - column)
        (is_hbroken ?l - line ?c - column)
        (is_vbroken ?l - line ?c - column)
    )
    (:action click_default
        :parameters (?l - line ?c - column)
        :precondition (and (is_default ?l ?c))
        :effect (and
                    ; COLOR
                    (when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
                    (when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_green ?l ?c)))
                    (when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_blue ?l ?c)))
                    (when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_off ?l ?c)))
                    ; VERTICAL
                    (forall (?h - column) 
							(when
								; PRE
								(and (not (is_hbroken ?l ?h)) (not (is_edgebroken ?l ?h)))
								; EFFECT
								(and 
								(when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
								(when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_green ?l ?c)))
								(when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_blue ?l ?c)))
								(when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_off ?l ?c))))))
                    ; HORIZONTAL
                    (forall (?v - line) 
                        (when
                            (and (not (is_vbroken ?v ?c)) (not (is_edgebroken ?v ?c)))
                            (and
								(when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
								(when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_green ?l ?c)))
								(when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_blue ?l ?c)))
								(when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_off ?l ?c))))))
                            )) 
    (:action click_edge
        :parameters (?l - line ?c - column)
        :precondition (and (is_edge ?l ?c))
        :effect (and
                    ; VERTICAL
                    (forall (?h - column) 
							(when
								; PRE
								(and (not (is_hbroken ?l ?h)) (not (is_edgebroken ?l ?h)))
								; EFFECT
								(and 
								(when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
								(when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_green ?l ?c)))
								(when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_blue ?l ?c)))
								(when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_off ?l ?c))))))
                    ; HORIZONTAL
                    (forall (?v - line) 
                        (when
                            (and (not (is_vbroken ?v ?c)) (not (is_edgebroken ?v ?c)))
                            (and
								(when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
								(when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_green ?l ?c)))
								(when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_blue ?l ?c)))
								(when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_off ?l ?c))))))
                            )) 
)
