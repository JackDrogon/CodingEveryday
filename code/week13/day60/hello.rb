class Hello < Struct.new :value, :step
  def inspect
    "hello => #{value}"
  end

  def run
    value = value.split(step)
  end
end
