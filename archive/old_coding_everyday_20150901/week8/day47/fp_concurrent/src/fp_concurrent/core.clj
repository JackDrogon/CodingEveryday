(ns fp-concurrent.core
  (:require [clojure.core.reducers :as r]))


(defn recursive-sum [numbers]
  (if (empty? numbers)
    0
    (+ (first numbers) (recursive-sum (rest numbers)))))

(defn reduce-sum [numbers]
  (reduce (fn [acc x] (+ acc x)) 0 numbers))

(defn sum [numbers]
  (reduce + numbers))

(defn parallel-sum [numbers]
  (r/fold + numbers))

(defn word-frequencies [words]
  (reduce
    (fn [counts word] (assoc counts word (inc (get counts word 0))))
    {} words))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println "Hello, World!"))
