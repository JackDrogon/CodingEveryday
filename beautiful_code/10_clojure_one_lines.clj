;; Multiple Each Item in a List by 2
(map #(* % 2) (range 1 11))

;; Sum a List of Numbers
(reduce + (range 1 1001))


;; Verify if Word Exists in a String
;; I used a regex here, because I believe that’s the right way to do it.
(def tweet "This is an example tweet talking about clojure and emacs.")
(def regex (re-pattern (apply str (interpose "|" ["clojure" "logic" "compojure" "emacs" "macros"]))))
(re-seq regex tweet) ; Gives me the actual matches instead of just true/false

;; As suggested by a commentator, this problem can be solved without using regex by leveraging Clojure’s sets.
(def tweet "This is an example tweet talking about clojure and emacs.")
(def is-word? (set ["clojure" "logic" "compojure" "emacs" "macros"]))
(not (nil? (some is-word? (.split tweet " ")))) ; Returns true/false


;; Read a File
(def file-text (slurp "data.txt")) ; Reads the whole file
(def file-lines (clojure.contrib.io/read-lines "data.txt")) ; Reads as a sequence of lines
;; Since Clojure Contrib has been deprecated for future Clojure releases, clojure.contrib.io/read-lines can be rewritten as (line-seq (clojure.java.io/reader (clojure.java.io/file “data.txt”))) in Clojure 1.3 onwards. Thanks to Aaron for pointing it out.


;; Happy Birthday to You
(doseq [l (map #(str "Happy Birthday " (if (= % 2) "dear Rich" "to You")) (range 4))] (println l))

;; Alternate version 
(dotimes [n 4] (println "Happy Birthday " (if (= n 2) "dear Rich" "to You")))



;; Filter List of Numbers
(partition-by #(> % 60) [49 58 76 82 88 90])

;; Fetch and Parse XML Web Service
(clojure.xml/parse "http://search.twitter.com/search.atom?&q=clojure")


;; Find Maximum (or Minimum) in a List
(reduce max [14 35 -7 46 98])
(reduce min [14 35 -7 46 98])
;; Now both together
((juxt #(reduce max %) #(reduce min %)) [14 35 -7 46 98]) ; Returns [98 -7]



;; Parallel Processing
; Assuming process-line to be a CPU intensive function that operates on a line
(pmap process-line lines) ; Note the "p" in front of map


;; Sieve of Eratosthenes
; I don’t I have a sufficiently good (in terms of performance & beauty) one line implementation of SoE. I would recommend checking out Christophe Grand’s treatise on the subject titled Everybody loves the Sieve of Eratosthenes for a great discussion on writing real world prime sieves in Clojure.


;; Solve FizzBuzz
(map #(cond (zero? (mod % 15)) "FizzBuzz" (zero? (mod % 3)) "Fizz" (zero? (mod % 5)) "Buzz" :else %) (range 1 101))
