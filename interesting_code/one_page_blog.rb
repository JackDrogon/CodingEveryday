require 'rubygems'
require 'sinatra'
require 'sequel'

get '/' do
  env.inspect
end

helpers do
  def h(string)
    string.to_s.gsub('<','&lt;').
      gsub('>','&gt;').gsub('"', '&quot;')
  end
end

configure do
  Sequel.sqlite('blogs.db')
  Sequel::Model.plugin :schema

  class Blog < Sequel::Model
    # unless table_exists?
    #   set_schema do
    #     primary_key :id
    #     string :title
    #     text :body
    #   end
    #   create_table
    # end
    set_schema do
      primary_key :id
      string :title
      text :body
    end
  end
end

get '/blogs' do
  haml :index, :locals => {:blogs => Blog.all}
end

get '/blogs/:id' do
  pass if params[:id] == 'new'
  haml(:show, :locals => {:blog => Blog[:id => params[:id]]}) +
    haml(:back_to_top)
end

get '/blogs/new' do
  haml(:new, :locals => {:blog => Blog.new})+haml(:back_to_top)
end

get '/blogs/:id/edit' do
  haml(:edit, :locals => {:blog => Blog[:id => params[:id]]}) +
    haml(:back_to_top)
end

put '/blogs/:id' do
  blog = Blog.find(:id => params[:id])
  blog.update(:title => params[:title], :body => params[:body])
  blog.save
  redirect "/blogs/#{params[:id]}"
end

post '/blogs' do
  blog = Blog.new(:title => params[:title], :body => params[:body])
  blog.save
  redirect "/blogs"
end

__END__
@@ layout
%html
  %head
    %title blog in sinatra
  %body= yield
@@ index
%div.body
  %table
    %thead
      %tr
        %td title
    %tbody
      - blogs.each do |blog|
        %tr
          %td= h blog.title
          %td
            %a{:href => "/blogs/#{blog.id}"} show
          %td
            %a{:href => "/blogs/#{blog.id}/edit"} edit
  %a{:href => '/blogs/new'} new blog
@@ show
%h3= h blog[:title]
%div= blog[:body]
@@ edit
%form{:action => "/blogs/#{blog.id}", :method => "post"}
  %input{ :type => "hidden", :name => "_method", :value => "put"}
  = haml :form, :locals => {:blog => blog}
</form>
@@ new
%form{:action => "/blogs", :method => "post"}
  = haml :form, :locals => {:blog => blog}
@@ form
%label{:for=>"title"} Description
%br
%input{:name=>"title", :value=>h(blog.title)}
%br
%label{:for => "body"}Content
%br
%textarea{:name => "body"}= blog.body
%br
%input{:type => "submit"}
@@ back_to_top
%div
  %a{ :href => "/blogs"} Back to Top
