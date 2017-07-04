(ns record)


(defrecord Person [first-name last-name])
(def foo (->Person "Aaron" "Bedra"))


(defrecord Book [title author])
(def b (->Book "Anathem" "Neal Stephenson"))
(println b)
(println (:title b)) ; Error: (println (b :title))
