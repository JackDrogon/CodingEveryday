(ns introduction)
(defn blank? [str]
  (every? #(Character/isWhitespace %) str))



(defn hello-world [username]
  (println (format "Hello, %s!" username)))

(hello-world "Jack")
