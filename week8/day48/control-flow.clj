(ns control-flow)

; Flow Control
; if, cond, for, loop

; if expression
(defn abs [x]
  (if (< x 0) (- x) x))

(println (abs 10))
(println (abs -10))


(defn haha [x]
  (if (< x 0)
    (- x)
    (do
      (println "Haha")
     x)))
(println (haha 10))
(println (haha -10))



; cond expression
(def x 10)
(cond (= x 10) "equal"
      (> x 10) "more")

; for expression
(def colors ["red", "black", "white"])
(println colors)
(for [x colors] (println x))
