require 'rubygems'
require 'sinatra'
require 'sass'

get '/upload' do
  erb :upload
end

post '/upload' do
  unless params[:file] &&
      (tempfile = params[:file][:tempfile]) &&
      (filename = params[:file][:filename])
    @error = 'No file selected'
    redirect to('/upload')
  end

  target = "./files/#{filename}"
  File.open(target, 'wb') {|f| f.write tempfile.read }
  # "Upload complete"
  lstr = ""
  system 'ls -l files > ls.tmp'
  File.open("ls../files") do |file|
    while line = file.gets
      lstr += line
      lstr += "<br>"
    end
    file.close();
  end

  "#{lstr}"
end

__END__
@@upload
<form action='/upload' enctype="multipart/form-data" method='POST'>
    <input name="file" type="file" />
    <input type="submit" value="Upload" />
</form>
