(ns function)

(def people ["Lea", "Han Solo"])
(count people) ; => 2
(map count people)
(println (map count people)) ; => (3, 8)



; Named Function
; (defn twiced "doc-string" [arg-list])
(defn greeting
  "Returns a greeting of the form 'Hello, username.'
  Default username is 'world'."
  ([] (greeting "world"))
  ([username] (str "Hello, " username)))

(defn date [person-1 person-2 & chaperones]
  (println person-1 "and" person-2
           "went out with" (count chaperones) "chaperones."))



; Anymous Function
; (fn [params*] body)
(require '[clojure.string :as str])
(filter (fn [w] (> (count w) 2)) (str/split "A fine day" #"\W+"))
(filter #(> (count %) 2) (str/split "A fine day it is" #"\W+")) ; #(> (count %) 2)   =>   (fn [w] (> (count w) 2))
(defn indexable-words [text]
  (let [indexable-word? (fn [w] (> (count w) 2))]
    (filter indexable-word? (str/split text #"\W+"))))



; Closure
(defn make-greeter [greeting-prefix]
  (fn [username] (str greeting-prefix ", " username)))

(def hello-greeting (make-greeter "Hello"))
(hello-greeting "world")

(def aloha-greeting (make-greeter "Aloha"))
(aloha-greeting "world")
