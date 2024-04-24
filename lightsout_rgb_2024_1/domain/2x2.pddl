(define (problem lights_out_2x2)
    (:domain lightsout_rgb)
    (:objects l1 l2 - line c1 c2 - column)
    (:init
        ; COLORS
        (is_red l1 c1) (is_red l1 c2)
        (is_red l2 c1) (is_off l2 c2)
        ; BUTTON TYPE
        (is_default l1 c1) (is_default l1 c2)
        (is_default l2 c1) (is_default l2 c2)
        ; MATRIX CONNECTION
        next_h(c1 c2)
        next_h(c2 c1)
        next_v(l1 l2)
        next_v(l2 l1)
    )

    (:goal
        (and
            (is_green l1 c1) (is_green l1 c2)
            (is_green l2 c1) (is_green l2 c2)
        )
    )
)
