defmodule Observer do
  
  def add_observer(pid, fun \\ :update) do
    send :observer, {pid, fun}
  end

  def start() do
    Process.register(spawn(fn -> accept([]) end), :observer)
  end

  def run() do
    send(:observer, :run)
  end

  def process(list) do
    process(0, list)
  end

  def process(num, list) do
    if rem(num, 5) == 1 do
      notify_observers(list)
    end
    process(num+1, list)
  end

  defp notify_observers(list) do
    list
      |> Enum.map(fn {_sender, fun} -> fun.() end)
  end

  defp accept(list) do
    receive do
      {sender, fun} -> 
        # send(sender, {self, :ok})
        accept([ {sender, fun} | list ])
      :run ->
        process(list)
      _ ->
        accept(list)
    end
  end

end

fun = fn(name) ->
        fn ->
          IO.puts "#{name}"

Observer.start
Observer.add_observer(self, fun("hello"))
Observer.add_observer(self, fun("world"))
