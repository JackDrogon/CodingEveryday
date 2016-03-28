#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'sinatra'

get "/" do
  erb :form
end

post '/save_image' do

  @filename = params[:file][:filename]
  file = params[:file][:tempfile]

  File.open("./public/#{@filename}", 'wb') do |f|
    f.write(file.read)
  end

  erb :show_image
end


__END__
@@form
 <html>
      <head>
          <title>Image Upload</title>
      </head>
      <body>
          <h1>Upload Image</h1>

          <form action="http://itp.nyu.edu/~rsm347/sinatra/file_upload/save_image" method="POST" enctype="multipart/form-data">
              <input type="file" name="file">
              <input type="submit" value="Upload image">
          </form>
      </body>
  </html>

@@show_image
 <html>
      <head>
          <title>Show Image</title>
      </head>
      <body>
          <h1>See Image</h1>
          <img src="http://itp.nyu.edu/~rsm347/sinatra/file_upload/public/<%= @filename %>" />
      </body>
  </html>
