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

        ; ======CONEXÕES======
        (next_h ?l1 ?l2 - line)
        (next_v ?c1 ?c2 - column)
    )
    (:action click
        :parameters (?l - line ?c - column)
        :precondition (and )
        :effect (and
            (when 
                (is_default ?l ?c) ; DEFAULT
                (and 
                    ; COLOR
                    (when (is_off ?l ?c) (and (not (is_off ?l ?c)) (is_red ?l ?c)))
                    (when (is_red ?l ?c) (and (not (is_red ?l ?c)) (is_blue ?l ?c)))
                    (when (is_blue ?l ?c) (and (not (is_blue ?l ?c)) (is_green ?l ?c)))
                    (when (is_green ?l ?c) (and (not (is_green ?l ?c)) (is_off ?l ?c)))
                    ; VERTICAL
                    (forall (?h - column) 
							(when
								; PRE
								(and (not (is_hbroken ?l ?h)) (not (is_edgebroken ?l ?h)))
								; EFFECT
								(and 
								(when(is_off ?l ?h) (and (not (is_off ?l ?h)) (is_red ?l ?h)))
								(when(is_red ?l ?h) (and (not (is_red ?l ?h)) (is_blue ?l ?h)))
								(when(is_blue ?l ?h) (and (not (is_blue ?l ?h)) (is_green ?l ?h)))
								(when(is_green ?l ?h) (and (not (is_green ?l ?h)) (is_off ?l ?h))))))
                    ; HORIZONTAL
                    (forall (?v - line) 
                        (when
                            (and (not (is_vbroken ?v ?c)) (not (is_edgebroken ?v ?c)))
                            (and
                                (when(is_off ?v ?c) (and (not (is_off ?v ?c)) (is_red ?v ?c)))
                                (when(is_red ?v ?c) (and (not (is_red ?v ?c)) (is_blue ?v ?c)))
                                (when(is_blue ?v ?c) (and (not (is_blue ?v ?c)) (is_green ?v ?c)))
                                (when(is_green ?v ?c) (and (not (is_green ?v ?c)) (is_off ?v ?c)))
                            ))))     
            )
        )
    )
)
