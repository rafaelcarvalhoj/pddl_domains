(define (problem lights_out_2x2)
    (:domain lightsout_rgb)
    (:objects l1 - line c1 - column)
    (:init
        ; COLORS
        (is_red l1 c1)
        ; BUTTON TYPE
        (is_default l1 c1)
        ; MATRIX CONNECTION
    )

    (:goal
        (and
            (is_green l1 c1)
        )
    )
)
