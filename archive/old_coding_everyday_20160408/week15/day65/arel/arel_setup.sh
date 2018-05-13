#!/usr/bin/env bash

# The following script should hopefully get you going in the most bandwidth
# efficient way. Remember to run it in a playground directory. Tested on Ubuntu.

set -e

arel_sha="f50de54a6f0c59ab75526cfdb7896830130ffdf7"
rails_sha="178448ae9d10a27773f548e4b71390391882480f"
format="tar.gz"

if ! type bundle &>/dev/null; then
  echo "error: Install bundler first." >&2
  exit 1
fi

if type wget &>/dev/null; then
  download_tool="wget -O "
elif type curl &>/dev/null; then
 download_tool="curl -L -o "
else
  echo "error: Install wget or curl" >&2
  exit 1
fi

$download_tool $arel_sha.$format https://github.com/rails/arel/archive/$arel_sha.$format
$download_tool $rails_sha.$format https://github.com/rails/rails/archive/$rails_sha.$format

tar xfz $arel_sha.$format
tar xfz $rails_sha.$format

bundle init
bundle config --local console pry

cat <<EOF >> Gemfile
gem "arel", path: "./arel-$arel_sha"
gem "activerecord", path: "./rails-$rails_sha", require: "active_record"
gem "sqlite3", "~> 1.3.9"
gem "pry", "~> 0.9.12"
EOF

cat <<EOF > .pryrc
Pry.config.pager = false
EOF

bundle install
bundle console
