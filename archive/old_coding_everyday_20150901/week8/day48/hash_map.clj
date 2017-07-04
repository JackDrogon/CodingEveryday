(ns hash_map)


; 哈希表
;;;;;;;;;;

; hash -> {}
(class {:a 1, :b 2, :c 3}) ; => clojure.lang.PersistentArrayMap

; 关键字类似字符串，但是做了一些性能上的优化
(class :a) ; => clojure.lang.Keyword


; Maps 的键可以是任意类型，但是通常推荐使用keywords
(def stringmap (hash-map "a" 1, "b" 2, "c" 3))
stringmap  ; => {"a" 1, "b" 2, "c" 3}

(def keymap (hash-map :a 1 :b 2 :c 3))
keymap ; => {:a 1, :c 3, :b 2} (不保证顺序)

; 顺便说一下, 逗号只是为了看着更清晰，其他都和空格一样，什么都不做.

; 从一个map中检索一个值，可以直接把这个map当做函数调用（这个NB）
(stringmap "a") ; => 1
(keymap :a) ; => 1

; 关键字也可以当做函数来调用，从一个map中检索值（这个更NB）
(:b keymap) ; => 2

; 检索一个不存在的值会返回nil
(stringmap "d") ; => nil

; 使用assoc 向一个map中添加新的键值对。
(assoc keymap :d 4) ; => {:a 1, :b 2, :c 3, :d 4}

; 请记住, clojure 类型是不可变的!
keymap ; => {:a 1, :b 2, :c 3}

; 使用dissoc 来删除key（可以删除多个）
(dissoc keymap :a :b) ; => {:c 3}
