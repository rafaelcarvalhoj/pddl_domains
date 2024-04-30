(define (domain lightsout_rgb)
	(:requirements :conditional-effects :universal-preconditions)
    (:types cell)
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

        ; ======CONEXÕES======
       	(vertical ?c1 ?c2 - cell)
		(horizontal ?c1 ?c2 - cell)
    )
	; UMA ACTION PARA CADA TIPO DE BOTAO
    (:action click_default ; DEFAULT
        :parameters (?c - cell)
        :precondition (is_default ?c)
        :effect (and
			(when (is_off ?c) (and (not (is_off ?c)) (is_red ?c)))
			(when (is_red ?c) (and (not (is_red ?c)) (is_blue ?c)))
			(when (is_blue ?c) (and (not (is_blue ?c)) (is_green ?c)))
			(when (is_green ?c) (and (not (is_green ?c)) (is_off))))
			(
				forall(?cn - cell)
				; VERTICAL
				((when (vertical ?c ?cn) ()))
				; HORIZONTAL
			)
		))) 
    )
)
