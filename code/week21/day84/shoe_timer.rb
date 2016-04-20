Shoes.app :title => "Timer", :height => 70, :width => 150 do
  stack do
    @cap = caption "Pope"
    flow do
      @start = button("start") { @t1 = Time.now }
      @stop = button("stop") do
        @t2 = Time.now

        t = 0
        File.open("f:/time", "r") { |file| t = file.gets }

        total_time = @t2 - @t1 + t.to_f
        @cap.text = "#{"%3.4f" % (total_time / 3600)} hours"

        File.open("f:/time", "w") { |file| file.puts total_time  }
      end
    end
  end
end
