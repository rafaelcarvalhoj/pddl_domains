(define (domain library)
    (:types book bookshelf libcar - object )
    (:predicates
        (book-at ?b - book ?bs - bookshelf)
        (book-car ?b - book ?c - libcar)
        (libcar-at ?c - libcar ?bs - bookshelf)
        (next ?bs1 - bookshelf ?bs2 - bookshelf) 
    )
    (:action move-front
        :parameters (?c - libcar ?bs1 - bookshelf ?bs2 - bookshelf)
        :precondition (and (libcar-at ?c ?bs1) (next ?bs1 ?bs2))
        :effect (and (libcar-at ?c ?bs2) (not (libcar-at ?c ?bs1)))
    )
    (:action move-back
        :parameters (?c - libcar ?bs1 - bookshelf ?bs2 - bookshelf)
        :precondition (and (libcar-at ?c ?bs1) (next ?bs2 ?bs1))
        :effect (and (libcar-at ?c ?bs2) (not (libcar-at ?c ?bs1)))
    )
    (:action take-book
        :parameters (?c - libcar ?bs1 - bookshelf ?b - book)
        :precondition (and (book-at ?b ?bs1) (libcar-at ?c ?bs1) (not (book-car ?b ?c)))
        :effect (not (book-at ?b ?bs1) ())
    )
    (:action
        :parameters (?c - libcar ?bs1 - bookshelf ?b - book)
        :precondition (and (libcar-at ?c ?bs1) (not (book-at ?b ?bs1)) (book-car ?b ?c))
        :effect (and (book-at ?b ?bs1) (not (book-car ?b ?c)))
    )
 )
