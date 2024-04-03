(define (problem library-1)
    (:domain library)
    (:objects
        book1 book2 - book
        shelf1 shelf2 - bookshelf
        cart - libcar
    )
    (:init
        (book-at book1 shelf1)
        (book-at book2 shelf2)
        (libcar-at cart shelf1)
        (next shelf1 shelf2)
        (next shelf2 shelf1) 
        (not (book-car book1 cart))
        (not (book-car book2 cart))
    )
    (:goal 
      (and
        (book-at book1 shelf2)
        (book-at book2 shelf1)
    )
  )
)
