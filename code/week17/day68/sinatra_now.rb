require 'sinatra'
require 'tilt/erubis'
require "sinatra/reloader" if development?

get '/' do
  content_type :text
  now = Time.now
  erb :index, :locals => {:now => now}
end

__END__
@@index
Hello, now is <%= now %>.
