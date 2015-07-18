#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'net/http'
require 'json'

GITHUB_URL = "https://api.github.com"

user = "dynamo"
project = "dynamo"

repo_issue_url = "#{GITHUB_URL}/repos/#{user}/#{project}/issues"
repo_issue_uri = URI(repo_issue_url)

repo_issue_json = Net::HTTP.get(repo_issue_uri)
repo_issue_json = JSON.parse(repo_issue_json)


puts repo_issue_url
#puts repo_issue_json
repo_issue_json.each { |issue| puts "#{issue['url']}, created_at: #{issue['created_at']}" }
