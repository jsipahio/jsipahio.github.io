#!/usr/bin/env bash

set -euo pipefail

for dir in */; do
    (
        cd "$dir" || exit

        shopt -s nullglob
        for md in quiz*.md; do
            html="${md%.md}.html"
            pandoc "$md" -f markdown -t html5 -o "$html"
        done
    )
done
