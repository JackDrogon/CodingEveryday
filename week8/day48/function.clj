(ns function)

(def people ["Lea", "Han Solo"])
(count people) ; => 2
(map count people)
(println (map count people)) ; => (3, 8)

; Named Function
(defn twiced "doc-string" [arg-list]
  )

; Anymous Function
